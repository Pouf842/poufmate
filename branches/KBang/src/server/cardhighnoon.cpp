#include "cardhighnoon.h"
#include "player.h"
#include "game.h"
#include "gamecycle.h"

CardHighNoon::CardHighNoon(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_HIGH_NOON)
{
}

CardHighNoon::~CardHighNoon()
{
}

void CardHighNoon::play()
{
    connect(&mp_game->gameCycle(), SIGNAL(newTurn(Player*)),
            this, SLOT(playEffect(Player*)));
    connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));
}

void CardHighNoon::playEffect(Player * player)
{
    player->modifyLifePoints(-1, NULL);
}

void CardHighNoon::stop()
{
    disconnect(&mp_game->gameCycle(), SIGNAL(newTurn(Player*)),
        this, SLOT(playEffect(Player*)));
    disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
        this, SLOT(stop()));
}