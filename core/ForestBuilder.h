#pragma once

#include "Noncopyable.hpp"
#include "Tree.h"

#include <memory>
#include <vector>

namespace treefinder
{
	class ForestBuilder : private Noncopyable
	{
	public:
		typedef std::shared_ptr< ForestBuilder > SharedPtr;
		ForestBuilder(std::vector< SampleTrees::SharedPtr >& sampleTreesPtrs);
		ForestBuilder() = delete;
		~ForestBuilder();

		std::vector< SampleTrees::SharedPtr > getTrimmedSampleTrees();
	private:
	};
}
