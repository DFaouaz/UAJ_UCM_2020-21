#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"
//#include ...


class IPersistence
{
protected:
	ISerializer* serializer;
public:
	IPersistence(ISerializer* serializer);
	~IPersistence();

	virtual void Send(const TrackerEvent& evt) = 0;
	virtual void Flush() = 0;
};

