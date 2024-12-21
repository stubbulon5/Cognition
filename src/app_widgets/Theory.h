//
//  Theory.h
//  bloom-macos
//
//
#pragma once
// Theory stuff 
#include "ofxMusicTheory.h"

// Sound stuff
#include "MidiShared.h"
#include "ofxAquamarine.h"
#include "ofxXmlSettings.h"

#include "../core/midifile/include/Binasc.h"
#include "../core/midifile/include/MidiEvent.h"
#include "../core/midifile/include/MidiEventList.h"
#include "../core/midifile/include/MidiFile.h"
#include "../core/midifile/include/MidiMessage.h"

#include "TheoryMidi.h"
#include "appConstants.h"


using Poco::RegularExpression;


//--------------------------------------------------------------
class vizTheory {

public:
    enum GeneralMidiInstrument {
        Acoustic_Grand_Piano = 1, Bright_Acoustic_Piano = 2, Electric_Grand_Piano = 3, Honky_tonk_Piano = 4, Electric_Piano_1 = 5, Electric_Piano_2 = 6, Harpsichord = 7, Clavi = 8, Celesta = 9, Glockenspiel = 10,
        Music_Box = 11, Vibraphone = 12, Marimba = 13, Xylophone = 14, Tubular_Bells = 15, Dulcimer = 16, Drawbar_Organ = 17, Percussive_Organ = 18, Rock_Organ = 19, Church_Organ = 20, 
        Reed_Organ = 21, Accordion = 22, Harmonica = 23, Tango_Accordion = 24, Acoustic_Guitar_nylon = 25, Acoustic_Guitar_steel = 26, Electric_Guitar_jazz = 27, Electric_Guitar_clean = 28, Electric_Guitar_muted = 29, Overdriven_Guitar = 30,
        Distortion_Guitar = 31, Guitar_harmonics = 32, Acoustic_Bass = 33, Electric_Bass_finger = 34, Electric_Bass_pick = 35, Fretless_Bass = 36, Slap_Bass_1 = 37, Slap_Bass_2 = 38, Synth_Bass_1 = 39, Synth_Bass_2 = 40, 
        Violin = 41, Viola = 42, Cello = 43, Contrabass = 44, Tremolo_Strings = 45, Pizzicato_Strings = 46, Orchestral_Harp = 47, Timpani = 48, String_Ensemble_1 = 49, String_Ensemble_2 = 50, 
        SynthStrings_1 = 51, SynthStrings_2 = 52, Choir_Aahs = 53, Voice_Oohs = 54, Synth_Voice = 55, Orchestra_Hit = 56, Trumpet = 57, Trombone = 58, Tuba = 59, Muted_Trumpet = 60,
        French_Horn = 61, Brass_Section = 62, SynthBrass_1 = 63, SynthBrass_2 = 64, Soprano_Sax = 65, Alto_Sax = 66, Tenor_Sax = 67, Baritone_Sax = 68, Oboe = 69, English_Horn = 70,
        Bassoon = 71, Clarinet = 72, Piccolo = 73, Flute = 74, Recorder = 75, Pan_Flute = 76, Blown_Bottle = 77, Shakuhachi = 78, Whistle = 79, Ocarina = 80,
        Lead_1_square = 81, Lead_2_sawtooth = 82, Lead_3_calliope = 83, Lead_4_chiff = 84, Lead_5_charang = 85, Lead_6_voice = 86, Lead_7_fifths = 87, Lead_8_bass_lead = 88, Pad_1_new_age = 89, Pad_2_warm = 90,
        Pad_3_polysynth = 91, Pad_4_choir = 92, Pad_5_bowed = 93, Pad_6_metallic = 94, Pad_7_halo = 95, Pad_8_sweep = 96, FX_1_rain = 97, FX_2_soundtrack = 98, FX_3_crystal = 99, FX_4_atmosphere = 100,
        FX_5_brightness = 101, FX_6_goblins = 102, FX_7_echoes = 103, FX_8_sci_fi = 104, Sitar = 105, Banjo = 106,Shamisen = 107, Koto = 108, Kalimba = 109, Bag_pipe = 110,
        Fiddle = 111, Shanai = 112, Tinkle_Bell = 113, Agogo = 114, Steel_Drums = 115, Woodblock = 116, Taiko_Drum = 117, Melodic_Tom = 118, Synth_Drum = 119, Reverse_Cymbal = 120,
        Guitar_Fret_Noise = 121, Breath_Noise = 122, Seashore = 123, Bird_Tweet = 124, Telephone_Ring = 125, Helicopter = 126, Applause = 127, Gunshot = 128         
    };

public:
    enum DegreeName {
        majorUnison                  = 0,
        augmentedUnison_minorSecond  = 1,
        majorSecond                  = 2,
        augmentedSecond_minorThird   = 3,
        majorThird                   = 4,
        perfectFourth                = 5,
        augmentedFourth_minorFifth   = 6,
        perfectFifth                 = 7,
        augmentedFifth_minorSixth    = 8,
        majorSixth                   = 9,
        augmentedSixth_minorSeventh  = 10,
        majorSeventh                 = 11,
        dominantThirteenth           = 12
    };
    
    enum class NoteMode {
        DEFAULT,
        SHARP,
        FLAT
    };
   
    static string extractFileSystemSafeName(string theoryArtifactName) {
        string illegalChars = "\\/:?\"<>|[]";
        for (auto it = theoryArtifactName.begin() ; it < theoryArtifactName.end() ; ++it){
            bool found = illegalChars.find(*it) != string::npos;
            if(found){
                *it = ' ';
            }
        }

        //ofStringReplace(theoryArtifactName, "#", "sharp");

        return theoryArtifactName;
    }    

    static string extractRootFromChord(string chordName) {
        string rootRaw = "";
        if (chordName.length() > 2) {        
            ofStringReplace(chordName, "sharp", "#");
            ofStringReplace(chordName, "flat", "b");
            ofStringReplace(chordName, "Sharp", "#");
            ofStringReplace(chordName, "Flat", "b");            
            ofStringReplace(chordName, " ", ""); 
        }
        if (chordName.length() > 1) {
            rootRaw = chordName.substr(0, 2);
            string rootRawLastChar = rootRaw.substr(1, 1);
            if (rootRawLastChar != "#" && rootRawLastChar != "b") {
                rootRaw = chordName.substr(0, 1);
            }
        } else {
            rootRaw = chordName.substr(0, 1);
        }
        return rootRaw;
    }

    static bool isValidKey(string context) {
        if (context.length() == 1 || context.length() == 2) {
            char &c = context[0];
            c = ::toupper(c);
            for(int i=0; i< getChromaticScaleSharps().size(); i++) {
                if (context == getChromaticScaleSharps()[i] || context == getChromaticScaleFlats()[i]) return true;
            }
        }
        return false;
    }    

    static string extractRootFromMusicTheoryContext(string context) {
        return extractRootFromChord(context);
    }    

    static string extractRemainderFromMusicTheoryContext(string root, string context) {
        if (context.length() > root.length()) {
            string remainder = context.substr(root.length(), context.length() - root.length());
            return remainder;
        }
        return "";
    }       
    
    static vizTheory::NoteMode getNoteMode(string noteName) {
        if (ofIsStringInString(noteName, "#")) {
            return vizTheory::NoteMode::SHARP;
        } else if (ofIsStringInString(noteName, "b")) {
            return vizTheory::NoteMode::FLAT;
        }
        return vizTheory::NoteMode::DEFAULT;
    }
    
    static vector<MusicTheory::NotePtr> getCircleOfFifthsNotesForScaleT1(string scaleName) { // SHARPS :: FLATS :: COF HALF CIRCLE
        vector<MusicTheory::NotePtr> circleOfFifthsForScale = vector<MusicTheory::NotePtr>();
        vector<string> c = getCircleOfFifthsSharps();
        
        for (int i = 0; i < (int)c.size(); i++) {
            circleOfFifthsForScale.push_back(MusicTheory::Note::create(c[i]));
        }
        return circleOfFifthsForScale;
    }

	static vector<string> getCircleOfFifthsNotesForScaleT1String(string scaleName) {
		vector<MusicTheory::NotePtr> circleOfFifthsForScale = getCircleOfFifthsNotesForScaleT1(scaleName);
		vector<string> circleOfFifthsForScaleString = vector<string>();

		for (int i = 0; i < (int)circleOfFifthsForScale.size(); i++) {
			circleOfFifthsForScaleString.insert(circleOfFifthsForScaleString.end(), circleOfFifthsForScale[i]->getDiatonicName());
		}
		return circleOfFifthsForScaleString;
	}

    static int getPosInScaleForRoot(shared_ptr<MusicTheory::Scale> scale, MusicTheory::NotePtr root) {
        for (int i=0; i<scale->notes.size(); i++) {
             if (scale->notes[i] == root) return i;
        }
        return 0;
    }
    
    
    static bool isChordValid(MusicTheory::ChordPtr mt_Chord) {
        return !(mt_Chord == nullptr || mt_Chord->notes.size() == 0 || mt_Chord->getName() == "Invalid chord" || mt_Chord->getRoot() == nullptr);
    }

    static bool chordHasNotes(MusicTheory::ChordPtr mt_Chord) {
        return !(mt_Chord == nullptr || mt_Chord->notes.size() == 0);
    }    

    static bool isScaleValid(MusicTheory::ScalePtr mt_Scale) {
        return !(mt_Scale == nullptr || mt_Scale->notes.size() == 0 || mt_Scale->getRoot() == nullptr);
    }    
    
    static MusicTheory::ChordPtr getDiatonicTriadForScaleAtRoot(shared_ptr<MusicTheory::Scale> scale, MusicTheory::NotePtr root) {
        // 8 % 7 = 1
        
        int posInScale = getPosInScaleForRoot(scale, root);
        
		int next_third_1_pos = (posInScale + 2) % scale->size();
		next_third_1_pos = std::min(next_third_1_pos, scale->size() - 1);
		next_third_1_pos = std::max(next_third_1_pos, 0);

		int next_third_2_pos = (posInScale + 4) % scale->size();
		next_third_2_pos = std::min(next_third_2_pos, scale->size() - 1);
		next_third_2_pos = std::max(next_third_2_pos, 0);
        
        MusicTheory::NotePtr next_third_1 = scale->notes[next_third_1_pos];
        MusicTheory::NotePtr next_third_2 = scale->notes[next_third_2_pos];
        
        deque<MusicTheory::NotePtr> diatonicTriad = {
            root,
            next_third_1,
            next_third_2
        };
        
        string chordNameShorthand = "C";
        vector<string> analyse = MusicTheory::Chord::analyse(diatonicTriad, true, false, false);
        
        if (analyse.size() > 0) {
            chordNameShorthand = analyse[0];
        }
        
        MusicTheory::ChordPtr diatonicChord = MusicTheory::Chord::fromShorthand(chordNameShorthand);
        return diatonicChord;
    }

    static vector<MusicTheory::ChordPtr> getDiatonicChordsForScale(string key, string scaleName) {
        shared_ptr<MusicTheory::Note> keyNote = MusicTheory::Note::create(key);
        vector<MusicTheory::ChordPtr> diatonicChordsForScale = vector<MusicTheory::ChordPtr>();
        shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::getScaleFromString(scaleName, keyNote); // We'll grab every 3rd from this scale to construct a chord!
        
        if (!keyNote || !scale) {
            cout << "Unable to find diatonic chords because scale: " << scaleName << " for key: " << key << " not found!";
            return vector<MusicTheory::ChordPtr>();
        }

        if (scale->notes.size() > 0) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[0])); // root chord
        if (scale->notes.size() > 1) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[1])); // ii chord
        if (scale->notes.size() > 2) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[2])); // iii chord
        if (scale->notes.size() > 3) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[3])); // iv chord
        if (scale->notes.size() > 4) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[4])); // v chord
        if (scale->notes.size() > 5) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[5])); // vi chord
        if (scale->notes.size() > 6) diatonicChordsForScale.insert(diatonicChordsForScale.end(), getDiatonicTriadForScaleAtRoot(scale, scale->notes[6])); // vii chord

        return diatonicChordsForScale;
    }
    
	static vector<MusicTheory::ChordPtr> getCircleOfFifthsChordsForScaleT1(string scaleName) { // SHARPS :: FLATS :: COF HALF CIRCLE

		vector<MusicTheory::NotePtr>  circleOfFifthsForScaleNotes = getCircleOfFifthsNotesForScaleT1(scaleName);
		vector<MusicTheory::ChordPtr> circleOfFifthsForScaleChords = vector<MusicTheory::ChordPtr>();

		for (int i = 0; i < (int)circleOfFifthsForScaleNotes.size(); i++) {
			MusicTheory::NotePtr n = circleOfFifthsForScaleNotes[i];

			shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::getScaleFromString(scaleName, n); // We'll grab every 3rd from this scale to construct a chord!

            
            // iv chord -- NON-IONIAN
            MusicTheory::NotePtr next_note_3 = scale->notes[3];
            MusicTheory::ChordPtr next_chord_for_scale_3 = getDiatonicTriadForScaleAtRoot(scale, next_note_3);
            //circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), next_chord_for_scale_3);
            
            // root chord
			MusicTheory::NotePtr root = scale->notes[0];
			MusicTheory::ChordPtr root_chord_for_scale = getDiatonicTriadForScaleAtRoot(scale, root);
            circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), root_chord_for_scale);
            
            // v chord v chord -- NON-IONIAN
            MusicTheory::NotePtr next_note_4 = scale->notes[4];
            MusicTheory::ChordPtr next_chord_for_scale_4 = getDiatonicTriadForScaleAtRoot(scale, next_note_4);
            //circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), next_chord_for_scale_4);
  
			

		}

		return circleOfFifthsForScaleChords;
	}

	static vector<string> getCircleOfFifthsChordsForScaleT1String(string scaleName) {
		vector<MusicTheory::ChordPtr> circleOfFifthsChordsForScale = getCircleOfFifthsChordsForScaleT1(scaleName);
		vector<string> circleOfFifthsChordsForScaleString = vector<string>();

		for (int i = 0; i < (int)circleOfFifthsChordsForScale.size(); i++) {
			MusicTheory::ChordPtr c = circleOfFifthsChordsForScale[i];
			string s = c->getName();
			circleOfFifthsChordsForScaleString.insert(circleOfFifthsChordsForScaleString.end(), circleOfFifthsChordsForScale[i]->getName());
		}
		return circleOfFifthsChordsForScaleString;
	}

	static vector<MusicTheory::ChordPtr> getCircleOfFifthsChordsForScaleT2(string scaleName) { // SHARPS :: FLATS :: COF HALF CIRCLE

		vector<MusicTheory::NotePtr>  circleOfFifthsForScaleNotes = getCircleOfFifthsNotesForScaleT1(scaleName);
		vector<MusicTheory::ChordPtr> circleOfFifthsForScaleChords = vector<MusicTheory::ChordPtr>();
		//  { "Dm", "Em", "Am", "Bm", "Em", "F#m", "Bm", "C#m", "F#m", "G#m", "C#m", "D#m",
	//	"G#m", "A#m", "Ebm", "Fm", "Bbm", "Cm", "Fm", "Gm", "Cm", "Dm", "Gm", "Am"


		// IONIAN : ["C", "D", "E", "F", "G", "A", "B"]     (both in C)
		// AEOLIAN : ["A", "B", "C", "D", "E", "F", "G"]

		for (int i = 0; i < (int)circleOfFifthsForScaleNotes.size(); i++) {
			MusicTheory::NotePtr n = circleOfFifthsForScaleNotes[i];

			shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::getScaleFromString(scaleName, n); // We'll grab every 3rd from this scale to construct a chord!

            MusicTheory::NotePtr root = scale->notes[0];
            
            // ii chord
            MusicTheory::NotePtr next_note_1 = scale->notes[1];
            MusicTheory::ChordPtr next_chord_for_scale_1 =  getDiatonicTriadForScaleAtRoot(scale, next_note_1);
            circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), next_chord_for_scale_1);
            
            // iii chord
            MusicTheory::NotePtr next_note_2 = scale->notes[2];
            MusicTheory::ChordPtr next_chord_for_scale_2 =  getDiatonicTriadForScaleAtRoot(scale, next_note_2);
            circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), next_chord_for_scale_2);
            
            // vi chord  -- NON-IONIAN
            MusicTheory::NotePtr next_note_5 = scale->notes[5];
            MusicTheory::ChordPtr next_chord_for_scale_5 =  getDiatonicTriadForScaleAtRoot(scale, next_note_5);
            //circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), next_chord_for_scale_5);
            

		}

		return circleOfFifthsForScaleChords;
	}

	static vector<string> getCircleOfFifthsChordsForScaleT2String(string scaleName) {
		vector<MusicTheory::ChordPtr> circleOfFifthsChordsForScale = getCircleOfFifthsChordsForScaleT2(scaleName);
		vector<string> circleOfFifthsChordsForScaleString = vector<string>();

		for (int i = 0; i < (int)circleOfFifthsChordsForScale.size(); i++) {
            MusicTheory::ChordPtr c = circleOfFifthsChordsForScale[i];
            string s = c->getName();
			circleOfFifthsChordsForScaleString.insert(circleOfFifthsChordsForScaleString.end(), circleOfFifthsChordsForScale[i]->getName());
		}
		return circleOfFifthsChordsForScaleString;
	}


	static vector<MusicTheory::ChordPtr> getCircleOfFifthsChordsForScaleT3(string scaleName) { // SHARPS :: FLATS :: COF HALF CIRCLE

		vector<MusicTheory::NotePtr>  circleOfFifthsForScaleNotes = getCircleOfFifthsNotesForScaleT1(scaleName);
		vector<MusicTheory::ChordPtr> circleOfFifthsForScaleChords = vector<MusicTheory::ChordPtr>();

		for (int i = 0; i < (int)circleOfFifthsForScaleNotes.size(); i++) {
			MusicTheory::NotePtr n = circleOfFifthsForScaleNotes[i];

			shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::getScaleFromString(scaleName, n); // We'll grab every 3rd from this scale to construct a chord!

            // vii chord
			MusicTheory::NotePtr vii = scale->notes[6];
			MusicTheory::ChordPtr vii_chord_for_scale = getDiatonicTriadForScaleAtRoot(scale, vii);

			circleOfFifthsForScaleChords.insert(circleOfFifthsForScaleChords.end(), vii_chord_for_scale);

		}
		return circleOfFifthsForScaleChords;
	}

	static vector<string> getCircleOfFifthsChordsForScaleT3String(string scaleName) {
		vector<MusicTheory::ChordPtr> circleOfFifthsChordsForScale = getCircleOfFifthsChordsForScaleT3(scaleName);
		vector<string> circleOfFifthsChordsForScaleString = vector<string>();

		for (int i = 0; i < (int)circleOfFifthsChordsForScale.size(); i++) {
			MusicTheory::ChordPtr c = circleOfFifthsChordsForScale[i];
			string s = c->getName();
			circleOfFifthsChordsForScaleString.insert(circleOfFifthsChordsForScaleString.end(), circleOfFifthsChordsForScale[i]->getName());
		}
		return circleOfFifthsChordsForScaleString;
	}

    // this is the 2nd tier of the color wheel found on google
    // static vector<string> getDefaultScaleDegreeHexColorsChromatic() {
    //     return {
    //         // Take from chromatic scale colors derived off hue circle degress
    //         /* C  */  "#EA4623",  /* C# */  "#E1712A",   /* D  */  "#EA9435",  /* D# */  "#F6C845",
    //         /* E  */  "#FBFA55",  /* F  */  "#95C441",   /* F# */  "#4FA937",  /* G  */  "#499DBB",
    //         /* G# */  "#2D5DAC",  /* A  */  "#15239C",   /* A# */  "#5B2B9D",  /* B  */  "#B63B78"
    //     };
    // }



    // custom color
    static vector<string> getDefaultScaleDegreeHexColorsChromatic() {
        return {
            // Take from chromatic scale colors derived off hue circle degress
            /* C  */  "#ff4848",  /* G  */  "#ff713b",   /* D  */  "#ffc752",  /* A  */  "#fbff52",
            /* E  */  "#9ed150",  /* B  */  "#50d16e",   /* F# */  "#00e9ff",  /* C# */  "#3f8fff",
            /* G# */  "#7c6dff",  /* D# */  "#b557ff",   /* A# */  "#fe85ff",  /* F  */  "#ff7ba0"
        };
    }


    static ofColor getDefaultScaleDegreeColor(int degree) {
        degree = std::min(11, degree);
        degree = std::max(0, degree);
        return Aquamarine::WidgetTheme::getColor_fromRGBAHex(
                getDefaultScaleDegreeHexColorsChromatic()[degree]
        );
    }

    static float getDefaultScaleDegreeHue(int degree) {
        return getDefaultScaleDegreeColor(degree).getHue();
    }    


    
    static vector<string> getChromaticScale() {
        //                               "Cb","Gb", "Db"
        return {"C", "Db", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B" };
    }
    
    static vector<string> getChromaticScaleSharps() {
        return {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    }
    
    static vector<string> getChromaticScaleFlats() {
        return {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    }
    
    static int getPositionInChromaticScaleForKey(string key) {
        vector<string> csS = getChromaticScaleSharps();
        vector<string> csF = getChromaticScaleFlats();
        
        for (int i=0; i<csS.size(); i++) {
            if (key == csS[i] || key == csF[i]) return i+1;
        }
        return -1;
    }
    
    
    static vector<string> getCircleOfFifths() {
        //                               "Cb","Gb", "Db"
        return {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};
    }
    
    static vector<string> getCircleOfFifthsSharps() {
        return {"C", "G", "D", "A", "E", "B", "F#", "C#", "G#", "D#", "A#", "F"};
    }
    
    static vector<string> getCircleOfFifthsFlats() {
        return {"C", "G", "D", "A", "E", "B", "Gb", "Db", "Ab", "Eb", "Bb", "F"};
    }
    
    static string getNextKey(string key, bool useCircleOfFifths, bool useSharps) {
        int pos = useCircleOfFifths ? getPositionInCircleOfFifthsForKey(key) : getPositionInChromaticScaleForKey(key);
        return useCircleOfFifths ? getNoteInCircleOfFifthsWithOffset(key, pos+1, useSharps) : getNoteInChromaticScaleWithOffset(key, pos+1, useSharps);
    }
    
    static string getPrevKey(string key, bool useCircleOfFifths, bool useSharps) {
        int pos = useCircleOfFifths ? getPositionInCircleOfFifthsForKey(key) : getPositionInChromaticScaleForKey(key);
        return useCircleOfFifths ? getNoteInCircleOfFifthsWithOffset(key, pos-1, useSharps) : getNoteInChromaticScaleWithOffset(key, pos-1, useSharps);
    }
    
    static int getNextKeyIndex(string key, bool useCircleOfFifths) {
        string nextKey = getNextKey(key, useCircleOfFifths, true);
        return useCircleOfFifths ? getPositionInCircleOfFifthsForKey(nextKey) : getPositionInChromaticScaleForKey(nextKey);
    }
    
    static int getPrevKeyIndex(string key, bool useCircleOfFifths) {
        string prevKey = getPrevKey(key, useCircleOfFifths, true);
        return useCircleOfFifths ? getPositionInCircleOfFifthsForKey(prevKey) : getPositionInChromaticScaleForKey(prevKey);
    }
    
    static int getPositionInCircleOfFifthsForKey(string key) {
        vector<string> cfS = getCircleOfFifthsSharps();
        vector<string> cfF = getCircleOfFifthsFlats();
        
        for (int i=0; i<cfS.size(); i++) {
            if (key == cfS[i] || key == cfF[i]) return i+1;
        }
        return -1;
    }
    
    static string getNoteInChromaticScaleForDegree(int degree, bool getSharp) {
        vector<string> csS = getChromaticScaleSharps();
        degree = std::min(degree, (int)csS.size());
        degree = std::max(degree, 1);
        if (getSharp) {
            return csS[degree-1];
        } else {
            vector<string> csF = getChromaticScaleFlats();
            return csF[degree-1];
        }
    }
    
    static string getNoteInCircleOfFifthsWithOffset(string key, int offset, bool useSharps) {
        int pos = getPositionInCircleOfFifthsForKey(key) + offset;
        
        if (pos > 12) pos = pos % 12;
        if (pos < 1) pos = 12 - pos;
        
        vector<string> cfS = getCircleOfFifthsSharps();
        vector<string> cfF = getCircleOfFifthsFlats();
        
        pos = std::min(pos, 12);
        pos = std::max(pos, 1);
        
        string newKey = useSharps ? cfS[pos - 1] : cfF[pos - 1];
        return newKey;
    }
    
    
    static string getNoteInChromaticScaleWithOffset(string key, int offset, bool useSharps) {
        int pos = getPositionInChromaticScaleForKey(key) + offset;
        
        if (pos > 12) pos = pos % 12;
        if (pos < 1) pos = 12 - pos;
        
        vector<string> cSS = getChromaticScaleSharps();
        vector<string> cSF = getChromaticScaleFlats();
        
        pos = std::min(pos, 12);
        pos = std::max(pos, 1);
        
        string newKey = useSharps ? cSS[pos - 1] : cSF[pos - 1];
        return newKey;
    }
    
    static ofColor getColorForKey(string key) {
        int degree = getPositionInCircleOfFifthsForKey(key);
        return getDefaultScaleDegreeColor(max(0, degree-1));
    }

    static ofColor getColorForKey(string key, int brightness) {
        ofColor keyColor = getColorForKey(key);
        keyColor.setBrightness(brightness);
        return keyColor; 
    }    
    
    static ofColor getColorForChord(string chordShorthand) {
        if (ofToLower(chordShorthand) == "unknown" || chordShorthand == "") return ofColor::black;
        MusicTheory::ChordPtr chord = MusicTheory::Chord::fromShorthand(chordShorthand);
        
        if (chord != nullptr) {
            return getColorForKey(chord->getRoot()->getDiatonicName());
        } else {
            return ofColor::black;
        }
    }
    
    /*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*
     Get the color for a Degree, use BRIGHTNESS to portray the Degree relative to the Key!
     ----------------------------------------------------------------
     Used in the context of a selected key. Shows the relative key color
     with brightness to portray the degree relative to the selected key. Put
     another way, c is always red, d yellow, etc but the brightness will vary
     *-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*/
    // ofColor getColorForKey_DegreeBrightness(string key, int degree) {
    
    static ofColor getColorForDegree_KeyBrightness(int degree, string key, bool highlighted) {
        degree = std::min(degree, 12);
        degree = std::max(degree, 1);
        ofColor color = getColorForKey(key);
        int degreeForKey = getPositionInCircleOfFifthsForKey(key);
        float brightness = getBrightnessForDegree(degree, highlighted);
        ofColor c = ofColor::fromHsb(color.getHue(), color.getSaturation(), brightness);
        return c;    
    }
    
    /*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*
     Get the color for a Key, use BRIGHTNESS to portray the Degree!
     ----------------------------------------------------------------
     Can be used regardless of wether a key is in focus or not
     and can be used by the end user to HARMONIZE, since the colors
     follow the hue circle and the notes follow the circle of fifths
     *-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*/
    static ofColor getColorForKey_DegreeBrightness(string key, int degree, bool highlighted) {
        ofColor color = getColorForKey(key);
        float brightness = getBrightnessForDegree(degree, highlighted);
        ofColor c = ofColor::fromHsb(color.getHue(), color.getSaturation(), brightness);
        return c;
    }
    
    /*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*
     Get a brightness for an Interval
     ----------------------------------------------------------------
     I, II, III IV, V, VI, VII are brightest, with lowering brightness for the more
     unusual intervals in chord / scale construction.
     *-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*/
    static float getBrightnessForDegree(int degree, bool highlighted) {
        
        int interval = degree - 1;
        ofColor c;
        
        float brightness = 0;
        
        switch(interval) {
                /* the normal stuff !!! */
            case vizTheory::DegreeName::majorUnison :
                brightness = 255.f;
                break;
            case vizTheory::DegreeName::perfectFourth :
                brightness = 210.0f;
                break;
            case vizTheory::DegreeName::perfectFifth :
                brightness = 240.0f;
                break;
            case vizTheory::DegreeName::majorThird :
                brightness = 240.0f;
                break;
            case vizTheory::DegreeName::majorSecond :
                brightness = 200.0f;
                break;
            case vizTheory::DegreeName::majorSixth :
                brightness = 160.0f;
                break;
            case vizTheory::DegreeName::majorSeventh :
                brightness = 180.0f;
                break;
                
                /* the interesting stuff !!! */
            case vizTheory::DegreeName::augmentedUnison_minorSecond :
                brightness = 150.0f;
                break;
            case vizTheory::DegreeName::augmentedSecond_minorThird :
                brightness = 150.0f;
                break;
            case vizTheory::DegreeName::augmentedFourth_minorFifth :
                brightness = 150.0f;
                break;
            case vizTheory::DegreeName::augmentedFifth_minorSixth :
                brightness = 150.0f;
                break;
            case vizTheory::DegreeName::augmentedSixth_minorSeventh :
                brightness = 150.0f;
                break;
            case vizTheory::DegreeName::dominantThirteenth :
                brightness = 150.0f;
                break;

            case -100 :
                brightness = 50.0f;
                break;

            case -200 :
                brightness = 25.0f;
                break;

            case -300 :
                brightness = 10.0f;
                break;                                
        }
        
        return highlighted ? brightness + 10.0f : brightness;
    }
    
    /*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*
     Focus on a scale
     ----------------------------------------------------------------
     Character notes in scales should be highlighted in extremely bright colours (
     eg magenta, bright blue, bright green and other notes/degrees range from black to gray.
     Idea being, the end user can focus on the CHARACTERISTICS of the scale rather than harmony.
     (harmony focus is viewing how the key colours blend!!!!)
     *-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*/
    static ofColor getColorForDegree_ScaleFocus(int degree, bool highlighted) {
        degree = std::min(degree, 12);
        degree = std::max(degree, 1);
        
        
        // TODO - load up scale metadata which defines character and focus notes
        // OVERRIDE the default Ionian (getBrightnessForDegree) brightness settings Uused
        // below for now)
        // Todo : user must pass in the scale, already loaded...

        float brightness = getBrightnessForDegree(degree, highlighted);
        ofColor c = ofColor::fromHsb(0, 0, 255 - brightness);
        
        return c;
    }
   
};



//--------------------------------------------------------------
class vizGuitar {
};

//--------------------------------------------------------------
class vizPiano {
};

class vizTheoryBase {

public:

    vizTheoryBase() {};

    virtual bool isNoteType() { return false; }
    virtual bool isChordType() { return false; }
    virtual bool isScaleType() { return false; }

    ofxXmlSettings getInstrumentRules() {
        return mInstrumentRules;
    }

    string getInstrumentRulesXMLString() {
        string retVal = "";
        TiXmlPrinter printer;
        TiXmlElement* rootElm = mInstrumentRules.doc.RootElement();
        if (rootElm != NULL) {
            rootElm->Accept( &printer );
            retVal = printer.CStr();    
        }
        return retVal;    
    } 

    void setInstrumentRules(ofxXmlSettings rules) {
        
        TiXmlElement* rootElm = rules.doc.RootElement();
        if (rootElm == NULL)  {
            return;
        } 

        TiXmlPrinter printer;
        rootElm->Accept( &printer );
        string newRulesXMLString = printer.CStr();    

        if (!mInstrumentRules.loadFromBuffer(newRulesXMLString)) {
            cout << "Error Loading new rules : \n" << newRulesXMLString << "\n";
        }   
    }

    void setInstrumentRules(string rules) {
        ofxXmlSettings rulesXML;  
        if (rulesXML.loadFromBuffer(rules.c_str())) {
            setInstrumentRules(rulesXML);
        }            
    }       

    void setInstrumentRule(string instrument, string tag, string value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    void setInstrumentRule(string instrument, string tag, int value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    void setInstrumentRule(string instrument, string tag,  double value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    string getInstrumentRule(string instrument, string tag, string defaultVal) {
        pushToInstrumentRulesTag(instrument);
        string val = mInstrumentRules.getValue(tag, defaultVal, 0);
        return val;
    }
    
    int getInstrumentRule(string instrument, string tag, int defaultVal) {
        pushToInstrumentRulesTag(instrument);
        int val = mInstrumentRules.getValue(tag, defaultVal, 0);
        return val;
    }
    
    double getInstrumentRule(string instrument, string tag,  double defaultVal) {
        pushToInstrumentRulesTag(instrument);
        double val = mInstrumentRules.setValue(tag, defaultVal, 0);
        return val;
    }


    void appendInstrumentRulesToXMLNode(ofxXmlSettings* xml, int index) {
        ofxXmlSettings rules = getInstrumentRules();
        TiXmlElement* rulesElm = rules.doc.RootElement();
        Aquamarine::Shared::appendXMLToTarget(rulesElm, xml, true);
    }

    bool getFboNeedsUpdate() {
        return fboNeedsUpdate;
    }

    void setFboNeedsUpdate(bool val) {
        fboNeedsUpdate = val;
    }

    void setFbo(ofFbo val) {
        fbo = val;
        fboNeedsUpdate = false;
    }

    ofFbo getFbo() {
        return fbo;
    }    

	virtual void saveFboToFile(string fileName, int width, int height) { 
		ofPixels pixels;
        pixels.allocate(width, height,  OF_IMAGE_COLOR_ALPHA);
		fbo.readToPixels(pixels);
		ofSaveImage(pixels, fileName, OF_IMAGE_QUALITY_BEST);     
	}

	virtual void saveFboToBuffer(ofBuffer &buffer, int width, int height) { 
		ofPixels pixels;
        pixels.allocate(width, height,  OF_IMAGE_COLOR_ALPHA);
		fbo.readToPixels(pixels);

        ofImage image;
        image.setFromPixels(pixels);
        image.save(buffer, OF_IMAGE_FORMAT_PNG, OF_IMAGE_QUALITY_BEST);
	}    


private:

    ofxXmlSettings mInstrumentRules = ofxXmlSettings();
    ofFbo fbo;
    bool fboNeedsUpdate = true;

    void pushToInstrumentRulesTag(string instrument) {
        
        
        while (mInstrumentRules.popTag() > 0); // pop to top!

/*
        if (!mInstrumentRules.bDocLoaded) {
            mInstrumentRules = ofxXmlSettings();
        }

        // Pop to root
        while(mInstrumentRules.getPushLevel() > 0) {
            mInstrumentRules.popTag();
        }
        */
        if (!mInstrumentRules.pushTag("rules")) {
            mInstrumentRules.addTag("rules");
            mInstrumentRules.pushTag("rules");
        }
        
        if (!mInstrumentRules.pushTag(instrument)) {
            mInstrumentRules.addTag(instrument);
            mInstrumentRules.pushTag(instrument);
        }
    }

    string getXMLString() {

        TiXmlElement* rootElm = mInstrumentRules.doc.RootElement();
        if (rootElm == NULL)  {
            return "";
        } 

        TiXmlPrinter printer;
        rootElm->Accept( &printer );
        return printer.CStr();    
    }

};

//--------------------------------------------------------------
class vizNote : public vizTheoryBase {
    
public:
    virtual bool isNoteType() override { return true; }
    virtual bool isChordType() override { return false; }
    virtual bool isScaleType() override { return false; }

    vizNote(string noteName, int noteOctave, int noteDegree, vector<string> noteTags, ofColor noteColor) :
    mNoteName(noteName)
    ,mNoteOctave(noteOctave)
    ,mNoteDegree(noteDegree)
    ,mNoteTags(noteTags)
    ,mNoteColor(noteColor){
        
        mt_Note = MusicTheory::Note::create(mNoteName);
        mt_Note->setOctave(noteOctave);
        mPositionInChromaticScale = vizTheory::getPositionInChromaticScaleForKey(noteName);  
        mMidiNote = vizMidiNote(mt_Note->toInt(), 100, 0.0f, vizMidiNote::getNoteValue(vizMidiNote::NoteValueName::quarterNote));     
    }
    
    vizNote(string noteName, int noteOctave, int noteDegree, vector<string> noteTags) :
    mNoteName(noteName)
    ,mNoteOctave(noteOctave)
    ,mNoteDegree(noteDegree)
    ,mNoteTags(noteTags)
    ,mNoteColor(ofColor::white){
        
        mt_Note = MusicTheory::Note::create(mNoteName);
        mt_Note->setOctave(noteOctave);
        mPositionInChromaticScale = vizTheory::getPositionInChromaticScaleForKey(mNoteName);
        mMidiNote = vizMidiNote(mt_Note->toInt(), 100, 0.0f, vizMidiNote::getNoteValue(vizMidiNote::NoteValueName::quarterNote));   
    }
    
    vizNote(string noteName, int noteOctave, int noteDegree) :
    mNoteName(noteName)
    ,mNoteOctave(noteOctave)
    ,mNoteDegree(noteDegree)
    ,mNoteTags(vector<string>{""})
    ,mNoteColor(ofColor::white){
        
        mt_Note = MusicTheory::Note::create(mNoteName);
        mt_Note->setOctave(noteOctave);
        mPositionInChromaticScale = vizTheory::getPositionInChromaticScaleForKey(mNoteName); 
        mMidiNote = vizMidiNote(mt_Note->toInt(), 100, 0.0f, vizMidiNote::getNoteValue(vizMidiNote::NoteValueName::quarterNote));               
    }
    
    vizNote(string xml)  {
        ofxXmlSettings noteXML = ofxXmlSettings();
        noteXML.loadFromBuffer(xml);
        
        if (!noteXML.tagExists("note")) return;
        
        mNoteName = noteXML.getAttribute("note", "name", "C");
        mNoteOctave = noteXML.getAttribute("note", "octave", 3);
        mt_Note = MusicTheory::Note::create(mNoteName);
        mt_Note->setOctave(mNoteOctave);
        mNoteColor = vizTheory::getColorForKey(mNoteName);
        mPositionInChromaticScale = vizTheory::getPositionInChromaticScaleForKey(mNoteName);
        mMidiNote = vizMidiNote(mt_Note->toInt(), 100, 0.0f, vizMidiNote::getNoteValue(vizMidiNote::NoteValueName::quarterNote));           
    }
    
    
    vizNote() : mNoteName(""), mNoteOctave(3), mNoteDegree(1), mNoteTags(vector<string>{""}) {}

    static vizNote noteFromString(string noteName) { // eg C3
        string key = "";
        string octave = "";

        if (noteName.length() > 2) {        
            key = noteName.substr(0, 2);
            octave = noteName.substr(2, 1);
        } else {
            key = noteName.substr(0, 1);
            octave = noteName.substr(1, 1);
        }
        return vizNote(ofToUpper(key), ofToInt(octave), 1);        
    }


    bool isEnharmonicallyEquivalent(string note) {
        if (getNoteName() == "") return false;
        int pos = vizTheory::getPositionInChromaticScaleForKey(getNoteNameNormalized());
        pos = std::min(pos, 12);
        pos = std::max(pos, 1);
        return (note == vizTheory::getChromaticScaleSharps()[pos-1] || note == vizTheory::getChromaticScaleFlats()[pos-1]);
    }
    
    string getNoteName() {
        return mNoteName;
    }
    
    string getNoteNameNormalized() {
        if (getNote() == nullptr) return "";
        return getNote()->getDiatonicName();
    }
    
    
    string getNoteNameRoman(string relativeRoot) {
        return MusicTheory::Interval::toRoman(getInterval(relativeRoot));
    }
    
    string getNoteNameRomanExtended(string relativeRoot) {
        string origRoman = getNoteNameRoman(relativeRoot);
        
        if (origRoman == "bII") {
            return "b9";
        } else if (origRoman == "II") {
            return "9";
        } else if (origRoman == "bIII" || origRoman == "#2") {
            return "#9";
        } else if (origRoman == "IV") {
            return "11";
        } else if (origRoman == "bV" || origRoman == "#4") {
            return "#11";
        } else if (origRoman == "bVI" || origRoman == "#5") {
            return "b13";
        } else if (origRoman == "VI" || origRoman == "bb7") {
            return "13";
        }
        return origRoman;
        
    }
    
    ofColor getNoteColor() {
        return mNoteColor;
    }
    
    void setNoteColor(ofColor val) {
        mNoteColor = val;;
    }
    
    int getNoteOctave() {
        return mNoteOctave;
    }
    
    void setNoteOctave(int val) {
        mNoteOctave = val;
    }
    
    int getInterval(string relativeRoot) {
        MusicTheory::NotePtr mt_RelativeNote = MusicTheory::Note::create(relativeRoot);
        if (mt_Note == nullptr || mt_RelativeNote == nullptr) return 0;
        int interval = MusicTheory::Interval::measure(mt_Note, mt_RelativeNote);
        return interval;
    }

    vizMidiNote& midiNote() {
        return mMidiNote;
    }

    
    vizNote getCalculatedNoteForOffset(int offsetFromNote, bool useSharp) {
        /*
         A note on octaves:
         https://music.stackexchange.com/questions/32715/what-do-the-terms-e2-a2-d3-g3-b3-e4-actually-mean
         
         They're just the "standard" numbers of those notes on a full sized 88 key piano: https://en.wikipedia.org/wiki/Piano_key_frequencies
         Interesting note: they run from C to C, not A to A. In other words the numbers start at C, not A. So they run as A0, B0, C1, D1... A1, B1, C2... etc.
         The octave number increases on the C, not the A. A slightly confusing convention!
         */
        
        int notePos = vizTheory::getPositionInChromaticScaleForKey(getNoteName()); // Starting at 'C'

        int octave = getNoteOctave();
        int additionalOctaves = (offsetFromNote + notePos-1) / 12;
        octave += additionalOctaves;

        string noteName = calculateNoteOffset(offsetFromNote, useSharp);
        ofColor c = vizTheory::getColorForKey(noteName);
        return vizNote(noteName, octave, offsetFromNote, vector<string>{}, c);
    }
    
    bool getIsNoteSharp() {
        vizTheory::NoteMode noteMode = vizTheory::getNoteMode(getNoteNameNormalized());
        return noteMode == vizTheory::NoteMode::SHARP;
    }
    
    string calculateNoteOffset(int offsetFromNote, bool useSharp) {
        if (getNoteName() == "") return "";
        int chromaticPositionFromC = vizTheory::getPositionInChromaticScaleForKey(getNoteName());
        int degree = ((chromaticPositionFromC + offsetFromNote) % 12);
        //  if (degree == 0 && offsetFromNote > 0) degree = 12;
        if (degree == 0) degree = 12;
        degree = std::min(degree, 12);
        return vizTheory::getNoteInChromaticScaleForDegree(degree, useSharp);
    }
    
    ofColor calculateNoteKeyColor(int offsetFromNote) {
        return vizTheory::getColorForKey(calculateNoteOffset(offsetFromNote, true));
    }
    
    ofColor calculateLabelColor(ofColor color) {
        return color;
    }
    
    MusicTheory::NotePtr getNote() {
        return mt_Note;
    }
    
    ofxXmlSettings* appendToXMLNode(ofxXmlSettings* noteXML, int index) {
        
        if (getNote() != nullptr) {
            noteXML->addTag("note");
            // string noteName, int noteOctave, int noteDegree, vector<string> noteTags, ofColor noteColor
            noteXML->setAttribute("note", "name", getNoteName(), index);
            noteXML->setAttribute("note", "octave", getNoteOctave(), index);
        }
        
        return noteXML;
    }
    
    void appendToXMLNode(ofxXmlSettings* noteXML) {
        appendToXMLNode(noteXML, 0);
    }
    
    ofxXmlSettings getXMLNode() {
        ofxXmlSettings noteXML = ofxXmlSettings();
        appendToXMLNode(&noteXML);
        return noteXML;
    }
    
    string getXML() {
        if (getNote() != nullptr) {
            string strXML;
            getXMLNode().copyXmlToString(strXML);
            return strXML;
        }
        return "";
    }

    void audition(int gmInstrument) {
        if (mNoteName == "") return;
        setIsPlaying(true);
        MidiShared::playNote(getNote(), gmInstrument);
        setIsPlaying(false);
    }
    
    vector<string> getNoteTags() {
        return mNoteTags;
    }
    
    void setNoteTags(vector<string> val) {
         mNoteTags = val;
    }
    
    string getNoteTagsString(string seperator) {
        string tmp = "";
        if(mNoteTags.size() > 0) {
            for (int i=0; i< mNoteTags.size(); i++) {
                if (i > 0) tmp += seperator;
                tmp += mNoteTags[i];
            }
            return tmp;
        }
        return "";
    }
    
    bool getIsExtended() {
        return mIsExtended;
    }
    
    void setIsExtended(bool val) {
        mIsExtended = val;
    }
    
    vizTheory::NoteMode getNoteMode() {
        return vizTheory::getNoteMode(getNoteName());
    }

    int getPositionInChromaticScale() {
        return mPositionInChromaticScale;
    }

    void setSequenceNumber(int sequenceNumber) {
        mSequenceNumber = sequenceNumber;
    }

    int getSequenceNumber() {
        return mSequenceNumber;
    }

    static float getDurationForWholeNote(int bpm) {
        return 60000 / bpm;
    }

    static float getDurationForHalfNote(int bpm) {
        return 60000 / bpm / 2;
    }    

    static float getDurationForQuarterNote(int bpm) {
        return 60000 / bpm / 4;
    }

    static float getDurationForEighthNote(int bpm) {
        return 60000 / bpm / 8;
    }  

    static float getDurationFor32ndNote(int bpm) {
        return 60000 / bpm / 32;
    }    

    void setIsPlaying(int isPlaying) {
        mIsPlaying = isPlaying;
    }

    int getIsPlaying() {
        return mIsPlaying;
    }        
    
    
private:
    string mNoteName = "";
    bool mIsExtended = false;
    int mNoteOctave;
    int mNoteDegree;
    vector<string> mNoteTags;
    ofColor mNoteColor;
    MusicTheory::NotePtr mt_Note;
    int mPositionInChromaticScale = 0;
    vizMidiNote mMidiNote;
    int mSequenceNumber = 0;
    bool mIsPlaying = false;
};

//--------------------------------------------------------------
class vizChord  : public vizTheoryBase  {
    
public:

    virtual bool isNoteType() override { return false; }
    virtual bool isChordType() override { return true; }
    virtual bool isScaleType() override { return false; }

    vizChord(string chordName) : mChordName(chordName)  {
        mt_Chord = MusicTheory::Chord::getChordFromString(chordName);        
        if (MusicTheory::Chord::isValid(mt_Chord)) {
            mChordColor = vizTheory::getColorForChord(chordName);        
            mNotes = getNormalizedNotesForChord();
        } else {
            chordName = "";
        }
    }

    vizChord(string chordName, vector<vizNote> notes, bool normalize) : mChordName(chordName), mNotes(notes) {
        
        mChordColor = vizTheory::getColorForChord(chordName);
        
        if (ofToLower(mChordName) == "unknown" || mChordName == "") return;
        mt_Chord = MusicTheory::Chord::create(mChordName);
        
        if (normalize) {
            mNotes = getNormalizedNotesForChord();
        }
        
    }
    
    vizChord(string xml, bool normalize)  {
        ofxXmlSettings chordXML = ofxXmlSettings();
        chordXML.loadFromBuffer(xml);

        if (!chordXML.tagExists("chord")) return;

        chordXML.pushTag("chord");
        
        mChordName = chordXML.getValue("name", "");

        mIsUserDefinedPoints = chordXML.getValue("userDefinedPoints", false);
        mUserDefinedName = chordXML.getValue("userDefinedName", "");

        if (!shorthandHasValidRoot(mChordName)) {
            return;
        }

        mt_Chord = MusicTheory::Chord::create(mChordName);
        
        
        int notes = chordXML.getNumTags("note");
        
        vector<vizNote> chordNotes = vector<vizNote>();
        
        for(int i = 0; i < notes; i++){
            string noteName = chordXML.getAttribute("note", "name", "C", i);
            
            vizNote noteToAdd = vizNote(
                                        noteName,
                                        chordXML.getAttribute("note", "octave", 3, i), 0, vector<string>{},
                                        vizTheory::getColorForKey(noteName)
                                        );
            chordNotes.push_back(noteToAdd);
        }
        

        // Rules
        TiXmlElement* rootElm = chordXML.doc.RootElement();
        TiXmlElement* rulesElm = rootElm->FirstChildElement("rules");
        if (rulesElm != NULL) {
            TiXmlPrinter printer;
            rulesElm->Accept( &printer );
            string rulesXMLStr = printer.CStr();
            
            ofxXmlSettings rulesXML;
            if (rulesXML.loadFromBuffer(rulesXMLStr)) {
                setInstrumentRules(rulesXML);
            }
        }


        
        if (normalize) {
           mNotes = chordNotes;
           mNotes = getNormalizedNotesForChord();
            
        } else {
           mNotes = chordNotes;
        }
        
        
        setChordColor(vizTheory::getColorForChord(getChordName()));
        
    }
    
    
    vizChord() : mChordName(""), mChordTags(vector<string>{""}), mChordColor(ofColor::white) { }

    vector<vizNote> getNormalizedNotesForChord() {
        
        vector<vizNote> chordNotes = mNotes;
        
        vizNote rootNote(vizTheory::extractRootFromChord(mChordName), 3, 0, vector<string>{});
        vizNote lowestChordRootNote = vizChord::findLowestRootNote(rootNote, chordNotes);
        
        for (vizNote &currNote:chordNotes) {
            bool isExtended = vizChord::calculateIfExtendedNote(lowestChordRootNote, chordNotes, currNote, false, false); // rule_strictExtendedNotes
            currNote.setNoteOctave(isExtended ? 4 : 3); // Normalize note octaves...
            currNote.setIsExtended(isExtended);
        }
        
        
        vector<vizNote> normalizedNotes = vector<vizNote>();
        
        for (int degree=0; degree<=11; degree++) {
            for (vizNote currNote:chordNotes) {
                if (currNote.getNoteOctave() == 3 && rootNote.getInterval(currNote.getNoteName()) == degree) {
                    normalizedNotes.push_back(currNote);
                }
            }
        }
        
        for (int degree=0; degree<=11; degree++) {
            for (vizNote currNote:chordNotes) {
                if (currNote.getNoteOctave() == 4 && rootNote.getInterval(currNote.getNoteName()) == degree) {
                    normalizedNotes.push_back(currNote);
                }
            }
        }
        
        return normalizedNotes;
        
    }

    bool isMajor() {
        if (mChordName == "" || mt_Chord == nullptr) return "";
        return mt_Chord->isMajor();
    }

    bool isMinor() {
        if (mChordName == "" || mt_Chord == nullptr) return "";
        return mt_Chord->isMinor();
    }    
    
    bool shorthandHasValidRoot(string chordName) {
        string rootRaw = ofToUpper(MusicTheory::Chord::getRootNote(chordName));
        
        if (rootRaw.length() == 0) return false;
        string root = rootRaw.substr(0, 1);
        
        if (root == "A" || root == "B" || root == "C" || root == "D" || root == "E" || root == "F" || root == "G") {
            return true;
        } else {
            return false;
        }
    }
    
    bool getIsUserDefinedPoints() {
        return mIsUserDefinedPoints;
    }

    void setIsUserDefinedPoints(bool val) {
        mIsUserDefinedPoints = val;
    }

    string getChordName_UserDefined() {
        return mUserDefinedName;
    }

    void setChordName_UserDefined(string val) {
        mUserDefinedName = val;
    }    

    string getChordName() {
        if (mChordName == "" || mt_Chord == nullptr) return "";
        return mt_Chord->getName();
    }
    
    string getChordNameSimplified(bool shortenMaj) {
        if (mChordName == "" || mt_Chord == nullptr) return "";
        string chordName = mt_Chord->getName();
        ofStringReplace(chordName, "M", shortenMaj ? "" : "Maj");
        return chordName;
    }

    string getChordNameForDisplay(bool simplified) {
        if (getChordName_UserDefined() != "") {
            return getChordRootNote().getNoteName() + getChordName_UserDefined();
        } else {
            return simplified ? getChordNameSimplified(true) : getChordName();
        }
    }    
    
    string getChordNameRoman(string rootChord) {
        
        //, bool includeChordSymbol
        // make minor lowercase
        
        MusicTheory::ChordPtr mt_RelativeChord = MusicTheory::Chord::create(rootChord);
        int interval = MusicTheory::Interval::measure(mt_RelativeChord->getRoot(), mt_Chord->getRoot());
        
        return MusicTheory::Interval::toRoman(interval) + mt_Chord->getChordSymbol();
    }
    
    string getChordRoot() {
        if (mt_Chord == nullptr) return "";
        return mt_Chord->getRoot()->getName();
    }
    
    bool isChordValid() {
        return !(mt_Chord == nullptr || mt_Chord->notes.size() == 0 || ofToLower(mt_Chord->getName()) == "unknown" || mt_Chord->getName() == "Invalid chord" || mt_Chord->getRoot() == nullptr);
    }

    bool chordHasNotes() {
        return !(mt_Chord == nullptr || mt_Chord->notes.size() == 0);
    }       
    
    vizNote getChordRootNote() {
        if (!isChordValid()) return vizNote("C", 3, 0, vector<string>{""});
        return vizNote(mt_Chord->getRoot()->getDiatonicName(), mt_Chord->getOctave(), 0);
    }

    int getInterval(string relativeChord) {
        MusicTheory::ChordPtr mt_RelativeChord = MusicTheory::Chord::create(relativeChord);
        int interval = MusicTheory::Interval::measure(mt_Chord->getRoot(), mt_RelativeChord->getRoot());
        return interval;
    }
    
    bool matchesChord(vizChord chord, bool exactNoteNameMatch, bool exactOctaveMatch) {
        
        vector<vizNote> notes = getNotes();
        vector<vizNote> chordToCheckNotes = chord.getNotes();
        
        if (notes.size() != chordToCheckNotes.size()) return false;
        
        for (int i = 0; i < chordToCheckNotes.size(); i++) {
            
            if (exactNoteNameMatch) {
                if (chordToCheckNotes[i].getNoteName() != notes[i].getNoteName()) {
                    return false;
                }
            } else {
                if (!chordToCheckNotes[i].isEnharmonicallyEquivalent(notes[i].getNoteNameNormalized())) {
                    return false;
                }
            }

            if (chordToCheckNotes[i].getNoteOctave() != notes[i].getNoteOctave()) {
                return false;
            }
        }
        return true;
    }
    
    MusicTheory::ChordPtr getChord() {
        return mt_Chord;
    }
    
    vector<vizNote> getNotes() {
        
        if (mNotes.size() > 0) {
            return mNotes;
        } else {
            mNotes = calculateNotes(true);
            return mNotes;
        }
    }
 
    vector<vizNote> calculateNotes(bool normalize) {
        vector<vizNote> notes = vector<vizNote>();
        
        if (getChord() != nullptr) {
            deque<MusicTheory::NotePtr> chordNotes = getChord()->getAllNotes();
            
            for (int i = 0; i < chordNotes.size(); i++) {
                vizNote noteToAdd = vizNote(chordNotes[i]->getDiatonicName(), chordNotes[i]->getOctave(), 0, vector<string>{});
                notes.push_back(noteToAdd);
            }
            
            vizNote rootNote(vizTheory::extractRootFromChord(getChord()->getName()), 3, 0, vector<string>{});
            vizNote lowestChordRootNote = vizChord::findLowestRootNote(rootNote, notes);
            
            for (vizNote &currNote:notes) {
                bool isExtended = vizChord::calculateIfExtendedNote(lowestChordRootNote, notes, currNote, false, false);
                if (normalize) currNote.setNoteOctave(isExtended ? 4 : 3); // Normalize note octaves...
                currNote.setIsExtended(isExtended);
            }
            
        }
        return notes;
    }
    
    string getXML() {
        
        if (getChord() != nullptr) {
            
            ofxXmlSettings chordXML = ofxXmlSettings();
            chordXML.addTag("chord");
            chordXML.pushTag("chord");
            chordXML.addValue("name", getChordName());

            if (getChordName_UserDefined() != "") {
                chordXML.addValue("userDefinedName", getChordName_UserDefined()); 
            } 

            if (getIsUserDefinedPoints()) {
                chordXML.addValue("userDefinedPoints", true);
            }             
            
            vector<vizNote> notes = getNotes();
            for (int i = 0; i < notes.size(); i++) {
                notes[i].appendToXMLNode(&chordXML, i);
            }
            
            // Rules
            appendInstrumentRulesToXMLNode(&chordXML, 0);

            chordXML.popTag();
            
            string strXML;
            chordXML.copyXmlToString(strXML);
            return strXML;
        }
        
        return "";
    }
    
    
    void appendToXMLNode(ofxXmlSettings* chordXML) {
        appendToXMLNode(chordXML, 0);
    }
    
    void appendToXMLNode(ofxXmlSettings* chordXML, int index) {
        
        if (getChord() != nullptr) {
            chordXML->addTag("chord");
            chordXML->pushTag("chord", index);
            chordXML->addValue("name", getChordName());

            if (getChordName_UserDefined() != "") {
                chordXML->addValue("userDefinedName", getChordName_UserDefined()); 
            } 

            if (getIsUserDefinedPoints()) {
                chordXML->addValue("userDefinedPoints", true);
            }               
            
            vector<vizNote> notes = getNotes();
            for (int i = 0; i < notes.size(); i++) {
                notes[i].appendToXMLNode(chordXML, i);
            }

            // Rules
            appendInstrumentRulesToXMLNode(chordXML, index);

            chordXML->popTag();

        }
    }
    
    ofColor getChordColor() {
        return mChordColor;
    }
    
    void setChordColor(ofColor color) {
        mChordColor = color;
    }

    void audition(int gmInstrument, int bpm = 120) {
        if (mChordName == "") return;

        setIsPlaying(true);

        vizNote rootNote = getChordRootNote();
        string rootName = rootNote.getNoteNameNormalized();

        int noteDuration = vizNote::getDurationForEighthNote(bpm);
        int notesPlayed = 0;

        for (int seq=0; seq <=5; seq++) { 
// 0-1 sequence bug
// add velocity
// add duration
/*
             { got to play in another thread !!
                    fretPoint.highlightPath.setColor(getSelectedFontColor(getSelectedKey().getNoteName()));

*/

            bool anyNotePlayed = false;
            for (int i = 0; i < mNotes.size(); i++) {
                if (mNotes[i].getSequenceNumber() == seq) {
                    int velocity = (mNotes[i].isEnharmonicallyEquivalent(rootName) ? 100 : 90); // 100 : 80);
                    if (seq > 0) velocity = velocity - 5; // softer notes for sequenced....
                    mNotes[i].setIsPlaying(true);
                    MidiShared::playNote(mNotes[i].getNote(), velocity, gmInstrument);
                    ofSleepMillis(noteDuration);
                    mNotes[i].setIsPlaying(false);
                    notesPlayed++;      
                    anyNotePlayed = true;              
                };
            }
            if (anyNotePlayed) ofSleepMillis(vizNote::getDurationForWholeNote(bpm));            
            if (notesPlayed == mNotes.size()) {
                setIsPlaying(false);
                return;
            }

            // ofSleepMillis(150);

        }

        setIsPlaying(false);        

    }

    static vizNote findLowestRootNote(vizNote rootNote, vector<vizNote> notes) {
        vizNote noteToReturn = rootNote;
        
        for (vizNote currNote:notes) {
            if (currNote.isEnharmonicallyEquivalent(rootNote.getNoteNameNormalized()) && currNote.getNoteOctave() < noteToReturn.getNoteOctave()) {
                noteToReturn = currNote;
            }
        }
        
        return noteToReturn;
    }

    // static vector<vizChord> getChords(vector<vizNotes>) {
    // }

    static vector<vizChord> getSynonymChords(vizChord chord) {
        if (chord.chordHasNotes()) {
            vector<string> analyse = MusicTheory::Chord::analyse(chord.getChord()->getAllNotes(), true, true, false);
            vector<vizChord> chords = vector<vizChord>();
            for(int i = 0;i<analyse.size();i++){
                //cout<<"Opt "<<i<<": "<<analyse[i]<<endl;
                vizChord chord = vizChord(analyse[i]);
                chords.push_back(chord);
            }
            return chords;
        } else {
            return vector<vizChord>();
        } 
    }   //in saved - why ceg not C ????

    static vector<string> searchChords(string context, int maxResults = 10) {
        context = ofToLower(context); 
        ofStringReplace(context, " ", ""); 

        vector<string> results;

        typedef map<string, string>::iterator it_type;
        for(it_type iterator = MusicTheory::ChordLookup.begin(); iterator != MusicTheory::ChordLookup.end(); iterator++) {
            string s = ofTrim(ofToLower(iterator->second));

            if (s.rfind(context, 0) == 0) { // match
                results.push_back(ofTrim(iterator->first));
            }
            if (results.size() >= maxResults) return results;
        }

        return results;     
    }    

    static vector<vizChord> getSynonymChordsFromChordXML(string xml) {
        vizChord chord = vizChord(xml, true);
        return getSynonymChords(chord);
    }        

    static bool doesContainDegree(vizNote chordRootNote, int degree, vector<vizNote> notes) {
        for (vizNote currNote:notes) {
            if (chordRootNote.getInterval(currNote.getNoteName()) == degree) {
                return true;
            }
        }
        return false;
    }
    
    static int getCountOfDegree(vizNote chordRootNote, int degree, vector<vizNote> notes) {
        int countOfDegree = 0;
        for (vizNote currNote:notes) {
            if (chordRootNote.getInterval(currNote.getNoteName()) == degree) {
                countOfDegree++;
            }
        }
        return countOfDegree;
    }

    static vector<vizNote> getDistinctNotes(vector<vizNote> notes) {
        vector<vizNote> countedNotes = {};
        for (vizNote currNote:notes) {
            bool found = false;
            for (vizNote countedNote:countedNotes) {
                if (countedNote.isEnharmonicallyEquivalent(currNote.getNoteNameNormalized())) {
                    found = true;
                }
            }
            if (!found) countedNotes.push_back(currNote);
        }
        return countedNotes;
    }

    static int numDistinctNotes(vector<vizNote> notes) {
        vector<vizNote> countedNotes = getDistinctNotes(notes);
        return countedNotes.size();
    }

    static bool noteFound(vizNote note, vector<vizNote> notes) {
        string noteNameNormalized = note.getNoteNameNormalized();
        for (vizNote currNote:notes) {
            if (currNote.getNoteOctave() == note.getNoteOctave() 
                && currNote.isEnharmonicallyEquivalent(noteNameNormalized)) return true;
        }
        return false;
    }    

    static vector<vizNote> getDistinctNotesAscending(vizNote rootNote, vector<vizNote> notes) {
        vector<vizNote> distinctNotes = getDistinctNotes(notes);
        vector<vizNote> countedNotes = {};

        vizNote intervalToAdd;

        while(distinctNotes.size() > 0) {
            int indexToErase = 0;
            int lowestIntervalFound = 1000;            
            for (int i=0; i< distinctNotes.size(); i++) {
                vizNote currNote = distinctNotes[i];
                int interval = rootNote.getInterval(currNote.getNoteName());
                if (interval <= lowestIntervalFound) {
                    intervalToAdd = currNote;
                    lowestIntervalFound = interval;
                    indexToErase = i;
                }
            }              
            countedNotes.push_back(intervalToAdd);
            distinctNotes.erase(distinctNotes.begin() + indexToErase);
        }

        return countedNotes;
    }    
    
    static bool calculateIfExtendedNote(vizNote chordRootNote, vector<vizNote> notesAdded, vizNote noteToAdd, bool strictOctave, bool simplifiedChordCalculation) {
        
        int rootOctave = chordRootNote.getNoteOctave();
        int noteToAddInterval = chordRootNote.getInterval(noteToAdd.getNoteName());

        if (simplifiedChordCalculation) {
            if (noteToAddInterval == vizTheory::DegreeName::majorUnison ||
                noteToAddInterval == vizTheory::DegreeName::majorThird ||
                noteToAddInterval == vizTheory::DegreeName::perfectFifth ||
                noteToAddInterval == vizTheory::DegreeName::augmentedSixth_minorSeventh ||
                noteToAddInterval == vizTheory::DegreeName::majorSeventh) return false;
        }

        vizNote lowestRootOctaveNote = vizChord::findLowestRootNote(chordRootNote, notesAdded);

        vector<vizNote> distinctNotes = getDistinctNotes(notesAdded);

        if (distinctNotes.size() > 3 && noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave()) {
            // --------------------------------------
            //    Extended / Complex chords
            // --------------------------------------            
            if     (noteToAddInterval == vizTheory::DegreeName::majorUnison)                 { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorUnison, notesAdded) > 1; }
            else if(noteToAddInterval == vizTheory::DegreeName::majorThird)                  { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorThird, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::perfectFifth)                { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::perfectFifth, notesAdded) > 1; }
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedSixth_minorSeventh) { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedSixth_minorSeventh, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::majorSeventh)                { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSeventh, notesAdded) > 1; } 


            else if(noteToAddInterval == vizTheory::DegreeName::augmentedUnison_minorSecond) { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedUnison_minorSecond, notesAdded) > 0; }                
            else if(noteToAddInterval == vizTheory::DegreeName::majorSecond)                 { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSecond, notesAdded) > 0; }                
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedSecond_minorThird)  { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedSecond_minorThird, notesAdded) > 0 
                                                                                                   && getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorThird, notesAdded) > 0; } // It's only a Sharp 9 if chord has Maj 3rd

            else if(noteToAddInterval == vizTheory::DegreeName::perfectFourth)               { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::perfectFourth, notesAdded) > 0; } 
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedFourth_minorFifth)  { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedFourth_minorFifth, notesAdded) > 0; } 
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedFifth_minorSixth)   { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedFifth_minorSixth, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::majorSixth)                  { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSixth, notesAdded) > 0; } 
            else if(noteToAddInterval == vizTheory::DegreeName::dominantThirteenth)          { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::dominantThirteenth, notesAdded) > 0; } 
            else { return true; }

        }  else {
            // --------------------------------------
            //    Less complex chords
            // --------------------------------------            
            if     (noteToAddInterval == vizTheory::DegreeName::majorUnison)                 { return noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorUnison, notesAdded) > 1; }
            else if(noteToAddInterval == vizTheory::DegreeName::majorThird)                  { return noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorThird, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::perfectFifth)                { return noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::perfectFifth, notesAdded) > 1; }
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedSixth_minorSeventh) { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedSixth_minorSeventh, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::majorSeventh)                { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSeventh, notesAdded) > 1; } 


            else if(noteToAddInterval == vizTheory::DegreeName::augmentedUnison_minorSecond) { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedUnison_minorSecond, notesAdded) > 0; }                
            else if(noteToAddInterval == vizTheory::DegreeName::majorSecond)                 { return distinctNotes.size() > 3 && noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSecond, notesAdded) > 1; }                
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedSecond_minorThird)  { return distinctNotes.size() > 3 && noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedSecond_minorThird, notesAdded) > 1; } // Only extended if the chord has > 3 notes
            else if(noteToAddInterval == vizTheory::DegreeName::perfectFourth)               { return distinctNotes.size() > 3 && noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() && getCountOfDegree(chordRootNote, vizTheory::DegreeName::perfectFourth, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedFourth_minorFifth)  { return distinctNotes.size() > 3 && noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() &&  getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedFourth_minorFifth, notesAdded) > 0; } 
            else if(noteToAddInterval == vizTheory::DegreeName::augmentedFifth_minorSixth)   { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::augmentedFifth_minorSixth, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::majorSixth)                  { return noteToAdd.getNoteOctave() > lowestRootOctaveNote.getNoteOctave() &&  getCountOfDegree(chordRootNote, vizTheory::DegreeName::majorSixth, notesAdded) > 1; } 
            else if(noteToAddInterval == vizTheory::DegreeName::dominantThirteenth)          { return getCountOfDegree(chordRootNote, vizTheory::DegreeName::dominantThirteenth, notesAdded) > 0; } 
            else { return true; }
        }

        return false;
    }

    string saveToMidiFile() {  
        vizNote rootNote = getChordRootNote();

        string proposedFileName = ofFilePath::join(APP_CONSTANTS::APPLICATION_CACHE_FOLDER(), vizTheory::extractFileSystemSafeName(
            getChordName_UserDefined() != "" ? rootNote.getNoteName() + getChordName_UserDefined() : getChordNameSimplified(false)) + ".mid");   

        vector<vizNote> notes = getNotes();        
        
        int starttime = 0;
        int duration = 16;   // (4=1/4 beat (32), 8=1/2 beat (16th), 16 = 1 beat, 32 = 2 beat, 48 = 3 beat, 64=1bar)
        int velocity = 100;

        smf::MidiFile midifile;
        int track   = 0;
        int channel = 0;
        int instr   = 0; //options.getInteger("instrument");
        midifile.addTimbre(track, 0, channel, instr);

        int tpq     = midifile.getTicksPerQuarterNote();


        for (vizNote note:notes) {
            int starttick = starttime;
            int key       = note.getNote()->toInt();
            //int endtick   = starttick + duration;
            int endtick   = starttick + int((float)duration / 16.0f * tpq);

            // Emphasise the root note a bit
            note.midiNote().setVelocity((note.getNoteNameNormalized() == rootNote.getNoteNameNormalized() ? 100 : 80));

            velocity = note.midiNote().getVelocity();
            midifile.addNoteOn (track, starttick, channel, key, velocity);
            midifile.addNoteOff(track, endtick,   channel, key);
        }
        midifile.sortTracks();  // Need to sort tracks since added events are
                                // appended to track in random tick order.
        // Write it!
        midifile.write(proposedFileName);

        return proposedFileName;
    }

    void setIsPlaying(bool isPlaying) {
        mIsPlaying = isPlaying;
    }

    bool getIsPlaying() {
        return mIsPlaying;
    }        
    
private:    
    vector<vizNote> mNotes;
    string mChordName = "";
    bool mIsUserDefinedPoints = false;
    string mUserDefinedName = "";
    vector<string> mChordTags;
    ofColor mChordColor;
    MusicTheory::ChordPtr mt_Chord;
    bool mIsPlaying = false;
   
};



//--------------------------------------------------------------
class vizScale  : public vizTheoryBase  {
    
    
public:
    virtual bool isNoteType() override { return false; }
    virtual bool isChordType() override { return false; }
    virtual bool isScaleType() override { return true; }

    vizScale() { }
    
    vizScale(string scaleName) : mScaleName(scaleName) {
        resolvePrettyName() ;
    }

    vizScale(string key, string scaleName, int octave) : mScaleName(scaleName) {
        if (ofToLower(mScaleName) == "unknown" || mScaleName == "") return;
        mKey = vizNote(key, octave, 1);
        mt_Scale = MusicTheory::Scale::scaleFromDictionary(scaleName, mKey.getNote());

        if (mt_Scale == nullptr || mt_Scale->name == "" || mt_Scale->name == "unknown") return;
        mNotes = getNotesForScale(key, mt_Scale->name);
        mScaleNamePretty = mt_Scale->prettyName;
    } 

    // Use this for instruments, where not repetition may be involved!
    vizScale(string key, string scaleName, vector<vizNote> notes) : mScaleName(scaleName), mNotes(notes) {
        if (ofToLower(mScaleName) == "unknown" || mScaleName == "") return;
        mKey = vizNote(key, 3, 1);
        mt_Scale = MusicTheory::Scale::scaleFromDictionary(scaleName, mKey.getNote());

        if (mt_Scale == nullptr || mt_Scale->name == "" || mt_Scale->name == "unknown") return;
        mScaleNamePretty = mt_Scale->prettyName;
    } 

    vizScale(string xml, bool normalize) :  vizScale(xml, "scale", normalize)  { }


    vizScale(string xml, string topLevelTagName, bool normalize)  {
        ofxXmlSettings scaleXML = ofxXmlSettings();
        scaleXML.loadFromBuffer(xml);

        if (!scaleXML.tagExists(topLevelTagName)) return;

        scaleXML.pushTag(topLevelTagName);

        mScaleName = scaleXML.getValue("name", "ionian");
        mScaleNamePretty = scaleXML.getValue("prettyName", mScaleName);

        mKey = vizNote(scaleXML.getValue("key", "C"), 3, 1);
        mt_Scale = MusicTheory::Scale::scaleFromDictionary(mScaleName, mKey.getNote());
      
        int notes = scaleXML.getNumTags("note");
        vector<vizNote> scaleNotes = vector<vizNote>();

        if (notes > 0) {
            for(int i = 0; i < notes; i++){
                string noteName = scaleXML.getAttribute("note", "name", "C", i);
                
                vizNote noteToAdd = vizNote(
                                            noteName,
                                            scaleXML.getAttribute("note", "octave", 3, i), 0, vector<string>{},
                                            vizTheory::getColorForKey(noteName)
                                            );
                scaleNotes.push_back(noteToAdd);
            }
        } else {
            scaleNotes = getNotesForScale(mKey.getNoteNameNormalized(), mScaleName, 3);
        }


       // Rules
        TiXmlElement* rootElm = scaleXML.doc.RootElement();
        TiXmlElement* rulesElm = rootElm->FirstChildElement("rules");
        if (rulesElm != NULL) {
            TiXmlPrinter printer;
            rulesElm->Accept( &printer );
            string rulesXMLStr = printer.CStr();
            
            ofxXmlSettings rulesXML;
            if (rulesXML.loadFromBuffer(rulesXMLStr)) {
                setInstrumentRules(rulesXML);
            }
        }        
        
        
        if (normalize) {
            // do nothing for now
           mNotes = scaleNotes;
            
        } else {
           mNotes = scaleNotes;
        }
     }

    bool matchesScale(vizScale scale) {
        return getName() == scale.getName() && getKey().getNoteName() == scale.getKey().getNoteName();
    }

    vector<vizNote> getNotes() {
        return mNotes;
    }

    string getXML() {

        if (getName() != "" && getName() != "unknown") {
            
            ofxXmlSettings scaleXML = ofxXmlSettings();
            scaleXML.addTag("scale");
            scaleXML.pushTag("scale");
            scaleXML.addValue("name", getName());
            scaleXML.addValue("prettyName", getNamePretty());
            scaleXML.addValue("key", getKey().getNoteName());
            
            vector<vizNote> notes = getNotes();
            if (notes.size() > 0) {
                for (int i = 0; i < notes.size(); i++) {
                    notes[i].appendToXMLNode(&scaleXML, i);
                }                
            }

            // Rules
            appendInstrumentRulesToXMLNode(&scaleXML, 0);

            scaleXML.popTag();
            
            string strXML;
            scaleXML.copyXmlToString(strXML);
            return strXML;
        }
        return "";
    }


    static vector<vizChord> getDiatonicChordsForScale(string key, string scaleName) {
        vector<MusicTheory::ChordPtr> chords = vizTheory::getDiatonicChordsForScale(key, scaleName);
 
        vector<vizChord> diatonicChordsForScale = vector<vizChord>();
        int incOctave = 0;
        for (int c=0; c<chords.size(); c++) {
            
            deque<MusicTheory::NotePtr> chordNotes = chords[c]->getAllNotes();
            vector<vizNote> notes = vector<vizNote>();
            
            string chordRootNote = ofToUpper(MusicTheory::Chord::getRootNote(chords[c]->getName()));

            if (c > 0 && incOctave == 0 && (chordRootNote == "C" || chordRootNote == "C#" || chordRootNote == "Db")) {
                // Bump octave when passing C                
                incOctave = 1;
            }

            //cout << "\n" << chords[c]->getName() << ":";
            for (int i = 0; i < chordNotes.size(); i++) {
                int octave = chordNotes[i]->getOctave() + incOctave;
                //cout << chordNotes[i]->getDiatonicName() << octave << "|";
                notes.push_back(vizNote(chordNotes[i]->getDiatonicName(), octave, 0, vector<string>{}));
            }
            diatonicChordsForScale.push_back(vizChord(chords[c]->getName(), notes, false)); // don't need to worry about extended chords
        }
        //cout << "\n-----------------------------------";
        
        return diatonicChordsForScale;
    }
    
    
    static vector<vector<vizChord>> getDiatonicChordMatrixForScale(string scaleName, vizTheory::NoteMode noteMode, bool useCircleOfFifths) {
        
        vector<string> keys;
        
        switch(noteMode) {
            case vizTheory::NoteMode::DEFAULT:
                keys = (useCircleOfFifths ? vizTheory::getCircleOfFifths() : vizTheory::getChromaticScale());
                break;
            case vizTheory::NoteMode::SHARP:
                keys = (useCircleOfFifths ? vizTheory::getCircleOfFifthsSharps() : vizTheory::getChromaticScaleSharps());
                break;
            case vizTheory::NoteMode::FLAT:
                keys = (useCircleOfFifths ? vizTheory::getCircleOfFifthsFlats() : vizTheory::getChromaticScaleFlats());
                break;
            default:
                keys = (useCircleOfFifths ? vizTheory::getCircleOfFifths() : vizTheory::getChromaticScale());
                break;
        }
        
        vector<vector<vizChord>> chordMatrix = vector<vector<vizChord>>();
        
        for (int i = 0; i < keys.size(); i++) {
            chordMatrix.push_back(getDiatonicChordsForScale(keys[i], scaleName));
        }

        return chordMatrix;
    }
    
    static vector<vizNote> getNotesForScale(string key, string scaleName) {
        return getNotesForScale(key, scaleName, 3);
    }
    
    static vector<vizNote> getNotesForScale(string key, string scaleName, int octave) {
        shared_ptr<MusicTheory::Note> keyNote = MusicTheory::Note::create(key);
        shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::getScaleFromString(scaleName, keyNote);
        if(!scale) {
            scale = MusicTheory::Scale::scaleFromDictionary(scaleName, keyNote);
        }         
        
        vector<vizNote> notesInScale = {};

        if (scaleName == "" || scale == nullptr) return notesInScale;

        for (int i=0; i<scale->notes.size(); i++) {

            // Bump octave when passing C
            if (i > 0 && ofToUpper(scale->notes[i]->getDiatonicName()) == "C") {
                octave++;
            }

            notesInScale.push_back(
               vizNote(scale->notes[i]->getDiatonicName(), octave, 0,
                       vector<string>{"TODO: some interesting info about this note's context in a scale"},
                       vizTheory::getColorForKey(scale->notes[i]->getDiatonicName())
                       )
               );
        }
        return notesInScale;
    }
    
    static vector<vizNote> getNotesForCircleOfFifths(vizTheory::NoteMode noteMode) {
  
        vector<vizNote> notesInScale = {};
        vector<string> notesInCOF;
        
        switch(noteMode) {
            case vizTheory::NoteMode::SHARP:
                notesInCOF = vizTheory::getCircleOfFifthsSharps(); break;
            case vizTheory::NoteMode::FLAT:
                notesInCOF = vizTheory::getCircleOfFifthsFlats(); break;
            case vizTheory::NoteMode::DEFAULT:
            default:
                notesInCOF = vizTheory::getCircleOfFifths(); break;
        }

        for (int i=0; i<notesInCOF.size(); i++) {
            notesInScale.push_back(vizNote(notesInCOF[i], 3, 0, vector<string>{}, vizTheory::getColorForKey(notesInCOF[i])));
        }
        return notesInScale;
    }
    
    static bool getIsDegreeFound(int interval, vector<vizNote> notes, vizNote forKey) {
        for (int j=0; j<notes.size(); j++) {
            if (forKey.getInterval(notes[j].getNoteName()) == interval) {
                return true;
            }
        }
        return false;
    }
    
    bool isScaleValid() {
        return !(mt_Scale == nullptr || mt_Scale->notes.size() == 0 || ofToLower(mt_Scale->getName()) == "unknown" || mt_Scale->getName() == "Invalid scale" || mt_Scale->getRoot() == nullptr);
    }

    string getName() {
        return mScaleName;
    }
    
    string getNamePretty() {
        return mScaleNamePretty;
    }

    vizNote getKey() {
        return mKey;
    }
    
    string determineNameFromSelectedNotes() {
        deque<MusicTheory::NotePtr> scaleNotes;
        for(vizNote currNote:mNotes) {
            scaleNotes.insert(scaleNotes.end(), currNote.getNote());
        }
        //string scaleName = MusicTheory::Scale::determine(scaleNotes);
        string scaleName = MusicTheory::Scale::determineFromDictionary(scaleNotes);

       // do exact matching 1st (deep scrub) then more general if not found....
        return scaleName;
    }

    static int getNoteOccuranceCount(vizNote note, vector<vizNote> notes, bool exactOctaveMatch) {
        int noteOccuranceCount = 0;
        for (vizNote currNote:notes) {
            if (currNote.isEnharmonicallyEquivalent(note.getNoteNameNormalized()) && (!exactOctaveMatch || note.getNoteOctave() == currNote.getNoteOctave())) {
                noteOccuranceCount++;
            }
        }
        return noteOccuranceCount;
    }


    string saveToMidiFile() {
        string proposedFileName = ofFilePath::join(APP_CONSTANTS::APPLICATION_CACHE_FOLDER(), vizTheory::extractFileSystemSafeName(getKey().getNoteName() + "_" + getName()) + ".mid");     
        vizNote rootNote = getKey();
        vizNote rootNoteOctaveHigher = vizNote(rootNote.getNoteName(), rootNote.getNoteOctave()+1, 1);
        vector<vizNote> notes = getNotes();

        int noteOccuranceCount = getNoteOccuranceCount(rootNote, notes, false);
        if (noteOccuranceCount<= 1) notes.push_back(rootNoteOctaveHigher);

        int starttime = 0;

        int numNotes = notes.size();

        float duration = 32.0f / (float)numNotes;   // (4=1/4 beat (32), 8=1/2 beat (16th), 16 = 1 beat, 32 = 2 beat, 48 = 3 beat, 64=1bar)
        int velocity = 100;

        smf::MidiFile midifile;
        int track   = 0;
        int channel = 0;
        int instr   = 0; //options.getInteger("instrument");
        midifile.addTimbre(track, 0, channel, instr);

        int tpq     = midifile.getTicksPerQuarterNote();
        float accumulatedTicks = 0.0f;

        for (vizNote note:notes) {
            int key       = note.getNote()->toInt();            
            int starttick = accumulatedTicks + starttime;
            int durationForTick = int((float)duration / 16.0f * tpq);
            int endtick   = accumulatedTicks +  durationForTick;

            // Emphasise the root note a bit
            velocity = (note.getNoteNameNormalized() == rootNote.getNoteNameNormalized() ? 100 : 80);

            midifile.addNoteOn (track, starttick, channel, key, velocity);
            midifile.addNoteOff(track, endtick,   channel, key);

            accumulatedTicks += durationForTick;
        }
        midifile.sortTracks();  // Need to sort tracks since added events are
                                // appended to track in random tick order.
        // Write it!
        midifile.write(proposedFileName);

        return proposedFileName;
    }

    static vector<string> searchScales(string context, int maxResults = 10) {
        context = ofToLower(context); 
        ofStringReplace(context, " ", ""); 

        vector<string> results;
        vector<string> scales = MusicTheory::Scale::getAllScalesData();
            int rowIndex=0;
            for (string scale:scales) {
                vector<string> scale_parts = ofSplitString(scale, "|");

                string scaleId = "", scaleName = "", origin = "", notes = "", numNotes = "";

                scaleId = (scale_parts.size() > 0) ? scale_parts[0] : "???";
                scaleName = (scale_parts.size() > 1) ? scale_parts[1] : "???";
                origin = (scale_parts.size() > 2) ? scale_parts[2] : "???";
                //notes = (scale_parts.size() > 3) ? scale_parts[3] : "???";
                //numNotes = (scale_parts.size() > 4) ? scale_parts[4] : "???";

                string s = ofToLower(scaleId);
                if (s.rfind(context, 0) == 0) { // match
                    results.push_back(scaleId);
                }
                if (results.size() >= maxResults) return results;
            }
            return results;     
    }

    static vector<vizScale> getScales(string context, int maxResults = 10) {
        vector<string> scales = searchScales(context, maxResults);
        vector<vizScale> results;
        for (string scaleId:scales) {
            results.push_back(vizScale("C", scaleId, 3));
        }
        return results;     
    }    

    static vector<vizScale> getScales(string context, string key, int maxResults = 10) {
        vector<vizScale> results;
        if (!vizTheory::isValidKey(key)) results;
        vector<string> scales = searchScales(context, maxResults);        
        for (string scaleId:scales) {
            results.push_back(vizScale(key, scaleId, 3));
        }
        return results;     
    }       

private:
    
    void resolvePrettyName() {
        mScaleNamePretty = getName();
        if (mScaleNamePretty.length() > 0) {
            mScaleNamePretty[0] = toupper(mScaleNamePretty[0]);
        }
    }
    
    vizNote mKey;
    vector<vizNote> mNotes;
    string mScaleName = "";
    string mScaleNamePretty = "";
    vector<string> mChordTags;
    shared_ptr<MusicTheory::Scale> mt_Scale;
    ofxXmlSettings mInstrumentRules = ofxXmlSettings();
    
};






















































//--------------------------------------------------------------
/* Use this when not data is not yet known (ie when it's definition is not yet a scale or chord) */
class vizNotes  : public vizTheoryBase  {
    
    
public:
    vizNotes() { }
 
    // Use this for instruments, where not repetition may be involved!
    vizNotes(string Name, vector<vizNote> notes) : mName(Name), mNotes(notes) {
    }    

    // Use this for instruments, where not repetition may be involved!
    vizNotes(vizNote key, string Name, vector<vizNote> notes) : mKey(key), mName(Name), mNotes(notes) {
    }    
    
    vizNotes(string xml, bool normalize)  {
        vizChord potentialChord = vizChord(xml, normalize);        
        vizScale potentialScale = vizScale(xml, normalize);

        if (potentialChord.getNotes().size() > 0) {
            appendNotes(potentialChord.getNotes());
            if (potentialChord.getChordName() != "") {
                mKey = potentialChord.getChordRootNote();
                addChord(potentialChord, false);
            }
        }

        if (potentialScale.getNotes().size() > 0) {
            appendNotes(potentialScale.getNotes());
            if (potentialScale.getKey().getNoteName() != "") {
                mKey = potentialScale.getKey();
                addScale(potentialScale, false);
            }            
        }        

        ofxXmlSettings notesXML = ofxXmlSettings();
        notesXML.loadFromBuffer(xml);

        if (notesXML.pushTag("notes")) {
            string key = notesXML.getValue("key", "");  
            if (key != "") {
                mKey = vizNote(key, 3, 1);  
            } 

            int notes = notesXML.getNumTags("note");
            
            vector<vizNote> scaleNotes = vector<vizNote>();
            
            for(int i = 0; i < notes; i++){

                string noteName = notesXML.getAttribute("note", "name", "C", i);

                vizNote noteToAdd = vizNote(
                                            noteName,
                                            notesXML.getAttribute("note", "octave", 3, i), 0, vector<string>{},
                                            vizTheory::getColorForKey(noteName)
                                            );
                mNotes.push_back(noteToAdd);
            }

        }




     }


    void appendNotes(vector<vizNote> notes) {
        if (notes.size() > 0) {
            mNotes.insert(mNotes.end(), notes.begin(), notes.end());
        } 
    }

    void addChord(vizChord chord, bool addOnlyIfNotFound) {
        if (chord.getChordName() != "") {
            if (addOnlyIfNotFound) {
                if(1==2) return; // todo
            }
            mChords.push_back(chord);
        } 
    }

    void addScale(vizScale scale, bool addOnlyIfNotFound) {
        if (scale.getName() != "") {
            if (addOnlyIfNotFound) {
                if(1==2) return; // todo
            }
            mScales.push_back(scale);
        } 
    }           

    vector<vizNote> getNotes() {
        return mNotes;
    }

    string getXML() {
        
        if (getNotes().size() > 0) {
            
            ofxXmlSettings notesXML = ofxXmlSettings();
            notesXML.addTag("notes");
            notesXML.pushTag("notes");    
            notesXML.addValue("name", getName());
            notesXML.addValue("key", getKey().getNoteName());        
            
            vector<vizNote> notes = getNotes();
            for (int i = 0; i < notes.size(); i++) {
                notes[i].appendToXMLNode(&notesXML, i);
            }

            // Rules
            appendInstrumentRulesToXMLNode(&notesXML, 0);            
            
            notesXML.popTag();
            
            string strXML;
            notesXML.copyXmlToString(strXML);
            return strXML;
        }
        
        return "";
    }


    
    static bool getIsDegreeFound(int interval, vector<vizNote> notes, vizNote forKey) {
        for (int j=0; j<notes.size(); j++) {
            if (forKey.getInterval(notes[j].getNoteName()) == interval) {
                return true;
            }
        }
        return false;
    }

    string getName() {
        return mName;
    }

    vizNote getKey() {
        return mKey;
    }
    
    static int getNoteOccuranceCount(vizNote note, vector<vizNote> notes, bool exactOctaveMatch) {
        int noteOccuranceCount = 0;
        for (vizNote currNote:notes) {
            if (currNote.isEnharmonicallyEquivalent(note.getNoteNameNormalized()) && (!exactOctaveMatch || note.getNoteOctave() == currNote.getNoteOctave())) {
                noteOccuranceCount++;
            }
        }
        return noteOccuranceCount;
    }


    string saveToMidiFile() {
        string proposedFileName = ofFilePath::join(APP_CONSTANTS::APPLICATION_CACHE_FOLDER(), vizTheory::extractFileSystemSafeName(getKey().getNoteName() + "_" + getName()) + ".mid");     
        vizNote rootNote = getKey();
        
        vector<vizNote> notes = getNotes();



        int starttime = 0;

        int numNotes = notes.size();

        float duration = 32.0f / (float)numNotes;   // (4=1/4 beat (32), 8=1/2 beat (16th), 16 = 1 beat, 32 = 2 beat, 48 = 3 beat, 64=1bar)
        int velocity = 100;

        smf::MidiFile midifile;
        int track   = 0;
        int channel = 0;
        int instr   = 0; //options.getInteger("instrument");
        midifile.addTimbre(track, 0, channel, instr);

        int tpq     = midifile.getTicksPerQuarterNote();
        float accumulatedTicks = 0.0f;

        for (vizNote note:notes) {
            int key       = note.getNote()->toInt();            
            int starttick = 0;
            int durationForTick = int((float)duration / 16.0f * tpq);
            int endtick   = accumulatedTicks +  durationForTick;
            //todo add velocity and duration data (strum effect - with small start offset)
            // Emphasise the root note a bit
            velocity = 80;

            midifile.addNoteOn (track, starttick, channel, key, velocity);
            midifile.addNoteOff(track, endtick,   channel, key);

            accumulatedTicks += durationForTick;
        }
        midifile.sortTracks();  // Need to sort tracks since added events are
                                // appended to track in random tick order.
        // Write it!
        midifile.write(proposedFileName);

        return proposedFileName;
    }

private:
    vizNote mKey;
    vector<vizNote> mNotes;
    vector<vizChord> mChords;
    vector<vizScale> mScales;        
    string mName = "unknown";
    ofxXmlSettings mInstrumentRules = ofxXmlSettings();
    
};








