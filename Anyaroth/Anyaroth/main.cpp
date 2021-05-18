#include "Game.h"
#ifdef DEBUG
#include "checkML.h"
#endif // DEBUG

#include "Tracker.h"

int main(int argc, char* argv[])
{
	try
	{
		// Tracker init 
		Tracker::Init(TrackerSettings::FromFile("./tracker_config"));

		Game game;
		game.run();
			
		// End of the system
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