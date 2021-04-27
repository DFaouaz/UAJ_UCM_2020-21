#pragma once
#include "ISerializer.h"
#include "TrackerSettings.h"

class SerializerFactory
{
public:
	static ISerializer* Create(TrackerSettings settings);
};

