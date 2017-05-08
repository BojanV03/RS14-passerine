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
    songPlayer = nullptr;

    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    drawPiano();
}

void Passerine::drawPiano(int startNote, int endNote)
{
    scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);

    int numberOfWhiteNotesInRange = 0;

    for(int i = startNote; i < endNote; i++)
    {
        int note = i % 12;
        if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
            numberOfWhiteNotesInRange++;
    }
    qDebug() << ui->graphicsView->width() << " " << ui->graphicsView->height();
    float y = 0;//TEMP!!!
    scene->clear();

    qDebug() << numberOfWhiteNotesInRange;

    float x, width, height;
    width = scene->width()/6;

    for(int j = startNote; j < endNote; j++)
    {
        int i = (j % 12);
        height = scene->height() / numberOfWhiteNotesInRange;
        x = 0;
        if(i == 1 || i == 3 || i == 6 || i == 8 || i == 10)
        {
            QPen pen(Qt::black);
            pen.setWidth(0);
            height /= 1.5;
            x+=(width*4/7);
            scene->addRect(x, y - height/2, width*3/7, height, pen, QBrush(Qt::black))->setZValue(10);
        }
        else
        {
            scene->addRect(x, y, width, height, QPen(Qt::black), QBrush(Qt::white))->setZValue(0);
            y += height;
        }
    }
}

void Passerine::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   drawPiano();
}

void Passerine::noteChanged(MidiEvent &m)
{
    qDebug() << "I've been notified of a " << m[1] << "note change. Sincerely, passerine.cpp";
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

    ui->playPauseButton->setText("Play");
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

void Passerine::on_playPauseButton_clicked()
{
     if(songPlayer != nullptr){
        if(songPlayer->isPlaying() == false){
            songPlayer->setPlaying(true);
            qDebug() << "Playing";
            qDebug() << "Playing from: " << songPlayer->getCurrentTime();
            songPlayer->PlaySong(songPlayer->getCurrentTime());
            ui->playPauseButton->setText("Pause");
        }
        else{
            songPlayer->setPlaying(false);
            qDebug() << "Stopping";
            ui->playPauseButton->setText("Play");
        }
    }
}

void Passerine::on_stopButton_clicked()
{
    if(songPlayer != nullptr)
    {
        if(songPlayer->isPlaying())
        {
            songPlayer->setPlaying(false);
            qDebug() << "Stopping";
            ui->playPauseButton->setText("Play");
        }
        qDebug() << "Set time to: " << songPlayer->getCurrentTime();
        songPlayer->setCurrentTime(0);
    }
}
