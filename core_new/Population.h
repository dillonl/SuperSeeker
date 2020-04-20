#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

namespace superseeker
{
	class Population
	{
	public:
		typedef std::shared_ptr< Population > SharedPtr;
		Population() = delete;
		Population( const Population& noncopyable) = delete;
		Population& operator=( const Population& noncopyable) = delete;
	    Population(const std::string& symbol, const float frequency);
		~Population();

		void setPotentialDirectParents(const std::unordered_set< Population::SharedPtr >& directParentsPtrs);

		void setPotentialDirectChildren(const std::unordered_set< Population::SharedPtr >& directChildrenPtrs);

		// potential just means that these are all parents/children within the sample that could (based on frequency) be a parent/child
		std::unordered_set< Population::SharedPtr > getPotentialDirectParents() { return this->m_potential_direct_parents; }
		std::unordered_set< Population::SharedPtr > getPotentialDirectChildren() { return this->m_potential_direct_children; }

		std::unordered_set< std::string > getPotentialDirectParentsSymbols();
		std::unordered_set< std::string > getPotentialDirectChildrenSymbols();

		std::string getSymbol() { return this->m_symbol; }
		float getFrequency() { return this->m_frequency; }

	private:
		std::unordered_set< Population::SharedPtr > m_potential_direct_parents;
        std::unordered_set< Population::SharedPtr > m_potential_direct_children;
		std::string m_symbol;
		float m_frequency;
	};
}
