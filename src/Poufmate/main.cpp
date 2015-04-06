#include <iostream>
#include "Poufmate.h"

using namespace std;

int main(int arg, char * argv[])
{
    try
    {
        PoufMate oController;
        oController.Start();
    }
    catch(...)
    {
    	cout << __FUNCTION__ << ":" << __LINE__ << endl;
    	cout << "Unknow uncatched exception" << endl;
        getchar();
    }

    return 0;
}

//					iMenuEntry = poInterface->iGetMenuEntry(oMenu);
//
//					switch(iMenuEntry)
//					{
//					  case 1 :
//						poChoosenModule = new OnePlayerGame;
//						break;
//					  case 2 :
//						poChoosenModule = new TwoPlayersGame;
//						break;
//					  case 3 :
//						poChoosenModule = new GameEdition;
//						break;
//					  /*case 4 :
//						poChoosenModule = new LanGame;
//						break;*/


//                      case 5 :
//                        delete poInterface;
//                        FreeLibrary(hIConsoleDLLHandle);
//
//                        hIConsoleDLLHandle = NULL;
//
//						while(!hIConsoleDLLHandle)
//						{
//							++iCurrentIDLL;
//
//							if(iCurrentIDLL == strInterfaceDLLs.end())
//								iCurrentIDLL = strInterfaceDLLs.begin();
//
//							hIConsoleDLLHandle = LoadLibrary(iCurrentIDLL->c_str());
//						}
//
//                        poGetIInstance = (pfpoGetInterface) GetProcAddress(hIConsoleDLLHandle, "poGetInterface");
//                        poInterface = poGetIInstance();
//
//                    


//					poChoosenModule->SetInterface(poInterface);
//					poInterface->setModule(poChoosenModule);
//					Entry::ENTRY_COMMAND eCmdReturn = Entry::EC_RESET_GAME;
//
//					while((eCmdReturn = poChoosenModule->Run()) == Entry::EC_RESET_GAME)
//						poChoosenModule->Initialize();
//
//					delete poChoosenModule;
//					poChoosenModule = NULL;
//
//					if(eCmdReturn == Entry::EC_QUIT_GAME)
//						bQuit = true;
//				}
//			}
//			catch(exception & e)
//			{
//				poInterface->DisplayMessage(e.what());
//			}
//		}
//
//        delete poInterface;
//
//        FreeLibrary(hIConsoleDLLHandle);
//	}
//	catch(exception & e)
//	{
//		cout << __FUNCTION__ << ":" << __LINE__ << endl;
//		cout << "Uncatched exception : " << e.what() << endl;
//        getchar();
//	}
//
//	return 0;
//}