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
    Piece::Color meNewPieceColor;
    Piece::PieceType meNewPieceType;
	bool bIsPieceSelection(std::string);
	bool bIsCoordinates(std::string);
	bool bIsCommand(std::string);
	void DisplaySelectedPiece();
	virtual void DisplayEditionCommands();
	void DisplayBoard(const Board & oBoard);
	void DisplayMessage(std::string strMessage);
	std::string strGetEntry();
	void DisplayPossibilities(std::vector<Position> oPossibilities);
	void DisplayCurrentPlayer(Piece::Color eCurrentPlayer);
	void DisplayGameOver(std::string strMessage = "");

  public :
    InterfaceConsole(struct Interface::stExportedMethods);
	virtual ~InterfaceConsole();
    virtual void Pause();
	virtual void DisplayGame(const Game &);
	virtual GameEntry oGetGameEntry(Game & poGame);
	virtual EditionEntry oGetEditionEntry(const GameEdition &);
	virtual std::string strGetIPEntry();
	virtual std::string strGetPortEntry();
	virtual void AddMessage(std::string);

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
};

#endif