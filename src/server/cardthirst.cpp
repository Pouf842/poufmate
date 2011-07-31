#include "cardthirst.h"
#include "game.h"
#include "gamecycle.h"

CardThirst::CardThirst(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THIRST)
{
}

CardThirst::~CardThirst()
{
}

void CardThirst::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));
	
	mp_game->setNbCardsToDraw(1);
}

void CardThirst::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			   this, SLOT(stop()));

	mp_game->setNbCardsToDraw(2);
}