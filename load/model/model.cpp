#include "model.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>
#include <ostream>
#include <utility>

sanguis::load::model::model::model(
	sge::path const& path)
{
	for(sge::directory_iterator beg(path), end; beg != end; ++beg)
	{
		if(!boost::filesystem::is_directory(*beg))
		{
			sge::clog << SGE_TEXT("warning: ") << *beg << SGE_TEXT(" is not a directory!\n");
			continue;
		}
		
		if(parts.insert(
			std::make_pair(
				beg->leaf(),
				part(*beg)))
		.second == false)
			throw sge::exception(SGE_TEXT("Double insert in model::model: ") + beg->string());
	}
}

sanguis::load::model::part const&
sanguis::load::model::model::operator[](sge::string const& name) const
{
	const part_map::const_iterator it(parts.find(name));
	if(it == parts.end())
		throw sge::exception(name + SGE_TEXT(" not found in model!"));
	return it->second;
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::begin() const
{
	return parts.begin();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::end() const
{
	return parts.end();
} 
sanguis::load::model::model::size_type
sanguis::load::model::model::size() const
{
	return parts.size();
}
