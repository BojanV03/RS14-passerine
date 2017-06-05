/********************************************************************************
** Form generated from reading UI file 'passerine.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
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
    QAction *actionLoadImage;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *tbLyrics;
    QSlider *songSlider;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer;
    QSlider *volumeSlider;
    QMenuBar *menuBar;
    QMenu *menuFIle;
    QMenu *menuAbout;

    void setupUi(QMainWindow *Passerine)
    {
        if (Passerine->objectName().isEmpty())
            Passerine->setObjectName(QStringLiteral("Passerine"));
        Passerine->resize(525, 353);
        Passerine->setWindowOpacity(5);
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
        actionLoadImage = new QAction(Passerine);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        centralWidget = new QWidget(Passerine);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        tbLyrics = new QTextEdit(centralWidget);
        tbLyrics->setObjectName(QStringLiteral("tbLyrics"));
        tbLyrics->setMaximumSize(QSize(16777215, 75));

        verticalLayout->addWidget(tbLyrics);

        songSlider = new QSlider(centralWidget);
        songSlider->setObjectName(QStringLiteral("songSlider"));
        songSlider->setEnabled(false);
        songSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(songSlider);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setLayoutDirection(Qt::LeftToRight);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSceneRect(QRectF(0, 0, 0, 0));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        playPauseButton = new QPushButton(centralWidget);
        playPauseButton->setObjectName(QStringLiteral("playPauseButton"));
        playPauseButton->setEnabled(false);

        horizontalLayout->addWidget(playPauseButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setEnabled(false);
        stopButton->setCheckable(false);
        stopButton->setAutoDefault(false);
        stopButton->setDefault(false);

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setMaximum(127);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(volumeSlider);


        verticalLayout->addLayout(horizontalLayout);

        Passerine->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Passerine);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 25));
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
        menuFIle->addAction(actionLoadImage);
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
        actionLoadImage->setText(QApplication::translate("Passerine", "Load Image", 0));
        actionLoadImage->setShortcut(QApplication::translate("Passerine", "Ctrl+C", 0));
        playPauseButton->setText(QApplication::translate("Passerine", "Play", 0));
        stopButton->setText(QApplication::translate("Passerine", "Stop", 0));
        menuFIle->setTitle(QApplication::translate("Passerine", "FIle", 0));
        menuAbout->setTitle(QApplication::translate("Passerine", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class Passerine: public Ui_Passerine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSERINE_H
