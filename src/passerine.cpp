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
        widthCoef = 800;

        scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);

        group = new AnimationGroup();

        pianoTimer = new QTimer(this);
        connect(pianoTimer, SIGNAL(timeout()), this, SLOT(updateGraphics()));

        ui->playPauseButton->setText("\u25B6");
        ui->stopButton->setText("\u23F9");

        scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);
        drawPiano();
    }

    void Passerine::ResizePiano(int _startNote, int _endNote)
    {
        startNote = _startNote;
        endNote = _endNote;
        scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);

        whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

        float y = 0;
        float x, width, height;
        width = scene->width()/6;

        QBrush brBlack(Qt::black);
        QBrush brWhite(Qt::white);

     /*   QPainter qp;
        qp.begin(ui->graphicsView);

        for(int j = 0; j < endNote-startNote; j++)
        {
            int i = (j % 12);
            x = 0;
            height = scene->height() / whiteNotesInRange;

            if(!isWhiteNote(i)) // Black Key
            {
                QPen pen(Qt::black);
                pen.setWidth(0);
                height /= 1.5;
                x+=(width*4/7);
                pianoKeys[i]->setRect(x, y - height/2, width*3/7, height);
                qp.fillRect(*pianoKeys[i], Qt::black);
            }
            else // White Key
            {
                pianoKeys[i]->setRect(x, y, width, height);

           //     scene->addRect(*pianoKeys[i], QPen(Qt::black), brWhite)->setZValue(0);
                y += height;
                qp.fillRect(*pianoKeys[i], Qt::white);
            }
        }
        qp.end();*/
        qDebug() << "REPAINTING STUFF";
    }

    void Passerine::drawPiano(int _startNote, int _endNote)
    {
        startNote = _startNote;
        endNote = _endNote;

        scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);

        whiteNotesInRange = countNumberOfWhiteNotesInRange(_startNote, _endNote);

        float y = 0;//TEMP!!!
        scene->clear();

        float x, width, height;
        width = scene->width()/6;

        QBrush brBlack(Qt::black);
        QBrush brWhite(Qt::red);

        for(int j = startNote; j < endNote; j++)
        {
            QRect *key;

            int i = (j % 12);
            height = scene->height() / whiteNotesInRange;
            x = 0;

            if(!isWhiteNote(i)) // Black Key
            {
                QPen pen(Qt::black);
                pen.setWidth(0);
                height /= 1.5;
                x+=(width*4/7);

                key = new QRect(x, y - height/2, width*3/7, height);

                scene->addRect(*key, pen, brBlack)->setZValue(10);
            }
            else // White Key
            {
                key = new QRect(x, y, width, height);

                scene->addRect(*key, QPen(Qt::black), brWhite)->setZValue(0);

                y += height;
            }

            pianoKeys.push_back(key);
        }
    }

    void Passerine::makeNoteGroup()
    {
        std::vector<Note> n = songPlayer->getNotes();

        float height = scene->height() / whiteNotesInRange;
        float width;

        for(unsigned i = 0; i < n.size(); i++){
            width = (n[i].getTimeEnd() - n[i].getTimeBegin()) * (float)widthCoef;
            if(isWhiteNote(n[i].getId())){
      //          qDebug() << "Drawn a white note " << tempNote.getId();
                group->addToGroup(new QGraphicsRectItem(n[i].getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, n[i].getId()-12)*height, width, whiteNoteHeight()));
            }
            else{
      //          qDebug() << "Drawn a black note " << tempNote.getId();
                group->addToGroup(new QGraphicsRectItem(n[i].getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, n[i].getId()-12) * height -  (height/1.5)/2, width, blackNoteHeight()));
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

        noteGraphicsInit();

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

    void Passerine::noteGraphicsInit()
    {
        makeNoteGroup();
        scene->addItem(group);
        group->setPos(group->pos().x() + scene->width()/6, group->pos().y());

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
         if(songPlayer->getSong() != nullptr){
            if(songPlayer->isPlaying() == false){
                songPlayer->setPlaying(true);
                qDebug() << "Playing";
                qDebug() << "Playing from: " << songPlayer->getCurrentTime();
                songPlayer->PlaySong(songPlayer->getCurrentTime());

                pianoTimer->start(33);
                ui->playPauseButton->setText("\u2016");
             }
            else{
                songPlayer->setPlaying(false);
                qDebug() << "Stopping";
                ui->playPauseButton->setText("\u25B6");
                pianoTimer->stop();
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
            pianoTimer->stop();
        }

        qDebug() << "Set time to: " << songPlayer->getCurrentTime();
        songPlayer->setCurrentTime(0);

        for(int i = 0; i < 128; i++)
            songPlayer->setNoteState(i, false);

        updateGraphics();
    }

    void Passerine::pianoKeyPress()
    {
        if(ui->graphicsView->viewport())
        {
            QPainter qp(ui->graphicsView);
            for(unsigned i = 0; i < pianoKeys.size(); i++){

                if(isWhiteNote(i)){
                    if(songPlayer->getNoteState(i) == true)
                       qp.fillRect(*pianoKeys[i], Qt::gray);
                    else
                       qp.fillRect(*pianoKeys[i], Qt::white);
                }
                else{
                    if(songPlayer->getNoteState(i) == true)
                       qp.fillRect(*pianoKeys[i], Qt::gray);
                    else
                       qp.fillRect(*pianoKeys[i], Qt::black);
                }

            }
            qp.end();
        }

    }
    void Passerine::updateGraphics()
    {
        ui->songProgressBar->setValue(songPlayer->getCurrentTime());
        pianoKeyPress();
        ResizePiano();
        group->setPos(scene->width()/6 - songPlayer->getCurrentTime()*widthCoef, group->pos().y());
    }

    double Passerine::whiteNoteHeight()
    {
        return scene->height() / countNumberOfWhiteNotesInRange();
    }

    double Passerine::blackNoteHeight()
    {
        return whiteNoteHeight() / 1.5;
    }


    // \u23F9 stop znak

    //void Passerine::on_songProgressBar_valueChanged(int value)
    //{

    //}
