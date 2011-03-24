#include <QTimer>

#include "highnoonevent.h"
#include "game.h"
#include "cardwidget.h"

using namespace client;

HighNoonEvent::HighNoonEvent(Game* game, HighNoonCardType type):
        GameEvent(game),
        m_type(type)
{
}

HighNoonEvent::~HighNoonEvent()
{
}

void HighNoonEvent::run()
{
    GameEvent::run();
/*    PlayerWidget* player = mp_game->playerWidget(m_playerId);
    player->dieAndRevealRole(m_role);*/
    QTimer::singleShot(1000, this, SLOT(finish()));
}
