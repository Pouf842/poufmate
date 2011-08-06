#include "cardthedaltons.h"
#include "game.h"
#include "gamecycle.h"
#include "gametable.h"
#include "player.h"
#include "playingcard.h"
#include "gameexceptions.h"

CardTheDaltons::CardTheDaltons(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THE_DALTONS), mp_currentPlayer(0)
{
}

CardTheDaltons::~CardTheDaltons()
{
}

void CardTheDaltons::play()
{
	mp_currentPlayer = 0;
    nextPlayer();
}

void CardTheDaltons::nextPlayer()
{
    if(mp_currentPlayer == 0)
        mp_currentPlayer = mp_game->gameCycle().currentPlayer();    // Highnoon are played on the sheriff turn
    else
    {
        mp_currentPlayer = mp_game->nextPlayer(mp_currentPlayer);

        if(mp_currentPlayer->role() == ROLE_SHERIFF)
			return;
    }

    if(mp_currentPlayer->table().count() == 0)
        nextPlayer();
    else if(mp_currentPlayer->table().count() == 1)
    {
        mp_game->gameTable().cancelCard(mp_currentPlayer->table().first(), mp_currentPlayer);
        nextPlayer();
    }
    else
        mp_game->gameCycle().setResponseMode(this, mp_currentPlayer);
}

void CardTheDaltons::respondCard(PlayingCard* targetCard)
{
    targetCard->assertOnTable();

    if(targetCard->owner() == mp_currentPlayer)
    {
        mp_game->gameTable().cancelCard(targetCard, mp_currentPlayer);
        mp_game->gameCycle().unsetResponseMode();
    }
    else
        throw BadCardException();

    nextPlayer();
}

ReactionType CardTheDaltons::reactionType() const
{
    return REACTION_DALTONS;// REQUEST_SELECT_ON_TABLE;
}

Player* CardTheDaltons::causedBy() const
{
    return 0;
}