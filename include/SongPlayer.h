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

class SongPlayer
{
public:
    SongPlayer(MidiFile *song = nullptr, int instrument = 0, int tempo = 0, RtMidiOut *outputPort = nullptr);

    MidiFile* getSong();
    int getInstrument();
    int getTempo();
    RtMidi* getPort();

    void setSong(MidiFile*);
    void setInstrument(int);
    void setTempo(int);
    void setPort(RtMidiOut *);

    void PlaySong();
    static void playSongWrapper(SongPlayer* player);
private:
    MidiFile *song;
    int instrument, tempo;
    RtMidiOut *outputPort;

    void PlaySongInNewThread();
};

#endif // SONGPLAYER_H
