#pragma once
#include "TrackerSettings.h"
#include "md5.h"
#include <string>
#include <vector>
#include <map>

class TrackerEvent;
class IPersistence;

class Tracker
{
private:
	static Tracker* _instance;
	std::string _sessionID = "";
	IPersistence* _persistenceObject;
	static std::string GenerateMD5(const std::string& input);
	static bool _initialized;

public:
	Tracker();
	~Tracker();

	// Creates the instance if needed and returns it
	static Tracker* GetInstance();
	static void Init(const TrackerSettings& settings = TrackerSettings::Default);
	static void Flush();
	static void End();
	static void TrackEvent(TrackerEvent* event);
	static void TrackEvent(const std::string& id, const std::string& info);
	static void TrackEvent(const std::string& id, const std::map<std::string, std::string>& attr);

	static const std::string& GetSessionID();

	// Utilities
	static long long GetTimestamp();
};

