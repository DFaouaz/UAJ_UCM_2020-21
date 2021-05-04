#pragma once
#include "TrackerEvent.h"

enum class InstantType
{
	NOSE
};

class InstantEvent : public TrackerEvent
{
private:
	std::map<InstantType, std::string> mapOfMarks = {
		{InstantType::NOSE,"nose"}
	};
public:
	InstantEvent(const InstantType& id);
	InstantEvent(const InstantType& id, const std::map<std::string, std::string>& attr);
	~InstantEvent();
};