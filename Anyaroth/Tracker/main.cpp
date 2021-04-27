
#include "Tracker.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

int main() {
	// Initilitation
	Tracker::Init();

	Tracker::TrackEvent("jugador_dispara", "asjhasd");
	Tracker::TrackEvent("button_pressed", "pause_button");
	Tracker::TrackEvent("button_pressed", std::vector<std::string>( { "resume", "bullet_01" }));
	Tracker::TrackEvent("level_end", "level_08");
	Tracker::TrackEvent("dict_info", std::map<std::string, std::string>(
	{ 
		{ "resume", "bullet_01" },
		{ "bullet_count", "25" }, 
		{ "damage_received", "124" } 
	}));

	// End of the system
	Tracker::End();
	return 0;
}