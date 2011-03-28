#include "highnoongraveyardwidget.h"
#include "cardwidget.h"
#include "cardwidgetfactory.h"

using namespace client;

HighNoonGraveyardWidget::HighNoonGraveyardWidget(QWidget* parent):
        CardPileWidget(parent)
{
    setPocketType(POCKET_HIGHNOON_GRAVEYARD);
}

HighNoonGraveyardWidget::~HighNoonGraveyardWidget()
{
}

void HighNoonGraveyardWidget::init(CardWidgetFactory* cardWidgetFactory)
{
    mp_cardWidgetFactory = cardWidgetFactory;
}

void HighNoonGraveyardWidget::push(HighNoonCardType type)
{
	CardWidget * card = mp_cardWidgetFactory->createHighNoonCard(this, type);
    CardPocket::push(card);
    card->setParent(this);
    card->setSize(m_cardWidgetSize);
    card->validate();
    card->move(newCardPosition());
    card->raise();
    card->show();
}