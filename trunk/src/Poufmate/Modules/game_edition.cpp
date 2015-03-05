#include "game_edition.h"
#include "two_players_game.h"
#include "one_player_game.h"
#include <string>
#include "Pieces/pawn.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"
#include "Pieces/bishop.h"
#include "Pieces/queen.h"
#include "Pieces/king.h"

using namespace std;

GameEdition::GameEdition(Interface * poInterface)
{
	meType = Module::MT_EDITION;
	meSelectedPieceType = Piece::PT_NONE;
	meSelectedPieceColor = Piece::PC_WHITE;
	SetInterface(poInterface);
}

GameEdition::~GameEdition()
{
}

void GameEdition::Initialize()
{
	moBoard = Board();
}

Entry::ENTRY_COMMAND GameEdition::Run()
{
	bool bQuit = false;

	Entry::ENTRY_COMMAND eCommand;

	while(!bQuit)
	{
		try
		{
			//EditionEntry oEntry = mpoInterface->oGetEditionEntry(*this);
			Entry oEntry = mpoInterface->oGetEntry();

			/* If the entry is 1 char long, it's a command */
			if(oEntry.bIsCommand())
			{
				eCommand = oEntry.eGetCommand();

				if(eCommand == Entry::EC_STOP_GAME
				|| eCommand == Entry::EC_QUIT_GAME)	// "x" quit the edition mode
					bQuit = true;
				else if(eCommand == Entry::EC_ONE_PLAYER_GAME)	// "1" launch a one player party with the current board
				{
					OnePlayerGame oGame(moBoard, mpoInterface);
					mpoInterface->setModule(&oGame);
					oGame.Run();
					mpoInterface->setModule(this);
				}
				else if(eCommand == Entry::EC_TWO_PLAYERS_GAME)	// "2" launch a two player party with the current board
				{
					TwoPlayersGame oGame(moBoard, mpoInterface);
					mpoInterface->setModule(&oGame);
					oGame.Run();
					mpoInterface->setModule(this);
				}
			}
			else
			{
				if(oEntry.bIsPiece())
				{
					meSelectedPieceType  = oEntry.eGetPieceType();
					meSelectedPieceColor = oEntry.eGetPieceColor();
				}
				else
				{
					Position oPos = oEntry.oGetPos();

					/* If it is a king, check the number of kings, and update moKings */
					if(meSelectedPieceType == Piece::PT_KING)
					{
						if(!moKingAlreadyThere[meSelectedPieceColor].bIsEmpty())
						{
							delete moBoard.poGetPiece(moKingAlreadyThere[meSelectedPieceColor]);	// Empty it
							moBoard.SetPiece(moKingAlreadyThere[meSelectedPieceColor], NULL);
							moKingAlreadyThere[meSelectedPieceColor].Empty();
						}


						moKingAlreadyThere[meSelectedPieceColor] = oPos;	// Update of moKings
					}

					/* Deleting a piece : if it is a king, update moKings */
					if(!moBoard.bIsSquareEmpty(oPos)					// If the square is not empty
					&&  moBoard.eGetSquareType(oPos) == Piece::PT_KING	// and contains a king
					&& (meSelectedPieceType != Piece::PT_KING || meSelectedPieceColor != moBoard.eGetSquareColor(oPos)))	// and we delete it with another piece
						moKingAlreadyThere[moBoard.eGetSquareColor(oPos)].Empty();	// Update moKings

					if(moBoard.poGetPiece(oPos))			// If the square is not empty
						delete moBoard.poGetPiece(oPos);	// Empty it

					Piece * poNewPiece = 0;

					/* Creating the new piece */
					switch(meSelectedPieceType)
					{
					  case Piece::PT_PAWN :
						  poNewPiece = new Pawn(meSelectedPieceColor);
						break;
					  case Piece::PT_ROOK :
						poNewPiece = new Rook(meSelectedPieceColor);
						break;
					  case Piece::PT_KNIGHT :
						poNewPiece = new Knight(meSelectedPieceColor);
						break;
					  case Piece::PT_BISHOP :
						poNewPiece = new Bishop(meSelectedPieceColor);
						break;
					  case Piece::PT_QUEEN :
						poNewPiece = new Queen(meSelectedPieceColor);
						break;
					  case Piece::PT_KING :
						poNewPiece = new King(meSelectedPieceColor);
						break;
					  case Piece::PT_NONE :
					  default :
						break;
					}

					moBoard.SetPiece(oPos, poNewPiece);	// Place the piece
				}
			}
		}
		catch(exception & e)
		{
			mpoInterface->DisplayMessage(e.what());
		}
	}

	return eCommand;
}