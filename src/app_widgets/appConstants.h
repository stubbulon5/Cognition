#pragma once
#include <string>
#include "../uiViz/Shared.h"
#include "../uiViz/WidgetManager.h"

// #include "ofxAquamarine.h"


//------------------------------ APP CONSTANTS --------------------------------

class APP_CONSTANTS {
public:
    static void BOOTSTRAP_APP();
    
    static int getAppMajorVersion();
    static int getAppMinorVersion();
    static int getAppPointVersion();
    
    static const std::string APPLICATION_NAME;
    static const std::string APPLICATION_VERSION;
    static const std::string APPLICATION_FILE_EXTENSION;
    static const std::string APPLICATION_LIC_ENC_KEY;
    static const std::string APPLICATION_WEBSITE;    

    static const std::string APPLICATION_SETTINGS_FOLDER();
    static const std::string APPLICATION_CACHE_FOLDER();
    static const std::string APPLICATION_SETTINGS_FILE();
    static const std::string APPLICATION_SETTINGS_FILE_FULL_PATH();  
    static const std::string APPLICATION_LIC_ENC_KEY_FILE();

    static const std::string DEFAULT_LANGUAGE_XML;
    
    static const std::string WIDGET_CLASS;
    static const std::string WIDGET_CLASS_MUSICAL;
    static const std::string WIDGET_CLASS_EVENT_LISTENER_MUSICAL;    
    static const std::string WIDGET_CLASS_MUSICAL_COMPOSER;
    static const std::string WIDGET_CLASS_CHORD_WHEEL;
    static const std::string WIDGET_CLASS_CHORD_WHEEL_FOR_KEY;
    static const std::string WIDGET_CLASS_CHORD_PROGRESSION;    
    static const std::string WIDGET_CLASS_KEY_PICKER;
    static const std::string WIDGET_CLASS_KEY_PICKER_POPOUT;
    static const std::string WIDGET_CLASS_CHORD_BUCKET;
    static const std::string WIDGET_CLASS_CHORD_BUCKET_SUGGESTER;    
    static const std::string WIDGET_CLASS_CHORD_DESIGNER;
    static const std::string WIDGET_CLASS_CHORD_RULES;
    static const std::string WIDGET_CLASS_SCALE_PICKER;
    static const std::string WIDGET_CLASS_SCALE_TABLE;
    static const std::string WIDGET_CLASS_CHORD_TABLE;
    static const std::string WIDGET_CLASS_NOTES_TABLE;
    static const std::string WIDGET_CLASS_STRINGED_INSTRUMENT;
    static const std::string WIDGET_CLASS_GUITAR;
    static const std::string WIDGET_CLASS_BASS_GUITAR;
    static const std::string WIDGET_CLASS_TUTOR;
    static const std::string WIDGET_CLASS_ABOUT;    
    static const std::string WIDGET_CLASS_UNIT_TESTS;
    static const std::string WIDGET_CLASS_MAIN_MENU;
    static const std::string WIDGET_CLASS_OMNI_MENU;
    static const std::string WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS;
    static const std::string WIDGET_CLASS_OMNI_MENU_LINKS;
    static const std::string WIDGET_CLASS_LICENCE;
    static const std::string WIDGET_CLASS_GET_STARTED;
    static const std::string WIDGET_CLASS_NOTIFICATIONS;    
    static const std::string WIDGET_CLASS_TEXT_EDITOR;    
    
    static const int ICON_WIDGET_CLASS_CHORD_DESIGNER;
    static const int ICON_WIDGET_CLASS_CHORD_WHEEL;
    static const int ICON_WIDGET_CLASS_CHORD_WHEEL_FOR_KEY;    
    static const int ICON_WIDGET_CLASS_KEY_PICKER;
    static const int ICON_WIDGET_CLASS_SCALE_PICKER;
    static const int ICON_WIDGET_CLASS_GUITAR;
    static const int ICON_WIDGET_CLASS_CHORD_BUCKET;
    
    static Aquamarine::WidgetManager::widget_map_type getAppWidgetMap();
    
    static std::map<std::string, Aquamarine::uiVizIcon*> getIconCacheMap(float scale);

#ifdef TARGET_OF_IOS
    static void setIOSGetDocumentsDirectory(std::string val);
    static std::string getIOSGetDocumentsDirectory();
#endif

};

class APP_WIDGET_EVENT {
public:
    static const std::string SET_SELECTED_KEY;
    static const std::string ADD_SELECTED_CHORD;
    static const std::string ADD_SELECTED_NOTE;    
    static const std::string SET_SELECTED_SCALE;
    static const std::string SET_HOVERED_CHORD;
};

