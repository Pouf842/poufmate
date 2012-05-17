#include "include_modules.h"
#include <vector>
#include <string>

#include "interface.h"
#include "windows.h"
using namespace std;

typedef Interface * (*pfpoGetInterface)(struct Interface::stExportedMethods);

int main(int argc, char * argv[])
{
	try
	{
        HINSTANCE hInterfaceDLLHandle = LoadLibrary("InterfaceSDL.dll");
        bool bInterfaceSDL = true;

        pfpoGetInterface poGetInterfaceInstance = (pfpoGetInterface) GetProcAddress(hInterfaceDLLHandle, "poGetInstance");

        DWORD error = GetLastError();

        Interface::stExportedMethods exportedMethods;

        exportedMethods.pBoardEGetSquareType = &Board::eGetSquareType;
        exportedMethods.pBoardEGetSquareColor = &Board::eGetSquareColor;
        exportedMethods.pBoardBIsSquareEmpty = &Board::bIsSquareEmpty;

        exportedMethods.pGameOGetBoard = &Game::oGetBoard;
        exportedMethods.pGameBIsPlayerInCheck = &Game::bIsPlayerInCheck;
        exportedMethods.pGameOGetKingPosition = &Game::oGetKingPosition;
        exportedMethods.pGameEGetCurrentPlayer = &Game::eGetCurrentPlayer;

        exportedMethods.pGameEditionOGetBoard = &GameEdition::oGetBoard;

        Interface * poInterface = poGetInterfaceInstance(exportedMethods);

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
                        poInterface = poGetInterfaceInstance(exportedMethods);

                        bInterfaceSDL = !bInterfaceSDL;
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
					string strCmdReturn = "";

					while((strCmdReturn = poChoosenModule->Run()) == "r")
						poChoosenModule->Initialize();

					delete poChoosenModule;
					poChoosenModule = NULL;

					if(strCmdReturn == "q")
						bQuit = true;
				}
			}
			catch(exception & e)
			{
				poInterface->AddMessage(e.what());
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