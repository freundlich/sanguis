#include <sanguis/tools/libmergeimage/impl/gather_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/tree_depth.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/filesystem/strip_prefix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::impl::path_vector_vector
sanguis::tools::libmergeimage::impl::gather_paths(
	std::filesystem::path const &_base_path
)
{
	sanguis::tools::libmergeimage::impl::path_vector_vector result;

	for(
		std::filesystem::recursive_directory_iterator it(
			_base_path
		);
		it != std::filesystem::recursive_directory_iterator();
		++it
	)
	{
		if(
			fcppt::cast::to_unsigned(
				it.depth()
			)
			==
			sanguis::tools::libmergeimage::impl::tree_depth::value - 1
			&&
			it.recursion_pending()
		)
		{
			it.disable_recursion_pending();

			sanguis::tools::libmergeimage::impl::path_vector temp;

			for(
				std::filesystem::path const &path
				:
				boost::make_iterator_range(
					std::filesystem::directory_iterator(
						*it
					),
					std::filesystem::directory_iterator()
				)
			)
			{
				temp.push_back(
					fcppt::filesystem::strip_prefix(
						_base_path,
						path
					)
				);
			}

			result.push_back(
				temp
			);
		}
	}

	return
		result;
}
