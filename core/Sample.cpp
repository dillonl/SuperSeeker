#include "Sample.h"

#include <iostream>
#include <algorithm>

namespace superseeker
{
	Sample::Sample(const std::string& sampleName, std::vector< Cluster::SharedPtr >& sampleClusterPtrs, float threshold) :
		m_sample_name(sampleName), m_sample_cluster_ptrs(sampleClusterPtrs), m_threshold(threshold)
	{
		setIDToClusterMap();
	}

	Sample::~Sample()
	{
	}

	void Sample::setIDToClusterMap()
	{
		for (auto clusterPtr : m_sample_cluster_ptrs)
		{
			this->m_id_to_cluster_map.emplace(clusterPtr->getID(), clusterPtr);
		}
	}

	Cluster::SharedPtr Sample::getClusterByID(int id)
	{
		auto iter = this->m_id_to_cluster_map.find(id);
		if (iter == this->m_id_to_cluster_map.end())
		{
			return nullptr;
		}
		else
		{
			return iter->second;
		}
	}

	std::vector< int > Sample::getAllClusterIDs()
	{
		std::vector< int > clusterIDs;
		for (auto clusterPtr : m_sample_cluster_ptrs)
		{
			clusterIDs.emplace_back(clusterPtr->getID());
		}
		return clusterIDs;
	}

}
