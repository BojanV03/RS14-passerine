#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include <include/Binasc.h>
#include <include/MidiEvent.h>
#include <include/MidiEventList.h>
#include <include/MidiFile.h>
#include <include/MidiMessage.h>
#include <include/Options.h>
#include <include/RtMidi.h>
#include <thread>
#include <float.h>
#include <include/SongObserver.h>
//#include <include/passerine.h>

class SongPlayer
{
public:
    SongPlayer(MidiFile *song = nullptr, int instrument = 0, int tempo = 0, RtMidiOut *outputPort = nullptr);

    MidiFile* getSong();
    int getInstrument();
    int getTempo();
    RtMidi* getPort();
    bool isPlaying();

    void setSong(MidiFile*);
    void setInstrument(int);
    void setTempo(int);
    void setPort(RtMidiOut *);
    void setPlaying(bool);

    void PlaySong(float startTime = 0, float endTime = FLT_MAX);

private:
    MidiFile *song;
    int instrument, tempo;
    RtMidiOut *outputPort;
    bool playing;

    vector<class SongObserver *> views;

    static void playSongWrapper(SongPlayer* player, float startTime, float endTime);
    void PlaySongInNewThread(float startTime = 0, float endTime = FLT_MAX);
};

#endif // SONGPLAYER_H
