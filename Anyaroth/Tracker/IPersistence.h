#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"


class IPersistence
{
protected:
	ISerializer* serializer;
public:
	IPersistence(ISerializer* serializer);
	~IPersistence();

	virtual bool Open() = 0;
	virtual void Send(const TrackerEvent& evt) = 0;
	virtual void Flush() = 0;
};

