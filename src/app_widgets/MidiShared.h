
#pragma once
#include "ofxMidi.h"
#include "ofxMusicTheory.h"
#include "TheoryMidi.h"
#include "TinyMidiPlayer.h"

class MidiShared {

public:

	static void configure();

	static ofxMidiOut getMidiOut();
	static void playNote(MusicTheory::NotePtr note,  int velocity, int gmInstrument);
	static void playNote(MusicTheory::NotePtr note, int gmInstrument);
	static void playChord(MusicTheory::ChordPtr chord, int gmInstrument);
    static void closePort();


private:
	static ofxMidiOut midiOut;
	static int channel;
	static unsigned int currentPgm;
	static int note, velocity;
	static int pan, bend, touch, polytouch, gmInstrument;
	static TinyMidiPlayer tinyMidiPlayer;
};
