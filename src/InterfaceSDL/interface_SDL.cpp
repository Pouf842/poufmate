#include "interface_SDL.h"

#include <iostream>
#include <string>
#define SQUARE_WIDTH 87
#define SQUARE_HEIGHT 87
#define SIDE_BOARD_WIDTH 480
#define FONT_HEIGHT 69
#define WINDOW_WIDTH (8 * SQUARE_WIDTH + SIDE_BOARD_WIDTH)
#define WINDOW_HEIGHT (8 * SQUARE_HEIGHT)
#define BACKGROUNDCOLOR 200, 200, 200

using namespace std;

extern "C" __declspec(dllexport) Interface * poGetInstance(struct Interface::stExportedMethods exportedMethods)
{
    Interface * poInterface = new InterfaceSDL(exportedMethods);

    return poInterface;
}

InterfaceSDL::InterfaceSDL(struct stExportedMethods exportedMethods)
{
	try
	{
		mExportedMethods = exportedMethods;

		if(SDL_Init(SDL_INIT_VIDEO) == -1)
			throw exception("SDL initialisation failed");

		if(!(mpoGame[SCREEN] = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF)))
			throw exception("SDL video mode initialisation failed");

		SDL_FillRect(mpoGame[SCREEN], NULL, SDL_MapRGB(mpoGame[SCREEN]->format, 200, 200, 200));

		if(TTF_Init() == -1)
			throw exception("SDL ttf module could not be loaded");

		mpoMenuFont = TTF_OpenFont("angelina.ttf", 65);
		mpoMessagesFont = TTF_OpenFont("angelina.ttf", 20);

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

		mpoPieces[Piece::PC_WHITE][Piece::PT_PAWN] = SDL_LoadBMP("Images/Pion blanc.bmp");
		mpoPieces[Piece::PC_WHITE][Piece::PT_ROOK] = SDL_LoadBMP("Images/Tour blanche.bmp");
		mpoPieces[Piece::PC_WHITE][Piece::PT_KNIGHT] = SDL_LoadBMP("Images/Cavalier blanc.bmp");
		mpoPieces[Piece::PC_WHITE][Piece::PT_BISHOP] = SDL_LoadBMP("Images/Fou blanc.bmp");
		mpoPieces[Piece::PC_WHITE][Piece::PT_QUEEN] = SDL_LoadBMP("Images/Reine blanche.bmp");
		mpoPieces[Piece::PC_WHITE][Piece::PT_KING] = SDL_LoadBMP("Images/Roi blanc.bmp");

		mpoPieces[Piece::PC_BLACK][Piece::PT_PAWN] = SDL_LoadBMP("Images/Pion noir.bmp");
		mpoPieces[Piece::PC_BLACK][Piece::PT_ROOK] = SDL_LoadBMP("Images/Tour noire.bmp");
		mpoPieces[Piece::PC_BLACK][Piece::PT_KNIGHT] = SDL_LoadBMP("Images/Cavalier noir.bmp");
		mpoPieces[Piece::PC_BLACK][Piece::PT_BISHOP] = SDL_LoadBMP("Images/Fou noir.bmp");
		mpoPieces[Piece::PC_BLACK][Piece::PT_QUEEN] = SDL_LoadBMP("Images/Reine noire.bmp");
		mpoPieces[Piece::PC_BLACK][Piece::PT_KING] = SDL_LoadBMP("Images/Roi noir.bmp");

		for(unsigned int i = 0; i < 6; ++i)	
			SDL_SetColorKey(mpoGame[i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoGame[i]->format, 255, 0, 0));

		SDL_SetColorKey(mpoGame[CHESS], SDL_SRCCOLORKEY, SDL_MapRGB(mpoGame[CHESS]->format, 0, 255, 0));

		for(unsigned int i = 0; i < 6; ++i)
		{
			SDL_SetColorKey(mpoPieces[Piece::PC_WHITE][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::PC_WHITE][i]->format, 255, 0, 0));
			SDL_SetColorKey(mpoPieces[Piece::PC_BLACK][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::PC_BLACK][i]->format, 255, 0, 0));
		}
	}
	catch(exception & e)
	{
		cout << "interface_SDL.cpp:InterfaceSDL" << endl;
		throw e;
	}
}

InterfaceSDL::~InterfaceSDL()
{
	for(unsigned int i = 0; i < 5; ++i)
		SDL_FreeSurface(mpoGame[i]);

	for(unsigned int i = 0; i < 6; ++i)
	{
		SDL_FreeSurface(mpoPieces[Piece::PC_WHITE][i]);
		SDL_FreeSurface(mpoPieces[Piece::PC_BLACK][i]);
	}

	TTF_CloseFont(mpoMenuFont);
	TTF_CloseFont(mpoMessagesFont);

	TTF_Quit();
	SDL_Quit();
}

void InterfaceSDL::BlitBoard(const Board & oBoard)
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

			if(!(oBoard.*mExportedMethods.pBoardBIsSquareEmpty)(oPos))
			{
				SDL_BlitSurface(mpoPieces[(oBoard.*mExportedMethods.pBoardEGetSquareColor)(oPos)][(oBoard.*mExportedMethods.pBoardEGetSquareType)(oPos)], NULL, mpoGame[SCREEN], &position);
			}
		}
}

void InterfaceSDL::BlitGameOver(std::string strMessage)
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

void InterfaceSDL::BlitMessage(std::string strMessage)
{
	SDL_Color oBlack = {0, 0, 0};

	moMessages.push(TTF_RenderText_Blended(mpoMessagesFont, strMessage.c_str(), oBlack));

	if(moMessages.size() > 10)
	{
		SDL_FreeSurface(moMessages.front());
		moMessages.pop();
	}
}

void InterfaceSDL::BlitPossibilities(vector<Position> oPossibilities)
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

void InterfaceSDL::BlitInCheck(Position oPos)
{
	SDL_Rect position;
	position.y = oPos.mX * SQUARE_HEIGHT;
	position.x = oPos.mY * SQUARE_WIDTH;

	SDL_BlitSurface(mpoGame[CHESS], NULL, mpoGame[SCREEN], &position);
}

void InterfaceSDL::BlitSelection(Position oPos)
{
	SDL_Rect position;
	position.x = oPos.mY * SQUARE_HEIGHT;
	position.y = oPos.mX * SQUARE_WIDTH;

	SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &position);
}

void InterfaceSDL::BlitCurrentPlayer(Piece::PIECE_COLOR eColor)
{
	SDL_Color oPlayerColor;
	string strPlayer = "";

	if(eColor == Piece::PC_WHITE)
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

char InterfaceSDL::cGetNewPieceType(Piece::PIECE_COLOR eColor)
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
	SDL_BlitSurface(mpoPieces[eColor][Piece::PT_QUEEN], NULL, mpoGame[SCREEN], &position);

	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::PT_BISHOP], NULL, mpoGame[SCREEN], &position);
	
	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::PT_KNIGHT], NULL, mpoGame[SCREEN], &position);
	
	position.x += 90;
	SDL_BlitSurface(mpoPieces[eColor][Piece::PT_ROOK], NULL, mpoGame[SCREEN], &position);

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

int InterfaceSDL::iGetMenuEntry(const std::vector<std::string> & oMenu)
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

	SDL_FillRect(mpoGame[SCREEN], NULL, SDL_MapRGB(mpoGame[SCREEN]->format, BACKGROUNDCOLOR));
	SDL_BlitSurface(mpoGame[BOARD], NULL, mpoGame[SCREEN], &position);

	position.x = FONT_HEIGHT;
	position.y = iStartPositionY;

	vector<SDL_Surface *> poOptions;

	for(unsigned int i = 0; i < oMenu.size(); ++i)
	{
		poOptions.push_back(TTF_RenderText_Blended(mpoMenuFont, (" " + oMenu[i]).c_str(), oRed));
		//SDL_SetColorKey(poOptions[i], SDL_SRCCOLORKEY, SDL_MapRGB(poOptions[i]->format, 255, 0, 0));
		//SDL_SetColorKey(mpoPieces[Piece::PC_WHITE][i], SDL_SRCCOLORKEY, SDL_MapRGB(mpoPieces[Piece::PC_WHITE][i]->format, 255, 0, 0));

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

					//SDL_FillRect(mpoGame[SCREEN], NULL, SDL_MapRGB(mpoGame[SCREEN]->format, 0, 0, 0));
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
				return 4;
				break;
			  case SDLK_KP5 :
			    return 5;
				break;
              case SDLK_KP6 :
			  case SDLK_x :
                return 6;
                break;
			  default :
				break;
			}
		}
		else if(event.type == SDL_QUIT)
			return 6;
	}

	return 1;
}

char InterfaceSDL::cGetPlayerColorChoice()
{
	return 'W';
}

void InterfaceSDL::Pause()
{
}

void InterfaceSDL::BlitGame(const Game & oGame)
{
	BlitBoard((oGame.*mExportedMethods.pGameOGetBoard)());
    if((oGame.*mExportedMethods.pGameBIsPlayerInCheck)(Piece::PC_BLACK))
		BlitInCheck((oGame.*mExportedMethods.pGameOGetKingPosition)(Piece::PC_BLACK));
    else if((oGame.*mExportedMethods.pGameBIsPlayerInCheck)(Piece::PC_WHITE))
		BlitInCheck((oGame.*mExportedMethods.pGameOGetKingPosition)(Piece::PC_WHITE));
}

void InterfaceSDL::DisplayGame(const Game & oGame)
{
    BlitGame(oGame);
	/*BlitBoard(oGame.oGetBoard());
	if(oGame.bIsBlackInCheck())
		BlitInCheck(oGame.oGetKingPosition(Piece::PC_BLACK));
	else if(oGame.bIsWhiteInCheck())
		BlitInCheck(oGame.oGetKingPosition(Piece::PC_WHITE));*/

	SDL_Flip(mpoGame[SCREEN]);
}

GameEntry InterfaceSDL::oGetGameEntry(Game & oGame)
{
	DisplayGame(oGame);
	bool bSelectionOk = false;
	SDL_Event event;
	Position oFirstSelection;
	Position oSecondSelection;
	Position oPossibilitiesPosition;
	vector<Position> oPossibilities;

    Board oBoard = (oGame.*mExportedMethods.pGameOGetBoard)();

	while(!bSelectionOk)
	{
		try
		{
			SDL_WaitEvent(&event);

			switch(event.type)
			{
			  case SDL_QUIT :
				return GameEntry("x");
				break;
			  case SDL_MOUSEBUTTONDOWN :
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					if(oFirstSelection.bIsEmpty())
					{
						oFirstSelection = Position(event.button.y / SQUARE_WIDTH, event.button.x / SQUARE_HEIGHT);

						if(!(oBoard.*mExportedMethods.pBoardBIsSquareEmpty)(oFirstSelection))
						{
							if((oBoard.*mExportedMethods.pBoardEGetSquareColor)(oFirstSelection) != (oGame.*mExportedMethods.pGameEGetCurrentPlayer)())
							{
								BlitMessage("This piece doesn't belong to you");
								oFirstSelection.Empty();
							}
						}
						else
							oFirstSelection.Empty();
					}
					else
					{
						oSecondSelection = Position(event.button.y / SQUARE_WIDTH, event.button.x / SQUARE_HEIGHT);
						bSelectionOk = true;
					}
				}
				else if(event.button.button == SDL_BUTTON_RIGHT)
				{
					oPossibilitiesPosition = Position(event.button.y / SQUARE_WIDTH, event.button.x / SQUARE_HEIGHT);
					oPossibilities = oGame.oGetPossibilities(oPossibilitiesPosition);
				}
				break;
			  case SDL_MOUSEBUTTONUP :
				if(event.button.button == SDL_BUTTON_RIGHT)
				{
					Position oMousePosition(event.button.y / SQUARE_WIDTH, event.button.x / SQUARE_HEIGHT);
					  
					for(unsigned int i = 0; i < oPossibilities.size(); ++i)
						if((oBoard.*mExportedMethods.pBoardEGetSquareColor)(oPossibilitiesPosition) == (oGame.*mExportedMethods.pGameEGetCurrentPlayer)()
						&& oPossibilities[i] == oMousePosition)
							return GameEntry(oPossibilitiesPosition, oMousePosition);

					oPossibilities.clear();
				}

				break;
			  case SDL_KEYUP  :
				switch(event.key.keysym.sym)
				{
				  case SDLK_x :
					return GameEntry("x");
					break;
				  case SDLK_c :
					return GameEntry("c");
					break;
				}
				break;
			  default :
				break;
			}
				
			BlitGame(oGame);
			BlitPossibilities(oPossibilities);
			if(!oFirstSelection.bIsEmpty())
				BlitSelection(oFirstSelection);

			SDL_Flip(mpoGame[SCREEN]);
			/*if(strFirstSelection == "x"
			|| strFirstSelection == "c")
				return GameEntry(strFirstSelection);

			oGame.CheckSelectionCoords(strFirstSelection);

			strSecondSelection = strGetEntry();

			if(strSecondSelection == "x"
			|| strSecondSelection == "c")
				return GameEntry(strSecondSelection);

			bSelectionOk = true;*/
		}
		catch(exception & e)
		{
			BlitMessage(e.what());
		}
	}

	return GameEntry(oFirstSelection, oSecondSelection);
}

void InterfaceSDL::AddMessage(std::string)
{
}

void InterfaceSDL::BlitEditionSelection(Piece::PIECE_TYPE eSelectedType, Piece::PIECE_COLOR eSelectedColor)
{
	unsigned int iColorFactor = (eSelectedColor == Piece::PC_WHITE ? 0 : 1);
	SDL_Rect oSelectionPosition = {SQUARE_WIDTH * (8 +iColorFactor) + 5, 1};
	switch(eSelectedType)
	{
	  case Piece::PT_PAWN :
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_ROOK :
		oSelectionPosition.y += SQUARE_HEIGHT;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_KNIGHT :
		oSelectionPosition.y += SQUARE_HEIGHT * 2;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_BISHOP :
		oSelectionPosition.y += SQUARE_HEIGHT * 3;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_QUEEN :
		oSelectionPosition.y += SQUARE_HEIGHT * 4;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_KING :
		oSelectionPosition.y += SQUARE_HEIGHT * 5;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  case Piece::PT_NONE :
		oSelectionPosition.x = SQUARE_WIDTH * 8 + 5 + SQUARE_WIDTH / 2;
		oSelectionPosition.y += SQUARE_HEIGHT * 6 + 5;
		SDL_BlitSurface(mpoGame[SELECTION], NULL, mpoGame[SCREEN], &oSelectionPosition);
		break;
	  default :
		break;
	}
}

EditionEntry InterfaceSDL::oGetEditionEntry(const GameEdition & oEdition)
{
	static Piece::PIECE_TYPE eSelectedType = Piece::PT_NONE;
	static Piece::PIECE_COLOR eSelectedColor = Piece::PC_BLACK;

	unsigned int iXMinEdition = 700;
	unsigned int iYMinEdition = 0;
	unsigned int iXMaxEdition = 700 + 2 * SQUARE_WIDTH;
	unsigned int iYMaxEdition = 7 * SQUARE_HEIGHT + 5;

	BlitBoard((oEdition.*mExportedMethods.pGameEditionOGetBoard)());
	BlitEditionCommands();
	BlitEditionSelection(eSelectedType, eSelectedColor);

	SDL_Flip(mpoGame[SCREEN]);

	SDL_Event event;
	bool bEntryOk = false;

	while(!bEntryOk)
	{
		SDL_WaitEvent(&event);

		switch(event.type)
		{
		  case SDL_QUIT :
			return EditionEntry("x");
			break;
		  case SDL_MOUSEBUTTONDOWN :
			if(event.button.x >= iXMinEdition && event.button.x <= iXMaxEdition
			&& event.button.y >= iYMinEdition && event.button.y <= iYMaxEdition)
			{
				if(event.button.x < iXMinEdition + SQUARE_WIDTH)
					eSelectedColor = Piece::PC_WHITE;
				else
					eSelectedColor = Piece::PC_BLACK;

				unsigned int iY = (event.button.y - iYMinEdition) /  SQUARE_HEIGHT + 1;

				switch(iY)
				{
				  case 1 :
					eSelectedType = Piece::PT_PAWN;
					break;
				  case 2 :
					eSelectedType = Piece::PT_ROOK;
					break;
				  case 3 :
					eSelectedType = Piece::PT_KNIGHT;
					break;
				  case 4 :
					eSelectedType = Piece::PT_BISHOP;
					break;
				  case 5 :
					eSelectedType = Piece::PT_QUEEN;
					break;
				  case 6 :
					eSelectedType = Piece::PT_KING;
					break;
				  case 7:
					eSelectedType = Piece::PT_NONE;
					break;
				  default:
					break;
				}
				
				BlitBoard((oEdition.*mExportedMethods.pGameEditionOGetBoard)());
				BlitEditionCommands();
				BlitEditionSelection(eSelectedType, eSelectedColor);

				SDL_Flip(mpoGame[SCREEN]);
			}
			else if(event.button.x < SQUARE_WIDTH * 8)
			{
				unsigned int iX = event.button.y / SQUARE_WIDTH;
				unsigned int iY = event.button.x / SQUARE_HEIGHT;
				return EditionEntry(Position(iX, iY), eSelectedType, eSelectedColor);
			}

			break;
		  case SDL_KEYDOWN :
			if(event.key.keysym.sym == SDLK_x)
				return EditionEntry("x");
			  
			break;
		  default :
			break;
		}

	}

	BlitBoard((oEdition.*mExportedMethods.pGameEditionOGetBoard)());
	BlitEditionCommands();
	BlitEditionSelection(eSelectedType, eSelectedColor);

	SDL_Flip(mpoGame[SCREEN]);

	return EditionEntry("");
}

std::string InterfaceSDL::strGetIPEntry()
{
	return "";
}

std::string InterfaceSDL::strGetPortEntry()
{
	return "";
}

void InterfaceSDL::BlitEditionCommands()
{
	SDL_Rect position;

	position.x = 700;
	position.y = 0;

	SDL_Rect oBoardPiece;
	oBoardPiece.h = 6 * SQUARE_HEIGHT;
	oBoardPiece.x = 0;
	oBoardPiece.w = 2 * SQUARE_WIDTH;
	oBoardPiece.y = 0;

	SDL_BlitSurface(mpoGame[BOARD], &oBoardPiece, mpoGame[SCREEN], &position);

	oBoardPiece.h = SQUARE_HEIGHT;
	oBoardPiece.w = SQUARE_WIDTH;
	oBoardPiece.x = SQUARE_WIDTH;
	oBoardPiece.y = 1;

	position.x = 743;
	position.y = 528;

	SDL_BlitSurface(mpoGame[BOARD], &oBoardPiece, mpoGame[SCREEN], &position);

	position.x = 700;
	position.y = 0;

	for(unsigned int i = 0; i < 6; ++i)
	{
		position.y = 87 * i + 5;
		SDL_BlitSurface(mpoPieces[Piece::PC_WHITE][i], NULL, mpoGame[SCREEN], &position);
	}

	position.x = 792;
	for(unsigned int i = 0; i < 6; ++i)
	{
		position.y = 87 * i + 5;
		SDL_BlitSurface(mpoPieces[Piece::PC_BLACK][i], NULL, mpoGame[SCREEN], &position);
	}
}