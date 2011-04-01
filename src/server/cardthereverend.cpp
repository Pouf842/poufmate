#include "cardthereverend.h"
#include "game.h"
#include "gamecycle.h"
#include "playingcard.h"
#include "reactionhandler.h"

CardTheReverend::CardTheReverend(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THE_REVEREND)
{
}

CardTheReverend::~CardTheReverend()
{
}

void CardTheReverend::play()
{
    mp_game->gameCycle().registerActionChecker(this);
    connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));
}

void CardTheReverend::stop()
{
    mp_game->gameCycle().unregisterActionChecker(this);
    disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));
}

bool CardTheReverend::checkCard(PlayingCard * card, Player * player)
{
    if(card->type() == CARD_BEER)
        if(mp_game->gameCycle().isResponse() && mp_game->gameCycle().reactionHandler()->reactionType() == REACTION_GENERALSTORE)
            return true;
        else
            return false;

    return true;
}