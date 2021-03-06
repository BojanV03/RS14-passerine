#include <include/piceditor.h>
#include "ui_piceditor.h"

picEditor::picEditor(QWidget *parent, QImage *_originalImage) :
    QDialog(parent), originalImage(_originalImage), ui(new Ui::picEditor)
{

    ui->setupUi(this);
    ui->picLabel->setPixmap(QPixmap::fromImage((*originalImage).scaled(width()-20, height()-20, Qt::KeepAspectRatio), Qt::AutoColor));

    GeneralMidi *gm = new GeneralMidi();

    for(int i = 0; i < 128; i++)
    {
        QString str1 = *gm->getNameFromId(i);
        QByteArray ba = str1.toLatin1();
        const char *c_str2 = ba.data();
        ui->comboInstrument->addItem(tr(c_str2));
    }
    delete gm;
}

picEditor::~picEditor()
{
    delete ui;
}

void picEditor::on_horizontalSlider_valueChanged(int)
{
    refreshImage();
}

void picEditor::on_cbPreview_toggled(bool)
{
    refreshImage();
}


void picEditor::on_cbInvert_toggled(bool)
{
    refreshImage();
}

void picEditor::on_cbLockToScale_toggled(bool checked)
{
    if(!checked)
    {
        numberOfKeys = NUMBER_OF_OCTAVES * KEYS_PER_OCTAVE;
    }
    else
    {
        numberOfKeys = NUMBER_OF_OCTAVES * KEYS_PER_SCALE;
    }
    refreshImage();
}

// Vraca ID note u zavisnosti od toga da li se sviraju samo bele ili sve note
int picEditor::getKeyInScale(int n)
{
    if(!ui->cbLockToScale->isChecked())
        return n;

    else
    {
        int j=0;
        for(int i = 0; i < 96; i++)
        {
            if(isWhiteNote(i))
              j++;
            if(j == n)
                return i;
        }
    }

    return -1;
}

/*
 * Pretvara sliku u crno/belu verziju i resizuje je tako da odgovara korisnikovim zahtevima
 */
void picEditor::refreshImage()
{
    int value = ui->horizontalSlider->value();

    if(!ui->cbPreview->isChecked()) //ako cbPreview nije checkiran, prikazi sliku u punoj rezoluciji
    {
        image = *originalImage;

        for (int ii = 0; ii < image.height(); ii++)
        {
            uchar* scan = image.scanLine(ii);
            int depth = 4;
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
    else    //inace resizuj sliku na zeljenu velicinu
    {
        QImage imagetmp(*originalImage);

        image = imagetmp.scaledToHeight(numberOfKeys);

        for (int ii = 0; ii < image.height(); ii++)
        {
            uchar* scan = image.scanLine(ii);
            int depth = 4;
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


/*
 * Generise MIDI file sa
 */
void picEditor::on_buttonBox_accepted()
{
    ui->cbPreview->setChecked(true);
    refreshImage();

    Midi->addTracks(2);    // Dodajemo trake
    int tpq = 100;            // Broj tikova po cetvrtini note
    Midi->setTicksPerQuarterNote(tpq);
    tpq = 10 * (96.0/numberOfKeys);

    // Dodajemo ime trake i tempo
    Midi->addTrackName(0, 0, "Test");
    Midi->addTempo(0, 0, 120);

    Midi->addPatchChange(0, 0, 0, ui->comboInstrument->currentIndex());
    qDebug() << "selected instrument: " << ui->comboInstrument->currentIndex();

    // Brojaci za debagovanje
    int noteOnCounter = 0;
    int noteOffCounter = 0;

    for (int i = 0; i < image.height(); i++)
    {
        uchar* scan = image.scanLine(i);
        int depth = 4;

        for (int j = 1; j < image.width(); j++)
        {
            QRgb* prevPixel = reinterpret_cast<QRgb*>(scan + (j-1)*depth);
            QRgb* currPixel = reinterpret_cast<QRgb*>(scan + j*depth);
            QRgb* nextPixel = reinterpret_cast<QRgb*>(scan + (j+1)*depth);

            // NoteOn event generisemo samo ako je pocetni pixel beo ili ako je prethodni bio crn a trenutni beo
            if((isWhite(currPixel) && j == 0) || (isWhite(currPixel) && !isWhite(prevPixel)))
            {
                Midi->addNoteOn(0, tpq*j, 0, getKeyInScale(i)+12, 60);

                noteOnCounter++;
            }
            // NoteOff event generisemo samo ako je trenutni pixel crn a prethodni beo ili ako je trenutni/zadnji pixel beo
            if((isWhite(currPixel) && (j + 1 == image.width())) || (isWhite(currPixel) && !isWhite(nextPixel)))
            {
                Midi->addNoteOff(0, tpq*(j+1), 0, getKeyInScale(i)+12);

                noteOffCounter++;
            }
        }
    }

    Midi->getTotalTimeInSeconds();
    Midi->joinTracks();
    Midi->sortTracks();

    Midi->write("GeneratedMidi.mid");
    playerRef->setSong(Midi);

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


MidiFile *picEditor::getMidi() const
{
    return Midi;
}

void picEditor::setMidi(MidiFile *value)
{
    Midi = value;
}


bool picEditor::isWhiteNote(int i)
{
    int note = i % 12;

    if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
        return true;

    return false;
}
