#ifndef __BISHOP_H_
#define __BISHOP_H_

/**
 * This class describes a particular type of piece : the bishop
 * @see class Piece
 */

#include "piece.h"
#include "position.h"

class Bishop : public Piece
{
  public :
    /**
	 * Constructor
	 */
	Bishop(Piece::Color);

	/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is diagonal,
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif