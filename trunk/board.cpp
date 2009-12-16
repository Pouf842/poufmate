#include <iostream>
#include "board.h"
#include "rook.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "position.h"

using namespace std;

void Board::InterfaceOnStream(ostream & os) const
{
	os << "    0   1   2   3   4   5   6   7" << endl;

	for(unsigned int i = 0; i < 8; ++i)
	{
		os << "   -------------------------------" << endl;
		os << i << " ";

		for(unsigned int j = 0; j < 8; ++j)
			os << "| " << moSquares[i][j].cGetChar() << " ";

		os << "|" << endl;
	}

	os << "   -------------------------------" << endl;
}

void Board::Init()
{
	for(unsigned int i = 0; i < 8; ++i)
	{
		moSquares[1][i].SetPiece(new Pawn(Piece::BLACK));
		moSquares[6][i].SetPiece(new Pawn(Piece::WHITE));
	}

	moSquares[0][0].SetPiece(new Rook(Piece::BLACK));
	moSquares[0][7].SetPiece(new Rook(Piece::BLACK));
	moSquares[7][0].SetPiece(new Rook(Piece::WHITE));
	moSquares[7][7].SetPiece(new Rook(Piece::WHITE));

	moSquares[0][1].SetPiece(new Knight(Piece::BLACK));
	moSquares[0][6].SetPiece(new Knight(Piece::BLACK));
	moSquares[7][1].SetPiece(new Knight(Piece::WHITE));
	moSquares[7][6].SetPiece(new Knight(Piece::WHITE));

	moSquares[0][2].SetPiece(new Bishop(Piece::BLACK));
	moSquares[0][5].SetPiece(new Bishop(Piece::BLACK));
	moSquares[7][2].SetPiece(new Bishop(Piece::WHITE));
	moSquares[7][5].SetPiece(new Bishop(Piece::WHITE));

	moSquares[0][3].SetPiece(new Queen(Piece::BLACK));
	moSquares[7][3].SetPiece(new Queen(Piece::WHITE));

	moSquares[0][4].SetPiece(new King(Piece::BLACK));
	moSquares[7][4].SetPiece(new King(Piece::WHITE));
}

bool Board::bIsSquareEmpty(unsigned int X, unsigned int Y) const
{
	return bIsSquareEmpty(Position(X, Y));
}

bool Board::bIsSquareEmpty(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].bIsEmpty();
}

Piece::Color Board::eGetSquareColor(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].eGetPieceColor();
}

void Board::MovePiece(Position oPos1, Position oPos2)
{
	unsigned int X1 = oPos1.mX;
	unsigned int Y1 = oPos1.mY;
	unsigned int X2 = oPos2.mX;
	unsigned int Y2 = oPos2.mY;

	Square & oPieceSquare = moSquares[X1][Y1];
	Square & oDestSquare = moSquares[X2][Y2];

	oDestSquare.SetPiece(oPieceSquare.poGetPiece());
	oPieceSquare.SetPiece(NULL);
}

void Board::SwitchPieces(Square & oFirstSquare, Square & oSecondSquare) const
{
	Piece * poSwap = oFirstSquare.poGetPiece();
	oFirstSquare.SetPiece(oSecondSquare.poGetPiece());
	oSecondSquare.SetPiece(poSwap);
}

ostream & operator<<(ostream & os, const Board & b)
{
	b.InterfaceOnStream(os);
	return os;
}

Piece * Board::poGetPiece(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].poGetPiece();
}

void Board::SetPiece(Position oPos, Piece * poNewPiece)
{
	moSquares[oPos.mX][oPos.mY].SetPiece(poNewPiece);
}

void Board::PromotePawn(Position oPos, char cNewType)
{
	Piece::Color ePlayerColor = eGetSquareColor(oPos);

	switch(cNewType)
	{
	  case 'R':
		SetPiece(oPos, new Rook(ePlayerColor));
		break;
	  case 'N':
		SetPiece(oPos, new Knight(ePlayerColor));
		break;
	  case 'B':
		SetPiece(oPos, new Bishop(ePlayerColor));
		break;
	  case 'Q':
		SetPiece(oPos, new Queen(ePlayerColor));
		break;
	  default :
		break;
	}
}