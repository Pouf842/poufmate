#include "cardcurse.h"
#include "game.h"
#include "gamecycle.h"
#include "gametable.h"
#include "playingcard.h"

CardCurse::CardCurse(Game * game, int id) : HighNoonCard(game, id, HIGHNOON_CURSE)
{
}

CardCurse::~CardCurse()
{
}

void CardCurse::play()
{
	connect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	QList<PlayingCard*> cards = mp_game->gameTable().getAllPlayingCards();

	for each(PlayingCard* card in cards)
	{
		m_cards[card] = card->suit();
		card->setSuit(SUIT_SPADES);
	}
}

void CardCurse::stop()
{
	disconnect(&mp_game->gameCycle(), SIGNAL(newGameTurn()),
			this, SLOT(stop()));

	for each(PlayingCard* card in m_cards.keys())
		card->setSuit(m_cards[card]);
}