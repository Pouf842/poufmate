#ifndef __GAME_H_
#define __GAME_H_

/**
 * This class describes a chess game
 * The Run() method start the game, controls
 * the actions of the players, interact with
 * them via an Interface object, and transmit
 * their choices of action to the board
 */

#include <vector>
#include "board.h"
#include "position.h"
#include "movement.h"

class Game
{
  protected :
	Board moBoard;					// The board of the game
	vector<Movement*> moHistory;	// History of moves
	Piece::Color meCurrentPlayer;	// Current playing player
	Position moKings[2];			// Positions of the two kings (usefull for check and checkmate verification)

	bool mbIsOver;					// true if the party is over
	Position moSelection;			// The selected square. Can be empty if no square has been selected yet

	/**
	 * Change the current player
	 */
	void SwitchPlayer();

	/**
	 * Return mbIsOver
	 */
	bool bIsOver();

	/**
	 * Cancel the last recorded move
	 */
	void CancelLastMove();

	/**
	 * Check if the given position is a valid selection. Throw an exception otherwise
	 */
	void CheckSelectionCoords(Position) const;

	/**
	 * Check if the given movement (described by two position) is a castling move
	 */
	bool bIsCastling(Position, Position);

	/**
	 * Check if the given movement is correct
	 */
	bool bIsMovementCorrect(Position, Position) const;

	/**
	 * Check if the player of the given color is in check
	 */
	bool bIsInCheck(Piece::Color) const;

	/**
	 * Check if the player of the given color is mate
	 */
	bool bIsCheckMate(Piece::Color);

	/**
	 * Check if the game is in a stalemate situation
	 */
	bool bIsGameInStaleMate();

	/**
	 * Check if the given move is a pawn's promotion
	 */
	bool bIsPromotion(Position oPos1, Position oPos2) const;

	/**
	 * Return all the possibilities of movement for the piece on the given square
	 */
	vector<Position> oGetPossibilities(Position);

	/**
	 * Check if the path of the castling described 
	 */
	bool bIsCastlingPathOk(Position, Position);

	/**
	 * Move a piece from the first given position, to the second
	 */
	void MovePiece(Position oPos1, Position oPos2);
  public :
	  
	/**
	 * Constructor
	 */
	Game();
	
	/**
	 * Launch the game, interact with the players via an interface,
	 * controls their movements, and transmit them to the board
	 */
	void Run();
};

#endif