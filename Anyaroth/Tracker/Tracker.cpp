#include "Tracker.h"
#include "IPersistence.h"


Tracker* Tracker::_instance = nullptr;

Tracker::Tracker() : _persistenceObject(nullptr)
{
}

Tracker::~Tracker()
{
}

Tracker* Tracker::getInstance() {
    if (_instance == nullptr)
        _instance = new Tracker();
    return _instance;
}

void Tracker::Init(IPersistence* persistence, const std::string& sesion)
{
    _persistenceObject = persistence;
    _sesionID = GenerateMD5(sesion);
}

void Tracker::End()
{
    _persistenceObject->Flush();
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    _persistenceObject->Send(*event);
}

void Tracker::TrackEvent(const std::string& id, const std::string& attr)
{
    TrackerEvent tEvent = TrackerEvent();
    tEvent.setSessionID(_sesionID); // TODO: session ID should not be in every single event

    _persistenceObject->Send(tEvent);
}

std::string Tracker::GenerateMD5(const std::string& input)
{
    return md5(input);
}