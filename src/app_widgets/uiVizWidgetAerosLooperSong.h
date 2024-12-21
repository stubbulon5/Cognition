//
//  uiVizWidgetAerosLooperSong.h
//
//
#pragma once
#include "ofxAquamarine.h"

#include "../core/aerosSong/song.pb.h"
#include "../core/AudioFile/AudioFile.h"

class uiVizWidgetAerosLooperSong : public uiVizWidget {
    
public:
    
    uiVizWidgetAerosLooperSong(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidget::loadState(widgetXML);

        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }
    
    virtual ~uiVizWidgetAerosLooperSong() {


        ofRemoveListener(TBL_NUMBER_PICKER->cellSelected, this,  &uiVizWidgetAerosLooperSong::onNumberMenuCellCelected);

    }
    
    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        string parentWidgetId = args.sender.getParentPersistentId();
        string event = args.getFullEventName();

        cout << event;

        if (args.sender.matchesWidget(BTN_SAVE_SONG)) {
            closeThisWidget("SUCCESS");

        }

    }

    void onNumberMenuCellCelected(uiVizWidgetTableArgs &args) {
        args.sender.setMetadata("META_VAL", args.row.key);
        args.sender.clearSelectedRows();
        args.sender.closeThisWidget("VALUE_SELECTED");
    }   
 

    static string getWavFileName(string channel, int part, int track, bool zeroBasedNums) { // channel 'a' = left, channel 'b' = right
        return ofToUpper("CH"+channel+"SP"+ofToString(part+(zeroBasedNums?1:0))+"T"+ofToString(track+(zeroBasedNums?1:0)))+".wav";
    }


/*
    ---------------------
drawColumnNVG(const string& text,
								  const Style& style,
								  float x, float y, float width,
								  ofAlignHorz horAlign){

	switch(horAlign){
		case OF_ALIGN_HORZ_LEFT: hAlign = NVG_ALIGN_LEFT; break;
		case OF_ALIGN_HORZ_CENTER: hAlign = NVG_ALIGN_CENTER; break;
		case OF_ALIGN_HORZ_RIGHT:
    --------------------

*/


    static int calculateTicksFromAudioFile(Singul::Song& aerosSong, AudioFile<double>& audioFile) {
        /*
        float millisecondsPerQuarterNote = aerosSong.bpm() / 1000.0f;
        float millisecondsPerTick = millisecondsPerQuarterNote / aerosSong.tpqn(); 
        float millisecondsTrackLength = audioFile.getLengthInSeconds()*1000;
        int ticks = millisecondsTrackLength * millisecondsPerTick;
        return ticks;
*/



///todo work out ticks 
//aerosSong.tpqn(); // Fixed to 24 for now, important to save for future version
                /*
                int numFrames = audioFile.getNumSamplesPerChannel(); //audioFile.printSummary();
                cout << numFrames << " FRAMES" << endl;

                int numTicks = (numFrames/1000.0)-0.5f;
                cout << numTicks << " TICKS" << endl;
                */

                // WORK THIS OUT ....
                // double lengthInSeconds = audioFile.getLengthInSeconds();
                // cout << lengthInSeconds << " SECS" << endl;

                // int resolution = aerosSong.time_sig().numerator(); // in ticks/beat                 
                // int numTicks = resolution * (1 / aerosSong.bpm()) * 1000 * lengthInSeconds;


        return (audioFile.getNumSamplesPerChannel()/1000.0)-0.5f;

    }

    static string getAudioFileInfoLog(string heading, AudioFile<double>& audioFile) {
        std::stringstream audioFileStr;
        audioFileStr << endl << heading;
        audioFileStr << endl << "---------------------------------------------------------------------------------------" << endl;          
        audioFileStr << endl << "Num Channels: " << audioFile.getNumChannels() << "(" <<  (audioFile.isStereo() ? "Stereo" : "Mono") << ")";
        audioFileStr << endl << "Num Samples Per Channel: " << audioFile.getNumSamplesPerChannel();
        audioFileStr << endl << "Sample Rate: " << audioFile.getSampleRate();
        audioFileStr << endl << "Bit Depth: " << audioFile.getBitDepth();
        audioFileStr << endl << "Length in Seconds: " << audioFile.getLengthInSeconds();          
        audioFileStr << endl << "---------------------------------------------------------------------------------------" << endl;  
        return audioFileStr.str();
    }    

    static string getSongInfoLog(Singul::Song& aerosSong) {
        std::stringstream songInfo;
        songInfo << endl << "---------------------------------------------------------------------------------------";
        songInfo << endl << "Aeros OS " << aerosSong.os_version() << " file  (Meta v" << aerosSong.meta_version() << " )";
        songInfo << endl << "SONG: " << aerosSong.title() << " | TIME SIG: " << aerosSong.time_sig().numerator() << " / " << aerosSong.time_sig().denonimator() << " @ " << aerosSong.bpm() << "BPM";
        songInfo << endl << "STEREO: " << aerosSong.stereo();
        songInfo << endl << "TICKS / QUARTER NOTE: " << aerosSong.tpqn(); // Fixed to 24 for now, important to save for future version
        songInfo << endl << "COUNT IN: " << aerosSong.count_in();
        songInfo << endl << "MODE: " << (aerosSong.mode_2x2_enabled() ? "2x2" : "6x6");
        songInfo << endl << "QUANTIZE: " << aerosSong.quantize_track_enabled();
        songInfo << endl << "ORDER INDEX: " << aerosSong.order_index();
        songInfo << endl << "MIDI SYNC: " << aerosSong.sync_tracks_option();
        songInfo << endl << "MIDI SELECT: " << aerosSong.midi_select_enabled();
        songInfo << endl << "MIDI BANK MSB: " << aerosSong.midi_bank_msb();
        songInfo << endl << "MIDI PROGRAM NUMBER: " << aerosSong.midi_program_number();
        return songInfo.str();
    }

    static string getTracksInfoLog(string heading, Singul::Song& aerosSong) {
        std::stringstream tracksInfo;
        if (heading != "") {
            tracksInfo << endl << endl << heading;
        }
        tracksInfo << endl << "---------------------------------------------------------------------------------------";          
        for (int p=0; p<aerosSong.parts_size(); p++) {
            const ::Singul::Part& part = aerosSong.parts(p);
            tracksInfo << endl << endl << "PART " << p+1 << " has " << part.tracks_size() << " tracks:";
            for (int t=0; t<part.tracks_size(); t++) {
                const ::Singul::Track& track = part.tracks(t);
                tracksInfo << endl << "TICKS: " << track.number_of_tick() << " | OFFSET: " << track.tick_offset(); // << " | LOCKED: " << aerosSong.locked(t);
                tracksInfo << " [";
                tracksInfo << "TRACK L: " << track.loop_a().filename() << " : " << track.loop_a().number_of_frames() << " frames | ";
                tracksInfo << "TRACK R: " << track.loop_b().filename() << " : " << track.loop_b().number_of_frames() << " frames";
                tracksInfo << "] ";
            }
        }
        tracksInfo << endl << "---------------------------------------------------------------------------------------" << endl;  
        return tracksInfo.str();
    }
        
    static string extractFileSystemSafeName(string fileName) {
        string illegalChars = "\\/:?\"<>|[]";
        for (auto it = fileName.begin() ; it < fileName.end() ; ++it){
            bool found = illegalChars.find(*it) != string::npos;
            if(found){
                *it = '-';
            }
        }
        return fileName;       
    }


    // Aeros accepted file format: Sample Rate: 44100 , Bit Depth: 24
    static void saveTrackAudioFiles(Singul::Song& aerosSong, string songPath, int partNum, int trackNum) {

        string loop_a_TargetFile = getWavFileName("A", partNum, trackNum, true);
        string loop_b_TargetFile = getWavFileName("B", partNum, trackNum, true);     

        string absolute_loop_a_TargetFile = ofFilePath::join(songPath, loop_a_TargetFile);
        string absolute_loop_b_TargetFile = ofFilePath::join(songPath, loop_b_TargetFile);

        const ::Singul::Part& part = aerosSong.parts(partNum);
        const ::Singul::Track& track = part.tracks(trackNum);

        int numFramesL = track.loop_a().number_of_frames();
        int numFramesR = track.loop_b().number_of_frames();
        int numTicksL, numTicksR = track.number_of_tick();
        bool trackL_loaded, trackR_loaded = false;

        int AEROS_SAMPLE_RATE = 44100;
        int AEROS_BIT_DEPTH = 24;

        AudioFile<double> audioFile;

        bool isUpdatedFile = false;
        string loopFileName = track.loop_a().filename();
        if (ofIsStringInString(loopFileName, "!|UPDATED|!")) {
            ofStringReplace(loopFileName, "!|UPDATED|!", "");
            isUpdatedFile = true;
        }

        // Have the files been removed?
        if(loopFileName == "") {
            ofFile::removeFile(absolute_loop_a_TargetFile, false);
            ofFile::removeFile(absolute_loop_b_TargetFile, false);
            return;
        }

        // Load the file
        if (isUpdatedFile && audioFile.load(loopFileName)) {

            cout << endl << "Converting "<<loopFileName<<" ("<<audioFile.getSampleRate()<< "khz "<<audioFile.getBitDepth()<<"bit "<<(audioFile.isStereo() ? "Stereo" : "Mono")<<")";

            int numFrames = audioFile.getNumSamplesPerChannel();

            AudioFile<double> a, b;
            int LEFT_CHANNEL = 0;
            int RIGHT_CHANNEL = 1;

                        
            // TODO: how to convert from 48 to 44.1 kHZ ????
            // https://github.com/adamstark/AudioFile/issues/54

            // Mono / left channel
            a.setNumChannels(1);
            a.samples[0] = audioFile.samples[LEFT_CHANNEL];  
            a.setSampleRate(AEROS_SAMPLE_RATE);
            a.setBitDepth(AEROS_BIT_DEPTH);                
            a.save(absolute_loop_a_TargetFile, AudioFileFormat::Wave);          
            aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_a()->set_filename(loop_a_TargetFile);
            aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_a()->set_number_of_frames(numFrames);    

            cout << getAudioFileInfoLog(loop_a_TargetFile, a);            

            if (aerosSong.stereo()) {
                // Stereo right channel
                if(audioFile.isStereo()) {
                    b.setNumChannels(1);
                    b.samples[0] = audioFile.samples[RIGHT_CHANNEL];
                    b.setSampleRate(AEROS_SAMPLE_RATE);
                    b.setBitDepth(AEROS_BIT_DEPTH);                        
                    b.save(absolute_loop_b_TargetFile, AudioFileFormat::Wave);

                } else {
                    a.save(absolute_loop_b_TargetFile, AudioFileFormat::Wave);
                }

                aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_b()->set_filename(loop_b_TargetFile);
                aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_b()->set_number_of_frames(numFrames);
            } else {
                aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_b()->set_filename("");
                aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->mutable_loop_b()->set_number_of_frames(0);                    
            }


            // Set the ticks
            int numTicks = calculateTicksFromAudioFile(aerosSong, audioFile);
            aerosSong.mutable_parts(partNum)->mutable_tracks(trackNum)->set_number_of_tick(numTicks);
        } else {
            cout << endl << "WAS NOT ABLE TO LOAD FILE !!! : " << track.loop_a().filename();
        }
    }  

    static void assignAudioFileAbsolutePathToTrackPart(Singul::Song& aerosSong, string audioFilePath, int p, int t) {
        const ::Singul::Part& part = aerosSong.parts(p);
        const ::Singul::Track& track = part.tracks(t);                

        // Mono
        aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_a()->set_filename("!|UPDATED|!"+audioFilePath);

        // Stereo
        if (aerosSong.stereo()) {
            aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_b()->set_filename("!|UPDATED|!"+audioFilePath);
        }
      
    } 

    static Singul::Song loadSong(string songsRootPath, string songName) {
        AudioFile<double> audioFile;
        
        // Project file structure
        string songParentFolderName = extractFileSystemSafeName(songName);
        string songPath = ofFilePath::join(songsRootPath, songParentFolderName);
        string songFilePath = ofFilePath::join(songPath, ".meta");        

        Singul::Song aerosSong;
        //Singul::Song* aerosSongForUpdate;
        fstream input(songFilePath, ios::in | ios::binary);

        std::stringstream buffer;
        buffer << input.rdbuf();

        if (!input) {
            cout << songFilePath << ": File not found.  Creating a new file." << endl;
        } else if (!aerosSong.ParseFromString(buffer.str())) { // !aerosSong.ParseFromIstream(&input) <--- newer 
            cerr << "Failed to parse Aeros v" << aerosSong.meta_version() << " file " << endl;
            cerr << aerosSong.InitializationErrorString();
        }

        // Log some info
        cout << getSongInfoLog(aerosSong);
        cout << getTracksInfoLog("TRACKS (before setting absolute path)", aerosSong);

        for (int p=0; p<aerosSong.parts_size(); p++) {
            const ::Singul::Part& part = aerosSong.parts(p);
            for (int t=0; t<part.tracks_size(); t++) {
                const ::Singul::Track& track = part.tracks(t);

                // We set absolute Wav file paths during load operation
                // when saving the file, we "consolidate" the files into the song project folder, then strip the path from
                // the filename to make it compatible with the Aeros...
                const string loop_a_absolute_path = ofFilePath::join(songPath, track.loop_a().filename()); 
                const string loop_b_absolute_path = ofFilePath::join(songPath, track.loop_b().filename());               

                if (track.loop_a().filename() != "" && audioFile.load(loop_a_absolute_path)) {
                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_a()->set_filename(loop_a_absolute_path);
                }

                if (track.loop_b().filename() != "" && audioFile.load(loop_b_absolute_path)) {
                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_b()->set_filename(loop_b_absolute_path);
                }
            }
        }
        cout << getTracksInfoLog("TRACKS (AFTER setting absolute path)", aerosSong);
        return aerosSong;

    }

    static string saveSong(string songsRootPath, Singul::Song aerosSong) {

        AudioFile<double> audioFileL;
        AudioFile<double> audioFileR;

        // Project file structure
        string songParentFolderName = extractFileSystemSafeName(aerosSong.title());
        string songPath = ofFilePath::join(songsRootPath, songParentFolderName);
        string songFilePath = ofFilePath::join(songPath, ".meta");

        // Song project folder - does it exist? if not, create folder
        ofDirectory dir(songPath);
        if(!dir.exists()){
            dir.create(true);
        }

        // Log some info
        cout << getSongInfoLog(aerosSong);
        cout << getTracksInfoLog("TRACKS (before processing)", aerosSong);

        for (int p=0; p<aerosSong.parts_size(); p++) {
            const ::Singul::Part& part = aerosSong.parts(p);
            for (int t=0; t<part.tracks_size(); t++) {
                const ::Singul::Track& track = part.tracks(t);

                saveTrackAudioFiles(aerosSong, songPath, p, t);

/*

                int numFramesL = track.loop_a().number_of_frames();
                int numFramesR = track.loop_b().number_of_frames();
                int numTicksL, numTicksR = track.number_of_tick();
                bool trackL_loaded, trackR_loaded = false;

                // Load the file
                if (track.loop_a().filename() != "" && audioFileL.load(track.loop_a().filename())) {


                    saveAudioFile(aerosSong, audioFileL, track.loop_a().filename());

                    numFramesL = audioFileL.getNumSamplesPerChannel(); //audioFile.printSummary();
                    numTicksL = calculateTicksFromAudioFile(aerosSong, audioFileL);
                    trackL_loaded = true;
                }

                if (track.loop_b().filename() != "" && audioFileR.load(track.loop_b().filename())) {
                    numFramesR = audioFileR.getNumSamplesPerChannel(); //audioFile.printSummary();
                    numTicksR = calculateTicksFromAudioFile(aerosSong, audioFileR);
                    trackR_loaded = true;
                }

                int numTicks = std::max(numTicksL, numTicksR);

                // Updating
                aerosSong.mutable_parts(p)->mutable_tracks(t)->set_number_of_tick(numTicks);

                // copy wav files to destination
                if (trackL_loaded) {
                    // do copy here ...
                    string loop_a_TargetFile = getWavFileName("A", p, t, true);
                    ofFile::copyFromTo(track.loop_a().filename(), ofFilePath::join(songPath, loop_a_TargetFile), false, true);

                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_a()->set_filename(loop_a_TargetFile);
                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_a()->set_number_of_frames(numFramesL);

                    cout << getAudioFileInfoLog(loop_a_TargetFile, audioFileL);

                }

                if (trackR_loaded) {
                    // do copy here ...                    
                    string loop_b_TargetFile = getWavFileName("B", p, t, true);
                    ofFile::copyFromTo(track.loop_b().filename(), ofFilePath::join(songPath, loop_b_TargetFile), false, true);

                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_b()->set_filename(loop_b_TargetFile);
                    aerosSong.mutable_parts(p)->mutable_tracks(t)->mutable_loop_b()->set_number_of_frames(numFramesR);
                }
                */     
            }
        }
        cout << getTracksInfoLog("TRACKS (AFTER processing)", aerosSong);

        // Persist the song .meta file
        string output;
        bool serialized = aerosSong.SerializeToString(&output);

        if (serialized) {
            ofstream outfile(songFilePath, ios::out | ios::binary);
            if (outfile.good()) {
                outfile.write(output.c_str(), output.size());
                outfile.close();
                cout << "-=-=-=-=- SAVED AEROS SONG -=-=-=-=-";
            } else {
                return "Error saving file";
            }
        } else {
            return "Error generating data to save";
        }           

        return "Success";
    }

    void draw(Aquamarine::uiVizWidgetContext context) override {

    }

    virtual void onToolTabsMenuItemSelected(uiVizWidgetMenuCollectionArgs &args) {
        cout << args.activeMenuTabId;
    }    

    virtual void onChildWidgetsLoaded() override {

        if (!hookedEvents) {
            TOOL_TABS = dynamic_cast<Aquamarine::uiVizWidgetMenuCollection*>(getChildWidgetByPersistentId("TOOL_TABS"));
            ofAddListener(TOOL_TABS->menuItemSelected, this, &uiVizWidgetAerosLooperSong::onToolTabsMenuItemSelected);


            BTN_SAVE_SONG = getButton("BTN_SAVE_SONG");


            SONG_INFO_HOLDER = TOOL_TABS->getWidgetForTag("newSong");    // use updateSong for update operation    
            

            LBL_SONG_TITLE = SONG_INFO_HOLDER->getLabel("LBL_SONG_TITLE");
            TXT_TITLE = SONG_INFO_HOLDER->getTextbox("TXT_TITLE");
            LBL_2X2_ENABLED = SONG_INFO_HOLDER->getLabel("LBL_2X2_ENABLED");
            MODE_2X2_ENABLED = SONG_INFO_HOLDER->getCheckbox("MODE_2X2_ENABLED");
            LBL_STEREO = SONG_INFO_HOLDER->getLabel("LBL_STEREO");
            STEREO = SONG_INFO_HOLDER->getCheckbox("STEREO");
            LBL_TIME_SIG = SONG_INFO_HOLDER->getLabel("LBL_TIME_SIG");
            BTN_TIME_SIGNATURE_NUMERATOR = SONG_INFO_HOLDER->getButton("BTN_TIME_SIGNATURE_NUMERATOR");
            BTN_TIME_SIGNATURE_DENOMINATOR = SONG_INFO_HOLDER->getButton("BTN_TIME_SIGNATURE_DENOMINATOR");
            BTN_BPM = SONG_INFO_HOLDER->getButton("BTN_BPM");
            LBL_RECORDING_OPTIONS = SONG_INFO_HOLDER->getLabel("LBL_RECORDING_OPTIONS");
            BTN_COUNT_IN = SONG_INFO_HOLDER->getButton("BTN_COUNT_IN");
            BTN_SYNC_TRACKS_OPTION = SONG_INFO_HOLDER->getButton("BTN_SYNC_TRACKS_OPTION");
            LBL_QUANTIZE = SONG_INFO_HOLDER->getLabel("LBL_QUANTIZE");
            QUANTIZE_TRACK_ENABLED = SONG_INFO_HOLDER->getCheckbox("QUANTIZE_TRACK_ENABLED");
            LBL_MIDI_OPTIONS = SONG_INFO_HOLDER->getLabel("LBL_MIDI_OPTIONS");
            BTN_MIDI_BANK_MSB = SONG_INFO_HOLDER->getButton("BTN_MIDI_BANK_MSB");
            BTN_MIDI_PROGRAM_NUMBER = SONG_INFO_HOLDER->getButton("BTN_MIDI_PROGRAM_NUMBER");
            CHK_MIDI_SELECT_ENABLED = SONG_INFO_HOLDER->getCheckbox("CHK_MIDI_SELECT_ENABLED");


            // Popout number pickers ...
            BTN_TIME_SIGNATURE_NUMERATOR->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::DOWN);
            BTN_TIME_SIGNATURE_DENOMINATOR->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::DOWN);
            BTN_BPM->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::DOWN);
            BTN_COUNT_IN->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::DOWN);
            BTN_SYNC_TRACKS_OPTION->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::DOWN);
            BTN_MIDI_BANK_MSB->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::UP);
            BTN_MIDI_PROGRAM_NUMBER->setPopoutWidgetIgnoreTheme(TBL_NUMBER_PICKER, PopoutDirection::UP);

            ofAddListener(TBL_NUMBER_PICKER->cellSelected, this,  &uiVizWidgetAerosLooperSong::onNumberMenuCellCelected);


            TBL_NUMBER_PICKER->setWidgetClosedCallback([this](uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, string result) {
                //cout << sender->getPersistentId() << " was " << result << " with val "; /// <<  sender->getMetadata("META_VAL");

                if(sender && result == "VALUE_SELECTED") {
                    int selectedVal = closedWidget->getMetadataInt("META_VAL");
                    this->setNumElmVal(sender, selectedVal);
                }

                closedWidget->setMetadata("META_VAL", "");

            });



            BTN_TIME_SIGNATURE_NUMERATOR->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 256, "NUMERATOR", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_TIME_SIGNATURE_NUMERATOR->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_TIME_SIGNATURE_NUMERATOR->getMetadata("META_VAL"), true, false);
            });
            BTN_TIME_SIGNATURE_DENOMINATOR->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 256, "DENOMINATOR", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_TIME_SIGNATURE_DENOMINATOR->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_TIME_SIGNATURE_DENOMINATOR->getMetadata("META_VAL"), true, false);
            });
            BTN_BPM->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(10, 300, "BPM", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_BPM->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_BPM->getMetadata("META_VAL"), true, false);
            });
            BTN_COUNT_IN->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 4, "COUNT IN", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_COUNT_IN->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_COUNT_IN->getMetadata("META_VAL"), true, false);
            });
            BTN_SYNC_TRACKS_OPTION->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 256, "SYNC TRACKS", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_SYNC_TRACKS_OPTION->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_SYNC_TRACKS_OPTION->getMetadata("META_VAL"), true, false);
            });
            BTN_MIDI_BANK_MSB->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 256, "MIDI BANK MSB", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_MIDI_BANK_MSB->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_MIDI_BANK_MSB->getMetadata("META_VAL"), true, false);
            });
            BTN_MIDI_PROGRAM_NUMBER->setPopoutWidgetShownCallback([this]() {
                this->getTBL_NUMBER_PICKER()->populateWithNumberRange(1, 256, "MIDI PROGRAM NUMBER", true, false);
                this->getTBL_NUMBER_PICKER()->setColumnFilterVal(0, BTN_MIDI_PROGRAM_NUMBER->getMetadata("META_VAL"), false);
                this->getTBL_NUMBER_PICKER()->selectRowByKey(BTN_MIDI_PROGRAM_NUMBER->getMetadata("META_VAL"), true, false);
            });

            hookedEvents = true;
        }
    }  

    Singul::Song populateSongFromWidget() {

        Singul::Song song;

        song.set_title(TXT_TITLE->getValue());
        song.set_mode_2x2_enabled(MODE_2X2_ENABLED->getValue());
        song.set_stereo(STEREO->getValue());

        song.mutable_time_sig()->set_numerator(BTN_TIME_SIGNATURE_NUMERATOR->getMetadataInt("META_VAL"));
        song.mutable_time_sig()->set_denonimator(BTN_TIME_SIGNATURE_DENOMINATOR->getMetadataInt("META_VAL"));
        song.set_bpm(BTN_BPM->getMetadataInt("META_VAL"));


        song.set_count_in(BTN_COUNT_IN->getMetadataInt("META_VAL"));
        song.set_sync_tracks_option(BTN_SYNC_TRACKS_OPTION->getMetadataInt("META_VAL"));

        song.set_quantize_track_enabled(QUANTIZE_TRACK_ENABLED->getValue());

        song.set_midi_bank_msb(BTN_MIDI_BANK_MSB->getMetadataInt("META_VAL"));
        song.set_midi_program_number(BTN_MIDI_PROGRAM_NUMBER->getMetadataInt("META_VAL"));

        song.set_midi_select_enabled(CHK_MIDI_SELECT_ENABLED->getValue());

        song.set_tpqn(24); // Fixed to 24 for now, important to save for future version
        song.set_order_index(0); // Fixed to 0 for now
        

        song.set_meta_version(AEROS_FILE_META_VERSION);
        song.set_os_version(AEROS_OS_VERSION);

        // Per track 
        //song.set_locked(0, LOCKED->getValue());

        return song;
    }

    void setNumElmVal(uiVizWidgetBase* elm, int val) {
        elm->setMetadata("META_VAL", val);
        if(elm->getPersistentId() == "BTN_BPM") {
            elm->setTitle(ofToString(val) + " BPM");
        } else {
            elm->setTitle(ofToString(val));
        }
        elm->setNeedsUpdate(true);
    }

    void populateWidgetFromSong(Singul::Song song) {

        TXT_TITLE->setValue(song.title(), false);
        MODE_2X2_ENABLED->setValue(song.mode_2x2_enabled(), false, false);
        STEREO->setValue(song.stereo(), false, false);

        setNumElmVal(BTN_TIME_SIGNATURE_NUMERATOR, song.time_sig().numerator());
        setNumElmVal(BTN_TIME_SIGNATURE_DENOMINATOR, song.time_sig().denonimator());
        setNumElmVal(BTN_BPM, song.bpm());


        setNumElmVal(BTN_COUNT_IN, song.count_in());
        setNumElmVal(BTN_SYNC_TRACKS_OPTION, song.sync_tracks_option());

        QUANTIZE_TRACK_ENABLED->setValue(song.quantize_track_enabled(), false, false);

        setNumElmVal(BTN_MIDI_BANK_MSB, song.midi_bank_msb());
        setNumElmVal(BTN_MIDI_PROGRAM_NUMBER, song.midi_program_number());

        CHK_MIDI_SELECT_ENABLED->setValue(song.midi_select_enabled(), false, false);

        //song.set_tpqn(24); // Fixed to 24 for now, important to save for future version
        //song.set_order_index(0); // Fixed to 0 for now

        // Per track 
        //song.set_locked(0, LOCKED->getValue());
        loadedSong = song;
    }

    void initializeWithEmptySong() {
        Singul::Song song;
        song.set_tpqn(24); // Fixed to 24 for now, important to save for future version
        song.set_order_index(0); // Fixed to 0 for now       

        song.set_meta_version(AEROS_FILE_META_VERSION);
        song.set_os_version(AEROS_OS_VERSION);
         
        populateWidgetFromSong(song);
    }

    uiVizWidgetTable* getTBL_NUMBER_PICKER() {
        // TBL_NUMBER_PICKER->setCellSelectionColor(ofColor::red);
        // TBL_NUMBER_PICKER->setCellLabelSelectedColor(ofColor::blue);
        return TBL_NUMBER_PICKER;
    }
    
private:

    const int AEROS_FILE_META_VERSION = 123;
    const string AEROS_OS_VERSION = "TODO_AEROS_OS_VERSION";

    uiVizWidgetMenuCollection* TOOL_TABS = nullptr;
    bool hookedEvents = false;

    uiVizWidgetElmButton* BTN_SAVE_SONG = nullptr;
    uiVizWidgetDialog* AEROS_DIALOG = nullptr;

    uiVizWidget* SONG_INFO_HOLDER = nullptr;


    uiVizWidgetElmLabel* LBL_SONG_TITLE = nullptr;
    uiVizWidgetElmTextbox* TXT_TITLE = nullptr;
    uiVizWidgetElmLabel* LBL_2X2_ENABLED = nullptr;
    uiVizWidgetElmCheckbox* MODE_2X2_ENABLED = nullptr;
    uiVizWidgetElmLabel* LBL_STEREO = nullptr;
    uiVizWidgetElmCheckbox* STEREO = nullptr;
    uiVizWidgetElmLabel* LBL_TIME_SIG = nullptr;
    uiVizWidgetElmButton* BTN_TIME_SIGNATURE_NUMERATOR = nullptr;
    uiVizWidgetElmButton* BTN_TIME_SIGNATURE_DENOMINATOR = nullptr;
    uiVizWidgetElmButton* BTN_BPM = nullptr;
    uiVizWidgetElmLabel* LBL_RECORDING_OPTIONS = nullptr;
    uiVizWidgetElmButton* BTN_COUNT_IN = nullptr;
    uiVizWidgetElmButton* BTN_SYNC_TRACKS_OPTION = nullptr;
    uiVizWidgetElmLabel* LBL_QUANTIZE = nullptr;
    uiVizWidgetElmCheckbox* QUANTIZE_TRACK_ENABLED = nullptr;
    uiVizWidgetElmLabel* LBL_MIDI_OPTIONS = nullptr;
    uiVizWidgetElmButton* BTN_MIDI_BANK_MSB = nullptr;
    uiVizWidgetElmButton* BTN_MIDI_PROGRAM_NUMBER = nullptr;
    uiVizWidgetElmCheckbox* CHK_MIDI_SELECT_ENABLED = nullptr;

    Singul::Song loadedSong;

    uiVizWidgetTable* TBL_NUMBER_PICKER = nullptr;

    void initWidget() override {
      

        if (!AEROS_DIALOG) {
           AEROS_DIALOG = new uiVizWidgetDialog("AEROS_DIALOG", R"(
                <widget>
                    <bounds width="500" height="300" />
                </widget>
                )");

            uiVizWidgetManager::addWidgetForPopout(*AEROS_DIALOG, getWidgetId(), true);
        }

        if (!TBL_NUMBER_PICKER) {
           TBL_NUMBER_PICKER = new uiVizWidgetTable("TBL_NUMBER_PICKER", R"(
                <widget>
                    <bounds width="200" height="170" />
                </widget>
                )");

            TBL_NUMBER_PICKER->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));
            TBL_NUMBER_PICKER->setCellSelectionColor(ofColor::red);
            TBL_NUMBER_PICKER->setCellLabelSelectedColor(ofColor::blue);
            uiVizWidgetManager::addWidgetForPopout(*TBL_NUMBER_PICKER, getWidgetId(), true);
        }


    }
    
};


