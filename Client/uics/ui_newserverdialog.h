/********************************************************************************
** Form generated from reading UI file 'newserverdialog.ui'
**
** Created: Thu 17. Mar 13:27:44 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSERVERDIALOG_H
#define UI_NEWSERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewServerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditHost;
    QLabel *label_2;
    QSpinBox *spinBoxPort;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewServerDialog)
    {
        if (NewServerDialog->objectName().isEmpty())
            NewServerDialog->setObjectName(QString::fromUtf8("NewServerDialog"));
        NewServerDialog->resize(219, 95);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewServerDialog->sizePolicy().hasHeightForWidth());
        NewServerDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(NewServerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewServerDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditHost = new QLineEdit(NewServerDialog);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));

        gridLayout->addWidget(lineEditHost, 0, 1, 1, 1);

        label_2 = new QLabel(NewServerDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBoxPort = new QSpinBox(NewServerDialog);
        spinBoxPort->setObjectName(QString::fromUtf8("spinBoxPort"));

        gridLayout->addWidget(spinBoxPort, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(NewServerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEditHost);
        label_2->setBuddy(spinBoxPort);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEditHost, spinBoxPort);
        QWidget::setTabOrder(spinBoxPort, buttonBox);

        retranslateUi(NewServerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewServerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewServerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewServerDialog);
    } // setupUi

    void retranslateUi(QDialog *NewServerDialog)
    {
        label->setText(QApplication::translate("NewServerDialog", "Server &Host:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewServerDialog", "Server &Port:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(NewServerDialog);
    } // retranslateUi

};

namespace Ui {
    class NewServerDialog: public Ui_NewServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSERVERDIALOG_H
