#include "cardthedoctor.h"
#include "player.h"
#include "game.h"

CardTheDoctor::CardTheDoctor(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_THE_DOCTOR)
{
}

CardTheDoctor::~CardTheDoctor()
{
}

void CardTheDoctor::play()
{
    int iMinLifePoints = 5;
    QList<Player*> playersToHeal;

    foreach(Player* player, mp_game->playerList())
    {
        if(player->isAlive())
        {
            if(player->lifePoints() == iMinLifePoints)
                playersToHeal.append(player);
            else if(player->lifePoints() < iMinLifePoints)
            {
                playersToHeal.clear();
                playersToHeal.append(player);
                iMinLifePoints = player->lifePoints();
            }
        }
    }

    foreach(Player * player, playersToHeal)
        player->modifyLifePoints(1, NULL);
}