/********************************************************************************
** Form generated from reading UI file 'passerine.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSERINE_H
#define UI_PASSERINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
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
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer;
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
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        playPauseButton = new QPushButton(centralWidget);
        playPauseButton->setObjectName(QStringLiteral("playPauseButton"));
        playPauseButton->setEnabled(false);

        horizontalLayout->addWidget(playPauseButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setEnabled(false);
        stopButton->setCheckable(false);
        stopButton->setAutoDefault(false);

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        Passerine->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Passerine);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 22));
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

        stopButton->setDefault(false);


        QMetaObject::connectSlotsByName(Passerine);
    } // setupUi

    void retranslateUi(QMainWindow *Passerine)
    {
        Passerine->setWindowTitle(QApplication::translate("Passerine", "Passerine", Q_NULLPTR));
        actionNew->setText(QApplication::translate("Passerine", "New", Q_NULLPTR));
        actionNew->setShortcut(QApplication::translate("Passerine", "Ctrl+N", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("Passerine", "Open", Q_NULLPTR));
        actionOpen->setShortcut(QApplication::translate("Passerine", "Ctrl+O", Q_NULLPTR));
        actionSave->setText(QApplication::translate("Passerine", "Save", Q_NULLPTR));
        actionSave->setShortcut(QApplication::translate("Passerine", "Ctrl+S", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("Passerine", "Save As...", Q_NULLPTR));
        actionSave_As->setShortcut(QApplication::translate("Passerine", "Ctrl+Shift+S", Q_NULLPTR));
        actionClose->setText(QApplication::translate("Passerine", "Close", Q_NULLPTR));
        actionClose->setShortcut(QApplication::translate("Passerine", "Ctrl+Q", Q_NULLPTR));
        actionAbout_Passerine->setText(QApplication::translate("Passerine", "About Passerine...", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("Passerine", "About Qt...", Q_NULLPTR));
        playPauseButton->setText(QApplication::translate("Passerine", "Play", Q_NULLPTR));
        stopButton->setText(QApplication::translate("Passerine", "Stop", Q_NULLPTR));
        menuFIle->setTitle(QApplication::translate("Passerine", "FIle", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("Passerine", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Passerine: public Ui_Passerine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSERINE_H
