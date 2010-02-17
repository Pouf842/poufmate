#include "include_modules.h"
#include <vector>
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

		vector<string> oMenu;
		oMenu.push_back("1.One player game (human VS computer)");
		oMenu.push_back("2.Two player game (human VS human)");
		oMenu.push_back("3.Edition mode");
		oMenu.push_back("4.Two player lan game");
		oMenu.push_back("5.Quit");

		Module * poChoosenModule = 0;	// Create a new game
		bool bQuit = false;
		int iMenuEntry;

		while(!bQuit)
		{
			try
			{
				while(!poChoosenModule && !bQuit)
				{
					iMenuEntry = poInterface->iGetMenuEntry(oMenu);

					switch(iMenuEntry)
					{
					  case 1 :
						poChoosenModule = new OnePlayerGame;
						break;
					  case 2 :
						poChoosenModule = new TwoPlayersGame;
						break;
					  case 3 :
						poChoosenModule = new GameEdition;
						break;
					  case 4 :
						poChoosenModule = new LanGame;
						break;
					  case 5 :
						bQuit = true;
						break;
					  default :
						break;
					}
				}

				if(!bQuit)
				{
					poChoosenModule->SetInterface(poInterface);
					poChoosenModule->Run();
					delete poChoosenModule;
					poChoosenModule = NULL;
				}
			}
			catch(exception & e)
			{
				poInterface->AddMessage(e.what());
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