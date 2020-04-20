#pragma once

#include "Noncopyable.hpp"

#include <memory>
#include <vector>
#include <tuple>

namespace treefinder
{
	class Tree : private Noncopyable
	{
	public:
		typedef std::shared_ptr< Tree > SharedPtr;
		Tree(const std::vector< std::tuple< char, float > >& proportions, std::vector< int >& parents);
		Tree() = delete;
		~Tree();
	};

	class SampleTrees : private Noncopyable
	{
	public:
		typedef std::shared_ptr< SampleTrees > SharedPtr;
	    SampleTrees(std::string& sampleName) : m_sample_name(sampleName) {}
		SampleTrees() = delete;
		~SampleTrees() {}
		std::string getSampleName() { return m_sample_name; }
		std::vector< Tree::SharedPtr >* getTreePtrsRef() { return &m_trees; }

	private:
		std::string m_sample_name;
		std::vector< Tree::SharedPtr > m_trees;
	};
}
