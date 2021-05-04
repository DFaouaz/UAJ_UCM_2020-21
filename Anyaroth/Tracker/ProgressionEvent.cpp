#include "ProgressionEvent.h"
#include "Tracker.h"

ProgressionEvent::ProgressionEvent(const ProgressionType& id)
{
	this->SetTimeStamp();
	this->SetEventID(mapOfMarks[id]);
	this->SetEventInfo("");
}

ProgressionEvent::ProgressionEvent(const ProgressionType& id, const std::map<std::string, std::string>& attr) 
{
	this->SetTimeStamp();
	this->SetEventID(mapOfMarks[id]);
	this->SetEventInfo("");
	this->SetEventAttr(attr);
}

ProgressionEvent::~ProgressionEvent()
{
}
