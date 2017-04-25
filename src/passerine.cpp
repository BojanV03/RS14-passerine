#include <include/passerine.h>
#include "ui_passerine.h"


#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

static SongPlayer *songPlayer;
static RtMidiOut *midiout;
static MidiFile midifile;

bool chooseMidiPort( RtMidiOut *rtmidi );

Passerine::Passerine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Passerine)
{
    ui->setupUi(this);
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

    qDebug() << "Uspesno citanje fajla";
    qDebug() << "Time: " << midifile.getTotalTimeInSeconds();

    // RtMidiOut constructor
    try {
      qDebug() << "Creating rtMidiOut: ";
      midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
      qDebug() << "Failed to create rtMidiOut!!!: ";
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    qDebug() << "Successfully created the rtMidiOut: ";
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
    songPlayer->PlaySong();

    return;
}

bool chooseMidiPort( RtMidiOut *rtmidi )
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
