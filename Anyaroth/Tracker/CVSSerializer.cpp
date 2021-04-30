#include "CVSSerializer.h"
#include "TrackerEvent.h"

CVSSerializer::CVSSerializer()
{
}

CVSSerializer::~CVSSerializer()
{
}

std::string CVSSerializer::Append(const std::string& content, const std::string& data) const
{
    return content + "\n" + data;
}

std::string CVSSerializer::Serialize(const TrackerEvent& trackerEvent) const
{
    return trackerEvent.ToCSV();
}

std::string CVSSerializer::GetExtension() const
{
    return ".csv";
}
