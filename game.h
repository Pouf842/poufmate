#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include "board.h"
#include "coordinates.h"
#include "movement.h"

class Game
{
  protected :
	enum CastlingSide {LEFT, RIGHT};
	Board moBoard;
	vector<Movement*> moHistory;
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
	bool bIsCastling(Coordinates, Coordinates);
	void CheckIsCastlingOk(Piece::Color ePlayer, Game::CastlingSide);
	void Castling(Piece::Color ePlayer, CastlingSide);
	bool bIsInCheck(Piece::Color) const;
	bool bIsCheckMate(Piece::Color);
	std::string strGetPossibilities(Coordinates);
  public :
	Game();
	void Run();
};

#endif