#include <vector>
#include <string>
#include <exception>
#include "windows.h"
#include "Interface\interface.h"
#include "Modules\module.h"

#include "Modules/one_player_game.h"
#include "Modules/two_players_game.h"
#include "Modules/game_edition.h"
//#include "Modules\include_modules.h"

using namespace std;

typedef Interface * (*pfpoGetInterface)();

vector<string> strInterfaceDLLs;

int main(int argc, char * argv[])
{
	try
	{
		strInterfaceDLLs.push_back("InterfaceIrrlicht.dll");
		strInterfaceDLLs.push_back("InterfaceConsole.dll");
		strInterfaceDLLs.push_back("InterfaceSDL.dll");
		vector<string>::iterator iCurrentIDLL = strInterfaceDLLs.begin();

		HINSTANCE hIConsoleDLLHandle = LoadLibrary(iCurrentIDLL->c_str());

        DWORD error = GetLastError();

		if(error)
			throw exception("Erreur : Impossible de charger l'interface console InterfaceConsole.dll");

		pfpoGetInterface poGetIInstance = (pfpoGetInterface) GetProcAddress(hIConsoleDLLHandle, "poGetInterface");

        error = GetLastError();

		if(error)
			throw exception("Erreur : La fonction "GET_INTERFACE_FUNCTION" n'a pas été trouvée");

        Interface * poInterface = poGetIInstance();

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
					  case 1 :
						poChoosenModule = new OnePlayerGame;
						break;
					  case 2 :
						poChoosenModule = new TwoPlayersGame;
						break;
					  case 3 :
						poChoosenModule = new GameEdition;
						break;
					  /*case 4 :
						poChoosenModule = new LanGame;
						break;*/
                      case 5 :
                        delete poInterface;
                        FreeLibrary(hIConsoleDLLHandle);

                        hIConsoleDLLHandle = NULL;

						while(!hIConsoleDLLHandle)
						{
							++iCurrentIDLL;

							if(iCurrentIDLL == strInterfaceDLLs.end())
								iCurrentIDLL = strInterfaceDLLs.begin();

							hIConsoleDLLHandle = LoadLibrary(iCurrentIDLL->c_str());
						}

                        poGetIInstance = (pfpoGetInterface) GetProcAddress(hIConsoleDLLHandle, "poGetInterface");
                        poInterface = poGetIInstance();

                        break;
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

        FreeLibrary(hIConsoleDLLHandle);
	}
	catch(exception & e)
	{
		cout << __FILE__ << ":" << __LINE__ << endl;
		cout << "Uncatched exception : " << e.what() << endl;
        getchar();
	}
	catch(...)
	{
		cout << __FILE__ << ":" << __LINE__ << endl;
		cout << "Unknow uncatched exception" << endl;
        getchar();
	}

	return 0;
}