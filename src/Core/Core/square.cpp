#include "square.h"

#include <exception>
#include <iostream>

using namespace std;

Square::Square() : mpoPiece(0)
{
}

bool Square::bIsEmpty() const
{
	return (mpoPiece == NULL);
}

void Square::SetPiece(Piece * poNewPiece)
{
	mpoPiece = poNewPiece;
}

Piece::PIECE_COLOR Square::eGetPieceColor() const
{
	try
	{
		if(!bIsEmpty())
			return mpoPiece->eGetColor();
		else
			throw exception("Empty square");
	}
	catch(exception & e)
	{
		cout << __FILE__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Piece::PIECE_TYPE Square::eGetPieceType() const
{
	try
	{
		if(!bIsEmpty())
			return mpoPiece->eGetType();
		else
			throw exception("Empty square");
	}
	catch(exception & e)
	{
		cout << __FILE__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Piece * Square::poGetPiece() const
{
	return mpoPiece;
}