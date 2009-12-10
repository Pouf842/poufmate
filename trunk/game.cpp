#include "game.h"
#include "board.h"
#include "piece.h"
#include "interface_console.h"
#include "first_move.h"
#include "castling_move.h"

#ifdef __SDL_
	#include "interface_SDL.h"
	#define DISPLAY InterfaceSDL
#else
	#define DISPLAY InterfaceConsole
#endif

#include <iostream>
#include <string>

using namespace std;

ostream & operator<<(ostream & os, const Board & b);

Game::Game() : moWhiteKing(7, 4), moBlackKing(0, 4)
{
	meCurrentPlayer = Piece::WHITE;
	mbIsOver = false;
}

void Game::Run()
{
	string strEntry = "";
	Interface * poInterface = DISPLAY::poGetInstance();

	moBoard.Init();

	while(!bIsOver())
	{
		poInterface->DisplayBoard(moBoard);

		if(bIsInCheck(meCurrentPlayer))
		{
			if(meCurrentPlayer == Piece::WHITE)
				poInterface->DisplayInCheck(moWhiteKing);
			else
				poInterface->DisplayInCheck(moBlackKing);
		}

		poInterface->DisplayMessage(string("Joueur ") + (meCurrentPlayer == Piece::WHITE ? "Blanc":"Noir"));

		if(!moSelection.bIsEmpty())
			poInterface->DisplaySelection(moSelection);

		try
		{
			if(moSelection.bIsEmpty())
			{
				strEntry = poInterface->strGetEntry();
			
				if(strEntry.size() != 0)
				{
					if(strEntry == "q")
					{
						mbIsOver = true;
						moSelection.Empty();
					}
					else if(strEntry == "c")
					{
						CancelLastMove();
						meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
					}
					else if(strEntry[strEntry.size() - 1] == '?')
					{
						string strPossibilities = strGetPossibilities(strEntry);
						poInterface->DisplayPossibilities(strPossibilities);
					}
					else
					{
						CheckSelectionCoords(strEntry);
						moSelection = strEntry;
					}

					strEntry = "";
				}
			}
			
			if(!moSelection.bIsEmpty())
			{
				strEntry = poInterface->strGetEntry();
				
				if(strEntry[strEntry.size() - 1] == '?')
				{
					string strPossibilities = strGetPossibilities(moSelection);
					poInterface->DisplayPossibilities(strPossibilities);
				}
				else
				{
					Coordinates oEntry(strEntry);
					if(bIsCastling(moSelection, oEntry))
					{
						if(bIsInCheck(meCurrentPlayer))
							throw exception("Castling is forbidden if you're in check");

						Game::CastlingSide eSide = (oEntry.mY > moSelection.mY ? Game::RIGHT : Game::LEFT);
						CheckIsCastlingOk(meCurrentPlayer, eSide);
						Castling(meCurrentPlayer, eSide);

						if(bIsInCheck(meCurrentPlayer))
						{
							CancelLastMove();
							throw exception("That move puts you in check");
						}

						meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
					}
					else
					{
						CheckIsMovementCorrect(moSelection, oEntry);
					
						MovePiece(moSelection, oEntry);

						if(bIsInCheck(meCurrentPlayer))
						{
							CancelLastMove();
							throw exception("That move puts you in check");
						}

						meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);

						if(bIsCheckMate(meCurrentPlayer))
						{
							poInterface->DisplayBoard(moBoard);
							poInterface->DisplayMessage(string(meCurrentPlayer == Piece::WHITE ? "White" : "Black") + " player is checkmate !");
							mbIsOver = true;
						}
					}

					moSelection.Empty();
					strEntry = "";
				}
			}
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
			moSelection.Empty();
			strEntry = "";
		}
	}

	poInterface->DisplayMessage("Fin de partie");
	poInterface->strGetEntry();
}

void Game::Castling(Piece::Color ePlayer, Game::CastlingSide eSide)
{
	Coordinates & oKing = (ePlayer == Piece::WHITE ? moWhiteKing : moBlackKing);
	Coordinates oKingNewPos(oKing.mX, (eSide == Game::RIGHT ? 6 : 2));
	Coordinates oTower((ePlayer == Piece::WHITE ? moWhiteKing.mX : moBlackKing.mX), (eSide == Game::RIGHT ? 7 : 0));
	Coordinates oTowerNewPos(oTower.mX, (eSide == Game::RIGHT ? 5 : 3));

	moHistory.push_back(new CastlingMove(oKing, oKingNewPos, moBoard.poGetPiece(oKing)));

	moBoard.MovePiece(oKing, oKingNewPos);
	moBoard.MovePiece(oTower, oTowerNewPos);
}

bool Game::bIsCastling(Coordinates oCoords1, Coordinates oCoords2)
{
	Coordinates oKing = (meCurrentPlayer == Piece::WHITE ? Coordinates(7, 4) : Coordinates(0, 4));

	if(oCoords1 == oKing
	&& oCoords1.mX == oCoords2.mX
	&& (oCoords2.mY == oCoords1.mY - 2 || oCoords2.mY == oCoords1.mY + 2))
		return true;

	return false;
}

void Game::CheckIsCastlingOk(Piece::Color ePlayer, Game::CastlingSide eSide)
{
	Coordinates oKing = (ePlayer == Piece::WHITE ? moWhiteKing : moBlackKing);

	if(moBoard.poGetPiece(oKing)->bHasAlreadyMoved())
		throw exception("Your king has already moved and therefore cannot castling");

	switch(eSide)
	{
	  case Game::RIGHT :
		if(moBoard.poGetPiece(Coordinates(oKing.mX, 7))->bHasAlreadyMoved())
			throw exception("Your tower has already moved, and therefore cannot castling");

		for(unsigned int j = oKing.mY + 1; j <= 6; ++j)
		{
			if(!moBoard.bIsSquareEmpty(oKing.mX, j))
				throw exception("The pass is obstructed");
		}

		break;
	  case Game::LEFT :
		if(moBoard.poGetPiece(Coordinates(oKing.mX, 0))->bHasAlreadyMoved())
			throw exception("Your tower has already moved, and therefore cannot castling");

		for(unsigned int j = oKing.mY - 1; j >= 2; --j)
		{
			if(!moBoard.bIsSquareEmpty(oKing.mX, j))
				throw exception("The pass is obstructed");
		}

		break;
	  default :
		break;
	}
}

string Game::strGetPossibilities(Coordinates oCoords)
{
	string strPossibilities = "";
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Coordinates oCoords2(i, j);

			if(Game::bIsMovementCorrect(oCoords, oCoords2))
			{
				MovePiece(oCoords, oCoords2);
				if(!bIsInCheck(meCurrentPlayer))
				{
					strPossibilities += i + '0';
					strPossibilities += j + '0';
					strPossibilities += "\n";
				}

				CancelLastMove();
			}
		}
	}

	return (strPossibilities == "" ? "None": strPossibilities);
}

bool Game::bIsInCheck(Piece::Color eColor) const
{
	Coordinates oKing(eColor == Piece::WHITE ? moWhiteKing : moBlackKing);

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Coordinates oCoords(i, j);
			if(!moBoard.bIsSquareEmpty(oCoords) && moBoard.eGetSquareColor(oCoords) != eColor)
			{
				if(bIsMovementCorrect(oCoords, oKing))
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
			Coordinates oCoords1(i, j);

			if(!moBoard.bIsSquareEmpty(oCoords1) && moBoard.eGetSquareColor(oCoords1) == ePlayer)
			{
				for(unsigned int k = 0; k < 8; ++k)
				{
					for(unsigned int l = 0; l < 8; ++l)
					{
						Coordinates oCoords2(k, l);

						if(bIsMovementCorrect(oCoords1, oCoords2))
						{
							MovePiece(oCoords1, oCoords2);

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

void Game::MovePiece(Coordinates oCoords1, Coordinates oCoords2)
{
	if(moBoard.poGetPiece(oCoords1)->bIsFirstMove())
		moHistory.push_back(new FirstMove(oCoords1, oCoords2, moBoard.poGetPiece(oCoords1), moBoard.poGetPiece(oCoords2)));
	else
		moHistory.push_back(new Movement(oCoords1, oCoords2, moBoard.poGetPiece(oCoords1), moBoard.poGetPiece(oCoords2)));

	if(moBoard.poGetPiece(oCoords1)->eGetType() == Piece::KING)
	{
		if(moBoard.eGetSquareColor(oCoords1) == Piece::WHITE)
			moWhiteKing = oCoords2;
		else
			moBlackKing = oCoords2;
	}

	moBoard.MovePiece(oCoords1, oCoords2);
}

void Game::CheckSelectionCoords(Coordinates oCoords) const
{	
	if(moBoard.bIsSquareEmpty(oCoords))
		throw exception("There is no piece on this square");

	if(moBoard.eGetSquareColor(oCoords) != meCurrentPlayer)
		throw exception("This piece does not belong to you");
}

void Game::CheckIsMovementCorrect(Coordinates oCoords1, Coordinates oCoords2) const
{
	if(oCoords1 == oCoords2)
		throw exception("No movement");

	if(moBoard.bIsSquareEmpty(oCoords1))
		throw exception("There is no piece on the starting square");

	if(!moBoard.bIsSquareEmpty(oCoords2) && moBoard.eGetSquareColor(oCoords1) == moBoard.eGetSquareColor(oCoords2))
		throw exception("The two pieces are on the same side");

	if(!moBoard.poGetPiece(oCoords1)->bIsMovementCorrect(oCoords1, oCoords2, moBoard))
		throw exception("Invalid move");
}

bool Game::bIsMovementCorrect(Coordinates oCoords1, Coordinates oCoords2) const
{
	if((oCoords1 == oCoords2)
	|| (moBoard.bIsSquareEmpty(oCoords1))
	|| (!moBoard.bIsSquareEmpty(oCoords2) && moBoard.eGetSquareColor(oCoords1) == moBoard.eGetSquareColor(oCoords2))
	|| (!moBoard.poGetPiece(oCoords1)->bIsMovementCorrect(oCoords1, oCoords2, moBoard)))
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
	{
		if(oLastMovement->eGetPlayerColor() == Piece::WHITE)
			moWhiteKing = oLastMovement->oGetCoords1();
		else
			moBlackKing = oLastMovement->oGetCoords1();
	}

	moHistory.pop_back();
}
