#pragma once

#include "Tree.h"
#include "SamplesProcessor.h"

#include <vector>
#include <memory>

namespace superseeker
{
	class TreeBuilder
	{
	public:
		typedef std::shared_ptr< TreeBuilder > SharedPtr;
		TreeBuilder(const std::vector< Sample::SharedPtr >& samplePtrs, float threshold);

		std::vector< Tree::SharedPtr > generateAllPossibleTrees();

	private:
		std::vector< Tree::SharedPtr > validatedTrees(const std::vector< Tree::SharedPtr >& potentialTreePtrs);
		std::vector< Tree::SharedPtr > generateAllTreesFromRoot(int rootID);
		void setPotentialRoots();
		void setPotentialRelationships();

		std::vector< int > m_potential_root_ids;
		std::unordered_map< int, std::vector< int > > m_potential_cluster_id_children_id_map;
		std::unordered_map< int, std::vector< int > > m_potential_cluster_id_parent_id_map;
		std::vector< Sample::SharedPtr > m_sample_ptrs;
		float m_threshold;
	};
}
