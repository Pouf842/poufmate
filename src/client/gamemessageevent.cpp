#include "gamemessageevent.h"
#include "game.h"
#include "card.h"

using namespace client;

GameMessageEvent::GameMessageEvent(Game* game, const GameMessage& gameMessage):
        GameEvent(game), m_gameMessage(gameMessage)
{
}

GameMessageEvent::~GameMessageEvent()
{
}

void GameMessageEvent::run()
{
    GameEvent::run();
    QString msg;
    QString playerName       = m_gameMessage.player ? mp_game->playerWidget(m_gameMessage.player)->name() : "";
    QString targetPlayerName = m_gameMessage.targetPlayer ? mp_game->playerWidget(m_gameMessage.targetPlayer)->name() : "";
    QString causedByName     = m_gameMessage.causedBy ? mp_game->playerWidget(m_gameMessage.causedBy)->name() : "";

    switch(m_gameMessage.type) {
    case GAMEMESSAGE_GAMESTARTED:
        mp_game->setGameState(GAMESTATE_PLAYING);
        msg = tr("The game has just started.");
        break;
    case GAMEMESSAGE_GAMEFINISHED:
        mp_game->setGameState(GAMESTATE_FINISHED);
        msg = tr("The game has finished.");
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMDECK:
        msg = tr("%1 drew %2 from the deck.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardListWidgetToString(m_gameMessage.cards));
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD:
        msg = tr("%1 drew %2 from the discard pile.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERDISCARDCARD:
        msg = tr("%1 discarded %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPLAYCARD:
        if (m_gameMessage.targetCard.id) {
            msg = tr("%1 played %2 on %3%4.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card)).
                        arg(cardToString(m_gameMessage.targetCard)).
                        arg(m_gameMessage.targetPlayer ?
                                tr(" owned by %1").arg(decoratePlayerName(targetPlayerName, 1)) : "");
        } else if (m_gameMessage.targetPlayer && m_gameMessage.targetPlayer != m_gameMessage.player) {
            msg = tr("%1 played %2 on %3.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card)).
                        arg(decoratePlayerName(targetPlayerName, 1));
        } else {
            msg = tr("%1 played %2.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card));
        }
        break;
    case GAMEMESSAGE_PLAYERRESPONDWITHCARD:
        msg = tr("&nbsp;&nbsp;&nbsp;&nbsp;%1 responded with %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPASS:
        msg = tr("&nbsp;&nbsp;&nbsp;&nbsp;%1 did not react.").
                    arg(decoratePlayerName(playerName));
        break;
    case GAMEMESSAGE_PLAYERPICKFROMSELECTION:
        msg = tr("&nbsp;&nbsp;&nbsp;&nbsp;%1 took %2 from selection.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERCHECKDECK:
        msg = tr("%1 \"drew!\" %2 (because of %3) and ").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.targetCard, 1)).
                    arg(cardToString(m_gameMessage.card));
        if (m_gameMessage.checkResult)
            msg += tr("was lucky.");
        else
            msg += tr("failed.");
        break;
    case GAMEMESSAGE_PLAYERSTEALCARD:
        msg = tr("%1 drew %2 from %3.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card)).
                    arg(decoratePlayerName(targetPlayerName, 1));
        break;
    case GAMEMESSAGE_PLAYERCANCELCARD:
        msg = tr("%1 forced %3 to discard %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card)).
                    arg(decoratePlayerName(targetPlayerName, 1));
        break;
    case GAMEMESSAGE_DECKREGENERATE:
        msg = tr("The deck ran out of cards. Cards from the discard pile were shuffled and are now used as new deck.");
        break;
	case GAMEMESSAGE_HIGHNOONDECKREGENERATE:
		msg = tr("The high noon deck ran out of cards. Cards from the high noon discard pile were shuffled and are now used as new deck.");
		break;
    case GAMEMESSAGE_PLAYERDIED:
        msg = tr("%1 passed away. R.I.P.").
                    arg(decoratePlayerName(playerName));
        break;
    case GAMEMESSAGE_HIGHNOON_CARD :
        switch(m_gameMessage.highNoonCardType)
        {
          case HIGHNOON_BLESSING :
            msg = tr("Thee shall be blessed as <i>only hearts</i> thee shall pick.");
            break;
          case HIGHNOON_CURSE :
            msg = tr("Thee shall be cursed, as <i>only spades</i> will fall on you.");
            break;
          case HIGHNOON_GHOST_TOWN :
            msg = tr("The deads rise from their graves.");
            break;
          case HIGHNOON_GOLD_RUSH :
            msg = tr("Gold rush ! <i>The play turn is now counter-clockwise</i>.");
            break;
          case HIGHNOON_HANGOVER :
            msg = tr("\nEvery body has a hangover. <i>All special abilities are disabled</i>.");
            break;
          case HIGHNOON_HIGH_NOON :
            msg = tr("\nHigh noon. The sun makes <i>everybody lose one life point at the beginning of their turn</i>.");
            break;
          case HIGHNOON_SHOOTOUT :
            msg = tr("\nShootout ! It's crazy out there ! Everybody can shoot a <i>additional bang</i> !");
            break;
          case HIGHNOON_THE_DALTONS :
            msg = tr("\nThe Daltons are in towns. They'll <i>rob a blue card</i> on everybody's table.");
            break;
          case HIGHNOON_THE_DOCTOR :
            msg = tr("\nThe doctor is here to <i>heal the weakests</i> of you.");
            break;
          case HIGHNOON_THE_REVEREND :
            msg = tr("\nThee shall not consume the drink of the devil. As <i>beer</i> is corrupting men.");
            break;
          case HIGHNOON_THE_SERMON :
            msg = tr("\nThee shall not shoot. <i>Bangs</i> are not allowed by our mighty lord.");
            break;
          case HIGHNOON_THIRST :
            msg = tr("\nThe thirst is striking everybody down. Everyone will <i>pick only one card at the beginning of their turn</i>.");
            break;
          case HIGHNOON_TRAIN_ARRIVAL :
            msg = tr("\nA fresh train arrival ! Everybody can <i>pick up three cards at the beginning of their turn</i>.");
            break;
          case HIGHNOON_INVALID :
            break;
        }
    case GAMEMESSAGE_INVALID:
        break;
    }
    if (!msg.isEmpty())
        mp_game->sendLogMessage(msg);
    qDebug() << msg;
    GameEvent::finish();
}

QString GameMessageEvent::cardToString(const CardData& cardData, bool withRankAndSuit)
{
    if (cardData.id == 0) {
        return tr("<i>unknown card</i>");
    }
    const Card* card = Card::findPlayingCard(cardData.type);
    if (card == 0)
        return "";

    QString res = "<b><i>" + card->name() + "</i></b>";
    if (withRankAndSuit)
        res += " (" + Card::rankToString(cardData.rank) +
               Card::suitToColorString(cardData.suit) + ")";
    return res;
}

QString GameMessageEvent::cardListWidgetToString(QList<CardData> cardListWidget)
{
    if (cardListWidget.size() == 0)
        return "";
    QStringList cardStrings;
    foreach(const CardData& cardData, cardListWidget) {
        cardStrings.append(cardToString(cardData));
    }
    QString result;
    QStringListIterator it(cardStrings);
    result = it.next();
    while(it.hasNext()) {
        QString next = it.next();
        if (it.hasNext()) {
            result = tr("%1, %2").arg(result).arg(next);
        } else {
            result = tr("%1 and %2").arg(result).arg(next);
        }
    }
    return result;
}

QString GameMessageEvent::decoratePlayerName(const QString& playerName, bool isTarget)
{
    return QString("<font color=\"%2\"><b>%1</b></font>").
                  arg(playerName).arg(isTarget ? "navy" : "lightblue");
}
