#include "entry.h"

#include <iostream>

using namespace std;

Entry::Entry() : mbIsCommand(true), meCommand(EC_NONE), mbIsPiece(false), mePieceType(Piece::PT_NONE), mePieceColor(Piece::PC_WHITE)
{
}

Entry::Entry(Position oPos) : moPos(oPos), mbIsCommand(false), meCommand(EC_NONE), mbIsPiece(false), mePieceType(Piece::PT_NONE), mePieceColor(Piece::PC_WHITE)
{

}

Entry::Entry(ENTRY_COMMAND eCommand) : mbIsCommand(true), meCommand(eCommand), mbIsPiece(false), mePieceType(Piece::PT_NONE), mePieceColor(Piece::PC_WHITE)
{
}

Entry::Entry(Piece::PIECE_TYPE ePieceType, Piece::PIECE_COLOR ePieceColor) : mbIsPiece(true), mePieceType(ePieceType), mePieceColor(ePieceColor), mbIsCommand(false), meCommand(EC_NONE)
{
}

Entry::~Entry()
{
}

bool Entry::bIsCommand() const
{
	return mbIsCommand;
}

bool Entry::bIsPiece() const
{
	return mbIsPiece;
}

Position Entry::oGetPos() const
{
	try
	{
		if(bIsCommand())
			throw exception("This entry is a command");

		return moPos;
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Entry::ENTRY_COMMAND Entry::eGetCommand() const
{
	try
	{
		if(!bIsCommand())
			throw exception("This entry is not a command");

		return meCommand;
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Piece::PIECE_TYPE  Entry::eGetPieceType() const
{
	return mePieceType;
}

Piece::PIECE_COLOR Entry::eGetPieceColor() const
{
	return mePieceColor;
}