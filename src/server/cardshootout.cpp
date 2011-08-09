#include "cardshootout.h"
#include "game.h"
#include "gamecycle.h"
#include "player.h"

CardShootOut::CardShootOut(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_SHOOTOUT)
{
}

CardShootOut::~CardShootOut()
{
}

void CardShootOut::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();

	foreach(Player * player, players)
		if(player->hasUnlimitedBangs())
			player->setNbBangsToPlay(2);
}

void CardShootOut::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();

	foreach(Player * player, players)
		if(player->hasUnlimitedBangs())
			player->setNbBangsToPlay(1);
}