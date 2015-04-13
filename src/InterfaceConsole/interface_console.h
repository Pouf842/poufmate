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
protected:
    Board moBoard;
    Position moSelectedPosition;
    unsigned int muLastPercent;
    bool mbStop;

public :
    InterfaceConsole(Controller *);
    virtual ~InterfaceConsole();

	/**
	 * Implemented Interface::methods
	 */
    virtual void Run();
    virtual void SetMenuState(std::vector<std::string> const * = NULL);
    virtual void SetGameState(const Board &);
    virtual void PieceMoved(Piece *, const Position &);
    virtual void PieceRemoved(Piece *);
    virtual void PieceAdded(Piece *, const Position &);
    virtual void PieceEatPiece(Piece *, Piece *);
    virtual Piece::PIECE_TYPE eGetPromotionNewPiece();
    virtual void DisplayMessage(std::string);
    virtual void Quit();

	/**
	 * Specific methods
	 */
	std::string strGetEntry();
	//void DisplayModule(const Module * oModule);
	void DisplayBoard();
	//void DisplayCurrentPlayer();
	//void DisplayPlayerInCheck();
	//void DisplayEditionSelection();
	void DisplayHelp();
	//Entry eGetSelectionPieceEntry(std::string);*/
};

#endif