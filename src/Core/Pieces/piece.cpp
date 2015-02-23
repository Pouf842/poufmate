#include "piece.h"

Piece::PIECE_COLOR Piece::eGetColor() const
{
	return meColor;
}

void Piece::SetFirstMove(bool bFirstMove)
{
	mbFirstMove = bFirstMove;
}

bool Piece::bHasAlreadyMoved() const
{
	return !bIsFirstMove();
}

bool Piece::bIsFirstMove() const
{
	return mbFirstMove;
}

Piece::PIECE_TYPE Piece::eGetType() const
{
	return meType;
}