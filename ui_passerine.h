/********************************************************************************
** Form generated from reading UI file 'passerine.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSERINE_H
#define UI_PASSERINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Passerine
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionClose;
    QAction *actionAbout_Passerine;
    QAction *actionAbout_Qt;
    QWidget *centralWidget;
    QTextEdit *tbLyrics;
    QMenuBar *menuBar;
    QMenu *menuFIle;
    QMenu *menuAbout;

    void setupUi(QMainWindow *Passerine)
    {
        if (Passerine->objectName().isEmpty())
            Passerine->setObjectName(QStringLiteral("Passerine"));
        Passerine->resize(525, 353);
        actionNew = new QAction(Passerine);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(Passerine);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(Passerine);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(Passerine);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionClose = new QAction(Passerine);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionAbout_Passerine = new QAction(Passerine);
        actionAbout_Passerine->setObjectName(QStringLiteral("actionAbout_Passerine"));
        actionAbout_Qt = new QAction(Passerine);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralWidget = new QWidget(Passerine);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setAutoFillBackground(false);
        tbLyrics = new QTextEdit(centralWidget);
        tbLyrics->setObjectName(QStringLiteral("tbLyrics"));
        tbLyrics->setGeometry(QRect(10, 250, 501, 71));
        Passerine->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Passerine);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 19));
        menuFIle = new QMenu(menuBar);
        menuFIle->setObjectName(QStringLiteral("menuFIle"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        Passerine->setMenuBar(menuBar);

        menuBar->addAction(menuFIle->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFIle->addAction(actionNew);
        menuFIle->addAction(actionOpen);
        menuFIle->addSeparator();
        menuFIle->addAction(actionSave);
        menuFIle->addAction(actionSave_As);
        menuFIle->addSeparator();
        menuFIle->addAction(actionClose);
        menuAbout->addAction(actionAbout_Passerine);
        menuAbout->addAction(actionAbout_Qt);

        retranslateUi(Passerine);

        QMetaObject::connectSlotsByName(Passerine);
    } // setupUi

    void retranslateUi(QMainWindow *Passerine)
    {
        Passerine->setWindowTitle(QApplication::translate("Passerine", "Passerine", 0));
        actionNew->setText(QApplication::translate("Passerine", "New", 0));
        actionNew->setShortcut(QApplication::translate("Passerine", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("Passerine", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("Passerine", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("Passerine", "Save", 0));
        actionSave->setShortcut(QApplication::translate("Passerine", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("Passerine", "Save As...", 0));
        actionSave_As->setShortcut(QApplication::translate("Passerine", "Ctrl+Shift+S", 0));
        actionClose->setText(QApplication::translate("Passerine", "Close", 0));
        actionClose->setShortcut(QApplication::translate("Passerine", "Ctrl+Q", 0));
        actionAbout_Passerine->setText(QApplication::translate("Passerine", "About Passerine...", 0));
        actionAbout_Qt->setText(QApplication::translate("Passerine", "About Qt...", 0));
        menuFIle->setTitle(QApplication::translate("Passerine", "FIle", 0));
        menuAbout->setTitle(QApplication::translate("Passerine", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class Passerine: public Ui_Passerine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSERINE_H
