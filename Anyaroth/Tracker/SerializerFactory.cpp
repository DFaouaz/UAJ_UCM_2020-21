#include "SerializerFactory.h"
#include "JsonSerializer.h"

ISerializer* SerializerFactory::Create(TrackerSettings settings)
{
	switch (settings.format)
	{
	case TrackerSettings::FormatType::JSON:
		return new JsonSerializer();
		break;
	case TrackerSettings::FormatType::CSV: // TODO: cambiar
		return new JsonSerializer();
		break;
	default:
		return new JsonSerializer();
		break;
	}

    return nullptr;
}
