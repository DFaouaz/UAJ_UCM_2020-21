#pragma once
#include "TrackerEvent.h"

class InstantEvent : public TrackerEvent
{
public:
	InstantEvent(const std::string& info);
	InstantEvent(const std::string& info, const std::map<std::string, std::string>& attr);
	~InstantEvent();
};