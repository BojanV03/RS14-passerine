#include <string>
#include <include/MidiFile.h>
#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
    Note(std::string n, int tb, int te);
    std::string getName() const;
    void setName(std::string n);
    int getTimeBegin() const;
    void setTimeBegin(int t);
    int getTimeEnd() const;
    void setTimeEnd(int t);

private:
    std::string _name;
    int _timeBegin;
    int _timeEnd;
};

#endif // NOTE_H
