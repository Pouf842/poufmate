#ifndef __ROOK_H_
#define __ROOK_H_

/**
 * This class describes a particular type of piece : the rook
 * @see class Piece
 */

#include "piece.h"
#include "Core/position.h"

class Rook : public Piece
{
  public :
	/**
	 * Constructor
	 */
	Rook(Piece::PIECE_COLOR);

	/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is horizontal or vertical,
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif