#pragma once
#include <string>

class TrackerEvent
{
private:
	std::string _sessionID;

public:
	TrackerEvent();
	~TrackerEvent();

	virtual std::string ToJSON() const;

	void setSessionID(const std::string& id);
	const std::string& getSessionID() const;
};

