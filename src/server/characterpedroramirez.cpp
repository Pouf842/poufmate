#include "characterpedroramirez.h"
#include "game.h"
#include "gamecycle.h"
#include "playingcard.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "player.h"

CharacterPedroRamirez::CharacterPedroRamirez(QObject *parent):
        CharacterBase(parent, CHARACTER_PEDRO_RAMIREZ)
{
}

void CharacterPedroRamirez::useAbility()
{
    gameCycle().draw(mp_player, m_bAbilityEnabled);
}

void CharacterPedroRamirez::draw(bool specialDraw)
{
    if (specialDraw) {
        if(!m_bAbilityEnabled)
            throw BadUsageException();

        if (gameTable().isEmptyGraveyard())
            throw BadGameStateException(); // @todo: maybe throw different exception
        notifyAbilityUse();
        gameTable().playerDrawFromGraveyard(mp_player);
        gameTable().playerDrawFromDeck(mp_player, mp_player->game()->iGetNbCardsToDraw() - 1, 0);
    } else {
        CharacterBase::draw(false);
    }
}
