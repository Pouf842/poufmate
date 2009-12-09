#ifndef __KING_H_
#define __KING_H_

#include "piece.h"

class King : public Piece
{
  public :
	King(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif