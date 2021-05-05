#include "ProgressionEvent.h"
#include "Tracker.h"

ProgressionEvent::ProgressionEvent(const ProgressionType& type)
{
	this->SetTimeStamp();
	this->SetEventID("progression_event");
	this->SetEventInfo(mapOfMarks[type]);
}

ProgressionEvent::ProgressionEvent(const ProgressionType& type, const std::map<std::string, std::string>& attr) 
{
	this->SetTimeStamp();
	this->SetEventID("progression_event");
	this->SetEventInfo(mapOfMarks[type]);
	this->SetEventAttr(attr);
}

ProgressionEvent::~ProgressionEvent()
{
}
