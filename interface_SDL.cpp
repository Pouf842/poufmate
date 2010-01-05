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

	if(!(mpoGame[SCREEN] = SDL_SetVideoMode(1000, 698, 32, /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF)))
		throw exception("SDL video mode initialisation failed");

	if(TTF_Init() == -1)
		throw exception("SDL ttf module could not be loaded");

	SDL_WM_SetCaption("PoufMate", NULL);
	mpoMessagesBG = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 698, 32, 0, 0, 0, 0);
	SDL_FillRect(mpoMessagesBG, NULL, SDL_MapRGB(mpoMessagesBG->format, 200, 200, 200));

	SDL_Rect position;
	position.x = 700;
	position.y = 0;

	SDL_BlitSurface(mpoMessagesBG, NULL, mpoGame[SCREEN], &position);

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
		SDL_FreeSurface(mpoGame[i]);

	for(unsigned int i = 0; i < 6; ++i)
	{
		SDL_FreeSurface(mpoPieces[Piece::WHITE][i]);
		SDL_FreeSurface(mpoPieces[Piece::BLACK][i]);
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
			strEntry = "x";
			break;
		  case SDL_MOUSEBUTTONDOWN :
			strEntry += '0' + event.button.y / CASE_WIDTH;
			strEntry += '0' + event.button.x / CASE_HEIGHT;
			if(event.button.button == SDL_BUTTON_RIGHT)
				strEntry += "?";
			break;
		  case SDL_KEYUP  :
			switch(event.key.keysym.sym)
			{
			  case SDLK_x :
				strEntry = "x";
				break;
			  case SDLK_c :
			    strEntry = "c";
				break;
			}
			break;
		  case SDL_MOUSEBUTTONUP :
/*			if(event.button.button == SDL_BUTTON_RIGHT)
			{
				strEntry += '0' + event.button.y / CASE_WIDTH;
				strEntry += '0' + event.button.x / CASE_HEIGHT;
			}*/
			return "";
			break;
		  default :
			strEntry = "";
			break;
		}
	}

	return strEntry;
}

void InterfaceSDL::DisplayPossibilities(vector<Position> oPossibilities)
{
	SDL_Rect position;
	unsigned int iIndex = 0;

	for(unsigned int i = 0; i < oPossibilities.size(); ++i)
	{
		position.y = (oPossibilities[i].mX) * CASE_HEIGHT;
		position.x = (oPossibilities[i].mY) * CASE_WIDTH;

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

char InterfaceSDL::cGetNewPieceType(Piece::Color eColor)
{
	SDL_Surface * poBackGround = SDL_CreateRGBSurface(SDL_HWSURFACE, 360, 90, 32, 0, 0, 0, 0);
	SDL_FillRect(poBackGround, NULL, SDL_MapRGB(poBackGround->format, 200, 200, 200));
	SDL_Event event;
	SDL_Rect position;

	position.x = 200;
	position.y = 300;

	SDL_BlitSurface(poBackGround, NULL, mpoGame[SCREEN], &position);

	position.x += 5;
	position.y += 5;
	SDL_BlitSurface(mpoPieces[eColor][Piece::QUEEN], NULL, mpoGame[SCREEN], &position);

	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::BISHOP], NULL, mpoGame[SCREEN], &position);
	
	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::KNIGHT], NULL, mpoGame[SCREEN], &position);
	
	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::ROOK], NULL, mpoGame[SCREEN], &position);

	SDL_Flip(mpoGame[SCREEN]);

	bool bOk = false;
	char cReturn = ' ';

	while(!bOk)
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_MOUSEBUTTONDOWN
		&& event.button.button == SDL_BUTTON_LEFT
		&& event.button.y > 300
		&& event.button.y < 400
		&& event.button.x > 200
		&& event.button.x < 560)
		{
				bOk = true;

				switch((event.button.x - 200) / 90)
				{
				  case 0 :
					cReturn = 'Q';
					bOk = true;
					break;
				  case 1 :
					cReturn = 'B';
					bOk = true;
					break;
				  case 2 :
					cReturn = 'N';
					bOk = true;
					break;
				  case 3 :
					cReturn = 'R';
					bOk = true;
					break;
				  default :
					break;
				}
		}
	}

	SDL_FreeSurface(poBackGround);
	return cReturn;
}

std::string InterfaceSDL::strGetEditionEntry()
{
	SDL_Rect position;

	position.x = 700;
	position.y = 0;

	SDL_Rect oBoardPiece;
	oBoardPiece.h = 6 * 87;
	oBoardPiece.x = 0;
	oBoardPiece.w = 2 * 87;
	oBoardPiece.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], &oBoardPiece, mpoGame[SCREEN], &position);

	oBoardPiece.h = 87;
	oBoardPiece.w = 87;
	oBoardPiece.x = 87;
	oBoardPiece.y = 1;

	position.x = 743;
	position.y = 528;

	SDL_BlitSurface(mpoGame[BOARD], &oBoardPiece, mpoGame[SCREEN], &position);

	position.x = 700;
	position.y = 0;

	for(unsigned int i = 0; i < 6; ++i)
	{
		position.y = 87 * i + 5;
		SDL_BlitSurface(mpoPieces[Piece::WHITE][i], NULL, mpoGame[SCREEN], &position);
	}

	position.x = 792;
	for(unsigned int i = 0; i < 6; ++i)
	{
		position.y = 87 * i + 5;
		SDL_BlitSurface(mpoPieces[Piece::BLACK][i], NULL, mpoGame[SCREEN], &position);
	}

	SDL_Flip(mpoGame[SCREEN]);

	string strReturn = "";
	SDL_Event event;

	while(strReturn == "")
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_MOUSEBUTTONDOWN
		&& event.button.button == SDL_BUTTON_LEFT)
		{
			if(event.button.x > 879);
			else if(event.button.x < 700)
			{
				strReturn += '0' + event.button.y / CASE_WIDTH;
				strReturn += '0' + event.button.x / CASE_HEIGHT;
			}
			else
			{
				if(event.button.y <= 92)
					strReturn += 'P';
				else if(event.button.y <= 179)
					strReturn += 'R';
				else if(event.button.y <= 266)
					strReturn += 'N';
				else if(event.button.y <= 353)
					strReturn += 'B';
				else if(event.button.y <= 440)
					strReturn += 'Q';
				else if(event.button.y <= 527)
					strReturn += 'K';
				else if(event.button.y <= 614
					 && event.button.x >= 743
					 && event.button.x <= 830)
					 return "#";

				if(event.button.x > 787)
					strReturn[0] = tolower(strReturn[0]);
			}
		}
	}

	return strReturn;
}

char InterfaceSDL::cGetMenuEntry()
{
	return '3';
}

void InterfaceSDL::DisplayMenu(const Menu & oMenu)
{
}