#include <string>
#include <include/MidiFile.h>
#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
    Note();

private:
    std::string name;
    int timeBegin;
    int timeEnd;
};

#endif // NOTE_H
