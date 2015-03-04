#ifndef __INTERFACE_CONSOLE_H_
#define __INTERFACE_CONSOLE_H_

/**
 * This is an implementation of the display interface.
 * It display the game in text mode, in console, via cout
 * @see class Interface
 */

#include "Interface/interface.h"
#include <sstream>
#include <vector>
#include <string>

class InterfaceConsole : public Interface
{
	/**
	 * Implemented Interface::methods
	 */
	virtual int iGetMenuEntry(const std::vector<std::string> oMenu);
	virtual void DisplayMessage(const std::string strMessage);
	virtual Entry oGetEntry();
	virtual std::string strGetIPEntry();
	virtual std::string strGetPortEntry();
	virtual Piece::PIECE_TYPE cGetNewPieceType(const Piece::PIECE_COLOR);
	virtual Piece::PIECE_COLOR cGetPlayerColorChoice();
	virtual Entry::ENTRY_COMMAND GameOver(std::string strMessage);
	virtual ~InterfaceConsole();

	/**
	 * Specific methods
	 */
	std::string strGetEntry();
	void DisplayModule(const Module * oModule);
	void DisplayBoard(const Board & oBoard);
	void DisplayCurrentPlayer(Piece::PIECE_COLOR eCurrentPlayer);
	void DisplayHelp();
};

#endif