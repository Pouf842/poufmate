#include "two_players_game.h"
#include "board.h"
#include "piece.h"
#include "include_movements.h"
#include "interface.h"
#include <string>

using namespace std;

TwoPlayersGame::TwoPlayersGame(Interface * poInterface) : Game(poInterface)
{
}

TwoPlayersGame::TwoPlayersGame(const Board & oBoard, Interface * poInterface) : Game(oBoard, poInterface)
{
}

TwoPlayersGame::~TwoPlayersGame()
{
}

std::string TwoPlayersGame::Run()
{
	if(!mpoInterface)
		throw exception("The interface is not defined");

	Movement * poNextMove = NULL;	// The next move

	while(!bIsOver())
	{
		try
		{
			GameEntry oEntry = mpoInterface->oGetGameEntry(*this);
			
			if(oEntry.bIsCommand())
			{
				string strEntry = oEntry.strGetCommand();

				if(strEntry == "");			// Do nothing
				else if(strEntry == "x")
					mbIsOver = true;		// Stop the game
				/* Cancel last move */
				else if(strEntry == "c")
				{
					CancelLastMove();
					SwitchPlayer();
				}
				else if(strEntry == "r")
					return "r";
				else if(strEntry == "q")
					return "q";
			}
			/* Select a piece or make a move */
			else
			{
				Position oPos1(oEntry.oGetPos1());
				Position oPos2(oEntry.oGetPos2());

				/* Determinate the movement's type and update poNextMove */
				if(bIsCastling(oPos1, oPos2))	// Castling
				{
					if(bIsInCheck(meCurrentPlayer))
						throw exception("Castling is not allowed if you're in check");

					if(!bIsCastlingPathOk(oPos1, oPos2))
						throw exception("Your king would be in check during castling");

					poNextMove = new CastlingMove(oPos1, oPos2);
				}
				else if(bIsPromotion(oPos1, oPos2))	// Promotion
				{
					char cNewPieceType = mpoInterface->cGetNewPieceType(meCurrentPlayer);
					poNextMove = new Promotion(oPos1, oPos2, cNewPieceType);
				}
				else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())	// First move
					poNextMove = new FirstMove(oPos1, oPos2);
				else if(bIsEnPassantOk(oPos1, oPos2))
					poNextMove = new EnPassant(oPos1, oPos2, (*moHistory.rbegin()));
				else
					poNextMove = new Movement(oPos1, oPos2);	// Other move

				/* Execute the move */
				ExecuteMovement(poNextMove);

				/* If the move puts the player in check, it is not valid */
				if(bIsInCheck(meCurrentPlayer))
				{
					CancelLastMove();
					throw exception("That move puts you in check");
				}

				(meCurrentPlayer == Piece::WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = false;    // if the move was authorized, player is no longer in check

				SwitchPlayer();	// Next player
			}

			/* If the player is checkmate, display a message and stop the game */
			if(bIsCheckMate(meCurrentPlayer))
				(meCurrentPlayer == Piece::WHITE ? mbIsWhiteCheckMate : mbIsBlackCheckMate) = true;
			else if(bIsGameInStaleMate())
				mbIsStaleMate = true;
			else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
				(meCurrentPlayer == Piece::WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = true;
		}
		catch(exception & e)
		{
			mpoInterface->AddMessage(e.what());	// Display the error message
		}
	}

	return "";
}
