#include <iostream>
#include "Core\board.h"
#include "Core\position.h"
#include "Pieces\rook.h"
#include "Pieces\pawn.h"
#include "Pieces\knight.h"
#include "Pieces\bishop.h"
#include "Pieces\queen.h"
#include "Pieces\king.h"

using namespace std;

void Board::Init()
{
	/* Creating pawns */
	for(unsigned int i = 0; i < 8; ++i)
	{
		moSquares[1][i].SetPiece(new Pawn(Piece::PC_BLACK));
		moSquares[6][i].SetPiece(new Pawn(Piece::PC_WHITE));
	}

	/* Creating rooks */
	moSquares[0][0].SetPiece(new Rook(Piece::PC_BLACK));
	moSquares[0][7].SetPiece(new Rook(Piece::PC_BLACK));
	moSquares[7][0].SetPiece(new Rook(Piece::PC_WHITE));
	moSquares[7][7].SetPiece(new Rook(Piece::PC_WHITE));

	/* Creating knights */
	moSquares[0][1].SetPiece(new Knight(Piece::PC_BLACK));
	moSquares[0][6].SetPiece(new Knight(Piece::PC_BLACK));
	moSquares[7][1].SetPiece(new Knight(Piece::PC_WHITE));
	moSquares[7][6].SetPiece(new Knight(Piece::PC_WHITE));

	/* Creating bishops */
	moSquares[0][2].SetPiece(new Bishop(Piece::PC_BLACK));
	moSquares[0][5].SetPiece(new Bishop(Piece::PC_BLACK));
	moSquares[7][2].SetPiece(new Bishop(Piece::PC_WHITE));
	moSquares[7][5].SetPiece(new Bishop(Piece::PC_WHITE));

	/* Creating queens */
	moSquares[0][3].SetPiece(new Queen(Piece::PC_BLACK));
	moSquares[7][3].SetPiece(new Queen(Piece::PC_WHITE));

	/* Creating kings */
	moSquares[0][4].SetPiece(new King(Piece::PC_BLACK));
	moSquares[7][4].SetPiece(new King(Piece::PC_WHITE));
}

bool Board::bIsSquareEmpty(unsigned int X, unsigned int Y) const
{
	return bIsSquareEmpty(Position(X, Y));
}

bool Board::bIsSquareEmpty(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].bIsEmpty();
}

Piece::PIECE_COLOR Board::eGetSquareColor(Position oPos) const
{
	return eGetSquareColor(oPos.mX, oPos.mY);
}

Piece::PIECE_COLOR Board::eGetSquareColor(unsigned int i, unsigned int j) const
{
	return moSquares[i][j].eGetPieceColor();
}

Piece::PIECE_TYPE Board::eGetSquareType(Position oPos) const
{
	return eGetSquareType(oPos.mX, oPos.mY);
}

Piece::PIECE_TYPE Board::eGetSquareType(unsigned int i, unsigned int j) const
{
	return moSquares[i][j].eGetPieceType();
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
