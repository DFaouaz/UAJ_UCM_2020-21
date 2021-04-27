
#include "Tracker.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

int main() {
	Tracker* tracker = Tracker::GetInstance();
	// Initilitation
	tracker->Init(new FilePersistence(new JsonSerializer(), "jeje.txt"), "Prueba");

	tracker->TrackEvent("", "");

	// End of the system
	tracker->End();
	return 0;
}