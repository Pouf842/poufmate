#include "interface_console.h"
#include "board.h"

using namespace std;

InterfaceConsole::InterfaceConsole() : mOs("")
{
}

Interface * InterfaceConsole::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceConsole;
	
	return mpoInstance;
}

void InterfaceConsole::DisplayBoard(const Board & oBoard)
{
	mOs << oBoard << endl;
}

void InterfaceConsole::DisplayMessage(string strMessage)
{
	mOs << strMessage << endl;
}

string InterfaceConsole::strGetEntry()
{
	string strCommand;
	cin >> strCommand;

	return strCommand;
}

void InterfaceConsole::DisplayPossibilities(std::string strPossibilities)
{
	mOs << "Possibilities : " << endl;
	for(unsigned int i = 0; i < strPossibilities.size(); ++i)
		if(strPossibilities[i] != ';')
			mOs << strPossibilities[i];
		else
			mOs << endl;

	mOs << endl;
}

void InterfaceConsole::DisplayCurrentPlayer(Piece::Color eCurrentPlayer)
{
	mOs << "Joueur " << (eCurrentPlayer == Piece::WHITE ? "Blanc":"Noir") << endl;
}

void InterfaceConsole::DisplaySelection(Position oPos)
{
	mOs << "Selected piece : " << oPos.mX << oPos.mY << endl;
}

void InterfaceConsole::DisplayInCheck(Position oPos)
{
	mOs << "The king in " << oPos.mX << oPos.mY << " is in check" << endl;
}

void InterfaceConsole::CommitDisplay()
{
	cout << mOs.str();
	mOs.str("");
}

char InterfaceConsole::cGetNewPieceType()
{
	char cNewType = ' ';

	while(1)
	{
		mOs << "Enter the type of the new piece : " << endl;
		mOs << "\tR = Rook" << endl;
		mOs << "\tN = Knight" << endl;
		mOs << "\tB = Bishop" << endl;
		mOs << "\tQ = Queen" << endl;
		mOs << "\tP = Pawn" << endl;

		CommitDisplay();

		cin >> cNewType;

		if(string("RNBQP").find(toupper(cNewType) != string::npos))
			return toupper(cNewType);
	}
}