#ifndef __CASTLING_MOVE_H_
#define __CASTLING_MOVE_H_

/**
 * This class describes a special type of movement : castling
 * It checks if the castling is possible by the three following way :
 * Has the rook already moved ?
 * Has the king already moved ?
 * Is the path cleared between the king and the rook ?
 * WARNING : It can't check if the king will be in check on the way
 * Therefore, this verification is to do in an upper level
 * @see class Movement
 */

#include "movement.h"

class CastlingMove : public Movement
{
  protected :
	Piece * mpoRook;	// The rook involved by the castling
	enum CastlingSide {LEFT, RIGHT};	// The possible sides of castling
	CastlingSide meSide;	// The side of the castling
  public :
	/**
	 * Constructor. Initialize meSide and therefore mpoRook
	 * from the two positions.
	 * It checks if the castling is possible by the three following way :
	 * Has the rook already moved ?
	 * Has the king already moved ?
	 * Is the path cleared between the king and the rook ?
	 * WARNING : It can't check if the king will be in check on the way
	 * Therefore, this verification is to do in an upper level
	 */
	CastlingMove(Position oPos1, Position oPos2);

	/**
	 * Overload of Movement::Execute()
	 * Executes the castling (move the piece on the static board)
	 * @see Movement::Execute()
	 */
	virtual void Execute();

	/**
	 * Overload of Movement::CancelMovement(Board &) const
	 * Cancels the movement. Replaces the king and the rook
	 * to their respectives original positions, and reset
	 * their bFirstMove to true
	 * @see Movement::CancelMovement()
	 */
	virtual void CancelMovement();
};

#endif
