#ifndef __LAN_GAME_H_
#define __LAN_GAME_H_

#include "game.h"
#include "interface.h"
#include <winsock2.h>

class LanGame : public Game
{
  protected :
	SOCKET moSocket;			/// Socket of communication between the two players
	Piece::Color mePlayerColor;	/// Color of the player

	/**
	 * Initialize the socket library and moSocket
	 */
	void InitSocket();

	/**
	 * Create a server socket in moSocket, bind it
	 * wait for a client connection and accept it
	 */
	void ServerSocket();

	/**
	 * Create a client socket in moSocket,
	 * and connect it to a specified (by the user) server
	 */
	void ClientSocket();

	/**
	 * Send a message to the opponent via the socket
	 */
	void SendToOpponent(std::string strMessage);

	/**
	 * Wait a message from the opponent
	 */
	std::string ReceiveFromOpponent();

	/**
	 * Wait for the opponent move and play it on the board
	 */
	void PlayOpponentMove();
  public :

    /**
	 * Basic constructor
	 */
	LanGame(Interface * poInterface = NULL);

	/**
	 * Constructor with a specified board
	 */
	LanGame(const Board &, Interface * poInterface = NULL);

	/**
	 * Destructor
	 */
	virtual ~LanGame();

	/**
	 * Implement of Module::Run()
	 * Run the lan party
	 */
	virtual std::string Run();
};

#endif