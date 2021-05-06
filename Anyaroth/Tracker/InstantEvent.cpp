#include "InstantEvent.h"
#include "Tracker.h"

InstantEvent::InstantEvent(const InstantType& id)
{
	this->SetTimeStamp();
	this->SetEventID("instant_event");
	this->SetEventInfo(mapOfMarks[id]);
}

InstantEvent::InstantEvent(const InstantType& id, const std::map<std::string, std::string>& attr)
{
	this->SetTimeStamp();
	this->SetEventID("instant_event");
	this->SetEventInfo(mapOfMarks[id]);
	this->SetEventAttr(attr);
}

InstantEvent::~InstantEvent()
{
}
