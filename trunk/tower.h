#ifndef __TOWER_H_
#define __TOWER_H_

#include "piece.h"
#include "position.h"

class Tower : public Piece
{
  protected :
  public :
	Tower(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif