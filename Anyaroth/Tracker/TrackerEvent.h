#pragma once
#include <string>
#include <vector>

class TrackerEvent
{
private:
	long long _timestamp;
	std::string _eventID;
	std::vector<std::string> _info;

public:
	TrackerEvent(const std::string& id, const std::string info);
	TrackerEvent(const std::string& id, const std::vector<std::string>& info);
	~TrackerEvent();

	virtual std::string ToJSON() const;

	void SetEventID(const std::string& id);
	const std::string& GetEventID() const;
};

