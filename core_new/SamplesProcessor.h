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

		std::vector< std::string > getSymbolsAsListWithRootAsFirst(const std::string& rootSymbol);
		std::vector< Tree::SharedPtr > generateTreesFromSamples();
		std::unordered_set< std::string > getAllPotentialRootSymbols() { return m_root_symbols; }
		std::unordered_set< std::string > getAllSymbols() { return m_all_symbols; }
		std::unordered_map< std::string, std::unordered_set< std::string > > getValidChildrenSymbolsAcrossSamples() { return m_valid_children_across_samples; }
		std::unordered_map< std::string, std::unordered_set< std::string > > getValidParentsSymbolsAcrossSamples() { return m_valid_parents_across_samples; }

		std::unordered_map< std::string, std::vector< std::string > > getValidParentsAsMapWithList();
		std::vector< std::vector< int > > getParentsSymbolsAsIdxs(const std::vector< std::string >& symbols);

	private:
		std::unordered_map< std::string, std::unordered_set< std::string > > getValidSymbolsAcrossSamples(std::function< std::unordered_set< std::string >(const Population::SharedPtr) >& funct);
		void setAllPotentialRootSymbols();
		void setAllSymbols();

		std::vector< Sample::SharedPtr > m_sample_ptrs;
		std::unordered_set< std::string > m_root_symbols;
		std::unordered_map< std::string, std::unordered_set< std::string > > m_valid_parents_across_samples;
		std::unordered_map< std::string, std::unordered_set< std::string > > m_valid_children_across_samples;
		std::unordered_set< std::string > m_all_symbols;
	};
}
