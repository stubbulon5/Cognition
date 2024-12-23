//
//  Shared.cpp
//  bloom-macos
//
//  Created by Stuart Barnes on 19/08/2018.
//
#include "MidiShared.h"

ofxMidiOut MidiShared::midiOut;
int MidiShared::channel;
unsigned int MidiShared::currentPgm;
int MidiShared::note, MidiShared::velocity;
int MidiShared::pan, MidiShared::bend, MidiShared::touch, MidiShared::polytouch;
int MidiShared::gmInstrument = 1;
TinyMidiPlayer MidiShared::tinyMidiPlayer = TinyMidiPlayer();

/*
 static methods
 */
void MidiShared::configure() {

	#if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
		std::cout << "***************************** MIDI PORTS  ***************************** " << std::endl;
		midiOut.listOutPorts();
		std::cout << std::endl;
		std::cout << "*********************************************************************** " << std::endl;
	#endif       


	bool foundPort = false;
	for(int i=0; i<midiOut.getNumOutPorts(); i++) {
		// Make below configurable!
		// midiOut.openPort(1); // by number
		// midiOut.openVirtualPort("CognitionApp");

		string portName = ofToLower(midiOut.getOutPortName(i));

		if (ofIsStringInString(portName, "cognition")) {
			midiOut.openPort(i); // by number
			#if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
				std::cout << "CONNECTED TO PORT " << midiOut.getName() << std::endl;
			#endif   			
			foundPort = true;
		}
		
	}

	if (!foundPort) {
		string portName = ofToLower(midiOut.getOutPortName(0));
		#if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
			std::cout << "CONNECTED TO PORT " << midiOut.getName() << std::endl;
		#endif   		
		midiOut.openPort(0);
	}

	channel = 0;
	currentPgm = 0;
	note = 0;
	velocity = 0;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;

	tinyMidiPlayer.configure();

}


ofxMidiOut MidiShared::getMidiOut() {
	return midiOut;
}

void MidiShared::playNote(MusicTheory::NotePtr note,  int velocity, int midiInstrument) {
	int midiNote = note->toInt();
	velocity = velocity;
	if (gmInstrument != midiInstrument) {
		gmInstrument = midiInstrument;
		// sdFluidSynthShared::programSelect(midiInstrument);
		tinyMidiPlayer.setInstrument(midiInstrument);
	}

	// getMidiOut().sendNoteOn(channel, midiNote, velocity);
	tinyMidiPlayer.noteOn(channel, midiNote, velocity);
}

void MidiShared::playNote(MusicTheory::NotePtr note, int gmInstrument) {
	MidiShared::playNote(note, 80, gmInstrument);
}

void MidiShared::playChord(MusicTheory::ChordPtr chord, int gmInstrument) {
	deque<MusicTheory::NotePtr> chordNotes = chord->getAllNotes();

	for (int i = 0; i < chordNotes.size(); i++) {
		// Is this a good enough approach or do we need to buffer the notes and send as a batch somehow?
		MidiShared::playNote(chordNotes[i], gmInstrument);
	}
}

void MidiShared::closePort() {
    midiOut.closePort();
}











/*

#include "ofApp.h"

 //--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);

	// print the available output ports to the console
	midiOut.listOutPorts();

	// connect
	midiOut.openPort(0); // by number
	//midiOut.openPort("IAC Driver Pure Data In"); // by name
	//midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port

	channel = 1;
	currentPgm = 0;
	note = 0;
	velocity = 0;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {

	// let's see something
	ofSetColor(0);
	stringstream text;
	text << "connected to port " << midiOut.getPort()
		<< " \"" << midiOut.getName() << "\"" << endl
		<< "is virtual?: " << midiOut.isVirtual() << endl << endl
		<< "sending to channel " << channel << endl << endl
		<< "current program: " << currentPgm << endl << endl
		<< "note: " << note << endl
		<< "velocity: " << velocity << endl
		<< "pan: " << pan << endl
		<< "bend: " << bend << endl
		<< "touch: " << touch << endl
		<< "polytouch: " << polytouch;
	ofDrawBitmapString(text.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::exit() {

	// clean up
	midiOut.closePort();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// ignore shift+s since it is used in keyReleased for sysex sending
	if (key == 'S') return;

	// send a note on if the key is a letter or a number
	if (isalnum((unsigned char)key)) {

		// scale the ascii values to midi velocity range 0-127
		// see an ascii table: http://www.asciitable.com/
		note = ofMap(key, 48, 122, 0, 127);
		velocity = 64;
		midiOut.sendNoteOn(channel, note, velocity);

		// print out both the midi note and the frequency
		ofLogNotice() << "note: " << note
			<< " freq: " << ofxMidi::mtof(note) << " Hz";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	switch (key) {

		// send pgm change on arrow keys
	case OF_KEY_UP:
		currentPgm = (int)ofClamp(currentPgm + 1, 0, 127);
		midiOut.sendProgramChange(channel, currentPgm);
		break;
	case OF_KEY_DOWN:
		currentPgm = (int)ofClamp(currentPgm - 1, 0, 127);
		midiOut << ProgramChange(channel, currentPgm); // stream interface
		break;

		// aftertouch
	case '[':
		touch = 64;
		midiOut.sendAftertouch(channel, touch);
		break;
	case ']':
		touch = 127;
		midiOut << Aftertouch(channel, touch); // stream interface
		break;

		// poly aftertouch
	case '<':
		polytouch = 64;
		midiOut.sendPolyAftertouch(channel, 64, polytouch);
		break;
	case '>':
		polytouch = 127;
		midiOut << PolyAftertouch(channel, 64, polytouch); // stream interface
		break;

		// sysex using raw bytes (use shift + s)
	case 'S': {
		// send a pitch change to Part 1 of a MULTI on an Akai sampler
		// from http://troywoodfield.tripod.com/sysex.html
		//
		// do you have an S2000 to try?
		//
		// note: this is probably not as efficient as the next two methods
		//       since it sends only one byte at a time, instead of all
		//       at once
		//
		midiOut.sendMidiByte(MIDI_SYSEX);
		midiOut.sendMidiByte(0x47); // akai manufacturer code
		midiOut.sendMidiByte(0x00); // channel 0
		midiOut.sendMidiByte(0x42); // MULTI
		midiOut.sendMidiByte(0x48); // using an Akai S2000
		midiOut.sendMidiByte(0x00); // Part 1
		midiOut.sendMidiByte(0x00); // transpose
		midiOut.sendMidiByte(0x01); // Access Multi Parts
		midiOut.sendMidiByte(0x4B); // offset
		midiOut.sendMidiByte(0x00); // offset
		midiOut.sendMidiByte(0x01); // Field size = 1
		midiOut.sendMidiByte(0x00); // Field size = 1
		midiOut.sendMidiByte(0x04); // pitch value = 4
		midiOut.sendMidiByte(0x00); // offset
		midiOut.sendMidiByte(MIDI_SYSEX_END);

		// send again using a vector
		//
		// sends all bytes within one message
		//
		vector<unsigned char> sysexMsg;
		sysexMsg.push_back(MIDI_SYSEX);
		sysexMsg.push_back(0x47);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(0x42);
		sysexMsg.push_back(0x48);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(0x01);
		sysexMsg.push_back(0x4B);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(0x01);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(0x04);
		sysexMsg.push_back(0x00);
		sysexMsg.push_back(MIDI_SYSEX_END);
		midiOut.sendMidiBytes(sysexMsg);

		// send again with the byte stream interface
		//
		// builds the message, then sends it on FinishMidi()
		//
		midiOut << StartMidi() << MIDI_SYSEX
			<< 0x47 << 0x00 << 0x42 << 0x48 << 0x00 << 0x00 << 0x01
			<< 0x4B << 0x00 << 0x01 << 0x00 << 0x04 << 0x00
			<< MIDI_SYSEX_END << FinishMidi();
		break;
	}

			  // print the port list
	case '?':
		midiOut.listOutPorts();
		break;

		// note off using raw bytes
	case ' ':
		// send with the byte stream interface, noteoff for note 60
		midiOut << StartMidi() << 0x80 << 0x3C << 0x40 << FinishMidi();
		break;

	default:

		// send a note off if the key is a letter or a number
		if (isalnum(key)) {
			note = ofMap(key, 48, 122, 0, 127);
			velocity = 0;
			midiOut << NoteOff(channel, note, velocity); // stream interface
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	// x pos controls the pan (ctl = 10)
	pan = ofMap(x, 0, ofGetWidth(), 0, 127);
	midiOut.sendControlChange(channel, 10, pan);

	// y pos controls the pitch bend
	bend = ofMap(y, 0, ofGetHeight(), 0, MIDI_MAX_BEND);
	midiOut.sendPitchBend(channel, bend);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}

*/
