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

TwoPlayersGame::TwoPlayersGame(const Board & oBoard) : moBoard(oBoard)
{
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

void TwoPlayersGame::SwitchPlayer()
{
	meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
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
							char cNewPieceType = poInterface->cGetNewPieceType();
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

void TwoPlayersGame::MovePiece(Position oPos1, Position oPos2)
{
	moBoard.SetPiece(oPos2, moBoard.poGetPiece(oPos1));
	moBoard.SetPiece(oPos1, 0);
}

bool TwoPlayersGame::bIsCastlingPathOk(Position oPos1, Position oPos2)
{
	Piece::Color eColor = moBoard.eGetSquareColor(oPos1);	// Color of the castling player
	bool bFirstMove = moBoard.poGetPiece(oPos1)->bIsFirstMove();	// Keeping it to restore it after the check

	/* For each squares between the king and the finishing square */
	for(unsigned int i = oPos1.mY; i != oPos2.mY; i += (oPos1.mY > oPos2.mY ? -1 : 1))
	{
		Position oPosInter(moKings[eColor].mX, i);	// Intermediate position

		if(moBoard.bIsSquareEmpty(oPosInter))	// If the intermediate square is empty
		{
			MovePiece(moKings[eColor], oPosInter);	// Move the king to the intermediate square
			moKings[eColor] = oPosInter;	// Update the king position

			if(bIsInCheck(eColor))	// If the king is in check, the castling is not possible
			{
				MovePiece(moKings[eColor], oPos1);	// Return the king to its initial position
				moBoard.poGetPiece(moKings[eColor])->SetFirstMove(bFirstMove);	// Restore the bFirstMove boolean of the king
				moKings[eColor] = oPos1;			// Restore the king's position
				return false;
			}
		}
		else
			return false;	// If the square is not empty
	}

	MovePiece(moKings[eColor], oPos1);	// Return the king to its initial position
	moKings[eColor] = oPos1;			// Restore the king's position

	moBoard.poGetPiece(moKings[eColor])->SetFirstMove(bFirstMove);	// Restore the bFirstMove boolean of the king

	return true;	// The castling path is clear
}

bool TwoPlayersGame::bIsPromotion(Position oPos1, Position oPos2) const
{
	Piece * oPiece = moBoard.poGetPiece(oPos1);	// Moving piece

	if(oPiece->eGetType() == Piece::PAWN	// If the piece is a pawn
	&& oPos2.mX == (oPiece->eGetColor() == Piece::WHITE ? 0 : 7))	// and if it reaches the other side of the board (0 for the whites, 7 for the blacks)
		return true;	// It's a promotion
	else
		return false;	// else, it's not
}

bool TwoPlayersGame::bIsCastling(Position oPos1, Position oPos2)
{
	Position oKing = (meCurrentPlayer == Piece::WHITE ? Position(7, 4) : Position(0, 4));	// Side of the board (0 for blacks, 7 for whites)

	if(oPos1 == oKing	// If the piece is a king
	&& oPos1.mX == oPos2.mX	// and the movement is horizontal
	&& (oPos2.mY == oPos1.mY - 2 || oPos2.mY == oPos1.mY + 2))	// and of two squares
		return true;	// It's a castling move
	else
		return false;	// else, it isn't
}

vector<Position> TwoPlayersGame::oGetPossibilities(Position oPos)
{
	vector<Position> oPossibilites;

//	oPossibilites.push_back(oPos);	// The square itself is a possibility

	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos2(i, j);

			if(bIsMovementCorrect(oPos, oPos2))	// If the movement is correct
			{
				try
				{
					/* Determining the type of the movement */
					Movement * poMove = NULL;

					if(bIsCastling(oPos, oPos2))
					{
						if(!bIsCastlingPathOk(oPos, oPos2))
							throw exception("Your king would be in check during castling");
						if(bIsInCheck(moBoard.eGetSquareColor(oPos)))
							throw exception("Castling is not allowed if you're in check");

						poMove = new CastlingMove(oPos, oPos2);
					}
					else if(moBoard.poGetPiece(oPos)->bIsFirstMove())
						poMove = new FirstMove(oPos, oPos2);
					else
						poMove = new Movement(oPos, oPos2);

					/* Executing the movement */
					moHistory.push_back(poMove);

					if(moBoard.poGetPiece(oPos)->eGetType() == Piece::KING)
						moKings[meCurrentPlayer] = oPos2;

					poMove->Execute();

					if(!bIsInCheck(moBoard.eGetSquareColor(oPos2)))	// If the player is not in check, the movement is possible
						oPossibilites.push_back(oPos2);

					CancelLastMove();	// Cancel the movement
				}
				catch(exception &)	// Catching exception for impossible movements
				{
				}
			}
		}
	}

	return oPossibilites;
}

bool TwoPlayersGame::bIsInCheck(Piece::Color eColor) const
{
	Position oKing(moKings[eColor]);	// Position of the player's king

	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);

			// If there is a piece of the opposite color on that square
			if(!moBoard.bIsSquareEmpty(oPos) && moBoard.eGetSquareColor(oPos) != eColor)
			{
				if(bIsMovementCorrect(oPos, oKing))	// And if that piece can capture the king
					return true;					// The player is in check
			}
		}
	}

	return false;
}

bool TwoPlayersGame::bIsCheckMate(Piece::Color ePlayer)
{
	if(!bIsInCheck(ePlayer))	// If the player is not in check, he can't be checkmate
		return false;

	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos1(i, j);

			/* If the square contains a piece of the player */
			if(!moBoard.bIsSquareEmpty(oPos1) && moBoard.eGetSquareColor(oPos1) == ePlayer)
			{
				/* For each squares of the board */
				for(unsigned int k = 0; k < 8; ++k)
				{
					for(unsigned int l = 0; l < 8; ++l)
					{
						Position oPos2(k, l);

						/* If the piece can go from the first square to the second */
						if(bIsMovementCorrect(oPos1, oPos2))
						{
							try
							{
								/* Determining the type of the movement */
								Movement * poMove = NULL;
								
								if(bIsCastling(oPos1, oPos2))
								{
									if(bIsInCheck(ePlayer))
										throw exception("Castling is not allowed if you're in check");

									if(!bIsCastlingPathOk(oPos1, oPos2))
										throw exception("Your king would be in check during castling");

									poMove = new CastlingMove(oPos1, oPos2);
								}
								else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())
									poMove = new FirstMove(oPos1, oPos2);
								else
									poMove = new Movement(oPos1, oPos2);

								moHistory.push_back(poMove);

								if(moBoard.poGetPiece(oPos1)->eGetType() == Piece::KING)
									moKings[meCurrentPlayer] = oPos2;

								poMove->Execute();	// Move the piece

								if(!bIsInCheck(ePlayer))	// Check if the player is still in check
								{
									CancelLastMove();		// If not, cancel the move, and return that the player is not in check
									return false;
								}

								CancelLastMove();	// Cancel the move anyway
							}
							catch(exception &)	// Catch the exception for impossible moves
							{
							}
						}
					}
				}
			}
		}
	}

	return true;	// If no moves turn the player in a non-in-check state, the player is checkmate
}

void TwoPlayersGame::CheckSelectionCoords(Position oPos) const
{	
	if(moBoard.bIsSquareEmpty(oPos))
		throw exception("There is no piece on this square");

	if(moBoard.eGetSquareColor(oPos) != meCurrentPlayer)
		throw exception("This piece does not belong to you");
}

bool TwoPlayersGame::bIsMovementCorrect(Position oPos1, Position oPos2) const
{
	if((oPos1 == oPos2)	// No move
	|| (moBoard.bIsSquareEmpty(oPos1))	// No piece to move
	|| (!moBoard.bIsSquareEmpty(oPos2) && moBoard.eGetSquareColor(oPos1) == moBoard.eGetSquareColor(oPos2))	// The two pieces are on the same side
	|| (!moBoard.poGetPiece(oPos1)->bIsMovementCorrect(oPos1, oPos2, moBoard)))	// The movement is not correct for this piece
		return false;

	return true;	// If none of the precedent verifications failed, the movement is correct
}

bool TwoPlayersGame::bIsOver()
{
	return mbIsOver;
}

void TwoPlayersGame::CancelLastMove()
{
	if(moHistory.size() == 0)
		throw exception("Empty history");

	Movement * oLastMovement = moHistory.back();	// Getting the last move
	oLastMovement->CancelMovement();				// Cancel it

	/* Update the kings position if necessary */
	if(oLastMovement->poGetMovingPiece()->eGetType() == Piece::KING)
		moKings[oLastMovement->eGetPlayerColor()] = oLastMovement->oGetCoords1();

	delete moHistory.back();	// Destroy the last move
	moHistory.pop_back();		// Supress the pointer from the list
}

bool TwoPlayersGame::bIsGameInStaleMate()
{
	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);

			if(!moBoard.bIsSquareEmpty(oPos) && moBoard.eGetSquareColor(oPos) == meCurrentPlayer)
				if(oGetPossibilities(oPos).size() != 0)
					return false;
		}

	return true;
}