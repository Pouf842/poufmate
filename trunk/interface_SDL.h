#ifndef __INTERFACE_SDL_H_
#define __INTERFACE_SDL_H_

#include "interface.h"
#include "SDL.h"
#include "SDL_ttf.h"

class InterfaceSDL : public Interface
{
  protected :
	SDL_Surface * mpoGame[5];
	SDL_Surface * mpoPieces[2][6];
	SDL_Surface * mpoMessagesBG;

	enum eGameImages {SCREEN = 0, BOARD = 1, SELECTION = 2, CHESS = 3, POSSIBLE = 4};

	InterfaceSDL();
	virtual ~InterfaceSDL();
  public :
	virtual void DisplayBoard(const Board &);
	virtual void DisplayMessage(std::string strMessage);
	virtual std::string strGetEntry();
	virtual void DisplayPossibilities(std::vector<Position>);
	virtual void DisplayInCheck(Position);
	virtual void DisplayCurrentPlayer(Piece::Color);
	virtual void DisplaySelection(Position);
	virtual void CommitDisplay();
	virtual char cGetNewPieceType(Piece::Color);
	virtual char cGetMenuEntry();
	virtual std::string strGetEditionEntry();
	virtual void DisplayMenu(const Menu &);
	static Interface * poGetInstance();
};

#endif
