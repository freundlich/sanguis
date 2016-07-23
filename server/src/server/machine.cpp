#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/server/load.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/net_id_from_player.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/net/deserialize.hpp>
#include <sanguis/server/net/serialize_to_circular_buffer.hpp>
#include <sanguis/server/net/serialize_to_data_buffer.hpp>
#include <alda/net/id.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <sge/timer/difference_fractional.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <fcppt/const.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::machine::machine(
	fcppt::log::context &_log_context,
	alda::net::port const _port,
	sanguis::io_service &_io_service
)
:
	log_context_{
		_log_context
	},
	log_{
		_log_context,
		sanguis::server::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("machine")
			}
		)
	},
	resources_(),
	port_(
		_port
	),
	io_service_(
		_io_service
	),
	net_(
		alda::net::parameters(
			_log_context,
			io_service_.impl(),
			sanguis::net::send_buffer_size(),
			sanguis::net::receive_buffer_size()
		)
	),
	desired_frame_time_{
		std::chrono::milliseconds(
			16
		)
	},
	frame_timer_(
		sanguis::timer::parameters(
			desired_frame_time_
		)
	),
	temp_buffer_(),
	overflow_messages_(),
	timer_(
		io_service_,
		sanguis::server::timer_callback{
			std::bind(
				std::bind(
					&sanguis::server::machine::timer_callback,
					this
				)
			)
		},
		desired_frame_time_
	),
	disconnect_connection_(
		net_.register_disconnect(
			alda::net::server::disconnect_callback{
				std::bind(
					&sanguis::server::machine::disconnect_callback,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	data_connection_(
		net_.register_data(
			alda::net::server::data_callback{
				std::bind(
					&sanguis::server::machine::data_callback,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	)
{
}

sanguis::server::machine::~machine()
{
}

void
sanguis::server::machine::listen()
{
	net_.listen(
		port_
	);
}

void
sanguis::server::machine::send_to_all(
	sanguis::messages::server::base const &_message
)
{
	temp_buffer_.clear();

	sanguis::server::net::serialize_to_data_buffer(
		_message,
		temp_buffer_
	);

	alda::net::server::connection_id_container const connections(
		net_.connections()
	);

	for(
		auto const &id
		:
		connections
	)
	{
		if(
			!sanguis::net::append_to_circular_buffer(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					net_.send_buffer(
						id
					)
				).get(),
				temp_buffer_
			)
		)
		{
			this->add_overflow_message(
				id,
				_message
			);

			continue;
		}

		net_.queue_send(
			id
		);
	}
}

bool
sanguis::server::machine::process_overflow()
{
	bool overflow_remaining{
		false
	};

	for(
		auto &queue_pair
		:
		overflow_messages_
	)
	{
		sanguis::server::machine::overflow_message_queue &queue(
			queue_pair.second
		);

		while(
			!queue.empty()
		)
		{
			sanguis::messages::server::unique_ptr const &message(
				queue.front()
			);

			alda::net::id const net_id(
				queue_pair.first
			);

			if(
				sanguis::server::net::serialize_to_circular_buffer(
					*message,
					FCPPT_ASSERT_OPTIONAL_ERROR(
						net_.send_buffer(
							net_id
						)
					).get()
				)
			)
				queue.pop();
			else
				break;
		}

		overflow_remaining =
			!queue.empty()
			||
			overflow_remaining;
	}

	return
		overflow_remaining;
}

void
sanguis::server::machine::send_unicast(
	sanguis::server::player_id const _id,
	sanguis::messages::server::base const &_message
)
{
	alda::net::id const net_id(
		sanguis::server::net_id_from_player(
			_id
		)
	);

	fcppt::optional::maybe(
		net_.send_buffer(
			net_id
		),
		[
			this,
			net_id
		]{
			FCPPT_LOG_INFO(
				log_,
				fcppt::log::_
					<< FCPPT_TEXT("Client ")
					<< net_id
					<< FCPPT_TEXT(" is gone.")
			);
		},
		[
			&_message,
			this,
			net_id
		](
			fcppt::reference<
				alda::net::buffer::circular_send::streambuf
			> const _buffer
		)
		{
			if(
				!sanguis::server::net::serialize_to_circular_buffer(
					_message,
					_buffer.get()
				)
			)
			{
				this->add_overflow_message(
					net_id,
					_message
				);

				return;
			}

			net_.queue_send(
				net_id
			);
		}
	);
}

sanguis::server::load const &
sanguis::server::machine::resources() const
{
	return
		resources_;
}

fcppt::log::context &
sanguis::server::machine::log_context() const
{
	return
		log_context_;
}

void
sanguis::server::machine::process_message(
	alda::net::id const _id,
	sanguis::messages::client::unique_ptr &&_message
)
{
	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("process_message")
	);

	this->process_event(
		sanguis::server::events::message(
			std::move(
				_message
			),
			sanguis::server::player_id_from_net(
				_id
			)
		)
	);
}

void
sanguis::server::machine::add_overflow_message(
	alda::net::id const _id,
	sanguis::messages::server::base const &_message
)
{
	overflow_messages_[
		_id
	].push(
		_message.clone()
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Client ")
			<< _id
			<< FCPPT_TEXT(" has no space left!")
	);
}

void
sanguis::server::machine::disconnect_callback(
	alda::net::id const _id,
	fcppt::string const &_error
)
{
	FCPPT_LOG_INFO(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Client ")
			<< _id
			<< FCPPT_TEXT(" disconnected: ")
			<< _error
	);

	this->disconnect_player(
		_id
	);
}

void
sanguis::server::machine::data_callback(
	alda::net::id const _id,
	alda::net::buffer::circular_receive::streambuf &_data
)
try
{
	while(
		fcppt::optional::maybe(
			sanguis::server::net::deserialize(
				_data
			),
			fcppt::const_(
				false
			),
			[
				this,
				_id
			](
				sanguis::messages::client::unique_ptr &&_message
			)
			{
				try
				{
					this->process_message(
						_id,
						std::move(
							_message
						)
					);
				}
				catch(
					sanguis::server::unknown_player_exception const &_error
				)
				{
					FCPPT_LOG_DEBUG(
						log_,
						fcppt::log::_
							<< FCPPT_TEXT("Client currently has no player ")
							<< _error.string()
					);
				}

				return
					true;
			}
		)
	)
		;
}
catch(
	fcppt::exception const &_error
)
{
	this->data_error(
		_id,
		_error.string()
	);
}
catch(
	...
)
{
	this->data_error(
		_id,
		FCPPT_TEXT("Unknown error")
	);
}

void
sanguis::server::machine::disconnect_player(
	alda::net::id const _id
)
{
	overflow_messages_.erase(
		_id
	);

	this->process_event(
		sanguis::server::events::disconnect(
			_id
		)
	);
}

void
sanguis::server::machine::data_error(
	alda::net::id const _id,
	fcppt::string const &_error
)
{
	FCPPT_LOG_ERROR(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Error while processing message from client ")
			<< _id
			<< FCPPT_TEXT(": ")
			<< _error
	);

	net_.disconnect(
		_id
	);

	this->disconnect_player(
		_id
	);
}

void
sanguis::server::machine::timer_callback()
{
	sanguis::slowdown const slowdown{
		sge::timer::difference_fractional<
			sanguis::slowdown::value_type
		>(
			frame_timer_
		)
	};

	this->process_event(
		sanguis::server::events::tick(
			std::chrono::duration_cast<
				sanguis::duration
			>(
				sge::timer::elapsed_and_reset(
					frame_timer_
				)
			),
			slowdown
		)
	);
}
