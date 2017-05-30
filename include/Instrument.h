#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QString>

class Instrument
{
public:
    Instrument(int _id, QString *_name);

    int getId() const;
    void setId(int value);
    QString *getName() const;
    void setName(QString *value);

private:
    int id;
    QString *name;
};

#endif // INSTRUMENT_H
