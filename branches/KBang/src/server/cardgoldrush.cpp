#include "cardgoldrush.h"
#include "gamecycle.h"
#include "game.h"

CardGoldRush::CardGoldRush(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_GOLD_RUSH)
{
}

CardGoldRush::~CardGoldRush()
{
}

void CardGoldRush::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();
	QList<Player*> reorderedPlayers;

	reorderedPlayers.append(*players.begin());
	
	QList<Player*>::Iterator reverseIterator = players.end();

	while(--reverseIterator != players.begin())
		reorderedPlayers.append(*reverseIterator);

	mp_game->setPlayerList(reorderedPlayers);
}

void CardGoldRush::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			   this, SLOT(stop()));

	QList<Player*> players = mp_game->playerList();
	QList<Player*> reorderedPlayers;

	reorderedPlayers.append(*players.begin());
	
	QList<Player*>::Iterator reverseIterator = players.end();

	while(--reverseIterator != players.begin())
		reorderedPlayers.append(*reverseIterator);

	mp_game->setPlayerList(reorderedPlayers);
}