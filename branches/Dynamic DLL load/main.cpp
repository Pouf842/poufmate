#include "include_modules.h"
#include <vector>
#include <string>

#include "interface.h"
#include "windows.h"
using namespace std;

//typedef static Interface * (*poGetInterfaceInstance)(struct stExportedMethods);
typedef int (*poFunctionTypeTest)();

int main(int argc, char * argv[])
{
	try
	{
        HINSTANCE hInterfaceDLLHandle = LoadLibrary("InterfaceSDL.dll");

        poFunctionTypeTest poGetInterfaceInstance = (poFunctionTypeTest) GetProcAddress(hInterfaceDLLHandle, "poGetInstance");

        Interface::stExportedMethods exportedMethods;

        exportedMethods.pBoardEGetSquareType = &Board::eGetSquareType;
        exportedMethods.pBoardEGetSquareColor = &Board::eGetSquareColor;
        exportedMethods.pBoardBIsSquareEmpty = &Board::bIsSquareEmpty;

        exportedMethods.pGameOGetBoard = &Game::oGetBoard;
        exportedMethods.pGameBIsPlayerInCheck = &Game::bIsPlayerInCheck;
        exportedMethods.pGameOGetKingPosition = &Game::oGetKingPosition;
        exportedMethods.pGameEGetCurrentPlayer = &Game::eGetCurrentPlayer;

        exportedMethods.pGameEditionOGetBoard = &GameEdition::oGetBoard;

        Interface * poInterface;
        //Interface * poInterface = Interface::poGetInstance(exportedMethods);

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
					string strCmdReturn = "";

					while((strCmdReturn = poChoosenModule->Run()) == "r")
					{
						poChoosenModule->Initialize();
					}

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