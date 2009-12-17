#ifndef __PIECE_H_
#define __PIECE_H_

/**
 * This is an abstract class describing a piece of the game
 * It's intented to be derivated for each type of piece
 */

#include "position.h"

class Board;

class Piece
{
  public :
	enum Color {BLACK = 0, WHITE = 1};	// Color of the piece
	enum PieceType {PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5, NONE = 6};	// Type of the piece

	/**
	 * Return the color of the piece
	 */
	virtual Color eGetColor() const;

	/**
	 * Return true if the movement described by the two given positions
	 * is correct for this piece on the given board.
	 * WARNING : The piece does not check if the finishing square is empty or contains a piece of a different color
	 * (except for the pawn, which must accept diagonal moves only for capturing).
	 * Therefore, this check has to be done in an upper level
	 */
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const = 0;

	/**
	 * Set the mbFirstMove boolean to a new value
	 */
	void SetFirstMove(bool);

	/**
	 * Return !bIsFirstMove()
	 */
	bool bHasAlreadyMoved() const;

	/**
	 * Return mbFirstMove
	 */
	bool bIsFirstMove() const;

	/**
	 * Return the type of the piece
	 */
	PieceType eGetType();

  protected :
	bool mbFirstMove;	// Boolean describing if the next move of the piece will be the first
	Color meColor;		// The color of the piece
	PieceType meType;	// The type of the piece
};

#endif