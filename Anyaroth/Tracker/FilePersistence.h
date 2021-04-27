#pragma once
#include "IPersistence.h"

#include <queue>
#include <string>

class TrackerEvent;

class FilePersistence : public IPersistence
{
private:
    std::queue<TrackerEvent> eventQueue;

    // Name of the file where the events will persist
    // TODO: filename should be generated automatically (UNIX timestamp)
    std::string fileName;

public:
    FilePersistence(ISerializer* serializer, const std::string& filepath);
    ~FilePersistence();

    virtual void Send(const TrackerEvent& evt);
    virtual void Flush();
};

