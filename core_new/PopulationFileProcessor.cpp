#include "PopulationFileProcessor.h"

#include <iostream>

namespace superseeker
{
	PopulationFileProcessor::PopulationFileProcessor(const std::string filename)
	{
	}

	PopulationFileProcessor::~PopulationFileProcessor() {}


	std::vector< Sample::SharedPtr > PopulationFileProcessor::getSamplePtrs(float threshold)
	{
		std::vector< Sample::SharedPtr > samplePtrs;
		std::vector< Population::SharedPtr > pop1 = {
			std::make_shared< Population >("1", 0.69),
			std::make_shared< Population >("2", 0.2),
			std::make_shared< Population >("3", 0.2),
			std::make_shared< Population >("4", 0.1),
			std::make_shared< Population >("5", 0.05),
			std::make_shared< Population >("6", 0.02),
			std::make_shared< Population >("7", 0.03),
			std::make_shared< Population >("8", 0.03),
			std::make_shared< Population >("9", 0.05)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("t1", pop1, threshold));

		std::vector< Population::SharedPtr > pop2 = {
			std::make_shared< Population >("1", 0.74),
			std::make_shared< Population >("2", 0.25),
			std::make_shared< Population >("3", 0.15),
			std::make_shared< Population >("4", 0.13),
			std::make_shared< Population >("5", 0),
			std::make_shared< Population >("6", 0.08),
			std::make_shared< Population >("7", 0.02),
			std::make_shared< Population >("8", 0),
			std::make_shared< Population >("9", 0.1)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("t2", pop2, threshold));

		std::vector< Population::SharedPtr > pop3 = {
			std::make_shared< Population >("1", 0.77),
			std::make_shared< Population >("2", 0.23),
			std::make_shared< Population >("3", 0.1),
			std::make_shared< Population >("4", 0.18),
			std::make_shared< Population >("5", 0),
			std::make_shared< Population >("6", 0.15),
			std::make_shared< Population >("7", 0.02),
			std::make_shared< Population >("8", 0),
			std::make_shared< Population >("9", 0.08)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("t3", pop3, threshold));

		return samplePtrs;
	}
}
