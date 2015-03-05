#include "characterjessejones.h"
#include "game.h"
#include "gametable.h"
#include "gamecycle.h"
#include "player.h"
#include "gameexceptions.h"

CharacterJesseJones::CharacterJesseJones(QObject *parent):
        CharacterBase(parent, CHARACTER_JESSE_JONES)
{
}

void CharacterJesseJones::useAbility(Player* targetPlayer)
{
	if(!m_bAbilityEnabled)
		throw BadUsageException();

	mp_targetPlayer = targetPlayer;
	gameCycle().draw(mp_player, true);
}

void CharacterJesseJones::draw(bool specialDraw)
{
    if (specialDraw) {
		if(!m_bAbilityEnabled)
			throw BadCardException();

        PlayingCard* targetCard = mp_targetPlayer->getRandomCardFromHand();
        if (targetCard == 0)
            throw BadTargetPlayerException();
        notifyAbilityUse();
        gameTable().playerStealCard(mp_player, targetCard);
        gameTable().playerDrawFromDeck(mp_player, mp_player->game()->iGetNbCardsToDraw() - 1, 0);
    } else {
        CharacterBase::draw(false);
    }
}