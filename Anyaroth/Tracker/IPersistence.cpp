#include "IPersistence.h"

IPersistence::IPersistence(ISerializer* serializer)
{
	this->serializer = serializer;
}

IPersistence::~IPersistence()
{
	if (serializer != nullptr)
		delete serializer;
}
