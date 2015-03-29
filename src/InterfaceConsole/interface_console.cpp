#include "interface_console.h"
#include "Modules/game.h"
#include "Modules/game_edition.h"
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

void InterfaceConsole::DisplayCurrentPlayer()
{
	try
	{
		if(mpoModule->eGetType() != Module::MT_GAME)
			throw exception("Cannot display in check player in a non-game module");

		Piece::PIECE_COLOR eCurrentPlayer = ((Game*) mpoModule)->eGetCurrentPlayer();

		cout << (eCurrentPlayer == Piece::PC_WHITE ? "White" : "Black") << " player" << endl;
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void InterfaceConsole::DisplayPlayerInCheck()
{
	try
	{
		if(mpoModule->eGetType() != Module::MT_GAME)
			throw exception("Cannot display in check player in a non-game module");

		bool bIsWhiteInCheck = ((Game*) mpoModule)->bIsPlayerInCheck(Piece::PC_WHITE);
		bool bIsBlackInCheck = ((Game*) mpoModule)->bIsPlayerInCheck(Piece::PC_BLACK);

		if(bIsWhiteInCheck)
			cout << "White player in check" << endl;
		else if(bIsBlackInCheck)
			cout << "Black player in check" << endl;	
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
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
			if(!oBoard.bIsSquareEmpty(oPos))
			{
                switch(oBoard.eGetSquareType(oPos))
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
                if(oBoard.eGetSquareColor(oPos) == Piece::PC_BLACK)
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

		if(oModule->eGetType() == Module::MT_GAME)
		{
			DisplayCurrentPlayer();
			DisplayPlayerInCheck();
		}
		else if(oModule->eGetType() == Module::MT_EDITION)
			DisplayEditionSelection();
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
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

	while(1)
	{
		try
		{
			string strEntry = strGetEntry();

			if(strEntry == "h")
			{
				DisplayHelp();
				return Entry::EC_NONE;
			}

			if(strEntry[0] == 'P'
			|| strEntry[0] == 'p')
				return eGetSelectionPieceEntry(strEntry);
			else
			{
				if(strEntry == "c")
					return Entry(Entry::EC_CANCEL_MOVE);
				else if(strEntry == "r")
					return Entry(Entry::EC_RESET_GAME);
				else if(strEntry == "x")
					return Entry(Entry::EC_STOP_GAME);
				else if(strEntry == "q")
					return Entry(Entry::EC_QUIT_GAME);
				else if(strEntry == "1")
					return Entry(Entry::EC_ONE_PLAYER_GAME);
				else if(strEntry == "2")
					return Entry(Entry::EC_TWO_PLAYERS_GAME);
				else if(strEntry == "h")
					DisplayHelp();
				else
				{
					string strPosition = strEntry;

					if(strPosition[0] >= 'a' && strPosition[0] <= 'h')
						strPosition[0] = strPosition[0] + 'A' - 'a';

					strPosition[0] = strPosition[0] - 'A' + '0';	// Conversion of alpha A-H to digit 1-8

					return Entry(strPosition);
				}
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

Piece::PIECE_TYPE InterfaceConsole::eGetNewPieceType(const Piece::PIECE_COLOR)
{
	try
	{
		cout << "Please choose a new piece type" << endl;

		char cChoice = ' ';
		string strChoices = "RKBQrkbq";

		while(strChoices.find(cChoice) == -1)
		{
			cout << "Enter :" << endl;
			cout << "\t'R' for Rook" << endl;
			cout << "\t'K' for Knight" << endl;
			cout << "\t'B' for Bishop" << endl;
			cout << "\t'Q' for Queen" << endl;
			cin >> cChoice;
		}

		switch(cChoice)
		{
		  case 'R':
		  case 'r':
			return Piece::PT_ROOK;
			break;
		  case 'K':
		  case 'k':
			return Piece::PT_KNIGHT;
			break;
		  case 'B':
		  case 'b':
			return Piece::PT_BISHOP;
			break;
		  case 'Q':
		  case 'q':
			return Piece::PT_QUEEN;
			break;
		  default:
			throw exception("Unknow choice of piece type");
			break;
		}
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Piece::PIECE_COLOR InterfaceConsole::eGetPlayerColorChoice()
{
	cout << "Which color would you like to play ? " << endl;

	char cChoice = ' ';

	while(cChoice != 'b'
	   && cChoice != 'w')
	{
		cout << "Enter 'b' for black, or 'w' for white" << endl;
		cin >> cChoice;
	}

	return (cChoice == 'w' ? Piece::PC_WHITE : Piece::PC_BLACK);
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

void InterfaceConsole::DisplayEditionSelection()
{
	try
	{
		if(mpoModule->eGetType() != Module::MT_EDITION)
			throw exception("Cannot display piece types in any other mode than edition");

		Piece::PIECE_TYPE ePieceType;

		ostringstream strPieces("");
		ostringstream strSelection("");

		for(unsigned int i = 0; i < 6; ++i)
		{
			switch(i)
			{
			  case 0 :
				strPieces << "R ";
				ePieceType = Piece::PT_ROOK;
				break;
			  case 1 :
				strPieces << "N ";
				ePieceType = Piece::PT_KNIGHT;
				break;
			  case 2 :
				strPieces << "B ";
				ePieceType = Piece::PT_BISHOP;
				break;
			  case 3 :
				strPieces << "Q ";
				ePieceType = Piece::PT_QUEEN;
				break;
			  case 4 :
				strPieces << "K ";
				ePieceType = Piece::PT_KING;
				break;
			  case 5 :
				strPieces << "P ";
				ePieceType = Piece::PT_PAWN;
				break;
			}

			if(ePieceType == mpoModule->eGetSelectedPieceType())
				strSelection << (mpoModule->eGetSelectedPieceColor() == Piece::PC_WHITE ? "W" : "B") << " ";
			else
				strSelection << "  ";
		}

		cout << strPieces.str() << endl;
		cout << strSelection.str() << endl;
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void InterfaceConsole::DisplayHelp()
{
	if(mpoModule->eGetType() == Module::MT_EDITION)
	{
		cout << "Edition commands :" << endl;
		cout << "\tTo choose a piece, enter \"PCT\", where 'P' is 'P', 'C' is a color between 'B' and 'W', and 'T' is a type between :" << endl;
		cout << "\t\t'R' for rook" << endl;
		cout << "\t\t'N' for knight" << endl;
		cout << "\t\t'B' for bishop" << endl;
		cout << "\t\t'Q' for queen" << endl;
		cout << "\t\t'K' for king" << endl;
		cout << "\t\t'P' for pawn" << endl;
		cout << "\tTo choose a position to place the selected piece, enter the position's coordinates directly" << endl;
	}
	else
	{
		cout << "Game commands :" << endl;
		cout << "\th : Display this help" << endl;
		cout << "\tc : Cancel last move or selection" << endl;
		cout << "\tr : Restart the current game session" << endl;
		cout << "\tx : Quit the current game session" << endl;
		cout << "\tq : Quit the game" << endl;
	}
}

void InterfaceConsole::SetBusy()
{
	DisplayModule(mpoModule);

	cout << "Computer thinking. Wait for your turn." << endl;
	cout << "|                    |" << endl;
	cout << " " << flush;

	muLastPercent = 0;
}

void InterfaceConsole::SetProgress(unsigned int uPercent)
{
	try
	{
		if(uPercent < 0 || uPercent > 100)
			throw exception("Error : Percentage must be between 0 and 100");

		if(uPercent / 5 > muLastPercent)
		{
			cout << "*" << flush;
			muLastPercent++;
		}
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

Entry InterfaceConsole::eGetSelectionPieceEntry(string strEntry)
{
	try
	{
		if(strEntry.length() < 0)
			throw exception("Malformated entry");

		if(strEntry.length() == 1)
			if(strEntry[0] != 'P'
			&& strEntry[0] != 'p')
				throw exception("Malformated entry");
			else
				return Entry(Piece::PT_NONE, Piece::PC_WHITE);

		if(strEntry.length() == 2)
			strEntry = string("P") + strEntry;

		if(strEntry[0] != 'P'
		&& strEntry[1] != 'p')
			throw exception("Malformated entry");

		Piece::PIECE_COLOR eColor;
		Piece::PIECE_TYPE eType;

		switch(strEntry[1])
		{
		  case 'B' :
		  case 'b' :
			eColor = Piece::PC_BLACK;
			break;
		  case 'W' :
		  case 'w' :
			eColor = Piece::PC_WHITE;
			break;
		  default :
			throw exception("Unknow specified color");
			break;
		}

		switch(strEntry[2])
		{
		  case 'R' :
		  case 'r' :
			eType = Piece::PT_ROOK;
			break;
		  case 'N' :
		  case 'n' :
			eType = Piece::PT_KNIGHT;
			break;
		  case 'B' :
		  case 'b' :
			eType = Piece::PT_BISHOP;
			break;
		  case 'Q' :
		  case 'q' :
			eType = Piece::PT_QUEEN;
			break;
		  case 'K' :
		  case 'k' :
			eType = Piece::PT_KING;
			break;
		  case 'P' :
		  case 'p' :
			eType = Piece::PT_PAWN;
			break;
		}

		return Entry(eType, eColor);
	}		
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}