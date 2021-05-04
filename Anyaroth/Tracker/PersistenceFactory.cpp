#include "PersistenceFactory.h"
#include "FilePersistence.h"
#include "ServerPersistence.h"

IPersistence* PersistenceFactory::Create(TrackerSettings settings, ISerializer* serializer)
{
	switch (settings.storage)
	{
	case TrackerSettings::StorageType::LOCAL:
		return new FilePersistence(serializer, settings.filepath);
		break;
	case TrackerSettings::StorageType::NET:
		return new ServerPersistence(serializer, settings.host, settings.port);
		break;
	default:
		return new FilePersistence(serializer, settings.host);
		break;
	}
}
