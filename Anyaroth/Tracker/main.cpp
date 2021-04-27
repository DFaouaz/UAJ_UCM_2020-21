
#include "Tracker.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

int main() {
	Tracker* tracker = Tracker::GetInstance();
	// Initilitation
	tracker->Init(new FilePersistence(new JsonSerializer()));


	tracker->TrackEvent("jugador_dispara", "asjhasd");
	tracker->TrackEvent("button_pressed", "pause_button");
	tracker->TrackEvent("button_pressed", std::vector<std::string>( { "resume", "bullet_01" }));
	tracker->TrackEvent("level_end", "level_08");
	tracker->TrackEvent("dict_info", std::map<std::string, std::string>(
	{ 
		{ "resume", "bullet_01" },
		{ "bullet_count", "25" }, 
		{ "damage_received", "124" } 
	}));

	// End of the system
	tracker->End();
	return 0;
}