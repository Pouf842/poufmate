/********************************************************************************
** Form generated from reading UI file 'joingamedialog.ui'
**
** Created: Wed 16. Mar 09:48:10 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINGAMEDIALOG_H
#define UI_JOINGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include "selectplayericonwidget.h"

QT_BEGIN_NAMESPACE

class Ui_JoinGameDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *gameListView;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *labelName;
    QLabel *label_14;
    QLabel *labelDescription;
    QLabel *label_15;
    QLabel *labelState;
    QLabel *label_16;
    QLabel *labelPlayers;
    QLabel *label_18;
    QLabel *labelAIPlayers;
    QLabel *label_17;
    QLabel *labelPassword;
    QTreeWidget *playerListView;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLineEdit *lineEditPlayerName;
    client::SelectPlayerIconWidget *selectPlayerIconWidget;
    QLabel *label_9;
    QLineEdit *lineEditPlayerPassword;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonRefresh;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonSpectate;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *JoinGameDialog)
    {
        if (JoinGameDialog->objectName().isEmpty())
            JoinGameDialog->setObjectName(QString::fromUtf8("JoinGameDialog"));
        JoinGameDialog->resize(575, 461);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(JoinGameDialog->sizePolicy().hasHeightForWidth());
        JoinGameDialog->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(JoinGameDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gameListView = new QTreeWidget(JoinGameDialog);
        gameListView->setObjectName(QString::fromUtf8("gameListView"));
        gameListView->setFocusPolicy(Qt::NoFocus);
        gameListView->setAutoScroll(true);
        gameListView->setAlternatingRowColors(true);
        gameListView->setIndentation(15);
        gameListView->setRootIsDecorated(false);
        gameListView->setItemsExpandable(false);
        gameListView->setSortingEnabled(true);
        gameListView->setAnimated(true);
        gameListView->setAllColumnsShowFocus(false);

        horizontalLayout_2->addWidget(gameListView);

        line_2 = new QFrame(JoinGameDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(JoinGameDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QFont font;
        font.setPointSize(12);
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 0, 0, 1, 2);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        labelName = new QLabel(frame);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout_2->addWidget(labelName, 1, 1, 1, 1);

        label_14 = new QLabel(frame);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 2, 0, 1, 1);

        labelDescription = new QLabel(frame);
        labelDescription->setObjectName(QString::fromUtf8("labelDescription"));

        gridLayout_2->addWidget(labelDescription, 2, 1, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 3, 0, 1, 1);

        labelState = new QLabel(frame);
        labelState->setObjectName(QString::fromUtf8("labelState"));

        gridLayout_2->addWidget(labelState, 3, 1, 1, 1);

        label_16 = new QLabel(frame);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 4, 0, 1, 1);

        labelPlayers = new QLabel(frame);
        labelPlayers->setObjectName(QString::fromUtf8("labelPlayers"));

        gridLayout_2->addWidget(labelPlayers, 4, 1, 1, 1);

        label_18 = new QLabel(frame);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 5, 0, 1, 1);

        labelAIPlayers = new QLabel(frame);
        labelAIPlayers->setObjectName(QString::fromUtf8("labelAIPlayers"));

        gridLayout_2->addWidget(labelAIPlayers, 5, 1, 1, 1);

        label_17 = new QLabel(frame);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 6, 0, 1, 1);

        labelPassword = new QLabel(frame);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        gridLayout_2->addWidget(labelPassword, 6, 1, 1, 1);


        verticalLayout->addWidget(frame);

        playerListView = new QTreeWidget(JoinGameDialog);
        new QTreeWidgetItem(playerListView);
        playerListView->setObjectName(QString::fromUtf8("playerListView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playerListView->sizePolicy().hasHeightForWidth());
        playerListView->setSizePolicy(sizePolicy1);
        playerListView->setFocusPolicy(Qt::NoFocus);
        playerListView->setEditTriggers(QAbstractItemView::EditKeyPressed);
        playerListView->setAlternatingRowColors(true);
        playerListView->setSelectionMode(QAbstractItemView::SingleSelection);
        playerListView->setIndentation(15);
        playerListView->setRootIsDecorated(false);
        playerListView->setUniformRowHeights(true);
        playerListView->setItemsExpandable(false);
        playerListView->setSortingEnabled(false);
        playerListView->setAnimated(false);
        playerListView->setAllColumnsShowFocus(false);
        playerListView->setHeaderHidden(false);
        playerListView->setExpandsOnDoubleClick(true);

        verticalLayout->addWidget(playerListView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(JoinGameDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        lineEditPlayerName = new QLineEdit(JoinGameDialog);
        lineEditPlayerName->setObjectName(QString::fromUtf8("lineEditPlayerName"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditPlayerName->sizePolicy().hasHeightForWidth());
        lineEditPlayerName->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lineEditPlayerName, 0, 1, 1, 1);

        selectPlayerIconWidget = new client::SelectPlayerIconWidget(JoinGameDialog);
        selectPlayerIconWidget->setObjectName(QString::fromUtf8("selectPlayerIconWidget"));
        selectPlayerIconWidget->setMinimumSize(QSize(64, 64));
        selectPlayerIconWidget->setMaximumSize(QSize(64, 64));
        selectPlayerIconWidget->setFrameShape(QFrame::Box);
        selectPlayerIconWidget->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(selectPlayerIconWidget, 0, 2, 2, 1);

        label_9 = new QLabel(JoinGameDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        lineEditPlayerPassword = new QLineEdit(JoinGameDialog);
        lineEditPlayerPassword->setObjectName(QString::fromUtf8("lineEditPlayerPassword"));
        sizePolicy3.setHeightForWidth(lineEditPlayerPassword->sizePolicy().hasHeightForWidth());
        lineEditPlayerPassword->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lineEditPlayerPassword, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line = new QFrame(JoinGameDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonRefresh = new QPushButton(JoinGameDialog);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));

        horizontalLayout->addWidget(pushButtonRefresh);

        pushButtonPlay = new QPushButton(JoinGameDialog);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));

        horizontalLayout->addWidget(pushButtonPlay);

        pushButtonSpectate = new QPushButton(JoinGameDialog);
        pushButtonSpectate->setObjectName(QString::fromUtf8("pushButtonSpectate"));
        pushButtonSpectate->setEnabled(false);

        horizontalLayout->addWidget(pushButtonSpectate);

        pushButtonCancel = new QPushButton(JoinGameDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);


        verticalLayout_2->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        label_7->setBuddy(lineEditPlayerName);
        label_9->setBuddy(lineEditPlayerPassword);
#endif // QT_NO_SHORTCUT

        retranslateUi(JoinGameDialog);
        QObject::connect(pushButtonCancel, SIGNAL(clicked()), JoinGameDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(JoinGameDialog);
    } // setupUi

    void retranslateUi(QDialog *JoinGameDialog)
    {
        JoinGameDialog->setWindowTitle(QApplication::translate("JoinGameDialog", "Join Game", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = gameListView->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("JoinGameDialog", "Players", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("JoinGameDialog", "State", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("JoinGameDialog", "Name", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("JoinGameDialog", "Game Info", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("JoinGameDialog", "Name:", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("JoinGameDialog", "[Name]", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("JoinGameDialog", "Description:", 0, QApplication::UnicodeUTF8));
        labelDescription->setText(QApplication::translate("JoinGameDialog", "[Description]", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("JoinGameDialog", "State:", 0, QApplication::UnicodeUTF8));
        labelState->setText(QApplication::translate("JoinGameDialog", "[State]", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("JoinGameDialog", "Players:", 0, QApplication::UnicodeUTF8));
        labelPlayers->setText(QApplication::translate("JoinGameDialog", "[Players]", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("JoinGameDialog", "AI Players:", 0, QApplication::UnicodeUTF8));
        labelAIPlayers->setText(QApplication::translate("JoinGameDialog", "[AI Players]", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("JoinGameDialog", "Password:", 0, QApplication::UnicodeUTF8));
        labelPassword->setText(QApplication::translate("JoinGameDialog", "[Password]", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = playerListView->headerItem();
        ___qtreewidgetitem1->setText(3, QApplication::translate("JoinGameDialog", "Z", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(2, QApplication::translate("JoinGameDialog", "Y", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(1, QApplication::translate("JoinGameDialog", "X", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("JoinGameDialog", "Players", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = playerListView->isSortingEnabled();
        playerListView->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem2 = playerListView->topLevelItem(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("JoinGameDialog", "Create new player", 0, QApplication::UnicodeUTF8));
        playerListView->setSortingEnabled(__sortingEnabled);

        label_7->setText(QApplication::translate("JoinGameDialog", "Player Name", 0, QApplication::UnicodeUTF8));
        selectPlayerIconWidget->setText(QApplication::translate("JoinGameDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Avatar</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_9->setToolTip(QApplication::translate("JoinGameDialog", "You can set your password here. This password will be required to reconnect to your player in case of disconnection.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("JoinGameDialog", "Player Password", 0, QApplication::UnicodeUTF8));
        pushButtonRefresh->setText(QApplication::translate("JoinGameDialog", "Refresh", 0, QApplication::UnicodeUTF8));
        pushButtonPlay->setText(QApplication::translate("JoinGameDialog", "Play", 0, QApplication::UnicodeUTF8));
        pushButtonSpectate->setText(QApplication::translate("JoinGameDialog", "Spectate", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("JoinGameDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class JoinGameDialog: public Ui_JoinGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINGAMEDIALOG_H
