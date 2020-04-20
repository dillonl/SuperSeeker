#include "Population.h"

#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace superseeker
{
	Population::Population(const std::string& symbol, const float frequency) : m_symbol(symbol), m_frequency(frequency)
	{
	}

	Population::~Population()
	{
	}

	void Population::setPotentialDirectParents(const std::unordered_set< Population::SharedPtr >& directParentsPtrs)
	{
		this->m_potential_direct_parents.empty();
		this->m_potential_direct_parents.insert(directParentsPtrs.begin(), directParentsPtrs.end());
	}

	void Population::setPotentialDirectChildren(const std::unordered_set< Population::SharedPtr >& directChildrenPtrs)
	{
		this->m_potential_direct_children.empty();
		this->m_potential_direct_children.insert(directChildrenPtrs.begin(), directChildrenPtrs.end());
	}

	std::unordered_set< std::string > Population::getPotentialDirectParentsSymbols()
	{
		std::unordered_set< std::string > parentsSymbols;
		std::for_each(this->m_potential_direct_parents.begin(), this->m_potential_direct_parents.end(),
					  [&parentsSymbols](const Population::SharedPtr parentPopPtr)
					  {
						  parentsSymbols.emplace(parentPopPtr->getSymbol());
					  });
		return parentsSymbols;
	}

	std::unordered_set< std::string > Population::getPotentialDirectChildrenSymbols()
	{
		std::unordered_set< std::string > childrenSymbols;
		std::for_each(this->m_potential_direct_children.begin(), this->m_potential_direct_children.end(),
					  [&childrenSymbols](const Population::SharedPtr childrenPopPtr)
					  {
						  childrenSymbols.emplace(childrenPopPtr->getSymbol());
					  });
		return childrenSymbols;
	}
}
