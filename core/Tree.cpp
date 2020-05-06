#include "Tree.h"

#include <unordered_map>
#include <deque>

namespace superseeker
{
	Tree::Tree(const std::vector< int >& parentsList)
	{
		for (int i = 0; i < parentsList.size(); ++i)
		{
			auto nodePtr = std::make_shared< Node >(i);
			this->m_node_map.emplace(i, nodePtr);
		}

		for (int i = 0; i < parentsList.size(); ++i)
		{
			auto nodePtr = this->m_node_map[i];
			if (parentsList[i] == -1)
			{
				this->m_root_node_ptr = nodePtr;
			}
			else
			{
				auto parentNodePtr = this->m_node_map[parentsList[i]];
				nodePtr->setParentNodePtr(parentNodePtr);
				parentNodePtr->addChildNodePtr(nodePtr);
			}
		}
		for (auto iter : this->m_node_map)
		{
			auto nodePtr = iter.second;
			if (nodePtr->getChildrenNodePtrs().size() == 0)
			{
				this->m_leaf_node_ptrs.emplace_back(nodePtr);
			}
		}
	}

	Tree::~Tree()
	{
	}

	bool Tree::isValidTree(const std::vector< Sample::SharedPtr >& samplePtrs, float threshold)
	{
		for (auto samplePtr : samplePtrs)
		{
			if (!isValidSampleTree(samplePtr, threshold)) { return false; }
		}
		return true;
	}

	bool Tree::isValidSampleTree(Sample::SharedPtr samplePtr, int threshold)
	{
		std::vector< int > weightSums(this->m_node_map.size(), 0);
		for (auto nodePtr : this->m_leaf_node_ptrs)
		{
			int clusterID = nodePtr->getClusterID();
			weightSums[clusterID] = samplePtr->getClusterByID(clusterID)->getFrequency();
			Node::SharedPtr parentPtr = nodePtr->getParentNodePtr();
			while (parentPtr != nullptr)
			{
				int parentClusterID = parentPtr->getClusterID();
				weightSums[parentClusterID] += samplePtr->getClusterByID(parentClusterID)->getFrequency();
				parentPtr = parentPtr->getParentNodePtr();
			}
		}
		for (auto clusterPtr : samplePtr->getClusterPtrs())
		{
			if ((weightSums[clusterPtr->getID()] - threshold - clusterPtr->getFrequency()) > 0)
			{
				return false;
			}
		}
		return true;
	}
}
