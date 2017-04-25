#ifndef PASSERINE_H
#define PASSERINE_H

#include <QMainWindow>
#include <QApplication>
#include <QDialog>
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <include/RtMidi.h>
#include <include/portselector.h>

#include <include/SongPlayer.h>
#include <include/MidiFile.h>

namespace Ui {
class Passerine;
}

class Passerine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Passerine(QWidget *parent = 0);
    ~Passerine();

private slots:
    void on_actionClose_triggered();

    void on_actionAbout_Passerine_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionOpen_triggered();


private:
    Ui::Passerine *ui;

};

#endif // PASSERINE_H
