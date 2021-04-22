#pragma once
#include <string>

class TrackerEvent
{
private:
	std::string _id_session;

public:
	TrackerEvent();

	virtual std::string ToJSON() const;

	void Set_Session_ID(std::string id);
	std::string Get_Session_ID();
};

