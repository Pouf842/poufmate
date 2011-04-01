#ifndef ACTIONCHECKER_H
#define ACTIONCHECKER_H

#include "gameenums.h"

class PlayingCard;
class Player;

class ActionChecker
{
  public :
    ActionChecker();
    virtual ~ActionChecker();

    virtual bool checkCard(PlayingCard * card, Player * player = 0);
    virtual bool checkAbility(CharacterType type);
};

#endif