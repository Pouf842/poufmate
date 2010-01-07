#ifndef __SQUARE_H_
#define __SQUARE_H_

/**
 * This class describes a square on a chess board
 * It may contains a piece
 */

#include "piece.h"

class Square
{
  protected :
	Piece * mpoPiece;	// The piece on the square (0 if there isn't any)
  public :
    /**
	 * Constructor
	 */
	Square();

	/**
	 * Return true if there isn't any piece on the square
	 */
	bool bIsEmpty() const;

	/**
	 * Put the specified piece on the square
	 */
	void SetPiece(Piece *);

	/**
	 * Return the color of the piece on the square, 
	 * or throws an exception if there isn't any
	 */
	Piece::Color eGetPieceColor() const;
	Piece::PieceType eGetPieceType() const;
	/**
	 * Return a pointer to the piece on that square
	 */
	Piece * poGetPiece() const;
};

#endif