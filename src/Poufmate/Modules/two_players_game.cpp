#include "two_players_game.h"

#include "Core/board.h"
#include "Pieces/piece.h"
#include "Interface/interface.h"
#include "Movements/include_movements.h"
#include <string>

using namespace std;

TwoPlayersGame::TwoPlayersGame(Interface * poInterface) : Game(poInterface, Module::MT_GAME)
{
}

TwoPlayersGame::TwoPlayersGame(const Board & oBoard, Interface * poInterface) : Game(oBoard, poInterface, Module::MT_GAME)
{
}

TwoPlayersGame::~TwoPlayersGame()
{
}

Entry::ENTRY_COMMAND TwoPlayersGame::Run()
{
	try
	{
		if(!mpoInterface)
			throw exception("The interface is not defined");

		Movement * poNextMove = NULL;	// The next move

		Entry::ENTRY_COMMAND eCommand;

		while(!bIsOver())
		{
			try
			{
				/* Select a piece or execute a command */
				Entry oEntry = mpoInterface->oGetEntry();

				if(oEntry.bIsCommand())
				{
					eCommand = oEntry.eGetCommand();

					if(eCommand == Entry::EC_NONE);			// Do nothing
					/* Cancel last move */
					else if(eCommand == Entry::EC_CANCEL_MOVE)
					{
						if(mpoSelectedPosition)
							mpoSelectedPosition = NULL;
						else
						{
							CancelLastMove();
							SwitchPlayer();
						}
					}
					else
						return eCommand;
				}
				/*Move the piece or execute a command*/
				else
				{
					if(oEntry.bIsPiece())
						throw exception("Invalid entry type : piece");

					if(!poGetSelectedPosition())
					{
						Position oPos(oEntry.oGetPos());

						if(moBoard.bIsSquareEmpty(oPos))
							throw exception("That square is empty !");
						else if(moBoard.eGetSquareColor(oPos) != meCurrentPlayer)
							throw exception("That piece does not belong to you !");

						SetSelectedPosition(oPos);
					}
					else
					{
						Position oPos1(*poGetSelectedPosition());
						Position oPos2(oEntry.oGetPos());

						if(oPos1 == oPos2)
							mpoSelectedPosition = NULL;
						else
						{
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
								poNextMove = new Promotion(oPos1, oPos2, mpoInterface->eGetNewPieceType(meCurrentPlayer));
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

							mpoSelectedPosition = NULL;
							SwitchPlayer();	// Next player

							/* If the player is checkmate, display a message and stop the game */
							if(bIsCheckMate(meCurrentPlayer))
							{
								(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteCheckMate : mbIsBlackCheckMate) = true;
								mbIsOver = true;
							}
							else if(bIsGameInStaleMate())
							{
								mbIsStaleMate = true;
								mbIsOver = true;
							}
							else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
								(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = true;

							RefreshCheckBooleans();
						}
					}
				}
			}
			catch(exception & e)
			{
				mpoInterface->DisplayMessage(e.what());	// Display the error message
				mpoSelectedPosition = NULL;
			}
		}

		if(mbIsBlackCheckMate || mbIsWhiteCheckMate)
		{
			string strGameOver = mbIsBlackCheckMate ? "Black" : "White";
			strGameOver += " player is check mate ! Game over.";
			eCommand = mpoInterface->GameOver(strGameOver);
		}
		else if(mbIsStaleMate)
			eCommand = mpoInterface->GameOver("It's a stale !");

		return eCommand;
	}		
	catch(exception & e)
	{
		cout << __FILE__ << ":" << __LINE__ << endl;
		throw e;
	}
}
