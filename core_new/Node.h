#pragma once

#include <memory>
#include <unordered_set>

namespace superseeker
{
	class Node
	{
	public:
		typedef std::shared_ptr< Node > SharedPtr;
		Node() = delete;
		Node(const Node& noncopyable) = delete;
		Node operator=(const Node& noncopyable) = delete;
	    Node(const std::string& symbol, Node::SharedPtr parentNodePtr) : m_symbol(symbol), m_parent_node_ptr(parentNodePtr) {}

		bool addChildNodePtr(Node::SharedPtr childNodePtr)
		{
			if (m_children_node_symbols.find(m_symbol) == m_children_node_symbols.end())
			{
				m_children_node_symbols.emplace(m_symbol);
				m_children_node_ptrs.emplace(childNodePtr);
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		std::string m_symbol;
		Node::SharedPtr m_parent_node_ptr;
		std::unordered_set< Node::SharedPtr > m_children_node_ptrs;
		std::unordered_set< std::string > m_children_node_symbols;
	};
}
