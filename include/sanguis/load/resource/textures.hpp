#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/texture_context_fwd.hpp>
#include <sanguis/load/resource/texture_context.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures
{
	FCPPT_NONCOPYABLE(
		textures
	);
public:
	sge::texture::part_ptr const
	load(
		texture_identifier const &
	) const;

	texture_context const
	load(
		fcppt::filesystem::path const &
	) const;

	textures(
		sge::renderer::device &,
		sge::image2d::system &
	);

	~textures();
private:
	friend class animations;

	sge::texture::part_ptr const
	do_load(
		texture_identifier const &
	) const;

	texture_context_impl_ptr const
	do_load_unnamed(
		fcppt::filesystem::path const &
	) const;

	sge::texture::part_ptr const
	do_load_inner(
		fcppt::filesystem::path const &
	) const;

	typedef std::map<
		texture_identifier,
		sge::texture::part_ptr
	> texture_map;

	typedef std::map<
		fcppt::filesystem::path,
		texture_context_impl_ptr
	> unnamed_texture_map;

	typedef std::map<
		texture_identifier,
		texture_identifier
	> texture_name_map;

	sge::renderer::device &renderer_;

	mutable sge::texture::manager texture_manager_;

	sge::image2d::system &image_loader_;

	mutable texture_map textures_;

	mutable unnamed_texture_map unnamed_textures_;

	mutable texture_name_map texture_names_;
};

}
}
}

#endif
