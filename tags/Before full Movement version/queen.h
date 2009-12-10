#ifndef __QUEEN_H_
#define __QUEEN_H_

#include "piece.h"
#include "coordinates.h"

class Queen : public Piece
{
  public :
	Queen(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif