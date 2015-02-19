#include "base_board.h"

BaseBoard::BaseBoard(void)
{
}

BaseBoard::~BaseBoard(void)
{
}

bool BaseBoard::bIsSquareEmpty(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].bIsEmpty();
}

Piece::Color BaseBoard::eGetSquareColor(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].eGetPieceColor();
}

Piece::PieceType BaseBoard::eGetSquareType(Position oPos) const
{
	return moSquares[oPos.mX][oPos.mY].eGetPieceType();
}

bool BaseBoard::bIsSquareEmpty(unsigned int X, unsigned int Y) const
{
	return bIsSquareEmpty(Position(X, Y));
}

Piece::Color BaseBoard::eGetSquareColor(unsigned int i, unsigned int j) const
{
	return eGetSquareColor(Position(i, j));
}

Piece::PieceType BaseBoard::eGetSquareType(unsigned int i, unsigned int j) const
{
	return eGetSquareType(Position(i, j));
}