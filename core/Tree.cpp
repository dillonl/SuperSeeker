#include "Tree.h"

#include <unordered_map>
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

namespace superseeker
{
	Tree::Tree(const std::vector< int >& parentsList) :
		m_parents_list(parentsList)
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
				nodePtr->setParentNodePtr(nullptr);
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
		// check for cycles, and do a quick rootcount (there should only be one root)
		int rootCounter = 0;
		for (auto iter : this->m_node_map)
		{
			std::unordered_set< int > cycleChecker;
			auto nodePtr = iter.second;
			rootCounter += (nodePtr->getParentNodePtr() == nullptr) ? 1 : 0;
			while (nodePtr != nullptr)
			{
				if (cycleChecker.find(nodePtr->getClusterID()) != cycleChecker.end())
				{
					return false; // a cycle was detected
				}
				cycleChecker.emplace(nodePtr->getClusterID());
				nodePtr = nodePtr->getParentNodePtr();
			}
		}
		if (rootCounter != 1) // there can only be one root
		{
			return false;
		}

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

	std::string Tree::getDotFormat(const std::vector< Sample::SharedPtr >& samplePtrs)
	{
		std::string dot = "digraph {\n";
		int count = 0;
		std::string parentsListNodeString = "node [ label=\"";
		for (auto i = 0; i < m_parents_list.size(); ++i)
		{
			if (i > 0) { parentsListNodeString += ", "; }
			parentsListNodeString += std::to_string(i+1) + "->" + std::to_string(m_parents_list[i] + 1);
		}
		dot += "\t" + parentsListNodeString + "\"]\n";
		for (auto samplePtr : samplePtrs)
		{
			dot += "\tsubgraph cluster_" + std::to_string(count) + " {\n";
			dot += "\t\tstyle=filled;\n";
			dot += "\t\tcolor=lightgrey;\n";
			std::queue< Node::SharedPtr > nodeQueuePtrs;
			// std::for_each (this->m_leaf_node_ptrs.begin(), this->m_leaf_node_ptrs.end(), [&nodeQueuePtrs](const Node::SharedPtr& leafNodePtr) { nodeQueuePtrs.push(leafNodePtr); } );
			nodeQueuePtrs.push(this->m_root_node_ptr);
			while (!nodeQueuePtrs.empty())
			{
				auto nodePtr = nodeQueuePtrs.front();
				nodeQueuePtrs.pop();
				auto clusterPtr = samplePtr->getClusterByID(nodePtr->getClusterID());
				auto clusterIDString = std::to_string(clusterPtr->getID() + 1);
				dot += "\t\tnode_"+samplePtr->getSampleName()+"_"+clusterIDString+" [label=\"" + clusterIDString + " ("+std::to_string(clusterPtr->getFrequency())+")\"];\n";
				if (nodePtr->getParentNodePtr() != nullptr)
				{
					auto parentClusterPtr = samplePtr->getClusterByID(nodePtr->getParentNodePtr()->getClusterID());
					auto parentClusterIDString = std::to_string(parentClusterPtr->getID() + 1);
					dot += "\t\tnode_"+samplePtr->getSampleName()+"_"+parentClusterIDString+" -> node_"+samplePtr->getSampleName()+"_"+clusterIDString+";\n";
				}
				for (auto iter : nodePtr->getChildrenNodePtrs())
				{
					nodeQueuePtrs.push(iter.second);
				}
			}
			dot += "\t\tlabel = \"" + samplePtr->getSampleName() + "\";\n";
			dot += "\t}\n";
			++count;
		}
		dot += "}\n";
		return dot;
	}
}
