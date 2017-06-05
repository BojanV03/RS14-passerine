#include <include/GeneralMidi.h>

GeneralMidi::GeneralMidi()
{
    QString name = QString::fromStdString("Acoustic Grand Piano");
    instruments.push_back(new Instrument(0, &name));

    name = name.fromStdString("Bright Acoustic Piano");
    instruments.push_back(new Instrument(1, &name));

    name = name.fromStdString("Electric Grand Piano");
    instruments.push_back(new Instrument(2, &name));

    name = name.fromStdString("Honky-tonk Piano");
    instruments.push_back(new Instrument(3, &name));

    name = name.fromStdString("Electric Piano 1");
    instruments.push_back(new Instrument(4, &name));

    name = name.fromStdString("Electric Piano 2");
    instruments.push_back(new Instrument(5, &name));

    name = name.fromStdString("Harpsichord");
    instruments.push_back(new Instrument(6, &name));

    name = name.fromStdString("Clavinet");
    instruments.push_back(new Instrument(7, &name));

    name = name.fromStdString("Celesta");
    instruments.push_back(new Instrument(8, &name));

    name = name.fromStdString("Glockenspiel");
    instruments.push_back(new Instrument(9, &name));

    name = name.fromStdString("Music Box");
    instruments.push_back(new Instrument(10, &name));

    name = name.fromStdString("Vibraphone");
    instruments.push_back(new Instrument(11, &name));

    name = name.fromStdString("Marimba");
    instruments.push_back(new Instrument(12, &name));

    name = name.fromStdString("Xylophone");
    instruments.push_back(new Instrument(13, &name));

    name = name.fromStdString("Tubular Bells");
    instruments.push_back(new Instrument(14, &name));

    name = name.fromStdString("Dulcimer");
    instruments.push_back(new Instrument(15, &name));

    name = name.fromStdString("Drawbar Organ");
    instruments.push_back(new Instrument(16, &name));

    name = name.fromStdString("Percussive Organ");
    instruments.push_back(new Instrument(17, &name));

    name = name.fromStdString("Rock Organ");
    instruments.push_back(new Instrument(18, &name));

    name = name.fromStdString("Church Organ");
    instruments.push_back(new Instrument(19, &name));

    name = name.fromStdString("Reed Organ");
    instruments.push_back(new Instrument(20, &name));

    name = name.fromStdString("Accordion");
    instruments.push_back(new Instrument(21, &name));

    name = name.fromStdString("Harmonica");
    instruments.push_back(new Instrument(22, &name));

    name = name.fromStdString("Tango Accordion");
    instruments.push_back(new Instrument(23, &name));

    name = name.fromStdString("Acoustic Guitar (nylon)");
    instruments.push_back(new Instrument(24, &name));

    name = name.fromStdString("Acoustic Guitar (steel)");
    instruments.push_back(new Instrument(25, &name));

    name = name.fromStdString("Electric Guitar (jazz)");
    instruments.push_back(new Instrument(26, &name));

    name = name.fromStdString("Electric Guitar (clean)");
    instruments.push_back(new Instrument(27, &name));

    name = name.fromStdString("Electric Guitar (muted)");
    instruments.push_back(new Instrument(28, &name));

    name = name.fromStdString("Overdriven Guitar");
    instruments.push_back(new Instrument(29, &name));

    name = name.fromStdString("Distortion Guitar");
    instruments.push_back(new Instrument(30, &name));

    name = name.fromStdString("Guitar Harmonics");
    instruments.push_back(new Instrument(31, &name));

    name = name.fromStdString("Acoustic Bass");
    instruments.push_back(new Instrument(32, &name));

    name = name.fromStdString("Electric Bass (finger)");
    instruments.push_back(new Instrument(33, &name));

    name = name.fromStdString("Electric Bass (pick)");
    instruments.push_back(new Instrument(34, &name));

    name = name.fromStdString("Fretless Bass");
    instruments.push_back(new Instrument(35, &name));

    name = name.fromStdString("Slap Bass 1");
    instruments.push_back(new Instrument(36, &name));

    name = name.fromStdString("Slap Bass 2");
    instruments.push_back(new Instrument(37, &name));

    name = name.fromStdString("Synth Bass 1");
    instruments.push_back(new Instrument(38, &name));

    name = name.fromStdString("Synth Bass 2");
    instruments.push_back(new Instrument(39, &name));

    name = name.fromStdString("Violin");
    instruments.push_back(new Instrument(40, &name));

    name = name.fromStdString("Viola");
    instruments.push_back(new Instrument(41, &name));

    name = name.fromStdString("Cello");
    instruments.push_back(new Instrument(42, &name));

    name = name.fromStdString("Contrabass");
    instruments.push_back(new Instrument(43, &name));

    name = name.fromStdString("Tremolo Strings");
    instruments.push_back(new Instrument(44, &name));

    name = name.fromStdString("Pizzicato Strings");
    instruments.push_back(new Instrument(45, &name));

    name = name.fromStdString("Orchestral Harp");
    instruments.push_back(new Instrument(46, &name));

    name = name.fromStdString("Timpani");
    instruments.push_back(new Instrument(47, &name));

    name = name.fromStdString("String Ensemble 1");
    instruments.push_back(new Instrument(48, &name));

    name = name.fromStdString("String Ensemble 2");
    instruments.push_back(new Instrument(49, &name));

    name = name.fromStdString("Synth Strings 1");
    instruments.push_back(new Instrument(50, &name));

    name = name.fromStdString("Synth Strings 2");
    instruments.push_back(new Instrument(51, &name));

    name = name.fromStdString("Choir Aahs");
    instruments.push_back(new Instrument(52, &name));

    name = name.fromStdString("Voice Oohs");
    instruments.push_back(new Instrument(53, &name));

    name = name.fromStdString("Synth Choir");
    instruments.push_back(new Instrument(54, &name));

    name = name.fromStdString("Orchestra Hit");
    instruments.push_back(new Instrument(55, &name));

    name = name.fromStdString("Trumpet");
    instruments.push_back(new Instrument(56, &name));

    name = name.fromStdString("Trombone");
    instruments.push_back(new Instrument(57, &name));

    name = name.fromStdString("Tuba");
    instruments.push_back(new Instrument(58, &name));

    name = name.fromStdString("Muted Trumpet");
    instruments.push_back(new Instrument(59, &name));

    name = name.fromStdString("French Horn");
    instruments.push_back(new Instrument(60, &name));

    name = name.fromStdString("Brass Section");
    instruments.push_back(new Instrument(61, &name));

    name = name.fromStdString("Synth Brass 1");
    instruments.push_back(new Instrument(62, &name));

    name = name.fromStdString("Synth Brass 2");
    instruments.push_back(new Instrument(63, &name));

    name = name.fromStdString("Soprano Sax");
    instruments.push_back(new Instrument(64, &name));

    name = name.fromStdString("Alto Sax");
    instruments.push_back(new Instrument(65, &name));

    name = name.fromStdString("Tenor Sax");
    instruments.push_back(new Instrument(66, &name));

    name = name.fromStdString("Baritone Sax");
    instruments.push_back(new Instrument(67, &name));

    name = name.fromStdString("Oboe");
    instruments.push_back(new Instrument(68, &name));

    name = name.fromStdString("English Horn");
    instruments.push_back(new Instrument(69, &name));

    name = name.fromStdString("Bassoon");
    instruments.push_back(new Instrument(70, &name));

    name = name.fromStdString("Clarinet");
    instruments.push_back(new Instrument(71, &name));

    name = name.fromStdString("Piccolo");
    instruments.push_back(new Instrument(72, &name));

    name = name.fromStdString("Flute");
    instruments.push_back(new Instrument(73, &name));

    name = name.fromStdString("Recorder");
    instruments.push_back(new Instrument(74, &name));

    name = name.fromStdString("Pan Flute");
    instruments.push_back(new Instrument(75, &name));

    name = name.fromStdString("Blown bottle");
    instruments.push_back(new Instrument(76, &name));

    name = name.fromStdString("Shakuhachi");
    instruments.push_back(new Instrument(77, &name));

    name = name.fromStdString("Whistle");
    instruments.push_back(new Instrument(78, &name));

    name = name.fromStdString("Ocarina");
    instruments.push_back(new Instrument(79, &name));

    name = name.fromStdString("Lead 1 (square)");
    instruments.push_back(new Instrument(80, &name));

    name = name.fromStdString("Lead 2 (sawtooth)");
    instruments.push_back(new Instrument(81, &name));

    name = name.fromStdString("Lead 3 (calliope)");
    instruments.push_back(new Instrument(82, &name));

    name = name.fromStdString("Lead 4 (chiff)");
    instruments.push_back(new Instrument(83, &name));

    name = name.fromStdString("Lead 5 (charang)");
    instruments.push_back(new Instrument(84, &name));

    name = name.fromStdString("Lead 6 (voice)");
    instruments.push_back(new Instrument(85, &name));

    name = name.fromStdString("Lead 7 (fifths)");
    instruments.push_back(new Instrument(86, &name));

    name = name.fromStdString("Lead 8 (bass + lead)");
    instruments.push_back(new Instrument(87, &name));

    name = name.fromStdString("Pad 1 (new age)");
    instruments.push_back(new Instrument(88, &name));

    name = name.fromStdString("Pad 2 (warm)");
    instruments.push_back(new Instrument(89, &name));

    name = name.fromStdString("Pad 3 (polysynth)");
    instruments.push_back(new Instrument(90, &name));

    name = name.fromStdString("Pad 4 (choir)");
    instruments.push_back(new Instrument(91, &name));

    name = name.fromStdString("Pad 5 (bowed)");
    instruments.push_back(new Instrument(92, &name));

    name = name.fromStdString("Pad 6 (metallic)");
    instruments.push_back(new Instrument(93, &name));

    name = name.fromStdString("Pad 7 (halo)");
    instruments.push_back(new Instrument(94, &name));

    name = name.fromStdString("Pad 8 (sweep)");
    instruments.push_back(new Instrument(95, &name));

    name = name.fromStdString("FX 1 (rain)");
    instruments.push_back(new Instrument(96, &name));

    name = name.fromStdString("FX 2 (soundtrack)");
    instruments.push_back(new Instrument(97, &name));

    name = name.fromStdString("FX 3 (crystal)");
    instruments.push_back(new Instrument(98, &name));

    name = name.fromStdString("FX 4 (atmosphere)");
    instruments.push_back(new Instrument(99, &name));

    name = name.fromStdString("FX 5 (brightness)");
    instruments.push_back(new Instrument(100, &name));

    name = name.fromStdString("FX 6 (goblins)");
    instruments.push_back(new Instrument(101, &name));

    name = name.fromStdString("FX 7 (echoes)");
    instruments.push_back(new Instrument(102, &name));

    name = name.fromStdString("FX 8 (sci-fi)");
    instruments.push_back(new Instrument(103, &name));

    name = name.fromStdString("Sitar");
    instruments.push_back(new Instrument(104, &name));

    name = name.fromStdString("Banjo");
    instruments.push_back(new Instrument(105, &name));

    name = name.fromStdString("Shamisen");
    instruments.push_back(new Instrument(106, &name));

    name = name.fromStdString("Koto");
    instruments.push_back(new Instrument(107, &name));

    name = name.fromStdString("Kalimba");
    instruments.push_back(new Instrument(108, &name));

    name = name.fromStdString("Bagpipe");
    instruments.push_back(new Instrument(109, &name));

    name = name.fromStdString("Fiddle");
    instruments.push_back(new Instrument(110, &name));

    name = name.fromStdString("Shanai");
    instruments.push_back(new Instrument(111, &name));

    name = name.fromStdString("Tinkle Bell");
    instruments.push_back(new Instrument(112, &name));

    name = name.fromStdString("Agogo");
    instruments.push_back(new Instrument(113, &name));

    name = name.fromStdString("Steel Drums");
    instruments.push_back(new Instrument(114, &name));

    name = name.fromStdString("Woodblock");
    instruments.push_back(new Instrument(115, &name));

    name = name.fromStdString("Taiko Drum");
    instruments.push_back(new Instrument(116, &name));

    name = name.fromStdString("Melodic Tom");
    instruments.push_back(new Instrument(117, &name));

    name = name.fromStdString("Synth Drum");
    instruments.push_back(new Instrument(118, &name));

    name = name.fromStdString("Reverse Cymbal");
    instruments.push_back(new Instrument(119, &name));

    name = name.fromStdString("Guitar Fret Noise");
    instruments.push_back(new Instrument(120, &name));

    name = name.fromStdString("Breath Noise");
    instruments.push_back(new Instrument(121, &name));

    name = name.fromStdString("Seashore");
    instruments.push_back(new Instrument(122, &name));

    name = name.fromStdString("Bird Tweet");
    instruments.push_back(new Instrument(123, &name));

    name = name.fromStdString("Telephone Ring");
    instruments.push_back(new Instrument(124, &name));

    name = name.fromStdString("Helicopter");
    instruments.push_back(new Instrument(125, &name));

    name = name.fromStdString("Applause");
    instruments.push_back(new Instrument(126, &name));

    name = name.fromStdString("Gunshot");
    instruments.push_back(new Instrument(127, &name));
}

std::vector<Instrument*> GeneralMidi::getInstruments() const
{
    return instruments;
}

void GeneralMidi::setInstruments(const std::vector<Instrument*> &value)
{
    instruments = value;
}

QString *GeneralMidi::getNameFromId(int id)
{
    return instruments[id]->getName();
}
