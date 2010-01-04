#ifndef __MOVEMENT_H_
#define __MOVEMENT_H_

/**
 * This class describes a basic movement
 * A basic movement is defined by starting coordinates
 * and landing coordinates. The class contains a static
 * Board, which can be initialized with SetBoard(Board * oNewBoard);
 * The Execute() methods execute the movement on the board stored in the static variable
 */

#include "piece.h"
#include "position.h"
#include "board.h"

class Movement
{
  protected :
    static Board * spoBoard;	// Static board, upon which the movements are executed
	Position moPos1;			// The start position
	Position moPos2;			// The landing position

	Piece * mpoMovingPiece;		// A pointer to the moving piece
	Piece * mpoCapturedPiece;	// A pointer to the captured piece (0 if there isn't any)

  public :
	/**
	 * Constructor. Starting position and landing positions
	 * are given as arguments.
	 * The pointers to pieces are initialized from the static board and the positions.
	 * It therefore checks if the starting square contains a piece,
	 * If the landing square doesn't contain a same colored piece,
	 * and if the moving piece can move as described
	 */
	Movement(Position oPos1,
			 Position oPos2);

	/**
	 * Set the static board to the one given as argument
	 */
	static void SetBoard(Board * oNewBoard);

	/**
	 * Return the Starting position
	 */
	Position oGetCoords1() const;

	/**
	 * Return the landing position
	 */
	Position oGetCoords2() const;

	/**
	 * Cancel the movement (execute the inverted movement)
	 */
	virtual void CancelMovement();

	/**
	 * Return a pointer to the moving piece
	 */
	Piece * poGetMovingPiece() const;

	/**
	 * Return a pointer to the captured piece
	 */
	Piece * poGetCapturedPiece() const;

	/**
	 * Return the color of the player doing the movement
	 * (Simply return the color of the moving piece)
	 */
	Piece::Color eGetPlayerColor() const;

	/**
	 * Execute the movement on the static board
	 */
	virtual void Execute();
};

#endif