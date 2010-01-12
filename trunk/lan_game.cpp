#include "lan_game.h"
#include "menu.h"
#include "include_movements.h"

using namespace std;

LanGame::LanGame() : Game()
{
	InitSocket();
}

LanGame::LanGame(const Board & oBoard) : Game(oBoard)
{
	InitSocket();	
}

void LanGame::InitSocket()
{
	WSADATA WSAData;

    if(WSAStartup(MAKEWORD(1,0), &WSAData) != 0)
		throw exception("WSA (socket library) initialisation failed");

	moSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(moSocket == -1)
		throw exception("Error : cannot create socket");
}

LanGame::~LanGame()
{
	/*if(moSocket)
		close(moSocket);*/

	WSACleanup();
}

void LanGame::ServerSocket(Interface * poInterface)
{
	string strPort = poInterface->strKeyboardEntry("Please enter the port", "85623");
	int iPort;

	if((iPort = atoi(strPort.c_str())) == 0
	|| iPort > 65535
	|| iPort < 0)
		throw exception("The port must be a positive numeric value inferior to 65535");

	SOCKET oBindSocket;
	oBindSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(oBindSocket == -1)
		throw exception("Error : cannot create socket");

	SOCKADDR_IN oSockAddr;
	oSockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	oSockAddr.sin_family		= AF_INET;
	oSockAddr.sin_port			= htons(iPort);

	int iError;

	if((iError = bind(oBindSocket, (SOCKADDR *) &oSockAddr, sizeof(oSockAddr))) == -1)
		throw exception("Unable to bind the socket");

	poInterface->DisplayMessage("En attente d'une connexion");
	listen(oBindSocket, 0);

	SOCKADDR_IN oSockClient;

	int oClientSize = sizeof(oSockClient);

	if((moSocket = accept(oBindSocket, (SOCKADDR *) &oSockClient, &oClientSize)) == INVALID_SOCKET)
		throw exception("Error : invalid socket in acceptance of client connection");

	mePlayerColor = Piece::WHITE;

	if(poInterface->cGetPlayerColorChoice() != 'W')
		mePlayerColor = Piece::BLACK;

	SendToOpponent(string("Color : ") + (mePlayerColor == Piece::WHITE ? 'B' : 'W'));
}

void LanGame::SendToOpponent(string strMessage)
{
	send(moSocket, strMessage.c_str(), strMessage.size() + 1, 0);
}

string LanGame::ReceiveFromOpponent()
{
	char ctOpponentEntry[255];
/*	string strOpponentEntry = "";

	do
	{*/
		recv(moSocket, ctOpponentEntry, sizeof(ctOpponentEntry), 0);
/*		strOpponentEntry += ctOpponentEntry;
	}
	while(strOpponentEntry[strOpponentEntry.size() - 1] != '\n');*/

	return ctOpponentEntry;
}

void LanGame::ClientSocket(Interface * poInterface)
{
	string strServerIP		= poInterface->strKeyboardEntry("Enter the server's adress");
	string strServerPort	= poInterface->strKeyboardEntry("Enter the server's port", "85623");

	SOCKADDR_IN oServerAdress;
	oServerAdress.sin_addr.s_addr	= inet_addr(strServerIP.c_str());
	oServerAdress.sin_family		= AF_INET;
	oServerAdress.sin_port		= htons(atoi(strServerPort.c_str()));

	connect(moSocket, (SOCKADDR *) &oServerAdress, sizeof(oServerAdress));

	string strColor = ReceiveFromOpponent();

	if(strColor.size() < 9 && strColor.substr(0, 8) != "Color : ")
		throw exception(("Error : waiting for color, getting \"" + strColor).c_str());

	mePlayerColor = (strColor[8] == 'W' ? Piece::WHITE : Piece::BLACK);
}

void LanGame::Run(Interface * poInterface)
{
	if(!poInterface)
		throw exception("The interface is not defined");

	Menu oLanMenu;

	oLanMenu.AddOption("1.Host a game");
	oLanMenu.AddOption("2.Join a game");

	unsigned int iChoice = poInterface->iGetMenuEntry(oLanMenu);

	switch(iChoice)
	{
	  case 1 :
		ServerSocket(poInterface);
		break;
	  case 2 :
		ClientSocket(poInterface);
		break;
	  default :
		return;
	    break;
	}

	string strEntry = "";

	poInterface->DisplayBoard(moBoard);
	poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	poInterface->CommitDisplay();

	Movement * poNextMove = NULL;

	while(!bIsOver())
	{
		try
		{
			if(meCurrentPlayer == mePlayerColor)
			{
				strEntry = poInterface->strGetEntry();	// Getting the next command
			
				if(strEntry == "");			// Do nothing
				else if(strEntry == "x")
					mbIsOver = true;		// Stop the game
				/* Cancel last move */
				else if(strEntry == "c")
				{
					CancelLastMove();
					CancelLastMove();
					moSelection.Empty();
				}
				/* Select a piece or make a move */
				else if(strEntry[strEntry.size() - 1] != '?')
				{
					Position oEntry(strEntry);

					/* Select a piece */
					if(moSelection.bIsEmpty())
					{
						CheckSelectionCoords(oEntry);
						moSelection = oEntry;
					}
					/* Try to make a move */
					else
					{
						if(moSelection != oEntry)	// Same square --> no move
						{
							/* Determinate the movement's type and update poNextMove */
							if(bIsCastling(moSelection, oEntry))	// Castling
							{
								if(bIsInCheck(meCurrentPlayer))
									throw exception("Castling is not allowed if you're in check");

								if(!bIsCastlingPathOk(moSelection, oEntry))
									throw exception("Your king would be in check during castling");

								poNextMove = new CastlingMove(moSelection, oEntry);
							}
							else if(bIsPromotion(moSelection, oEntry))	// Promotion
							{
								char cNewPieceType = poInterface->cGetNewPieceType(meCurrentPlayer);
								poNextMove = new Promotion(moSelection, oEntry, cNewPieceType);
							}
							else if(moBoard.poGetPiece(moSelection)->bIsFirstMove())	// First move
								poNextMove = new FirstMove(moSelection, oEntry);
							else if(bIsEnPassantOk(moSelection, oEntry))
								poNextMove = new EnPassant(moSelection, oEntry, (*moHistory.rbegin()));
							else
								poNextMove = new Movement(moSelection, oEntry);	// Other move

							/* Execute the move */
							ExecuteMovement(poNextMove);
							SendToOpponent(moSelection.ToString() + oEntry.ToString());

							/* If the move puts the player in check, it is not valid */
							if(bIsInCheck(meCurrentPlayer))
							{
								CancelLastMove();
								throw exception("That move puts you in check");
							}

							SwitchPlayer();	// Next player
						}
						
						moSelection.Empty();	// No selection
					}
				}
			}
			else
			{
				PlayOpponentMove(poInterface);
				SwitchPlayer();
			}

			/* Display the game */
			poInterface->DisplayBoard(moBoard);

			/* If the player is checkmate, display a message and stop the game */
			if(strEntry == "x")	// Display a message
				poInterface->DisplayMessage("Game over !");
			else if(bIsCheckMate(meCurrentPlayer))
			{
				mbIsOver = true;
				poInterface->DisplayGameOver(string(meCurrentPlayer == Piece::WHITE ? "White " : "Black ") + " player is check mate !");
			}
			else if(bIsGameInStaleMate())
			{
				mbIsOver = true;
				poInterface->DisplayMessage("This is a stalemate");
			}
			else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
			{
				poInterface->DisplayInCheck(moKings[meCurrentPlayer]);
				poInterface->DisplayMessage(string("The ") + (meCurrentPlayer == Piece::WHITE ? " white" : " black") + " king is in check");
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
			}
			else
				poInterface->DisplayCurrentPlayer(meCurrentPlayer);
	
			/* If asked (strEntry ends with '?'), display the possibilities for a specified piece */
			if(strEntry.size() != 0
			&& strEntry[strEntry.size() - 1] == '?')
				poInterface->DisplayPossibilities(oGetPossibilities(strEntry.substr(0, 2)));

			/* If there is a selected piece, display it */
			if(!moSelection.bIsEmpty())
				poInterface->DisplaySelection(moSelection);
		}
		catch(exception & e)
		{
			poInterface->DisplayMessage(e.what());
		}

		poInterface->CommitDisplay();
	}
}

void LanGame::PlayOpponentMove(Interface * poInterface)
{
	string strOpponentEntry = ReceiveFromOpponent();

	moSelection = strOpponentEntry.substr(0, 2);
	Position oEntry = strOpponentEntry.substr(2);

	Movement * poNextMove = NULL;
	/* Determinate the movement's type and update poNextMove */
	if(bIsCastling(moSelection, oEntry))	// Castling
	{
		if(bIsInCheck(meCurrentPlayer))
			throw exception("Castling is not allowed if you're in check");

		if(!bIsCastlingPathOk(moSelection, oEntry))
			throw exception("Your king would be in check during castling");

		poNextMove = new CastlingMove(moSelection, oEntry);
	}
	else if(bIsPromotion(moSelection, oEntry))	// Promotion
	{
		char cNewPieceType = poInterface->cGetNewPieceType(meCurrentPlayer);
		poNextMove = new Promotion(moSelection, oEntry, cNewPieceType);
	}
	else if(moBoard.poGetPiece(moSelection)->bIsFirstMove())	// First move
		poNextMove = new FirstMove(moSelection, oEntry);
	else if(bIsEnPassantOk(moSelection, oEntry))
		poNextMove = new EnPassant(moSelection, oEntry, (*moHistory.rbegin()));
	else
		poNextMove = new Movement(moSelection, oEntry);	// Other move

	/* Execute the move */
	ExecuteMovement(poNextMove);
}