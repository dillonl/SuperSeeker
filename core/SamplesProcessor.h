#pragma once

#include "Sample.h"

#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

namespace superseeker
{
	class SamplesProcessor : public std::enable_shared_from_this< SamplesProcessor >
	{
	public:
		typedef std::shared_ptr< SamplesProcessor > SharedPtr;
		SamplesProcessor() = delete;
		SamplesProcessor(const SamplesProcessor& noncopyable) = delete;
		SamplesProcessor& operator=(const SamplesProcessor& noncopyable) = delete;
		SamplesProcessor(std::vector< Sample::SharedPtr > samplePtrs);
		~SamplesProcessor();

		std::vector< int > getAllPotentialRootSymbols();
	};
}
