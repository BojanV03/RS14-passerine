#include <string>
#include <include/MidiFile.h>
#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
    Note(char n, double tb, double te);
    char getId() const;
    void setId(char n);
    double getTimeBegin() const;
    void setTimeBegin(double t);
    double getTimeEnd() const;
    void setTimeEnd(double t);

private:
    char _id;
    double _timeBegin;
    double _timeEnd;
};

#endif // NOTE_H
