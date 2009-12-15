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
			
			if(strEntry == "x")
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
						/*if(bIsCastling(moSelection, oEntry))
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
						}
						else
						{
							CheckIsMovementCorrect(moSelection, oEntry);

							bool bIsPawnProm = bIsPromotion(moSelection, oEntry);
							MovePiece(moSelection, oEntry);

							if(bIsInCheck(meCurrentPlayer))
							{
								CancelLastMove();
								throw exception("That move puts you in check");
							}

							if(bIsPawnProm)
								PromotePawn(oEntry, poInterface->cGetNewPieceType());

							if(bIsCheckMate(meCurrentPlayer))
							{
								poInterface->DisplayBoard(moBoard);
								poInterface->DisplayMessage(string(meCurrentPlayer == Piece::WHITE ? "White" : "Black") + " player is checkmate !");
								mbIsOver = true;
							}
						}*/

						if(bIsCastling(moSelection, oEntry))
							poNextMove = new CastlingMove(moSelection, oEntry);
						else if(bIsPromotion(moSelection, oEntry))
							poNextMove = new Promotion(moSelection, oEntry);
						else if(moBoard.poGetPiece(moSelection)->bIsFirstMove())
							poNextMove = new FirstMove(moSelection, oEntry);
						else
							poNextMove = new Movement(moSelection, oEntry);

						moHistory.push_back(poNextMove);
						poNextMove->Execute();

						if(moBoard.poGetPiece(moSelection)->eGetType() == Piece::KING)
							moKings[moBoard.eGetSquareColor(moSelection)] = oEntry;

						if(bIsInCheck(meCurrentPlayer))
						{
							CancelLastMove();
							throw exception("That move puts you in check");
						}

						if(bIsCheckMate(meCurrentPlayer))
							mbIsCurrentPlayerCheckMate = true;
						else
							SwitchPlayer();
					}
					
					moSelection.Empty();
				}
			}

			poInterface->DisplayBoard(moBoard);
			
			if(mbIsCurrentPlayerCheckMate)
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
			else		
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	
			if(strEntry.size() != 0
			&& strEntry[strEntry.size() - 1] == '?')
				poInterface->DisplayPossibilities(strGetPossibilities(strEntry.substr(0, 2)));

			if(bIsInCheck(meCurrentPlayer))
				poInterface->DisplayInCheck(moKings[meCurrentPlayer]);

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

void Game::PromotePawn(Position oPos, char cNewType)
{
	moBoard.PromotePawn(oPos, cNewType);
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

/*void Game::Castling(Piece::Color ePlayer, Game::CastlingSide eSide)
{
	Position & oKing = moKings[ePlayer];
	Position oKingNewPos(oKing.mX, (eSide == Game::RIGHT ? 6 : 2));
	Position oRook(moKings[ePlayer].mX, (eSide == Game::RIGHT ? 7 : 0));
	Position oRookNewPos(oRook.mX, (eSide == Game::RIGHT ? 5 : 3));

	moHistory.push_back(new CastlingMove(oKing, oKingNewPos, moBoard.poGetPiece(oKing)));

	moBoard.MovePiece(oKing, oKingNewPos);
	moBoard.MovePiece(oRook, oRookNewPos);
}*/

bool Game::bIsCastling(Position oPos1, Position oPos2)
{
	Position oKing = (meCurrentPlayer == Piece::WHITE ? Position(7, 4) : Position(0, 4));

	if(oPos1 == oKing
	&& oPos1.mX == oPos2.mX
	&& (oPos2.mY == oPos1.mY - 2 || oPos2.mY == oPos1.mY + 2))
		return true;

	return false;
}

/*void Game::CheckIsCastlingOk(Piece::Color ePlayer, Game::CastlingSide eSide)
{
	Position oKing = moKings[ePlayer];

	if(moBoard.poGetPiece(oKing)->bHasAlreadyMoved())
		throw exception("Your king has already moved and therefore cannot castling");

	switch(eSide)
	{
	  case Game::RIGHT :
		if(moBoard.poGetPiece(Position(oKing.mX, 7))->bHasAlreadyMoved())
			throw exception("Your rook has already moved, and therefore cannot castling");

		for(unsigned int j = oKing.mY + 1; j <= 6; ++j)
		{
			if(!moBoard.bIsSquareEmpty(oKing.mX, j))
				throw exception("The pass is obstructed");
		}

		break;
	  case Game::LEFT :
		if(moBoard.poGetPiece(Position(oKing.mX, 0))->bHasAlreadyMoved())
			throw exception("Your rook has already moved, and therefore cannot castling");

		for(unsigned int j = oKing.mY - 1; j >= 2; --j)
		{
			if(!moBoard.bIsSquareEmpty(oKing.mX, j))
				throw exception("The pass is obstructed");
		}

		break;
	  default :
		break;
	}
}*/

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
				//MovePiece(oPos, oPos2);
				Movement oMove(oPos, oPos2);
				oMove.Execute();

				if(!bIsInCheck(meCurrentPlayer))
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
							Movement oMove(oPos1, oPos2);
							oMove.Execute();

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

/*void Game::MovePiece(Position oPos1, Position oPos2)
{
	if(moBoard.poGetPiece(oPos1)->bIsFirstMove())
		moHistory.push_back(new FirstMove(oPos1, oPos2, moBoard.poGetPiece(oPos1), moBoard.poGetPiece(oPos2)));
	else if(bIsPromotion(oPos1, oPos2))
		moHistory.push_back(new Promotion(oPos1, oPos2, moBoard.poGetPiece(oPos1), moBoard.poGetPiece(oPos2)));
	else
		moHistory.push_back(new Movement(oPos1, oPos2, moBoard.poGetPiece(oPos1), moBoard.poGetPiece(oPos2)));

	if(moBoard.poGetPiece(oPos1)->eGetType() == Piece::KING)
		moKings[moBoard.eGetSquareColor(oPos1)] = oPos2;

	moBoard.MovePiece(oPos1, oPos2);
}*/

void Game::CheckSelectionCoords(Position oPos) const
{	
	if(moBoard.bIsSquareEmpty(oPos))
		throw exception("There is no piece on this square");

	if(moBoard.eGetSquareColor(oPos) != meCurrentPlayer)
		throw exception("This piece does not belong to you");
}

void Game::CheckIsMovementCorrect(Position oPos1, Position oPos2) const
{
	if(oPos1 == oPos2)
		throw exception("No movement");

	if(moBoard.bIsSquareEmpty(oPos1))
		throw exception("There is no piece on the starting square");

	if(!moBoard.bIsSquareEmpty(oPos2) && moBoard.eGetSquareColor(oPos1) == moBoard.eGetSquareColor(oPos2))
		throw exception("The two pieces are on the same side");

	if(!moBoard.poGetPiece(oPos1)->bIsMovementCorrect(oPos1, oPos2, moBoard))
		throw exception("Invalid move");
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
