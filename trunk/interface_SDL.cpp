#include "Interface_SDL.h"

#include <iostream>
#include <string>
using namespace std;

InterfaceSDL::InterfaceSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		throw exception("SDL initialisation failed");

	if(!(mpoGame[SCREEN] = SDL_SetVideoMode(698, 698, 32, /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF)))
		throw exception("SDL video mode initialisation failed");

	SDL_WM_SetCaption("PoufMate", NULL);

	mpoGame[BOARD] = SDL_LoadBMP("Images/Echiquier.bmp");

	mpoGame[SELECTION] = SDL_LoadBMP("Images/Selection.bmp");
	mpoGame[CHESS] = SDL_LoadBMP("Images/Echec.bmp");
	mpoGame[POSSIBLE] = SDL_LoadBMP("Images/Possible.bmp");

	mpoPieces[Piece::WHITE][Piece::PAWN] = SDL_LoadBMP("Images/Pion blanc.bmp");
	mpoPieces[Piece::WHITE][Piece::TOWER] = SDL_LoadBMP("Images/Tour blanche.bmp");
	mpoPieces[Piece::WHITE][Piece::KNIGHT] = SDL_LoadBMP("Images/Cavalier blanc.bmp");
	mpoPieces[Piece::WHITE][Piece::BISHOP] = SDL_LoadBMP("Images/Fou blanc.bmp");
	mpoPieces[Piece::WHITE][Piece::QUEEN] = SDL_LoadBMP("Images/Reine blanche.bmp");
	mpoPieces[Piece::WHITE][Piece::KING] = SDL_LoadBMP("Images/Roi blanc.bmp");

	mpoPieces[Piece::BLACK][Piece::PAWN] = SDL_LoadBMP("Images/Pion noir.bmp");
	mpoPieces[Piece::BLACK][Piece::TOWER] = SDL_LoadBMP("Images/Tour noire.bmp");
	mpoPieces[Piece::BLACK][Piece::KNIGHT] = SDL_LoadBMP("Images/Cavalier noir.bmp");
	mpoPieces[Piece::BLACK][Piece::BISHOP] = SDL_LoadBMP("Images/Fou noir.bmp");
	mpoPieces[Piece::BLACK][Piece::QUEEN] = SDL_LoadBMP("Images/Reine noire.bmp");
	mpoPieces[Piece::BLACK][Piece::KING] = SDL_LoadBMP("Images/Roi noir.bmp");

	for(unsigned int i = 0; i < 5; ++i)	
		SDL_SetColorKey(mpoGame[i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoGame[i]->format, 255, 0, 0));

	for(unsigned int i = 0; i < 6; ++i)
	{
		SDL_SetColorKey(mpoPieces[Piece::WHITE][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::WHITE][i]->format, 255, 0, 0));
		SDL_SetColorKey(mpoPieces[Piece::BLACK][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::BLACK][i]->format, 255, 0, 0));
	}
}

InterfaceSDL::~InterfaceSDL()
{
	for(unsigned int i = 0; i < 5; ++i)
		SDL_free(mpoGame[i]);

	for(unsigned int i = 0; i < 6; ++i)
	{
		SDL_free(mpoPieces[Piece::WHITE][i]);
		SDL_free(mpoPieces[Piece::BLACK][i]);
	}

	SDL_Quit();
}

void InterfaceSDL::DisplayBoard(const Board & oBoard) const
{
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &position);

	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			SDL_Rect position;
			position.x = i * 87;
			position.y = j * 87;

			Coordinates oCoords(j, i);

			if(!oBoard.bIsSquareEmpty(oCoords))
			{
				SDL_BlitSurface(mpoPieces[oBoard.eGetSquareColor(oCoords)][oBoard.poGetPiece(oCoords)->eGetType()], NULL, mpoGame[SCREEN], &position);
			}
		}

	SDL_Flip(mpoGame[SCREEN]);
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
	SDL_Flip(mpoGame[SCREEN]);
}

void InterfaceSDL::DisplayInCheck(Coordinates oCoords) const
{
	SDL_Rect position;
	position.x = oCoords.mX * 87;
	position.y = oCoords.mY * 87;

	SDL_BlitSurface(mpoGame[CHESS], NULL, mpoGame[SCREEN], &position);
	SDL_Flip(mpoGame[SCREEN]);
}

void InterfaceSDL::DisplaySelection(Coordinates oCoords) const
{
	SDL_Rect position;
	position.x = oCoords.mX * 87;
	position.y = oCoords.mY * 87;

	SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &position);
	SDL_Flip(mpoGame[SCREEN]);
}

Interface * InterfaceSDL::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceSDL;

	return mpoInstance;
}

void InterfaceSDL::DisplayCurrentPlayer(Piece::Color) const
{
}