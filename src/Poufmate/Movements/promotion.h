#ifndef __PROMOTION_H_
#define __PROMOTION_H_

/**
 * This class describes a special type of movement : pawn's promotion
 * It's described by two position (as any movements, see class Movement)
 * and the type new piece, whereby the pawn is replaced.
 * This piece is deleted when the move is cancelled
 * @see class Movement
 */

#include "piece.h"
#include "Core/position.h"
#include "Core/board.h"
#include "movement.h"

class Promotion : public Movement
{
  protected :
	Piece * mpoNewPiece;	// The piece whereby the pawn is replaced
  public :
	/**
	 * Constructor. Same as that of Movement, but takes a PieceType
	 * and create a new piece to replace the pawn.
	 */
	Promotion(Position, Position, Piece::PIECE_TYPE);

	/**
	 * Overload of Movement::CancelMovement(Board &)
	 * Same as Movement::CancelMovement(Board &),
	 * but also delete the replacement piece (moNewPiece)
	 */
	virtual void CancelMovement();

	/**
	 * Overload of Movement::Execute()
	 * Execute a promotion move : transform the moving piece
	 * to a new one of given type (mpoNewPiece) and place it
	 * on the finishing square
	 * @see Movement::Execute()
	 */
	virtual void Execute();
};

#endif
