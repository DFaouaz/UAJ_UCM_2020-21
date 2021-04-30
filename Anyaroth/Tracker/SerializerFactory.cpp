#include "SerializerFactory.h"
#include "JsonSerializer.h"
#include "CVSSerializer.h"

ISerializer* SerializerFactory::Create(TrackerSettings settings)
{
	switch (settings.format)
	{
	case TrackerSettings::FormatType::JSON:
		return new JSONSerializer();
		break;
	case TrackerSettings::FormatType::CSV:
		return new CVSSerializer();
		break;
	default:
		return new JSONSerializer();
		break;
	}

    return nullptr;
}
