#include "Interface_SDL.h"

#include <iostream>
#include <string>
#define SQUARE_WIDTH 87
#define SQUARE_HEIGHT 87
#define SIDE_BOARD_WIDTH 480
#define FONT_HEIGHT 69

using namespace std;

InterfaceSDL::InterfaceSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		throw exception("SDL initialisation failed");

	if(!(mpoGame[SCREEN] = SDL_SetVideoMode(8 * SQUARE_WIDTH + SIDE_BOARD_WIDTH, 8 * SQUARE_HEIGHT, 32, /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF)))
		throw exception("SDL video mode initialisation failed");

	SDL_FillRect(mpoGame[SCREEN], NULL, SDL_MapRGB(mpoGame[SCREEN]->format, 200, 200, 200));

	if(TTF_Init() == -1)
		throw exception("SDL ttf module could not be loaded");

	mpoMenuFont = TTF_OpenFont("angelina.ttf", 65);
	mpoMessagesFont = TTF_OpenFont("angelina.ttf", 30);

	if(!mpoMenuFont || !mpoMessagesFont)
		throw exception("Font couldn't be loaded");

	SDL_WM_SetCaption("PoufMate", NULL);
	mpoGame[MESSAGEBOARD] = SDL_CreateRGBSurface(SDL_HWSURFACE, SIDE_BOARD_WIDTH, 8 * SQUARE_HEIGHT, 32, 0, 0, 0, 0);

	SDL_FillRect(mpoGame[MESSAGEBOARD], NULL, SDL_MapRGB(mpoGame[MESSAGEBOARD]->format, 200, 200, 200));

	SDL_Rect position;
	position.x = 8 * SQUARE_WIDTH;
	position.y = 0;

	SDL_BlitSurface(mpoGame[MESSAGEBOARD], NULL, mpoGame[SCREEN], &position);

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

	for(unsigned int i = 0; i < 6; ++i)	
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

	TTF_CloseFont(mpoMenuFont);
	TTF_CloseFont(mpoMessagesFont);

	TTF_Quit();
	SDL_Quit();
}

void InterfaceSDL::DisplayBoard(const Board & oBoard)
{
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &position);

	position.x = 8 * SQUARE_WIDTH;
	SDL_BlitSurface(mpoGame[MESSAGEBOARD], NULL, mpoGame[SCREEN], &position);

	position.x = 8 * SQUARE_HEIGHT + 5;
	position.y = 0;

	queue<SDL_Surface *> oTemp = moMessages;

	for(unsigned int i = 0; i < moMessages.size(); ++i)
	{
		SDL_Surface * poTemp = oTemp.front();
		SDL_BlitSurface(poTemp, NULL, mpoGame[SCREEN], &position);
		position.y += moMessages.front()->h;

		oTemp.pop();
	}

	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			SDL_Rect position;
			position.x = i * SQUARE_WIDTH;
			position.y = j * SQUARE_HEIGHT;

			Position oPos(j, i);

			if(!oBoard.bIsSquareEmpty(oPos))
			{
				SDL_BlitSurface(mpoPieces[oBoard.eGetSquareColor(oPos)][oBoard.poGetPiece(oPos)->eGetType()], NULL, mpoGame[SCREEN], &position);
			}
		}
}

void InterfaceSDL::DisplayGameOver(std::string strMessage)
{
	SDL_Color oBlack = {0, 0, 0};
	SDL_Color oBackGround = {255, 255, 255};
	
	SDL_Surface * poMessage = TTF_RenderText_Shaded(mpoMenuFont, strMessage.c_str(), oBlack, oBackGround);

	SDL_Rect position;

	position.x = 8 * SQUARE_WIDTH / 2 - poMessage->w / 2;
	position.y = 8 * SQUARE_WIDTH / 2 - poMessage->h / 2;;

	SDL_BlitSurface(poMessage, NULL, mpoGame[SCREEN], &position);
	SDL_Flip(mpoGame[SCREEN]);

	SDL_Event event;

	do
	{
		SDL_WaitEvent(&event);
	} while(event.type != SDL_KEYDOWN && event.type != SDL_MOUSEBUTTONDOWN);

	return;
}

void InterfaceSDL::DisplayMessage(std::string strMessage)
{
	SDL_Color oBlack = {0, 0, 0};

	moMessages.push(TTF_RenderText_Blended(mpoMessagesFont, strMessage.c_str(), oBlack));

	if(moMessages.size() > 10)
	{
		SDL_FreeSurface(moMessages.front());
		moMessages.pop();
	}
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
			strEntry += '0' + event.button.y / SQUARE_WIDTH;
			strEntry += '0' + event.button.x / SQUARE_HEIGHT;
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
				strEntry += '0' + event.button.y / SQUARE_WIDTH;
				strEntry += '0' + event.button.x / SQUARE_HEIGHT;
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
		position.y = (oPossibilities[i].mX) * SQUARE_HEIGHT;
		position.x = (oPossibilities[i].mY) * SQUARE_WIDTH;

		SDL_BlitSurface(mpoGame[POSSIBLE], NULL, mpoGame[SCREEN], &position);
	}
}

void InterfaceSDL::DisplayInCheck(Position oPos)
{
	SDL_Rect position;
	position.y = oPos.mX * SQUARE_HEIGHT;
	position.x = oPos.mY * SQUARE_WIDTH;

	SDL_BlitSurface(mpoGame[CHESS], NULL, mpoGame[SCREEN], &position);
}

void InterfaceSDL::DisplaySelection(Position oPos)
{
	SDL_Rect position;
	position.x = oPos.mY * SQUARE_HEIGHT;
	position.y = oPos.mX * SQUARE_WIDTH;

	SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &position);
}

Interface * InterfaceSDL::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceSDL;

	return mpoInstance;
}

void InterfaceSDL::DisplayCurrentPlayer(Piece::Color eColor)
{
	SDL_Color oPlayerColor;
	string strPlayer = "";

	if(eColor == Piece::WHITE)
	{
		strPlayer = "Current player : White player";
		oPlayerColor.b = 255;
		oPlayerColor.g = 255;
		oPlayerColor.r = 255;
	}
	else
	{
		strPlayer = "Current Player : Black player";
		oPlayerColor.b = 0;
		oPlayerColor.g = 0;
		oPlayerColor.r = 0;
	}

	SDL_Surface * poCurrentPlayer = TTF_RenderText_Blended(mpoMessagesFont, strPlayer.c_str(), oPlayerColor);

	SDL_Rect position;

	position.x = 8 * SQUARE_WIDTH + ((SIDE_BOARD_WIDTH / 2) - (poCurrentPlayer->w / 2));
	position.y = 6 * SQUARE_HEIGHT;

	SDL_BlitSurface(poCurrentPlayer, NULL, mpoGame[SCREEN], &position);
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
				strReturn += '0' + event.button.y / SQUARE_WIDTH;
				strReturn += '0' + event.button.x / SQUARE_HEIGHT;
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
		else if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
			  case SDLK_x :
				return "x";
				break;
			  case SDLK_KP1 :
				return "1";
			  case SDLK_KP2 :
				return "2";
				break;
			}
		}
		else if(event.type == SDL_QUIT)
			return "x";
	}

	return strReturn;
}

int InterfaceSDL::iGetMenuEntry(const Menu & oMenu)
{
	SDL_Color oRed = {255, 0, 0};
	SDL_Color oYellow = {255, 255, 0};
	SDL_Rect position;

	int iStartPositionY = FONT_HEIGHT;
	int iEndPositionY = -1;

	int iStartPositionX = FONT_HEIGHT;
	int iEndPositionX = -1;

	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &position);

	position.x = FONT_HEIGHT;
	position.y = iStartPositionY;

	vector<SDL_Surface *> poOptions;

	for(unsigned int i = 0; i < oMenu.size(); ++i)
	{
		poOptions.push_back(TTF_RenderText_Blended(mpoMenuFont, (" " + oMenu[i]).c_str(), oRed));
		//SDL_SetColorKey(poOptions[i], SDL_SRCCOLORKEY, SDL_MapRGB(poOptions[i]->format, 255, 0, 0));
		//SDL_SetColorKey(mpoPieces[Piece::WHITE][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::WHITE][i]->format, 255, 0, 0));

		SDL_BlitSurface(poOptions[i], NULL, mpoGame[SCREEN], &position);

		position.y += 2 * FONT_HEIGHT;

		if(iStartPositionX + poOptions[i]->w > iEndPositionX)
			iEndPositionX = iStartPositionX + poOptions[i]->w;
	}
	
	iEndPositionY = position.y;

	SDL_Flip(mpoGame[SCREEN]);

	bool bOk = false;
	SDL_Event event;

	unsigned int iSelection = 0;

	while(!bOk)
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_MOUSEMOTION)
		{
			int iMouseX = event.motion.x;
			int iMouseY = event.motion.y;

			if(iMouseX >= iStartPositionX
			&& iMouseX <= iEndPositionX
			&& iMouseY >= iStartPositionY
			&& iMouseY <= iEndPositionY
			&& (((iMouseY - iStartPositionY) / FONT_HEIGHT) % 2) == 0)
			{
				position.y = iStartPositionY;

				unsigned int iNewSelection = ((iMouseY - iStartPositionY) / FONT_HEIGHT) / 2;

				if(iNewSelection != iSelection && iNewSelection < poOptions.size())
				{	
					SDL_Rect oBoardPosition;
					oBoardPosition.x = 0;
					oBoardPosition.y = 0;

					SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &oBoardPosition);
					oBoardPosition.x += 8 * SQUARE_HEIGHT;
					SDL_BlitSurface(mpoGame[MESSAGEBOARD], NULL, mpoGame[SCREEN], &oBoardPosition);

					SDL_FreeSurface(poOptions[iSelection]);
					poOptions[iSelection] = TTF_RenderText_Blended(mpoMenuFont, (" " + oMenu[iSelection]).c_str(), oRed);

					iSelection = iNewSelection;

					SDL_FreeSurface(poOptions[iSelection]);
					poOptions[iSelection] = TTF_RenderText_Shaded(mpoMenuFont, (" " + oMenu[iSelection]).c_str(), oRed, oYellow);
				
					for(unsigned int i = 0; i < poOptions.size(); ++i)
					{
						SDL_BlitSurface(poOptions[i], NULL, mpoGame[SCREEN], &position);

						position.y += 2 * FONT_HEIGHT;
					}
				}

				SDL_Flip(mpoGame[SCREEN]);
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN
		&& event.button.button == SDL_BUTTON_LEFT)
		{
			int iMouseX = event.button.x;
			int iMouseY = event.button.y;

			if(iMouseX >= iStartPositionX
			&& iMouseX <= iEndPositionX
			&& iMouseY >= iStartPositionY
			&& iMouseY <= iEndPositionY
			&& (((iMouseY - iStartPositionY) / FONT_HEIGHT) % 2) == 0)
				return ((iMouseY - iStartPositionY) / FONT_HEIGHT) / 2 + 1;
		}
		else if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
			  case SDLK_KP1 :
				return 1;
				break;
			  case SDLK_KP2 :
				return 2;
				break;
			  case SDLK_KP3 :
				return 3;
				break;
			  case SDLK_KP4 :
			  case SDLK_x :
				return 4;
				break;
			  default :
				break;
			}
		}
		else if(event.type == SDL_QUIT)
			return 4;
	}

	return 1;
}

char InterfaceSDL::cGetPlayerColorChoice()
{
	return 'W';
}