#pragma once

#include "Cluster.h"
#include "Sample.h"

#include <unordered_map>

namespace superseeker
{
	class SampleFileProcessor
	{
	public:
		typedef std::shared_ptr< SampleFileProcessor > SharedPtr;
		SampleFileProcessor() = delete;
		SampleFileProcessor( const SampleFileProcessor& noncopyable) = delete;
		SampleFileProcessor& operator=( const SampleFileProcessor& noncopyable) = delete;
		SampleFileProcessor(const std::string filename, float threshold);
		~SampleFileProcessor();

		std::vector< Sample::SharedPtr > getSamplePtrs();
		std::vector< Sample::SharedPtr > getSimulatedSamplePtrs();

	private:
		void processSampleFile();

		std::vector< Sample::SharedPtr > m_sample_ptrs;
		std::string m_file_path;
		float m_threshold;
	};
}
