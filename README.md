# 🎶🎵 RS14-passerine 🎵🎶

A simple program for writing down sheet music. Inspired by Super Mario Paint Composer

## Prerequisites

- ALSA - In order to build this tool you will need to have the ALSA(Advanced Linux Sound Architecture) library installed on your Linux system. It usually comes with the system but if not, installing libasound2-dev with your favorite package manager should do the trick.

- TiMidity++ - software synthesizer, which handles MIDI playback.

- Soundfonts - You will need to install FluidR3 soundfont, and append the following line to your /etc/timidity++/timidity.cfg file (with sudo privileges):

```
soundfont /usr/share/soundfonts/FluidR3_GM.sf2
```

## Usage

It supports playback of MIDI songs, at the moment. You can use the seek bar to play the song from whichever part you want!

## Progress

version -1: https://youtu.be/biz5vJ76a4g

versionn 0: https://youtu.be/nEcjDrxMd64

### Special thanks to

Midi parsing library borrowed from craigsapp:
https://github.com/craigsapp/midifile

RealTime Midi(rtMidi) Input/Output library borrowed from thestk:
https://github.com/thestk/rtmidi
