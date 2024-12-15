
#pragma once

#ifndef TARGET_OF_IOS	
#include "ofxFluidSynth.h"
#endif

#include <iostream>

class sdFluidSynthShared {

public:
	static void configure();
	static void close();
	static void programSelect(int program);
#ifndef TARGET_OF_IOS	
	static int handle_midi_event(void* data, fluid_midi_event_t* event);
	fluid_synth_t* getSynth();
#endif

private:

};
