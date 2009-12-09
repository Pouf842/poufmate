#ifndef __KNIGHT_H_
#define __KNIGHT_H_

#include "piece.h"

class Knight : public Piece
{
  public :
	Knight(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif