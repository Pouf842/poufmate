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


}

void CardGoldRush::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			   this, SLOT(stop()));
}