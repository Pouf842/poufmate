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

GameEdition::GameEdition(Interface * poInterface)
{
	SetInterface(poInterface);
}

GameEdition::~GameEdition()
{
}

Board GameEdition::oGetBoard() const
{
	return moBoard;
}

void GameEdition::Run()
{
	bool bQuit = false;

	while(!bQuit)
	{
		try
		{
			EditionEntry oEntry = mpoInterface->oGetEditionEntry(*this);

			/* If the entry is 1 char long, it's a command */
			if(oEntry.bIsCommand())
			{
				string strEntry = oEntry.strGetCommand();

				if(strEntry == "x")	// "x" quit the edition mode
					bQuit = true;
				else if(strEntry == "1")	// "1" launch a one player party with the current board
				{
					OnePlayerGame oGame(moBoard, mpoInterface);
					oGame.Run();
				}
				else if(strEntry == "2")	// "2" launch a two player party with the current board
				{
					TwoPlayersGame oGame(moBoard, mpoInterface);
					oGame.Run();
				}
			}
			else
			{
				Position oPos = oEntry.oGetPosition();

				/* Deleting a piece : if it is a king, update moKings */
				if(oEntry.eGetPieceType() != Piece::KING		// If the new piece type is not KING
				&& !moBoard.bIsSquareEmpty(oPos)				// and the choosen square is not empty
				&& moBoard.eGetSquareType(oPos) == Piece::KING)	// and it contains a king
					moKingAlreadyThere[moBoard.eGetSquareColor(oPos)].Empty();	// Update moKings

				if(moBoard.poGetPiece(oPos))			// If the square is not empty
					delete moBoard.poGetPiece(oPos);	// Empty it

				Piece * poNewPiece = 0;

				/* Creating the new piece */
				switch(oEntry.eGetPieceType())
				{
				  case Piece::PAWN :
					  poNewPiece = new Pawn(oEntry.eGetPieceColor());
					break;
				  case Piece::ROOK :
					poNewPiece = new Rook(oEntry.eGetPieceColor());
					break;
				  case Piece::KNIGHT :
					poNewPiece = new Knight(oEntry.eGetPieceColor());
					break;
				  case Piece::BISHOP :
					poNewPiece = new Bishop(oEntry.eGetPieceColor());
					break;
				  case Piece::QUEEN :
					poNewPiece = new Queen(oEntry.eGetPieceColor());
					break;
				  case Piece::KING :
					poNewPiece = new King(oEntry.eGetPieceColor());
					break;
				  case Piece::NONE :
				  default :
					break;
				}

				/* If it is a king, check the number of kings, and update moKings */
				if(oEntry.eGetPieceType() == Piece::KING)
				{
					if(!moKingAlreadyThere[oEntry.eGetPieceColor()].bIsEmpty())
						throw exception("You already have a king of that color on the board");
					else
						moKingAlreadyThere[oEntry.eGetPieceColor()] = oPos;	// Update of moKings
				}

				moBoard.SetPiece(oPos, poNewPiece);	// Place the piece
			}
		}
		catch(exception & e)
		{
			mpoInterface->AddMessage(e.what());
		}
	}
}