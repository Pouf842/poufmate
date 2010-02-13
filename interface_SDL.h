#ifndef __INTERFACE_SDL_H_
#define __INTERFACE_SDL_H_

#include "interface.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <queue>
#include <vector>

class InterfaceSDL : public Interface
{
  protected :
	SDL_Surface * mpoGame[6];
	SDL_Surface * mpoPieces[2][6];
	TTF_Font * mpoMenuFont;
	TTF_Font * mpoMessagesFont;
	std::queue<SDL_Surface *> moMessages;

	enum eGameImages {SCREEN = 0, BOARD = 1, MESSAGEBOARD = 2, SELECTION = 3, CHESS = 4, POSSIBLE = 5};

	InterfaceSDL();
	virtual ~InterfaceSDL();
  public :
	virtual void DisplayGame(const Game &);
	virtual void DisplayBoard(const Board &);
	virtual void DisplayMessage(std::string strMessage);
	virtual std::string strGetEntry();
	virtual void DisplayPossibilities(std::vector<Position>);
	virtual void DisplayInCheck(Position);
	virtual void DisplayCurrentPlayer(Piece::Color);
	virtual void DisplaySelection(Position);
	virtual void CommitDisplay();
	virtual char cGetNewPieceType(Piece::Color);
	virtual char cGetPlayerColorChoice();
	virtual int iGetMenuEntry(const std::vector<std::string> &);
	virtual std::string strGetEditionEntry();
	virtual void DisplayGameOver(std::string);
	virtual std::string strKeyboardEntry(std::string strMessage, std::string strDefaultValue = "");
	static Interface * poGetInstance();
};

#endif
