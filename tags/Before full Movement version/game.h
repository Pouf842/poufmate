#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include "board.h"
#include "position.h"
#include "movement.h"

class Game
{
  protected :
	enum CastlingSide {LEFT, RIGHT};
	Board moBoard;
	vector<Movement*> moHistory;
	Piece::Color meCurrentPlayer;
	Position moKings[2];

	bool mbIsOver;
	Position moSelection;

	void CheckSelectionCoords(Position) const;
	void CheckIsMovementCorrect(Position, Position) const;
	bool bIsMovementCorrect(Position, Position) const;
	bool bIsOver();
	void CancelLastMove();
	void MovePiece(Position, Position);
	bool bIsCastling(Position, Position);
	void CheckIsCastlingOk(Piece::Color ePlayer, Game::CastlingSide);
	void Castling(Piece::Color ePlayer, CastlingSide);
	bool bIsInCheck(Piece::Color) const;
	bool bIsCheckMate(Piece::Color);
	std::string strGetPossibilities(Position);
	void SwitchPlayer();
	bool bIsPromotion(Position oPos1, Position oPos2) const;
	void PromotePawn(Position, char);
  public :
	Game();
	void Run();
};

#endif