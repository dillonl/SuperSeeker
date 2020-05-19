#include "Params.h"

namespace superseeker
{
	Params::Params(int argc, char** argv) :
		m_options("SuperSeeker", "Subclone Tree Builder")
	{
		this->m_options.add_options()
			("h,help","Print help message")
			("s,sample_path", "Path to sample file", cxxopts::value< std::string >())
			("o,output_path", "Path to output directory", cxxopts::value< std::string >())
			("t,threshold", "Subclone population threshold [optional - default is 0]", cxxopts::value< float >()->default_value("0"));
		this->m_options.parse(argc, argv);
	}

	Params::~Params()
	{
	}

	void Params::printHelp()
	{
		std::cout << "SuperSeeker: V1.0" << std::endl;
		std::cout << this->m_options.help() << std::endl;
	}

	bool Params::validateInput()
	{
		std::vector< std::string > errorMessages;
		if (!m_options.count("s"))
		{
			errorMessages.emplace_back("samples path is required");
		}
		if (errorMessages.size() > 0)
		{
			std::cout << "There was a problem parsing commands" << std::endl;
			for (auto message : errorMessages)
			{
				std::cout << message << std::endl;
			}
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Params::getHelpFlag()
	{
		return m_options.count("h") > 0;
	}

	std::string Params::getSamplesPath()
	{
		auto samplePath = m_options["s"].as< std::string >();
		return samplePath;
	}

	std::string Params::getOutputPath()
	{
		auto outputPath = m_options["o"].as< std::string >();
		return outputPath;
	}

	float Params::getThreshold()
	{
		return m_options["t"].as< float >();
	}

}
