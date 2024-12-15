//
//  uiVizShared.cpp
//  bloom-macos
//
//  Created by Stuart Barnes on 19/08/2018.
//
#include "sdFluidSynthShared.h"
#include "ofMain.h"
#include "uiVizTheory.h"

/*
 static methods
 */

#ifdef TARGET_OF_IOS
void sdFluidSynthShared::configure() {}
void sdFluidSynthShared::close() {}
#else

fluid_midi_driver_t* m_mdriver;
int sfont_id;
int currentProgram = -1;

void sdFluidSynthShared::configure() {
    std::filesystem::path p = std::filesystem::path(u8"Arachno SoundFont - Version 1.0.sf2");
    string soundFontPath = ofToDataPath(p, true);
    
    string midiId = "Cognition_Inst1";

    fluid_settings_t* settings = new_fluid_settings();

    #if defined(TARGET_LINUX)
    fluid_settings_setstr(settings, "audio.driver", "alsa");
    fluid_settings_setstr(settings, "midi.driver", "alsa_seq");
    fluid_settings_setstr(settings, "midi.alsa_seq.id", midiId.c_str());
    #elif defined(TARGET_OSX)
    fluid_settings_setstr(settings, "audio.driver", "coreaudio");
    fluid_settings_setstr(settings, "midi.driver", "coremidi");
    fluid_settings_setstr(settings, "midi.coremidi.id", midiId.c_str());
    #elif defined(TARGET_WIN32)
    fluid_settings_setstr(settings, "audio.driver", "dsound");
    fluid_settings_setstr(settings, "midi.driver", "winmidi");
    fluid_settings_setstr(settings, "midi.winmidi.device", midiId.c_str());
    #endif
    // Jack stuff (if appicable)
    fluid_settings_setint(settings, "audio.jack.autoconnect", 1);
    fluid_settings_setstr(settings, "audio.jack.id", "Cognition_Inst1");
    fluid_settings_setstr(settings, "midi.jack.id", midiId.c_str());
    fluid_settings_setstr(settings, "synth.default-soundfont", soundFontPath.c_str());

    // General settings
    fluid_settings_setint(settings, "synth.polyphony", 256);

    // Comment these eventually
    //fluid_settings_setint(settings, "synth.dump", 1);
    //fluid_settings_setint(settings, "synth.verbose", 1);

    ofxFluidSynth::configure(settings);
    sfont_id = fluid_synth_sfload(ofxFluidSynth::getSynth(), soundFontPath.c_str(),  1);
    m_mdriver = new_fluid_midi_driver(settings, sdFluidSynthShared::handle_midi_event, NULL);

    sdFluidSynthShared::programSelect(vizTheory::GeneralMidiInstrument::Acoustic_Grand_Piano);

}

void sdFluidSynthShared::programSelect(int program) {
    if (currentProgram == program) return;
    currentProgram = program;
    fluid_synth_program_select(
         ofxFluidSynth::getSynth(), 
        1, 
        sfont_id,
        0, 
        program
    );     
}

int sdFluidSynthShared::handle_midi_event(void* data, fluid_midi_event_t* event) {

    fluid_synth_noteon(
        ofxFluidSynth::getSynth(), 
        1, 
        fluid_midi_event_get_pitch(event), 
        fluid_midi_event_get_velocity(event)
    );
    //printf("event type: %d\n", fluid_midi_event_get_type(event));
    return 0;
}

fluid_synth_t* sdFluidSynthShared::getSynth() {
	return ofxFluidSynth::getSynth();
}

void sdFluidSynthShared::close() {
    ofxFluidSynth::close();
    delete_fluid_midi_driver(m_mdriver);
}

#endif