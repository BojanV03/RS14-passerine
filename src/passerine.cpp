#include "include/passerine.h"
#include "ui_passerine.h"
#include <QApplication>
#include <QDialog>
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <include/Binasc.h>
#include <include/MidiEvent.h>
#include <include/MidiEventList.h>
#include <include/MidiFile.h>
#include <include/MidiMessage.h>
#include <include/Options.h>
#include <include/RtMidi.h>
#include <include/portselector.h>

#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

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
    MidiFile midifile;

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

    RtMidiOut *midiout = 0;
    std::vector<unsigned char> message;

    // RtMidiOut constructor
    try {
      qDebug() << "Creating output: ";
      midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
      qDebug() << "NEUSPEH!!!: ";
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    qDebug() << "Successfully created the output: ";
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

    midifile.joinTracks();
    midifile.sortTracks();
    qDebug() << "Number of tracks: " << midifile.getNumTracks();

    qDebug() << "EventCount: " << midifile.getEventCount(0);
    // Program change: 192, 5
    message.push_back( 192 );
    message.push_back( 7 );
    midiout->sendMessage( &message );

    SLEEP( 500 );

    message[0] = 0xF1;
    message[1] = 60;
    midiout->sendMessage( &message );

    // Control Change: 176, 7, 100 (volume)
    message[0] = 176;
    message[1] = 7;
    message.push_back( 100 );
    midiout->sendMessage( &message );

    double prevSeconds = 0;
    for(int i = 0; i < midifile.getEventCount(0); i++)
    {
        MidiEvent curr = midifile.getEvent(0, i);
        if(curr.isNoteOn() || curr.isNoteOff())
        {
            message[0] = curr[0];
            message[1] = curr[1];
            message[2] = curr[2];

            usleep((curr.seconds - prevSeconds)*1000000);
            midiout->sendMessage( &message);
            if(curr.isNoteOn())
                qDebug() << "NoteOn: " << message[1];
            prevSeconds = curr.seconds;
        }
    }

    // Control Change: 176, 7, 40
    message[0] = 176;
    message[1] = 7;
    message[2] = 100;
    midiout->sendMessage( &message );

    SLEEP( 500 );

    // Sysex: 240, 67, 4, 3, 2, 247
    message[0] = 240;
    message[1] = 67;
    message[2] = 4;
    message.push_back( 3 );
    message.push_back( 2 );
    message.push_back( 247 );
    midiout->sendMessage( &message );
    // Clean up
    delete midiout;
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

  std::cout << "\n";
  qDebug() << "Selected Port: " << QString::fromStdString(rtmidi->getPortName(PS->selectedPort));
  rtmidi->openPort(PS->selectedPort);

  return true;
}
