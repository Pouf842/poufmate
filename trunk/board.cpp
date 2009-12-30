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

void Board::Init()
{
	/* Creating pawns */
	for(unsigned int i = 0; i < 8; ++i)
	{
		moSquares[1][i].SetPiece(new Pawn(Piece::BLACK));
		moSquares[6][i].SetPiece(new Pawn(Piece::WHITE));
	}

	/* Creating rooks */
	moSquares[0][0].SetPiece(new Rook(Piece::BLACK));
	moSquares[0][7].SetPiece(new Rook(Piece::BLACK));
	moSquares[7][0].SetPiece(new Rook(Piece::WHITE));
	moSquares[7][7].SetPiece(new Rook(Piece::WHITE));

	/* Creating knights */
	moSquares[0][1].SetPiece(new Knight(Piece::BLACK));
	moSquares[0][6].SetPiece(new Knight(Piece::BLACK));
	moSquares[7][1].SetPiece(new Knight(Piece::WHITE));
	moSquares[7][6].SetPiece(new Knight(Piece::WHITE));

	/* Creating bishops */
	moSquares[0][2].SetPiece(new Bishop(Piece::BLACK));
	moSquares[0][5].SetPiece(new Bishop(Piece::BLACK));
	moSquares[7][2].SetPiece(new Bishop(Piece::WHITE));
	moSquares[7][5].SetPiece(new Bishop(Piece::WHITE));

	/* Creating queens */
	moSquares[0][3].SetPiece(new Queen(Piece::BLACK));
	moSquares[7][3].SetPiece(new Queen(Piece::WHITE));

	/* Creating kings */
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

Piece * Board::poGetPiece(unsigned int i, unsigned int j) const
{
	return moSquares[i][j].poGetPiece();
}

Piece * Board::poGetPiece(Position oPos) const
{
	return poGetPiece(oPos.mX, oPos.mY);
}

void Board::SetPiece(Position oPos, Piece * poNewPiece)
{
	moSquares[oPos.mX][oPos.mY].SetPiece(poNewPiece);
}
