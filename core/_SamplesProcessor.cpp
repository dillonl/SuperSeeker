#include "SamplesProcessor.h"
#include "TreeBuilder.h"

namespace superseeker
{
	SamplesProcessor::SamplesProcessor(std::vector< Sample::SharedPtr > samplePtrs) :
		m_sample_ptrs(samplePtrs)
	{
		std::function< std::unordered_set< int >(const Cluster::SharedPtr) > parentsFunct = &Cluster::getPotentialDirectParentsIndices;
		std::function< std::unordered_set< int >(const Cluster::SharedPtr) > childrenFunct = &Cluster::getPotentialDirectChildrenIndices;
		setAllIndices();
		// m_valid_children_across_samples = getValidSymbolsAcrossIndices(childrenFunct);
		// m_valid_parents_across_samples = getValidSymbolsAcrossIndices(parentsFunct);
		setAllPotentialRootIndices();
	}

	SamplesProcessor::~SamplesProcessor()
	{
	}

	void printValid(std::unordered_map< std::string, std::unordered_set< std::string > > valid)
	{
		for (auto iter : valid)
		{
			std::cout << iter.first << ": ";
			for (auto validSymbol : iter.second)
			{
				std::cout << validSymbol << ", ";
			}
			std::cout << std::endl << "----------" << std::endl;
		}
	}

	void SamplesProcessor::setAllIndices()
	{
		this->m_all_indices.empty();
		for (auto samplePtr : this->m_sample_ptrs)
		{
			for (auto clusterPtr : samplePtr->getClusterPtrs())
			{
				this->m_all_indices.emplace(clusterPtr->getIndex());
			}
		}
	}

	std::vector< Tree::SharedPtr > SamplesProcessor::generateTreesFromSamples()
	{
		// auto treeBuilderPtr = std::make_shared< TreeBuilder >(allSymbols, rootSymbols, validParentsAcrossSample, validChildrenAcrossSample);
		auto treeBuilderPtr = std::make_shared< TreeBuilder >(shared_from_this());
		auto treePtrs = treeBuilderPtr->generateAllPossibleTrees();
		return treePtrs;
	}

	/*
	std::unordered_map< std::string, std::unordered_set< std::string > > SamplesProcessor::getValidSymbolsAcrossIndices(std::function< std::unordered_set< int >(const Cluster::SharedPtr) >& funct)
	{
		std::unordered_map< std::string, std::unordered_set< std::string > > validSymbolMap; // all the parents (rep as symbol) with the consequent child symbol as the key
		for (auto symbol : this->m_all_symbols)
		{
			std::unordered_map< std::string, int > parentsCount;
			for (auto s : this->m_all_symbols) { parentsCount.emplace(s, 0); }
			for (auto samplePtr : this->m_sample_ptrs)
			{
				for (auto clusterPtr : samplePtr->getClusterPtrs())
				{
					if (clusterPtr->getSymbol().compare(symbol) != 0) { continue; }
					auto pp = funct(clusterPtr);
					for (auto parentSymbol : pp)
					{
						parentsCount[parentSymbol] = parentsCount[parentSymbol] + 1;
					}
				}
			}
			std::unordered_set< std::string > validParents;
			for (auto iter : parentsCount)
			{
				if (iter.second == this->m_sample_ptrs.size())
				{
					validParents.emplace(iter.first);
				}
			}
			validSymbolMap[symbol] = validParents;
		}
		/*
		for (auto symbol : this->m_all_symbols)
		{
			std::cout << symbol << "{ ";
			for (auto parentSymbol : validSymbolMap[symbol])
			{
				std::cout << parentSymbol << ", ";
			}
			std::cout << " } " << std::endl;
		}
		*/
	/*
		return validSymbolMap;
	}
	*/

	void SamplesProcessor::setAllPotentialRootIndices()
	{
		this->m_root_indices.empty();
		for (auto samplePtr : this->m_sample_ptrs)
		{
			for (auto clusterPtr : samplePtr->getClusterPtrs())
			{
				auto clusterIndex = clusterPtr->getIndex();
				auto frequency = clusterPtr->getFrequency();
				float frequencySum = 0;
				for (auto pp : samplePtr->getClusterPtrs())
				{
					if (pp->getIndex() == clusterIndex) { continue; } // we don't want to accumulate our frequency
					frequencySum += pp->getFrequency();
				}
				if (frequency >= frequencySum)
				{
					this->m_root_indices.emplace(clusterIndex);
				}
			}
		}
	}

	std::vector< int > SamplesProcessor::getIndicesAsListWithRootAsFirst(int rootIndex)
	{
		std::vector< int > indices(this->m_all_indices.begin(), this->m_all_indices.end());
		for (int i = 1; i < indices.size(); ++i)
		{
			if (indices[i] == rootIndex)
			{
				int zeroIndex = indices[0];
				indices[i] = zeroIndex;
				indices[0] = rootIndex;
				break;
			}
		}
		return indices;
	}

	std::unordered_map< int, std::vector< int > > SamplesProcessor::getValidParentsAsMapWithList()
	{
		std::unordered_map< int, std::vector< int > > parentsMap;
		for (auto iter : m_valid_parents_across_samples)
		{
			auto parentsIndices = m_valid_parents_across_samples[iter.first];
			std::vector< std::string > parentsContainer(parentsIndices.size());
			int count = 0;
			for (auto parentSymbol : parentsSymbols)
			{
				parentsContainer[count++] = parentSymbol;
			}
			parentsMap[iter.first] = parentsContainer;
		}
		return parentsMap;
	}

	/*
	std::vector< std::vector< int > > SamplesProcessor::getParentsSymbolsAsIdxs(const std::vector< int >& indices)
	{
		std::unordered_map< int, int > indexToArrayIndex;
		for (int i = 0; i < symbols.size(); ++i)
		{
			symbolToIdx[symbols[i]] = i;
		}
		std::vector< std::vector< int > > parentsIdxs(symbols.size());
		for (int i = 0; i < symbols.size(); ++i)
		{
			auto symbol = symbols[i];
			auto parentsSymbols = m_valid_parents_across_samples[symbol];
			for (auto parentSymbol : parentsSymbols)
			{
				parentsIdxs[i].emplace_back(symbolToIdx[parentSymbol]); // add parent idx
			}
			// std::cout << "symbols #parents: " << parentsIdxs[i].size() << " " << parentsSymbols.size() << std::endl;
		}
		return parentsIdxs;
	}
	*/

	/*
	void SamplesProcessor::calculateValidParentsAndChildrensAcrossSamples()
	{
        std::unordered_map< std::string, std::unordered_set< std::string > > validParentsSymbolMap; // all the parents (rep as symbol) with the consequent child symbol as the key
		std::unordered_map< std::string, std::unordered_set< std::string > > validChildrenSymbolMap; // all the parents (rep as symbol) with the consequent child symbol as the key
        for (auto samplePtr : this->m_sample_ptrs)
		{
			std::cout << samplePtr->getSampleName() << std::endl;
			for (auto populationPtr : samplePtr->getPopulationPtrs())
			{
				auto symbol = populationPtr->getSymbol();
				auto pp = populationPtr->getPotentialDirectParentsSymbols();
				auto parentsIter = validParentsSymbolMap.find(symbol);
				if (parentsIter == validParentsSymbolMap.end())
				{
					validParentsSymbolMap.emplace(symbol, pp);
				}
				else
				{
					std::unordered_set< std::string > parentsSymbols;
					for (auto sym : (*parentsIter).second)
					{
						if (pp.find(sym) != pp.end())
						{
							parentsSymbols.emplace(sym);
						}
					}
					validParentsSymbolMap[symbol] =  parentsSymbols;
				}

				auto pc = populationPtr->getPotentialDirectChildrenSymbols();
				auto childrenIter = validChildrenSymbolMap.find(populationPtr->getSymbol());
				if (childrenIter == validChildrenSymbolMap.end())
				{
					validChildrenSymbolMap.emplace(populationPtr->getSymbol(), pc);
				}
				else
				{
					std::unordered_set< std::string > childrenSymbols;
					for (auto sym : (*childrenIter).second) { if (pc.find(sym) != pc.end()) { childrenSymbols.emplace(sym); } }
					validChildrenSymbolMap[symbol] = childrenSymbols;
				}
			}
		}
	}
	*/
}
