#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/texture_context_fwd.hpp>
#include <sanguis/load/resource/texture_context.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
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
	sge::texture::const_part_shared_ptr const
	load(
		texture_identifier const &
	) const;

	texture_context const
	load(
		boost::filesystem::path const &
	) const;

	textures(
		sge::renderer::device &,
		sge::image2d::system &
	);

	~textures();
private:
	friend class animations;

	sge::texture::const_part_shared_ptr const
	do_load(
		texture_identifier const &
	) const;

	texture_context_impl_ptr const
	do_load_unnamed(
		boost::filesystem::path const &
	) const;

	sge::texture::const_part_shared_ptr const
	do_load_inner(
		boost::filesystem::path const &
	) const;

	typedef std::map<
		texture_identifier,
		sge::texture::const_part_shared_ptr
	> texture_map;

	typedef std::map<
		boost::filesystem::path,
		texture_context_impl_ptr
	> unnamed_texture_map;

	typedef std::map<
		texture_identifier,
		texture_identifier
	> texture_name_map;

	sge::renderer::device &renderer_;

	sge::image2d::system &image_loader_;

	mutable texture_map textures_;

	mutable unnamed_texture_map unnamed_textures_;

	mutable texture_name_map texture_names_;
};

}
}
}

#endif
