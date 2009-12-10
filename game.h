#ifndef __GAME_H_
#define __GAME_H_

#include "board.h"
#include "movement.h"
#include <vector>
#include "coordinates.h"

class Game
{
  protected :
    Board moBoard;
	vector<Movement> moHistory;
	Piece::Color meCurrentPlayer;
	Coordinates miXWhiteKing;
	Coordinates moWhiteKing;
	Coordinates moBlackKing;

	bool mbIsOver;
	Coordinates moSelection;

	bool bIsCoordsCorrect(Coordinates) const;
	void CheckSelectionCoords(Coordinates) const;
	void CheckIsMovementCorrect(Coordinates, Coordinates) const;
	bool bIsMovementCorrect(Coordinates, Coordinates) const;
	bool bIsOver();
	void CancelLastMove();
	void MovePiece(Coordinates, Coordinates);
	bool bIsInCheck(Piece::Color) const;
	bool bIsCheckMate(Piece::Color);
	std::string strGetPossibilities(Coordinates);
  public :
	Game();
	void Run();
};

#endif