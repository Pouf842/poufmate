#ifndef __PAWN_H_
#define __PAWN_H_

/**
 * This class describes a particular type of piece : the pawn
 * @see class Piece
 */

#include "piece.h"
#include "Core/position.h"

class Pawn : public Piece
{
  public :
	/**
	 * Constructor
	 */
	Pawn(Piece::PIECE_COLOR);

	/**
	 * Overload of Piece::bIsMovementCorrect()
	 * Check if the movement is not backward ; is one or two squares forward,
	 * or one squares in diagonal ; if it's the first move in case of two squares forward
	 * if it's a capture in case of diagonal,
	 * and if the path is not obstructed
	 * @see Piece::bIsMovementCorrect()
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif