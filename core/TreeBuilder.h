#pragma once

#include "Tree.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <tuple>

namespace treefinder
{
	class TreeBuilder
	{
	public:
		typedef std::shared_ptr< TreeBuilder > SharedPtr;
        TreeBuilder(const std::string& filePath, float threshold);
		~TreeBuilder();

		TreeBuilder( const TreeBuilder& noncopyable) = delete;
		TreeBuilder& operator=( const TreeBuilder& noncopyable) = delete;
		TreeBuilder() = delete;

		std::vector< Tree::SharedPtr > getTreesFromProportions1(const std::vector< std::tuple< char, float > >& proportions);
		std::vector< Tree::SharedPtr > getTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions);

	private:
		std::unordered_map< std::string, std::vector< std::tuple< char, float > > > extractSampleProportionsFromFile(const std::string& filePath);
		void populateSampleProportions(const std::unordered_map< std::string, std::vector< std::tuple< char, float > > >& samplesProportions);

		std::unordered_map< std::string, std::vector< Tree::SharedPtr > > m_all_sample_proportions;
		float m_threshold;
	};
}
