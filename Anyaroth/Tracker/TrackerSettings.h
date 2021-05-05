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

	float flushInterval; // If flush interval is greater than 0.0, the tracker assumes async flush should be used.

	static TrackerSettings Default;

	static TrackerSettings FromFile(const std::string& filepath);
};


