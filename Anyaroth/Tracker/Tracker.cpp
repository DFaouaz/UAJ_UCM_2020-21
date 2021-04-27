#include "Tracker.h"
#include "IPersistence.h"
#include <chrono>
#include "PersistenceFactory.h"
#include "SerializerFactory.h"

Tracker* Tracker::_instance = nullptr;	

Tracker::Tracker() : _persistenceObject(nullptr), _serializer(nullptr)
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

void Tracker::Init(const TrackerSettings& settings)
{
    if (_instance != nullptr) return; // Cannot initialize more than once

    _instance = GetInstance();

    // Configure tracker
    _instance->_sessionID = GenerateMD5(settings.appID + std::to_string(GetTimestamp()));
    _instance->_serializer = SerializerFactory::Create(settings);
    _instance->_persistenceObject = PersistenceFactory::Create(settings, _instance->_serializer);

    // Init persitence thread
    // TODO: do stuff...
}

void Tracker::End()
{
    if (_instance == nullptr) return;
    _instance->_persistenceObject->Flush();
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    if (_instance == nullptr) return;
    _instance->_persistenceObject->Send(*event);
}

void Tracker::TrackEvent(const std::string& id, const std::string& info)
{
    if (_instance == nullptr) return;
    TrackerEvent tEvent = TrackerEvent(id, info);
    _instance->_persistenceObject->Send(tEvent);
}

void Tracker::TrackEvent(const std::string& id, const std::vector<std::string>& info)
{
    if (_instance == nullptr) return;
    TrackerEvent tEvent = TrackerEvent(id, info);
    _instance->_persistenceObject->Send(tEvent);
}

void Tracker::TrackEvent(const std::string& id, const std::map<std::string, std::string>& attr)
{
    if (_instance == nullptr) return;
    TrackerEvent tEvent = TrackerEvent(id, attr);
    _instance->_persistenceObject->Send(tEvent);
}

const std::string& Tracker::GetSessionID()
{
    if (_instance == nullptr) return "";
    return _instance->_sessionID;
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