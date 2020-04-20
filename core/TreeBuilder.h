#pragma once

#include "Noncopyable.hpp"
#include "Tree.h"
#include "ForestBuilder.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <tuple>

namespace treefinder
{
	class TreeBuilder : private Noncopyable
	{
	public:
		typedef std::shared_ptr< TreeBuilder > SharedPtr;
        TreeBuilder(const std::string& filePath, float threshold);
        TreeBuilder() = delete;
		~TreeBuilder();

		std::vector< SampleTrees::SharedPtr > getProcessedSampleTreesPtrs();

	private:
		void populateTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions, std::vector< Tree::SharedPtr >* treePtrsPtr);
		std::unordered_map< std::string, std::vector< std::tuple< char, float > > > extractSampleProportionsFromFile(const std::string& filePath);
		ForestBuilder::SharedPtr getForestFromSampleProportions(const std::unordered_map< std::string, std::vector< std::tuple< char, float > > >& samplesProportions);

		std::vector< Tree::SharedPtr > getTreesFromProportions1(const std::vector< std::tuple< char, float > >& proportions);

		ForestBuilder::SharedPtr m_forest_builder;
		std::string m_file_path;
		float m_threshold;
	};
}
