#include "Interface_SDL.h"

#include <iostream>
#include <string>
using namespace std;

InterfaceSDL::InterfaceSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		throw exception("SDL initialisation failed");

	if(!(mpoScreen = SDL_SetVideoMode(698, 698, 32, /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF)))
		throw exception("SDL video mode initialisation failed");

	SDL_WM_SetCaption("PoufMate", NULL);

	mpoBoard = SDL_LoadBMP("Images/Echiquier.bmp");

	mpoSelection = SDL_LoadBMP("Images/Selection.bmp");
	SDL_SetColorKey(mpoSelection, SDL_SRCCOLORKEY, SDL_MapRGB(mpoSelection->format, 255, 0, 0));

	mpoChess = SDL_LoadBMP("Images/Echec.bmp");
	SDL_SetColorKey(mpoChess, SDL_SRCCOLORKEY, SDL_MapRGB(mpoChess->format, 255, 0, 0));

	mpoPossibleMove = SDL_LoadBMP("Images/Possible.bmp");
	SDL_SetColorKey(mpoPossibleMove, SDL_SRCCOLORKEY, SDL_MapRGB(mpoPossibleMove->format, 255, 0, 0));

	mpoWhitePawn = SDL_LoadBMP("Images/Pion blanc.bmp");
	mpoWhiteTower = SDL_LoadBMP("Images/Tour blanche.bmp");
	mpoWhiteKnight = SDL_LoadBMP("Images/Cavalier blanc.bmp");
	mpoWhiteBishop = SDL_LoadBMP("Images/Fou blanc.bmp");
	mpoWhiteQueen = SDL_LoadBMP("Images/Reine blanche.bmp");
	mpoWhiteKing = SDL_LoadBMP("Images/Roi blanc.bmp");

	mpoBlackPawn = SDL_LoadBMP("Images/Pion noir.bmp");
	mpoBlackTower = SDL_LoadBMP("Images/Tour noire.bmp");
	mpoBlackKnight = SDL_LoadBMP("Images/Cavalier noir.bmp");
	mpoBlackBishop = SDL_LoadBMP("Images/Fou noir.bmp");
	mpoBlackQueen = SDL_LoadBMP("Images/Reine noire.bmp");
	mpoBlackKing = SDL_LoadBMP("Images/Roi noir.bmp");
}

InterfaceSDL::~InterfaceSDL()
{
	SDL_free(mpoBoard);
	SDL_free(mpoSelection);
	SDL_free(mpoChess);
	SDL_free(mpoPossibleMove);

	SDL_Quit();
}

void InterfaceSDL::DisplayBoard(const Board &) const
{
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(mpoBoard, NULL, mpoScreen, &position);
	SDL_Flip(mpoScreen);
}

void InterfaceSDL::DisplayMessage(std::string strMessage) const
{
}

std::string InterfaceSDL::strGetEntry() const
{
	string strEntry = "";

	SDL_Event event;
    SDL_WaitEvent(&event);

    switch(event.type)
    {
      case SDL_QUIT :
		strEntry = "q";
		break;
	  case SDL_MOUSEBUTTONUP :
		//strEntry = 
		break;
	  case SDL_KEYUP  :
		  switch(event.key.keysym.sym)
		  {
			case SDLK_q :
			strEntry = "q";
		  }
    }

	return strEntry;
}

void InterfaceSDL::DisplayPossibilities(std::string strPossibilities) const
{
	//SDL_BlitSurface(mpoPossibleMove, NULL, mpoScreen, );
	SDL_Flip(mpoScreen);
}

void InterfaceSDL::DisplayInCheck(unsigned int X, unsigned int Y) const
{
	SDL_Rect position;
	position.x = X * 87;
	position.y = Y * 87;

	SDL_BlitSurface(mpoChess, NULL, mpoScreen, &position);
	SDL_Flip(mpoScreen);
}

void InterfaceSDL::DisplaySelection(unsigned int X, unsigned int Y) const
{
	SDL_Rect position;
	position.x = X * 87;
	position.y = Y * 87;

	SDL_BlitSurface(mpoSelection, NULL, mpoScreen, &position);
	SDL_Flip(mpoScreen);
}

Interface * InterfaceSDL::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceSDL;

	return mpoInstance;
}
