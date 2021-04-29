#pragma once
#include <string>
#include <map>

class TrackerEvent
{
private:
	long long _timestamp;
	std::string _eventID;
	std::string _info;
	std::map<std::string, std::string> _attr;

public:
	TrackerEvent(const std::string& id, const std::string info);
	TrackerEvent(const std::string& id, const std::map<std::string, std::string>& attr);
	~TrackerEvent();

	virtual std::string ToJSON() const;

	void SetEventID(const std::string& id);
	const std::string& GetEventID() const;
};

