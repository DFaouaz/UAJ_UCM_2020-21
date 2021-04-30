#include "Tracker.h"
#include "IPersistence.h"
#include <chrono>
#include "PersistenceFactory.h"
#include "SerializerFactory.h"

Tracker* Tracker::_instance = nullptr;	
bool Tracker::_initialized = false;

Tracker::Tracker() : _persistenceObject(nullptr)
{
}

Tracker::~Tracker()
{
    if (_persistenceObject != nullptr)
        delete _persistenceObject;
}

Tracker* Tracker::GetInstance() {
    if (_instance == nullptr)
        _instance = new Tracker();
    return _instance;
}

void Tracker::Init(const TrackerSettings& settings)
{
    if (_initialized) return; // Cannot initialize more than once

    _instance = GetInstance();
    _instance->_settings = settings;

    // Configure tracker
    _instance->_sessionID = GenerateMD5(settings.appID + std::to_string(GetTimestamp()));
    ISerializer* serializer = SerializerFactory::Create(settings);
    _instance->_persistenceObject = PersistenceFactory::Create(settings, serializer);
    _instance->_persistenceObject->Open();


    _initialized = true;

    // Init trace
    TrackEvent("application_start", settings.appID);

    // Init persitence thread
    // TODO: do stuff...
}

void Tracker::Flush()
{
    if (!_initialized) return;
    _instance->_persistenceObject->Flush();
}

void Tracker::End()
{
    if (!_initialized) return;

    // End trace
    TrackEvent("application_ends", _instance->_settings.appID);

    _instance->_persistenceObject->Flush();
    _initialized = false;

    delete _instance;
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    if (!_initialized) return;
    _instance->_persistenceObject->Send(*event);
}

void Tracker::TrackEvent(const std::string& id, const std::string& info)
{
    if (!_initialized) return;
    TrackerEvent tEvent = TrackerEvent(id, info);
    _instance->_persistenceObject->Send(tEvent);
}

void Tracker::TrackEvent(const std::string& id, const std::map<std::string, std::string>& attr)
{
    if (!_initialized) return;
    TrackerEvent tEvent = TrackerEvent(id, attr);
    _instance->_persistenceObject->Send(tEvent);
}

const std::string& Tracker::GetSessionID()
{
    if (!_initialized) return "";
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