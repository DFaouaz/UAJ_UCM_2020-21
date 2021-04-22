#include "TrackerEvent.h"

TrackerEvent::TrackerEvent()
{
}

std::string TrackerEvent::ToJSON() const
{
    std::string json;

    json = "{";
    json += "\"id_session\":" + _id_session;
    json += "}";

    return json;
}

void TrackerEvent::Set_Session_ID(std::string id)
{
    _id_session = id;
}

std::string TrackerEvent::Get_Session_ID()
{
    return _id_session;
}
