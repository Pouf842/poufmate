#include "interface_console.h"
#include "Modules/game.h"
#include "Core/board.h"

using namespace std;

extern "C" __declspec(dllexport) Interface * poGetInterface()
{
    Interface * poInterface = new InterfaceConsole();

    return poInterface;
}

int InterfaceConsole::iGetMenuEntry(const std::vector<std::string> oMenu)
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

void InterfaceConsole::DisplayMessage(const std::string strMessage)
{
	cout << strMessage << endl;
}

void InterfaceConsole::DisplayCurrentPlayer(Piece::PIECE_COLOR eCurrentPlayer)
{
	cout << (eCurrentPlayer == Piece::PC_WHITE ? "White":"Black") << " player" << endl;
}

void InterfaceConsole::DisplayBoard(const Board & oBoard)
{
	string strBoardDisplay[1 + 8 * 2 + 1];
	int iCurrentLine = 0;
	strBoardDisplay[iCurrentLine++] = "    0   1   2   3   4   5   6   7";	// Display coordinates

	for(unsigned int i = 0; i < 8; ++i)
	{
		strBoardDisplay[iCurrentLine++] = "   -------------------------------";	// Separator
		strBoardDisplay[iCurrentLine] += (char) ('A' + i);
		strBoardDisplay[iCurrentLine] += " ";	// Display coordinate

		/* For each square of the board */
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);
			strBoardDisplay[iCurrentLine] += "| ";	// Separator

			char cPieceChar = ' ';	// Empty square (default value)

			/* Check the piece type */
			if(!(oBoard.bIsSquareEmpty)(oPos))
			{
                switch((oBoard.eGetSquareType)(oPos))
				{
				  case Piece::PT_ROOK :
					cPieceChar = 'R';
					break;
				  case Piece::PT_BISHOP :
					cPieceChar = 'B';
					break;
				  case Piece::PT_KNIGHT :
					cPieceChar = 'N';
					break;
				  case Piece::PT_QUEEN :
					cPieceChar = 'Q';
					break;
				  case Piece::PT_KING :
					cPieceChar = 'K';
					break;
				  case Piece::PT_PAWN :
					cPieceChar = 'P';
					break;
				}

				/* Black pieces are in lower case */
                if((oBoard.eGetSquareColor)(oPos) == Piece::PC_BLACK)
					cPieceChar = tolower(cPieceChar);
			}

			 strBoardDisplay[iCurrentLine] += cPieceChar;
			 strBoardDisplay[iCurrentLine] += " ";
		}

		strBoardDisplay[iCurrentLine++] += "|";	// End-of-line separator
	}

	strBoardDisplay[iCurrentLine++] = "   -------------------------------";	// Last separator (bottom of the board)

	if(mpoModule->bIsGame())
	{
		Game * poGame = (Game*) mpoModule;

		Position * poSelectedPosition = NULL;
		if(poSelectedPosition = poGame->poGetSelectedPosition())
		{
			int X = poSelectedPosition->mY;
			int Y = poSelectedPosition->mX;

			for(unsigned j = 0; j < 5; ++j)
			{
				strBoardDisplay[1 + Y * 2][2 + X * 4 + j] = '*';
				strBoardDisplay[3 + Y * 2][2 + X * 4 + j] = '*';
			}

			strBoardDisplay[2 + Y * 2][2 + X * 4] = '*';
			strBoardDisplay[2 + Y * 2][2 + X * 4 + 4] = '*';			
		}
	}

	for(unsigned int i = 0; i < iCurrentLine; ++i)
		cout << strBoardDisplay[i] << endl;
}

void InterfaceConsole::DisplayModule(const Module * oModule)
{
	try
	{
		if(!oModule)
			throw exception("Le module n'est pas défini");

		DisplayBoard(oModule->oGetBoard());

		if(oModule->eGetType() == Module::MT_ONE_PLAYER_GAME
		|| oModule->eGetType() == Module::MT_TWO_PLAYER_GAME)
			DisplayCurrentPlayer(((Game*)oModule)->eGetCurrentPlayer());
	}
	catch(exception & e)
	{
		DisplayMessage(e.what());
		throw e;
	}
}

string InterfaceConsole::strGetEntry()
{
	string strCommand;
	cin >> strCommand;

	return strCommand;
}

Entry InterfaceConsole::oGetEntry()
{
	DisplayModule(mpoModule);

	string strEntry;

	while(1)
	{
		try
		{
			string strFirstSelection = strGetEntry();

			if(strFirstSelection == "c")
				return Entry(Entry::EC_CANCEL_MOVE);
			else if(strFirstSelection == "r")
				return Entry(Entry::EC_RESET_GAME);
			else if(strFirstSelection == "x")
				return Entry(Entry::EC_STOP_GAME);
			else if(strFirstSelection == "q")
				return Entry(Entry::EC_QUIT_GAME);
			else if(strFirstSelection == "h")
				DisplayHelp();
			else
			{
				string strPosition = strFirstSelection;

				if(strPosition[0] >= 'a' && strPosition[0] <= 'h')
					strPosition[0] = strPosition[0] + 'A' - 'a';

				strPosition[0] = strPosition[0] - 'A' + '0';	// Conversion of alpha A-H to digit 1-8

				return Entry(strPosition);
			}
		}
		catch(exception & e)
		{
			DisplayMessage(("Erreur : " + string(e.what())).c_str());
		}
	}

	return Entry(Entry::EC_NONE);
}

std::string InterfaceConsole::strGetIPEntry()
{
	return "";
}

std::string InterfaceConsole::strGetPortEntry()
{
	return "";
}

Piece::PIECE_TYPE InterfaceConsole::cGetNewPieceType(const Piece::PIECE_COLOR)
{
	return Piece::PT_KING;
}

Piece::PIECE_COLOR InterfaceConsole::cGetPlayerColorChoice()
{
	return Piece::PC_WHITE;
}

InterfaceConsole::~InterfaceConsole()
{
}

Entry::ENTRY_COMMAND InterfaceConsole::GameOver(std::string strMessage)
{
	cout << "Game over !" << endl;
	cout << strMessage << endl;

	char cCommand = ' ';

	while(cCommand != 'r'
	   && cCommand != 'x'
	   && cCommand != 'q')
	{
		cout << "Enter 'r' to reset the game, x to return to the menu, or q to quit" << endl;
		cin >> cCommand;
	}

	switch(cCommand)
	{
	case 'r' :
		return Entry::EC_RESET_GAME;
		break;
	case 'x' :
		return Entry::EC_STOP_GAME;
		break;
	case 'q' :
		return Entry::EC_QUIT_GAME;
		break;
	}

	return Entry::EC_NONE;
}

void InterfaceConsole::DisplayHelp()
{
	cout << "Commandes :" << endl;
	cout << "h : Afficher cette aide" << endl;
	cout << "c : Annuler un coup" << endl;
	cout << "r : Recommencer une partie" << endl;
	cout << "x : Quitter la partie" << endl;
	cout << "q : Quitter le jeu" << endl;
}
/*
InterfaceConsole::InterfaceConsole() : meNewPieceType(Piece::NONE), meNewPieceColor(Piece::PC_WHITE)
{
}

InterfaceConsole::~InterfaceConsole()
{
}

Entry InterfaceConsole::oGetEntry(Game & oGame)
{
	DisplayGame(oGame);
	
	if(oGame.bIsOver())
	{
		Entry oEntry(strGetEntry());

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
			|| strFirstSelection == "c"
			|| strFirstSelection == "r"
			|| strFirstSelection == "q")
				return Entry(strFirstSelection);

			oGame.CheckSelectionCoords(strFirstSelection);

			strSecondSelection = strGetEntry();

			if(strSecondSelection == "x"
			|| strSecondSelection == "c"
			|| strSecondSelection == "r"
			|| strSecondSelection == "q")
				return Entry(strSecondSelection);

			bSelectionOk = true;
		}
		catch(exception & e)
		{
			DisplayMessage(e.what());
		}
	}

	return Entry(strFirstSelection, strSecondSelection);
}

EditionEntry InterfaceConsole::oGetEditionEntry(const GameEdition & oGameEdition)
{
	static bool bAlreadyEntered = false;

    DisplayBoard(oGameEdition.oGetBoard)());

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
				meNewPieceColor = Piece::PC_WHITE;
			else
				meNewPieceColor = Piece::PC_BLACK;
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

	string strSelected = (meNewPieceColor == Piece::PC_WHITE ? "White " : "Black ");

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

char InterfaceConsole::cGetNewPieceType(Piece::PIECE_COLOR)
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

char InterfaceConsole::cGetPlayerColorChoice()
{
	cout << "Which color would you like to play ?" << endl;
	cout << "\tW : White" << endl;
	cout << "\tB : Black" << endl;

	char cColor = ' ';
	cin >> cColor;

	/* While the user doesn't entry W or B * /
	while(cColor != 'W' && cColor != 'B')
	{
		cout << "Your answer has to be W (White) or B (Black)" << endl;
		cin >> cColor;
	}

	return cColor;
}
*/