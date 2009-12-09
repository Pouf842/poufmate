#ifndef __TOWER_H_
#define __TOWER_H_

#include "piece.h"

class Tower : public Piece
{
  protected :
  public :
	Tower(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const;
};

#endif