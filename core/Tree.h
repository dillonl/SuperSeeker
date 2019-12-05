#pragma once

#include <memory>
#include <vector>
#include <tuple>

namespace treefinder
{
	class Tree
	{
	public:
		typedef std::shared_ptr< Tree > SharedPtr;
		Tree(const std::vector< std::tuple< char, float > >& proportions, std::vector< int >& parents);
		~Tree();

		Tree( const Tree& noncopyable) = delete;
		Tree& operator=( const Tree& noncopyable) = delete;
		Tree() = delete;
	};
}
