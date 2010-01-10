#include "one_player_game.h"
#include "board.h"
#include "piece.h"
#include "include_movements.h"
#include "interface.h"
#include <time.h>

using namespace std;

OnePlayerGame::OnePlayerGame() : Game()
{
	srand((unsigned int) time(NULL));
}

OnePlayerGame::OnePlayerGame(const Board & oBoard) : Game(oBoard)
{
	srand((unsigned int) time(NULL));
}

OnePlayerGame::~OnePlayerGame()
{
}

void OnePlayerGame::Run(Interface * poInterface)
{
	if(!poInterface)
		throw exception("The interface is not defined");

	string strEntry = "";

	Movement::SetBoard(&moBoard);

	Piece::Color ePlayerColor = Piece::WHITE;

	if(poInterface->cGetPlayerColorChoice() != 'W')
		ePlayerColor = Piece::BLACK;

	poInterface->DisplayBoard(moBoard);
	poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	poInterface->CommitDisplay();

	Movement * poNextMove = NULL;

	while(!bIsOver())
	{
		try
		{
			if(meCurrentPlayer == ePlayerColor)
			{
				strEntry = poInterface->strGetEntry();	// Getting the next command
			
				if(strEntry == "");			// Do nothing
				else if(strEntry == "x")
					mbIsOver = true;		// Stop the game
				/* Cancel last move */
				else if(strEntry == "c")
				{
					CancelLastMove();
					CancelLastMove();
					moSelection.Empty();
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
							else if(bIsEnPassantOk(moSelection, oEntry))
								poNextMove = new EnPassant(moSelection, oEntry, (*moHistory.rbegin()));
							else
								poNextMove = new Movement(moSelection, oEntry);	// Other move

							/* Execute the move */
							ExecuteMovement(poNextMove);

							/* Update the king position if necessary */
							if(moBoard.eGetSquareType(oEntry) == Piece::KING)
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
			}
			else
			{
				PlayComputerMove(5);
				SwitchPlayer();
			}

			/* Display the game */
			poInterface->DisplayBoard(moBoard);

			/* If the player is checkmate, display a message and stop the game */
			if(strEntry == "x")	// Display a message
				poInterface->DisplayMessage("Game over !");
			else if(bIsCheckMate(meCurrentPlayer))
			{
				mbIsOver = true;
				poInterface->DisplayGameOver(string(meCurrentPlayer == Piece::WHITE ? "White " : "Black ") + " player is check mate !");
			}
			else if(bIsGameInStaleMate())
			{
				mbIsOver = true;
				poInterface->DisplayMessage("This is a stalemate");
			}
			else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
			{
				poInterface->DisplayInCheck(moKings[meCurrentPlayer]);
				poInterface->DisplayMessage(string("The ") + (meCurrentPlayer == Piece::WHITE ? " white" : " black") + " king is in check");
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
			poInterface->DisplayMessage(e.what());
		}

		poInterface->CommitDisplay();
	}
}

void OnePlayerGame::PlayComputerMove(unsigned int iDepth)
{
	vector<Movement *> oPossibleMovement = GenerateMovementsForPlayer(meCurrentPlayer);

	if(oPossibleMovement.size() == 0)
		return;

	vector<int> oScores;

	int iMinimumDesFils = 30000;
	Movement * oBestMove = new Movement(*oPossibleMovement[0]);

	cout << "|";
	for(unsigned int i = 0; i < oPossibleMovement.size(); ++i)
		cout << " ";

	cout << "|" << endl << " ";

	for(unsigned int i = 0; i < oPossibleMovement.size(); ++i)
	{
		cout << "*" << flush;

		if(moBoard.eGetSquareType(oPossibleMovement[i]->oGetCoords1()) == Piece::KING)
			moKings[meCurrentPlayer] = oPossibleMovement[i]->oGetCoords2();

		ExecuteMovement(oPossibleMovement[i]);
		SwitchPlayer();

		oScores.push_back(Alphabeta(3, iMinimumDesFils));

		if(oScores.back() < iMinimumDesFils)
		{
			iMinimumDesFils = oScores.back();

			if(oBestMove)
				delete oBestMove;

			oBestMove = new Movement(*oPossibleMovement[i]);
		}

		CancelLastMove();
		SwitchPlayer();
	}

	ExecuteMovement(oBestMove);

	cout << endl;
}

vector<Movement*> OnePlayerGame::GenerateMovementsForPlayer(Piece::Color eColor)
{
	vector<Movement*> oPossibleMovements;

	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			if(!moBoard.bIsSquareEmpty(Position(i, j))
			&& moBoard.eGetSquareColor(Position(i, j)) == eColor)
			{
				vector<Position> oPossibilities = oGetPossibilities(i, j);

				for(unsigned int k = 0; k < oPossibilities.size(); ++k)
				{
					Position oPos1(i, j);
					Position oPos2 = oPossibilities[k];

					try
					{
						if(bIsCastling(oPos1, oPos2))	// Castling
							oPossibleMovements.push_back(new CastlingMove(oPos1, oPos2));
						else if(bIsPromotion(oPos1, oPos2))	// Promotion
						{
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, 'Q'));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, 'N'));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, 'B'));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, 'R'));
						}
						else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())	// First move
							oPossibleMovements.push_back(new FirstMove(oPos1, oPos2));
						else if(bIsEnPassantOk(oPos1, oPos2))
							oPossibleMovements.push_back(new EnPassant(oPos1, oPos2, (*moHistory.rbegin())));
						else
							oPossibleMovements.push_back(new Movement(oPos1, oPos2));	// Other move
					}
					catch(exception &)
					{
					}
				}
			}
		}

		return oPossibleMovements;
}

int OnePlayerGame::HeuristicValue(Piece::Color ePlayer)
{
	Piece::Color eOpponent = (ePlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);

	if(bIsCheckMate(eOpponent))
		return 30000;

	if(bIsCheckMate(ePlayer))
		return -30000;

	if(bIsInCheck(eOpponent))
		return 1000;

	if(bIsInCheck(ePlayer))
		return -1000;

	int iScore = 0;

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			if(!moBoard.bIsSquareEmpty(i, j))
			{
				int iFactor = (moBoard.eGetSquareColor(i, j) == ePlayer ? 1 : -1);

				switch(moBoard.eGetSquareType(i, j))
				{
				  case Piece::ROOK :
					iScore += iFactor * 5;
					break;
				  case Piece::KNIGHT :
					iScore += iFactor * 3;
					break;
				  case Piece::BISHOP :
					iScore += iFactor * 3;
					break;
				  case Piece::QUEEN :
					iScore += iFactor * 9;
					break;
				  case Piece::PAWN :
				    iScore += iFactor * 1;
					break;
				}

				vector<Position> oPossibleMoves = oGetPossibilities(i, j);

				for(unsigned int k = 0; k < oPossibleMoves.size(); ++k)
				{
					if(bIsCastling(Position(i, j), oPossibleMoves[k]))
						iScore += 10;
					else if(bIsPromotion(Position(i, j), oPossibleMoves[k]))
						iScore += 20;
					else if(moBoard.bIsSquareEmpty(oPossibleMoves[k]))
						iScore += iFactor * 1;
					else
					{
						switch(moBoard.eGetSquareType(oPossibleMoves[k]))
						{
						  case Piece::ROOK :
							iScore += iFactor * (5 + 1);
							break;
						  case Piece::KNIGHT :
							iScore += iFactor * (3 + 1);
							break;
						  case Piece::BISHOP :
							iScore += iFactor * (3 + 1);
							break;
						  case Piece::QUEEN :
							iScore += iFactor * (9 + 1);
							break;
						  case Piece::PAWN :
							iScore += iFactor * (1 + 1);
							break;
						}
					}
				}
			}
		}
	}

	return iScore;
}

int OnePlayerGame::Alphabeta(unsigned int profondeur, int MinimumDesFreres)
{
	if(profondeur == 0)
		return HeuristicValue(meCurrentPlayer);
	else
	{
		int MinimumDesFils = 30000;
		vector<Movement *> oPossibilities = GenerateMovementsForPlayer(meCurrentPlayer);

		for(unsigned int i = 0; i < oPossibilities.size(); ++i)
		{
			ExecuteMovement(oPossibilities[i]);
			SwitchPlayer();

			int iCurrentValue;

			iCurrentValue = Alphabeta(profondeur - 1, MinimumDesFils);

			if(iCurrentValue < MinimumDesFils)
				MinimumDesFils = iCurrentValue;

			if(iCurrentValue < -(MinimumDesFreres))
			{
				CancelLastMove();
				SwitchPlayer();

				return -iCurrentValue;
			}

			CancelLastMove();
			SwitchPlayer();
		}

		return -MinimumDesFils;
	}
}
