#include "TreeBuilder.h"

#include <iostream>
#include <future>

namespace treefinder
{
	TreeBuilder::TreeBuilder(const std::string& filePath, float threshold) : m_file_path(filePath), m_threshold(threshold)
	{

	}

	TreeBuilder::~TreeBuilder()
	{
	}

	std::vector< SampleTrees::SharedPtr > TreeBuilder::getProcessedSampleTreesPtrs()
	{
		auto samplesProportions = extractSampleProportionsFromFile(this->m_file_path);
		m_forest_builder = getForestFromSampleProportions(samplesProportions);
		return m_forest_builder->getTrimmedSampleTrees();
	}

	std::unordered_map< std::string, std::vector< std::tuple< char, float > > > TreeBuilder::extractSampleProportionsFromFile(const std::string& filePath)
	{
		// for now the format is going to be:
		// samplename\t{label_1:proportion_1,label_2:proportion_2,...,label_3:proportion_n]\n
		/*
		FILE* fp = fopen(filePath.c_str(), "r");
		if (fp == NULL)
		{
			exit(EXIT_FAILURE);
		}

		char* line = NULL;
		size_t len = 0;
		while ((getline(&line, &len, fp)) != -1)
		{
			// using printf() in all tests for consistency
			printf("%s", line);
		}
		fclose(fp);
		if (line)
		{
			free(line);
		}
		*/
		std::unordered_map< std::string, std::vector< std::tuple< char, float > > > proportionsMap;
		std::vector< std::tuple< char, float > > proportions;
		// std::tuple< char, float > C1 = std::make_tuple('1', 0.40);
		// std::tuple< char, float > C2 = std::make_tuple('2', 0.28);
		// std::tuple< char, float > C3 = std::make_tuple('3', 0.8);
		// std::tuple< char, float > C4 = std::make_tuple('4', 0.24);
		proportionsMap["B0"] = {std::make_tuple('1', 0.40), std::make_tuple('2', 0.28), std::make_tuple('3', 0.8), std::make_tuple('6', 0.24)};
		proportionsMap["B1"] = {std::make_tuple('1', 0.50), std::make_tuple('2', 0.06), std::make_tuple('4', 0.36), std::make_tuple('5', 0.08)};
		proportionsMap["B2"] = {std::make_tuple('7', 0.60), std::make_tuple('8', 0.20)};
		proportionsMap["B3"] = {std::make_tuple('7', 0.28), std::make_tuple('8', 0.16), std::make_tuple('9', 0.36)};
		proportionsMap["B4"] = {std::make_tuple('7', 0.40)};
		/*
		std::tuple< char, float > A = std::make_tuple('A', 0.7);
		std::tuple< char, float > B = std::make_tuple('B', 0.1);
		std::tuple< char, float > C = std::make_tuple('C', 0.08);
		std::tuple< char, float > D = std::make_tuple('D', 0.06);
		std::tuple< char, float > E = std::make_tuple('E', 0.04);
		std::tuple< char, float > F = std::make_tuple('F', 0.02);
		std::tuple< char, float > G = std::make_tuple('G', 0.01);
		std::tuple< char, float > H = std::make_tuple('H', 0.01);
		std::tuple< char, float > I = std::make_tuple('I', 0.01);
		std::tuple< char, float > J = std::make_tuple('J', 0.01);
		std::tuple< char, float > K = std::make_tuple('K', 0.01);
		std::tuple< char, float > L = std::make_tuple('L', 0.01);
		std::tuple< char, float > M = std::make_tuple('M', 0.01);
		std::tuple< char, float > N = std::make_tuple('N', 0.01);
		proportions.emplace_back(A);
		proportions.emplace_back(B);
		proportions.emplace_back(C);
		proportions.emplace_back(D);
		proportions.emplace_back(E);
		proportions.emplace_back(F);
		proportions.emplace_back(G);
		proportions.emplace_back(H);
		proportions.emplace_back(I);
		proportions.emplace_back(J);
		proportions.emplace_back(K);
		proportions.emplace_back(L);
		proportions.emplace_back(M);
		proportions.emplace_back(N);
		proportionsMap["FOO"] = proportions;
		proportionsMap["BAR"] = proportions;
		proportionsMap["BIZ"] = proportions;
		proportionsMap["BAZ"] = proportions;
		*/
		return proportionsMap;
	}

	ForestBuilder::SharedPtr TreeBuilder::getForestFromSampleProportions(const std::unordered_map< std::string, std::vector< std::tuple< char, float > > >& samplesProportions)
	{
		std::vector< SampleTrees::SharedPtr > sampleTreesPtrs(samplesProportions.size());
		int count = 0;
		std::vector< std::future< void > > futureFuncts;
		for (auto iter : samplesProportions)
		{
			std::string sampleName = iter.first;
			std::vector< std::tuple< char, float > > proportions(iter.second);
			SampleTrees::SharedPtr sampleTreesPtr = std::make_shared< SampleTrees >(sampleName);
			auto funct = [this, count, sampleTreesPtr, proportions, &sampleTreesPtrs]()
			{
				populateTreesFromProportions(proportions, sampleTreesPtr->getTreePtrsRef());
				sampleTreesPtrs[count] = sampleTreesPtr;
			};
			futureFuncts.emplace_back(std::async(funct));
			++count;
		}
		for (auto& futureFunct : futureFuncts)
		{
			futureFunct.wait();
		}
		ForestBuilder::SharedPtr forestBuilderPtr = std::make_shared< ForestBuilder >(sampleTreesPtrs);
	}

	void TreeBuilder::populateTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions, std::vector< Tree::SharedPtr >* treePtrsPtr)
	{
		std::vector< int > parents(proportions.size(), 0);
		parents[0] = -1; // the root doesn't have a parent
		for (int i = 1; i < parents.size(); ++i) // initialize the array
		{
			parents[i] = i - 1;
		}
		int currentIdx = parents.size() - 1;
		int parent = currentIdx - 1;
		while (true)
		{
			if (parent < 0)
			{
				do
				{
					--currentIdx;
					if (parents[currentIdx] > 0)
					{
						--parents[currentIdx];
						break;
					}
				}while (currentIdx >= 1);
				if (currentIdx == 0)
				{
					/*
					std::cout << "ending" << std::endl;
					for (int i = 0; i < parents.size(); ++i)
					{
						std::cout << parents[i] << ",";
					}
					std::cout << std::endl;
					*/
					break;
				}
				++currentIdx;
				for (; currentIdx < parents.size() - 1; ++currentIdx)
				{
					parents[currentIdx] = currentIdx - 1;
				}
				parent = currentIdx - 1;
			}
			parents[currentIdx] = parent;
			/*
			for (int i = 0; i < parents.size(); ++i)
			{
				std::cout << parents[i] << ",";
			}
			std::cout << std::endl;
			*/
			auto treePtr = std::make_shared< Tree >(proportions, parents);
			treePtrsPtr->emplace_back(treePtr);
			--parent;
		}
		std::cout << "trees: " << treePtrsPtr->size() << std::endl;
	}

	std::vector< Tree::SharedPtr > TreeBuilder::getTreesFromProportions1(const std::vector< std::tuple< char, float > >& proportions)
	{
		std::vector< Tree::SharedPtr > trees;
		std::vector< std::function < void(int, std::vector< int >&) > > functions;
		std::vector< int > parents(proportions.size(), 0);
		parents[0] = -1; // the root doesn't have a parent
		for (int a1 = 0; a1 >= 0; --a1)
		{
			parents[1] = a1;
			for (int a2 = 1; a2 >= 0; --a2)
			{
				parents[2] = a2;
				for (int a3 = 2; a3 >= 0; --a3)
				{
					parents[3] = a3;
					for (int a4 = 3; a4 >= 0; --a4)
					{
						parents[4] = a4;
						for (int a5 = 4; a5 >= 0; --a5)
						{
							parents[5] = a5;
							for (int a6 = 5; a6 >= 0; --a6)
							{
								parents[6] = a6;
								for (int a7 = 6; a7 >= 0; --a7)
								{
									parents[7] = a7;
									for (int a8 = 7; a8 >= 0; --a8)
									{
										parents[8] = a8;
										for (int a9 = 8; a9 >= 0; --a9)
										{
											parents[9] = a9;
											for (int a10 = 9; a10 >= 0; --a10)
											{
												parents[10] = a10;
												auto treePtr = std::make_shared< Tree >(proportions, parents);
												trees.emplace_back(treePtr);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		std::cout << "trees: " << trees.size() << std::endl;
		return trees;
	}

	/*
	std::vector< Tree::SharedPtr > TreeBuilder::getTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions)
	{
		// it is presumed that the proportions are sorted by the float
		std::vector< Tree::SharedPtr > trees;
		std::vector< int > parents(proportions.size(), 0);
		return trees;
	}
	*/

	/*
	std::vector< Tree::SharedPtr > TreeBuilder::getTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions)
	{
		// it is presumed that the proportions are sorted by the float
		std::vector< Tree::SharedPtr > trees;
		std::vector< std::function < void(int, std::vector< int >&) > > functions;
		for (int i = 0; i < proportions.size(); ++i)
		{
			auto funct = [&proportions, &trees](int idx, std::vector< int >& parentIdxs)
			{
				for (int j = idx - 1; j >= 0; --j)
				{
					parentIdxs[idx] = j;
					auto treePtr = std::make_shared< Tree >(proportions, parentIdxs);
					trees.emplace_back(treePtr);
				}
			};
			functions.emplace_back(funct);
		}
		std::vector< int > parents(proportions.size(), 0);
		parents[0] = -1; // the root doesn't have a parent
		for (int i = 1; i < proportions.size(); ++i)
		{
			for (auto funct : functions)
			{
				funct(i, parents);
			}
		}
		std::cout << "we created " << trees.size() << " trees" << std::endl;
		return trees;
	}
	*/
}
