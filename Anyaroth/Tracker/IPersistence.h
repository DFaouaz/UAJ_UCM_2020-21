#pragma once
// TODO: incluir la clase TrackerEvent
// TODO: incluir la clase ISerializer
//#include ...


class IPersistence
{
protected:
	ISerializer* serializer;
public:
	IPersistence(ISerializer* serializer) : serializer(serializer) {};

	virtual void Send(const TrackerEvent& evt) = 0;
	virtual void Flush() = 0;
};

