#include "interface_console.h"
#include "board.h"

using namespace std;

InterfaceConsole::InterfaceConsole() : mOs("")
{
}

InterfaceConsole::~InterfaceConsole()
{
}

Interface * InterfaceConsole::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceConsole;
	
	return mpoInstance;
}

void InterfaceConsole::DisplayGameOver(std::string)
{
}

void InterfaceConsole::DisplayBoard(const Board & oBoard)
{
	mOs << "    0   1   2   3   4   5   6   7" << endl;	// Display coordinates

	for(unsigned int i = 0; i < 8; ++i)
	{
		mOs << "   -------------------------------" << endl;	// Separator
		mOs << i << " ";	// Display coordinate

		/* For each square of the board */
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);
			mOs << "| ";	// Separator

			char cPieceChar = ' ';	// Empty square (default value)

			/* Check the piece type */
			if(!oBoard.bIsSquareEmpty(oPos))
			{
				switch(oBoard.eGetSquareType(oPos))
				{
				  case Piece::ROOK :
					cPieceChar = 'R';
					break;
				  case Piece::BISHOP :
					cPieceChar = 'B';
					break;
				  case Piece::KNIGHT :
					cPieceChar = 'N';
					break;
				  case Piece::QUEEN :
					cPieceChar = 'Q';
					break;
				  case Piece::KING :
					cPieceChar = 'K';
					break;
				  case Piece::PAWN :
					cPieceChar = 'P';
					break;
				}

				/* Black pieces ar in lower case */
				if(oBoard.poGetPiece(oPos)->eGetColor() == Piece::BLACK)
					cPieceChar = tolower(cPieceChar);
			}

			 mOs << cPieceChar << " ";
		}

		mOs << "|" << endl;	// End-of-line separator
	}

	mOs << "   -------------------------------" << endl;	// Last separator (bottom of the board)
}

void InterfaceConsole::DisplayMessage(string strMessage)
{
	mOs << strMessage << endl;
}

string InterfaceConsole::strGetEditionEntry()
{
	cout << "New piece type :" << endl;
	cout << "\tR/r : White/Black rook" << endl;
	cout << "\tK/k : White/Black knight" << endl;
	cout << "\tB/b : White/Black bishop" << endl;
	cout << "\tQ/q : White/Black queen" << endl;
	cout << "\tK/k : White/Black king" << endl;
	cout << "\tP/p : White/Black pawn" << endl;
	cout << "\t# : None" << endl;

	cout << "Actions :" << endl;
	cout << "\tx : Quit" << endl;
	cout << "\t1 : One player game" << endl;
	cout << "\t2 : Two player game" << endl;

	string strCommand;
	cin >> strCommand;

	return strCommand;
}

string InterfaceConsole::strGetEntry()
{
	string strCommand;
	cin >> strCommand;

	return strCommand;
}

void InterfaceConsole::DisplayPossibilities(vector<Position> oPossibilities)
{
	mOs << "Possibilities : " << endl;
	for(unsigned int i = 0; i < oPossibilities.size(); ++i)
		mOs << "\t" << oPossibilities[i].mX << oPossibilities[i].mY << endl;

	mOs << endl;
}

void InterfaceConsole::DisplayCurrentPlayer(Piece::Color eCurrentPlayer)
{
	mOs << (eCurrentPlayer == Piece::WHITE ? "White":"Black") << " player" << endl;
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

char InterfaceConsole::cGetNewPieceType(Piece::Color eColor)
{
	char cNewType = ' ';

	while(1)
	{
		mOs << "Enter the type of the new piece : " << endl;
		mOs << "\tR = Rook" << endl;
		mOs << "\tN = Knight" << endl;
		mOs << "\tB = Bishop" << endl;
		mOs << "\tQ = Queen" << endl;

		CommitDisplay();

		cin >> cNewType;

		if(string("RNBQrnbq").find(toupper(cNewType) != string::npos))
			return toupper(cNewType);
	}
}

int InterfaceConsole::iGetMenuEntry(const Menu & oMenu)
{
	for(unsigned int i = 0; i < oMenu.size(); ++i)
		cout << oMenu.oGetOptions()[i] << endl;

	int i = 0;
	cin >> i;

	return i;
}

void InterfaceConsole::DisplayMenu(const Menu & oMenu)
{
}

char InterfaceConsole::cGetPlayerColorChoice()
{
	cout << "Which color would you like to play ?" << endl;
	cout << "\tW : White" << endl;
	cout << "\tB : Black" << endl;

	char cColor = ' ';
	cin >> cColor;

	while(cColor != 'W' && cColor != 'B')
	{
		cout << "Your answer has to be W (White) or B (Black)" << endl;
		cin >> cColor;
	}

	return cColor;
}