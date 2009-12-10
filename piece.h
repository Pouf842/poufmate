#ifndef __PIECE_H_
#define __PIECE_H_

#include "coordinates.h"

class Board;

class Piece
{
  public :
	enum Color {BLACK, WHITE};
	enum PieceType {PAWN, TOWER, KNIGHT, BISHOP, QUEEN, KING, NONE};

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