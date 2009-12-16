#include "game.h"
#include "board.h"
#include "piece.h"
#include "first_move.h"
#include "castling_move.h"
#include "promotion.h"

#ifdef __SDL_
	#include "interface_SDL.h"
	#define DISPLAY InterfaceSDL
#else
	#include "interface_console.h"
	#define DISPLAY InterfaceConsole
#endif

#include <iostream>
#include <string>

using namespace std;

ostream & operator<<(ostream & os, const Board & b);

Game::Game()
{
	moKings[Piece::WHITE] = Position(7, 4);
	moKings[Piece::BLACK] = Position(0, 4);

	meCurrentPlayer = Piece::WHITE;
	mbIsOver = false;
	mbIsCurrentPlayerCheckMate = false;
}

void Game::SwitchPlayer()
{
	meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
}

void Game::Run()
{
	string strEntry = "";
	Interface * poInterface = DISPLAY::poGetInstance();

	moBoard.Init();
	Movement::SetBoard(&moBoard);

	poInterface->DisplayBoard(moBoard);
	poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	poInterface->CommitDisplay();
	
	Movement * poNextMove = 0;

	while(!bIsOver())
	{
		try
		{
			strEntry = poInterface->strGetEntry();
			
			if(strEntry == "");
			else if(strEntry == "x")
				mbIsOver = true;
			else if(strEntry == "c")
			{
				CancelLastMove();
				moSelection.Empty();
				SwitchPlayer();
			}
			else if(strEntry.size() != 0
			&& strEntry[strEntry.size() - 1] != '?')
			{
				Position oEntry(strEntry);

				if(moSelection.bIsEmpty())
				{
					CheckSelectionCoords(oEntry);
					moSelection = oEntry;
				}
				else
				{
					if(moSelection != oEntry)
					{
						if(bIsCastling(moSelection, oEntry))
						{
							if(bIsInCheck(meCurrentPlayer))
								throw exception("Castling is not allowed if you're in check");

							poNextMove = new CastlingMove(moSelection, oEntry);
						}
						else if(bIsPromotion(moSelection, oEntry))
							poNextMove = new Promotion(moSelection, oEntry);
						else if(moBoard.poGetPiece(moSelection)->bIsFirstMove())
							poNextMove = new FirstMove(moSelection, oEntry);
						else
							poNextMove = new Movement(moSelection, oEntry);

						moHistory.push_back(poNextMove);
						poNextMove->Execute();

						if(moBoard.poGetPiece(oEntry)->eGetType() == Piece::KING)
							moKings[moBoard.eGetSquareColor(oEntry)] = oEntry;

						if(bIsInCheck(meCurrentPlayer))
						{
							CancelLastMove();
							throw exception("That move puts you in check");
						}

						SwitchPlayer();
					}
					
					moSelection.Empty();
				}
			}

			poInterface->DisplayBoard(moBoard);
			

			if(bIsCheckMate(meCurrentPlayer))
			{
				mbIsOver = true;
				string strMessage = "The ";
				strMessage += (meCurrentPlayer == Piece::WHITE ? "white" : "black");
				strMessage += " player is checkmate !";

				poInterface->DisplayMessage(strMessage);
				poInterface->DisplayMessage("Game over !");
			}
			else if(strEntry == "x")
				poInterface->DisplayMessage("Game over !");
			else if(bIsInCheck(meCurrentPlayer))
			{
				poInterface->DisplayInCheck(moKings[meCurrentPlayer]);
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
			}
			else
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	
			if(strEntry.size() != 0
			&& strEntry[strEntry.size() - 1] == '?')
				poInterface->DisplayPossibilities(strGetPossibilities(strEntry.substr(0, 2)));


			if(!moSelection.bIsEmpty())
				poInterface->DisplaySelection(moSelection);
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
		}

		poInterface->CommitDisplay();
	}
	
	strEntry = poInterface->strGetEntry();

	return;
}

bool Game::bIsPromotion(Position oPos1, Position oPos2) const
{
	Piece * oPiece = moBoard.poGetPiece(oPos1);
	if(oPiece->eGetType() == Piece::PAWN
	&& oPos2.mX == (oPiece->eGetColor() == Piece::WHITE ? 0 : 7))
		return true;
	else
		return false;
}

bool Game::bIsCastling(Position oPos1, Position oPos2)
{
	Position oKing = (meCurrentPlayer == Piece::WHITE ? Position(7, 4) : Position(0, 4));

	if(oPos1 == oKing
	&& oPos1.mX == oPos2.mX
	&& (oPos2.mY == oPos1.mY - 2 || oPos2.mY == oPos1.mY + 2))
		return true;

	return false;
}

string Game::strGetPossibilities(Position oPos)
{
	string strPossibilities = "";
	strPossibilities += (oPos.mX + '0');
	strPossibilities += oPos.mY + '0';
	strPossibilities += ';';

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos2(i, j);

			if(Game::bIsMovementCorrect(oPos, oPos2))
			{
				Movement * poMove = 0;

				if(bIsCastling(oPos, oPos2))
				{
					if(bIsInCheck(moBoard.eGetSquareColor(oPos2)))
						continue;

					poMove = new CastlingMove(oPos, oPos2);
				}
				else if(moBoard.poGetPiece(oPos)->bIsFirstMove())
					poMove = new FirstMove(oPos, oPos2);
				else
					poMove = new Movement(oPos, oPos2);

				moHistory.push_back(poMove);
				if(moBoard.poGetPiece(oPos)->eGetType() == Piece::KING)
					moKings[meCurrentPlayer] = oPos2;

				poMove->Execute();

				if(!bIsInCheck(moBoard.eGetSquareColor(oPos2)))
				{
					strPossibilities += i + '0';
					strPossibilities += j + '0';
					strPossibilities += ";";
				}

				CancelLastMove();
			}
		}
	}

	return (strPossibilities == "" ? "None": strPossibilities);
}

bool Game::bIsInCheck(Piece::Color eColor) const
{
	Position oKing(moKings[eColor]);

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);
			if(!moBoard.bIsSquareEmpty(oPos) && moBoard.eGetSquareColor(oPos) != eColor)
			{
				if(bIsMovementCorrect(oPos, oKing))
					return true;
			}
		}
	}

	return false;
}

bool Game::bIsCheckMate(Piece::Color ePlayer)
{
	if(!bIsInCheck(ePlayer))
		return false;

	bool bMate = true;

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos1(i, j);

			if(!moBoard.bIsSquareEmpty(oPos1) && moBoard.eGetSquareColor(oPos1) == ePlayer)
			{
				for(unsigned int k = 0; k < 8; ++k)
				{
					for(unsigned int l = 0; l < 8; ++l)
					{
						Position oPos2(k, l);

						if(bIsMovementCorrect(oPos1, oPos2))
						{
							Movement * poMove = 0;
							
							if(bIsCastling(oPos1, oPos2))
							{
								if(bIsInCheck(ePlayer))
									throw exception("Castling is not allowed if you're in check");

								poMove = new CastlingMove(oPos1, oPos2);
							}
							else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())
								poMove = new FirstMove(oPos1, oPos2);
							else
								poMove = new Movement(oPos1, oPos2);

							moHistory.push_back(poMove);

							if(moBoard.poGetPiece(oPos1)->eGetType() == Piece::KING)
								moKings[meCurrentPlayer] = oPos2;

							poMove->Execute();

							if(!bIsInCheck(ePlayer))
							{
								CancelLastMove();
								return false;
							}

							CancelLastMove();
						}
					}
				}
			}
		}
	}

	return bMate;
}

void Game::CheckSelectionCoords(Position oPos) const
{	
	if(moBoard.bIsSquareEmpty(oPos))
		throw exception("There is no piece on this square");

	if(moBoard.eGetSquareColor(oPos) != meCurrentPlayer)
		throw exception("This piece does not belong to you");
}

bool Game::bIsMovementCorrect(Position oPos1, Position oPos2) const
{
	if((oPos1 == oPos2)
	|| (moBoard.bIsSquareEmpty(oPos1))
	|| (!moBoard.bIsSquareEmpty(oPos2) && moBoard.eGetSquareColor(oPos1) == moBoard.eGetSquareColor(oPos2))
	|| (!moBoard.poGetPiece(oPos1)->bIsMovementCorrect(oPos1, oPos2, moBoard)))
		return false;

	return true;
}

bool Game::bIsOver()
{
	return mbIsOver;
}

void Game::CancelLastMove()
{
	if(moHistory.size() == 0)
		throw exception("Empty history");

	Movement * oLastMovement = moHistory.back();
	oLastMovement->CancelMovement(moBoard);

	if(oLastMovement->poGetMovingPiece()->eGetType() == Piece::KING)
		moKings[oLastMovement->eGetPlayerColor()] = oLastMovement->oGetCoords1();

	moHistory.pop_back();
}
