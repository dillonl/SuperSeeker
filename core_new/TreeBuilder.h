#pragma once

#include "Tree.h"
#include "SamplesProcessor.h"

#include <vector>
#include <memory>

namespace superseeker
{
	class TreeBuilder
	{
	public:
		typedef std::shared_ptr< TreeBuilder > SharedPtr;
		TreeBuilder(SamplesProcessor::SharedPtr samplesProcessorPtr);

		std::vector< Tree::SharedPtr > generateAllPossibleTrees();
		std::vector< Tree::SharedPtr > generateAllTreesFromRoot(std::string& rootSymbol);

	private:
		SamplesProcessor::SharedPtr m_samples_processor_ptr;
	};
}
