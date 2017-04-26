#include <include/SongPlayer.h>
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
    outputPort(_outputPort)
{
    playing = false;
}

void SongPlayer::PlaySong(float startTime, float endTime)
{
    setPlaying(true);
    std::thread t1 (SongPlayer::playSongWrapper, this, startTime, endTime);
    t1.detach();
    setPlaying(false);
    return;
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
    qDebug() << "Sent: " << message;
    outputPort->sendMessage( &message );

    message[0] = 0xC1;          //Channel 2 instrument
    message[1] = instrument;
    qDebug() << "Sent: " << message;
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

    double prevSeconds = 0;
    for(int i = 0; i < song->getEventCount(0); i++)
    {
        while(playing == false) {}

        MidiEvent curr = song->getEvent(0, i);



        if(curr.seconds < startTime)
        {
            prevSeconds = curr.seconds;
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
            usleep((curr.seconds - prevSeconds)*1000000);
            outputPort->sendMessage( &message);
//            if(curr.isNoteOn())
//                qDebug() << "NoteOn: " << message[0] << message[1] << message[2];
            prevSeconds = curr.seconds;
        }
        else if(curr.isMeta() && curr[1] == 5)
        {
            usleep((curr.seconds - prevSeconds)*1000000);
            QString S;
            for(int j = 0; j < curr[2]; j++)
            {
                S.append(curr[3+j]);
            }
            qDebug() << S;
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

MidiFile* SongPlayer::getSong()
{
    return song;
}
int SongPlayer::getInstrument()
{
    return instrument;
}
int SongPlayer::getTempo()
{
    return tempo;
}
RtMidi* SongPlayer::getPort()
{
    return outputPort;
}

bool SongPlayer::isPlaying()
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
