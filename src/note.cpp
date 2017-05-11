#include <include/note.h>

Note::Note(std::string n, int tb, int te)
    :_name(n), _timeBegin(tb), _timeEnd(te)
    {}

std::string Note::getName() const
{
    return _name;
}

void Note::setName(std::string n)
{
    _name = n;
}

int Note::getTimeBegin() const
{
    return _timeBegin;
}

void Note::setTimeBegin(int t)
{
    _timeBegin = t;
}

int Note::getTimeEnd() const
{
    return _timeEnd;
}

void Note::setTimeEnd(int t)
{
    _timeEnd = t;
}
