#include <iostream>

#include "core_new/PopulationFileProcessor.h"
#include "core_new/Population.h"
#include "core_new/SamplesProcessor.h"
#include "core_new/TreeBuilder.h"

int main(int argc, char** argv)
{
	float threshold = 0.01;
    auto populationFileProcessorPtr = std::make_shared< superseeker::PopulationFileProcessor >("foo.txt");
    auto samplePtrs = populationFileProcessorPtr->getSamplePtrs(threshold);
    auto samplesProcessorPtr = std::make_shared< superseeker::SamplesProcessor >(samplePtrs);
	auto treePtrs = samplesProcessorPtr->generateTreesFromSamples();
	return 0;
}
