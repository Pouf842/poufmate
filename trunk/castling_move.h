#ifndef __CASTLING_MOVE_H_
#define __CASTLING_MOVE_H_

#include "movement.h"

class CastlingMove : public Movement
{
  protected :
	Piece * mpoRook;
	enum CastlingSide {LEFT, RIGHT};
	CastlingSide meSide;
  public :
	CastlingMove(Position oPos1, Position oPos2);
	virtual void Execute();
	virtual void CancelMovement(Board &) const;
};

#endif
