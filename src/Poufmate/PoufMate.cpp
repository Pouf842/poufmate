#include "PoufMate.h"
#include "windows.h"
#include "interface.h"
#include "game.h"

#include <iostream>

using namespace std;

PoufMate::PoufMate()
{
    try
    {
        vector<string> strInterfaceDLLs;
        typedef Interface * (*pfpoGetInterface)(Controller *);

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

        mpoInterface = poGetIInstance(this);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

PoufMate::~PoufMate()
{
}

void PoufMate::Start()
{
    try
    {
        vector<string> oMenu;
        oMenu.push_back("1.One player game (human VS computer)");
        oMenu.push_back("2.Two player game (human VS human)");
        oMenu.push_back("3.Edition mode");
        oMenu.push_back("4.Two player lan game");
        oMenu.push_back("5.Change interface");
        oMenu.push_back("6.Quit");

        mpoInterface->SetMenuState(&oMenu);
        mpoInterface->Run();
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        cout << "Uncatched exception : " << e.what() << endl;
        getchar();
    }
}

void PoufMate::SetMenuChoice(unsigned short sChoiceIndex)
{
    try
    {
        Game * poGame;
        //GameEdition * poGameEdition;
        switch(sChoiceIndex)
        {
		    case 1:
		    case 2:
                poGame = new Game(this);
                mpoInterface->SetController(poGame);
                mpoInterface->SetGameState(poGame->oGetBoard());
			    break;
		    case 3:
			    //mpoCurrentModule = new GameEdition;
			    break;
		    case 6:
                mpoInterface->Quit();
			    break;
        }
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void PoufMate::Quit()
{
    try
    {
        mpoInterface->Quit();
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}
