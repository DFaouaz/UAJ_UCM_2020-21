#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>

FilePersistence::FilePersistence(ISerializer* serializer, const std::string& filepath) : IPersistence(serializer)
{
	this->filepath = filepath;
	filename = std::to_string(Tracker::GetTimestamp()) + serializer->GetExtension();
}

FilePersistence::~FilePersistence()
{
}

// Receives a tracker event and adds it to the event queue
void FilePersistence::Send(const TrackerEvent& evt)
{
	eventQueue.push(evt);
}

// Flushes all the content inside the event queue into a file
void FilePersistence::Flush()
{
	// Create and open the text file
	std::ofstream file(filepath + filename);

	std::string serializedText;
	while (!eventQueue.empty())
	{
		TrackerEvent evt = eventQueue.front(); eventQueue.pop();
		serializedText.append(serializer->Serialize(evt));
	}

	// Write the serialized text to the file
	file << serializedText;

	// Close the file
	file.close();
}
