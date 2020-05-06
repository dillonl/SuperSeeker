
#include "SampleFileProcessor.h"

#include <string.h>
#include <iostream>
#include <fstream>

namespace superseeker
{
	SampleFileProcessor::SampleFileProcessor(const std::string filename, float threshold) :
		m_file_path(filename), m_threshold(threshold)
	{
		this->processSampleFile();
	}

	SampleFileProcessor::~SampleFileProcessor() {}

	void split(const std::string& s, char c, std::vector< std::string >& v)
	{
		std::string::size_type i = 0;
		std::string::size_type j = s.find(c);

		while (j != std::string::npos)
		{
			v.push_back(s.substr(i, j-i));
			i = ++j;
			j = s.find(c, j);

			if (j == std::string::npos)
			{
				v.push_back(s.substr(i, s.length()));
			}
		}
	}

	void SampleFileProcessor::processSampleFile()
	{
		std::string line;
		std::ifstream in(this->m_file_path);
		if (!in)
		{
			std::cout << "Cannot open input file: " << this->m_file_path << std::endl;
			exit(0);
		}
		std::vector< std::vector< float > > samples;
		while (std::getline(in, line))
		{
			std::vector< std::string > lineSplit;
			char token = '\t';
			split(line, token, lineSplit);
			if (samples.size() == 0)
			{
				samples.resize(lineSplit.size()); // this sets the number of samples represented in the file (columns)
			}
			int i = 0;
			for (auto c : lineSplit) // iterate through all the clusters in a line
			{
				samples[i].emplace_back(std::stof(c));
				++i;
			}
		}
		this->m_sample_ptrs.clear();
		for (int i = 0; i < samples.size(); ++i)
		{
			std::vector< Cluster::SharedPtr > clusters;
			for (int j = 0; j < samples[i].size(); ++j)
			{
				clusters.emplace_back(std::make_shared< Cluster >(j, samples[i][j])); // it is key that the clusters are sequential and zero-based
			}
			std::string sampleName = "sample_";
			sampleName += std::to_string(i);
			this->m_sample_ptrs.emplace_back(std::make_shared< Sample >(sampleName, clusters, m_threshold));
		}
		in.close();
	}

	std::vector< Sample::SharedPtr > SampleFileProcessor::getSamplePtrs()
	{
		return this->m_sample_ptrs;
	}

	std::vector< Sample::SharedPtr > SampleFileProcessor::getSimulatedSamplePtrs()
	{


		std::vector< Sample::SharedPtr > samplePtrs;
		std::vector< Cluster::SharedPtr > s1 = {
			std::make_shared< Cluster >(1, 0.69),
			std::make_shared< Cluster >(2, 0.2),
			std::make_shared< Cluster >(3, 0.2),
			std::make_shared< Cluster >(4, 0.1),
			std::make_shared< Cluster >(5, 0.05),
			std::make_shared< Cluster >(6, 0.02),
			std::make_shared< Cluster >(7, 0.03),
			std::make_shared< Cluster >(8, 0.03),
			std::make_shared< Cluster >(9, 0.05)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("s1", s1, m_threshold));

		std::vector< Cluster::SharedPtr > s2 = {
			std::make_shared< Cluster >(1, 0.74),
			std::make_shared< Cluster >(2, 0.25),
			std::make_shared< Cluster >(3, 0.15),
			std::make_shared< Cluster >(4, 0.13),
			std::make_shared< Cluster >(5, 0),
			std::make_shared< Cluster >(6, 0.08),
			std::make_shared< Cluster >(7, 0.02),
			std::make_shared< Cluster >(8, 0),
			std::make_shared< Cluster >(9, 0.1)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("t2", s2, m_threshold));

		std::vector< Cluster::SharedPtr > s3 = {
			std::make_shared< Cluster >(1, 0.77),
			std::make_shared< Cluster >(2, 0.23),
			std::make_shared< Cluster >(3, 0.1),
			std::make_shared< Cluster >(4, 0.18),
			std::make_shared< Cluster >(5, 0),
			std::make_shared< Cluster >(6, 0.15),
			std::make_shared< Cluster >(7, 0.02),
			std::make_shared< Cluster >(8, 0),
			std::make_shared< Cluster >(9, 0.08)
		};
		samplePtrs.emplace_back(std::make_shared< Sample >("t3", s3, m_threshold));

		return samplePtrs;
	}
}
