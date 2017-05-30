#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T19:11:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Passerine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
        src/passerine.cpp \
    src/Binasc.cpp \
    src/MidiEvent.cpp \
    src/MidiEventList.cpp \
    src/MidiFile.cpp \
    src/MidiMessage.cpp \
    src/Options.cpp \
    src/RtMidi.cpp \
    src/rtmidi_c.cpp \
    src/portselector.cpp \
    src/SongPlayer.cpp \
    src/Octave.cpp \
    src/Key.cpp \
    src/note.cpp \
    src/AnimationGroup.cpp \
    src/noteGroup.cpp \
    src/piceditor.cpp \
    src/Instrument.cpp \
    src/GeneralMidi.cpp

HEADERS  += include/passerine.h \
    include/Binasc.h \
    include/MidiEvent.h \
    include/MidiEventList.h \
    include/MidiFile.h \
    include/MidiMessage.h \
    include/Options.h \
    include/RtMidi.h \
    include/rtmidi_c.h \
    include/portselector.h \
    include/SongPlayer.h \
    include/SongPlayer.h \
    include/Octave.h \
    include/Octave.h \
    include/Key.h \
    include/Key.h \
    include/note.h \
    include/AnimationGroup.h \
    include/noteGroup.h \
    include/piceditor.h \
    include/Instrument.h \
    include/GeneralMidi.h

FORMS    += ui/passerine.ui \
    ui/portselector.ui \
    ui/piceditor.ui

unix:!macx: LIBS += -lasound

DISTFILES +=

CONFIG += c++11
