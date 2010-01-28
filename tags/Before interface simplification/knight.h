#ifndef __KNIGHT_H_
#define __KNIGHT_H_

/**
 * This class describes a particular type of piece : the knight
 * @see class Piece
 */

#include "piece.h"
#include "position.h"

class Knight : public Piece
{
  public :
	/**
	 * Constructor
	 */
	Knight(Piece::Color);

		/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is two squares on an axe, and two on the other,
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif