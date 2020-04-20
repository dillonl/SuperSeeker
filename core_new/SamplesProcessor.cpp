#include "SamplesProcessor.h"
#include "TreeBuilder.h"

namespace superseeker
{
	SamplesProcessor::SamplesProcessor(std::vector< Sample::SharedPtr > samplePtrs) :
		m_sample_ptrs(samplePtrs)
	{
		std::function< std::unordered_set< std::string >(const Population::SharedPtr) > parentsFunct = &Population::getPotentialDirectParentsSymbols;
		std::function< std::unordered_set< std::string >(const Population::SharedPtr) > childrenFunct = &Population::getPotentialDirectChildrenSymbols;
		setAllSymbols();
		m_valid_children_across_samples = getValidSymbolsAcrossSamples(childrenFunct);
		m_valid_parents_across_samples = getValidSymbolsAcrossSamples(parentsFunct);
		setAllPotentialRootSymbols();
		/*
		for (auto symbol : this->m_all_symbols)
		{
			std::cout << symbol << ": " << m_valid_parents_across_samples[symbol].size() << std::endl;
		}
		*/
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

	void SamplesProcessor::setAllSymbols()
	{
		// std::unordered_set< std::string > allSymbols;
		m_all_symbols.empty();
		for (auto samplePtr : m_sample_ptrs)
		{
			for (auto populationPtr : samplePtr->getPopulationPtrs())
			{
				m_all_symbols.emplace(populationPtr->getSymbol());
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

	std::unordered_map< std::string, std::unordered_set< std::string > > SamplesProcessor::getValidSymbolsAcrossSamples(std::function< std::unordered_set< std::string >(const Population::SharedPtr) >& funct)
	{
		std::unordered_map< std::string, std::unordered_set< std::string > > validSymbolMap; // all the parents (rep as symbol) with the consequent child symbol as the key
		for (auto symbol : this->m_all_symbols)
		{
			std::unordered_map< std::string, int > parentsCount;
			for (auto s : this->m_all_symbols) { parentsCount.emplace(s, 0); }
			for (auto samplePtr : this->m_sample_ptrs)
			{
				for (auto populationPtr : samplePtr->getPopulationPtrs())
				{
					if (populationPtr->getSymbol().compare(symbol) != 0) { continue; }
					auto pp = funct(populationPtr);
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
		return validSymbolMap;
	}

	void SamplesProcessor::setAllPotentialRootSymbols()
	{
		m_root_symbols.empty();
		for (auto samplePtr : this->m_sample_ptrs)
		{
			for (auto populationPtr : samplePtr->getPopulationPtrs())
			{
				auto symbol = populationPtr->getSymbol();
				auto frequency = populationPtr->getFrequency();
				float frequencySum = 0;
				for (auto pp : samplePtr->getPopulationPtrs())
				{
					if (pp->getSymbol().compare(symbol) == 0) { continue; } // we don't want to accumulate our frequency
					frequencySum += pp->getFrequency();
				}
				if (frequency >= frequencySum)
				{
					m_root_symbols.emplace(symbol);
				}
			}
		}
	}

	std::vector< std::string > SamplesProcessor::getSymbolsAsListWithRootAsFirst(const std::string& rootSymbol)
	{
		std::vector< std::string > symbols(m_all_symbols.begin(), m_all_symbols.end());
		for (int i = 1; i < symbols.size(); ++i)
		{
			if (symbols[i].compare(rootSymbol) == 0)
			{
				std::string zeroSymbol = symbols[0];
				symbols[i] = zeroSymbol;
				symbols[0] = rootSymbol;
				break;
			}
		}
		return symbols;
	}

	std::unordered_map< std::string, std::vector< std::string > > SamplesProcessor::getValidParentsAsMapWithList()
	{
		std::unordered_map< std::string, std::vector< std::string > > parentsMap;
		for (auto iter : m_valid_parents_across_samples)
		{
			auto parentsSymbols = m_valid_parents_across_samples[iter.first];
			std::vector< std::string > parentsContainer(parentsSymbols.size());
			int count = 0;
			for (auto parentSymbol : parentsSymbols)
			{
				parentsContainer[count++] = parentSymbol;
			}
			parentsMap[iter.first] = parentsContainer;
		}
		return parentsMap;
	}

	std::vector< std::vector< int > > SamplesProcessor::getParentsSymbolsAsIdxs(const std::vector< std::string >& symbols)
	{
		std::unordered_map< std::string, int > symbolToIdx;
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
