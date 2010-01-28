#include "game_edition.h"
#include "two_players_game.h"
#include "one_player_game.h"
#include <string>
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

using namespace std;

GameEdition::GameEdition() : meNewPieceType(Piece::NONE), meNewPieceColor(Piece::WHITE)
{
}

GameEdition::~GameEdition()
{
}

void GameEdition::Run(Interface * poInterface)
{
	bool bQuit = false;
	string strEntry = "";

	poInterface->DisplayBoard(moBoard);
	poInterface->CommitDisplay();

	while(!bQuit)
	{
		try
		{
			strEntry = poInterface->strGetEditionEntry();

			/* If the entry is 1 char long, it's a command */
			if(strEntry.size() == 1)
			{
				if(strEntry == "x")	// "x" quit the edition mode
					bQuit = true;
				else if(strEntry == "1")	// "1" launch a one player party with the current board
				{
					OnePlayerGame oGame(moBoard);
					oGame.Run(poInterface);
				}
				else if(strEntry == "2")	// "2" launch a two player party with the current board
				{
					TwoPlayersGame oGame(moBoard);
					oGame.Run(poInterface);
				}
				else	// Choice of a new piece type
				{
					switch(strEntry[0])
					{
					  case 'P' :
						meNewPieceType = Piece::PAWN;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'R' :
						meNewPieceType = Piece::ROOK;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'N' :
						meNewPieceType = Piece::KNIGHT;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'B' :
						meNewPieceType = Piece::BISHOP;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'Q' :
						meNewPieceType = Piece::QUEEN;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'K' :
						meNewPieceType = Piece::KING;
						meNewPieceColor = Piece::WHITE;
						break;
					  case 'p' :
						meNewPieceType = Piece::PAWN;
						meNewPieceColor = Piece::BLACK;
						break;
					  case 'r' :
						meNewPieceType = Piece::ROOK;
						meNewPieceColor = Piece::BLACK;
						break;
					  case 'n' :
						meNewPieceType = Piece::KNIGHT;
						meNewPieceColor = Piece::BLACK;
						break;
					  case 'b' :
						meNewPieceType = Piece::BISHOP;
						meNewPieceColor = Piece::BLACK;
						break;
					  case 'q' :
						meNewPieceType = Piece::QUEEN;
						meNewPieceColor = Piece::BLACK;
						break;
					  case 'k' :
						meNewPieceType = Piece::KING;
						meNewPieceColor = Piece::BLACK;
						break;
					  case '#' :
						meNewPieceType = Piece::NONE;
					  default :
						break;
					}
				}
			}
			else if(strEntry.size() == 2)	// The entry is a position
			{
				/* Deleting a piece : if it is a king, update moKings */
				if(meNewPieceType == Piece::NONE					// If the new piece type is NONE (empty square)
				&& !moBoard.bIsSquareEmpty(strEntry)				// and the choosen square is not empty
				&& moBoard.eGetSquareType(strEntry) == Piece::KING)	// and it contains a king
					moKingAlreadyThere[moBoard.eGetSquareColor(strEntry)].Empty();	// Update moKings

				if(moBoard.poGetPiece(strEntry))			// If the square is not empty
					delete moBoard.poGetPiece(strEntry);	// Empty it

				Piece * poNewPiece = 0;

				/* Creating the new piece */
				switch(meNewPieceType)
				{
				  case Piece::PAWN :
					poNewPiece = new Pawn(meNewPieceColor);
					break;
				  case Piece::ROOK :
					poNewPiece = new Rook(meNewPieceColor);
					break;
				  case Piece::KNIGHT :
					poNewPiece = new Knight(meNewPieceColor);
					break;
				  case Piece::BISHOP :
					poNewPiece = new Bishop(meNewPieceColor);
					break;
				  case Piece::QUEEN :
					poNewPiece = new Queen(meNewPieceColor);
					break;
				  case Piece::KING :
					poNewPiece = new King(meNewPieceColor);
					break;
				  case Piece::NONE :
				  default :
					break;
				}

				/* If it is a king, check the number of kings, and update moKings */
				if(meNewPieceType == Piece::KING)
				{
					if(!moKingAlreadyThere[meNewPieceColor].bIsEmpty())
					{
						poInterface->DisplayInCheck(moKingAlreadyThere[meNewPieceColor]);
						throw exception("You already have a king of that color on the board");
					}
					else
						moKingAlreadyThere[meNewPieceColor] = strEntry;	// Update of moKings
				}

				moBoard.SetPiece(strEntry, poNewPiece);	// Place the piece
			}

			poInterface->DisplayBoard(moBoard);
			poInterface->CommitDisplay();
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
			poInterface->DisplayBoard(moBoard);
			poInterface->CommitDisplay();
		}
	}
}