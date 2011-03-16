/********************************************************************************
** Form generated from reading UI file 'creategamedialog.ui'
**
** Created: Wed 16. Mar 09:48:10 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGAMEDIALOG_H
#define UI_CREATEGAMEDIALOG_H

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
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "selectplayericonwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CreateGameDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBoxMinPlayers;
    QLabel *label_4;
    QSpinBox *spinBoxMaxPlayers;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonOrderChronological;
    QRadioButton *radioButtonOrderRandom;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *lineEditGameName;
    QLabel *label_2;
    QLineEdit *lineEditGameDescription;
    QLabel *label_3;
    QLineEdit *lineEditGamePasswordPlayers;
    QLineEdit *lineEditPlayerName;
    QPushButton *pushButtonCreate;
    QPushButton *pushButtonCancel;
    QLabel *label_8;
    QSpinBox *spinBoxAIPlayers;
    QLabel *label_7;
    QLabel *label_9;
    client::SelectPlayerIconWidget *selectPlayerIconWidget;
    QLineEdit *lineEditPlayerPassword;
    QFrame *line_2;
    QLabel *label_11;
    QLineEdit *lineEditGamePasswordSpectators;
    QSpinBox *spinBoxMaxSpectators;
    QLabel *label_6;
    QLabel *label_12;
    QFrame *line;
    QLabel *label_5;

    void setupUi(QDialog *CreateGameDialog)
    {
        if (CreateGameDialog->objectName().isEmpty())
            CreateGameDialog->setObjectName(QString::fromUtf8("CreateGameDialog"));
        CreateGameDialog->resize(374, 369);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateGameDialog->sizePolicy().hasHeightForWidth());
        CreateGameDialog->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(CreateGameDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinBoxMinPlayers = new QSpinBox(CreateGameDialog);
        spinBoxMinPlayers->setObjectName(QString::fromUtf8("spinBoxMinPlayers"));

        horizontalLayout->addWidget(spinBoxMinPlayers);

        label_4 = new QLabel(CreateGameDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(16, 16777215));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_4);

        spinBoxMaxPlayers = new QSpinBox(CreateGameDialog);
        spinBoxMaxPlayers->setObjectName(QString::fromUtf8("spinBoxMaxPlayers"));

        horizontalLayout->addWidget(spinBoxMaxPlayers);


        gridLayout->addLayout(horizontalLayout, 2, 2, 1, 4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButtonOrderChronological = new QRadioButton(CreateGameDialog);
        radioButtonOrderChronological->setObjectName(QString::fromUtf8("radioButtonOrderChronological"));
        radioButtonOrderChronological->setChecked(true);

        verticalLayout->addWidget(radioButtonOrderChronological);

        radioButtonOrderRandom = new QRadioButton(CreateGameDialog);
        radioButtonOrderRandom->setObjectName(QString::fromUtf8("radioButtonOrderRandom"));

        verticalLayout->addWidget(radioButtonOrderRandom);


        gridLayout->addLayout(verticalLayout, 8, 2, 1, 4);

        horizontalSpacer = new QSpacerItem(213, 28, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 14, 0, 1, 3);

        label = new QLabel(CreateGameDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        lineEditGameName = new QLineEdit(CreateGameDialog);
        lineEditGameName->setObjectName(QString::fromUtf8("lineEditGameName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditGameName->sizePolicy().hasHeightForWidth());
        lineEditGameName->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditGameName, 0, 2, 1, 4);

        label_2 = new QLabel(CreateGameDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        lineEditGameDescription = new QLineEdit(CreateGameDialog);
        lineEditGameDescription->setObjectName(QString::fromUtf8("lineEditGameDescription"));
        sizePolicy1.setHeightForWidth(lineEditGameDescription->sizePolicy().hasHeightForWidth());
        lineEditGameDescription->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditGameDescription, 1, 2, 1, 4);

        label_3 = new QLabel(CreateGameDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        lineEditGamePasswordPlayers = new QLineEdit(CreateGameDialog);
        lineEditGamePasswordPlayers->setObjectName(QString::fromUtf8("lineEditGamePasswordPlayers"));
        sizePolicy1.setHeightForWidth(lineEditGamePasswordPlayers->sizePolicy().hasHeightForWidth());
        lineEditGamePasswordPlayers->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditGamePasswordPlayers, 5, 2, 2, 4);

        lineEditPlayerName = new QLineEdit(CreateGameDialog);
        lineEditPlayerName->setObjectName(QString::fromUtf8("lineEditPlayerName"));

        gridLayout->addWidget(lineEditPlayerName, 10, 1, 1, 4);

        pushButtonCreate = new QPushButton(CreateGameDialog);
        pushButtonCreate->setObjectName(QString::fromUtf8("pushButtonCreate"));

        gridLayout->addWidget(pushButtonCreate, 14, 3, 1, 1);

        pushButtonCancel = new QPushButton(CreateGameDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        gridLayout->addWidget(pushButtonCancel, 14, 4, 1, 2);

        label_8 = new QLabel(CreateGameDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 2);

        spinBoxAIPlayers = new QSpinBox(CreateGameDialog);
        spinBoxAIPlayers->setObjectName(QString::fromUtf8("spinBoxAIPlayers"));

        gridLayout->addWidget(spinBoxAIPlayers, 3, 2, 1, 4);

        label_7 = new QLabel(CreateGameDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_7, 10, 0, 1, 1);

        label_9 = new QLabel(CreateGameDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 12, 0, 1, 1);

        selectPlayerIconWidget = new client::SelectPlayerIconWidget(CreateGameDialog);
        selectPlayerIconWidget->setObjectName(QString::fromUtf8("selectPlayerIconWidget"));
        selectPlayerIconWidget->setFrameShape(QFrame::Box);
        selectPlayerIconWidget->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(selectPlayerIconWidget, 10, 5, 3, 1);

        lineEditPlayerPassword = new QLineEdit(CreateGameDialog);
        lineEditPlayerPassword->setObjectName(QString::fromUtf8("lineEditPlayerPassword"));

        gridLayout->addWidget(lineEditPlayerPassword, 12, 1, 1, 4);

        line_2 = new QFrame(CreateGameDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 13, 0, 1, 6);

        label_11 = new QLabel(CreateGameDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 7, 0, 1, 2);

        lineEditGamePasswordSpectators = new QLineEdit(CreateGameDialog);
        lineEditGamePasswordSpectators->setObjectName(QString::fromUtf8("lineEditGamePasswordSpectators"));
        lineEditGamePasswordSpectators->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEditGamePasswordSpectators->sizePolicy().hasHeightForWidth());
        lineEditGamePasswordSpectators->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditGamePasswordSpectators, 7, 2, 1, 4);

        spinBoxMaxSpectators = new QSpinBox(CreateGameDialog);
        spinBoxMaxSpectators->setObjectName(QString::fromUtf8("spinBoxMaxSpectators"));
        spinBoxMaxSpectators->setEnabled(false);
        spinBoxMaxSpectators->setMinimum(-1);

        gridLayout->addWidget(spinBoxMaxSpectators, 4, 2, 1, 4);

        label_6 = new QLabel(CreateGameDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 8, 0, 1, 2);

        label_12 = new QLabel(CreateGameDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 4, 0, 1, 2);

        line = new QFrame(CreateGameDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 9, 0, 1, 6);

        label_5 = new QLabel(CreateGameDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 2, 2);

#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(spinBoxMaxPlayers);
        label->setBuddy(lineEditGameName);
        label_2->setBuddy(lineEditGameDescription);
        label_3->setBuddy(spinBoxMinPlayers);
        label_8->setBuddy(spinBoxAIPlayers);
        label_7->setBuddy(lineEditPlayerName);
        label_9->setBuddy(lineEditPlayerPassword);
        label_11->setBuddy(lineEditGamePasswordSpectators);
        label_6->setBuddy(radioButtonOrderChronological);
        label_12->setBuddy(spinBoxMaxSpectators);
        label_5->setBuddy(lineEditGamePasswordPlayers);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEditGameName, lineEditGameDescription);
        QWidget::setTabOrder(lineEditGameDescription, spinBoxMinPlayers);
        QWidget::setTabOrder(spinBoxMinPlayers, spinBoxMaxPlayers);
        QWidget::setTabOrder(spinBoxMaxPlayers, spinBoxAIPlayers);
        QWidget::setTabOrder(spinBoxAIPlayers, spinBoxMaxSpectators);
        QWidget::setTabOrder(spinBoxMaxSpectators, lineEditGamePasswordPlayers);
        QWidget::setTabOrder(lineEditGamePasswordPlayers, lineEditGamePasswordSpectators);
        QWidget::setTabOrder(lineEditGamePasswordSpectators, radioButtonOrderChronological);
        QWidget::setTabOrder(radioButtonOrderChronological, radioButtonOrderRandom);
        QWidget::setTabOrder(radioButtonOrderRandom, lineEditPlayerName);
        QWidget::setTabOrder(lineEditPlayerName, lineEditPlayerPassword);
        QWidget::setTabOrder(lineEditPlayerPassword, pushButtonCreate);
        QWidget::setTabOrder(pushButtonCreate, pushButtonCancel);

        retranslateUi(CreateGameDialog);
        QObject::connect(pushButtonCancel, SIGNAL(clicked()), CreateGameDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(CreateGameDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateGameDialog)
    {
        CreateGameDialog->setWindowTitle(QApplication::translate("CreateGameDialog", "Create a game", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CreateGameDialog", "-", 0, QApplication::UnicodeUTF8));
        radioButtonOrderChronological->setText(QApplication::translate("CreateGameDialog", "Chronological", 0, QApplication::UnicodeUTF8));
        radioButtonOrderRandom->setText(QApplication::translate("CreateGameDialog", "Random", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("CreateGameDialog", "Game Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CreateGameDialog", "Game Description", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CreateGameDialog", "Number of Players", 0, QApplication::UnicodeUTF8));
        pushButtonCreate->setText(QApplication::translate("CreateGameDialog", "Create", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("CreateGameDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("CreateGameDialog", "Number of AI Players", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("CreateGameDialog", "Player Name", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_9->setToolTip(QApplication::translate("CreateGameDialog", "You can set your password here. This password will be required to reconnect to your player in case of disconnection.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("CreateGameDialog", "Player Password", 0, QApplication::UnicodeUTF8));
        selectPlayerIconWidget->setText(QApplication::translate("CreateGameDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Avatar</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_11->setToolTip(QApplication::translate("CreateGameDialog", "This is the password that is required to join the game as a spectator.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_11->setText(QApplication::translate("CreateGameDialog", "Password for Spectators", 0, QApplication::UnicodeUTF8));
        spinBoxMaxSpectators->setSpecialValueText(QApplication::translate("CreateGameDialog", "Infinity", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CreateGameDialog", "Order of Players", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("CreateGameDialog", "Max. Number of Spectators", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("CreateGameDialog", "This is the password that is required to join the game as a player.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("CreateGameDialog", "Password for Players", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateGameDialog: public Ui_CreateGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGAMEDIALOG_H
