#include <vector>
#include <string>
#include <exception>
#include "windows.h"
#include "Interface\interface.h"
#include "Modules\module.h"

#include "Modules\two_players_game.h"
//#include "Modules\include_modules.h"

using namespace std;

typedef Interface * (*pfpoGetInterface)();

int main(int argc, char * argv[])
{
	try
	{
        HINSTANCE hInterfaceDLLHandle = LoadLibrary("InterfaceConsole.dll");

        DWORD error = GetLastError();

		if(error)
			throw exception("Erreur : Impossible de charger l'interface console InterfaceConsole.dll");

		pfpoGetInterface poGetInterfaceInstance = (pfpoGetInterface) GetProcAddress(hInterfaceDLLHandle, "poGetInterface");

        error = GetLastError();

		if(error)
			throw exception("Erreur : La fonction "GET_INTERFACE_FUNCTION" n'a pas été trouvée");
        bool bInterfaceSDL = false;

        Interface * poInterface = poGetInterfaceInstance();

		vector<string> oMenu;
		oMenu.push_back("1.One player game (human VS computer)");
		oMenu.push_back("2.Two player game (human VS human)");
		oMenu.push_back("3.Edition mode");
		oMenu.push_back("4.Two player lan game");
        oMenu.push_back("5.Change interface");
		oMenu.push_back("6.Quit");

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
					  /*case 1 :
						poChoosenModule = new OnePlayerGame;
						break;*/
					  case 2 :
						poChoosenModule = new TwoPlayersGame;
						break;
					  /*case 3 :
						poChoosenModule = new GameEdition;
						break;
					  case 4 :
						poChoosenModule = new LanGame;
						break;
                      case 5 :
                        delete poInterface;
                        FreeLibrary(hInterfaceDLLHandle);

                        if(bInterfaceSDL)
                            hInterfaceDLLHandle = LoadLibrary("InterfaceConsole.dll");
                        else
                            hInterfaceDLLHandle = LoadLibrary("InterfaceSDL.dll");

                        poGetInterfaceInstance = (pfpoGetInterface) GetProcAddress(hInterfaceDLLHandle, "poGetInstance");
                        poInterface = poGetInterfaceInstance();

                        bInterfaceSDL = !bInterfaceSDL;
                        break;*/
					  case 6 :
						bQuit = true;
						break;
					  default :
						break;
					}
				}

				if(!bQuit && poChoosenModule)
				{
					poChoosenModule->SetInterface(poInterface);
					poInterface->setModule(poChoosenModule);
					Entry::ENTRY_COMMAND eCmdReturn = Entry::EC_RESET_GAME;

					while((eCmdReturn = poChoosenModule->Run()) == Entry::EC_RESET_GAME)
						poChoosenModule->Initialize();

					delete poChoosenModule;
					poChoosenModule = NULL;

					if(eCmdReturn == Entry::EC_QUIT_GAME)
						bQuit = true;
				}
			}
			catch(exception & e)
			{
				poInterface->DisplayMessage(e.what());
			}
		}

        delete poInterface;

        FreeLibrary(hInterfaceDLLHandle);
	}
	catch(exception & e)
	{
		cout << "Uncatched exception : " << e.what() << endl;
        getchar();
	}
	catch(...)
	{
		cout << "Unknow uncatched exception" << endl;
	}

	return 0;
}