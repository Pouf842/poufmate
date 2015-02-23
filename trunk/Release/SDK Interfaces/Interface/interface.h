#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#define GET_INTERFACE_FUNCTION "poGetInterface"
/**
 * Interface User/Computer.
 * Contains all the possibles interactions of the user with the game
 * Derivate it to make your own type of display for the game.
 * It's a singleton. Each game should be display only once.
 * The displays are pushed, then commited by a call to CommitDisplay
 */

#include <vector>
#include "Modules\module.h"
#include "entry.h"

class Module;

extern "C" __declspec(dllexport) Interface * poGetInterface();

class Interface
{
protected :
	const Module * mpoModule;
public :
	/**
	 * Set the board to be displayed
	 */
	virtual void setModule(const Module * poModule);

	/**
	 * Returns the user's choice
	 * among the oMenu menu provided as an index
	 */
	virtual int iGetMenuEntry(const std::vector<std::string> oMenu) = 0;

	/**
	 * Returns the user's last input.
	 * Can be a command, or a selected position
	 */
	virtual Entry oGetEntry() = 0;

	/**
	 * Displays a message
	 */
	virtual void DisplayMessage(const std::string strMessage) = 0;

	/**
	 * Returns an IP address provided by the user
	 * for LAN games
	 */
	virtual std::string strGetIPEntry() = 0;
	
	/**
	 * Returns a port provided by the user
	 * for LAN games
	 */
	virtual std::string strGetPortEntry() = 0;

	/**
	 * Return a type of piece (for pawn promotion)
	 */
	virtual Piece::PIECE_TYPE cGetNewPieceType(const Piece::PIECE_COLOR) = 0;
	
	/**
	 * Returns a piece color
	 */
	virtual Piece::PIECE_COLOR cGetPlayerColorChoice() = 0;

	/**
	 * Game is over ! Act consequently, please,
	 * and return a command, but EC_CANCEL_MOVE
	 */
	virtual Entry::ENTRY_COMMAND GameOver(std::string strMessage) = 0;

	virtual ~Interface() {};
};

#endif
