#pragma once
#include "IPersistence.h"

#include <queue>
#include <string>


class FilePersistence : public IPersistence
{
private:
    bool initialized;
    std::queue<TrackerEvent> eventQueue;

    std::string filepath;
    // Name of the file where the events will persist
    std::string filename;

public:
    FilePersistence(ISerializer* serializer, const std::string& filepath);
    ~FilePersistence();

    virtual bool Open();
    virtual void Send(const TrackerEvent& evt);
    virtual void Flush();
};

