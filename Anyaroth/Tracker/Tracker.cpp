#include "Tracker.h"
#include "IPersistence.h"
using namespace std;

Tracker* Tracker::_instance = nullptr;

Tracker::Tracker() = default;

Tracker* Tracker::getInstance() {
    if (_instance == nullptr)
        _instance = new Tracker();
    return _instance;
}

void Tracker::Init(IPersistence* persistence, string sesion)
{
    _persistenceObject = persistence;
    _sesionID = GenerateMD5(sesion);
}

void Tracker::End()
{
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    _persistenceObject->Send(event);
}

string GenerateMD5(string input)
{
    return md5(input);
}