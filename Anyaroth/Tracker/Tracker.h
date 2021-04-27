#pragma once
#include "md5.h"
#include <string>

class TrackerEvent;
class IPersistence;

class Tracker
{
private:
	static Tracker* _instance;
	std::string _sesionID = "";
	IPersistence* _persistenceObject;
	std::string GenerateMD5(const std::string& input);

public:
	Tracker();
	~Tracker();

	// Creates the instance if needed and returns it
	static Tracker* getInstance();
	void Init(IPersistence* persistence, const std::string& sesion);
	void End();
	void TrackEvent(TrackerEvent* event);
	void TrackEvent(const std::string& id, const std::string& attr);
};

