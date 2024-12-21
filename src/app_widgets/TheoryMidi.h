//
//  Theory.h
//  bloom-macos
//
//
#pragma once

#include "ofxXmlSettings.h"



//--------------------------------------------------------------
class vizMidiNote {

public:
    vizMidiNote() { };

    /*
        duration: 1.0f = 4 x 1/4 notes (ie 1.0f = 1 bar, 0.25 = quarter note, 0.03125 = 1/32nd!)


    */

    vizMidiNote(int note, int velocity, float offset, float duration) {
        setVelocity(velocity);
    }

    int getVelocity() {
        return mVelocity;
    }

    void setVelocity(int val) {
        mVelocity = min(val, 127);
        mVelocity = max(val, 0);
    }    

    enum NoteValueName {
        wholeNote           = 1,
        halfNote            = 2,
        quarterNote         = 3,
        eighthNote          = 4,
        sixteenthNote       = 5,
        thirtySecondNote    = 6,
        sixtyFourthNote     = 7
    };

    static float getNoteValue(NoteValueName val) {
        switch(val) {
            case vizMidiNote::NoteValueName::wholeNote: return 1.0f;
            case vizMidiNote::NoteValueName::halfNote: return 1.0f / 2.0f;
            case vizMidiNote::NoteValueName::quarterNote: return 1.0f / 4.0f;
            case vizMidiNote::NoteValueName::eighthNote: return 1.0f / 8.0f;
            case vizMidiNote::NoteValueName::sixteenthNote: return 1.0f / 16.0f;
            case vizMidiNote::NoteValueName::thirtySecondNote: return 1.0f / 32.0f;
            case vizMidiNote::NoteValueName::sixtyFourthNote: return 1.0f / 64.0f;
            default: return 1.0f;
        }
    }

private:
    int mNote = 0; // 0 - 127;
    int mVelocity = 0; // 0 - 127;
    float offset = 0.0f;
    float duration = 0.0f;
};






