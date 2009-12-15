#ifndef __FIRST_MOVE_H_
#define __FIRST_MOVE_H_

#include "movement.h"

class FirstMove : public Movement
{
  public :
	FirstMove(Position oPos1,
			 Position oPos2);
	virtual void CancelMovement(Board &) const;
};

#endif
