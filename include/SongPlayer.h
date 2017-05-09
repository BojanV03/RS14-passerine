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

class Passerine;

class SongPlayer
{
public:
    SongPlayer(MidiFile *song = nullptr, int instrument = 0, int tempo = 0, RtMidiOut *outputPort = nullptr, Passerine *main = nullptr);

    MidiFile* getSong()const;
    int getInstrument()const;
    int getTempo()const;
    RtMidi* getPort()const;
    bool isPlaying()const;
    float getCurrentTime() const;

    void setSong(MidiFile*);
    void setInstrument(int);
    void setTempo(int);
    void setPort(RtMidiOut *);
    void setPlaying(bool);
    void setCurrentTime(float value);

    void PlaySong(float startTime = 0, float endTime = FLT_MAX);


private:
    MidiFile *song;
    int instrument, tempo;
    RtMidiOut *outputPort;
    bool playing;
    bool stopped;

    Passerine *main;
    float currentTime = 0;

    static void playSongWrapper(SongPlayer* player, float startTime, float endTime);
    void PlaySongInNewThread(float startTime = 0, float endTime = FLT_MAX);


};

// TODO: UNHACK
#include <include/passerine.h>
#endif // SONGPLAYER_H
