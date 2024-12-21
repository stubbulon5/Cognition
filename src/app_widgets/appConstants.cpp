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

    Aquamarine::WidgetManager::initWidgetManager(
      APP_CONSTANTS::APPLICATION_NAME,
      APP_CONSTANTS::APPLICATION_VERSION,
      APP_CONSTANTS::APPLICATION_FILE_EXTENSION,
      true
    );
    
    Aquamarine::WidgetManager::bootstrapWidgetMap(APP_CONSTANTS::getAppWidgetMap());
    Aquamarine::IconCache::bootstrapIconMap(Aquamarine::Shared::getViz()->getScale(), APP_CONSTANTS::getIconCacheMap(Aquamarine::Shared::getViz()->getScale()));
}

int APP_CONSTANTS::getAppMajorVersion() {
    return Aquamarine::WidgetManager::getAppMajorVersion(APP_CONSTANTS::APPLICATION_VERSION);
}

int APP_CONSTANTS::getAppMinorVersion() {
    return Aquamarine::WidgetManager::getAppMinorVersion(APP_CONSTANTS::APPLICATION_VERSION);
}

int APP_CONSTANTS::getAppPointVersion() {
    return Aquamarine::WidgetManager::getAppPointVersion(APP_CONSTANTS::APPLICATION_VERSION);
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
    "<WIDGET_NAME_Widget>Widget</WIDGET_NAME_Widget>"
    "<WIDGET_NAME_WidgetMenu>Menu</WIDGET_NAME_WidgetMenu>"
    "<WIDGET_NAME_WidgetTable>Table</WIDGET_NAME_WidgetTable>"
    "<WIDGET_NAME_WidgetMatrix>Matrix</WIDGET_NAME_WidgetMatrix>"
    "<WIDGET_NAME_WidgetSequencer>Sequencer</WIDGET_NAME_WidgetSequencer>"
    "<WIDGET_NAME_WidgetPianoRoll>Piano Roll</WIDGET_NAME_WidgetPianoRoll>"
    "<WIDGET_NAME_WidgetVideoPlayer>Video Player</WIDGET_NAME_WidgetVideoPlayer>"
    "<WIDGET_NAME_WidgetVideoGrabber>Video Grabber</WIDGET_NAME_WidgetVideoGrabber>"
    "<WIDGET_NAME_WidgetSoundPlayer>Sound Player</WIDGET_NAME_WidgetSoundPlayer>"
    "<WIDGET_NAME_WidgetImageView>Image View</WIDGET_NAME_WidgetImageView>"
    "<WIDGET_NAME_WidgetDebug>Debug</WIDGET_NAME_WidgetDebug>"
    "<WIDGET_NAME_WidgetEventListener>Event Listener</WIDGET_NAME_WidgetEventListener>"
    "<WIDGET_NAME_WidgetClipboardMenu>Clipboard</WIDGET_NAME_WidgetClipboardMenu>"
    "<WIDGET_NAME_WidgetSettings>Settings</WIDGET_NAME_WidgetSettings>"
    "<WIDGET_NAME_WidgetTextEditor>Text Editor</WIDGET_NAME_WidgetTextEditor>"
    "<WIDGET_NAME_WidgetFileList>File List</WIDGET_NAME_WidgetFileList>"
    "<WIDGET_NAME_WidgetFileLocationsList>File Locations</WIDGET_NAME_WidgetFileLocationsList>"
    "<WIDGET_NAME_WidgetFileExplorer>File Explorer</WIDGET_NAME_WidgetFileExplorer>"
    "<WIDGET_NAME_WidgetFileLoad>File Load</WIDGET_NAME_WidgetFileLoad>"
    "<WIDGET_NAME_WidgetFileSave>File Save</WIDGET_NAME_WidgetFileSave>"
    "<WIDGET_NAME_WidgetThemeEditor>Theme Editor</WIDGET_NAME_WidgetThemeEditor>"
    "<WIDGET_NAME_WidgetThemePreview>Theme Preview</WIDGET_NAME_WidgetThemePreview>"    
    "<WIDGET_NAME_WidgetWidgetList>Widget List</WIDGET_NAME_WidgetWidgetList>"
    "<WIDGET_NAME_WidgetDialog>Dialog</WIDGET_NAME_WidgetDialog>"
    "<WIDGET_NAME_WidgetEventListener>Listener config</WIDGET_NAME_WidgetEventListener>"

    // <!-- App Widgets -->
    "<WIDGET_NAME_WidgetMusical>Musical Widget</WIDGET_NAME_WidgetMusical>"
    "<WIDGET_NAME_WidgetMusicalComposer>Musical Composer</WIDGET_NAME_WidgetMusicalComposer>"
    "<WIDGET_NAME_WidgetChordWheel>Chord Wheel</WIDGET_NAME_WidgetChordWheel>"
    "<WIDGET_NAME_WidgetChordProgression>Chord Progression</WIDGET_NAME_WidgetChordProgression>"    
    "<WIDGET_NAME_WidgetChordBucket>Chord Bucket</WIDGET_NAME_WidgetChordBucket>"
    "<WIDGET_NAME_WidgetChordDesigner>Chord Designer</WIDGET_NAME_WidgetChordDesigner>"
    "<WIDGET_NAME_WidgetChordRules>Chord Rules</WIDGET_NAME_WidgetChordRules>"
    "<WIDGET_NAME_WidgetScalePicker>Scale Picker</WIDGET_NAME_WidgetScalePicker>"
    "<WIDGET_NAME_WidgetScaleTable>Scale Table</WIDGET_NAME_WidgetScaleTable>"
    "<WIDGET_NAME_WidgetChordTable>Chord Table</WIDGET_NAME_WidgetChordTable>"    
    "<WIDGET_NAME_WidgetKeyPicker>Circle of Fifths</WIDGET_NAME_WidgetKeyPicker>"
    "<WIDGET_NAME_WidgetStringedInstrument>Stringed Instrument</WIDGET_NAME_WidgetStringedInstrument>"
    "<WIDGET_NAME_WidgetGuitar>Guitar</WIDGET_NAME_WidgetGuitar>"
    "<WIDGET_NAME_WidgetBassGuitar>Bass Guitar</WIDGET_NAME_WidgetBassGuitar>"
    "<WIDGET_NAME_WidgetTutor>Tutor</WIDGET_NAME_WidgetTutor>"
    "<WIDGET_NAME_WidgetUnitTests>Unit Tests</WIDGET_NAME_WidgetUnitTests>"
    "<WIDGET_NAME_WidgetMainMenu>Main Menu</WIDGET_NAME_WidgetMainMenu>"
    "<WIDGET_NAME_WidgetOmniMenu>Omni Menu</WIDGET_NAME_WidgetOmniMenu>"
    "<WIDGET_NAME_WidgetOmniMenuSearchResults>Omni Menu Results</WIDGET_NAME_WidgetOmniMenuSearchResults>"
    "<WIDGET_NAME_WidgetOmniMenuLinks>Omni Menu Links</WIDGET_NAME_WidgetOmniMenuLinks>"
    "<WIDGET_NAME_WidgetLicence>Licence</WIDGET_NAME_WidgetLicence>"
    "<WIDGET_NAME_WidgetGetStarted>Get Started</WIDGET_NAME_WidgetGetStarted>"
    "<WIDGET_NAME_WidgetNotifications>Notifications</WIDGET_NAME_WidgetNotifications>"
    "<WIDGET_NAME_WidgetEventListenerMusical>Musical Listener config</WIDGET_NAME_WidgetEventListenerMusical>"


"</LANGUAGE>";

/* IMPORT ALL SUPPORTED WIDGET CLASSES HERE */
#include "../viz/widget/Widget.h"

/* -------> YOU OWN WIDGETS HERE <------- */
#include "WidgetMusical.h"
#include "WidgetEventListenerMusical.h"
#include "WidgetMusicalComposer.h"
#include "WidgetChordWheel.h"
#include "WidgetChordWheelForKey.h"
#include "WidgetChordProgression.h"
#include "WidgetChordBucket.h"
#include "WidgetChordBucketSuggester.h"
#include "WidgetChordDesigner.h"
#include "WidgetChordRules.h"
#include "WidgetScalePicker.h"
#include "WidgetScaleTable.h"
#include "WidgetChordTable.h"
#include "WidgetNotesTable.h"
#include "WidgetKeyPicker.h"
#include "WidgetKeyPickerPopout.h"
#include "WidgetStringedInstrument.h"
#include "WidgetGuitar.h"
#include "WidgetBassGuitar.h"
#include "WidgetTutor.h"
#include "WidgetUnitTests.h"
#include "WidgetMainMenu.h"
#include "WidgetLicence.h"

/* DEFINE ALL SUPPORTED WIDGET CLASS NAME HERE */
//const string WidgetManager::WIDGET_CLASS_BASE = "WidgetBase";
const std::string APP_CONSTANTS::WIDGET_CLASS = "Widget";
const std::string APP_CONSTANTS::WIDGET_CLASS_MUSICAL = "WidgetMusical";
const std::string APP_CONSTANTS::WIDGET_CLASS_EVENT_LISTENER_MUSICAL = "WidgetEventListenerMusical";
const std::string APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER = "WidgetMusicalComposer";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL = "WidgetChordWheel";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL_FOR_KEY = "WidgetChordWheelForKey";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION = "WidgetChordProgression";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET = "WidgetChordBucket";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER = "WidgetChordBucketSuggester";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER = "WidgetChordDesigner";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_RULES = "WidgetChordRules";
const std::string APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER = "WidgetScalePicker";
const std::string APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE = "WidgetScaleTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_CHORD_TABLE = "WidgetChordTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE = "WidgetNotesTable";
const std::string APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER = "WidgetKeyPicker";
const std::string APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT = "WidgetKeyPickerPopout";
const std::string APP_CONSTANTS::WIDGET_CLASS_STRINGED_INSTRUMENT = "WidgetStringedInstrument";
const std::string APP_CONSTANTS::WIDGET_CLASS_GUITAR = "WidgetGuitar";
const std::string APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR = "WidgetBassGuitar";
const std::string APP_CONSTANTS::WIDGET_CLASS_TUTOR = "WidgetTutor";
const std::string APP_CONSTANTS::WIDGET_CLASS_ABOUT = "WidgetAbout";
const std::string APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS = "WidgetUnitTests";
const std::string APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU = "WidgetMainMenu";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU = "WidgetOmniMenu";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS = "WidgetOmniMenuSearchResults";
const std::string APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_LINKS = "WidgetOmniMenuLinks";
const std::string APP_CONSTANTS::WIDGET_CLASS_LICENCE = "WidgetLicence";
const std::string APP_CONSTANTS::WIDGET_CLASS_GET_STARTED = "WidgetGetStarted";
const std::string APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS = "WidgetNotifications";
const std::string APP_CONSTANTS::WIDGET_CLASS_TEXT_EDITOR = "WidgetTextEditor";

const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_DESIGNER = -5000;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL = -5001;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL_FOR_KEY = -5001;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_KEY_PICKER = -5002;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_SCALE_PICKER = -5003;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_GUITAR = -5004;
const int APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET = -5005;



template<typename T> Aquamarine::Widget * createWidget(string persistentId, string widgetXML) { return new T(persistentId, widgetXML); }
typedef std::map<std::string, Aquamarine::Widget*(*)(string persistentId, string widgetXML)> widget_map_type;

Aquamarine::WidgetManager::widget_map_type APP_CONSTANTS::getAppWidgetMap() {
    
    Aquamarine::WidgetManager::widget_map_type appWidgetMap;
    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS] = &createWidget<Aquamarine::Widget>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MUSICAL] = &createWidget<WidgetMusical>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_EVENT_LISTENER_MUSICAL] = &createWidget<WidgetEventListenerMusical>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER] = &createWidget<WidgetMusicalComposer>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL] = &createWidget<WidgetChordWheel>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL_FOR_KEY] = &createWidget<WidgetChordWheelForKey>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION] = &createWidget<WidgetChordProgression>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET] = &createWidget<WidgetChordBucket>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER] = &createWidget<WidgetChordBucketSuggester>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER] = &createWidget<WidgetChordDesigner>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_RULES] = &createWidget<WidgetChordRules>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER] = &createWidget<WidgetScalePicker>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE] = &createWidget<WidgetScaleTable>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_CHORD_TABLE] = &createWidget<WidgetChordTable>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE] = &createWidget<WidgetNotesTable>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER] = &createWidget<WidgetKeyPicker>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT] = &createWidget<WidgetKeyPickerPopout>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_STRINGED_INSTRUMENT] = &createWidget<WidgetStringedInstrument>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_GUITAR] = &createWidget<WidgetGuitar>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR] = &createWidget<WidgetBassGuitar>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_TUTOR] = &createWidget<WidgetTutor>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_ABOUT] = &createWidget<WidgetAbout>;    
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS] = &createWidget<WidgetUnitTests>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU] = &createWidget<WidgetMainMenu>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU] = &createWidget<WidgetOmniMenu>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS] = &createWidget<WidgetOmniMenuSearchResults>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_LINKS] = &createWidget<WidgetOmniMenuLinks>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_LICENCE] = &createWidget<WidgetLicence>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_GET_STARTED] = &createWidget<WidgetGetStarted>;
    appWidgetMap[APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS] = &createWidget<WidgetNotifications>;
    
    return appWidgetMap;
}

std::map<std::string, Aquamarine::Icon*> APP_CONSTANTS::getIconCacheMap(float scale) {
    
    std::map<std::string, Aquamarine::Icon*> iconCacheMap;
    
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
    
    iconCacheMap["MED_CONTENT_THEORY_LABEL"] = new Aquamarine::Icon("ui/svg/ic_info_outline_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_THEORY_COLOR"] = new Aquamarine::Icon("ui/svg/ic_color_lens_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_THEORY_SCALE"] = new Aquamarine::Icon("ui/svg/ic_tonality_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_SETTINGS"] = new Aquamarine::Icon("ui/svg/ic_settings_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
    iconCacheMap["MED_CONTENT_VIEW"] = new Aquamarine::Icon("ui/svg/ic_view_compact_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, 0);
    iconCacheMap["MED_ADD_CIRCLE"] = new Aquamarine::Icon("ui/svg/ic_add_circle_outline_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::ADD_CIRCLE);
    iconCacheMap["MED_MENU"] = new Aquamarine::Icon("ui/svg/ic_apps_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MENU);
    iconCacheMap["MED_KEY"] = new Aquamarine::Icon("ui/svg/ic_vpn_key_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_RULES"] = new Aquamarine::Icon("ui/svg/ic_tune_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_EDIT"] = new Aquamarine::Icon("ui/svg/ic_edit_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
    iconCacheMap["MED_CONTENT_TICK"] = new Aquamarine::Icon("ui/svg/ic_check_"+ofToString(iconSizeFromFile)+"px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);

    iconCacheMap["MED_INST_ELECTRIC_GUIT"] = new Aquamarine::Icon("ui/music-icons/electric-guitar.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, 0);

    /* Icon images for Widgets - If a custom image / ico is required for a widget, specify it here */
    iconCacheMap["WidgetGuitar"] = new Aquamarine::Icon("ui/images/WidgetGuitar.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_GUITAR);
/*    
    iconCacheMap["WidgetChordDesigner"] = new Aquamarine::Icon("ui/images/WidgetChordDesigner.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_DESIGNER);
    iconCacheMap["WidgetChordWheel"] = new Aquamarine::Icon("ui/images/WidgetChordWheel.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL);
    iconCacheMap["WidgetKeyPicker"] = new Aquamarine::Icon("ui/images/WidgetKeyPicker.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_KEY_PICKER);
    iconCacheMap["WidgetScalePicker"] = new Aquamarine::Icon("ui/images/WidgetScalePicker.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_SCALE_PICKER);    
*/
    iconCacheMap["WidgetChordBucket"] = new Aquamarine::Icon("ui/images/WidgetChordBucket.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);
    iconCacheMap["MED_CONTENT_BUCKET"] = new Aquamarine::Icon("ui/images/bucket.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);




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
