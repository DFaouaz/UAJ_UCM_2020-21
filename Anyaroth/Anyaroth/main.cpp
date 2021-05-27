#include "Game.h"
#ifdef DEBUG
#include "checkML.h"
#endif // DEBUG

#include "Tracker.h"

int main(int argc, char* argv[])
{
	try
	{
		ReplaySettings replaySettings = ReplaySettings::FromFile("./replay_config.cfg");

		// Tracker init 
		if (replaySettings.recording)
			Tracker::Init(TrackerSettings::FromFile("./tracker_config"));

		Game game(replaySettings);
		game.run();
			
		// End of the system
		if (replaySettings.recording)
			Tracker::End();
	}
	catch (string& exception)
	{
		cout << exception << endl;
	}
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	return 0;
}