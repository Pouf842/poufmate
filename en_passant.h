#ifndef __EN_PASSANT_H_
#define __EN_PASSANT_H_

#include "movement.h"
#include "position.h"

class EnPassant : public Movement
{
  public :
	EnPassant(Position, Position, Movement*);
	virtual void Execute();
	virtual void CancelMovement();
};

#endif