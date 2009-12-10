#ifndef __KNIGHT_H_
#define __KNIGHT_H_

#include "piece.h"
#include "coordinates.h"

class Knight : public Piece
{
  public :
	Knight(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsmovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif