#ifndef __BASE_BOARD_H_
#define __BASE_BOARD_H_

#include "position.h"
#include "piece.h"
#include "square.h"

class BaseBoard
{
  protected :
	Square moSquares[8][8];	// The squares of the board

  public:
	BaseBoard(void);
	~BaseBoard(void);

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
	 * Overload of eGetSquareType(Position)
	 * @see eGetSquareType(Position)
	 */
	Piece::PieceType eGetSquareType(unsigned int, unsigned int) const;

	/**
	 * Return the type of the piece on the specified square
	 */
	Piece::PieceType eGetSquareType(Position) const;

	/**
	 * Overload of eGetSquareColor(Position)
	 * @see eGetSquareColor(Position)
	 */
	Piece::Color eGetSquareColor(unsigned int, unsigned int) const;

	/**
	 * Return the color of the piece on the specified square
	 */
	Piece::Color eGetSquareColor(Position) const;
	
	/**
	 * Return a pointer to the piece of the specified square
	 */
	Piece * poGetPiece(Position) const;
};

#endif