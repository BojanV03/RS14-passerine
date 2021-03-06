#ifndef PICEDITOR_H
#define PICEDITOR_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <include/SongPlayer.h>
#include <include/MidiFile.h>
#include <QDebug>
#include <include/GeneralMidi.h>

#define isWhite(A) (*A == QColor(255, 255, 255).rgba())
#define NUMBER_OF_OCTAVES 8
#define KEYS_PER_OCTAVE 12
#define KEYS_PER_SCALE 7

namespace Ui
{
class picEditor;
}

class picEditor : public QDialog
{
    Q_OBJECT

public:
    explicit picEditor(QWidget *parent = 0, QImage *originalImage=nullptr);
    ~picEditor();

    SongPlayer *getPlayerRef() const;
    void setPlayerRef(SongPlayer *value);

    MidiFile *getMidi() const;
    void setMidi(MidiFile *value);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_cbPreview_toggled(bool checked);

    void on_cbInvert_toggled(bool checked);

    void on_buttonBox_accepted();

    void on_cbLockToScale_toggled(bool checked);

private:
    QImage *originalImage;
    int numberOfKeys = 96;
    SongPlayer *playerRef;
    void refreshImage();
    Ui::picEditor *ui;
    QImage image;
    MidiFile *Midi = new MidiFile();

    int getKeyInScale(int n);
    bool isWhiteNote(int i);
};

#endif // PICEDITOR_H
