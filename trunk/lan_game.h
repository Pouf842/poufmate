#ifndef __LAN_GAME_H_
#define __LAN_GAME_H_

#include "game.h"
#include "interface.h"
#include <winsock.h>

class LanGame : public Game
{
  private :
	SOCKET moSocket;
	Piece::Color mePlayerColor;
	void InitSocket();
	void ServerSocket(Interface *);
	void ClientSocket(Interface *);
	void SendToOpponent(std::string strMessage);
	std::string ReceiveFromOpponent();

  public :
	LanGame();
	LanGame(const Board &);
	virtual ~LanGame();
	virtual void Run(Interface * poInterface);
	void PlayOpponentMove(Interface *);
};

#endif