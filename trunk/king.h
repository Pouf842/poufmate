#ifndef __KING_H_
#define __KING_H_

#include "piece.h"
#include "coordinates.h"

class King : public Piece
{
  public :
	King(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif