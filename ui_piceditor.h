/********************************************************************************
** Form generated from reading UI file 'piceditor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICEDITOR_H
#define UI_PICEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_picEditor
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *picLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider;
    QCheckBox *cbPreview;
    QCheckBox *cbInvert;
    QCheckBox *cbLockToScale;
    QComboBox *comboInstrument;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *picEditor)
    {
        if (picEditor->objectName().isEmpty())
            picEditor->setObjectName(QStringLiteral("picEditor"));
        picEditor->resize(724, 492);
        picEditor->setAutoFillBackground(true);
        verticalLayoutWidget = new QWidget(picEditor);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 701, 471));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        picLabel = new QLabel(verticalLayoutWidget);
        picLabel->setObjectName(QStringLiteral("picLabel"));

        verticalLayout->addWidget(picLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(256);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        cbPreview = new QCheckBox(verticalLayoutWidget);
        cbPreview->setObjectName(QStringLiteral("cbPreview"));

        horizontalLayout_2->addWidget(cbPreview);

        cbInvert = new QCheckBox(verticalLayoutWidget);
        cbInvert->setObjectName(QStringLiteral("cbInvert"));

        horizontalLayout_2->addWidget(cbInvert);

        cbLockToScale = new QCheckBox(verticalLayoutWidget);
        cbLockToScale->setObjectName(QStringLiteral("cbLockToScale"));

        horizontalLayout_2->addWidget(cbLockToScale);

        comboInstrument = new QComboBox(verticalLayoutWidget);
        comboInstrument->setObjectName(QStringLiteral("comboInstrument"));

        horizontalLayout_2->addWidget(comboInstrument);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setMaximumSize(QSize(16777215, 50));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(picEditor);
        QObject::connect(buttonBox, SIGNAL(accepted()), picEditor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), picEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(picEditor);
    } // setupUi

    void retranslateUi(QDialog *picEditor)
    {
        picEditor->setWindowTitle(QApplication::translate("picEditor", "Dialog", 0));
        picLabel->setText(QApplication::translate("picEditor", "TextLabel", 0));
        cbPreview->setText(QApplication::translate("picEditor", "Preview", 0));
        cbInvert->setText(QApplication::translate("picEditor", "Invert", 0));
        cbLockToScale->setText(QApplication::translate("picEditor", "Lock Scale", 0));
    } // retranslateUi

};

namespace Ui {
    class picEditor: public Ui_picEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICEDITOR_H
