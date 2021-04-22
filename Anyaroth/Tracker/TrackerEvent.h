#pragma once
#include <string>

class TrackerEvent
{
private:
	std::string _id_session;

public:
	TrackerEvent() {}

	std::string ToJSON();

	void Set_Session_ID(std::string id);
	std::string Get_Session_ID();
};

