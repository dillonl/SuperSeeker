#include "Sample.h"

#include <iostream>
#include <algorithm>

namespace superseeker
{
	Sample::Sample(const std::string& sampleName, std::vector< Population::SharedPtr >& samplePopulationPtrs, float threshold) :
		m_sample_name(sampleName), m_sample_population_ptrs(samplePopulationPtrs), m_threshold(threshold)
	{
		calculateAndSetSamplePopulationPotentialParentsAndChildren();
	}

	Sample::~Sample()
	{
	}

	void Sample::calculateAndSetSamplePopulationPotentialParentsAndChildren()
	{
		for (auto outerPopulationPtr : m_sample_population_ptrs)
		{
			std::unordered_set< Population::SharedPtr > parentPtrs;
			std::unordered_set< Population::SharedPtr > childrenPtrs;
			for (auto innerPopulationPtr : m_sample_population_ptrs)
			{
				if (outerPopulationPtr->getSymbol().compare(innerPopulationPtr->getSymbol()) == 0) { continue; } // we can't add ourselves, let's just skip it so there are no issues down the road
				if (outerPopulationPtr->getFrequency() <= (innerPopulationPtr->getFrequency() + m_threshold)) // the threshold gives a cushion to the frequency comparison
				{
					parentPtrs.emplace(innerPopulationPtr);
				}
				if (outerPopulationPtr->getFrequency() >= (innerPopulationPtr->getFrequency() - m_threshold)) // the threshold gives a cushion to the frequency comparison
				{
					childrenPtrs.emplace(innerPopulationPtr);
				}
			}
			outerPopulationPtr->setPotentialDirectParents(parentPtrs);
			outerPopulationPtr->setPotentialDirectChildren(childrenPtrs);
		}
	}

}
