#include "TrackerSettings.h"
#include <fstream>
#include <sstream>
#include <vector>

TrackerSettings TrackerSettings::Default =
{
	"",
	FormatType::JSON,
	StorageType::LOCAL,
	"./",
	"localhost",
	8080,
	3.0f
};

TrackerSettings TrackerSettings::FromFile(const std::string& filepath)
{
	TrackerSettings settings = Default;
	// Open file
	std::ifstream file;
	file.open(filepath);

	if(!file.is_open()) 
	{
		printf("Error ocurred while opening settings file: \n %s\n", filepath.c_str());
		settings = Default;
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

			if (id == "app_id") 
			{
				settings.appID = value;
			}
			else if (id == "format")
			{
				if (value == "json")
					settings.format = FormatType::JSON;
				else if (value == "csv")
					settings.format = FormatType::CSV;
				else
					settings.format = FormatType::JSON;
			}
			else if (id == "storage")
			{
				if (value == "local")
					settings.storage = StorageType::LOCAL;
				else if (value == "net")
					settings.storage = StorageType::NET;
				else
					settings.storage = StorageType::LOCAL;
			}
			else if (id == "filepath")
			{
				settings.filepath = value;
			}
			else if (id == "host") 
			{
				settings.host = value;
			}
			else if (id == "port") 
			{
				settings.port = static_cast<uint32_t>(std::stoul(value));
			}
			else if (id == "flush_interval") 
			{
				settings.flushInterval = (float)std::atof(value.c_str());
			}
		}
	}
	catch (...) 
	{
		printf("Config file format not valid\nIt should be \"parameter_name : value\"\n");
		settings = Default;
		return settings;
	}
	return settings;
}
