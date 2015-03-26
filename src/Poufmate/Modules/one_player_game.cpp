#include "one_player_game.h"

#include "Core/board.h"
#include "Pieces/piece.h"
#include "Movements/include_movements.h"
#include "Interface/interface.h"
#include <time.h>

using namespace std;

OnePlayerGame::OnePlayerGame(Interface * poInterface) : Game(poInterface, Module::MT_GAME)
{
}

OnePlayerGame::OnePlayerGame(const Board & oBoard, Interface * poInterface) : Game(oBoard, poInterface)
{
}

OnePlayerGame::~OnePlayerGame()
{
}

Entry::ENTRY_COMMAND OnePlayerGame::Run()
{
	try
	{
		if(!mpoInterface)
			throw exception("The interface is not defined");

		Piece::PIECE_COLOR ePlayerColor = mpoInterface->eGetPlayerColorChoice();

		Movement * poNextMove = NULL;
		Entry::ENTRY_COMMAND eCommand;

		while(!bIsOver())
		{
			try
			{
				if(meCurrentPlayer == ePlayerColor)
				{
					Entry oEntry = mpoInterface->oGetEntry();	// Getting the next command
				
					if(oEntry.bIsCommand())			// Do nothing
					{
						eCommand = oEntry.eGetCommand();

						if(eCommand == Entry::EC_NONE);
						/* Cancel last move */
						else if(eCommand == Entry::EC_CANCEL_MOVE)
						{
							CancelLastMove();
							CancelLastMove();
						}
						else
							return eCommand;
					}
					/* Select a piece or make a move */
					else
					{
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

							/* Update the king position if necessary */
							if(moBoard.eGetSquareType(oPos2) == Piece::PT_KING)
								moKings[moBoard.eGetSquareColor(oPos2)] = oPos2;

							/* If the move puts the player in check, it is not valid */
							if(bIsInCheck(meCurrentPlayer))
							{
								CancelLastMove();
								throw exception("That move puts you in check");
							}

							RefreshCheckBooleans();

							mpoSelectedPosition = NULL;
							SwitchPlayer();	// Next player
						}
					}
				}
				else
				{
					PlayComputerMove(5);
					SwitchPlayer();
				}

				/* If the player is checkmate, display a message and stop the game */
				if(bIsCheckMate(meCurrentPlayer))
					(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteCheckMate : mbIsBlackCheckMate) = true;
				else if(bIsGameInStaleMate())
					mbIsStaleMate = true;
				else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
					(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = true;
			}
			catch(exception & e)
			{
				cout << __FILE__ << ":" << __LINE__ << endl;
				mpoInterface->DisplayMessage(e.what());
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

void OnePlayerGame::PlayComputerMove(unsigned int iDepth)
{
	vector<Movement *> oPossibleMovement = GenerateMovementsForPlayer(meCurrentPlayer);

	if(oPossibleMovement.size() == 0)
		return;

	vector<int> oScores;

	int iMinimumDesFils = 30000;
	Movement * oBestMove = new Movement(*oPossibleMovement[0]);

	mpoInterface->SetBusy();

	for(unsigned int i = 0; i < oPossibleMovement.size(); ++i)
	{
		mpoInterface->SetProgress((i * 100) / oPossibleMovement.size());

		if(moBoard.eGetSquareType(oPossibleMovement[i]->oGetCoords1()) == Piece::PT_KING)
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

vector<Movement*> OnePlayerGame::GenerateMovementsForPlayer(Piece::PIECE_COLOR eColor)
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
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, Piece::PT_QUEEN));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, Piece::PT_KNIGHT));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, Piece::PT_BISHOP));
							oPossibleMovements.push_back(new Promotion(oPos1, oPos2, Piece::PT_ROOK));
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

int OnePlayerGame::HeuristicValue(Piece::PIECE_COLOR ePlayer)
{
	Piece::PIECE_COLOR eOpponent = (ePlayer == Piece::PC_WHITE ? Piece::PC_BLACK : Piece::PC_WHITE);

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
				  case Piece::PT_QUEEN :
					iScore += iFactor * 9;
					break;
				  case Piece::PT_ROOK :
					iScore += iFactor * 5;
					break;
				  case Piece::PT_KNIGHT :
					iScore += iFactor * 3;
					break;
				  case Piece::PT_BISHOP :
					iScore += iFactor * 3;
					break;
				  case Piece::PT_PAWN :
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
						  case Piece::PT_ROOK :
							iScore += iFactor * (5 + 1);
							break;
						  case Piece::PT_KNIGHT :
							iScore += iFactor * (3 + 1);
							break;
						  case Piece::PT_BISHOP :
							iScore += iFactor * (3 + 1);
							break;
						  case Piece::PT_QUEEN :
							iScore += iFactor * (9 + 1);
							break;
						  case Piece::PT_PAWN :
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
