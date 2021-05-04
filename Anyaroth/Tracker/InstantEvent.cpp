#include "InstantEvent.h"
#include "Tracker.h"

InstantEvent::InstantEvent(const InstantType& id)
{
	this->SetTimeStamp();
	this->SetEventID(mapOfMarks[id]);
	this->SetEventInfo("");
}

InstantEvent::InstantEvent(const InstantType& id, const std::map<std::string, std::string>& attr)
{
	this->SetTimeStamp();
	this->SetEventID(mapOfMarks[id]);
	this->SetEventInfo("");
	this->SetEventAttr(attr);
}

InstantEvent::~InstantEvent()
{
}
