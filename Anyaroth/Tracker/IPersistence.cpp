#include "IPersistence.h"

IPersistence::IPersistence(ISerializer* serializer)
{
	this->serializer = serializer;
}

IPersistence::~IPersistence()
{
	// maybe delete serializer here
}
