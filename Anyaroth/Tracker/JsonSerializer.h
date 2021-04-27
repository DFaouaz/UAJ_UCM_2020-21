#pragma once

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "ISerializer.h"

class TrackerEvent;

class JsonSerializer : public ISerializer
{
public:
	JsonSerializer();
	~JsonSerializer();

	virtual std::string Append(const std::string& content, const std::string& data) const;
	virtual std::string Serialize(const TrackerEvent& trackerEvent) const;
	virtual std::string GetExtension() const;
};

#endif