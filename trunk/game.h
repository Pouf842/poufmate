#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include "board.h"
#include "position.h"
#include "movement.h"

class Game
{
  protected :
	Board moBoard;
	vector<Movement*> moHistory;
	Piece::Color meCurrentPlayer;
	Position moKings[2];

	bool mbIsOver;
	bool mbIsCurrentPlayerCheckMate;
	Position moSelection;

	void SwitchPlayer();
	bool bIsOver();
	void CancelLastMove();
	void CheckSelectionCoords(Position) const;
	bool bIsCastling(Position, Position);
	bool bIsMovementCorrect(Position, Position) const;
	bool bIsInCheck(Piece::Color) const;
	bool bIsCheckMate(Piece::Color);
	bool bIsPromotion(Position oPos1, Position oPos2) const;
	std::string strGetPossibilities(Position);
  public :
	Game();
	void Run();
};

#endif