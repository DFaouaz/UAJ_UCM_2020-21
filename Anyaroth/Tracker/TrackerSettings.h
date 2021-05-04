#pragma once
#include <string>

struct TrackerSettings
{
public:
	enum class FormatType {
		JSON,
		CSV
	};

	enum class StorageType {
		LOCAL,
		NET
	};

	std::string appID;
	FormatType format;
	StorageType storage;
	std::string filepath;
	std::string host;
	uint32_t port;

	float flushInterval;

	static TrackerSettings Default;

	static TrackerSettings FromFile(const std::string& filepath);
};


