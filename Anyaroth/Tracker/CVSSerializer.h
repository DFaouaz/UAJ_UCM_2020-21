#pragma once

#ifndef CSV_SERIALIZER_H
#define CSV_SERIALIZER_H

#include "ISerializer.h"

class CVSSerializer : public ISerializer
{

public:
	CVSSerializer();
	~CVSSerializer();

	virtual std::string Append(const std::string& content, const std::string& data) const;
	virtual std::string Serialize(const TrackerEvent& trackerEvent) const;
	virtual std::string GetExtension() const;
};

#endif
