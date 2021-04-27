#include "JSONSerializer.h"
#include "TrackerEvent.h"

JsonSerializer::JsonSerializer()
{
}

JsonSerializer::~JsonSerializer()
{
}

std::string JsonSerializer::Append(const std::string& content, const std::string& data) const
{
	std::string result = content;
	if (content == "") result = "[\n]";

	result.pop_back(); // Remove last bracket

	if (0 <= result.size() - 2 && result[result.size() - 2] == '}') 
	{ 
		result.pop_back();
		result += ",\n"; 
	}

	result += data;
	result += "\n]";

	return result;
}

std::string JsonSerializer::Serialize(const TrackerEvent& trackerEvent) const
{
	return trackerEvent.ToJSON();
}

std::string JsonSerializer::GetExtension() const
{
	return ".json";
}
