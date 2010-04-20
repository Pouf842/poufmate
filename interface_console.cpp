#include "interface_console.h"
#include "board.h"

using namespace std;

InterfaceConsole::InterfaceConsole() : meNewPieceType(Piece::NONE), meNewPieceColor(Piece::WHITE)
{
}

InterfaceConsole::~InterfaceConsole()
{
}

GameEntry InterfaceConsole::oGetGameEntry(Game & oGame)
{
	DisplayGame(oGame);
	
	if(oGame.bIsOver())
	{
		GameEntry oEntry(strGetEntry());

		while(!oEntry.bIsCommand())
		{
			DisplayMessage("Press x to exit.");
			oEntry = strGetEntry();
		}
	}

	bool bSelectionOk = false;
	string strFirstSelection;
	string strSecondSelection;

	while(!bSelectionOk)
	{
		try
		{
			strFirstSelection = strGetEntry();

			if(strFirstSelection == "x"
			|| strFirstSelection == "c")
				return GameEntry(strFirstSelection);

			oGame.CheckSelectionCoords(strFirstSelection);

			strSecondSelection = strGetEntry();

			if(strSecondSelection == "x"
			|| strSecondSelection == "c")
				return GameEntry(strSecondSelection);

			bSelectionOk = true;
		}
		catch(exception & e)
		{
			DisplayMessage(e.what());
		}
	}

	return GameEntry(strFirstSelection, strSecondSelection);
}

void InterfaceConsole::DisplayGame(const Game & oGame)
{
	DisplayBoard(oGame.oGetBoard());

	if(oGame.bIsWhiteInCheck())
		DisplayGameOver("White king is in check");

	if(oGame.bIsBlackInCheck())
		DisplayGameOver("Black king is in check");

	if(oGame.bIsWhiteCheckMate())
	{
		DisplayGameOver("White king is check mate !");
		return;
	}

	if(oGame.bIsBlackCheckMate())
	{
		DisplayGameOver("Black king is check mate !");
		return;
	}

	if(oGame.bIsOver())
	{
		DisplayGameOver();
		return;
	}
	
	DisplayCurrentPlayer(oGame.eGetCurrentPlayer());
}

void InterfaceConsole::DisplayGameOver(std::string strMessage)
{
	cout << "Game over !" << endl;
	cout << strMessage << endl;
}

EditionEntry InterfaceConsole::oGetEditionEntry(const GameEdition & oGameEdition)
{
	static bool bAlreadyEntered = false;

	DisplayBoard(oGameEdition.oGetBoard());

	if(!bAlreadyEntered)
		DisplayEditionCommands();

	bAlreadyEntered = true;
	while(1)
	{
		DisplaySelectedPiece();
		string strEntry = strGetEntry();

		if(bIsPieceSelection(strEntry))
		{
			switch(toupper(strEntry[0]))
			{
			  case 'R' :
				meNewPieceType = Piece::ROOK;
				break;
			  case 'N' :
				meNewPieceType = Piece::KNIGHT;
				break;
			  case 'B' :
				meNewPieceType = Piece::BISHOP;
				break;
			  case 'Q' :
				meNewPieceType = Piece::QUEEN;
				break;
			  case 'K' :
				meNewPieceType = Piece::KING;
				break;
			  case 'P' :
				meNewPieceType = Piece::PAWN;
				break;
				break;
			  case '*' :
				meNewPieceType = Piece::NONE;
				break;
			  default :
				DisplayMessage("Unknown piece type");
				break;
			}

			if(toupper(strEntry[0]) == strEntry[0])
				meNewPieceColor = Piece::WHITE;
			else
				meNewPieceColor = Piece::BLACK;
		}
		else if(bIsCoordinates(strEntry))
			return EditionEntry(strEntry, meNewPieceType, meNewPieceColor);
		else if(bIsCommand(strEntry))
			if(strEntry[0] == 'h')
				DisplayEditionCommands();
			else
			{
				bAlreadyEntered = false;
				return EditionEntry(strEntry);
			}
		else
		{
			DisplayMessage("Invalid command");
			DisplayEditionCommands();
		}
	}
}

void InterfaceConsole::DisplaySelectedPiece()
{
	cout << "Selected piece : ";
	if(meNewPieceType == Piece::NONE)
	{
		cout << "Empty square" << endl;
		return;
	}

	string strSelected = (meNewPieceColor == Piece::WHITE ? "White " : "Black ");

	switch(meNewPieceType)
	{
	  case Piece::ROOK :
		strSelected += "rook";
		break;
	  case Piece::KNIGHT :
		strSelected += "knight";
		break;
	  case Piece::BISHOP :
		strSelected += "bishop";
		break;
	  case Piece::QUEEN :
		strSelected += "queen";
		break;
	  case Piece::KING :
		strSelected += "king";
		break;
	  case Piece::PAWN :
		strSelected += "pawn";
		break;
	  default :
	    string strSelected = "Unknown piece type";
		break;
	}

	cout << strSelected << endl;
}

bool InterfaceConsole::bIsCommand(string strEntry)
{
	return (strEntry.size() == 1 && (string("xX12").find(strEntry[0]) != -1));
}

bool InterfaceConsole::bIsCoordinates(string strEntry)
{
	if(strEntry.size() != 2
	|| !isdigit(strEntry[0])
	|| !isdigit(strEntry[1]))
		return false;

	return true;
}

bool InterfaceConsole::bIsPieceSelection(string strEntry)
{
	return (strEntry.size() == 1 && (string("RNBQKPrnbqkp*").find(strEntry[0]) != -1));
}

void InterfaceConsole::DisplayEditionCommands()
{
	cout << "Commands : " << endl;
	cout << "\tR/r : White/Black rook" << endl;
	cout << "\tN/n : White/Black knight" << endl;
	cout << "\tB/b : White/Black bishop" << endl;
	cout << "\tQ/q : White/Black queen" << endl;
	cout << "\tK/k : White/Black king" << endl;
	cout << "\tP/p : White/Black pawn" << endl;
	cout << "\t* : Empty square" << endl;
	cout << "\tXY : coordinates to place the selected piece" << endl;
	cout << "\tx : Exit" << endl;
	cout << "\t1 : Play game in one player mode" << endl;
	cout << "\t2 : Play game in two player mode" << endl;
	cout << "\th : Display this help" << endl;
}

std::string InterfaceConsole::strGetIPEntry()
{
	cout << "Server IP : " << flush;

	string strIP;
	bool bIPOk = false;

	while(!bIPOk)
	{
		cin >> strIP;

		try
		{
			if(strIP.size() < 7
			|| strIP.size() > 15)
				throw exception("Invalid IP format");
			
			unsigned int iDigitCount = 0;
			for(unsigned int i = 0; i < strIP.size(); ++i)
			{
				if(!isdigit(strIP[i]) && strIP[i] != '.')
					throw exception("Invalid IP format");

				if(strIP[i] == '.')
				{
					if(iDigitCount == 0 || iDigitCount > 3)
						throw exception("Invalid IP format");
					else
						iDigitCount = 0;
				}
				else
					++iDigitCount;
			}

			if(iDigitCount > 3)
				throw exception("Invalid IP format");

			bIPOk = true;
		}
		catch(exception & e)
		{
			cout << endl;
			DisplayMessage(e.what());
		}
	}

	return strIP;
}

void InterfaceConsole::Pause()
{
	string strEmpty;
	cin >> strEmpty;
}

std::string InterfaceConsole::strGetPortEntry()
{
	cout << "Port number : " << flush;

	string strPort;
	int iPort;

	cin >> strPort;
	iPort = atoi(strPort.c_str());
	while(!iPort || iPort > 65535 || iPort < 1)
	{
		DisplayMessage("Invalid port");
		cin >> strPort;
	}

	return strPort;
}

Interface * InterfaceConsole::poGetInstance()
{
	if(!mpoInstance)
		mpoInstance = new InterfaceConsole;
	
	return mpoInstance;
}

void InterfaceConsole::DisplayBoard(const Board & oBoard)
{
	cout << "    0   1   2   3   4   5   6   7" << endl;	// Display coordinates

	for(unsigned int i = 0; i < 8; ++i)
	{
		cout << "   -------------------------------" << endl;	// Separator
		cout << i << " ";	// Display coordinate

		/* For each square of the board */
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);
			cout << "| ";	// Separator

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

				/* Black pieces are in lower case */
				if(oBoard.poGetPiece(oPos)->eGetColor() == Piece::BLACK)
					cPieceChar = tolower(cPieceChar);
			}

			 cout << cPieceChar << " ";
		}

		cout << "|" << endl;	// End-of-line separator
	}

	cout << "   -------------------------------" << endl;	// Last separator (bottom of the board)
}

void InterfaceConsole::AddMessage(string strMessage)
{
	DisplayMessage(strMessage);
}

void InterfaceConsole::DisplayMessage(string strMessage)
{
	cout << strMessage << endl;
}

string InterfaceConsole::strGetEntry()
{
	string strCommand;
	cin >> strCommand;

	return strCommand;
}

void InterfaceConsole::DisplayPossibilities(vector<Position> oPossibilities)
{
	cout << "Possibilities : " << endl;

	for(unsigned int i = 0; i < oPossibilities.size(); ++i)
		cout << "\t" << oPossibilities[i].mX << oPossibilities[i].mY << endl;

	cout << endl;
}

void InterfaceConsole::DisplayCurrentPlayer(Piece::Color eCurrentPlayer)
{
	cout << (eCurrentPlayer == Piece::WHITE ? "White":"Black") << " player" << endl;
}

char InterfaceConsole::cGetNewPieceType(Piece::Color)
{
	char cNewType = ' ';

	// While the user didn't enter a valid entry
	while(1)
	{
		cout << "Enter the type of the new piece : " << endl;
		cout << "\tR = Rook" << endl;
		cout << "\tN = Knight" << endl;
		cout << "\tB = Bishop" << endl;
		cout << "\tQ = Queen" << endl;

		cin >> cNewType;

		if(string("RNBQrnbq").find(toupper(cNewType) != string::npos))
			return toupper(cNewType);

		cout << "Invalid entry" << endl;
	}
}

int InterfaceConsole::iGetMenuEntry(const vector<string> & oMenu)
{
	/* Display all the options of the menu */
	for(unsigned int i = 0; i < oMenu.size(); ++i)
		cout << oMenu[i] << endl;

	unsigned char cChoice = '0';
	bool bOk = false;

	/* While the user doesn't entry a valid option */
	while(1)
	{
		cin >> cChoice;

		if(cChoice >= '1' && cChoice <= ('0' + oMenu.size()))
			return cChoice - '0';
		else if(cChoice == 'x')
			return oMenu.size();	// The last option of the menu is to quit
	}
}

char InterfaceConsole::cGetPlayerColorChoice()
{
	cout << "Which color would you like to play ?" << endl;
	cout << "\tW : White" << endl;
	cout << "\tB : Black" << endl;

	char cColor = ' ';
	cin >> cColor;

	/* While the user doesn't entry W or B */
	while(cColor != 'W' && cColor != 'B')
	{
		cout << "Your answer has to be W (White) or B (Black)" << endl;
		cin >> cColor;
	}

	return cColor;
}
