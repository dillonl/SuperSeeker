#include "TreeBuilder.h"
#include "Tree.h"

#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace superseeker
{

	TreeBuilder::TreeBuilder(const std::vector< Sample::SharedPtr >& samplePtrs, float threshold) :
		m_sample_ptrs(samplePtrs),
		m_threshold(threshold)
	{
		setPotentialRoots();
		setPotentialRelationships();
	}

	void TreeBuilder::setPotentialRoots()
	{
		if (this->m_sample_ptrs.size() == 0) { return; }
		auto clusterIDs = this->m_sample_ptrs[0]->getAllClusterIDs();
		for (int clusterID : clusterIDs)
		{
			bool potentialRoot = true;
			for (auto samplePtr : this->m_sample_ptrs)
			{

				int childSum = 0;
				auto currentCluster = samplePtr->getClusterByID(clusterID);
				for (auto clusterPtr : samplePtr->getClusterPtrs())
				{
					if (clusterPtr->getID() == clusterID) { continue; } // we don't want compare us to ourself
					childSum += clusterPtr->getFrequency();
				}
				if ((childSum - this->m_threshold - currentCluster->getFrequency()) > 0)
				{
					potentialRoot = false;
					break;
				}
			}
			if (potentialRoot && std::find(this->m_potential_root_ids.begin(), this->m_potential_root_ids.end(), potentialRoot) == this->m_potential_root_ids.end())
			{
				this->m_potential_root_ids.emplace_back(clusterID);
			}
		}
	}

	void TreeBuilder::setPotentialRelationships()
	{
		if (this->m_sample_ptrs.size() == 0) { return; }
		auto clusterIDs = this->m_sample_ptrs[0]->getAllClusterIDs();
		for (int clusterID : clusterIDs)
		{
			bool couldBeRoot = true;
			if (this->m_potential_cluster_id_children_id_map.find(clusterID) == this->m_potential_cluster_id_children_id_map.end())
			{
				std::vector< int > children;
				std::vector< int > parents;
				this->m_potential_cluster_id_children_id_map.emplace(clusterID, children);
				this->m_potential_cluster_id_parent_id_map.emplace(clusterID, parents);
			}
			float smallestClusterFrequency = 1;
			float largestClusterFrequency = 0;
			for (auto samplePtr : this->m_sample_ptrs)
			{
				auto currentCluster = samplePtr->getClusterByID(clusterID);
				if (currentCluster == nullptr) { continue; } // skip if the custerID is not found
				smallestClusterFrequency = (currentCluster->getFrequency() < smallestClusterFrequency) ? currentCluster->getFrequency() : smallestClusterFrequency;
				largestClusterFrequency = (currentCluster->getFrequency() > largestClusterFrequency) ? currentCluster->getFrequency() : largestClusterFrequency;
			}
			bool potentialChild = true;
			bool potentialParent = true;
			for (int potentialClusterID : clusterIDs)
			{
				if (clusterID == potentialClusterID) { continue; }
				for (auto samplePtr : this->m_sample_ptrs)
				{
					auto potentialCluster = samplePtr->getClusterByID(potentialClusterID);
					// std::cout << "\t" << largestClusterFrequency << " - " << potentialCluster->getFrequency() << " (" << this->m_threshold << ") " << ((potentialCluster->getFrequency() + this->m_threshold) - largestClusterFrequency) << std::endl;
					if (((potentialCluster->getFrequency() + this->m_threshold) - largestClusterFrequency) < 0) { potentialParent = false; couldBeRoot = false; } // checking if potentialCluster could not be a parent a child of currentCluster
					if ((smallestClusterFrequency - (potentialCluster->getFrequency() + this->m_threshold)) < 0) { potentialChild = false; } // checking if potentialCluster could not be a child of currentCluster
				}
				if (potentialChild)
				{
					this->m_potential_cluster_id_children_id_map[clusterID].emplace_back(potentialClusterID);
				}
				if (potentialParent)
				{
					this->m_potential_cluster_id_parent_id_map[clusterID].emplace_back(potentialClusterID);
				}
			}
			if (couldBeRoot)
			{
				this->m_potential_cluster_id_parent_id_map[clusterID].emplace_back(-1);
			}
		}
	}

	std::vector< Tree::SharedPtr > TreeBuilder::generateAllPossibleTrees()
	{
		std::unordered_set< std::string > addedTrees;
		std::vector< Tree::SharedPtr > treePtrs;

		std::vector< std::vector< int > > parentsList(this->m_potential_cluster_id_parent_id_map.size());
		for (auto iter : this->m_potential_cluster_id_parent_id_map)
		{
			parentsList[iter.first] = iter.second;
			if (iter.second.size() == 0)
			{
				std::cout << "There are no valid tree structures for this data" << std::endl;
				exit(0);
			}
		}

		std::vector< int > sizeArray(parentsList.size(), 0);
		std::vector< int > counterArray(parentsList.size(), 0);
		int totalCombinationCount = 1;
		for (int i = 0; i < parentsList.size(); ++i)
		{
			sizeArray[i] = parentsList[i].size();
			totalCombinationCount *= (parentsList[i].size() > 0) ? parentsList[i].size() : totalCombinationCount;
		}

		std::vector< std::vector< int > > combinationList(totalCombinationCount);
		// std::cout << "total count: " <<  totalCombinationCount << std::endl;
		int count = 0;
		for (int countdown = totalCombinationCount; countdown > 0; --countdown)
		{
			combinationList[count].resize(parentsList.size());
			for (int i = 0; i < parentsList.size(); ++i)
			{
				combinationList[count][i] = parentsList[i][counterArray[i]];
			}
			if (std::count(combinationList[count].begin(), combinationList[count].end(), -1) == 1)
			{
				auto treePtr = std::make_shared< Tree >(combinationList[count]);
				treePtrs.emplace_back(treePtr);
			}
			++count;

			for (int incIndex =  parentsList.size() - 1; incIndex >= 0; --incIndex)
			{
				if (counterArray[incIndex] + 1 < sizeArray[incIndex])
				{
					++counterArray[incIndex];
					break;
				}
				counterArray[incIndex] = 0;
			}
		}
		return validatedTrees(treePtrs);
	}

	std::vector< Tree::SharedPtr > TreeBuilder::validatedTrees(const std::vector< Tree::SharedPtr >& potentialTreePtrs)
	{
		std::vector< Tree::SharedPtr > validatedTreePtrs;
		for (auto potentialTreePtr : potentialTreePtrs)
		{
			if (potentialTreePtr->isValidTree(this->m_sample_ptrs, this->m_threshold))
			{
				validatedTreePtrs.emplace_back(potentialTreePtr);
			}
		}
		return validatedTreePtrs;
	}

}
