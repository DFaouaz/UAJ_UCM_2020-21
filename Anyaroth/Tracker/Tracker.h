#pragma once
#include "TrackerSettings.h"
#include "ProgressionEvent.h"
#include "InstantEvent.h"
#include "md5.h"
#include <string>
#include <vector>
#include <map>
#include <mutex>


class IPersistence;

class Tracker
{
private:
	static Tracker* _instance;
	std::string _sessionID = "";
	IPersistence* _persistenceObject;
	static std::string GenerateMD5(const std::string& input);
	static bool _initialized;

	TrackerSettings _settings;

	std::thread flushThread;
	std::condition_variable awakeCond;
	std::mutex persistenceMutex;

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
	static void TrackProgressionEvent(const ProgressionEvent::ProgressionType& type);
	static void TrackProgressionEvent(const ProgressionEvent::ProgressionType& type, const std::map<std::string, std::string>& attr);
	static void TrackInstantEvent(const std::string& info);
	static void TrackInstantEvent(const std::string& info, const std::map<std::string, std::string>& attr);

	static std::string GetSessionID();

	// Utilities
	static long long GetTimestamp();

private:
	static void AsyncFlush();
};

