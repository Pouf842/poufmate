#ifndef __GAME_H_
#define __GAME_H_

#include "board.h"
#include "movement.h"
#include <vector>

class Game
{
  protected :
    Board moBoard;
	vector<Movement> moHistory;
	Piece::Color meCurrentPlayer;
	unsigned int miXWhiteKing;
	unsigned int miYWhiteKing;
	unsigned int miXBlackKing;
	unsigned int miYBlackKing;
	bool mbIsOver;
	std::string mstrSelection;

	bool bIsCoordsCorrect(unsigned int X, unsigned int Y) const;
	void CheckCoords(unsigned int X, unsigned int Y) const;
	void CheckIsMovementCorrect(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2) const;
	bool bIsMovementCorrect(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2) const;
	bool bIsOver();
	void CancelLastMove();
	void MovePiece(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2);
	bool bIsInCheck(Piece::Color) const;
	bool bIsCheckMate(Piece::Color);
	std::string strGetPossibilities(unsigned int X, unsigned int Y);
  public :
	Game();
	void Run();
};

#endif