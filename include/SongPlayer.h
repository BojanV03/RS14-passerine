#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include <include/Binasc.h>
#include <include/MidiEvent.h>
#include <include/MidiEventList.h>
#include <include/MidiFile.h>
#include <include/MidiMessage.h>
#include <include/Options.h>
#include <include/RtMidi.h>
#include <include/note.h>

#include <thread>
#include <float.h>
#include <QString>

class Passerine;

class SongPlayer
{
public:
    SongPlayer(MidiFile *song = nullptr, int instrument = 0, int tempo = 0, RtMidiOut *outputPort = nullptr);

    MidiFile* getSong()const;
    int getInstrument()const;
    int getTempo()const;
    RtMidi* getPort()const;
    bool isPlaying()const;
    float getCurrentTime() const;
    bool getNoteState(int pos) const;

    void setSong(MidiFile*);
    void setInstrument(int);
    void setTempo(int);
    void setPort(RtMidiOut *);
    void setPlaying(bool);
    void setCurrentTime(float value);
    void setNoteState(int pos, bool state);

    void PlaySong(float startTime = 0, float endTime = FLT_MAX);
    void noteChanged(MidiEvent &m);

    std::vector<Note*> getNotes() const;
    void setNotes(const std::vector<Note> &value);


    QString getLyrics() const;
    void setLyrics(const QString &value);

    std::vector<unsigned char> allNotesOffSignal = {0xB0, 0x7B, 0x00};

    bool getStopped() const;
    void setStopped(bool value);

    void stop();
private:
    MidiFile *song;
    int instrument, tempo;
    RtMidiOut *outputPort;
    bool playing;
    bool stopped;
    std::vector<bool> noteStates;

    float currentTime = 0;

    std::vector<Note*> notes;
    QString lyrics;

    bool threadCreated = false;

    std::thread playThread;

    static void playSongWrapper(SongPlayer* player, float startTime, float endTime);
    void PlaySongInNewThread(float startTime = 0, float endTime = FLT_MAX);

};

#endif // SONGPLAYER_H
