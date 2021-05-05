#pragma once
#include "TrackerEvent.h"


class ProgressionEvent : public TrackerEvent
{
public:
	enum class ProgressionType
	{
		INITIALIZED, PROGRESSED, COMPLETED
	};

private:
	std::map<ProgressionType, std::string> mapOfMarks = {
		{ProgressionType::INITIALIZED,"initialized"},
		{ProgressionType::PROGRESSED,"progressed"},
		{ProgressionType::COMPLETED, "completed"}
	};
public:
	ProgressionEvent(const ProgressionType& type);
	ProgressionEvent(const ProgressionType& type, const std::map<std::string, std::string>& attr);
	~ProgressionEvent();
};

