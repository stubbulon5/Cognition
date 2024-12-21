#include "appConstants.h"

const std::string APP_CONSTANTS::APPLICATION_NAME = "cognition";
const std::string APP_CONSTANTS::APPLICATION_VERSION = "1.0.0"; /* Major.Minor.Patch*/
const std::string APP_CONSTANTS::APPLICATION_FILE_EXTENSION = "jam";
const std::string APP_CONSTANTS::APPLICATION_LIC_ENC_KEY = "DuYZL7n7B6Uj2gEfhsdY65PD5ARU3AdwENmfKjcXeH7SAnJvqy5keKP9VgTNGHaW873ugQg79ZAmcVFdjAppVNpGUS7scSdaPRuGhnr4cQeZBw4xG4KuGJLttHvvrkvR";
const std::string APP_CONSTANTS::APPLICATION_WEBSITE = "https://www.harmonyframeworks.com";

const std::string APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER() {
    #ifdef TARGET_OF_IOS
        return ofFilePath::join(getIOSGetDocumentsDirectory(), "." + APP_CONSTANTS::APPLICATION_NAME); // eg ~/.cognition
    #else
        return ofFilePath::join(ofFilePath::getUserHomeDir(), "." + APP_CONSTANTS::APPLICATION_NAME); // eg ~/.cognition
    #endif
}

const std::string APP_CONSTANTS::APPLICATION_CACHE_FOLDER() {
    return ofFilePath::join(APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER(), "cache"); // eg ~/.cognition/cache
}

const std::string APP_CONSTANTS::APPLICATION_SETTINGS_FILE() {
    return "settings.xml";
}

const std::string APP_CONSTANTS::APPLICATION_SETTINGS_FILE_FULL_PATH() {
    return ofFilePath::join(APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER(), APP_CONSTANTS::APPLICATION_SETTINGS_FILE()); // eg ~/.cognition/settings.xml
}

const std::string APP_CONSTANTS::APPLICATION_LIC_ENC_KEY_FILE() {
    return ofFilePath::join(APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER(), "key.txt"); // eg ~/.cognition/key.txt
}

void APP_CONSTANTS::BOOTSTRAP_APP() {

    ofDirectory::createDirectory(APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER(), true, false);
    ofDirectory::createDirectory(APP_CONSTANTS::APPLICATION_CACHE_FOLDER(), true, false);

    Aquamarine::uiVizWidgetManager::initWidgetManager(
      APP_CONSTANTS::APPLICATION_NAME,
      APP_CONSTANTS::APPLICATION_VERSION,
      APP_CONSTANTS::APPLICATION_FILE_EXTENSION);
    
    Aquamarine::uiVizWidgetManager::bootstrapWidgetMap(APP_CONSTANTS::getAppWidgetMap());
    Aquamarine::uiVizIconCache::bootstrapIconMap(Aquamarine::uiVizShared::getViz()->getScale(), APP_CONSTANTS::getIconCacheMap(Aquamarine::uiVizShared::getViz()->getScale()));
}

int APP_CONSTANTS::getAppMajorVersion() {
    return Aquamarine::uiVizWidgetManager::getAppMajorVersion(APP_CONSTANTS::APPLICATION_VERSION);
}

int APP_CONSTANTS::getAppMinorVersion() {
    return Aquamarine::uiVizWidgetManager::getAppMinorVersion(APP_CONSTANTS::APPLICATION_VERSION);
}

int APP_CONSTANTS::getAppPointVersion() {
    return Aquamarine::uiVizWidgetManager::getAppPointVersion(APP_CONSTANTS::APPLICATION_VERSION);
}

const std::string APP_CONSTANTS::DEFAULT_LANGUAGE_XML = ""
"<LANGUAGE name='english'>"
    "<SCALE>Scale</SCALE>"
    "<COLOR>Color</COLOR>"
    "<LABEL>Label</LABEL>"   
    "<OCTAVE>Octave</OCTAVE>"
    "<REGULAR>Regular</REGULAR>"
    "<LAYOUT>Layout</LAYOUT>"
    "<SIDEBAR>Sidebar</SIDEBAR>"   
    "<SMALLER_DIAGRAMS>Smaller Diagrams</SMALLER_DIAGRAMS>"         
    "<STRINGED_CHORD_DIAGRAM>Stringed Diagram</STRINGED_CHORD_DIAGRAM>"
    "<SHOW_OCTAVE>Show octave</SHOW_OCTAVE>"
    "<NOTE_MODE>Note mode</NOTE_MODE>"
    "<DEFAULT>Default</DEFAULT>"
    "<SHARP>Sharp</SHARP>"
    "<FLAT>Flat</FLAT>"
    "<KEY>Key</KEY>"
    "<DEGREE>Degree</DEGREE>"
    "<CHORDS>Chords</CHORDS>"
    "<CHORD>Chord</CHORD>"
    "<SCALES>Scales</SCALES>"
    "<BLACK_AND_WHITE>Black &amp; White</BLACK_AND_WHITE>"    
    "<ALTERNATE_KEYS_DEGREES>Key &amp; Degree</ALTERNATE_KEYS_DEGREES>"
    "<CHORD_VIEW>Fretboard view</CHORD_VIEW>"
    "<NONE>None</NONE>"
    "<SETTINGS>Settings</SETTINGS>"
    "<SOUND>Sound</SOUND>"
    "<FLIP_ORIENTATION>Flip orientation</FLIP_ORIENTATION>"
    "<SWITCH_VIEW>Switch View</SWITCH_VIEW>"
    "<SAVE>Save</SAVE>"
    "<EXPORT_PNG>Export PNG</EXPORT_PNG>"
    "<EXPORT_XML>Export XML</EXPORT_XML>"
    "<EXPORT_HTML>Export HTML</EXPORT_HTML>"    
    "<DELETE>Delete</DELETE>"
    "<AUDITION>Audition</AUDITION>"
    "<LEFT_HAND>Left Hand</LEFT_HAND>"
    "<TUNINGS>Tunings</TUNINGS>"
    "<START_FRET>Start Fret</START_FRET>"
    "<END_FRET>End Fret</END_FRET>"
    "<STRINGS>Strings</STRINGS>"
    "<KEY_PICKER>Key Picker</KEY_PICKER>"
    "<CHORD_WHEEL>Chord Wheel</CHORD_WHEEL>"
    "<CHORD_WHEEL_FOR_KEY>Chord Wheel for Key</CHORD_WHEEL_FOR_KEY>"
    "<CHORD_PROGRESSION>Chord Progression</CHORD_PROGRESSION>"    
    "<CHORD_DESIGNER>Chord Designer</CHORD_DESIGNER>"
    "<SCALE_PICKER>Scale Picker</SCALE_PICKER>"
    "<CHORD_ALTERNATIVES>Chord Alternatives</CHORD_ALTERNATIVES>"    
    "<CHORD_RULES>Chord Rules</CHORD_RULES>"
    "<SCALE_RULES>Scale Rules</SCALE_RULES>"
    "<CHORD_BUCKET>Chord Bucket</CHORD_BUCKET>"
    "<CHORD_BUCKET_SUGGESTER>Chord Suggester</CHORD_BUCKET_SUGGESTER>"    
    
    // <!-- System widgets -->
    "<WIDGET_NAME_uiVizWidget>Widget</WIDGET_NAME_uiVizWidget>"
    "<WIDGET_NAME_uiVizWidgetMenu>Menu</WIDGET_NAME_uiVizWidgetMenu>"
    "<WIDGET_NAME_uiVizWidgetTable>Table</WIDGET_NAME_uiVizWidgetTable>"
    "<WIDGET_NAME_uiVizWidgetMatrix>Matrix</WIDGET_NAME_uiVizWidgetMatrix>"
    "<WIDGET_NAME_uiVizWidgetSequencer>Sequencer</WIDGET_NAME_uiVizWidgetSequencer>"
    "<WIDGET_NAME_uiVizWidgetPianoRoll>Piano Roll</WIDGET_NAME_uiVizWidgetPianoRoll>"
    "<WIDGET_NAME_uiVizWidgetVideoPlayer>Video Player</WIDGET_NAME_uiVizWidgetVideoPlayer>"
    "<WIDGET_NAME_uiVizWidgetVideoGrabber>Video Grabber</WIDGET_NAME_uiVizWidgetVideoGrabber>"
    "<WIDGET_NAME_uiVizWidgetSoundPlayer>Sound Player</WIDGET_NAME_uiVizWidgetSoundPlayer>"
    "<WIDGET_NAME_uiVizWidgetImageView>Image View</WIDGET_NAME_uiVizWidgetImageView>"
    "<WIDGET_NAME_uiVizWidgetDebug>Debug</WIDGET_NAME_uiVizWidgetDebug>"
    "<WIDGET_NAME_uiVizWidgetEventListener>Event Listener</WIDGET_NAME_uiVizWidgetEventListener>"
    "<WIDGET_NAME_uiVizWidgetClipboardMenu>Clipboard</WIDGET_NAME_uiVizWidgetClipboardMenu>"
    "<WIDGET_NAME_uiVizWidgetSettings>Settings</WIDGET_NAME_uiVizWidgetSettings>"
    "<WIDGET_NAME_uiVizWidgetTextEditor>Text Editor</WIDGET_NAME_uiVizWidgetTextEditor>"
    "<WIDGET_NAME_uiVizWidgetFileList>File List</WIDGET_NAME_uiVizWidgetFileList>"
    "<WIDGET_NAME_uiVizWidgetFileLocationsList>File Locations</WIDGET_NAME_uiVizWidgetFileLocationsList>"
    "<WIDGET_NAME_uiVizWidgetFileExplorer>File Explorer</WIDGET_NAME_uiVizWidgetFileExplorer>"
    "<WIDGET_NAME_uiVizWidgetFileLoad>File Load</WIDGET_NAME_uiVizWidgetFileLoad>"
    "<WIDGET_NAME_uiVizWidgetFileSave>File Save</WIDGET_NAME_uiVizWidgetFileSave>"
    "<WIDGET_NAME_uiVizWidgetThemeEditor>Theme Editor</WIDGET_NAME_uiVizWidgetThemeEditor>"
    "<WIDGET_NAME_uiVizWidgetThemePreview>Theme Preview</WIDGET_NAME_uiVizWidgetThemePreview>"    
    "<WIDGET_NAME_uiVizWidgetWidgetList>Widget List</WIDGET_NAME_uiVizWidgetWidgetList>"
    "<WIDGET_NAME_uiVizWidgetDialog>Dialog</WIDGET_NAME_uiVizWidgetDialog>"
    "<WIDGET_NAME_uiVizWidgetEventListener>Listener config</WIDGET_NAME_uiVizWidgetEventListener>"

    // <!-- App Widgets -->
    "<WIDGET_NAME_uiVizWidgetMusical>Musical Widget</WIDGET_NAME_uiVizWidgetMusical>"
    "<WIDGET_NAME_uiVizWidgetMusicalComposer>Musical Composer</WIDGET_NAME_uiVizWidgetMusicalComposer>"
    "<WIDGET_NAME_uiVizWidgetChordWheel>Chord Wheel</WIDGET_NAME_uiVizWidgetChordWheel>"
    "<WIDGET_NAME_uiVizWidgetChordProgression>Chord Progression</WIDGET_NAME_uiVizWidgetChordProgression>"    
    "<WIDGET_NAME_uiVizWidgetChordBucket>Chord Bucket</WIDGET_NAME_uiVizWidgetChordBucket>"
    "<WIDGET_NAME_uiVizWidgetChordDesigner>Chord Designer</WIDGET_NAME_uiVizWidgetChordDesigner>"
    "<WIDGET_NAME_uiVizWidgetChordRules>Chord Rules</WIDGET_NAME_uiVizWidgetChordRules>"
    "<WIDGET_NAME_uiVizWidgetScalePicker>Scale Picker</WIDGET_NAME_uiVizWidgetScalePicker>"
    "<WIDGET_NAME_uiVizWidgetScaleTable>Scale Table</WIDGET_NAME_uiVizWidgetScaleTable>"
    "<WIDGET_NAME_uiVizWidgetChordTable>Chord Table</WIDGET_NAME_uiVizWidgetChordTable>"    
    "<WIDGET_NAME_uiVizWidgetKeyPicker>Circle of Fifths</WIDGET_NAME_uiVizWidgetKeyPicker>"
    "<WIDGET_NAME_uiVizWigetStringedInstrument>Stringed Instrument</WIDGET_NAME_uiVizWigetStringedInstrument>"
    "<WIDGET_NAME_uiVizWidgetGuitar>Guitar</WIDGET_NAME_uiVizWidgetGuitar>"
    "<WIDGET_NAME_uiVizWidgetBassGuitar>Bass Guitar</WIDGET_NAME_uiVizWidgetBassGuitar>"
    "<WIDGET_NAME_uiVizWidgetTutor>Tutor</WIDGET_NAME_uiVizWidgetTutor>"
    "<WIDGET_NAME_uiVizWidgetUnitTests>Unit Tests</WIDGET_NAME_uiVizWidgetUnitTests>"
    "<WIDGET_NAME_uiVizWidgetMainMenu>Main Menu</WIDGET_NAME_uiVizWidgetMainMenu>"
    "<WIDGET_NAME_uiVizWidgetOmniMenu>Omni Menu</WIDGET_NAME_uiVizWidgetOmniMenu>"
    "<WIDGET_NAME_uiVizWidgetOmniMenuSearchResults>Omni Menu Results</WIDGET_NAME_uiVizWidgetOmniMenuSearchResults>"
    "<WIDGET_NAME_uiVizWidgetOmniMenuLinks>Omni Menu Links</WIDGET_NAME_uiVizWidgetOmniMenuLinks>"
    "<WIDGET_NAME_uiVizWidgetLicence>Licence</WIDGET_NAME_uiVizWidgetLicence>"
    "<WIDGET_NAME_uiVizWidgetGetStarted>Get Started</WIDGET_NAME_uiVizWidgetGetStarted>"
    "<WIDGET_NAME_uiVizWidgetNotifications>Notifications</WIDGET_NAME_uiVizWidgetNotifications>"
    "<WIDGET_NAME_uiVizWidgetEventListenerMusical>Musical Listener config</WIDGET_NAME_uiVizWidgetEventListenerMusical>"


"</LANGUAGE>";

/* IMPORT ALL SUPPORTED WIDGET CLASSES HERE */
#include "../uiViz/widget/uiVizWidget.h"

/* -------> YOU OWN WIDGETS HERE <------- */
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetEventListenerMusical.h"
#include "uiVizWidgetMusicalComposer.h"
#include "uiVizWidgetChordWheel.h"
#include "uiVizWidgetChordWheelForKey.h"
#include "uiVizWidgetChordProgression.h"
#include "uiVizWidgetChordBucket.h"
#include "uiVizWidgetChordBucketSuggester.h"
#include "uiVizWidgetChordDesigner.h"
#include "uiVizWidgetChordRules.h"
#include "uiVizWidgetScalePicker.h"
#include "uiVizWidgetScaleTable.h"
#include "uiVizWidgetChordTable.h"
#include "uiVizWidgetNotesTable.h"
#include "uiVizWidgetKeyPicker.h"
#include "uiVizWidgetKeyPickerPopout.h"
#include "uiVizWigetStringedInstrument.h"
#include "uiVizWidgetGuitar.h"
#include "uiVizWidgetBassGuitar.h"
#include "uiVizWidgetTutor.h"
#include "uiVizWidgetUnitTests.h"
#include "uiVizWidgetMainMenu.h"
#include "uiVizWidgetLicence.h"

/* DEFINE ALL SUPPORTED WIDGET CLASS NAME HERE */
//const string uiVizWidgetManager::WIDGET_CLASS_BASE = "uiVizWidgetBase";
const std::string APP_CONSTANTS::WIDGET_CLASS = "uiVizWidget";
const std::string APP_CONSTANTS::WIDGET_CLASS_MUSICAL = "uiVizWidgetMusical";
const std::string APP_CONSTANTS::WIDGET_CLASS_EVENT_LISTENER_MUSICAL = "uiVizWidgetEventListenerMusical";
const std::string APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER = "uiVizWidgetMusicalComposer";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL = "uiVizWidgetChordWheel";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL_FOR_KEY = "uiVizWidgetChordWheelForKey";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION = "uiVizWidgetChordProgression";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET = "uiVizWidgetChordBucket";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER = "uiVizWidgetChordBucketSuggester";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER = "uiVizWidgetChordDesigner";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_RULES = "uiVizWidgetChordRules";
const std::string APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER = "uiVizWidgetScalePicker";
const std::string APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE = "uiVizWidgetScaleTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_TABLE = "uiVizWidgetChordTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE = "uiVizWidgetNotesTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER = "uiVizWidgetKeyPicker";
const std::string APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT = "uiVizWidgetKeyPickerPopout";
const std::string APP_CONSTANTS::WIDGET_CLASS_STRINGED_INSTRUMENT = "uiVizWigetStringedInstrument";
const std::string APP_CONSTANTS::WIDGET_CLASS_GUITAR = "uiVizWidgetGuitar";
const std::string APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR = "uiVizWidgetBassGuitar";
const std::string APP_CONSTANTS::WIDGET_CLASS_TUTOR = "uiVizWidgetTutor";
const std::string APP_CONSTANTS::WIDGET_CLASS_ABOUT = "uiVizWidgetAbout";
const std::string APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS = "uiVizWidgetUnitTests";
const std::string APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU = "uiVizWidgetMainMenu";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU = "uiVizWidgetOmniMenu";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS = "uiVizWidgetOmniMenuSearchResults";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_LINKS = "uiVizWidgetOmniMenuLinks";
const std::string APP_CONSTANTS::WIDGET_CLASS_LICENCE = "uiVizWidgetLicence";
const std::string APP_CONSTANTS::WIDGET_CLASS_GET_STARTED = "uiVizWidgetGetStarted";
const std::string APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS = "uiVizWidgetNotifications";
const std::string APP_CONSTANTS::WIDGET_CLASS_TEXT_EDITOR = "uiVizWidgetTextEditor";

const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_DESIGNER = -5000;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL = -5001;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL_FOR_KEY = -5001;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_KEY_PICKER = -5002;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_SCALE_PICKER = -5003;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_GUITAR = -5004;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET = -5005;



template<typename T> Aquamarine::uiVizWidget * createWidget(string persistentId, string widgetXML) { return new T(persistentId, widgetXML); }
typedef std::map<std::string, Aquamarine::uiVizWidget*(*)(string persistentId, string widgetXML)> widget_map_type;

Aquamarine::uiVizWidgetManager::widget_map_type APP_CONSTANTS::getAppWidgetMap() {
    
    Aquamarine::uiVizWidgetManager::widget_map_type appWidgetMap;
    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS] = &createWidget<Aquamarine::uiVizWidget>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MUSICAL] = &createWidget<uiVizWidgetMusical>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_EVENT_LISTENER_MUSICAL] = &createWidget<uiVizWidgetEventListenerMusical>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER] = &createWidget<uiVizWidgetMusicalComposer>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL] = &createWidget<uiVizWidgetChordWheel>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL_FOR_KEY] = &createWidget<uiVizWidgetChordWheelForKey>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION] = &createWidget<uiVizWidgetChordProgression>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET] = &createWidget<uiVizWidgetChordBucket>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER] = &createWidget<uiVizWidgetChordBucketSuggester>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER] = &createWidget<uiVizWidgetChordDesigner>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_RULES] = &createWidget<uiVizWidgetChordRules>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER] = &createWidget<uiVizWidgetScalePicker>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE] = &createWidget<uiVizWidgetScaleTable>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_TABLE] = &createWidget<uiVizWidgetChordTable>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE] = &createWidget<uiVizWidgetNotesTable>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER] = &createWidget<uiVizWidgetKeyPicker>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT] = &createWidget<uiVizWidgetKeyPickerPopout>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_STRINGED_INSTRUMENT] = &createWidget<uiVizWigetStringedInstrument>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_GUITAR] = &createWidget<uiVizWidgetGuitar>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR] = &createWidget<uiVizWidgetBassGuitar>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_TUTOR] = &createWidget<uiVizWidgetTutor>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_ABOUT] = &createWidget<uiVizWidgetAbout>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS] = &createWidget<uiVizWidgetUnitTests>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU] = &createWidget<uiVizWidgetMainMenu>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU] = &createWidget<uiVizWidgetOmniMenu>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS] = &createWidget<uiVizWidgetOmniMenuSearchResults>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_LINKS] = &createWidget<uiVizWidgetOmniMenuLinks>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_LICENCE] = &createWidget<uiVizWidgetLicence>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_GET_STARTED] = &createWidget<uiVizWidgetGetStarted>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS] = &createWidget<uiVizWidgetNotifications>;
    
    return appWidgetMap;
}

std::map<std::string, Aquamarine::uiVizIcon*> APP_CONSTANTS::getIconCacheMap(float scale) {
    
    std::map<std::string, Aquamarine::uiVizIcon*> iconCacheMap;
    
    int iconSizeFromFile = 48; // The files we are sourcing are sized at 48x48px
    
    int iconSizeReg = 18;
    int iconSizeMed = 27;
    int iconSizeLrg = 40;
    
    float iconSizeRegScale = ((float)iconSizeReg / (float)iconSizeFromFile) * (float)scale; // When scale is 1, this is the regular size
    float iconSizeMedScale = (iconSizeMed / (float)iconSizeFromFile) * (float)scale;
    float iconSizeLrgScale = (iconSizeLrg / (float)iconSizeFromFile) * (float)scale;
    
    int iconSizeRegScaledSize = iconSizeFromFile * (float)iconSizeRegScale;
    int iconSizeMedScaledSize = iconSizeFromFile * (float)iconSizeMedScale;
    int iconSizeLrgScaledSize = iconSizeFromFile * (float)iconSizeLrgScale;
    
    iconCacheMap["MED_CONTENT_THEORY_LABEL"] = new Aquamarine::uiVizIcon("ui/svg/ic_info_outline_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_THEORY_COLOR"] = new Aquamarine::uiVizIcon("ui/svg/ic_color_lens_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_THEORY_SCALE"] = new Aquamarine::uiVizIcon("ui/svg/ic_tonality_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_SETTINGS"] = new Aquamarine::uiVizIcon("ui/svg/ic_settings_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_VIEW"] = new Aquamarine::uiVizIcon("ui/svg/ic_view_compact_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, 0);
    iconCacheMap["MED_ADD_CIRCLE"] = new Aquamarine::uiVizIcon("ui/svg/ic_add_circle_outline_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::ADD_CIRCLE);
    iconCacheMap["MED_MENU"] = new Aquamarine::uiVizIcon("ui/svg/ic_apps_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::MENU);
    iconCacheMap["MED_KEY"] = new Aquamarine::uiVizIcon("ui/svg/ic_vpn_key_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_RULES"] = new Aquamarine::uiVizIcon("ui/svg/ic_tune_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_EDIT"] = new Aquamarine::uiVizIcon("ui/svg/ic_edit_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_TICK"] = new Aquamarine::uiVizIcon("ui/svg/ic_check_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, Aquamarine::uiVizIconCache::IconTag::MED_KEY);

    iconCacheMap["MED_INST_ELECTRIC_GUIT"] = new Aquamarine::uiVizIcon("ui/music-icons/electric-guitar.svg", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, 0);

    /* Icon images for Widgets - If a custom image / ico is required for a widget, specify it here */
    iconCacheMap["uiVizWidgetGuitar"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetGuitar.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_GUITAR);
/*    
    iconCacheMap["uiVizWidgetChordDesigner"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetChordDesigner.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_DESIGNER);
    iconCacheMap["uiVizWidgetChordWheel"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetChordWheel.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL);
    iconCacheMap["uiVizWidgetKeyPicker"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetKeyPicker.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_KEY_PICKER);
    iconCacheMap["uiVizWidgetScalePicker"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetScalePicker.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_SCALE_PICKER);    
*/
    iconCacheMap["uiVizWidgetChordBucket"] = new Aquamarine::uiVizIcon("ui/images/uiVizWidgetChordBucket.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);
    iconCacheMap["MED_CONTENT_BUCKET"] = new Aquamarine::uiVizIcon("ui/images/bucket.png", Aquamarine::uiVizCoord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::uiVizIcon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);




    return iconCacheMap;
}


const std::string APP_WIDGET_EVENT::SET_SELECTED_KEY = "set_selected_key";
const std::string APP_WIDGET_EVENT::ADD_SELECTED_CHORD = "add_selected_chord";
const std::string APP_WIDGET_EVENT::ADD_SELECTED_NOTE = "add_selected_note";
const std::string APP_WIDGET_EVENT::SET_SELECTED_SCALE = "set_selected_scale";
const std::string APP_WIDGET_EVENT::SET_HOVERED_CHORD = "set_hovered_chord";


#ifdef TARGET_OF_IOS
    std::string mIOSGetDocumentsDirectory = "";
    void APP_CONSTANTS::setIOSGetDocumentsDirectory(std::string val) {
        mIOSGetDocumentsDirectory = val;
    }
    std::string APP_CONSTANTS::getIOSGetDocumentsDirectory() {
        return mIOSGetDocumentsDirectory;
    }
#endif
