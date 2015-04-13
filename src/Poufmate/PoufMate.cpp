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
        mpoGame = new Game(mpoInterface, this);

        moMainMenu.push_back("1.One player game (human VS computer)");
        moMainMenu.push_back("2.Two player game (human VS human)");
        moMainMenu.push_back("3.Edition mode");
        moMainMenu.push_back("4.Two player lan game");
        moMainMenu.push_back("5.Change interface");
        moMainMenu.push_back("6.Quit");
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
        mpoInterface->SetMenuState(&moMainMenu);
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
        //GameEdition * poGameEdition;
        switch(sChoiceIndex)
        {
		    case 1:
		    case 2:
                mpoGame->Initialize();
                mpoInterface->SetController(mpoGame);
                mpoInterface->SetGameState(mpoGame->oGetBoard());
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

void PoufMate::Back()
{
    mpoInterface->SetController(this);
    mpoInterface->SetMenuState(&moMainMenu);
}