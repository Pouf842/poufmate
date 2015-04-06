#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

#include "module.h"
#include "Core\board.h"
#include "Core\position.h"

class Movement;
class Controller;

class Game : public Module
{
  protected :
	std::vector<Movement*> moHistory;	// History of moves
	Piece::PIECE_COLOR meCurrentPlayer;		// Current playing player
	Position moKings[2];				// Positions of the two kings (usefull for check and checkmate verification)
	Position moSelectedPosition;		// Selected square
    Controller * mpoController;

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
	virtual bool bIsCastling(Position, Position) const;

	/**
	 * Check if the given movement is correct
	 */
	virtual bool bIsMovementCorrect(Position, Position) const;

	/**
	 * Check if the player of the given color is in check
	 */
	virtual bool bIsInCheck(Piece::PIECE_COLOR) const;

	/**
	 * Check if the player of the given color is mate
	 */
	virtual bool bIsCheckMate(Piece::PIECE_COLOR);

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
	virtual bool bIsEnPassantOk(Position oPos1, Position oPos2) const;

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

	
	/**
	 * Set the selected position
	 */
	void SetSelectedPosition(Position);

	void RefreshCheckBooleans();

  public :

	/**
	 * Basic constructor
	 */
	Game(Controller * poInterface = NULL, Module::MODULE_TYPE = Module::MT_NONE);

    virtual void GrabPiece(const Position &);
    virtual void DropPiece(const Position &);
    virtual void SelectNewPiece();

	/**
	 * Constructor with a specified board
	 * Throw exception if there is more or less
	 * than 1 king for each player
	 */
    Game(const Board &, Controller * poInterface = NULL, Module::MODULE_TYPE = Module::MT_NONE);

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

	Piece::PIECE_COLOR eGetCurrentPlayer() const;
	Position oGetKingPosition(Piece::PIECE_COLOR) const;
	/**
	 * Return mbIsOver
	 */
	virtual bool bIsOver() const;
	bool bIsPlayerInCheck(Piece::PIECE_COLOR) const;
    bool bIsPlayerCheckMate(Piece::PIECE_COLOR) const;
	bool bIsStaleMate() const;
	
	/**
	 * Get the previously selected position
	 */
	Position oGetSelectedPosition() const;
};

#endif