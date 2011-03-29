#include "cardthedaltons.h"
#include "game.h"
#include "player.h"

CardTheDaltons::CardTheDaltons(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THE_DALTONS)
{
}

CardTheDaltons::~CardTheDaltons()
{
}

void CardTheDaltons::play()
{
    QList<Player*> playersToDiscard;

    //foreach(Player * player, mp_game->playerList())
    Player * player;
    {
        if(player->isAlive())
        {
            if(!player->table().isEmpty())
            {
                /*PlayingCard * targetCard;
                mp_game->gameTable()->cancelCard(targetCard, player);*/
            }
        }
    }
}