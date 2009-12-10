#ifndef __PAWN_H_
#define __PAWN_H_

#include "piece.h"
#include "coordinates.h"

class Pawn : public Piece
{
  public :
	Pawn(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif