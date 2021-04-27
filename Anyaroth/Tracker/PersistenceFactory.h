#pragma once
#include "IPersistence.h"
#include "TrackerSettings.h"

class PersistenceFactory
{
public:
	static IPersistence* Create(TrackerSettings settings, ISerializer* serializer);
};

