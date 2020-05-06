#pragma once

#include "Cluster.h"

#include <vector>
#include <unordered_map>

namespace superseeker
{
	class Sample
	{
	public:
		typedef std::shared_ptr< Sample > SharedPtr;
		Sample() = delete;
		Sample( const Sample& noncopyable) = delete;
		Sample& operator=( const Sample& noncopyable) = delete;
		Sample(const std::string& sampleName, std::vector< Cluster::SharedPtr >& sampleClusterPtrs, float threshold);
		~Sample();

		Cluster::SharedPtr getClusterByID(int id);
		std::vector< Cluster::SharedPtr > getClusterPtrs() { return this->m_sample_cluster_ptrs; }
		std::string getSampleName() { return m_sample_name; }
		std::vector< int > getAllClusterIDs();
	private:
		void setIDToClusterMap();
		std::string m_sample_name;
		float m_threshold;
		std::vector< Cluster::SharedPtr > m_sample_cluster_ptrs;
		std::unordered_map< int, Cluster::SharedPtr > m_id_to_cluster_map;
	};
}
