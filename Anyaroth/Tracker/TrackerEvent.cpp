#include "TrackerEvent.h"
#include "Tracker.h"

TrackerEvent::TrackerEvent(const std::string& id, const std::string info)
{
    _timestamp = Tracker::GetTimestamp();
    _eventID = id;
    _info = { info };
}

TrackerEvent::TrackerEvent(const std::string& id, const std::vector<std::string>& info)
{
    _timestamp = Tracker::GetTimestamp();
    _eventID = id;
    _info = info;
}

TrackerEvent::~TrackerEvent()
{
}

std::string TrackerEvent::ToJSON() const
{
    std::string json;
    json = "{\n";
    json += "\"timestamp\" : " + std::to_string(_timestamp) + ",\n";
    json += "\"event_id\" : " + _eventID + ",\n";
    json += "\"info\" : [\n";

    for (int i = 0; i < _info.size(); i++) {
        json += _info[i];
        if (i != _info.size() - 1) json += ",";
        json += "\n";
    }
    json += "]\n";
    json += "},\n";

    return json;
}

void TrackerEvent::SetEventID(const std::string& id)
{
    _eventID = id;
}

const std::string& TrackerEvent::GetEventID() const
{
    return _eventID;
}
