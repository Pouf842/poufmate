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

	cout << endl;
}

void InterfaceConsole::DisplaySelection(Coordinates oCoords) const
{
	cout << oCoords.mX << oCoords.mY << endl;
}

void InterfaceConsole::DisplayInCheck(Coordinates oCoords) const
{
	cout << "The king in " << oCoords.mX << oCoords.mY << " is in check" << endl;
}