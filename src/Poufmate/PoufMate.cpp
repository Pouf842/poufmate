#include "PoufMate.h"
#include "windows.h"
#include "interface.h"
#include "Modules/game.h"

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

        mpoCurrentInterface = poGetIInstance(this);
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

        mpoCurrentInterface->SetMenuState(&oMenu);
        mpoCurrentInterface->Run();
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
        if(mpoCurrentModule)
        {
            delete mpoCurrentModule;
            mpoCurrentModule = NULL;
        }

        switch(sChoiceIndex)
        {
			case 1:
			case 2:
				mpoCurrentModule = new Game();
				mpoCurrentInterface->SetGameState(mpoCurrentModule->oGetBoard());
				break;
			case 3:
				//mpoCurrentModule = new GameEdition;
				break;
			case 6:
				mpoCurrentInterface->Quit();
				break;
        }
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void PoufMate::GrabPiece(const Position & oPiecePosition)
{
    try
    {
        mpoCurrentModule->GrabPiece(oPiecePosition);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void PoufMate::DropPiece(const Position & oDropPosition)
{
    try
    {
        mpoCurrentModule->DropPiece(oDropPosition);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void PoufMate::SelectNewPiece(Piece::PIECE_COLOR eColor, Piece::PIECE_TYPE eType)
{
    try
    {
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void PoufMate::Escape()
{
    try
    {
        delete mpoCurrentModule;
		mpoCurrentModule = NULL;
        mpoCurrentInterface->SetMenuState();
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

vector<Position> PoufMate::oGetPossibleMoves(const Position & oPiecePosition) const
{
    return vector<Position>();
}

Piece::PIECE_TYPE PoufMate::eGetNewPieceType()
{
    try
    {
        mpoCurrentInterface->eGetPromotionNewPiece();
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}