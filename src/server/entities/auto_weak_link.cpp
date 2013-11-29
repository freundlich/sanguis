#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <fcppt/optional_ref_compare.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref_()
{
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	sanguis::server::entities::with_links &_ref
)
:
	ref_(
		_ref
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

	return
		*this;
}

void
sanguis::server::entities::auto_weak_link::unlink()
{
	auto_weak_hook::unlink();

	ref_ =
		sanguis::server::entities::auto_weak_link::optional_with_links_ref();
}

sanguis::server::entities::with_links &
sanguis::server::entities::auto_weak_link::operator*() const
{
	return
		this->checked_ref();
}

sanguis::server::entities::auto_weak_link::optional_with_links_ref const
sanguis::server::entities::auto_weak_link::operator->() const
{
	return
		this->get();
}

sanguis::server::entities::auto_weak_link::optional_with_links_ref const
sanguis::server::entities::auto_weak_link::get() const
{
	return
		sanguis::server::entities::auto_weak_link::optional_with_links_ref(
			this->checked_ref()
		);
}

sanguis::server::entities::auto_weak_link::operator bool() const
{
	return
		this->is_linked();
}

bool
sanguis::server::entities::auto_weak_link::operator==(
	sanguis::server::entities::auto_weak_link const &_link
) const
{
	return
		fcppt::optional_ref_compare(
			_link.ref_,
			ref_
		);
}

sanguis::server::entities::with_links &
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

bool
sanguis::server::entities::operator!=(
	sanguis::server::entities::auto_weak_link const &_left,
	sanguis::server::entities::auto_weak_link const &_right
)
{
	return
		!(
			_left
			==
			_right
		);
}
