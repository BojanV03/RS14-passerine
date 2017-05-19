#include <include/SongPlayer.h>
#include <include/note.h>
#include <QTimer>
#include <QDebug>
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

SongPlayer::SongPlayer(MidiFile *_song, int _instrument, int _tempo, RtMidiOut *_outputPort) :
    song(_song),
    instrument(_instrument),
    tempo(_tempo),
    outputPort(_outputPort),
    noteStates(128, false)
{

    playing = false;

    if(_song != nullptr)
    {
        _song->joinTracks();
        _song->sortTracks();
        int numEvent;
        numEvent = _song->getEventCount(0);

        for(unsigned i = 0; i< numEvent; i++)
        {
            double end;

            MidiEvent event = _song->getEvent(0,i);
            if(event.isNoteOn())
            {
                for(unsigned j = i; j< numEvent; j++)
                {
                    if(_song->getEvent(0,j).isNoteOff() && event[1] == _song->getEvent(0,j)[1])
                    {
                        end = _song->getEvent(0,j).seconds;
                        break;

                    }
                }
   //             std::cout<<event[1]<<" "<<event.seconds<<" "<< end <<endl;
                Note *n = new Note(event[1], event.seconds, end);

                notes.push_back(n);
            }

        }
        qDebug() << "Number of notes" << notes.size();


    }
}

void SongPlayer::PlaySong(float startTime, float endTime)
{
    setPlaying(true);
    std::thread t1 (SongPlayer::playSongWrapper, this, startTime, endTime);
    t1.detach();
    return;
}

float SongPlayer::getCurrentTime() const
{
    return currentTime;
}

void SongPlayer::setCurrentTime(float value)
{
    currentTime = value;
}

void SongPlayer::playSongWrapper(SongPlayer* player, float startTime, float endTime)
{
    player->PlaySongInNewThread(startTime, endTime);
}

void SongPlayer::PlaySongInNewThread(float startTime, float endTime)
{
    std::vector<unsigned char> message;

    song->joinTracks();
    song->sortTracks();

    // Program change: 192, 5
    message.push_back( 0xC0 );  //Channel 1 instrument
    message.push_back( instrument );
    //qDebug() << "Sent: " << message;
    outputPort->sendMessage( &message );

    message[0] = 0xC1;          //Channel 2 instrument
    message[1] = instrument;
    //qDebug() << "Sent: " << message;
    outputPort->sendMessage( &message );

    qDebug() << "Number of tracks: " << song->getNumTracks();
    qDebug() << "EventCount: " << song->getEventCount(0);

    message[0] = 0xF1;  //System common- undefined?
    message[1] = 60;
    outputPort->sendMessage( &message );

    // Control Change: 176, 7, 100 (volume)
    message[0] = 0xB0;       //set volume to 100
    message[1] = 7;
    message.push_back( 100 );
    message[0] = 0xB1;       //set volume to 100
    message[1] = 7;
    message[2] = 100;
    outputPort->sendMessage( &message );

    double prevSeconds = startTime;
    for(int currentEvent = 0; isPlaying() && currentEvent < song->getEventCount(0); currentEvent++)
    {
   //     qDebug() << currentEvent;
        MidiEvent curr = song->getEvent(0, currentEvent);
        currentTime = prevSeconds;
        if(curr.seconds < startTime)
        {
            continue;
        }
        else if(curr.seconds > endTime)
        {
            playing = false;
            break;
        }
        if(curr.isNoteOn() || curr.isNoteOff())
        {
            message[0] = curr[0];
            message[1] = curr[1];
            message[2] = curr[2];
            while(currentTime < curr.seconds -0.016)
            {
                currentTime += 0.016;
                usleep(0.016*1000000);
            }
    //        usleep((curr.seconds - prevSeconds)*1000000);
            outputPort->sendMessage( &message);

            noteChanged(curr);

//            if(curr.isNoteOn())
//                qDebug() << "NoteOn: " << message[0] << message[1] << message[2];
            prevSeconds = curr.seconds;

        }
        else if(curr.isMeta() && curr[1] == 5)
        {
            while(currentTime < curr.seconds -0.016)
            {
                currentTime += 0.016;
                usleep(0.016*1000000);
            }
            QString S;
            for(int j = 0; j < curr[2]; j++)
            {
                lyrics.append(curr[3+j]);
            }
 //           qDebug() << S;
            prevSeconds = curr.seconds;
        }
        else
        {
            message[0] = curr[0];
            message[1] = curr[1];
            message[2] = curr[2];
            while(currentTime < curr.seconds -0.016)
            {
                currentTime += 0.016;
                usleep(0.016*1000000);
            }
            outputPort->sendMessage( &message);
            prevSeconds = curr.seconds;
        }
    }

    // Control Change: 176, 7, 40
    message[0] = 176;
    message[1] = 7;
    message[2] = 100;
    outputPort->sendMessage( &message );

    SLEEP( 500 );

    // Sysex: 240, 67, 4, 3, 2, 247
    message[0] = 240;
    message[1] = 67;
    message[2] = 4;
    message.push_back( 3 );
    message.push_back( 2 );
    message.push_back( 247 );
    outputPort->sendMessage( &message );
}

void SongPlayer::noteChanged(MidiEvent &m)
{
    if(m.isNoteOn())
    {
        noteStates[m[1]-12] = true;// -12 because the first key on our keyboard is the 12th key in the midi standard
//        qDebug() << m[1]-12 << "is now " << noteStates[m[1]-12];
    }
    else if(m.isNoteOff())
    {
        noteStates[m[1]-12] = false;
//        qDebug() << m[1]-12 << "is now " << noteStates[m[1]-12];
    }
}
std::vector<Note*> SongPlayer::getNotes() const
{
    return notes;
}

void SongPlayer::setNotes(const std::vector<Note> &value)
{
//    notes = value;
}

QString SongPlayer::getLyrics() const
{
    return lyrics;
}

MidiFile* SongPlayer::getSong() const
{
    return song;
}
int SongPlayer::getInstrument() const
{
    return instrument;
}
int SongPlayer::getTempo() const
{
    return tempo;
}
RtMidi* SongPlayer::getPort() const
{
    return outputPort;
}

bool SongPlayer::getNoteState(int pos) const
{
    return noteStates[pos];
}

bool SongPlayer::isPlaying() const
{
    return playing;
}

void SongPlayer::setSong(MidiFile *_song)
{
    song = _song;
}
void SongPlayer::setInstrument(int _instrument)
{
    instrument = _instrument;
}
void SongPlayer::setTempo(int _tempo)
{
    tempo = _tempo;
}
void SongPlayer::setPort(RtMidiOut* _outputPort)
{
    outputPort = _outputPort;
}

void SongPlayer::setPlaying(bool _playing)
{
    playing = _playing;
}

void SongPlayer::setNoteState(int pos, bool state)
{
    noteStates[pos] = state;
}
