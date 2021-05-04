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
	TrackerEvent() = default;
	TrackerEvent(const std::string& id, const std::string info);
	TrackerEvent(const std::string& id, const std::map<std::string, std::string>& attr);
	~TrackerEvent();

	virtual std::string ToJSON() const;
	virtual std::string ToCSV() const;

	void SetTimeStamp();

	void SetEventID(const std::string& id);
	void SetEventInfo(const std::string& info);
	void SetEventAttr(const std::map<std::string, std::string>& attr);
	const std::string& GetEventID() const;
};

