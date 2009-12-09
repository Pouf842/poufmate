#include "game.h"
#include "board.h"
#include "piece.h"
#include "interface_console.h"
#include "interface_SDL.h"
#include <iostream>
#include <string>

using namespace std;

ostream & operator<<(ostream & os, const Board & b);

Game::Game()
{
	meCurrentPlayer = Piece::WHITE;
	miXWhiteKing = 7;
	miYWhiteKing = 4;
	miXBlackKing = 0;
	miYBlackKing = 4;
	mbIsOver = false;
}

bool Game::bIsCoordsCorrect(unsigned int X, unsigned int Y) const
{
	return (X < 8 && Y < 8);
}

void Game::Run()
{
	string strEntry = "";
	//Interface * poInterface = InterfaceConsole::poGetInstance();
	Interface * poInterface = InterfaceSDL::poGetInstance();

	moBoard.Init();

	while(!bIsOver())
	{
		poInterface->DisplayBoard(moBoard);
		if(mstrSelection != "")
			poInterface->DisplaySelection(mstrSelection[0] - '0', mstrSelection[1] - '0');

		if(bIsInCheck(meCurrentPlayer))
		{
			if(meCurrentPlayer == Piece::WHITE)
				poInterface->DisplayInCheck(miXWhiteKing, miYWhiteKing);
			else
				poInterface->DisplayInCheck(miXBlackKing, miYBlackKing);
		}

		poInterface->DisplayMessage(string("Joueur ") + (meCurrentPlayer == Piece::WHITE ? "Blanc":"Noir"));

		try
		{
			if(mstrSelection == "")
			{
				strEntry = poInterface->strGetEntry();
			
				if(strEntry.size() != 0)
				{
					if(strEntry == "q")
					{
						mbIsOver = true;
						mstrSelection = "";
					}
					else if(strEntry == "c")
					{
						CancelLastMove();
						meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
					}
					else if(strEntry[strEntry.size() - 1] == '?')
					{
						string strPossibilities = strGetPossibilities(strEntry[0] - '0', strEntry[1] - '0');
						poInterface->DisplayPossibilities(strPossibilities);
					}
					else
					{
						unsigned int X = strEntry[0] - '0';
						unsigned int Y = strEntry[1] - '0';

						CheckCoords(X, Y);
						mstrSelection = strEntry;
					}

					strEntry = "";
				}
			}
			
			if(mstrSelection != "")
			{
				strEntry = poInterface->strGetEntry();
				
				if(strEntry[strEntry.size() - 1] == '?')
				{
					string strPossibilities = strGetPossibilities(mstrSelection[0] - '0', mstrSelection[1] - '0');
					poInterface->DisplayPossibilities(strPossibilities);
				}
				else
				{
					unsigned int X1 = mstrSelection[0] - '0';
					unsigned int Y1 = mstrSelection[1] - '0';

					unsigned int X2 = strEntry[0] - '0';
					unsigned int Y2 = strEntry[1] - '0';

					/*if(bIsCastling(X1, Y1, X2, Y2))
					{
						if(bIsInCheck(meCurrentPlayer))
							throw exception("Castling is forbidden if you're in check");

						CheckIsMovementCorrect(X1, Y1, X2, Y2);
					}
					else
					{*/
						CheckIsMovementCorrect(X1, Y1, X2, Y2);
					
						MovePiece(X1, Y1, X2, Y2);
						meCurrentPlayer = (meCurrentPlayer == Piece::WHITE ? Piece::BLACK : Piece::WHITE);

						if(bIsCheckMate(meCurrentPlayer))
						{
							poInterface->DisplayBoard(moBoard);
							poInterface->DisplayMessage(string(meCurrentPlayer == Piece::WHITE ? "White" : "Black") + " player is checkmate !");
							mbIsOver = true;
						}
					//}

					mstrSelection = "";
					strEntry = "";
				}
			}
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
			mstrSelection = "";
			strEntry = "";
		}
	}

	poInterface->DisplayMessage("Fin de partie");
	poInterface->strGetEntry();
}


string Game::strGetPossibilities(unsigned int X, unsigned int Y)
{
	string strPossibilities = "";
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			if(Game::bIsMovementCorrect(X, Y, i, j))
			{
				MovePiece(X, Y, i, j);
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
	unsigned int iXKing = (eColor == Piece::WHITE ? miXWhiteKing : miXBlackKing);
	unsigned int iYKing = (eColor == Piece::WHITE ? miYWhiteKing : miYBlackKing);

	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			if(!moBoard.bIsSquareEmpty(i, j) && moBoard.eGetSquareColor(i, j) != eColor)
			{
				if(bIsMovementCorrect(i, j, iXKing, iYKing))
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
			if(!moBoard.bIsSquareEmpty(i, j) && moBoard.eGetSquareColor(i, j) == ePlayer)
			{
				for(unsigned int k = 0; k < 8; ++k)
				{
					for(unsigned int l = 0; l < 8; ++l)
					{
						if(bIsMovementCorrect(i, j, k, l))
						{
							MovePiece(i, j, k, l);

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

void Game::MovePiece(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2)
{
	moHistory.push_back(Movement(meCurrentPlayer, X1, Y1, X2, Y2, moBoard.poGetPiece(X1, Y1), moBoard.poGetPiece(X2, Y2)));

	if(moBoard.poGetPiece(X1, Y1)->eGetType() == Piece::KING)
	{
		if(moBoard.eGetSquareColor(X1, Y2) == Piece::WHITE)
		{
			miXWhiteKing = X2;
			miYWhiteKing = Y2;
		}
		else
		{
			miXBlackKing = X2;
			miYBlackKing = Y2;
		}
	}

	moBoard.MovePiece(X1, Y1, X2, Y2);
}

void Game::CheckCoords(unsigned int X, unsigned int Y) const
{
	if(!bIsCoordsCorrect(X, Y))
		throw exception("Invalid start coordinates");
	
	if(moBoard.bIsSquareEmpty(X, Y))
		throw exception("There is no piece on this square");

	if(moBoard.eGetSquareColor(X, Y) != meCurrentPlayer)
		throw exception("This piece does not belong to you");
}

void Game::CheckIsMovementCorrect(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2) const
{
	if(X1 == X2 && Y1 == Y2)
		throw exception("No movement");

	if(!bIsCoordsCorrect(X1, Y1) || ! bIsCoordsCorrect(X2, Y2))
		throw exception("Invalid coordinates");

	if(moBoard.bIsSquareEmpty(X1, Y1))
		throw exception("There is no piece on the starting square");

	if(!moBoard.bIsSquareEmpty(X2, Y2) && moBoard.eGetSquareColor(X1, Y1) == moBoard.eGetSquareColor(X2, Y2))
		throw exception("The two pieces are on the same side");

	if(!moBoard.poGetPiece(X1, Y1)->bIsmovementCorrect(X1, Y1, X2, Y2, moBoard))
		throw exception("Invalid move");
}

bool Game::bIsMovementCorrect(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2) const
{
	if((X1 == X2 && Y1 == Y2)
	|| (!bIsCoordsCorrect(X1, Y1) || ! bIsCoordsCorrect(X2, Y2))
	|| (moBoard.bIsSquareEmpty(X1, Y1))
	|| (!moBoard.bIsSquareEmpty(X2, Y2) && moBoard.eGetSquareColor(X1, Y1) == moBoard.eGetSquareColor(X2, Y2))
	|| (!moBoard.poGetPiece(X1, Y1)->bIsmovementCorrect(X1, Y1, X2, Y2, moBoard)))
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

	Movement oLastMovement = moHistory.back();
	moBoard.SetPiece(oLastMovement.iGetX1(), oLastMovement.iGetY1(), oLastMovement.poGetMovingPiece());
	moBoard.SetPiece(oLastMovement.iGetX2(), oLastMovement.iGetY2(), oLastMovement.poGetCapturedPiece());

	if(oLastMovement.poGetMovingPiece()->eGetType() == Piece::KING)
	{
		if(oLastMovement.eGetPlayerColor() == Piece::WHITE)
		{
			miXWhiteKing = oLastMovement.iGetX1();
			miYWhiteKing = oLastMovement.iGetY1();
		}
		else
		{
			miXBlackKing = oLastMovement.iGetX1();
			miYBlackKing = oLastMovement.iGetY1();
		}
	}

	moHistory.pop_back();
}
