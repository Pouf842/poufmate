#ifndef __BISHOP_H_
#define __BISHOP_H_

#include "piece.h"
#include "coordinates.h"

class Bishop : public Piece
{
  public :
	Bishop(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif