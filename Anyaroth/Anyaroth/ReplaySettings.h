#pragma once
#include <string>

struct ReplaySettings
{
public: 
	bool recording;
	bool replaying;
	std::string recordFileName;

	static ReplaySettings FromFile(const std::string& filepath);
};

