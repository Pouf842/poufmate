#include "lan_game.h"
#include "include_movements.h"
#include <string>
#include <vector>

using namespace std;

LanGame::LanGame(Interface * poInterface) : Game(poInterface)
{
	InitSocket();
}

LanGame::LanGame(const Board & oBoard, Interface * poInterface) : Game(oBoard, poInterface)
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
	if(moSocket)
		closesocket(moSocket);

	WSACleanup();
}

void LanGame::ServerSocket()
{
	/* Get the port from the user */
	string strPort = mpoInterface->strGetPortEntry();
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

	/* Bind the socket to any address */
	if(bind(oBindSocket, (SOCKADDR *) &oSockAddr, sizeof(oSockAddr)) == -1)
		throw exception("Unable to bind the socket");

	/* Wait for the client */
	mpoInterface->AddMessage("En attente d'une connexion");
	listen(oBindSocket, 0);

	SOCKADDR_IN oSockClient;

	int oClientSize = sizeof(oSockClient);

	/* Accept the client */
	if((moSocket = accept(oBindSocket, (SOCKADDR *) &oSockClient, &oClientSize)) == INVALID_SOCKET)
		throw exception("Error : invalid socket in acceptance of client connection");

	mePlayerColor = Piece::WHITE;

	/* Choice of the color */
	if(mpoInterface->cGetPlayerColorChoice() != 'W')
		mePlayerColor = Piece::BLACK;

	/* Sending his color to the opponent */
	SendToOpponent(string("Color : ") + (mePlayerColor == Piece::WHITE ? 'B' : 'W'));
}

void LanGame::SendToOpponent(string strMessage)
{
	send(moSocket, strMessage.c_str(), strMessage.size() + 1, 0);
}

string LanGame::ReceiveFromOpponent()
{
	char ctOpponentEntry[255];
	memset(ctOpponentEntry, 0, 255);

	int iReturn = recv(moSocket, ctOpponentEntry, sizeof(ctOpponentEntry), 0);

	/* Connection closed */
	if(iReturn == 0 || iReturn == -1)
	{
		mbIsOver = true;
		throw exception("Connection closed");
	}

	return ctOpponentEntry;
}

void LanGame::ClientSocket()
{
	/* Ask server IP and port to the user */
	string strServerIP		= mpoInterface->strGetIPEntry();
	string strServerPort	= mpoInterface->strGetPortEntry();

	SOCKADDR_IN oServerAdress;
	oServerAdress.sin_addr.s_addr	= inet_addr(strServerIP.c_str());
	oServerAdress.sin_family		= AF_INET;
	oServerAdress.sin_port		= htons(atoi(strServerPort.c_str()));

	/* Connection to the server */
	if(connect(moSocket, (SOCKADDR *) &oServerAdress, sizeof(oServerAdress)) == SOCKET_ERROR)
	{
		mbIsOver = true;
		throw exception("Connection failed");
	}

	mpoInterface->AddMessage("Connection successful. Waiting for the server to choose his color.");
	string strColor = ReceiveFromOpponent();	// Wait for the player color (server player choose his own, and send his to the client)

	if(strColor.size() < 9 && strColor.substr(0, 8) != "Color : ")
	{
		mbIsOver = true;
		throw exception(("Error : waiting for color, getting \"" + strColor + "\"").c_str());
	}

	mePlayerColor = (strColor[8] == 'W' ? Piece::WHITE : Piece::BLACK);
}

void LanGame::Run()
{
	if(!mpoInterface)
		throw exception("The interface is not defined");

	vector<string> oLanMenu;

	oLanMenu.push_back("1.Host a game");
	oLanMenu.push_back("2.Join a game");

	unsigned int iChoice = mpoInterface->iGetMenuEntry(oLanMenu);

	switch(iChoice)
	{
	  case 1 :
		ServerSocket();
		break;
	  case 2 :
		ClientSocket();
		break;
	  default :
		return;
	    break;
	}

	Movement * poNextMove = NULL;

	while(!bIsOver())
	{
		try
		{
			if(meCurrentPlayer == mePlayerColor)
			{
				mpoInterface->AddMessage("It's your turn.");
				GameEntry oEntry = mpoInterface->oGetGameEntry(*this);

				if(oEntry.bIsCommand())
				{
					string strEntry = oEntry.strGetCommand();

					if(strEntry == "");			// Do nothing
					else if(strEntry == "x")
						mbIsOver = true;		// Stop the game
					/* Cancel last move */
					else if(strEntry == "c")
					{
						SendToOpponent("c");
						bool bOk = (ReceiveFromOpponent() == "Y\n");

						if(bOk)
						{
							CancelLastMove();
							CancelLastMove();
						}
						else
							mpoInterface->AddMessage("The opponent refuse the annulment");
					}
				}
				else
				{
					Position oPos1(oEntry.oGetPos1());
					Position oPos2(oEntry.oGetPos2());

					/* Determinate the movement's type and update poNextMove */
					if(bIsCastling(oPos1, oPos2))	// Castling
					{
						if(bIsInCheck(meCurrentPlayer))
							throw exception("Castling is not allowed if you're in check");

						if(!bIsCastlingPathOk(oPos1, oPos2))
							throw exception("Your king would be in check during castling");

						poNextMove = new CastlingMove(oPos1, oPos2);
					}
					else if(bIsPromotion(oPos1, oPos2))	// Promotion
					{
						char cNewPieceType = mpoInterface->cGetNewPieceType(meCurrentPlayer);
						poNextMove = new Promotion(oPos1, oPos2, cNewPieceType);
					}
					else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())	// First move
						poNextMove = new FirstMove(oPos1, oPos2);
					else if(bIsEnPassantOk(oPos1, oPos2))
						poNextMove = new EnPassant(oPos1, oPos2, (*moHistory.rbegin()));
					else
						poNextMove = new Movement(oPos1, oPos2);	// Other move

					/* Execute the move */
					ExecuteMovement(poNextMove);
					SendToOpponent(oPos1.ToString() + oPos2.ToString());

					/* If the move puts the player in check, it is not valid */
					if(bIsInCheck(meCurrentPlayer))
					{
						CancelLastMove();
						throw exception("That move puts you in check");
					}

					SwitchPlayer();	// Next player
				}
			}
			else
			{
				mpoInterface->DisplayGame(*this);
				mpoInterface->AddMessage("Waiting for your opponent to play");
				PlayOpponentMove();
				SwitchPlayer();
			}

			/* If the player is checkmate, display a message and stop the game */
			if(bIsCheckMate(meCurrentPlayer))
				(meCurrentPlayer == Piece::WHITE ? mbIsWhiteCheckMate : mbIsBlackCheckMate) = true;
			else if(bIsGameInStaleMate())
				mbIsStaleMate = true;
			else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
				(meCurrentPlayer == Piece::WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = true;
		}
		catch(exception & e)
		{
			mpoInterface->AddMessage(e.what());
			mpoInterface->GetEmptyEntry();
		}
	}
}

void LanGame::PlayOpponentMove()
{
	string strOpponentEntry = ReceiveFromOpponent();

	Position oSelection = strOpponentEntry.substr(0, 2);
	Position oEndingPos = strOpponentEntry.substr(2);

	Movement * poNextMove = NULL;
	/* Determinate the movement's type and update poNextMove */
	if(bIsCastling(oSelection, oEndingPos))	// Castling
	{
		if(bIsInCheck(meCurrentPlayer))
			throw exception("Castling is not allowed if you're in check");

		if(!bIsCastlingPathOk(oSelection, oEndingPos))
			throw exception("Your king would be in check during castling");

		poNextMove = new CastlingMove(oSelection, oEndingPos);
	}
	else if(bIsPromotion(oSelection, oEndingPos))	// Promotion
	{
		char cNewPieceType = mpoInterface->cGetNewPieceType(meCurrentPlayer);
		poNextMove = new Promotion(oSelection, oEndingPos, cNewPieceType);
	}
	else if(moBoard.poGetPiece(oSelection)->bIsFirstMove())	// First move
		poNextMove = new FirstMove(oSelection, oEndingPos);
	else if(bIsEnPassantOk(oSelection, oEndingPos))
		poNextMove = new EnPassant(oSelection, oEndingPos, (*moHistory.rbegin()));
	else
		poNextMove = new Movement(oSelection, oEndingPos);	// Other move

	/* Execute the move */
	ExecuteMovement(poNextMove);
}