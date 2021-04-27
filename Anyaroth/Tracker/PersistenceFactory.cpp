#include "PersistenceFactory.h"
#include "FilePersistence.h"

IPersistence* PersistenceFactory::Create(TrackerSettings settings, ISerializer* serializer)
{
	switch (settings.storage)
	{
	case TrackerSettings::StorageType::LOCAL:
		return new FilePersistence(serializer, settings.host);
		break;
	case TrackerSettings::StorageType::NET: // TODO: cambiar
		return new FilePersistence(serializer, settings.host);
		break;
	default:
		return new FilePersistence(serializer, settings.host);
		break;
	}
}
