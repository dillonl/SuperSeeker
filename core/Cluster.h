#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

namespace superseeker
{
	class Cluster
	{
	public:
		typedef std::shared_ptr< Cluster > SharedPtr;
		Cluster() = delete;
		Cluster( const Cluster& noncopyable) = delete;
		Cluster& operator=( const Cluster& noncopyable) = delete;

	    Cluster(int id, const float frequency);
		~Cluster();

		int getID() { return this->m_id; }
		float getFrequency() { return this->m_frequency; }

	private:
		int m_id;
		float m_frequency;
	};
}
