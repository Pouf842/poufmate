#include "Interface_SDL.h"

#include <iostream>
#include <string>
#define CASE_WIDTH 87
#define CASE_HEIGHT 87

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
	mpoPieces[Piece::WHITE][Piece::ROOK] = SDL_LoadBMP("Images/Tour blanche.bmp");
	mpoPieces[Piece::WHITE][Piece::KNIGHT] = SDL_LoadBMP("Images/Cavalier blanc.bmp");
	mpoPieces[Piece::WHITE][Piece::BISHOP] = SDL_LoadBMP("Images/Fou blanc.bmp");
	mpoPieces[Piece::WHITE][Piece::QUEEN] = SDL_LoadBMP("Images/Reine blanche.bmp");
	mpoPieces[Piece::WHITE][Piece::KING] = SDL_LoadBMP("Images/Roi blanc.bmp");

	mpoPieces[Piece::BLACK][Piece::PAWN] = SDL_LoadBMP("Images/Pion noir.bmp");
	mpoPieces[Piece::BLACK][Piece::ROOK] = SDL_LoadBMP("Images/Tour noire.bmp");
	mpoPieces[Piece::BLACK][Piece::KNIGHT] = SDL_LoadBMP("Images/Cavalier noir.bmp");
	mpoPieces[Piece::BLACK][Piece::BISHOP] = SDL_LoadBMP("Images/Fou noir.bmp");
	mpoPieces[Piece::BLACK][Piece::QUEEN] = SDL_LoadBMP("Images/Reine noire.bmp");
	mpoPieces[Piece::BLACK][Piece::KING] = SDL_LoadBMP("Images/Roi noir.bmp");

	for(unsigned int i = 0; i < 5; ++i)	
		SDL_SetColorKey(mpoGame[i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoGame[i]->format, 255, 0, 0));

	SDL_SetColorKey(mpoGame[CHESS], SDL_SRCCOLORKEY, SDL_MapRGB(mpoGame[CHESS]->format, 0, 255, 0));

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

void InterfaceSDL::DisplayBoard(const Board & oBoard)
{
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &position);

	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			SDL_Rect position;
			position.x = i * CASE_WIDTH;
			position.y = j * CASE_HEIGHT;

			Position oPos(j, i);

			if(!oBoard.bIsSquareEmpty(oPos))
			{
				SDL_BlitSurface(mpoPieces[oBoard.eGetSquareColor(oPos)][oBoard.poGetPiece(oPos)->eGetType()], NULL, mpoGame[SCREEN], &position);
			}
		}
}

void InterfaceSDL::DisplayMessage(std::string strMessage)
{
}

std::string InterfaceSDL::strGetEntry()
{
	string strEntry = "";

	SDL_Event event;

	while(strEntry == "")
	{
		SDL_WaitEvent(&event);

		switch(event.type)
		{
		  case SDL_QUIT :
			return "x";
			break;
		  case SDL_MOUSEBUTTONDOWN :
			strEntry += '0' + event.button.y / CASE_WIDTH;
			strEntry += '0' + event.button.x / CASE_HEIGHT;
			if(event.button.button == SDL_BUTTON_RIGHT)
				strEntry += "?";

			return strEntry;
			break;
		  case SDL_KEYUP  :
			switch(event.key.keysym.sym)
			{
			  case SDLK_x :
				return "x";
				break;
			  case SDLK_c :
			    return "c";
				break;
			}
		  case SDL_MOUSEBUTTONUP :
			if(event.button.button == SDL_BUTTON_RIGHT)
				return "";

		  default :
			break;
		}
	}
}

void InterfaceSDL::DisplayPossibilities(std::string strPossibilities)
{
	SDL_Rect position;
	unsigned int iIndex = 0;

	while((iIndex = strPossibilities.find(';', iIndex + 1)) != string::npos)
	{
		position.y = (strPossibilities[iIndex - 2] - '0') * CASE_HEIGHT;
		position.x = (strPossibilities[iIndex - 1] - '0') * CASE_WIDTH;

		SDL_BlitSurface(mpoGame[POSSIBLE], NULL, mpoGame[SCREEN], &position);
	}
}

void InterfaceSDL::DisplayInCheck(Position oPos)
{
	SDL_Rect position;
	position.y = oPos.mX * CASE_HEIGHT;
	position.x = oPos.mY * CASE_WIDTH;

	SDL_BlitSurface(mpoGame[CHESS], NULL, mpoGame[SCREEN], &position);
}

void InterfaceSDL::DisplaySelection(Position oPos)
{
	SDL_Rect position;
	position.x = oPos.mY * CASE_HEIGHT;
	position.y = oPos.mX * CASE_WIDTH;

	SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &position);
}

Interface * InterfaceSDL::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceSDL;

	return mpoInstance;
}

void InterfaceSDL::DisplayCurrentPlayer(Piece::Color)
{
}

void InterfaceSDL::CommitDisplay()
{
	SDL_Flip(mpoGame[SCREEN]);
}