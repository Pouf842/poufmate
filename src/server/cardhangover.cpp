#include "cardhangover.h"
#include "player.h"
#include "game.h"
#include "gamecycle.h"
#include "characterbase.h"

CardHangOver::CardHangOver(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_HANGOVER)
{
}

CardHangOver::~CardHangOver()
{
}

void CardHangOver::play()
{
    mp_game->gameCycle().registerActionChecker(this);
    connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));
    
    QList<Player *> players = mp_game->playerList();

    for each(Player * player in players)
        player->character()->enableAbility(false);
}

void CardHangOver::stop()
{
    mp_game->gameCycle().unregisterActionChecker(this);
    disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));

    QList<Player *> players = mp_game->playerList();

    for each(Player * player in players)
        player->character()->enableAbility(true);
}

bool CardHangOver::checkAbility(Player *)
{
    return false;
}