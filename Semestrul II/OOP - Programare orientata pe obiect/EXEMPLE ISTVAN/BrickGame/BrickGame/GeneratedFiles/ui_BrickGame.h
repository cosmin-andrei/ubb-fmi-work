/********************************************************************************
** Form generated from reading UI file 'BrickGame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRICKGAME_H
#define UI_BRICKGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrickGameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BrickGameClass)
    {
        if (BrickGameClass->objectName().isEmpty())
            BrickGameClass->setObjectName(QString::fromUtf8("BrickGameClass"));
        BrickGameClass->resize(600, 400);
        menuBar = new QMenuBar(BrickGameClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        BrickGameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BrickGameClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BrickGameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BrickGameClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BrickGameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BrickGameClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BrickGameClass->setStatusBar(statusBar);

        retranslateUi(BrickGameClass);

        QMetaObject::connectSlotsByName(BrickGameClass);
    } // setupUi

    void retranslateUi(QMainWindow *BrickGameClass)
    {
        BrickGameClass->setWindowTitle(QApplication::translate("BrickGameClass", "BrickGame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrickGameClass: public Ui_BrickGameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRICKGAME_H
