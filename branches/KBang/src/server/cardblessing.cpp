#include "cardblessing.h"
#include "game.h"
#include "gamecycle.h"
#include "gametable.h"
#include "playingcard.h"

CardBlessing::CardBlessing(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_BLESSING)
{
}

CardBlessing::~CardBlessing()
{
}

void CardBlessing::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<PlayingCard*> cards = mp_game->gameTable().getAllPlayingCards();

	for each(PlayingCard* card in cards)
	{
		m_cards[card] = card->suit();
		card->setSuit(SUIT_HEARTS);
	}
}

void CardBlessing::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	for each(PlayingCard* card in m_cards.keys())
		card->setSuit(m_cards[card]);
}