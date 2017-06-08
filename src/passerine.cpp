#include <include/passerine.h>

#include "ui_passerine.h"


#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


Passerine::Passerine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Passerine)
{

    ui->setupUi(this);

    songPlayer = new SongPlayer();
    widthCoef = 200;

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    group = new NoteGroup();
    group->setWidthCoef(widthCoef);
    pianoTimer = new QTimer(this);
    connect(pianoTimer, SIGNAL(timeout()), this, SLOT(updateGraphics()));

    ui->volumeSlider->setValue(75);
    songPlayer->setVolume(75);

    ui->playPauseButton->setText("\u25B6");
    ui->stopButton->setText("\u23F9");

    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    drawPiano();


    // RtMidiOut constructor
    try
    {
      midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error )
    {
      qDebug() << "Failed to create rtMidiOut!!!: ";
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    // Call function to select port.
    try
    {
      if ( chooseMidiPort( midiout ) == false )
      {
          qDebug() << "Failed to connect to port: ";
          delete midiout;
          return;
      }
    }
    catch ( RtMidiError &error )
    {
      error.printMessage();
      qDebug() << "Exception: ";
      delete midiout;
    }

    lastNoteAdded = 0;
    lastNoteRemoved = 0;
}

// Promena velicine nota prilikom promene velicine prozora
void Passerine::ResizeNotes(int _startNote, int _endNote)
{
    float height = scene->height()/countNumberOfWhiteNotesInRange(_startNote, _endNote);
    std::vector<Note *> n = songPlayer->getNotes();
    float width;

    for(unsigned i = 0; i < n.size(); i++)
    {
        width = (n[i]->getTimeEnd() - n[i]->getTimeBegin()) * (float)widthCoef;
        if(isWhiteNote(n[i]->getId()))
        {
            n[i]->setRect(n[i]->getRect().x(), countNumberOfWhiteNotesInRange(0, n[i]->getId()-12)*height, width, whiteNoteHeight());
        }
        else
        {
            n[i]->setRect(n[i]->getRect().x(), countNumberOfWhiteNotesInRange(0, n[i]->getId()-12) * height -  (height/1.5)/2, width, blackNoteHeight());
        }
        group->setRect(QRect(0, 0, songPlayer->getSong()->getTotalTimeInSeconds()*widthCoef + 5*scene->width()/6, ui->graphicsView->scene()->height()));
        group->setSceneWidth(scene->width());
    }
    updateGraphics();
}

// Promena velicine dirki prilikom promene velicine prozora
void Passerine::ResizePiano(int _startNote, int _endNote)
{
    startNote = _startNote;
    endNote = _endNote;
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height() - 5);

    whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

    float y = 0;
    float x, width, height;
    width = scene->width()/6;

    group->setStartX(width);
    group->setPianoTopKey(startNote);
    group->setPianoBottomKey(endNote);
    group->setNumOfWhiteNotes(whiteNotesInRange);

    for(unsigned j = 0; j < pianoKeys.size(); j++)
    {
        int i = (j % 12);
        x = 0;
        height = scene->height() / whiteNotesInRange;

        if(!isWhiteNote(i)) // Black Key
        {
            height /= 1.5;
            x+=(width*4/7);
            pianoKeys[j]->setRect(x, y - height/2, width*3/7, height);
        }
        else // White Key
        {
            pianoKeys[j]->setRect(x, y, width, height);

            y += height;
        }
        pianoKeys[j]->setOutputPort(midiout);
    }
    scene->update();
}

// Iscrtavanje dirki na klaviru
void Passerine::drawPiano(int _startNote, int _endNote)
{
    startNote = _startNote;
    endNote = _endNote;

    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height() - 51);

    whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

    float y = 0;
    scene->clear();

    float x, width, height;
    width = scene->width()/6;

    for(int j = startNote; j < endNote; j++)
    {
        Key *key;

        int i = (j % 12);
        height = scene->height() / whiteNotesInRange;
        qDebug() << "Passerine.cpp height: " << height;
        x = 0;
        if(!isWhiteNote(i)) // Black Key
        {
            height /= 1.5;
            x+=(width*4/7);

            key = new Key(j, QRect(x, y - height/2, width*3/7, height));
            key->setZValue(2);
            scene->addItem(key);

        }
        else // White Key
        {
            key = new Key(j, QRect(x, y, width, height));

            scene->addItem(key);
            key->setZValue(1);

            y += height;
        }
        pianoKeys.push_back(key);
        key->setMidiID(j+12);
    }
}

void Passerine::makeNoteGroup()
{
    allNotesSortedByBeginTime = songPlayer->getNotes();

    float height = scene->height() / whiteNotesInRange;
    float width;
    group->setPlayerRef(songPlayer);
    for(unsigned i = 0; i < allNotesSortedByBeginTime.size(); i++){
        width = (allNotesSortedByBeginTime[i]->getTimeEnd() - allNotesSortedByBeginTime[i]->getTimeBegin()) * (float)widthCoef;
        if(isWhiteNote(allNotesSortedByBeginTime[i]->getId()))
        {
            allNotesSortedByBeginTime[i]->setRect(allNotesSortedByBeginTime[i]->getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, allNotesSortedByBeginTime[i]->getId()-12)*height, width, whiteNoteHeight());
        }
        else
        {
            allNotesSortedByBeginTime[i]->setRect(allNotesSortedByBeginTime[i]->getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, allNotesSortedByBeginTime[i]->getId()-12) * height -  (height/1.5)/2, width, blackNoteHeight());
        }
    }

    allNotesSortedByEndTime = allNotesSortedByBeginTime;

    std::sort(allNotesSortedByBeginTime.begin(), allNotesSortedByBeginTime.end(), [](Note *a, Note *b)
    {
        if(a->getTimeBegin() < b->getTimeBegin())
            return true;
        else
            return false;
    });

    std::sort(allNotesSortedByEndTime.begin(), allNotesSortedByEndTime.end(), [](Note *a, Note *b)
    {
        if(a->getTimeEnd() < b->getTimeEnd())
            return true;
        else
            return false;
    });
}

int Passerine::countNumberOfWhiteNotesInRange(int _startNote, int _endNote)
{
    int _whiteNotesInRange = 0;
    for(int i = _startNote; i < _endNote; i++)
    {
        int note = i % 12;
        if(isWhiteNote(note))
            _whiteNotesInRange++;
    }
    return _whiteNotesInRange;
}

void Passerine::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   ResizePiano();
   ResizeNotes();
   updateGraphics();
}

Passerine::~Passerine()
{
    delete scene;
    delete songPlayer;
    delete group;
    delete pianoTimer;
    delete midiout;
    delete ui;
}

void Passerine::on_actionClose_triggered()
{
    QApplication::quit();
}

void Passerine::on_actionAbout_Passerine_triggered()
{
    QWidget *a = new QWidget();
    QString *s = new QString("A simple MIDI file composer.\n\n"
                             "\nFaculty of Mathematics, University of Belgrade "
                             "2017\n");

    QMessageBox::about(a, tr("About Passerine"), *s);

}

void Passerine::on_actionAbout_Qt_triggered()
{
    QWidget *a = new QWidget();

    QMessageBox::aboutQt(a, tr("About Qt"));
}
// Otvara fajl, i pesmu, enableuje GUI i prikaze note
void Passerine::on_actionOpen_triggered()
{
    if(songPlayer != nullptr){
        songPlayer->killSound();
        songPlayer->stop();
    }

    QString filename = QFileDialog::getOpenFileName(
                this,
                "Open Midi File",
                "",
                tr("MIDI (*.mid);;All files (*.*)" )
        );

    int n = midifile.read(filename.toUtf8().constData());

    if(n == 0)
    {
        qDebug() << "Neuspesno citanje fajla";
        return;
    }

    enabledGUI(true);
    qDebug() << "Time: " << midifile.getTotalTimeInSeconds();

    ui->songSlider->setMaximum(midifile.getTotalTimeInSeconds());

    if(songPlayer == nullptr)
    {
        songPlayer = new SongPlayer(&midifile, 0, 60, midiout);
    }
    else
    {
        songPlayer->setSong(&midifile);
        songPlayer->setCurrentTime(0);
        songPlayer->setPort(midiout);
    }


    enabledGUI(true);
    noteGraphicsInit();

    on_stopButton_clicked();
}

// biramo output port
bool Passerine::chooseMidiPort( RtMidiOut *rtmidi )
{
  std::string portName;
  unsigned int nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 )
  {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }
  PortSelector *PS = new PortSelector(NULL, rtmidi);
  PS->exec();
  qDebug() << PS->selectedPort;

  if(PS->selectedPort != -1)
      std::cout << "\nPrihvacen ";
  else
  {
      delete PS;
      return false;
  }
  std::cout << "\nOpening " << rtmidi->getPortName(PS->selectedPort) << std::endl;
  qDebug() << "Selected Port: " << QString::fromStdString(rtmidi->getPortName(PS->selectedPort));
  rtmidi->openPort(PS->selectedPort);

  delete PS;
  return true;
}

void Passerine::noteGraphicsInit()
{
    for(unsigned i = 0; i < allNotesSortedByBeginTime.size(); i++)
        delete allNotesSortedByBeginTime[i];

    allNotesSortedByBeginTime.clear();
    allNotesSortedByEndTime.clear();
    resetPiano();

    makeNoteGroup();
    updateNoteGroup();

    scene->addItem(group);
    group->setPos(scene->width()/6, group->pos().y());
    group->setRect(QRect(0, 0, songPlayer->getSong()->getTotalTimeInSeconds()*widthCoef + 5*scene->width()/6, ui->graphicsView->scene()->height()));
    group->setSceneWidth(scene->width());
}

bool Passerine::isWhiteNote(int i)
{
    int note = i % 12;
    if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
        return true;
    return false;
}

void Passerine::on_playPauseButton_clicked()
{
     if(songPlayer->getSong() != nullptr)
     {
        if(songPlayer->isPlaying() == false)
        {
            songPlayer->setPlaying(true);
            songPlayer->PlaySong(songPlayer->getCurrentTime());

            pianoTimer->start();
            ui->playPauseButton->setText("\u2016\u2016");
            ui->songSlider->setDisabled(true);
         }
        else
        {
            songPlayer->setPlaying(false);
            ui->playPauseButton->setText("\u25B6");
            pianoTimer->stop();
            ui->songSlider->setDisabled(false);

            songPlayer->killSound();
        }
    }
}

void Passerine::on_stopButton_clicked()
{
    if(songPlayer->getSong() == nullptr)
        return;

    if(songPlayer->isPlaying() == true)
    {
        songPlayer->setPlaying(false);
        ui->playPauseButton->setText("\u25B6");
        pianoTimer->stop();
        ui->songSlider->setDisabled(false);

        songPlayer->killSound();
    }

    songPlayer->stop();

    for(int i = 0; i < 128; i++)
        songPlayer->setNoteState(i, false);

    allNotesSortedByBeginTime.clear();
    allNotesSortedByEndTime.clear();

    makeNoteGroup();
    updateNoteGroup();

    updateGraphics();
}

void Passerine::pianoKeyPress()
{
    if(ui->graphicsView->viewport())
    {
        for(unsigned i = 0; i < pianoKeys.size(); i++)
        {
            if(songPlayer->getNoteState(i) == true)
               pianoKeys[i]->pressKey();
            else
               pianoKeys[i]->releaseKey();
        }
    }
}

void Passerine::updateGraphics()
{
    currentTime = chrono::duration_cast< chrono::microseconds >(
                chrono::system_clock::now().time_since_epoch()
            );
    chrono::microseconds difference = (currentTime - previousTime);
//    qDebug() << difference.count();
    previousTime = chrono::duration_cast< chrono::microseconds >(
                chrono::system_clock::now().time_since_epoch()
            );

    updateLastNotes();
    updateNoteGroup();

    if(songPlayer!= nullptr)
    {
        ui->tbLyrics->setText(songPlayer->getLyrics());
        ui->songSlider->setValue(songPlayer->getCurrentTime());
    }

    pianoKeyPress();
    group->setX(scene->width()/6 - songPlayer->getCurrentTime()*widthCoef);
}

double Passerine::whiteNoteHeight()
{
    return scene->height() / countNumberOfWhiteNotesInRange();
}

double Passerine::blackNoteHeight()
{
    return whiteNoteHeight() / 1.5;
}

void Passerine::on_songSlider_sliderMoved(int position)
{
    songPlayer->setCurrentTime(position);
    updateGraphics();
}

void Passerine::resetPiano()
{
    for(unsigned i = 0; i < pianoKeys.size(); i++){
        pianoKeys[i]->releaseKey();
        songPlayer->setNoteState(i, false);
    }
}

void Passerine::enabledGUI(bool value)
{
    ui->playPauseButton->setText("\u25B6");
    ui->playPauseButton->setEnabled(value);
    ui->stopButton->setEnabled(value);
    ui->songSlider->setValue(0);
    ui->songSlider->setEnabled(value);
    ui->volumeSlider->setEnabled(value);
    ui->tbnoteLength->setEnabled(value);
}

void Passerine::updateNoteGroup()
{
    float k = scene->width() / widthCoef + 5;

    for(; lastNoteRemoved < allNotesSortedByEndTime.size(); lastNoteRemoved++){
        if(allNotesSortedByEndTime[lastNoteRemoved]->getTimeEnd() >= songPlayer->getCurrentTime())
            break;

        allNotesSortedByEndTime[lastNoteRemoved]->hide();
        allNotesSortedByEndTime[lastNoteRemoved]->setParentItem(nullptr);
    }

    for(; lastNoteAdded < allNotesSortedByBeginTime.size(); lastNoteAdded++){
        if(allNotesSortedByBeginTime[lastNoteAdded]->getTimeBegin() > songPlayer->getCurrentTime() + k)
            break;

        group->addToGroup(allNotesSortedByBeginTime[lastNoteAdded]);
    }

    group->show();
}

void Passerine::on_songSlider_sliderReleased()
{
    resetPiano();
}

void Passerine::on_actionNew_triggered()
{
    MidiFile *m = new MidiFile();

    songPlayer->setSong(m);
    songPlayer->setCurrentTime(0);
    songPlayer->setPort(midiout);
    ui->songSlider->setValue(0);
    enabledGUI(true);
}

void Passerine::on_actionLoadImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Open Midi File",
                "",
                tr("PNG (*.png);;BMP (*.bmp);;JPEG (*.jpg);;All files (*.*)" )
        );
    QImage image(filename);

    picEditor *pe = new picEditor(this, &image);

    pe->setPlayerRef(songPlayer);
    pe->exec();

    ui->songSlider->setMaximum(songPlayer->getSong()->getTotalTimeInSeconds());
    midifile.read("GeneratedMidi.mid");
//    songPlayer->setSong(&midifile);
    songPlayer->setCurrentTime(0);
    songPlayer->setPort(midiout);

    qDebug() << "Izasao " << songPlayer->getSong()->getTotalTimeInSeconds();
//    updateGraphics();
    noteGraphicsInit();
    updateGraphics();

    delete pe;
}

void Passerine::on_actionSave_triggered()
{
    midifile.joinTracks();
    midifile.sortTracks();
    midifile.write(midifile.getFilename());
}

void Passerine::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Midi File"), "",
        tr("MidiFile (*.mid);;All Files (*)"));
    QFile f(filename);
    f.open( QIODevice::WriteOnly );
    midifile.write(filename.toUtf8().constData());
    f.close();

}

void Passerine::updateLastNotes()
{
    auto i = std::find_if(allNotesSortedByBeginTime.begin(), allNotesSortedByBeginTime.end(), [this](Note *a)
    {
        if(a->getTimeBegin() >= songPlayer->getCurrentTime())
            return true;
        else
            return false;
    });

    auto j = std::find_if(allNotesSortedByEndTime.begin(), allNotesSortedByEndTime.end(), [this](Note *a)
    {
        if(a->getTimeEnd() <= songPlayer->getCurrentTime() + scene->width()/widthCoef + 5)
            return true;
        else
            return false;
    });

    lastNoteAdded = i - allNotesSortedByBeginTime.begin();
    lastNoteRemoved = j - allNotesSortedByEndTime.begin();
}


void Passerine::on_volumeSlider_sliderMoved(int position)
{
    songPlayer->setVolumeLoudnessMultiplier(position);
}

void Passerine::on_tbnoteLength_textChanged()
{
    QString num = ui->tbnoteLength->toPlainText();
    bool ok;
    double d = num.toDouble(&ok);
    if(ok)
    {
        group->setNewNoteLength(d);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","text box value must be a float number");
        messageBox.setFixedSize(500,200);
        ui->tbnoteLength->setText("1");
    }
}
