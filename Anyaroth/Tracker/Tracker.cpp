#include "Tracker.h"
using namespace std;

Tracker* Tracker::_instance = nullptr;

Tracker::Tracker() = default;

Tracker* Tracker::getInstance() {
    if (_instance == nullptr)
        _instance = new Tracker();
    return _instance;
}

void Tracker::Init()
{
}

void Tracker::End()
{
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    //_persistenceObject.send(event);
}
