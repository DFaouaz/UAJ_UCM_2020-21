#pragma once


class IPersistence;
class TrackerEvent;

class Tracker
{
private:
	static Tracker* _instance;
	IPersistence* _persistenceObject;
public:
	// Creates the instance if needed and returns it
	static Tracker* getInstance();
	void Init();
	void End();
	void TrackEvent(TrackerEvent* event);
};

