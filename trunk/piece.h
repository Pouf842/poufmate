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
	virtual bool bIsmovementCorrect(Coordinates, Coordinates, const Board & oBoard) const = 0;
	void SetFirstMove(bool);
	bool bHasAlreadyMoved();
	PieceType eGetType();

  protected :
    bool mbFirstMove;
	Color meColor;
	PieceType meType;
};

#endif