#ifndef CHARACTERPROPERTYCHANGE_H
#define CHARACTERPROPERTYCHANGE_H

#include "characterbase.h"

class CharacterPropertyChange : public CharacterBase
{
Q_OBJECT
public:
    enum Type {
        RoseDoolan,
        PaulRegret,
        WillyTheKid,
        SlabTheKiller
    };

    CharacterPropertyChange(QObject* parent, Type);
    virtual int maxLifePoints() const;
    virtual void setPlayer(Player* player);
    virtual void enableAbility(bool bEnable);
    virtual void setAbility();
    virtual void unsetAbility();

private:
    Type m_type;
};

#endif // CHARACTERPROPERTYCHANGE_H
