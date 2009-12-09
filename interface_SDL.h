#ifndef __INTERFACE_SDL_H_
#define __INTERFACE_SDL_H_

#include "interface.h"
#include "SDL.h"

class InterfaceSDL : public Interface
{
  protected :
	SDL_Surface * mpoScreen;
	SDL_Surface * mpoBoard;
	SDL_Surface * mpoSelection;
	SDL_Surface * mpoChess;
	SDL_Surface * mpoPossibleMove;

	SDL_Surface * mpoWhitePawn;
	SDL_Surface * mpoWhiteTower;
	SDL_Surface * mpoWhiteKnight;
	SDL_Surface * mpoWhiteBishop;
	SDL_Surface * mpoWhiteQueen;
	SDL_Surface * mpoWhiteKing;

	SDL_Surface * mpoBlackPawn;
	SDL_Surface * mpoBlackTower;
	SDL_Surface * mpoBlackKnight;
	SDL_Surface * mpoBlackBishop;
	SDL_Surface * mpoBlackQueen;
	SDL_Surface * mpoBlackKing;

	InterfaceSDL();
	~InterfaceSDL();
  public :
	virtual void DisplayBoard(const Board &) const;
	virtual void DisplayMessage(std::string strMessage) const;
	virtual std::string strGetEntry() const;
	virtual void DisplayPossibilities(std::string strPossibilities) const;
	virtual void DisplayInCheck(unsigned int X, unsigned int Y) const;
	virtual void DisplaySelection(unsigned int X, unsigned int Y) const;
	static Interface * poGetInstance();
};

#endif
