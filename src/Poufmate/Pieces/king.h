#ifndef __KING_H_
#define __KING_H_

/**
 * This class describes a particular type of piece : the king
 * @see class Piece
 */

#include "piece.h"
#include "Core/position.h"

class King : public Piece
{
  public :
	/**
	 * Constructor
	 */
	King(Piece::PIECE_COLOR);

	/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is rectilign, and of one square,
	 * or two squares on Y axes (horizontal) and if it is the first move (castling),
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif