#pragma once

#include <memory>

#include <cxxopts.hpp>

namespace superseeker
{
	class Params
	{
	public:
		typedef std::shared_ptr< Params > SharedPtr;
		Params() = delete;
		Params( const Params& noncopyable ) = delete;
		Params& operator=( const Params& noncopyable ) = delete;
		Params(int argc, char** argv);
		~Params();

		void printHelp();
		bool validateInput();

		std::string getSamplesPath();
		std::string getOutputPath();
		float getThreshold();
		bool getHelpFlag();

	private:
		cxxopts::Options m_options;
	};
}
