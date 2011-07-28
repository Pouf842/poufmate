#include "cardtrainarrival.h"
#include "game.h"
#include "gamecycle.h"
#include "reactionhandler.h"
#include "characterbase.h"

CardTrainArrival::CardTrainArrival(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_TRAIN_ARRIVAL)
{
}

CardTrainArrival::~CardTrainArrival()
{
}

void CardTrainArrival::play()
{
    mp_game->gameCycle().registerActionChecker(this);
    connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
            this, SLOT(stop()));

    CharacterBase::setNbCardsToDraw(3);
}

bool CardTrainArrival::checkAbility(CharacterType type)
{
    return (type != CHARACTER_KIT_CARLSON);
}

void CardTrainArrival::stop()
{
    mp_game->gameCycle().unregisterActionChecker(this);
    disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
               this, SLOT(stop()));

    CharacterBase::setNbCardsToDraw(2);
}