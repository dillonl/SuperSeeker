#include "TreeBuilder.h"

namespace superseeker
{

	TreeBuilder::TreeBuilder(SamplesProcessor::SharedPtr samplesProcessorPtr) : m_samples_processor_ptr(samplesProcessorPtr)
	{
	}

	std::vector< Tree::SharedPtr > TreeBuilder::generateAllPossibleTrees()
	{
		std::vector< Tree::SharedPtr > treePtrs;
		for (auto rootSymbol : m_samples_processor_ptr->getAllPotentialRootSymbols())
		{
			auto tmpTreePtrs = generateAllTreesFromRoot(rootSymbol);
			treePtrs.insert(treePtrs.end(), tmpTreePtrs.begin(), tmpTreePtrs.end());
		}
		return treePtrs;
	}

	std::vector< Tree::SharedPtr > TreeBuilder::generateAllTreesFromRoot(std::string& rootSymbol)
	{
		auto childrenSymbolsMap = this->m_samples_processor_ptr->getValidChildrenSymbolsAcrossSamples();
		auto symbols = this->m_samples_processor_ptr->getSymbolsAsListWithRootAsFirst(rootSymbol);
		std::vector< std::vector< int > > symbolsParentsIdxs = this->m_samples_processor_ptr->getParentsSymbolsAsIdxs(symbols);
		std::vector< int > symbolsTreeParent(symbols.size(), 0);
		std::vector< std::vector< int > > trees;
		symbolsTreeParent[0] = -1;
		for (auto i = symbolsParentsIdxs.size() - 1; i >= 1; --i)
		{
			// std::cout << "working on: " << i << std::endl;
			for (auto j = i; j < symbolsParentsIdxs.size(); ++j)
			{
				// std::cout << "working on: " << i << ", " << j << std::endl;
				for (auto k = 0; k < symbolsParentsIdxs[j].size(); ++k)
				{
					symbolsTreeParent[j] = symbolsParentsIdxs[j][k];
					trees.emplace_back(symbolsTreeParent);
				}
			}
		}
		std::cout << "number of trees generated: " << trees.size() << std::endl;
		/*
		std::unordered_map< std::string, int > symbolToIdx;
		for (int i = 0; i < symbols.size(); ++i) { symbolToIdx.emplace(symbols[i], i); }
		auto mapOfParentsSymbols = this->m_samples_processor_ptr->getValidParentsAsMapWithList();
		std::vector< size_t > indexOfSymbolParents(symbols.size(), 0);

		*/
		std::vector< Tree::SharedPtr > treePtrs;

		// build the tree here, use the idea from the other treebuilder class
		return treePtrs;
	}


    /*
	std::vector< Tree::SharedPtr > TreeBuilder::generateAllTreesFromRoot(std::string& rootSymbol)
	{
		auto childrenSymbolsMap = this->m_samples_processor_ptr->getValidChildrenSymbolsAcrossSamples();
		auto symbols = this->m_samples_processor_ptr->getSymbolsAsListWithRootAsFirst(rootSymbol);
		std::unordered_map< std::string, int > symbolToIdx;
		for (int i = 0; i < symbols.size(); ++i) { symbolToIdx.emplace(symbols[i], i); }
		auto mapOfParentsSymbols = this->m_samples_processor_ptr->getValidParentsAsMapWithList();
		std::vector< size_t > indexOfSymbolParents(symbols.size(), 0);
		std::vector< int > symbolsTreeParent(symbols.size(), 0);
		symbolsTreeParent[0] = -1;
		for (int outerNumber = 1; outerNumber < symbols.size(); ++outerNumber)
		{
			auto outerParentsList = mapOfParentsSymbols[symbols[outerNumber]];
			for (int innerNumber = 0; innerNumber < mapOfParentsSymbols[symbols[outerNumber]].size(); ++innerNumber)
			{
				std::string outerNumbersParentSymbol = outerParentsList[innerNumber];
				auto innerValidChildren = childrenSymbolsMap[outerNumbersParentSymbol];
				if (innerValidChildren.find(symbols[outerNumber]) != innerValidChildren.end())
				{
					symbolsTreeParent[outerNumber] = symbolToIdx[outerNumbersParentSymbol];
				}
				else
				{
					std::cout << "not a viable tree " << outerNumbersParentSymbol << " " << symbols[outerNumber] << std::endl;
					continue;
				}
			}
		}
		std::vector< Tree::SharedPtr > treePtrs;

		// build the tree here, use the idea from the other treebuilder class
		return treePtrs;
	}
	*/
}
