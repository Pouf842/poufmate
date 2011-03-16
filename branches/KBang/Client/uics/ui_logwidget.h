/********************************************************************************
** Form generated from reading UI file 'logwidget.ui'
**
** Created: Wed 16. Mar 09:48:10 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWIDGET_H
#define UI_LOGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *mp_tabWidget;
    QWidget *mp_tabLog;
    QGridLayout *gridLayout;
    QTextBrowser *mp_logView;
    QWidget *mp_tabDebug;
    QGridLayout *gridLayout1;
    QTextBrowser *mp_xmlView;

    void setupUi(QWidget *LogWidget)
    {
        if (LogWidget->objectName().isEmpty())
            LogWidget->setObjectName(QString::fromUtf8("LogWidget"));
        LogWidget->resize(268, 224);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LogWidget->sizePolicy().hasHeightForWidth());
        LogWidget->setSizePolicy(sizePolicy);
        LogWidget->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	border: 1px solid gray;\n"
"	background-color: rgba(0, 0, 0, 32);\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"	background: rgba(0, 0, 0, 0);\n"
"	border: 0;\n"
"\n"
"    /*    \n"
"    position: absolute;\n"
"    top: 7px;\n"
"    */\n"
"}\n"
"QTabWidget::tab-bar {\n"
"	left: 10px;\n"
"}\n"
"QTabBar::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                   stop: 0 rgba(0, 0, 0, 16),\n"
"								   stop: 0.4 rgba(0, 0, 0, 32),\n"
"                                   stop: 0.5 rgba(0, 0, 0, 30),\n"
"                                   stop: 1.0 rgba(0, 0, 0, 16));\n"
"     min-width: 8ex;\n"
"     padding: 2px;\n"
"	margin-right: 2px;\n"
"/*\n"
"	padding: 4px;\n"
"	margin-right: 2px;\n"
"	min-width: 40px;\n"
"*/\n"
"		\n"
";\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                   stop: 0 rgba(0, 0, 0, 32),\n"
"								   stop: 0.4 rgba(0, 0"
                        ", 0, 64),\n"
"                                   stop: 0.5 rgba(0, 0, 0, 60),\n"
"                                   stop: 1.0 rgba(0, 0, 0, 32));\n"
"	border: 1px solid gray;\n"
"	border-bottom: 0;\n"
"\n"
" }\n"
"QScrollBar:vertical {\n"
"	border: 1px solid grey;\n"
"	background: rgba(0, 0, 0, 0);\n"
"	width: 15px;\n"
"	margin: 19px 0 19px 0;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"	background: rgba(0, 0, 0, 32);\n"
"	border-top: 1px solid grey;\n"
"	border-bottom: 1px solid grey;\n"
"	min-height: 45px;\n"
"	margin-top: -1;\n"
"	margin-bottom: -1;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"	border: 1px solid grey;\n"
"	background: rgba(0, 0, 0, 32);\n"
"	height: 15px;\n"
"	subcontrol-position: bottom;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"	border: 1px solid grey;\n"
"	background: rgba(0, 0, 0, 32);\n"
"	height: 15px;\n"
"	subcontrol-position: top;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
""
                        "	border: 1px solid grey;\n"
"	width: 5px;\n"
"	height: 5px;\n"
"	background: rgb(0, 0, 0, 32);\n"
"}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"	background: none;\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(LogWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mp_tabWidget = new QTabWidget(LogWidget);
        mp_tabWidget->setObjectName(QString::fromUtf8("mp_tabWidget"));
        mp_tabWidget->setFocusPolicy(Qt::WheelFocus);
        mp_tabWidget->setStyleSheet(QString::fromUtf8(""));
        mp_tabWidget->setTabShape(QTabWidget::Triangular);
        mp_tabLog = new QWidget();
        mp_tabLog->setObjectName(QString::fromUtf8("mp_tabLog"));
        gridLayout = new QGridLayout(mp_tabLog);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        mp_logView = new QTextBrowser(mp_tabLog);
        mp_logView->setObjectName(QString::fromUtf8("mp_logView"));
        mp_logView->setFocusPolicy(Qt::NoFocus);
        mp_logView->setStyleSheet(QString::fromUtf8(""));
        mp_logView->setOpenLinks(false);

        gridLayout->addWidget(mp_logView, 0, 0, 1, 1);

        mp_tabWidget->addTab(mp_tabLog, QString());
        mp_tabDebug = new QWidget();
        mp_tabDebug->setObjectName(QString::fromUtf8("mp_tabDebug"));
        gridLayout1 = new QGridLayout(mp_tabDebug);
        gridLayout1->setSpacing(0);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        mp_xmlView = new QTextBrowser(mp_tabDebug);
        mp_xmlView->setObjectName(QString::fromUtf8("mp_xmlView"));

        gridLayout1->addWidget(mp_xmlView, 0, 0, 1, 1);

        mp_tabWidget->addTab(mp_tabDebug, QString());

        horizontalLayout->addWidget(mp_tabWidget);


        retranslateUi(LogWidget);

        mp_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LogWidget);
    } // setupUi

    void retranslateUi(QWidget *LogWidget)
    {
        LogWidget->setWindowTitle(QApplication::translate("LogWidget", "Form", 0, QApplication::UnicodeUTF8));
        mp_logView->setHtml(QApplication::translate("LogWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; color:#ffffff;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        mp_tabWidget->setTabText(mp_tabWidget->indexOf(mp_tabLog), QApplication::translate("LogWidget", "Log", 0, QApplication::UnicodeUTF8));
        mp_xmlView->setHtml(QApplication::translate("LogWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        mp_tabWidget->setTabText(mp_tabWidget->indexOf(mp_tabDebug), QApplication::translate("LogWidget", "Xml", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogWidget: public Ui_LogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWIDGET_H
