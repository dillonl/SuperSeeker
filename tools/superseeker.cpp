#include <iostream>

#include "core/SampleFileProcessor.h"
#include "core/Cluster.h"
// #include "core/SamplesProcessor.h"
#include "core/TreeBuilder.h"

int main(int argc, char** argv)
{
	float threshold = 0.01;
    auto sampleFileProcessorPtr = std::make_shared< superseeker::SampleFileProcessor >("/scratch/ucgd/lustre/work/u0105808/SuperSeeker/tests/washu/UPN400220", threshold);
    auto samplePtrs = sampleFileProcessorPtr->getSamplePtrs();
	auto treeBuilderPtr = std::make_shared< superseeker::TreeBuilder >(samplePtrs, threshold);
	auto treePtrs = treeBuilderPtr->generateAllPossibleTrees();
    // auto samplesProcessorPtr = std::make_shared< superseeker::SamplesProcessor >(samplePtrs);
	// auto treePtrs = samplesProcessorPtr->generateTreesFromSamples();
	return 0;
}
