#pragma once
#include "TrackerEvent.h"



class InstantEvent : public TrackerEvent
{
public:
	enum class InstantType
	{
		LAUNCH
	};
private:
	std::map<InstantType, std::string> mapOfMarks = {
		{InstantType::LAUNCH,"Lanzado"}
	};
public:
	InstantEvent(const InstantType& id);
	InstantEvent(const InstantType& id, const std::map<std::string, std::string>& attr);
	~InstantEvent();
};