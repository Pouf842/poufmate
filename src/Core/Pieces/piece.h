#ifndef __PIECE_H_
#define __PIECE_H_

/**
 * This is an abstract class describing a piece of the game
 * It's intented to be derivated for each type of piece
 */

#include "Core\position.h"

class Board;

class Piece
{
  public :
	enum PIECE_COLOR
	{
		PC_BLACK = 0,
		PC_WHITE
	};	// Color of the piece

	enum PIECE_TYPE
	{
		PT_PAWN = 0,
		PT_ROOK,
		PT_KNIGHT,
		PT_BISHOP,
		PT_QUEEN,
		PT_KING,
		PT_NONE
	};	// Type of the piece

	/**
	 * Return the color of the piece
	 */
	virtual PIECE_COLOR eGetColor() const;

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
	PIECE_TYPE eGetType() const;

  protected :
	bool mbFirstMove;	// Boolean describing if the next move of the piece will be the first
	PIECE_COLOR meColor;		// The color of the piece
	PIECE_TYPE meType;	// The type of the piece
};

#endif