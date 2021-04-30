#include "TrackerEvent.h"
#include "Tracker.h"

TrackerEvent::TrackerEvent(const std::string& id, const std::string info)
{
    _timestamp = Tracker::GetTimestamp();
    _eventID = id;
    _info = info;
}

TrackerEvent::TrackerEvent(const std::string& id, const std::map<std::string, std::string>& attr)
{
    _timestamp = Tracker::GetTimestamp();
    _eventID = id;
    _info = "";
    _attr = attr;
}

TrackerEvent::~TrackerEvent()
{
}

std::string TrackerEvent::ToJSON() const
{
    std::string json;
    json = "{\n";
    json += "\"timestamp\" : " + std::to_string(_timestamp) + ",\n";
    json += "\"event_id\" : \"" + _eventID + "\",\n";

    // Info
    json += "\"info\" : \"" + _info + "\",\n";

    // Attributes
    json += "\"attributes\" : {";
    if (_attr.size() != 0) json += "\n";

    int count = 0;
    for (auto entry : _attr) {
        count++;
        json += "\"" + entry.first + "\" : \"" + entry.second + "\"";
        if (count != _attr.size()) json += ",\n";
        else json += "\n";
    }
    json += "}\n";

    // End of event object
    json += "}";

    return json;
}

std::string TrackerEvent::ToCSV() const
{
    std::string csv;
    csv += std::to_string(_timestamp) + "," + _eventID + "," + _info;

    for (auto entry : _attr)
        csv += "," + entry.first + "," + entry.second;

    return csv;
}

void TrackerEvent::SetEventID(const std::string& id)
{
    _eventID = id;
}

const std::string& TrackerEvent::GetEventID() const
{
    return _eventID;
}
