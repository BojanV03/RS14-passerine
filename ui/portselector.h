#ifndef PORTSELECTOR_H
#define PORTSELECTOR_H

#include <QDialog>
#include <QListWidgetItem>
#include <include/RtMidi.h>
#include <include/rtmidi_c.h>

namespace Ui {
class PortSelector;
}

class PortSelector : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelector(QWidget *parent = 0, RtMidiOut *midi = new RtMidiOut());
    ~PortSelector();
    int selectedPort;
private slots:
    void on_buttonBox_accepted();

    void on_portList_itemChanged(QListWidgetItem *item);

    void on_portList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::PortSelector *ui;
};

#endif // PORTSELECTOR_H
