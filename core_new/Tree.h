#pragma once

#include "Node.h"

#include <unordered_map>

namespace superseeker
{
	class Tree
	{
	public:
		typedef std::shared_ptr< Tree > SharedPtr;
		Tree(Node::SharedPtr rootNodePtr);
		Tree() = delete;
		~Tree();

	private:
		Node::SharedPtr m_root_node_ptr;
		std::unordered_map< std::string, bool > m_visited_map;
	};
}
