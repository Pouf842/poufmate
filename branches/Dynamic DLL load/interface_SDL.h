#ifndef __INTERFACE_SDL_H_
#define __INTERFACE_SDL_H_

#include "interface.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <queue>
#include <vector>

class __declspec(dllexport) InterfaceSDL : public Interface
{
  public :
    virtual void Pause();
	virtual void DisplayGame(const Game &);
	virtual GameEntry oGetGameEntry(Game &);
	virtual void AddMessage(std::string);
	virtual EditionEntry oGetEditionEntry(const GameEdition &);
	virtual std::string strGetIPEntry();
	virtual std::string strGetPortEntry();
	virtual char cGetNewPieceType(Piece::Color);
	virtual int iGetMenuEntry(const std::vector<std::string> &);
	virtual char cGetPlayerColorChoice();
	static Interface * poGetInstance(struct stExportedMethods exportedMethods);

  protected :
	SDL_Surface * mpoGame[6];
	SDL_Surface * mpoPieces[2][6];
	TTF_Font * mpoMenuFont;
	TTF_Font * mpoMessagesFont;
	std::queue<SDL_Surface *> moMessages;

	enum eGameImages {SCREEN = 0, BOARD = 1, MESSAGEBOARD = 2, SELECTION = 3, CHESS = 4, POSSIBLE = 5};

	InterfaceSDL(struct stExportedMethods exportedMethods);
	virtual ~InterfaceSDL();
	virtual void BlitBoard(const Board &);
	virtual void BlitMessage(std::string strMessage);
	virtual void BlitPossibilities(std::vector<Position>);
	virtual void BlitInCheck(Position);
	virtual void BlitCurrentPlayer(Piece::Color);
	virtual void BlitSelection(Position);
	virtual void BlitGameOver(std::string);
	virtual void BlitGame(const Game &);
	virtual void BlitEditionCommands();
	virtual void BlitEditionSelection(Piece::PieceType, Piece::Color);
};

#endif
