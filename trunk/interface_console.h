#ifndef __INTERFACE_CONSOLE_H_
#define __INTERFACE_CONSOLE_H_

/**
 * This is an implementation of the display interface.
 * It display the game in text mode, in console, via cout
 * @see class Interface
 */

#include "interface.h"
#include <sstream>
#include <vector>
#include <string>

class InterfaceConsole : public Interface
{
  protected :
	std::stringstream mOs;	// Stream containing the displays

	/**
	 * Constructor
	 */
	InterfaceConsole();

	/**
	 * Destructor
	 */
	virtual ~InterfaceConsole();

  public :
	/**
	 * Implement of Interface::DisplayBoard(const Board &)
	 * Display the board as text (with |, -, lower case letters for black pieces,
	 * and upper case for whites)
	 * @see Interface::DisplayBoard(const Board &)
	 */
	virtual void DisplayBoard(const Board &);

	/**
	 * Implement of Interface::DisplayMessage(std::string strMessage)
	 * Simply displays a message in console
	 * @see Interface::DisplayMessage(std::string strMessage)
	 */
	virtual void DisplayMessage(std::string strMessage);

	/**
	 * Implement of Interface::strGetEntry()
	 * Wait for a keyboard entry from the user.
	 * See the description in class Interface for possible values to return
	 * @see Interface::strGetEntry()
	 */
	virtual std::string strGetEntry();

	/**
	 * Implement of Interface::strGetEditionEntry()
	 * Wait for a keyboard entry from the user in edition mode
	 * See the description in class Interface for possible values to return
	 * @see Interface::strGetEntry()
	 */
	virtual std::string strGetEditionEntry();

	/**
	 * Implement of Interface::DisplayPossibilities(vector<Position>)
	 * Displays a list of coordinates contained in the vector
	 * @see Interface::DisplayPossibilities(vector<Position>)
	 */
	virtual void DisplayPossibilities(std::vector<Position>);

	/**
	 * Implement of Interface::DisplayInCheck(Position)
	 * Simply display a message saying that
	 * the king in the given position is in check
	 * @see Interface::DisplayInCheck(Position)
	 */
	virtual void DisplayInCheck(Position);

	/**
	 * Implement of Interface::DisplayCurrentPlayer(Piece::Color)
	 * Display the player which is the next to play
	 * @see Interface::DisplayCurrentPlayer(Piece::Color)
	 */
	virtual void DisplayCurrentPlayer(Piece::Color);

	/** Implement of Interface::DisplaySelection(Position)
	 * Display the given coordinates as a selected piece
	 * @see Interface::DisplaySelection(Position)
	 */
	virtual void DisplaySelection(Position);

	/**
	 * Implement of Interface::CommitDisplay()
	 * @see Interface::CommitDisplay()
	 */
	virtual void CommitDisplay();

	/**
	 * Implement of Interface::cGetNewPieceType()
	 * Wait for an keyboard entry from the user.
	 * See Interface::cGetNewPieceType() for possible values to return
	 * @see Interface::cGetNewPieceType()
	 */
	virtual char cGetNewPieceType(Piece::Color);

	/**
	 * Implement of Interface::iGetMenuEntry()
	 * Return an entry of the main menu
	 * @see Interface::iGetMenuEntry()
	 */
	virtual int iGetMenuEntry(const std::vector<std::string> &);

	/**
	 * Implement of Interface::cGetPlayerColorChoice()
	 * Return a character specifying a color choice from the user
	 * @see Interface::cGetPlayerColorChoice()
	 */
	virtual char cGetPlayerColorChoice();

	/**
	 * Implement of Interface::DisplayGameOver()
	 * Display a "Game over" message and a complement
	 * @see Interface::DisplayGameOver()
	 */
	virtual void DisplayGameOver(std::string);

	/**
	 * Implement of Interface::strKeyBoardEntry()
	 * Ask the user for a keyboard entry
	 * @see Interface::strKeyboardEntry()
	 */
	virtual std::string strKeyboardEntry(std::string strMessage, std::string strDefaultValue = "");

	/**
	 * Implement of Interface::poGetInstance()
	 * @see Interface::poGetInstance()
	 */
	static Interface * poGetInstance();
};

#endif