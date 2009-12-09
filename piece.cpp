#include "piece.h"

Piece::Color Piece::eGetColor() const
{
	return meColor;
}

void Piece::SetFirstMove(bool bFirstMove)
{
	mbFirstMove = bFirstMove;
}

bool Piece::bHasAlreadyMoved()
{
	return mbFirstMove;
}

Piece::PieceType Piece::eGetType()
{
	return meType;
}