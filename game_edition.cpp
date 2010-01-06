#include "game_edition.h"
#include "two_players_game.h"
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

			if(strEntry.size() == 1)
			{
				if(strEntry == "x")
					bQuit = true;
				else if(strEntry == "l")
				{
					TwoPlayersGame oGame(moBoard);
					oGame.Run(poInterface);
				}
				else
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
			else if(strEntry.size() == 2)
			{
				if(meNewPieceType == Piece::NONE
				&& !moBoard.bIsSquareEmpty(strEntry)
				&& moBoard.poGetPiece(strEntry)->eGetType() == Piece::KING)
					moKingAlreadyThere[moBoard.eGetSquareColor(strEntry)].Empty();

				if(moBoard.poGetPiece(strEntry))
					delete moBoard.poGetPiece(strEntry);

				Piece * poNewPiece = 0;

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

				if(meNewPieceType == Piece::KING)
				{
					if(!moKingAlreadyThere[meNewPieceColor].bIsEmpty())
					{
						poInterface->DisplayInCheck(moKingAlreadyThere[meNewPieceColor]);
						throw exception("You already have a king of that color on the board");
					}
					else
						moKingAlreadyThere[meNewPieceColor] = strEntry;
				}

				moBoard.SetPiece(strEntry, poNewPiece);
			}

			poInterface->DisplayBoard(moBoard);

			poInterface->CommitDisplay();
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
			poInterface->CommitDisplay();
		}
	}
}