#include "TrackerEvent.h"

TrackerEvent::TrackerEvent()
{
}

TrackerEvent::~TrackerEvent()
{
}

std::string TrackerEvent::ToJSON() const
{
    std::string json;

    json = "{";
    json += "\"session_id\":" + _sessionID;
    json += "}";

    return json;
}

void TrackerEvent::setSessionID(const std::string& id)
{
    _sessionID = id;
}

const std::string& TrackerEvent::getSessionID() const
{
    return _sessionID;
}
