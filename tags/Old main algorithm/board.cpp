#include <iostream>
#include "board.h"
#include "tower.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

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

	moSquares[0][0].SetPiece(new Tower(Piece::BLACK));
	moSquares[0][7].SetPiece(new Tower(Piece::BLACK));
	moSquares[7][0].SetPiece(new Tower(Piece::WHITE));
	moSquares[7][7].SetPiece(new Tower(Piece::WHITE));

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
	return moSquares[X][Y].bIsEmpty();
}

Piece::Color Board::eGetSquareColor(unsigned int X, unsigned int Y) const
{
	return moSquares[X][Y].eGetPieceColor();
}

void Board::MovePiece(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2)
{
	Square & oPieceSquare = moSquares[X1][Y1];
	Square & oDestSquare = moSquares[X2][Y2];

	if(oDestSquare.bIsEmpty())
		SwitchPieces(oPieceSquare, oDestSquare);
	else
	{
		oDestSquare.SetPiece(oPieceSquare.poGetPiece());
		oPieceSquare.SetPiece(NULL);
	}

	oDestSquare.poGetPiece()->SetFirstMove(false);
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

Piece * Board::poGetPiece(unsigned int X, unsigned int Y) const
{
	return moSquares[X][Y].poGetPiece();
}

void Board::SetPiece(unsigned int X, unsigned int Y, Piece * poNewPiece)
{
	if(X < 0 || X > 7 || Y < 0 || Y > 7)
		throw exception("Invalid coordinates");

	moSquares[X][Y].SetPiece(poNewPiece);
}