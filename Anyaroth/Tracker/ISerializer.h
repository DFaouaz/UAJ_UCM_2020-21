#pragma once

#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <string>

class TrackerEvent;

class ISerializer
{
public:
	ISerializer();
	virtual ~ISerializer();

	virtual std::string Serialize(const TrackerEvent& trackerEvent) const = 0;
	virtual std::string GetExtension() const = 0;

};

#endif