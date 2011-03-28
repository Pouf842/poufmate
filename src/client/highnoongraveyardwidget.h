#ifndef HIGHNOONGRAVEYARDWIDGET_H
#define HIGHNOONGRAVEYARDWIDGET_H

#include "cardpilewidget.h"

namespace client {
class CardWidgetFactory;

class HighNoonGraveyardWidget : public CardPileWidget
{
Q_OBJECT
public:
    HighNoonGraveyardWidget(QWidget *parent = 0);
    ~HighNoonGraveyardWidget();

    void init(CardWidgetFactory*);
	virtual void push(HighNoonCardType);
private:
    CardWidgetFactory* mp_cardWidgetFactory;
};
}


#endif // highnoongraveyardwidget_H
