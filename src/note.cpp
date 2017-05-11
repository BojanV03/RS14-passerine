#include <include/note.h>

Note::Note(char n, double tb, double te)
    :_id(n), _timeBegin(tb), _timeEnd(te)
    {}

char Note::getId() const
{
    return _id;
}

void Note::setId(char n)
{
    _id = n;
}

double Note::getTimeBegin() const
{
    return _timeBegin;
}

void Note::setTimeBegin(double t)
{
    _timeBegin = t;
}

double Note::getTimeEnd() const
{
    return _timeEnd;
}

void Note::setTimeEnd(double t)
{
    _timeEnd = t;
}
