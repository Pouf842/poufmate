#include "game_edition.h"
#include "two_players_game.h"
#include <string>
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

using namespace std;

GameEdition::GameEdition() : meNewPieceType(Piece::NONE), mbNewPieceSelected(false)
{
}

GameEdition::~GameEdition()
{
}

void GameEdition::Run(Interface * poInterface)
{
	bool bQuit = false;
	string strEntry = "";

	poInterface->DisplayBoard(moBoard);
	poInterface->CommitDisplay();

	while(!bQuit)
	{
		strEntry = poInterface->strGetEntry();

		if(strEntry.size() == 1)
		{
			if(strEntry == "x")
				bQuit = true;
			else if(strEntry == "r")
			{
				TwoPlayersGame oGame(moBoard);
				oGame.Run(poInterface);
			}
			else
			{
				mbNewPieceSelected = true;

				switch(strEntry[0])
				{
				  case 'P' :
					meNewPieceType = Piece::PAWN;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'R' :
					meNewPieceType = Piece::ROOK;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'N' :
					meNewPieceType = Piece::KNIGHT;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'B' :
					meNewPieceType = Piece::BISHOP;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'Q' :
					meNewPieceType = Piece::QUEEN;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'K' :
					meNewPieceType = Piece::KING;
					meNewPieceColor = Piece::WHITE;
					break;
				  case 'p' :
					meNewPieceType = Piece::PAWN;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'r' :
					meNewPieceType = Piece::ROOK;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'n' :
					meNewPieceType = Piece::KNIGHT;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'b' :
					meNewPieceType = Piece::BISHOP;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'q' :
					meNewPieceType = Piece::QUEEN;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'k' :
					meNewPieceType = Piece::KING;
					meNewPieceColor = Piece::BLACK;
					break;
				  case 'x' :
				  case 'X' :
				  default :
					mbNewPieceSelected = false;
				}

				if(mbNewPieceSelected)
					moSelection.Empty();
			}
		}
		else if(strEntry.size() == 2)
		{
			Position oPos = strEntry;

			if(mbNewPieceSelected)
			{
				if(moBoard.poGetPiece(oPos))
					delete moBoard.poGetPiece(oPos);

				Piece * poNewPiece = 0;

				switch(meNewPieceType)
				{
				  case Piece::PAWN :
					poNewPiece = new Pawn(meNewPieceColor);
					break;
				  case Piece::ROOK :
					poNewPiece = new Rook(meNewPieceColor);
					break;
				  case Piece::KNIGHT :
					poNewPiece = new Knight(meNewPieceColor);
					break;
				  case Piece::BISHOP :
					poNewPiece = new Bishop(meNewPieceColor);
					break;
				  case Piece::QUEEN :
					poNewPiece = new Queen(meNewPieceColor);
					break;
				  case Piece::KING :
					poNewPiece = new King(meNewPieceColor);
					break;
				  case Piece::NONE :
				  default :
					break;
				}

				moBoard.SetPiece(oPos, poNewPiece);
			}
			else
			{
				if(moSelection.bIsEmpty())
					moSelection = strEntry;
				else
				{
					if(!moBoard.bIsSquareEmpty(strEntry))
						delete moBoard.poGetPiece(strEntry);

					moBoard.SetPiece(strEntry, moBoard.poGetPiece(moSelection));
					moBoard.SetPiece(moSelection, 0);
				}
			}
		}

		poInterface->DisplayBoard(moBoard);

		/* If there is a selected piece, display it */
		if(!moSelection.bIsEmpty())
			poInterface->DisplaySelection(moSelection);

		poInterface->CommitDisplay();
	}
}