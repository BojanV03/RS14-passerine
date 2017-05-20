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

    group = new QGraphicsItemGroup();

    pianoTimer = new QTimer(this);
    connect(pianoTimer, SIGNAL(timeout()), this, SLOT(updateGraphics()));

    ui->playPauseButton->setText("\u25B6");
    ui->stopButton->setText("\u23F9");

    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height()-10);
    drawPiano();
}

void Passerine::ResizeNotes(int _startNote, int _endNote)
{
    float height = scene->height()/countNumberOfWhiteNotesInRange(_startNote, _endNote);
    std::vector<Note*> n = songPlayer->getNotes();
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
    }
    updateGraphics();
}

void Passerine::ResizePiano(int _startNote, int _endNote)
{
    startNote = _startNote;
    endNote = _endNote;
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height()-10);

    whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

    float y = 0;
    float x, width, height;
    width = scene->width()/6;


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
    }
    scene->update();
}

void Passerine::drawPiano(int _startNote, int _endNote)
{
    startNote = _startNote;
    endNote = _endNote;

    scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);

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
    }
}

void Passerine::makeNoteGroup()
{
    std::vector<Note*> n = songPlayer->getNotes();

    float height = scene->height() / whiteNotesInRange;
    float width;

    for(unsigned i = 0; i < n.size(); i++){
        width = (n[i]->getTimeEnd() - n[i]->getTimeBegin()) * (float)widthCoef;
        if(isWhiteNote(n[i]->getId()))
        {
            group->addToGroup(n[i]);
            n[i]->setRect(n[i]->getTimeBegin() * widthCoef + scene->width()/6, countNumberOfWhiteNotesInRange(0, n[i]->getId()-12)*height, width, whiteNoteHeight());
        }
        else
        {
            group->addToGroup(n[i]);
            n[i]->setRect(n[i]->getTimeBegin() * widthCoef + scene->width()/6, countNumberOfWhiteNotesInRange(0, n[i]->getId()-12) * height -  (height/1.5)/2, width, blackNoteHeight());
        }
    }
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
                             "2017");

    QMessageBox::about(a, tr("About Passerine"), *s);

}

void Passerine::on_actionAbout_Qt_triggered()
{
    QWidget *a = new QWidget();

    QMessageBox::aboutQt(a, tr("About Qt"));
}

void Passerine::on_actionOpen_triggered()
{
    if(songPlayer != nullptr){
        songPlayer->stop();
    }

    QString filename = QFileDialog::getOpenFileName(
                this,
                "Open Midi File",
                "",
                tr("MIDI (*.mid);;All files (*.*)" )
        );;

    int n = midifile.read(filename.toUtf8().constData());

    if(n == 0)
    {
        qDebug() << "Neuspesno citanje fajla";
        return;
    }

    qDebug() << "Time: " << midifile.getTotalTimeInSeconds();

    ui->songSlider->setMaximum(midifile.getTotalTimeInSeconds());
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
    ui->playPauseButton->setText("\u25B6");
    ui->playPauseButton->setEnabled(true);
    ui->stopButton->setEnabled("true");
    ui->songSlider->setValue(0);
    ui->songSlider->setDisabled(true);

    noteGraphicsInit();

    return;
}

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
      return false;

  std::cout << "\nOpening " << rtmidi->getPortName(PS->selectedPort) << std::endl;
  qDebug() << "Selected Port: " << QString::fromStdString(rtmidi->getPortName(PS->selectedPort));
  rtmidi->openPort(PS->selectedPort);

  return true;
}

void Passerine::noteGraphicsInit()
{
    makeNoteGroup();
    scene->addItem(group);
    group->setPos(scene->width()/6, group->pos().y());

    group->show();
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
            ui->playPauseButton->setText("\u2016");
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

    ui->songSlider->setValue(songPlayer->getCurrentTime());
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
}
