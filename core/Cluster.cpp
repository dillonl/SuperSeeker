#include "Cluster.h"

#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace superseeker
{
	Cluster::Cluster(int id, const float frequency) : m_id(id), m_frequency(frequency)
	{
	}

	Cluster::~Cluster()
	{
	}

	/*
	void Cluster::setPotentialDirectParents(const std::unordered_set< Cluster::SharedPtr >& directParentsPtrs)
	{
		this->m_potential_direct_parents.empty();
		this->m_potential_direct_parents.insert(directParentsPtrs.begin(), directParentsPtrs.end());
	}

	void Cluster::setPotentialDirectChildren(const std::unordered_set< Cluster::SharedPtr >& directChildrenPtrs)
	{
		this->m_potential_direct_children.empty();
		this->m_potential_direct_children.insert(directChildrenPtrs.begin(), directChildrenPtrs.end());
	}

	std::unordered_set< int > Cluster::getPotentialDirectParentsIDs()
	{
		std::unordered_set< int > parentsIDs;
		std::for_each(this->m_potential_direct_parents.begin(), this->m_potential_direct_parents.end(),
					  [&parentsIDs](const Cluster::SharedPtr parentClusterPtr)
					  {
						  parentsIDs.emplace(parentClusterPtr->getID());
					  });
		return parentsIDs;
	}

	std::unordered_set< int > Cluster::getPotentialDirectChildrenIDs()
	{
		std::unordered_set< int > childrenIDs;
		std::for_each(this->m_potential_direct_children.begin(), this->m_potential_direct_children.end(),
					  [&childrenIDs](const Cluster::SharedPtr childrenClusterPtr)
					  {
						  childrenIDs.emplace(childrenClusterPtr->getID());
					  });
		return childrenIDs;
	}
	*/
}
