#include "Instrument.h"

Instrument::Instrument(int _id, QString *_name)
{
    id = _id;

//    if(name != nullptr)
//        delete name;

    name = new QString(*_name);
}

int Instrument::getId() const
{
    return id;
}

void Instrument::setId(int value)
{
    id = value;
}

QString *Instrument::getName() const
{
    return name;
}

void Instrument::setName(QString *value)
{
    name = value;
}

