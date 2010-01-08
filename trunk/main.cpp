#include "include_modules.h"
#include <string>

#ifdef __SDL_
	#include "interface_SDL.h"
	#define DISPLAY InterfaceSDL
#else
	#include "interface_console.h"
	#define DISPLAY InterfaceConsole
#endif

using namespace std;

int main(int argc, char * argv[])
{
	try
	{
		Interface * poInterface = DISPLAY::poGetInstance();

		Menu oMenu;
		oMenu.AddOption("1.One player game (human VS computer)");
		oMenu.AddOption("2.Two player game (human VS human)");
		oMenu.AddOption("3.Edition mode");
		oMenu.AddOption("4.Quit");

		Module * poChoosenModule = 0;	// Create a new game
		bool bQuit = false;
		char iMenuEntry;

		while(!bQuit)
		{
			try
			{
				while(!poChoosenModule && !bQuit)
				{
					iMenuEntry = poInterface->cGetMenuEntry(oMenu);

					switch(iMenuEntry)
					{
					  case '1' :
						poChoosenModule = new OnePlayerGame;
						break;
					  case '2' :
						poChoosenModule = new TwoPlayersGame;
						break;
					  case '3' :
						/*poInterface->DisplayMessage("This module has not been implemented yet");
						poInterface->CommitDisplay();*/
						poChoosenModule = new GameEdition;
						break;
					  case '4' :
					  case 'x' :
						bQuit = true;
						break;
					  default :
						break;
					}
				}

				if(!bQuit)
				{
					poChoosenModule->Run(poInterface);
					delete poChoosenModule;
					poChoosenModule = NULL;
				}
			}
			catch(exception & e)
			{
				poInterface->DisplayMessage(e.what());
				poInterface->CommitDisplay();
			}
		}

		Interface::FreeInstance();
	}
	catch(exception & e)
	{
		cout << "Uncatched exception : " << e.what() << endl;
	}
	catch(...)
	{
		cout << "Unknow uncatched exception" << endl;
	}

	return 0;
}