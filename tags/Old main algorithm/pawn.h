#ifndef __PAWN_H_
#define __PAWN_H_

#include "piece.h"

class Pawn : public Piece
{
  public :
	Pawn(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif