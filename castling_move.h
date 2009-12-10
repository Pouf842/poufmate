#ifndef __CASTLING_MOVE_H_
#define __CASTLING_MOVE_H_

#include "movement.h"

class CastlingMove : public Movement
{
  public :
	CastlingMove(Coordinates oCoords1, Coordinates oCoords2, Piece * poMovingPiece);
	virtual void CancelMovement(Board &) const;
};

#endif
