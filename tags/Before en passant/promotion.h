#ifndef __PROMOTION_H_
#define __PROMOTION_H_

/**
 * This class describes a special type of movement : pawn's promotion
 * It's described by two position (as any movements, see class Movement)
 * and the type new piece, whereby the pawn is replaced.
 * This piece is deleted when the move is cancelled
 * @see class Movement
 */

#include "movement.h"
#include "piece.h"
#include "position.h"
#include "board.h"

class Promotion : public Movement
{
  protected :
	Piece * mpoNewPiece;	// The piece whereby the pawn is replaced
  public :
	/**
	 * Constructor. Same as that of Movement, but takes a PieceType
	 * and create a new piece to replace the pawn.
	 */
	Promotion(Position, Position, Piece::PieceType);

	/**
	 * Constructor. Same as that of Movement, but takes a char
	 * representing the type of the new piece
	 * and create it to replace the pawn.
	 * The char can be one of the following :
	 * 'R' or 'r' for a rook
	 * 'N' or 'n' for a knight
	 * 'B' or 'b' for a bishop
	 * 'Q' or 'q' for a queen
	 * Note that in case of a pawn type, no new piece
	 * is created
	 */
	Promotion(Position oPos1, Position oPos2, char cType);

	/**
	 * Overload of Movement::CancelMovement(Board &)
	 * Same as Movement::CancelMovement(Board &),
	 * but also delete the replacement piece (moNewPiece)
	 */
	virtual void CancelMovement();
	virtual void Execute();
};

#endif
