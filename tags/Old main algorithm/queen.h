#ifndef __QUEEN_H_
#define __QUEEN_H_

#include "piece.h"

class Queen : public Piece
{
  public :
	Queen(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif