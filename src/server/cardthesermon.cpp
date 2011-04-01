#include "cardthesermon.h"
#include "game.h"
#include "gamecycle.h"
#include "playingcard.h"
#include "reactionhandler.h"

CardTheSermon::CardTheSermon(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THE_SERMON)
{
}

CardTheSermon::~CardTheSermon()
{
}

void CardTheSermon::play()
{
    mp_game->gameCycle().registerActionChecker(this);
    connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));
}

void CardTheSermon::stop()
{
    mp_game->gameCycle().unregisterActionChecker(this);
    disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
               this, SLOT(stop()));
}

bool CardTheSermon::checkCard(PlayingCard * card, Player * player)
{
    if(card->type() == CARD_BANG)
        if(mp_game->gameCycle().isResponse() && mp_game->gameCycle().reactionHandler()->reactionType() == REACTION_GENERALSTORE)
            return true;
        else
            return false;

    return true;
}