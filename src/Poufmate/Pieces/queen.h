#ifndef __QUEEN_H_
#define __QUEEN_H_

/**
 * This class describes a particular type of piece : the queen
 * @see class Piece
 */

#include "piece.h"
#include "Core/position.h"

class Queen : public Piece
{
  public :
	/**
	 * Constructor
	 */
	Queen(Piece::PIECE_COLOR);

	/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is rectilign,
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif