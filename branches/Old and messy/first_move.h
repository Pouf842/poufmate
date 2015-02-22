#ifndef __FIRST_MOVE_H_
#define __FIRST_MOVE_H_

/**
 * This class describes a special type of movement : first moves
 * The only difference with a basic move is that it reset the bFirstMove boolean
 * of the moving piece to true when it is canceled
 * @see class Movement
 */

#include "movement.h"

class FirstMove : public Movement
{
  public :
    /**
	 * Constructor
	 * @see the constructor of Movement
	 */
	FirstMove(Position oPos1,
			 Position oPos2);

	/**
	 * Overload of Movement::CancelMovement(Board &) const;
	 * Cancel the movement, and reset the bFirstMove boolean
	 * of the moving piece to true
	 */
	virtual void CancelMovement();
};

#endif
