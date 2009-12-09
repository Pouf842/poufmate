#ifndef __BISHOP_H_
#define __BISHOP_H_

#include "piece.h"

class Bishop : public Piece
{
  public :
	Bishop(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif