
#include "../game_entry.h"

using namespace std;

GameEntry::GameEntry(Position oPos1, Position oPos2) : moPos1(oPos1), moPos2(oPos2), mbIsCommand(false), mstrCommand("")
{

}

GameEntry::GameEntry(string strCommand) : mbIsCommand(true), mstrCommand(strCommand)
{
}

GameEntry::~GameEntry()
{
}

bool GameEntry::bIsCommand()
{
	return mbIsCommand;
}

Position GameEntry::oGetPos1()
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return moPos1;
}

Position GameEntry::oGetPos2()
{
	if(bIsCommand())
		throw exception("This entry is a command");

	return moPos2;
}

std::string GameEntry::strGetCommand()
{
	if(!bIsCommand())
		throw exception("This entry is not a command");

	return mstrCommand;
}

