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

using namespace std;

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
	 * Return the color of the specified square
	 */
	Piece::Color eGetSquareColor(Position) const;

	/**
	 * Return a pointer to the piece of the specified square
	 */
	Piece * poGetPiece(Position) const;

	/**
	 * Replace the piece of the specified square
	 * by the specified piece
	 */
	void SetPiece(Position, Piece * poNewPiece);
};

#endif