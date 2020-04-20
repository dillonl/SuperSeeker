#pragma once

#include "Population.h"

#include <vector>

namespace superseeker
{
	class Sample
	{
	public:
		typedef std::shared_ptr< Sample > SharedPtr;
		Sample() = delete;
		Sample( const Sample& noncopyable) = delete;
		Sample& operator=( const Sample& noncopyable) = delete;
		Sample(const std::string& sampleName, std::vector< Population::SharedPtr >& samplePopulationPtrs, float threshold);
		~Sample();

		void calculateAndSetSamplePopulationPotentialParentsAndChildren();

		std::vector< Population::SharedPtr > getPopulationPtrs() { return this->m_sample_population_ptrs; }
		std::string getSampleName() { return m_sample_name; }
	private:
		std::string m_sample_name;
		float m_threshold;
		std::vector< Population::SharedPtr > m_sample_population_ptrs;
	};
}
