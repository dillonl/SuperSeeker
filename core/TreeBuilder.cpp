#include "TreeBuilder.h"

#include <iostream>

namespace treefinder
{
	TreeBuilder::TreeBuilder(const std::string& filePath, float threshold) : m_threshold(threshold)
	{
		auto samplesProportions = extractSampleProportionsFromFile(filePath);
		populateSampleProportions(samplesProportions);
	}

	TreeBuilder::~TreeBuilder()
	{
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
		return proportionsMap;
	}

	void TreeBuilder::populateSampleProportions(const std::unordered_map< std::string, std::vector< std::tuple< char, float > > >& samplesProportions)
	{
		this->m_all_sample_proportions.clear();
		for (auto iter : samplesProportions)
		{
			auto sampleProportions = getTreesFromProportions(iter.second);
			this->m_all_sample_proportions.emplace(iter.first, sampleProportions);
		}
	}

	std::vector< Tree::SharedPtr > TreeBuilder::getTreesFromProportions(const std::vector< std::tuple< char, float > >& proportions)
	{
		std::vector< Tree::SharedPtr > treePtrs;
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
			// auto treePtr = std::make_shared< Tree >(proportions, parents);
			// std::shared_ptr< std::tuple< char, float > > treePtr = nullptr;
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
			treePtrs.emplace_back(nullptr);
			--parent;
		}
		std::cout << "trees: " << treePtrs.size() << std::endl;
		// exit(0);
		return treePtrs;
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
