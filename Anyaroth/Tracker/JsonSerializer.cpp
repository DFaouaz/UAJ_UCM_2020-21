#include "JSONSerializer.h"

JsonSerializer::JsonSerializer()
{
}

JsonSerializer::~JsonSerializer()
{
}

std::string JsonSerializer::Serialize(const TrackerEvent& trackerEvent) const
{
	return trackerEvent.ToJSON();
}
