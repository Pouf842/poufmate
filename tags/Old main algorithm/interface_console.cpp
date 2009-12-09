#include "interface_console.h"
#include "board.h"

using namespace std;

InterfaceConsole::InterfaceConsole()
{
}

Interface * InterfaceConsole::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceConsole;
	
	return mpoInstance;
}

void InterfaceConsole::DisplayBoard(const Board & oBoard) const
{
	cout << oBoard << endl;
}

void InterfaceConsole::DisplayMessage(string strMessage) const
{
	cout << strMessage << endl;
}

string InterfaceConsole::strGetEntry() const
{
	string strCommand;
	cin >> strCommand;

	return strCommand;
}

void InterfaceConsole::DisplayPossibilities(std::string strPossibilities) const
{
	for(unsigned int i = 0; i < strPossibilities.size(); ++i)
		if(strPossibilities[i] != ';')
			cout << strPossibilities[i];
		else
			cout << endl;
}

void InterfaceConsole::DisplaySelection(std::string strSelection) const
{
}

void InterfaceConsole::DisplayInCheck(unsigned int X, unsigned int Y) const
{
	cout << "The king in " << X << Y << " is in check" << endl;
}