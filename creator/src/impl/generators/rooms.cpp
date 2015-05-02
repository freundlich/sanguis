#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/filled_rect.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/place_boss.hpp>
#include <sanguis/creator/impl/rect.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/set_opening_tiles.hpp>
#include <sanguis/creator/impl/generators/rooms.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_size.hpp>
#include <sanguis/creator/impl/random/uniform_size_variate.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/object.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices_advanced.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{
	enum class
	edge
	{
		none,
		right,
		top,
		left,
		bottom
	};

	using signed_rect =
		fcppt::math::box::object<
			sanguis::creator::difference_type,
			2
		>;

	using pos_type =
		sanguis::creator::signed_pos;

	using int_type =
		pos_type::value_type;

	struct
	line
	{
		pos_type p1;
		pos_type p2;
	};

	pos_type
	topleft(
		::signed_rect const &_rect
	)
	{
		return
			_rect.pos();
	}

	pos_type
	topright(
		::signed_rect const &_rect
	)
	{
		return pos_type{
			_rect.right(),
			_rect.top()
		};
	}

	pos_type
	bottomleft(
		::signed_rect const &_rect
	)
	{
		return pos_type{
			_rect.left(),
			_rect.bottom()
		};
	}

	pos_type
	bottomright(
		::signed_rect const &_rect
	)
	{
		return
			_rect.pos() + _rect.size();
	}

	::line
	side(
		::signed_rect const &_rect,
		::edge _edge
	){

		switch(_edge)
		{
			case ::edge::top:
				return ::line{topleft(_rect), topright(_rect)};
			case ::edge::left:
				return ::line{topleft(_rect), bottomleft(_rect)};
			case ::edge::bottom:
				return ::line{bottomleft(_rect), bottomright(_rect)};
			case ::edge::right:
				return ::line{topright(_rect), bottomright(_rect)};
			default:
				throw sanguis::creator::exception(
					FCPPT_TEXT("there are only four sides to a rectangle!"));
		}
	}

	bool
	intersect(
		::line const &_line,
		::signed_rect const &_rect
	)
	{
		return
			_line.p2.x() >= _rect.left() &&
			_line.p2.y() >= _rect.top() &&
			_line.p1.x() <= _rect.left() + _rect.w() &&
			_line.p1.y() <= _rect.top() + _rect.h();
	}

	::edge
	clip(
		::signed_rect &cur,
		::signed_rect const &other
	)
	{

		::edge last{
			::edge::none
		};

		if (
			fcppt::math::box::contains_point(cur, cur.pos()) &&
			fcppt::math::box::contains_point(cur, ::bottomright(other))
		)
		{
			cur.w(other.left() - cur.left() - 1);
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::top), other)
		)
		{
			::int_type oldy = cur.top();
			cur.top(other.bottom() + 1);
			cur.h(cur.h() - (cur.top() - oldy));
			last = ::edge::top;
		}

		if (
			intersect(::side(cur, ::edge::right), other)
		)
		{
			cur.w(other.left() - cur.left() - 1);
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::bottom), other)
		)
		{
			cur.h(other.top() - cur.top() - 1);
			last = ::edge::bottom;
		}

		if (
			intersect(::side(cur, ::edge::left), other)
		)
		{
			::int_type oldx = cur.left();
			cur.left(
				other.right() + 1);
			cur.w(cur.w() - (cur.left() - oldx));
			last = ::edge::left;
		}

		return last;
	}
}

sanguis::creator::impl::result
sanguis::creator::impl::generators::rooms(
	sanguis::creator::impl::parameters const &_parameters
)
{
	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::impl::random::uniform_int<
			::int_type
		>
	>
	uniform_int2;

	sanguis::creator::grid::dim const size{
		100u,
		75u
	};

	auto rand_int =
		[&_parameters]
		(
			 ::int_type const min,
			 ::int_type const max
		 )
		{
			return
			fcppt::random::make_variate(
				_parameters.randgen(),
				uniform_int2{
					uniform_int2::param_type::min{
						min
					},
					uniform_int2::param_type::max{
						max
					}
				}
			);
		};

	sanguis::creator::grid
	grid{
		sanguis::creator::grid::dim{
			size
		},
		sanguis::creator::tile::nothing
	};

	sanguis::creator::background_grid
	bg_grid{
		grid.size(),
		sanguis::creator::background_tile::space
	};

	::int_type startw =
		rand_int(10, 20)();
	::int_type starth =
		rand_int(10, 20)();

	std::vector<
		::signed_rect
	>
	rects{
		::signed_rect{
			::signed_rect::vector{
				rand_int(0, static_cast<::int_type>(size.w()) - startw - 1)(),
				rand_int(0, static_cast<::int_type>(size.h()) - starth - 1)()
			},
			::signed_rect::dim{
				startw,
				starth
			}
		}
	};

	using corridor =
		std::pair<
			::pos_type,
			::edge
		>;

	std::vector<
		corridor
	>
	corridors;

	for (
		::int_type i = 0;
		i < 100;
		++i
	)
	{
		::signed_rect rect;

		{
			::int_type const w = rand_int(5, std::min(15 + i/2, static_cast<::int_type>(size.w() - 1)))();
			::int_type const h = rand_int(5, std::min(15 + i/2, static_cast<::int_type>(size.h() - 1)))();
			::int_type const x = rand_int(0, static_cast<::int_type>(size.w()) - w - 1)();
			::int_type const y = rand_int(0, static_cast<::int_type>(size.h()) - h - 1)();

			rect = ::signed_rect{
				::signed_rect::vector{
					x,
					y
				},
				::signed_rect::dim{
					w,
					h
				}
			};
		}

		bool
		wellformed{
			true};

		::edge
		clipped_edge{
			::edge::none};


		typedef
		fcppt::optional<
			::signed_rect
		>
		optional_signed_rect;

		optional_signed_rect opt_neighbor;

		for (
			auto const &other
			:
			rects
		)
		{
			::edge e =
				::clip(
					rect,
					other);

			// rect has just been clipped with other,
			// so it's next to it
			if (e != ::edge::none)
			{
				opt_neighbor =
					optional_signed_rect(
						other
					);

				clipped_edge = e;
			}

			wellformed =
				rect.w() > 2
				&&
				rect.h() > 2;

			// rect has been clipped into oblivion, discard it
			if (!wellformed)
				break;
		}

		if (!wellformed || !opt_neighbor.has_value())
			continue;

		::signed_rect const neighbor(
			opt_neighbor.get_unsafe()
		);

		switch (clipped_edge)
		{
			case ::edge::top:
			case ::edge::bottom:
			{
				int_type xmin{
					std::max(
						rect.left(),
						neighbor.left()
					) +
					1
				};

				int_type xmax{
					std::min(
						rect.right(),
						neighbor.right()
					) -
					2
				};

				if (xmin >= xmax)
					continue;

				::int_type x{
					rand_int(xmin, xmax)()
				};

				corridors.push_back(
					std::make_pair(
						::pos_type{
							x,
							clipped_edge == ::edge::top
							?
							rect.top()
							:
							rect.bottom()
						},
						clipped_edge));

				break;
			}
			case ::edge::left:
			case ::edge::right:
			{
				int_type const ymin{
					std::max(
						rect.top(),
						neighbor.top()
					) +
					1
				};

				int_type const ymax{
					std::min(
						rect.bottom(),
						neighbor.bottom()
					) -
					2
				};

				if (ymin >= ymax)
					continue;

				::int_type const y{
					rand_int(ymin, ymax)()
				};

				corridors.push_back(
					std::make_pair(
						::pos_type{
							clipped_edge == ::edge::left
							?
							rect.left()
							:
							rect.right(),
							y
						},
						clipped_edge));

				break;
			}
			default:
				FCPPT_ASSERT_UNREACHABLE;
		}

		rects.push_back(
			rect);
	}

	for (
		auto const &rect
		:
		rects
	)
	{
		sanguis::creator::impl::rect(
			fcppt::math::box::structure_cast<
				sanguis::creator::rect,
				fcppt::cast::size_fun
			>(
				rect
			),
			[
				&grid
			]
			(sanguis::creator::pos const _pos)
			{
				grid[
					_pos
				]
				=
				sanguis::creator::tile::concrete_wall;
			}
		);

		sanguis::creator::impl::filled_rect(
			fcppt::math::box::structure_cast<
				sanguis::creator::rect,
				fcppt::cast::size_fun
			>(
				rect
			),
			[
				&bg_grid
			]
			(sanguis::creator::pos const _pos)
			{
				bg_grid[
					_pos
				]
				=
				sanguis::creator::background_tile::space_floor;
			}
		);
	}

	auto const
	set_tile(
		[
			&grid,
			&bg_grid
		]
		(
			::pos_type input_pos,
			sanguis::creator::tile tile
		)
		{
			auto pos(
				fcppt::math::vector::structure_cast<
					sanguis::creator::pos,
					fcppt::cast::to_unsigned_fun
				>(
					input_pos
				)
			);

			grid[
				pos
			] =
				tile;

			bg_grid[
				pos
			] =
				sanguis::creator::background_tile::space_floor;
		}
	);

	for (auto const &corr : corridors)
	{
		::pos_type const &pos{corr.first};
		::edge const &e{corr.second};

		using sanguis::creator::tile;

		switch (e)
		{
			case ::edge::top:
			{
				set_tile(pos + ::pos_type{ 0, -1 }, tile::nothing);
				set_tile(pos + ::pos_type{ 0, -2 }, tile::nothing);
				set_tile(pos + ::pos_type{ -1, -1 }, tile::concrete_wall);
				set_tile(pos + ::pos_type{ +1, -1 }, tile::concrete_wall);
				set_tile(pos, tile::space_door_open_h);
				break;
			}
			case ::edge::bottom:
			{
				set_tile(pos + ::pos_type{ 0, -1 }, tile::nothing);
				set_tile(pos + ::pos_type{ 0, +1 }, tile::nothing);
				set_tile(pos + ::pos_type{ -1, 0 }, tile::concrete_wall);
				set_tile(pos + ::pos_type{ +1, 0 }, tile::concrete_wall);
				set_tile(pos, tile::space_door_open_h);
				break;
			}
			case ::edge::left:
			{
				set_tile(pos + ::pos_type{ -1, 0 }, tile::nothing);
				set_tile(pos + ::pos_type{ -2, 0 }, tile::nothing);
				set_tile(pos + ::pos_type{ -1, -1 }, tile::concrete_wall);
				set_tile(pos + ::pos_type{ -1, +1 }, tile::concrete_wall);
				set_tile(pos, tile::space_door_open_v);
				break;
			}
			case ::edge::right:
			{
				set_tile(pos + ::pos_type{ -1, 0 }, tile::nothing);
				set_tile(pos + ::pos_type{ +1, 0 }, tile::nothing);
				set_tile(pos + ::pos_type{ 0, -1 }, tile::concrete_wall);
				set_tile(pos + ::pos_type{ 0, +1 }, tile::concrete_wall);
				set_tile(pos, tile::space_door_open_v);
				break;
			}
			default:
				FCPPT_ASSERT_UNREACHABLE;
		}
	}

	auto
	rect_to_pos(
		[]
		(
			signed_rect _rect
		)
		{
			return
				fcppt::math::vector::structure_cast<
					sanguis::creator::pos,
					fcppt::cast::to_unsigned_fun
				>
				(
					fcppt::math::box::center(
						_rect)
				);
		}
	);

	sanguis::creator::opening_container_array const
	openings(
		fcppt::algorithm::enum_array_fold<
			sanguis::creator::opening_container_array
		>(
			[
				&rect_to_pos,
				&rects
			](
				sanguis::creator::opening_type const _type
			)
			{
				switch(
					_type
				)
				{
				case sanguis::creator::opening_type::entry:
					return
						sanguis::creator::opening_container{
							sanguis::creator::opening{
								rect_to_pos(
									rects.front()
								)
							}
						};
				case sanguis::creator::opening_type::exit:
					return
						sanguis::creator::opening_container{
							sanguis::creator::opening{
								rect_to_pos(
									rects.back()
								)
							}
						};
				}

				FCPPT_ASSERT_UNREACHABLE;
			}
		)
	);

	sanguis::creator::impl::set_opening_tiles(
		grid,
		openings
	);

	sanguis::creator::spawn_container
	spawners{};

	if(
		_parameters.spawn_boss().get()
	)
		spawners.push_back(
			sanguis::creator::impl::place_boss(
				openings
			)
		);

	sanguis::creator::impl::enemy_type_container const
	enemy_types{
		sanguis::creator::enemy_type::zombie00,
		sanguis::creator::enemy_type::zombie01,
		sanguis::creator::enemy_type::maggot
	};

	auto random_monster(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices_advanced<
				sanguis::creator::impl::random::uniform_int_wrapper
			>(
				enemy_types
			)
		)
	);

	// TODO more sensible spawner placement
	sanguis::creator::impl::filled_rect(
		fcppt::math::box::structure_cast<
			sanguis::creator::rect,
			fcppt::cast::to_unsigned_fun
		>(
			rects.back()
		),
		[&]
		(sanguis::creator::pos const _pos)
		{
			if (
				sanguis::creator::tile_is_solid(
					grid[
						_pos
					]
				)
			)
				return;
			spawners.push_back(
				sanguis::creator::spawn{
					sanguis::creator::spawn_pos{
						_pos
					},
					enemy_types[
						random_monster(
							_parameters.randgen()
						)
					],
					sanguis::creator::spawn_type::single,
					sanguis::creator::enemy_kind::normal
				}
			);
		}
	);

	spawners.push_back(
		sanguis::creator::spawn{
			sanguis::creator::spawn_pos{
				fcppt::math::vector::structure_cast<
					sanguis::creator::pos,
					fcppt::cast::to_unsigned_fun
				>(
					fcppt::math::vector::structure_cast<
						sanguis::creator::signed_pos,
						fcppt::cast::size_fun
					>(
						rects.front().pos()
						+
						fcppt::math::vector::fill<
							sanguis::creator::signed_pos
						>(
							1
						)
					)
				)
			},
			enemy_types[
				random_monster(
					_parameters.randgen()
				)
			],
			sanguis::creator::spawn_type::single,
			sanguis::creator::enemy_kind::normal
		}
	);

	return
		sanguis::creator::impl::result(
			grid,
			bg_grid,
			openings,
			spawners,
			sanguis::creator::destructible_container{}
		);
}