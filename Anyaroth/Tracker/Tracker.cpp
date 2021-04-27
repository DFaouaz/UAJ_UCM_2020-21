#include "Tracker.h"
#include "IPersistence.h"
#include <chrono>


Tracker* Tracker::_instance = nullptr;

Tracker::Tracker() : _persistenceObject(nullptr)
{
}

Tracker::~Tracker()
{
}

Tracker* Tracker::GetInstance() {
    if (_instance == nullptr)
        _instance = new Tracker();
    return _instance;
}

void Tracker::Init(IPersistence* persistence, const std::string& session)
{
    _persistenceObject = persistence;
    _sessionID = GenerateMD5(session + std::to_string(GetTimestamp()));
}

void Tracker::End()
{
    _persistenceObject->Flush();
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    _persistenceObject->Send(*event);
}

void Tracker::TrackEvent(const std::string& id, const std::string& info)
{
    TrackerEvent tEvent = TrackerEvent(id, info);
    _persistenceObject->Send(tEvent);
}

void Tracker::TrackEvent(const std::string& id, const std::vector<std::string>& info)
{
    TrackerEvent tEvent = TrackerEvent(id, info);
    _persistenceObject->Send(tEvent);
}

const std::string& Tracker::GetSessionID() const
{
    return _sessionID;
}

long long Tracker::GetTimestamp()
{
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count();
}

std::string Tracker::GenerateMD5(const std::string& input)
{
    return md5(input);
}