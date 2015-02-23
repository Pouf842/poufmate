#include "entry.h"

using namespace std;

Entry::Entry() : mbIsCommand(true), meCommand(EC_NONE)
{
}

Entry::Entry(Position oPos) : moPos(oPos), mbIsCommand(false), meCommand(EC_NONE)
{

}

Entry::Entry(ENTRY_COMMAND eCommand) : mbIsCommand(true), meCommand(eCommand)
{
}

Entry::~Entry()
{
}

bool Entry::bIsCommand() const
{
	return mbIsCommand;
}

Position Entry::oGetPos() const
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return moPos;
}

Entry::ENTRY_COMMAND Entry::eGetCommand() const
{
	if(!bIsCommand())
		throw exception("This entry is not a command");

	return meCommand;
}

