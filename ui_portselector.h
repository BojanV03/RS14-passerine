/********************************************************************************
** Form generated from reading UI file 'portselector.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTSELECTOR_H
#define UI_PORTSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_PortSelector
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *portList;

    void setupUi(QDialog *PortSelector)
    {
        if (PortSelector->objectName().isEmpty())
            PortSelector->setObjectName(QStringLiteral("PortSelector"));
        PortSelector->resize(400, 300);
        buttonBox = new QDialogButtonBox(PortSelector);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        portList = new QListWidget(PortSelector);
        portList->setObjectName(QStringLiteral("portList"));
        portList->setGeometry(QRect(20, 10, 371, 221));

        retranslateUi(PortSelector);
        QObject::connect(buttonBox, SIGNAL(accepted()), PortSelector, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PortSelector, SLOT(reject()));

        QMetaObject::connectSlotsByName(PortSelector);
    } // setupUi

    void retranslateUi(QDialog *PortSelector)
    {
        PortSelector->setWindowTitle(QApplication::translate("PortSelector", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PortSelector: public Ui_PortSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTSELECTOR_H
