
#include "Tracker.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

int main() {
	// Initilitation
	TrackerSettings mySettings = {
		"",
		TrackerSettings::FormatType::CSV,
		TrackerSettings::StorageType::NET,
		"./",
		"localhost",
		8080,
		3.0f
	};

	Tracker::Init(mySettings);

	Tracker::TrackEvent("jugador_dispara", "asjhasd");
	Tracker::TrackEvent("button_pressed", "pause_button");
	Tracker::TrackEvent("level_end", "level_08");
	Tracker::TrackProgressionEvent(ProgressionType::INITIALIZED);
	Tracker::TrackProgressionEvent(ProgressionType::INITIALIZED);
	Tracker::TrackEvent("dict_info", std::map<std::string, std::string>(
	{ 
		{ "resume", "bullet_01" },
		{ "bullet_count", "25" }, 
		{ "damage_received", "124" } 
	}));

	Tracker::Flush();

	Tracker::TrackEvent("button_pressed", "pause_button");
	Tracker::TrackEvent("level_end", "level_08");
	Tracker::End();
	return 0;
}