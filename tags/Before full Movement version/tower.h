#ifndef __TOWER_H_
#define __TOWER_H_

#include "piece.h"
#include "coordinates.h"

class Tower : public Piece
{
  protected :
  public :
	Tower(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Coordinates, Coordinates, const Board & oBoard) const;
};

#endif