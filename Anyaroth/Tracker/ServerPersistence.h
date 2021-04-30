#pragma once
#include "IPersistence.h"
#include <queue>


class ServerPersistence : public IPersistence
{
public:
	ServerPersistence(ISerializer* serializer, const std::string& address, uint32_t port);
	~ServerPersistence();

	virtual bool Open();
	virtual void Send(const TrackerEvent& evt) ;
	virtual void Flush();

private:
	bool initialized;

	// Persistence data
	std::queue<TrackerEvent> eventQueue;

	// Server data
	std::string address;
	uint32_t port;

	// Socket data
	int32_t fdSock;

};

