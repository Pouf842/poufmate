#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include "module.h"
#include "board.h"
#include "position.h"
#include "movement.h"
#include "interface.h"

class Game : public Module
{
  protected :
	Board moBoard;					// The board of the game
	std::vector<Movement*> moHistory;	// History of moves
	Piece::Color meCurrentPlayer;	// Current playing player
	Position moKings[2];			// Positions of the two kings (usefull for check and checkmate verification)

	bool mbIsOver;					// true if the party is over
	bool mbIsWhiteInCheck;
	bool mbIsBlackInCheck;
	bool mbIsWhiteCheckMate;
	bool mbIsBlackCheckMate;
	bool mbIsStaleMate;

	/**
	 * Change the current player
	 */
	virtual void SwitchPlayer();

	/**
	 * Cancel the last recorded move
	 */
	virtual void CancelLastMove();

	/**
	 * Check if the given movement (described by two position) is a castling move
	 */
	virtual bool bIsCastling(Position, Position);

	/**
	 * Check if the given movement is correct
	 */
	virtual bool bIsMovementCorrect(Position, Position) const;

	/**
	 * Check if the player of the given color is in check
	 */
	virtual bool bIsInCheck(Piece::Color) const;

	/**
	 * Check if the player of the given color is mate
	 */
	virtual bool bIsCheckMate(Piece::Color);

	/**
	 * Check if the game is in a stalemate situation
	 */
	virtual bool bIsGameInStaleMate();

	/**
	 * Execute the given movement, store it in the history
	 * and update the kings' position if necessary
	 */
	virtual void ExecuteMovement(Movement * poMove);

	/**
	 * Checks if the move described by the two position
	 * is a correct en passant move, and throws an exception
	 * describing the problem if it's not
	 */
	virtual bool bIsEnPassantOk(Position oPos1, Position oPos2);

	/**
	 * Check if the given move is a pawn's promotion
	 */
	virtual bool bIsPromotion(Position oPos1, Position oPos2) const;


	/**
	 * Check if the path of the castling described 
	 */
	virtual bool bIsCastlingPathOk(Position, Position);

	/**
	 * Move a piece from the first given position, to the second
	 */
	virtual void MovePiece(Position oPos1, Position oPos2);
	virtual void Initialize();

  public :

	/**
	 * Basic constructor
	 */
    Game(Interface * poInterface = NULL);

	/**
	 * Constructor with a specified board
	 * Throw exception if there is more or less
	 * than 1 king for each player
	 */
	Game(const Board &, Interface * poInterface = NULL);

	/**
	 * Check if the given position is a valid selection. Throw an exception otherwise
	 */
	virtual void CheckSelectionCoords(Position) const;

	/**
	 * Return all the possibilities of movement for the piece on the given square
	 */
	virtual std::vector<Position> oGetPossibilities(Position);

	/**
	 * Overload of oGetPossibilities(Position)
	 * @see oGetPossibilities(Position)
	 */
	virtual std::vector<Position> oGetPossibilities(unsigned int, unsigned int);
	Board oGetBoard() const;
	Piece::Color eGetCurrentPlayer() const;
	Position oGetKingPosition(Piece::Color) const;
	/**
	 * Return mbIsOver
	 */
	virtual bool bIsOver() const;
	bool bIsPlayerInCheck(Piece::Color) const;
    bool bIsPlayerCheckMate(Piece::Color) const;
	bool bIsStaleMate() const;

};

#endif