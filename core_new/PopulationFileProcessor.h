#pragma once

#include "Population.h"
#include "Sample.h"

#include <unordered_map>

namespace superseeker
{
	class PopulationFileProcessor
	{
	public:
		typedef std::shared_ptr< PopulationFileProcessor > SharedPtr;
		PopulationFileProcessor() = delete;
		PopulationFileProcessor( const PopulationFileProcessor& noncopyable) = delete;
		PopulationFileProcessor& operator=( const PopulationFileProcessor& noncopyable) = delete;
		PopulationFileProcessor(const std::string filename);
		~PopulationFileProcessor();

		std::vector< Sample::SharedPtr > getSamplePtrs(float threshold);
		// calculate possible population parents
		// calculate possible population children

	private:
		void processPopulationFile();
	};
}
