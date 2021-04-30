#include "JSONSerializer.h"
#include "TrackerEvent.h"

JSONSerializer::JSONSerializer()
{
}

JSONSerializer::~JSONSerializer()
{
}

std::string JSONSerializer::Append(const std::string& content, const std::string& data) const
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

std::string JSONSerializer::Serialize(const TrackerEvent& trackerEvent) const
{
	return trackerEvent.ToJSON();
}

std::string JSONSerializer::GetExtension() const
{
	return ".json";
}
