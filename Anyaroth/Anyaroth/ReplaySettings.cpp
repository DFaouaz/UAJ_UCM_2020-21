#include "ReplaySettings.h"
#include <fstream>
#include <sstream>
#include <vector>

ReplaySettings ReplaySettings::FromFile(const std::string& filepath)
{
    ReplaySettings settings;

	// Open file
	std::ifstream file;
	file.open(filepath);

	if (!file.is_open())
	{
		printf("Error ocurred while opening settings file: \n %s\n", filepath.c_str());
		return settings;
	}

	std::string content;

	file.seekg(0, std::ios::end);
	content.reserve((size_t)file.tellg());
	file.seekg(0, std::ios::beg);

	content.assign((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();

	int initIndex = 0;
	int foundIndex = 0;
	std::string splitted;
	std::vector<std::string> results;

	// Split
	while (foundIndex >= 0)
	{
		foundIndex = content.find("\n", initIndex);
		splitted = content.substr(initIndex, foundIndex - initIndex);
		initIndex = foundIndex + 1;
		results.push_back(splitted);
	}

	std::string id;
	std::string value;
	char token;

	try
	{
		for (std::string str : results)
		{
			std::stringstream ss;
			ss.str(str);
			if (!(ss >> id >> token >> value)) throw std::exception();
			if (token != ':') throw std::exception();

			if (id == "recording")
			{
				settings.recording = (value == "0") ? false : true;
			}
			else if (id == "replaying")
			{
				settings.replaying = (value == "0") ? false : true;
			}
			else if (id == "recordFileName")
			{
				settings.recordFileName = value;
			}
		}
	}
	catch (...)
	{
		printf("Config file format not valid\nIt should be \"parameter_name : value\"\n");
		return settings;
	}
	return settings;

}
