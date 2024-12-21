//
//  Shared.cpp
//  bloom-macos
//
//  Created by Stuart Barnes on 19/08/2018.
//
#include "ofxTinyMidiPlayer.h"
#include "ofMain.h"
// #include "uiVizTheory.h"

class TinyMidiPlayer {

public:
    void configure() {
        // std::filesystem::path p = std::filesystem::path(u8"Arachno SoundFont - Version 1.0.sf2");
        std::filesystem::path p = std::filesystem::path(u8"gm.sf2");
        string soundFontPath = ofToDataPath(p, true);
        string midiId = "Cognition_Inst1";

        // Load sound font
        float volumeDb = -4; 
        soundFont.load(soundFontPath, volumeDb); 	// Volume - decrease if audio clipping occurs. See soundFont.wasAudioClipping() and example-play-midi

        // Choose some instrument
        setInstrument(1); // vizTheory::GeneralMidiInstrument::Acoustic_Grand_Piano

        // Start audio stream
        setupSoundStream();    
    }

    void setInstrument(int instr)
    {

        if (currentInstrument == instr) return;
        currentInstrument = instr;

        ofxTinyMidiLock lock(soundFont);	// Lock resources
        soundFont.channelSetProgramUnsafe(0, instr);
        currentInstrument = instr;
    }

    void setupSoundStream()
    {
        cout << "Starting audio output" << endl;
        // Api: 
        // DEFAULT
        // MS_WASAPI /*!< The Microsoft WASAPI API. */
        // MS_ASIO   /*!< The Steinberg Audio Stream I/O API. */
        // MS_DS     /*!< The Microsoft Direct Sound API. */

        ofSoundDevice::Api API = //ofSoundDevice::Api::MS_ASIO  // Use this for ASIO sound card for the better responsibilty, SR 44100, buffer 64, buffers 2
                                //ofSoundDevice::Api::MS_DS;  // Use this for internal sound card, then need buffer 128, buffers 4
                                ofSoundDevice::Api::OSX_CORE;

        auto devices = soundStream.getDeviceList(API);
        // auto devices = soundStream.getMatchingDevices("default");
        cout << devices << endl;
        if (devices.empty()) {
            cout << "No sound devices" << endl;
        }
        else {

            // Let's search for at least one output! (make this read from config / settings ui in due course)
            int deviceIndex = 0;
            for(int d=0; d<devices.size(); d++) {
                if (devices[d].outputChannels > 0) {
                    deviceIndex = d;
                    break;
                } 
            }

            auto& device = devices[deviceIndex];
            if (device.outputChannels == 0 && device.sampleRates.empty()) {
                ofSystemAlertDialog("Can't initialize output device " + device.name);
                _exit(0);
            }

            ofSoundStreamSettings settings;
            settings.setApi(API);
            settings.setOutDevice(device);

            settings.setOutListener(this);
            settings.sampleRate = 44100;
            settings.numOutputChannels = device.outputChannels;
            settings.numInputChannels = 0; //device.inputChannels;
            settings.bufferSize = 512;
            settings.numBuffers = 4;
            soundStream.setup(settings);
        }
    }


    void noteOn(int channel, int midiNote, int velocity)
    {
        // Note: we enable and disable notes by locking resources, 
        // it's simple, but latency is a large.
        // For faster performance, implement starting notes right inside 
        // custom audioOut function as in "example-play-midi" example project.
        // if (!pressedNotes_[note])
        // {
        // 	pressedNotes_[note] = 1;
        // 	ofxTinyMidiLock lock(soundFont);	// Lock resources
        // 	int velocity = 100;	// Maximum 127
            soundFont.noteOnUnsafe(channel, midiNote, velocity);
        // }
    }

    //--------------------------------------------------------------
    void noteOff(int note)
    {
        // if (pressedNotes_[note])
        // {
        // 	pressedNotes_[note] = 0;
        // 	ofxTinyMidiLock lock(soundFont);	// Lock resources
            soundFont.noteOffUnsafe(0, note);
        // }
    }

void audioOut(ofSoundBuffer& output) {
	// expected 2 channels
	if (output.getNumChannels() != 2) {
		cout << "ofApp::audioOut - expected stereo buffer" << endl;
		return;
	}

	int flagMixing = 0;
	soundFont.audioOut(output, flagMixing);
 }


private:
    int sfont_id;
    int currentInstrument = -1;
    ofSoundStream soundStream;
    ofxTinyMidiSoundFont soundFont;

};