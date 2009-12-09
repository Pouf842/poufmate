#ifndef __SQUARE_H_
#define __SQUARE_H_

#include "piece.h"

class Square
{
  protected :
	Piece * mpoPiece;
  public :
	Square();
	char cGetChar() const;
	bool bIsEmpty() const;
	void SetPiece(Piece *);
	Piece::Color eGetPieceColor() const;
	Piece * poGetPiece() const;
};

#endif