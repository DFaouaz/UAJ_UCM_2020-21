#pragma once
#include "IPersistence.h"
#include <queue>
#include <string>

class FilePersistence :
    public IPersistence
{
private:
    std::queue<TrackerEvent> eventQueue;

    // Name of the file where the events will persist
    std::string fileName;

public:
    virtual void Send(const TrackerEvent& evt);
    virtual void Flush();
};

