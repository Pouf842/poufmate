#ifndef __INTERFACE_SDL_H_
#define __INTERFACE_SDL_H_

#include "interface.h"
#include "SDL.h"

class InterfaceSDL : public Interface
{
  protected :
	SDL_Surface * mpoGame[5];
	SDL_Surface * mpoPieces[2][6];

	enum eGameImages {SCREEN = 0, BOARD = 1, SELECTION = 2, CHESS = 3, POSSIBLE = 4};

	InterfaceSDL();
	~InterfaceSDL();
  public :
	virtual void DisplayBoard(const Board &) const;
	virtual void DisplayMessage(std::string strMessage) const;
	virtual std::string strGetEntry() const;
	virtual void DisplayPossibilities(std::string strPossibilities) const;
	virtual void DisplayInCheck(Coordinates) const;
	virtual void DisplaySelection(Coordinates) const;
	virtual void DisplayCurrentPlayer(Piece::Color) const;
	static Interface * poGetInstance();
};

#endif
