#pragma once
#include "TrackerEvent.h"

enum class ProgressionType
{
	INITIALIZED, PROGRESSED, COMPLETED
};

class ProgressionEvent : public TrackerEvent
{
private:
	std::map<ProgressionType, std::string> mapOfMarks = {
		{ProgressionType::INITIALIZED,"initialized"},
		{ProgressionType::PROGRESSED,"progressed"},
		{ProgressionType::COMPLETED, "completed"}
	};
public:
	ProgressionEvent(const ProgressionType& id);
	ProgressionEvent(const ProgressionType& id, const std::map<std::string, std::string>& attr);
	~ProgressionEvent();
};

