#include "piece.h"

Piece::Color Piece::eGetColor() const
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

Piece::PieceType Piece::eGetType()
{
	return meType;
}