#include "Game.h"
#ifdef DEBUG
#include "checkML.h"
#endif // DEBUG

#include "Tracker.h"

int main(int argc, char* argv[])
{
	try
	{
		// Tracker init (ejemplo, aqui quiza no deberia de ir)
		Tracker::Init(TrackerSettings::FromFile("./tracker_config"));

		Game game;
		game.run();

		Tracker::TrackEvent("jugador_dispara", "asjhasd");
		Tracker::TrackEvent("button_pressed", "pause_button");
		Tracker::TrackEvent("level_end", "level_08");
		Tracker::TrackEvent("dict_info", std::map<std::string, std::string>(
			{
				{ "resume", "bullet_01" },
				{ "bullet_count", "25" },
				{ "damage_received", "124" }
			}));
			
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