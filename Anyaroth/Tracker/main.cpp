
#include "Tracker.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

int main() {
	Tracker* tracker = Tracker::GetInstance();
	// Initilitation
	tracker->Init(new FilePersistence(new JsonSerializer()));

	tracker->TrackEvent("level_start", "level_08");
	tracker->TrackEvent("button_pressed", "pause_button");
	tracker->TrackEvent("button_pressed", std::vector<std::string>( { "resume", "bullet_01" }));
	tracker->TrackEvent("level_end", "level_08");

	// End of the system
	tracker->End();
	return 0;
}