#pragma once

#include "Sample.h"
#include "Node.h"
#include "Tree.h"

#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

namespace superseeker
{
	class SamplesProcessor : public std::enable_shared_from_this< SamplesProcessor >
	{
	public:
		typedef std::shared_ptr< SamplesProcessor > SharedPtr;
		SamplesProcessor() = delete;
		SamplesProcessor(const SamplesProcessor& noncopyable) = delete;
		SamplesProcessor& operator=(const SamplesProcessor& noncopyable) = delete;
		SamplesProcessor(std::vector< Sample::SharedPtr > samplePtrs);
		~SamplesProcessor();

		std::vector< int > getIndicesAsListWithRootAsFirst(int rootIndex);
		std::vector< Tree::SharedPtr > generateTreesFromSamples();
		std::unordered_set< int > getAllPotentialRootIndices() { return this->m_root_indices; }
		std::unordered_set< int > getAllIndices() { return m_all_indices; }
		std::unordered_map< int, std::unordered_set< int > > getValidChildrenIndicesAcrossSamples() { return m_valid_children_across_samples; }
		std::unordered_map< int, std::unordered_set< int > > getValidParentsIndicesAcrossSamples() { return m_valid_parents_across_samples; }

		std::unordered_map< int, std::vector< int > > getValidParentsAsMapWithList();
		/* std::vector< std::vector< int > > getParentsIndicesAsIdxs(const std::vector< int >& indices); */

	private:
		/* std::unordered_map< std::string, std::unordered_set< std::string > > getValidSymbolsAcrossSamples(std::function< std::unordered_set< std::string >(const Cluster::SharedPtr) >& funct); */
		void setAllPotentialRootIndices();
		void setAllIndices();

		std::vector< Sample::SharedPtr > m_sample_ptrs;
		std::unordered_set< int > m_root_indices;
		std::unordered_map< int, std::unordered_set< int > > m_valid_parents_across_samples;
		std::unordered_map< int, std::unordered_set< int > > m_valid_children_across_samples;
		std::unordered_set< int > m_all_indices;
	};
}
