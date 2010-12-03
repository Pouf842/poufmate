#ifndef __INTERFACE_H_
#define __INTERFACE_H_

/**
 * Interface User/Computer.
 * Contains all the possibles interactions of the user with the game
 * Derivate it to make your own type of display for the game.
 * It's a singleton. Each game should be display only once.
 * The displays are pushed, then commited by a call to CommitDisplay
 */

//#ifdef __INTERFACEDLL_
//    #define __declspec(dllexport) IMPORT_EXPORT
//#else
//    #define __declspec(dllimport) IMPORT_EXPORT
//#endif

#include "board.h"
#include "game.h"
#include "game_edition.h"
#include "game_entry.h"
#include "edition_entry.h"
#include "position.h"
#include <string>
#include <vector>

class Game;
class GameEdition;

class /*IMPORT_EXPORT*/ Interface
{
  public :
    struct stExportedMethods
    {
        Piece::Color (Board::*pBoardEGetSquareColor)(Position) const;
        Piece::PieceType (Board::*pBoardEGetSquareType)(Position) const;
        bool (Board::*pBoardBIsSquareEmpty)(Position) const;

        bool (Game::*pGameBIsPlayerInCheck)(Piece::Color) const;
        Board (Game::*pGameOGetBoard)(void) const;
        Position (Game::*pGameOGetKingPosition)(Piece::Color) const;
        Piece::Color (Game::*pGameEGetCurrentPlayer)() const;

        Board (GameEdition::*pGameEditionOGetBoard)() const;
    };

	/**
	 * Pause the program in wait of an entry from the user
	 * to continue
	 */
	virtual void Pause() = 0;
	virtual void DisplayGame(const Game &) = 0;
	virtual GameEntry oGetGameEntry(Game &) = 0;
	virtual void AddMessage(std::string);
	virtual EditionEntry oGetEditionEntry(const GameEdition &) = 0;
	virtual std::string strGetIPEntry() = 0;
	virtual std::string strGetPortEntry() = 0;

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
	 * Return the unique instance of the class
	 */
    static Interface * poGetInstance(struct stExportedMethods) {return NULL;};

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
    
  protected :
    struct stExportedMethods mExportedMethods;
	static Interface * mpoInstance;	// The unique instance of the class
	std::vector<std::string> moMessages;

	/**
	 * Destructor
	 */
	virtual ~Interface();
};

#endif
