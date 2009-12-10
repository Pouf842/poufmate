#ifndef __FIRST_MOVE_H_
#define __FIRST_MOVE_H_

#include "movement.h"

class FirstMove : public Movement
{
  public :
	FirstMove(Coordinates oCoords1,
			 Coordinates oCoords2,
			 Piece * poMovingPiece, Piece * poCapturedPiece = 0);
	virtual void CancelMovement(Board &) const;
};

#endif
