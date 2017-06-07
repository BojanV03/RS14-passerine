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
    noteStates(128, false),
    volumeCh(16, 100)
{
    playing = false;

    setSong(_song);
}

void SongPlayer::PlaySong(float startTime, float endTime)
{
    setPlaying(true);
    stopped = false;
    playThread = std::thread(SongPlayer::playSongWrapper, this, startTime, endTime);
    playThread.detach();
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

int SongPlayer::getVolumeLoudnessMultiplier() const
{
    return volumeLoudnessMultiplier;
}

void SongPlayer::setVolumeLoudnessMultiplier(int value)
{
    volumeLoudnessMultiplier = value;

    setSongVolumeOnAllChannels();
}

void SongPlayer::removeNote(Note *me)
{
    int ind = 0;
    for(auto i = notes.begin(); i != notes.end(); i++)
    {
        i++;
        if(*i == me)
        {
            notes.erase(notes.begin() + ind);
        }
    }

}
std::vector<char> SongPlayer::getVolumeCh() const
{
    return volumeCh;
}

void SongPlayer::setVolumeCh(unsigned channel, unsigned char value)
{
    if(channel > volumeCh.size())
        return;

    volumeCh[channel] = value;
}

void SongPlayer::resetVolumeCh()
{
    for(auto i = volumeCh.begin(); i != volumeCh.end(); i++)
    {
        *i = 100;
    }
}

void SongPlayer::setSongVolumeOnAllChannels()
{
    std::vector<unsigned char> message(3);

    for(unsigned char i = 0; i < 16; i++)
    {
        message[0] = 0xB0+i;
        message[1] = 0x07;
        message[2] = (unsigned char) ((volumeCh[i] * (volumeLoudnessMultiplier/100.0)) < 128 ? (volumeCh[i] * (volumeLoudnessMultiplier/100.0)) : 127);
        qDebug() << "Channel " << i << " volume is now: " << message[2];
        outputPort->sendMessage(&message);
    }
}

int SongPlayer::getVolume() const
{
    return volume;
}

void SongPlayer::setVolume(int value)
{
    volume = value;
}


void SongPlayer::playSongWrapper(SongPlayer* player, float startTime, float endTime)
{
    player->PlaySongInNewThread(startTime, endTime);
}

void SongPlayer::PlaySongInNewThread(float startTime, float endTime)
{
    std::vector<unsigned char> message;

    qDebug() << "Thread is now running";
    song->joinTracks();
    song->sortTracks();

    // Program change: 192, 5
    message.push_back( 0xC0 );  //Channel 1 instrument
    message.push_back( instrument );
    //qDebug() << "Sent: " << message;
//    outputPort->sendMessage( &message );

    message[0] = 0xC1;          //Channel 2 instrument
    message[1] = instrument;
    //qDebug() << "Sent: " << message;
//    outputPort->sendMessage( &message );

//    qDebug() << "Number of tracks: " << song->getNumTracks();
//    qDebug() << "EventCount: " << song->getEventCount(0);

    message[0] = 0xF1;  // System common- undefined?
    message[1] = 60;
    outputPort->sendMessage( &message );

    // Control Change: 176, 7, 100 (volume)
    setSongVolumeOnAllChannels();

    message[0] = 0xBF;
    message[1] = 0x07;
    message.push_back(100);
    outputPort->sendMessage(&message);
    message[0] = 0xB1;
    outputPort->sendMessage(&message);

    double prevSeconds = startTime;
    for(int currentEvent = 0; isPlaying() && currentEvent < song->getEventCount(0); currentEvent++)
    {
        if(stopped)
            break;
        MidiEvent curr = song->getEvent(0, currentEvent);
        message.resize(curr.size());


        // Update instruments
        if(curr[0] >= 0xC0 && curr[0] <= 0xCF)
        {
            message[0] = curr[0];
            message[1] = curr[1];
            outputPort->sendMessage(&message);
        }

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
        // Volume Change control
        if(curr[0] >= 0xB0 && curr[0] <= 0xBF && (curr[1] == 0x07 || curr[1] == 0x27))
        {
            qDebug() << "Volume changed for channel" << curr[0] - 0xB0 << " to the value of " << curr[2];
            volumeCh[curr.getChannel()] = curr[2];
        }
        if(curr.isNoteOn() || curr.isNoteOff())
        {
            message[0] = curr[0];
            message[1] = curr[1];
            message[2] = curr[2];
            while(currentTime < curr.seconds - 0.001)
            {
                if(!playing || stopped)
                    return;
                currentTime += 0.001;
                usleep(0.001*1000000);
            }
            outputPort->sendMessage( &message);
            noteChanged(curr);
            prevSeconds = curr.seconds;
         //   if(curr.isNoteOff())
         //   qDebug() << curr.seconds;

        }
        else if(curr.isMeta() && curr[1] == 5)
        {
            while(currentTime < curr.seconds -0.016)
            {
                if(!playing || stopped)
                    return;
                currentTime += 0.016;
                usleep(0.016*1000000);
            }
            QString S;
            for(int j = 0; j < curr[2]; j++)
            {
                lyrics.append(curr[3+j]);
            }
            prevSeconds = curr.seconds;
        }
        else
        {
            message[0] = curr[0];
            message[1] = curr[1];
            message[2] = curr[2];
            while(currentTime < curr.seconds -0.016)
            {
                if(!playing || stopped)
                    return;
                currentTime += 0.016;
                usleep(0.016*1000000);
            }
            outputPort->sendMessage( &curr);
            prevSeconds = curr.seconds;
        }
    }

    // Control Change: 176, 7, 40
    message[0] = 176;
    message[1] = 7;
    message[2] = 100;
    outputPort->sendMessage( &message );

//    SLEEP( 500 );

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
std::vector<Note *> SongPlayer::getNotes() const
{
    return notes;
}

void SongPlayer::setNotes(const std::vector<Note> &)
{
//    notes = value;
}

QString SongPlayer::getLyrics() const
{
    return lyrics;
}

void SongPlayer::killSound()
{
    if(currentTime == 0)
        return;

    for(int i = 0; i < 16; i++)
    {
        std::vector<unsigned char> v;
        v.push_back(0xB0+i);
        v.push_back(0x7B);
        v.push_back(0x00);
        outputPort->sendMessage(&v);
    }
}

bool SongPlayer::getStopped() const
{
    return stopped;
}

void SongPlayer::setStopped(bool value)
{
    stopped = value;
}

void SongPlayer::stop()
{
    playing = false;
    currentTime = 0;
    stopped = true;
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
    clearNotes();

    for(unsigned i = 0; i<16; i++)
        volumeCh.push_back(100);

    if(_song != nullptr)
    {
        song = _song;

        song->joinTracks();
        song->sortTracks();
        int numEvent;
        numEvent = song->getEventCount(0);

        for(int i = 0; i< numEvent; i++)
        {
            double end;

            MidiEvent event = song->getEvent(0,i);

            if(event.isNoteOn())
            {
                int j;
                for(j = i; j< numEvent; j++)
                {
                    if(song->getEvent(0,j).isNoteOff() && event[1] == song->getEvent(0,j)[1])
                    {
                        end = song->getEvent(0,j).seconds;
                        break;

                    }
                }
                Note * n(new Note(event[1], event.seconds, end, event.getChannel()));
                n->setOnEvent(&song->getEvent(0, i));
                n->setOffEvent(&song->getEvent(0, j));
                n->setSong(song);
                notes.push_back(n);

            }
        }
        qDebug() << "Number of notes" << notes.size();
    }
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

void SongPlayer::clearNotes()
{
    if(notes.size() != 0)
    {
        notes.erase(notes.begin(), notes.end());
        qDebug() << "Removed notes";
    }
    notes.clear();
    qDebug() << "Left " << notes.size() << " notes";
}

Note * SongPlayer::addNote(int id, float time, float duration)
{
//    qDebug() << "Added note " << id << " starting at: " << time << " seconds and lasting " << duration << " seconds";

    Note * n(new Note(id, time, time + duration));
    qDebug() << "***** " << duration;

    int index = song->addNoteOn(0, song->getAbsoluteTickTime(time), 0, id, 90);
  //  song->getEvent(0, index).tick = song->getAbsoluteTickTime(time);
    n->setOnEvent(&song->getEvent(0, index));
    song->getEvent(0, index).seconds=song->getTimeInSeconds(0, index);

    qDebug() << "start time: " << song->getEvent(0, index).seconds;
    index = song->addNoteOff(0, song->getAbsoluteTickTime(time+duration), 0, id);

  //  song->getEvent(0, index).seconds = time+duration;
  //  song->getEvent(0, index).tick = song->getAbsoluteTickTime(time+duration);
    n->setOffEvent(&song->getEvent(0, index));
    song->getEvent(0, index).seconds=song->getTimeInSeconds(0, index);

    song->sortTracks();
    qDebug() << "Note starting at: " << song->getAbsoluteTickTime(time) << " and ending at " << song->getAbsoluteTickTime(time+duration);
    notes.push_back(n);
    return n;
}


