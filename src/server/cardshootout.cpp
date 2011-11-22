#include "cardshootout.h"
#include "game.h"
#include "gamecycle.h"
#include "player.h"

CardShootOut::CardShootOut(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_SHOOTOUT)
{
    m_iInitialNbBang = mp_game->getNbBangsToPlayInTurn();
}

CardShootOut::~CardShootOut()
{
}

void CardShootOut::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();
    mp_game->setNbBangsToPlayInTurn(m_iInitialNbBang + 1);
}

void CardShootOut::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();
    mp_game->setNbBangsToPlayInTurn(m_iInitialNbBang);
}