#include <QTimer>

#include "highnoonevent.h"
#include "game.h"
#include "deckwidget.h"
#include "highnoongraveyardwidget.h"
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
	mp_game->highNoonDeck()->pop();
	mp_game->highNoonGraveyard()->push(m_type);

    QTimer::singleShot(1000, this, SLOT(finish()));
}
