
#include "edition_entry.h"

using namespace std;

EditionEntry::EditionEntry(string strCommand) : mbIsCommand(true), mstrCommand(strCommand)
{
}

EditionEntry::EditionEntry(Position oPos, Piece::PieceType eType, Piece::Color eColor) : moNewPiecePosition(oPos), meNewPieceType(eType), meNewPieceColor(eColor), mbIsCommand(false), mstrCommand("")
{
}

EditionEntry::~EditionEntry()
{
}

bool EditionEntry::bIsCommand()
{
	return mbIsCommand;
}

std::string EditionEntry::strGetCommand()
{
	if(!bIsCommand())
		throw exception("This entry is not a command");

	return mstrCommand;
}

Piece::PieceType EditionEntry::eGetPieceType()
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return meNewPieceType;
}

Piece::Color EditionEntry::eGetPieceColor()
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return meNewPieceColor;
}

Position EditionEntry::oGetPosition()
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return moNewPiecePosition;
}
