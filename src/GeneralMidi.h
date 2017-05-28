#ifndef GENERALMIDI_H
#define GENERALMIDI_H

#include <vector>
#include <src/Instrument.h>

class GeneralMidi
{
public:
    GeneralMidi();

    std::vector<Instrument*> getInstruments() const;
    void setInstruments(const std::vector<Instrument*> &value);

    QString* getNameFromId(int id);

private:
    std::vector<Instrument*> instruments;
};

#endif // GENERALMIDI_H
