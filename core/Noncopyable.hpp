#pragma once

namespace treefinder
{
	class Noncopyable
	{
	public:
		Noncopyable( const Noncopyable& noncopyable) = delete;
		Noncopyable& operator=( const Noncopyable& noncopyable) = delete;

		Noncopyable() = default;

	};
}
