#include "Tracker.h"
#include "IPersistence.h"
#include <chrono>
#include "PersistenceFactory.h"
#include "SerializerFactory.h"
#include <thread>

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
    _initialized = _instance->_persistenceObject->Open();

    if (!_initialized) {
        End(); // Close tracker immediately
        return;
    }

    // Init trace
    TrackEvent("application_start", settings.appID);

    if (settings.flushInterval > 0.0) {
        _instance->flushThread = std::thread([&] {
            AsyncFlush();
        });
    }
}

void Tracker::Flush()
{
    if (!_initialized) return;

    if (_instance->_settings.flushInterval > 0.0) return;

    // Defensive code
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Flush();
}

void Tracker::AsyncFlush() {    
    printf("Async flushing thread started successfully\n");

    while (_initialized) {
        std::unique_lock<std::mutex> lck(_instance->persistenceMutex);
        _instance->awakeCond.wait_for(lck, std::chrono::milliseconds((int)(_instance->_settings.flushInterval * 1000)), [&] { return !_initialized; });
        _instance->_persistenceObject->Flush();
        printf("Async flush done\n");
    }

    // Last flush
    _instance->persistenceMutex.lock();
    _instance->_persistenceObject->Flush();
    _instance->persistenceMutex.unlock();

    printf("Async flushing thread ended successfully\n");
}

void Tracker::End()
{
    if (!_initialized) return;

    // End trace
    TrackEvent("application_ends", _instance->_settings.appID);

    Flush();

    _initialized = false;
    _instance->awakeCond.notify_all();

    if(_instance->flushThread.joinable())
        _instance->flushThread.join();

    delete _instance;
}

void Tracker::TrackEvent(TrackerEvent* event)
{
    if (!_initialized) return;

    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(*event);
}

void Tracker::TrackEvent(const std::string& id, const std::string& info)
{
    if (!_initialized) return;
    TrackerEvent tEvent = TrackerEvent(id, info);

    std::unique_lock<std::mutex> lock (_instance->persistenceMutex);
    _instance->_persistenceObject->Send(tEvent);
}

void Tracker::TrackEvent(const std::string& id, const std::map<std::string, std::string>& attr)
{
    if (!_initialized) return;
    TrackerEvent tEvent = TrackerEvent(id, attr);
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(tEvent);
}

void Tracker::TrackProgressionEvent(const ProgressionEvent::ProgressionType& type)
{
    if (!_initialized) return;
    ProgressionEvent pEvent = ProgressionEvent(type);
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(pEvent);
}
void Tracker::TrackProgressionEvent(const ProgressionEvent::ProgressionType& type, const std::map<std::string, std::string>& attr)
{
    if (!_initialized) return;
    ProgressionEvent pEvent = ProgressionEvent(type, attr);
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(pEvent);
}

void Tracker::TrackInstantEvent(const InstantEvent::InstantType& id)
{
    if (!_initialized) return;
    InstantEvent pEvent = InstantEvent(id);
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(pEvent);
}

void Tracker::TrackInstantEvent(const InstantEvent::InstantType& id, const std::map<std::string, std::string>& attr)
{
    if (!_initialized) return;
    InstantEvent pEvent = InstantEvent(id, attr);
    std::unique_lock<std::mutex> lock(_instance->persistenceMutex);
    _instance->_persistenceObject->Send(pEvent);
}

std::string Tracker::GetSessionID()
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