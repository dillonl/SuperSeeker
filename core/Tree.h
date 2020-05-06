#pragma once

#include "Node.h"
#include "Sample.h"

#include <unordered_map>
#include <vector>

namespace superseeker
{
	class Tree
	{
	public:
		typedef std::shared_ptr< Tree > SharedPtr;
		Tree(const Tree& noncopyable) = delete;
		Tree operator=(const Tree& noncopyable) = delete;
		Tree() = delete;

		Tree(const std::vector< int >& parentsList);
		~Tree();

		bool isValidTree(const std::vector< Sample::SharedPtr >& samplePtrs, float threshold);

	private:
		bool isValidSampleTree(Sample::SharedPtr samplePtr, int threshold);

		Node::SharedPtr m_root_node_ptr;
		std::vector< Node::SharedPtr > m_parents_list;
		std::unordered_map< int, Node::SharedPtr > m_node_map;
		std::vector< Node::SharedPtr > m_leaf_node_ptrs;
	};
}
