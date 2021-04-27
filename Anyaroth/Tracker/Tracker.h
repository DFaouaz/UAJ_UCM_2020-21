#pragma once
#include "md5.h"
#include <string>
#include <vector>

class TrackerEvent;
class IPersistence;

class Tracker
{
private:
	static Tracker* _instance;
	std::string _sessionID = "";
	IPersistence* _persistenceObject;
	std::string GenerateMD5(const std::string& input);

public:
	Tracker();
	~Tracker();

	// Creates the instance if needed and returns it
	static Tracker* GetInstance();
	void Init(IPersistence* persistence, const std::string& session = "");
	void End();
	void TrackEvent(TrackerEvent* event);
	void TrackEvent(const std::string& id, const std::string& info);
	void TrackEvent(const std::string& id, const std::vector<std::string>& info);

	const std::string& GetSessionID() const;

	// Utilities
	static long long GetTimestamp();
};

