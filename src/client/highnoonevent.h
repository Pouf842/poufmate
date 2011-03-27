#ifndef HIGHNOONEVENT_H
#define HIGHNOONEVENT_H

#include "parser/parserstructs.h"
#include "gameevent.h"

namespace client
{
class Game;

class HighNoonEvent : public GameEvent
{
Q_OBJECT;
public:
    HighNoonEvent(Game* game, HighNoonCardType type);
    virtual ~HighNoonEvent();
    virtual void run();
protected :
    HighNoonCardType m_type;
};
}
#endif
