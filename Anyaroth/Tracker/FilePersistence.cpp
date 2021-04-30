#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>

FilePersistence::FilePersistence(ISerializer* serializer, const std::string& filepath) : IPersistence(serializer)
{
	this->filepath = filepath;
	filename = std::to_string(Tracker::GetTimestamp()) + serializer->GetExtension();
	initialized = false;
}

FilePersistence::~FilePersistence()
{
}

bool FilePersistence::Open()
{
	bool result = true;
	try {
		std::ofstream file;
		file.open(filepath + filename);
		file << "";
		file.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error ocurred trying to open file:\n" + filepath + filename << "\n";
		std::cerr << "Error: " << e.what() << '\n';
		result = false;
	}

	return initialized = result;
}

// Receives a tracker event and adds it to the event queue
void FilePersistence::Send(const TrackerEvent& evt)
{
	if (!initialized) return;
	eventQueue.push(evt);
}

// Flushes all the content inside the event queue into a file
void FilePersistence::Flush()
{
	if (!initialized) return;
	// Create and open the text file
	std::ifstream file;
	file.open(filepath + filename);

	std::string serializedText;

	file.seekg(0, std::ios::end);
	serializedText.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	serializedText.assign((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();

	std::ofstream fileO;
	fileO.open(filepath + filename);

	while (!eventQueue.empty())
	{
		TrackerEvent evt = eventQueue.front(); eventQueue.pop();
		serializedText = serializer->Append(serializedText, serializer->Serialize(evt));
	}

	// Write the serialized text to the file
	fileO << serializedText;

	// Close the file
	fileO.close();
}
