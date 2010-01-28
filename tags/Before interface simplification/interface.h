#ifndef __INTERFACE_H_
#define __INTERFACE_H_

/**
 * Interface User/Computer.
 * Contains all the possibles interactions of the user with the game
 * Derivate it to make your own type of display for the game.
 * It's a singleton. Each game should be display only once.
 * The displays are pushed, then commited by a call to CommitDisplay
 */

#include "board.h"
#include "position.h"
#include <string>
#include <vector>

class Interface
{
  protected :
	static Interface * mpoInstance;	// The unique instance of the class

	/**
	 * Destructor
	 */
	virtual ~Interface();

  public :

	/**
	 * Display the board
	 */
	virtual void DisplayBoard(const Board &) = 0;

	/**
	 * Display any message
	 */
	virtual void DisplayMessage(std::string strMessage) = 0;

	/**
	 * Return the command given by the user.
	 * Those are the possibles values to return :
	 * "x" to quit the game
	 * "c" to cancel the last move
	 * "XY", where X and Y are the coordinates of a piece on the board (X is vertical, Y is horizontal) for a selection
	 * "XY?" to get the possibile moves of the piece in XY on the board
	 */
	virtual std::string strGetEntry() = 0;

	/**
	 * Return the command given by the user in edition module.
	 * Those are the possibles value to return :
	 * "x" to quit the edition mode
	 * "1" to launch a one player party
	 * "2" to launch a two player party
	 * "3" to launch a two player lan party
	 * "R", "N", "B", "Q", "K", "P", and the same in lower case
	 * to choose the type of the next piece to put on board
	 * "XY" the coordinates of a square, where to put a piece of the choosen type
	 */
	virtual std::string strGetEditionEntry() = 0;

	/**
	 * Display all the possibilities of move contained in the vector
	 */
	virtual void DisplayPossibilities(std::vector<Position>) = 0;

	/**
	 * Display a square as a piece in check
	 */
	virtual void DisplayInCheck(Position) = 0;

	/**
	 * Display the color of the current player
	 */
	virtual void DisplayCurrentPlayer(Piece::Color) = 0;

	/**
	 * Display the selected piece
	 */
	virtual void DisplaySelection(Position) = 0;

	/**
	 * Commit all displays pushed since the last commit
	 */
	virtual void CommitDisplay() = 0;

	/**
	 * Return a type of piece (for pawn promotion)
	 * Possible values to return are :
	 * R or r for a rook
	 * N or n for a knight
	 * B or b for a bishop
	 * Q or q for a queen
	 * P or p for a pawn
	 */
	virtual char cGetNewPieceType(Piece::Color) = 0;

	/**
	 * Return an entry of the main menu
	 */
	virtual int iGetMenuEntry(const std::vector<std::string> &) = 0;

	/**
	 * Return player color as a character
	 * ('W', or 'w' for white, and 'B' or 'b' for black)
	 */
	virtual char cGetPlayerColorChoice() = 0;

	/**
	 * Display a "Game over" message, followed by a specified complement
	 */
	virtual void DisplayGameOver(std::string) = 0;

	/**
	 * Ask the user for a keyboard entry with the specified message (strMessage)
	 * and eventually a default value
	 */
	virtual std::string strKeyboardEntry(std::string strMessage, std::string strDefaultValue = "") = 0;

	/**
	 * Return the unique instance of the class
	 */
	static Interface * poGetInstance() {}

	/**
	 * Free the instance of the class
	 */
	static void FreeInstance()
	{
		if(mpoInstance)
		{
			delete mpoInstance;
			mpoInstance = NULL;
		}
	}
};

#endif
