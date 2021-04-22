#pragma once

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "ISerializer.h"


class JsonSerializer : public ISerializer
{
public:
	JsonSerializer();
	~JsonSerializer();

	virtual std::string Serialize(const TrackerEvent& trackerEvent) const;
};

#endif