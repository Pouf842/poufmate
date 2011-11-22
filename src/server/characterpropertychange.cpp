#include "characterpropertychange.h"
#include "player.h"

CharacterPropertyChange::CharacterPropertyChange(QObject* parent, Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
        m_type(type)
{
    switch(type) {
    case RoseDoolan:
        setCharacterType(CHARACTER_ROSE_DOOLAN);
        break;
    case PaulRegret:
        setCharacterType(CHARACTER_PAUL_REGRET);
        break;
    case WillyTheKid:
        setCharacterType(CHARACTER_WILLY_THE_KID);
        break;
    case SlabTheKiller:
        setCharacterType(CHARACTER_SLAB_THE_KILLER);
        break;
    }
}

int CharacterPropertyChange::maxLifePoints() const
{
    if (m_type == PaulRegret)
        return 3;
    else
        return 4;
}

void CharacterPropertyChange::setPlayer(Player* player)
{
    CharacterBase::setPlayer(player);
    setAbility();
}

void CharacterPropertyChange::setAbility()
{
    switch(m_type) {
    case RoseDoolan:
        mp_player->modifyDistanceOut(1);
        break;
    case PaulRegret:
        mp_player->modifyDistanceIn(1);
        break;
    case WillyTheKid:
        mp_player->modifyUnlimitedBangs(true);
        break;
    case SlabTheKiller:
        mp_player->setBangPower(2);
        break;
    }
}

void CharacterPropertyChange::unsetAbility()
{
    switch(m_type) {
    case RoseDoolan:
        mp_player->modifyDistanceOut(-1);
        break;
    case PaulRegret:
        mp_player->modifyDistanceIn(-1);
        break;
    case WillyTheKid:
        mp_player->modifyUnlimitedBangs(false);
        break;
    case SlabTheKiller:
        mp_player->setBangPower(1);
        break;
    }
}