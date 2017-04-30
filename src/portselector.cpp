#include <include/portselector.h>
#include "ui_portselector.h"
#include <QDebug>

PortSelector::PortSelector(QWidget *parent, RtMidiOut *Midi) :
    QDialog(parent),
    ui(new Ui::PortSelector)
{
    ui->setupUi(this);
    int numOfPorts = Midi->getPortCount();
    for(int i = 0; i < numOfPorts; i++)
    {
        QListWidgetItem *qlwi = new QListWidgetItem();
        qlwi->setData(0, i);
        ui->portList->addItem(QString::fromStdString(Midi->getPortName(i)));
    }


}

PortSelector::~PortSelector()
{
    delete ui;
}
void PortSelector::on_buttonBox_accepted()
{
    selectedPort = ui->portList->currentRow();
}

void PortSelector::on_buttonBox_rejected()
{
    selectedPort = -1;
}
