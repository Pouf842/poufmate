#ifndef __PIECE_H_
#define __PIECE_H_

#include "coordinates.h"

class Board;

class Piece
{
  public :
	enum Color {BLACK = 0, WHITE = 1};
	enum PieceType {PAWN = 0, TOWER = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5, NONE = 6};

	virtual char cGetChar() const = 0;
	virtual Color eGetColor() const;
	virtual bool bIsMovementCorrect(Coordinates, Coordinates, const Board & oBoard) const = 0;
	void SetFirstMove(bool);
	bool bHasAlreadyMoved() const;
	bool bIsFirstMove() const;
	PieceType eGetType();

  protected :
	bool mbFirstMove;
	Color meColor;
	PieceType meType;
};

#endif