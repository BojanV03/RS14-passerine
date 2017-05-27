#include "piceditor.h"
#include "ui_piceditor.h"

picEditor::picEditor(QWidget *parent, QImage *_originalImage) :
    QDialog(parent), originalImage(_originalImage), ui(new Ui::picEditor)
{
    ui->setupUi(this);
    ui->picLabel->setPixmap(QPixmap::fromImage((*originalImage).scaled(width()-20, height()-20, Qt::KeepAspectRatio), Qt::AutoColor));
}

picEditor::~picEditor()
{
    delete ui;
}
#include <QDebug>

void picEditor::on_horizontalSlider_valueChanged(int value)
{
    refreshImage();
}

void picEditor::on_cbPreview_toggled(bool checked)
{
    refreshImage();
}

void picEditor::refreshImage()
{

    int value = ui->horizontalSlider->value();

    if(!ui->cbPreview->isChecked())
    {
        image = *originalImage;

        for (int ii = 0; ii < image.height(); ii++)
        {
            uchar* scan = image.scanLine(ii);
            int depth =4;
            for (int jj = 0; jj < image.width(); jj++)
            {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
                int gray = qGray(*rgbpixel);
                if(gray >= value)
                    *rgbpixel = QColor(255, 255, 255).rgba();
                else
                    *rgbpixel = QColor(0, 0, 0).rgba();
            }
        }
        if(ui->cbInvert->isChecked())
        {
            image.invertPixels();
        }
        ui->picLabel->setPixmap(QPixmap::fromImage(image.scaled(width()-20, height()-20, Qt::KeepAspectRatio), Qt::AutoColor));
    }
    else
    {
        QImage imagetmp(*originalImage);


        image = imagetmp.scaledToHeight(96);

        for (int ii = 0; ii < image.height(); ii++)
        {
            uchar* scan = image.scanLine(ii);
            int depth =4;
            for (int jj = 0; jj < image.width(); jj++)
            {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
                int gray = qGray(*rgbpixel);
                if(gray >= value)
                    *rgbpixel = QColor(255, 255, 255).rgba();
                else
                    *rgbpixel = QColor(0, 0, 0).rgba();
            }
        }
        if(ui->cbInvert->isChecked())
        {
            image.invertPixels();
        }
        ui->picLabel->setPixmap(QPixmap::fromImage(image.scaled(width()-20, height()-20, Qt::KeepAspectRatio), Qt::AutoColor));
    }
}

MidiFile *picEditor::getMidi() const
{
    return Midi;
}

void picEditor::setMidi(MidiFile *value)
{
    Midi = value;
}


void picEditor::on_cbInvert_toggled(bool checked)
{
    refreshImage();
}

#define isWhite(A) (*A == QColor(255, 255, 255).rgba())
#include <include/MidiFile.h>

void picEditor::on_buttonBox_accepted()
{
    ui->cbPreview->setChecked(true);
    refreshImage();

    Midi->addTracks(2);    // Add another two tracks to the MIDI file
    int tpq = 100;            // ticks per quarter note
    Midi->setTicksPerQuarterNote(tpq);
    tpq = 10;
    // Add some expression track (track 0) messages:
    Midi->addTrackName(0, 0, "Test");
    Midi->addTempo(0, 0, 120);

    int noteOnCounter = 0;
    int noteOffCounter = 0;
    for (int i = 0; i < image.height(); i++)
    {
        uchar* scan = image.scanLine(i);
        int depth =4;
        for (int j = 1; j < image.width(); j++)
        {
            QRgb* prevPixel = reinterpret_cast<QRgb*>(scan + (j-1)*depth);
            QRgb* currPixel = reinterpret_cast<QRgb*>(scan + j*depth);
            QRgb* nextPixel = reinterpret_cast<QRgb*>(scan + (j+1)*depth);

            // NoteOn event generisemo samo ako je pocetni pixel beo ili ako je prethodni bio crn a trenutni beo
            if((isWhite(currPixel) && j == 0) || (isWhite(currPixel) && !isWhite(prevPixel)))
            {
                qDebug() << "Note on: 0 " << j << " 0 " << i+1 << " 60";
                int n = Midi->addNoteOn(0, tpq*j, 0, i+12, 60);
         //     Midi->getEvent(0, n).seconds = j/100.0;
                noteOnCounter++;
            }
            // NoteOff event generisemo samo ako je trenutni pixel crn a prethodni beo ili ako je trenutni/zadnji pixel beo
            if((isWhite(currPixel) && (j + 1 == image.width()) || (isWhite(currPixel) && !isWhite(nextPixel))))
            {
                qDebug() << "Note off: 0 " << j << " 0 " << i+1;
                int n = Midi->addNoteOff(0, tpq*(j+1), 0, i+12);
        //        Midi->getEvent(0, n).seconds = j/100.0;
                noteOffCounter++;
            }
        }
    }

    Midi->getTotalTimeInSeconds();
    Midi->joinTracks();
    Midi->sortTracks();
//    Midi->buildTimeMap();
    Midi->write("GeneratedMidi.mid");
    playerRef->setSong(Midi);
//    delete Midi;
    qDebug() << noteOnCounter << " je on; " << noteOffCounter << " je off.";
}

SongPlayer *picEditor::getPlayerRef() const
{
    return playerRef;
}

void picEditor::setPlayerRef(SongPlayer *value)
{
    playerRef = value;
}

void picEditor::on_cbLockToScale_toggled(bool checked)
{

}
