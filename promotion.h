#ifndef __PROMOTION_H_
#define __PROMOTION_H_

#include "movement.h"
#include "piece.h"
#include "position.h"
#include "board.h"

class Promotion : public Movement
{
  public :
    Promotion(Position, Position, Piece *, Piece *);
	void CancelMovement(Board &) const;
};

#endif
