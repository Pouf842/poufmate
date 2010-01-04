#include "two_players_game.h"
#include "board.h"
#include "piece.h"
#include "first_move.h"
#include "castling_move.h"
#include "promotion.h"
#include "interface.h"

#include <iostream>
#include <string>

using namespace std;

TwoPlayersGame::TwoPlayersGame()
{
	/* Initialise the positions of the kings */
	moKings[Piece::WHITE] = Position(7, 4);	
	moKings[Piece::BLACK] = Position(0, 4);	

	meCurrentPlayer = Piece::WHITE;	// White moves first
	mbIsOver = false;
}

TwoPlayersGame::TwoPlayersGame(const Board & oBoard)
{
	moBoard = oBoard;

	Position oWhiteKing;
	Position oBlackKing;

	bool bWhiteFounded = false;
	bool bBlackFounded = false;

	for(unsigned int i = 0; i < 8 && (!bWhiteFounded || !bBlackFounded); ++i)
	{
		for(unsigned int j = 0; j < 8 && (!bWhiteFounded || !bBlackFounded); ++j)
		{
			if(!moBoard.bIsSquareEmpty(i, j))
			{
				Piece * poCurrentPiece = moBoard.poGetPiece(i, j);

				if(poCurrentPiece->eGetType() == Piece::KING)
				{
					moKings[poCurrentPiece->eGetColor()] = Position(i, j);

					if(poCurrentPiece->eGetColor() == Piece::WHITE)
						bWhiteFounded = true;
					else
						bBlackFounded = true;
				}
			}
		}
	}

	meCurrentPlayer = Piece::WHITE;	// White moves first
	mbIsOver = false;
}

TwoPlayersGame::~TwoPlayersGame()
{
}

void TwoPlayersGame::Run(Interface * poInterface)
{
	if(!poInterface)
		throw exception("The interface is not defined");

	string strEntry = "";	// The command the player will entry

	moBoard.Init();
	Movement::SetBoard(&moBoard);

	poInterface->DisplayBoard(moBoard);
	poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	poInterface->CommitDisplay();
	
	Movement * poNextMove = NULL;	// The next move

	while(!bIsOver())
	{
		try
		{
			strEntry = poInterface->strGetEntry();	// Getting the next command
			
			if(strEntry == "");			// Do nothing
			else if(strEntry == "x")
				mbIsOver = true;		// Stop the game
			/* Cancel last move */
			else if(strEntry == "c")
			{
				CancelLastMove();
				moSelection.Empty();
				SwitchPlayer();
			}
			/* Select a piece or make a move */
			else if(strEntry[strEntry.size() - 1] != '?')
			{
				Position oEntry(strEntry);

				/* Select a piece */
				if(moSelection.bIsEmpty())
				{
					CheckSelectionCoords(oEntry);
					moSelection = oEntry;
				}
				/* Try to make a move */
				else
				{
					if(moSelection != oEntry)	// Same square --> no move
					{
						/* Determinate the movement's type and update poNextMove */
						if(bIsCastling(moSelection, oEntry))	// Castling
						{
							if(bIsInCheck(meCurrentPlayer))
								throw exception("Castling is not allowed if you're in check");

							if(!bIsCastlingPathOk(moSelection, oEntry))
								throw exception("Your king would be in check during castling");

							poNextMove = new CastlingMove(moSelection, oEntry);
						}
						else if(bIsPromotion(moSelection, oEntry))	// Promotion
						{
							char cNewPieceType = poInterface->cGetNewPieceType(meCurrentPlayer);
							poNextMove = new Promotion(moSelection, oEntry, cNewPieceType);
						}
						else if(moBoard.poGetPiece(moSelection)->bIsFirstMove())	// First move
							poNextMove = new FirstMove(moSelection, oEntry);
						else
							poNextMove = new Movement(moSelection, oEntry);	// Other move

						/* Execute the move */
						moHistory.push_back(poNextMove);
						poNextMove->Execute();

						/* Update the king position if necessary */
						if(moBoard.poGetPiece(oEntry)->eGetType() == Piece::KING)
							moKings[moBoard.eGetSquareColor(oEntry)] = oEntry;

						/* If the move puts the player in check, it is not valid */
						if(bIsInCheck(meCurrentPlayer))
						{
							CancelLastMove();
							throw exception("That move puts you in check");
						}

						SwitchPlayer();	// Next player
					}
					
					moSelection.Empty();	// No selection
				}
			}

			/* Display the game */
			poInterface->DisplayBoard(moBoard);

			/* If the player is checkmate, display a message and stop the game */
			if(strEntry == "x")	// Display a message
				poInterface->DisplayMessage("Game over !");
			else if(bIsCheckMate(meCurrentPlayer))
			{
				mbIsOver = true;
				string strMessage = "The ";
				strMessage += (meCurrentPlayer == Piece::WHITE ? "white" : "black");
				strMessage += " player is checkmate !";

				poInterface->DisplayMessage(strMessage);
				poInterface->DisplayMessage("Game over !");
			}
			else if(bIsGameInStaleMate())
			{
				mbIsOver = true;
				poInterface->DisplayMessage("This is a stalemate");
			}
			else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
			{
				poInterface->DisplayInCheck(moKings[meCurrentPlayer]);
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
			}
			else
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	
			/* If asked (strEntry ends with '?'), display the possibilities for a specified piece */
			if(strEntry.size() != 0
			&& strEntry[strEntry.size() - 1] == '?')
				poInterface->DisplayPossibilities(oGetPossibilities(strEntry.substr(0, 2)));

			/* If there is a selected piece, display it */
			if(!moSelection.bIsEmpty())
				poInterface->DisplaySelection(moSelection);
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());	// Display the error message
		}

		poInterface->CommitDisplay();	// Commit the displays
	}
	
	strEntry = poInterface->strGetEntry();	// Wait for the player to read the message before quiting
	return;
}
