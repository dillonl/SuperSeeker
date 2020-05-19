#pragma once

#include "Cluster.h"

#include <memory>
#include <unordered_map>
#include <iostream>

namespace superseeker
{
	class Node
	{
	public:
		typedef std::shared_ptr< Node > SharedPtr;
		Node() = delete;
		Node(const Node& noncopyable) = delete;

		Node operator=(const Node& noncopyable) = delete;
	    Node(int clusterID) : m_cluster_id(clusterID), m_parent_node_ptr(nullptr) {}

		void addChildNodePtr(Node::SharedPtr childNodePtr)
		{
			if (childNodePtr != nullptr && this->m_children_node_ptrs.find(childNodePtr->getClusterID()) == this->m_children_node_ptrs.end())
			{
				this->m_children_node_ptrs.emplace(childNodePtr->getClusterID(), childNodePtr);
			}
		}

		void setParentNodePtr(Node::SharedPtr parentNodePtr) { this->m_parent_node_ptr = parentNodePtr; }

		int getClusterID() { return this->m_cluster_id; }
		Node::SharedPtr getParentNodePtr() { return this->m_parent_node_ptr; }
		std::unordered_map< int, Node::SharedPtr > getChildrenNodePtrs() { return this->m_children_node_ptrs; }

	private:
		int m_cluster_id;
		Node::SharedPtr m_parent_node_ptr;
		std::unordered_map< int, Node::SharedPtr > m_children_node_ptrs;
	};
}
