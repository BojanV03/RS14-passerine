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
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QImage>

#include <include/RtMidi.h>
#include <include/portselector.h>
#include <include/MidiFile.h>
#include <include/SongPlayer.h>
#include <include/note.h>
#include <include/Key.h>
#include <include/piceditor.h>
#include <chrono>
#include <algorithm>

#include <include/noteGroup.h>

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

    int countNumberOfWhiteNotesInRange(int _startNote = 0, int _endNote = 96);

    void on_songSlider_sliderMoved(int position);

    void on_songSlider_sliderReleased();

    void on_actionNew_triggered();

    void on_actionLoadImage_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_volumeSlider_sliderMoved(int position);

//    void on_tbnoteLength_textChanged();

    void on_tbnoteLength_textChanged(const QString &arg1);

private:
    Ui::Passerine *ui;

    SongPlayer *songPlayer;
    RtMidiOut *midiout;
    MidiFile midifile;
    QGraphicsScene *scene;
    NoteGroup *group;

    int startNote;
    int endNote;
    int whiteNotesInRange;
    int widthCoef;
    std::vector<Key*> pianoKeys;

    std::vector<Note*> allNotesSortedByBeginTime;
    std::vector<Note*> allNotesSortedByEndTime;
    unsigned lastNoteAdded;
    unsigned lastNoteRemoved;

    void updateLastNotes();

    QTimer *pianoTimer;

    bool chooseMidiPort( RtMidiOut *rtmidi );
    bool isWhiteNote(int i);
    void drawPiano(int startNote = 0, int endNote = 96);
    double blackNoteHeight();
    double whiteNoteHeight();
    void makeNoteGroup();
    void noteGraphicsInit();
    void pianoKeyPress();
    void ResizePiano(int _startNote = 0, int _endNote = 96);
    void resetPiano();
    void enabledGUI(bool value);
    void updateNoteGroup();

    chrono::microseconds currentTime;
    chrono::microseconds previousTime;
    void ResizeNotes(int _startNote = 0, int _endNote = 96);
};

#endif // PASSERINE_H
