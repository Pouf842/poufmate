#ifndef __EN_PASSANT_H_
#define __EN_PASSANT_H_

/**
 * This class describes a special type of movement : en passant
 * It checks if the movement is a correct en passant :
 * Is the last move a 2 squares forward from a pawn ?
 * Is the captured pawn is the last that has moved ?
  * @see class Movement
 */

#include "movement.h"
#include "position.h"

class EnPassant : public Movement
{
  public :
	/**
	 * Constructor. Takes a last movement,
	 * which should be the last one of the game
	 * to check if the en passant is possible
	 */
	EnPassant(Position, Position, Movement*);

	/**
	 * Overload of Movement::Execute()
	 * Execute the movement
	 * @see Movement::Execute()
	 */
	virtual void Execute();

	/**
	 * Overload of Movement::CancelMovement()
	 * Cancel the movement
	 * @see Movement::CancelMovement()
	 */
	virtual void CancelMovement();
};

#endif