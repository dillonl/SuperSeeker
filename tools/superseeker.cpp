#include <iostream>

#include "core/Params.h"
#include "core/SampleFileProcessor.h"
#include "core/Cluster.h"
#include "core/TreeBuilder.h"

#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool fileExists(const std::string& name)
{
	std::ifstream f(name.c_str());
	if (!f)
	{
		return false;
	}
	return true;
}

bool directoryExists(const std::string& path)
{
	if(!path.empty())
	{
		struct stat sb;
		if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			return true;
		}
	}
	return false;
}

int main(int argc, char** argv)
{
    superseeker::Params params(argc, argv);
	if (params.getHelpFlag())
	{
		params.printHelp();
		return 0;
	}
	float threshold = params.getThreshold();
	if (threshold < 0 || threshold > 1)
	{
		std::cout << "Invalid threshold: " << threshold << " must be between [0, 1]" << std::endl;
		return 1;
	}
	std::string samplesPath = params.getSamplesPath();
	if (!fileExists(samplesPath))
	{
		std::cout << "File not found: " << samplesPath << std::endl;
		return 1;
	}
	std::string outputDirectoryPath = params.getOutputPath();
	if (!directoryExists(outputDirectoryPath))
	{
		std::cout << "Output directory not found: " << samplesPath << std::endl;
		return 1;
	}

	auto sampleFileProcessorPtr = std::make_shared< superseeker::SampleFileProcessor >(samplesPath, threshold);
    auto samplePtrs = sampleFileProcessorPtr->getSamplePtrs();
	auto treeBuilderPtr = std::make_shared< superseeker::TreeBuilder >(samplePtrs, threshold);
	auto treePtrs = treeBuilderPtr->generateAllPossibleTrees();
	if (treePtrs.size() == 0)
	{
		std::cout << "There are no valid tree structures for this data" << std::endl;
		return 0;
	}
	int count = 0;
	for (auto treePtr : treePtrs)
	{
		std::ofstream out(outputDirectoryPath + "sample_trees_" + std::to_string(count++) + ".dot");
		out << treePtr->getDotFormat(samplePtrs);
		out.close();
	}
    // auto samplesProcessorPtr = std::make_shared< superseeker::SamplesProcessor >(samplePtrs);
	// auto treePtrs = samplesProcessorPtr->generateTreesFromSamples();
	return 0;
}
