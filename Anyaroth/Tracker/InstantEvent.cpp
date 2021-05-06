#include "InstantEvent.h"
#include "Tracker.h"

InstantEvent::InstantEvent(const std::string& info)
{
	this->SetTimeStamp();
	this->SetEventID("instant_event");
	this->SetEventInfo(info);
}

InstantEvent::InstantEvent(const std::string& info, const std::map<std::string, std::string>& attr)
{
	this->SetTimeStamp();
	this->SetEventID("instant_event");
	this->SetEventInfo(info);
	this->SetEventAttr(attr);
}

InstantEvent::~InstantEvent()
{
}
