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
	std::string host; // This is the net host or the filepath
	float flushInterval;

	static TrackerSettings Default;
};


