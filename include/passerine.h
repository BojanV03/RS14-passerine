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
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <include/MidiFile.h>
#include <include/SongPlayer.h>
#include <QTimer>
namespace Ui {
class Passerine;
}

class Passerine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Passerine(QWidget *parent = 0);
    ~Passerine();
    void resizeEvent(QResizeEvent* event);
    void noteChanged(MidiEvent &m);


private slots:
    void on_actionClose_triggered();

    void on_actionAbout_Passerine_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionOpen_triggered();

    void on_playPauseButton_clicked();

    void on_stopButton_clicked();

    void updateGraphics();

private:
    Ui::Passerine *ui;

    SongPlayer *songPlayer;
    RtMidiOut *midiout;
    MidiFile midifile;
    QGraphicsScene *scene;
    std::vector<bool> noteStates;

    QTimer *graphicsTimer;

    bool chooseMidiPort( RtMidiOut *rtmidi );
    void drawPiano(int startNote = 0, int endNote = 96);
};

#endif // PASSERINE_H
