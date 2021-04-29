#pragma once
#include "IPersistence.h"

#include <queue>
#include <string>

class TrackerEvent;

class FilePersistence : public IPersistence
{
private:
    std::queue<TrackerEvent> eventQueue;

    std::string filepath;
    // Name of the file where the events will persist
    std::string filename;

public:
    FilePersistence(ISerializer* serializer, const std::string& filepath);
    ~FilePersistence();

    virtual void Send(const TrackerEvent& evt);
    virtual void Flush();
    virtual void Open();
};

