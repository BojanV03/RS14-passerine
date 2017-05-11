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

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    graphicsTimer = new QTimer(this);
    connect(graphicsTimer, SIGNAL(timeout()), this, SLOT(updateGraphics()));

    ui->playPauseButton->setText("\u25B6");
    ui->stopButton->setText("\u23F9");


    drawPiano();
}

void Passerine::drawPiano(int _startNote, int _endNote)
{
    startNote = _startNote;
    endNote = _endNote;

    scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);

    whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

    float y = 0;//TEMP!!!
    scene->clear();

 //   qDebug() << numberOfWhiteNotesInRange;

    float x, width, height;
    width = scene->width()/6;

    QBrush brBlack(Qt::black);
    QBrush brWhite(Qt::white);
    QBrush brGray(Qt::gray);

//    int q = 0;
//    for(auto i = noteStates.cbegin(); i != noteStates.cend(); i++, q++)
//    {
//        qDebug() << q << " is now " << *i;
//    }
    for(int j = startNote; j < endNote; j++)
    {
        int i = (j % 12);
        height = scene->height() / whiteNotesInRange;
        x = 0;
        if(!isWhiteNote(i)) // Black Key
        {
            QPen pen(Qt::black);
            pen.setWidth(0);
            height /= 1.5;
            x+=(width*4/7);
            if(songPlayer->getNoteState(j) == true)
            {
                scene->addRect(x, y - height/2, width*3/7, height, pen, brGray)->setZValue(10);
//                scene->addRect(x + width*3/7, y-height/2, height, height, QPen(Qt::black), QBrush(QPixmap("slika.jpg").scaled(height, height, Qt::IgnoreAspectRatio)))->setZValue(100);
            }
            else
                scene->addRect(x, y - height/2, width*3/7, height, pen, brBlack)->setZValue(10);
        }
        else // White Key
        {
            if(songPlayer->getNoteState(j) == true)
            {
                scene->addRect(x, y, width, height, QPen(Qt::black), brGray)->setZValue(0);
//                scene->addRect(x + width, y-height/2, height, height, QPen(Qt::black), QBrush(QPixmap("slika.jpg").scaled(height, height, Qt::IgnoreAspectRatio)))->setZValue(100);
//                qDebug() << j << " is now " << (noteStates[j] ? "Gray" : "White");
            }
            else
            {
                scene->addRect(x, y, width, height, QPen(Qt::black), brWhite)->setZValue(0);
//                qDebug() << j << " is now " << (noteStates[j] ? "Gray" : "White");
            }
            y += height;
        }
    }
}

void Passerine::drawNotes()
{
    qDebug() << "DrawingNotes" << songPlayer->getNotes().size();

    float noteViewDistance = 10; // in seconds
    for(int i = 0; i < songPlayer->getNotes().size(); i++)
    {
        Note tempNote = songPlayer->getNotes()[i];
        if(tempNote.getTimeEnd() < songPlayer->getCurrentTime())
        {
            continue;
        }
        else if(tempNote.getTimeBegin() > songPlayer->getCurrentTime() + 10)
        {
            break;
        }
        else
        {
            float height = scene->height() / whiteNotesInRange;
            float keyboardWidth = scene->width() / 6;
            float pixelsPerSecond = scene->width() - keyboardWidth; // cela scena - sirina nota
            pixelsPerSecond /= noteViewDistance;                                  // podeljeno sa 10 sekundi koliko je vidljivo na ekranu

            float noteStartPixel = tempNote.getTimeBegin() - songPlayer->getCurrentTime();
            noteStartPixel *= pixelsPerSecond;
            noteStartPixel = noteStartPixel > 0? noteStartPixel : 0;
            noteStartPixel += keyboardWidth;

            float noteEndPixel = tempNote.getTimeEnd() - songPlayer->getCurrentTime();
            noteEndPixel *= pixelsPerSecond;
            noteEndPixel = noteEndPixel < (noteViewDistance*pixelsPerSecond) ? noteEndPixel : (noteViewDistance*pixelsPerSecond);
            noteEndPixel += keyboardWidth;


            if(isWhiteNote(tempNote.getId()))
            {
                qDebug() << "Drawn a white note " << tempNote.getId();
                scene->addRect(noteStartPixel, countNumberOfWhiteNotesInRange(startNote, tempNote.getId()-12)*height, noteEndPixel-noteStartPixel, height, QPen(Qt::red), QBrush(Qt::black));
            }
            else
            {
                qDebug() << "Drawn a black note " << tempNote.getId();
               scene->addRect(noteStartPixel, countNumberOfWhiteNotesInRange(startNote, tempNote.getId()-12)*height - (height/1.5)/2, noteEndPixel-noteStartPixel, height/1.5, QPen(Qt::red), QBrush(Qt::black));
            }
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

   drawPiano();
   drawNotes();
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
        songPlayer->setPlaying(false);
    }

    QString filename = QFileDialog::getOpenFileName(
                this,
                "Open Midi File",
                "",
                tr("MIDI (*.mid);;All files (*.*)" )
        );;

    int n = midifile.read(filename.toUtf8().constData());

    if(n == 0){
        qDebug() << "Neuspesno citanje fajla";
        return;
    }
    qDebug() << "Time: " << midifile.getTotalTimeInSeconds();

    ui->songProgressBar->setMaximum(midifile.getTotalTimeInSeconds());
    // RtMidiOut constructor
    try {
      midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
      qDebug() << "Failed to create rtMidiOut!!!: ";
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    // Call function to select port.
    try {
      if ( chooseMidiPort( midiout ) == false ){
          qDebug() << "Failed to port: ";
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

    songPlayer = new SongPlayer(&midifile, 0, 60, midiout);

    ui->playPauseButton->setText("\u25B6");
    ui->playPauseButton->setEnabled(true);
    ui->stopButton->setEnabled("true");

    return;
}

bool Passerine::chooseMidiPort( RtMidiOut *rtmidi )
{
  std::string portName;
  unsigned int nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
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

bool Passerine::isWhiteNote(int i)
{
    int note = i % 12;
    if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
        return true;
    return false;
}

void Passerine::on_playPauseButton_clicked()
{
     if(songPlayer->getSong() != nullptr){
        if(songPlayer->isPlaying() == false){
            songPlayer->setPlaying(true);
            qDebug() << "Playing";
            qDebug() << "Playing from: " << songPlayer->getCurrentTime();
            songPlayer->PlaySong(songPlayer->getCurrentTime());

            ui->playPauseButton->setText("\u2016");
            graphicsTimer->start(33);
        }
        else{
            songPlayer->setPlaying(false);
            qDebug() << "Stopping";
            ui->playPauseButton->setText("\u25B6");
            graphicsTimer->stop();
        }
    }
}

void Passerine::on_stopButton_clicked()
{
    if(songPlayer->getSong() == nullptr)
        return;

    if(songPlayer->isPlaying()){
        songPlayer->setPlaying(false);
        qDebug() << "Stopping";
        ui->playPauseButton->setText("\u25B6");
        graphicsTimer->stop();
    }

    qDebug() << "Set time to: " << songPlayer->getCurrentTime();
    songPlayer->setCurrentTime(0);

    for(int i = 0; i < 128; i++)
        songPlayer->setNoteState(i, false);

    updateGraphics();
}

void Passerine::updateGraphics()
{
    drawPiano();
    ui->songProgressBar->setValue(songPlayer->getCurrentTime());
    drawNotes();
}

// \u23F9 stop znak

void Passerine::on_songProgressBar_valueChanged(int value)
{

}
