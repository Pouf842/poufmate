#include "square.h"
#include <exception>

Square::Square() : mpoPiece(0)
{
}

char Square::cGetChar() const
{
	if(mpoPiece)
		return mpoPiece->cGetChar();
	else
		return ' ';
}

bool Square::bIsEmpty() const
{
	return (mpoPiece == 0);
}

void Square::SetPiece(Piece * poNewPiece)
{
	mpoPiece = poNewPiece;
}

Piece::Color Square::eGetPieceColor() const
{
	if(mpoPiece)
		return mpoPiece->eGetColor();
	else
		throw std::exception("Empty square");
}

Piece * Square::poGetPiece() const
{
	return mpoPiece;
}