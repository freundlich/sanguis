#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref_(
		nullptr
	)
{
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	sanguis::server::entities::base &_ref
)
:
	ref_(
		&_ref
	)
{
	this->add_me();
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link const &_old
)
:
	auto_weak_hook(
		_old
	),
	ref_(
		_old.ref_
	)
{
	if(
		_old.is_linked()
	)
		this->add_me();
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
{
}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link const &_old
)
{
	this->unlink();

	auto_weak_hook::operator=(
		_old
	);

	ref_ = _old.ref_;

	if(
		_old.is_linked()
	)
		this->add_me();

	return *this;
}

void
sanguis::server::entities::auto_weak_link::unlink()
{
	auto_weak_hook::unlink();

	ref_ = 0;
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::operator*() const
{
	return this->checked_ref();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::operator->() const
{
	return this->get();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::get() const
{
	return &this->checked_ref();
}

sanguis::server::entities::auto_weak_link::operator bool() const
{
	return this->is_linked();
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	FCPPT_ASSERT_PRE(
		ref_
	);

	return *ref_;
}

void
sanguis::server::entities::auto_weak_link::add_me()
{
	if(
		!ref_
	)
		return;

	ref_->insert_link(
		*this
	);
}
