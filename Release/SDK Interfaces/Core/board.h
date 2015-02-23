#ifndef __BOARD_H_
#define __BOARD_H_

/**
 * This class described a chess board
 * It containt a set of 8x8 squares,
 * and an interface to manipulate those squares
 */

#include <iostream>
#include "square.h"
#include "position.h"

class Board
{
  protected :
	Square moSquares[8][8];	// The squares of the board

  public :
	/**
	 * Initializes the board. Creates and places the pieces on the squares
	 */
	void Init();

	/**
	 * Return true if the specified square is empty.
	 * In fact, call bIsSquareEmpty(Position)
	 */
	bool bIsSquareEmpty(unsigned int, unsigned int) const;

	/**
	 * Return true if the specified square is empty.
	 */
	bool bIsSquareEmpty(Position) const;

	/**
	 * Move a piece from the first position to the second
	 * (Set the first square's piece to NULL)
	 */
	void MovePiece(Position, Position);

	/**
	 * Return the color of the piece on the specified square
	 */
	Piece::PIECE_COLOR eGetSquareColor(Position) const;

	/**
	 * Overload of eGetSquareColor(Position)
	 * @see eGetSquareColor(Position)
	 */
	Piece::PIECE_COLOR eGetSquareColor(unsigned int, unsigned int) const;

	/**
	 * Return the type of the piece on the specified square
	 */
	Piece::PIECE_TYPE eGetSquareType(Position) const;

	/**
	 * Overload of eGetSquareType(Position)
	 * @see eGetSquareType(Position)
	 */
	Piece::PIECE_TYPE eGetSquareType(unsigned int, unsigned int) const;

	/**
	 * Return a pointer to the piece of the specified square
	 */
	Piece * poGetPiece(Position) const;

	/**
	 * Overload of poGetPiece(Position)
	 * @see poGetPiece(Position)
	 */
	Piece * Board::poGetPiece(unsigned int i, unsigned int j) const;

	/**
	 * Replace the piece of the specified square
	 * by the specified piece
	 */
	void SetPiece(Position, Piece * poNewPiece);
};

#endif