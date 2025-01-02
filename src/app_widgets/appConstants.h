#pragma once
#include "ofxAquamarine.h"

class APP_CONSTANTS {
public:

    static const string APPLICATION_WEBSITE;
    static const string DEFAULT_LANGUAGE_XML;
    
    static const string WIDGET_CLASS;
    static const string WIDGET_CLASS_MUSICAL;
    static const string WIDGET_CLASS_EVENT_LISTENER_MUSICAL;    
    static const string WIDGET_CLASS_MUSICAL_COMPOSER;
    static const string WIDGET_CLASS_CHORD_WHEEL;
    static const string WIDGET_CLASS_CHORD_WHEEL_FOR_KEY;
    static const string WIDGET_CLASS_CHORD_PROGRESSION;    
    static const string WIDGET_CLASS_KEY_PICKER;
    static const string WIDGET_CLASS_KEY_PICKER_POPOUT;
    static const string WIDGET_CLASS_CHORD_BUCKET;
    static const string WIDGET_CLASS_CHORD_BUCKET_SUGGESTER;    
    static const string WIDGET_CLASS_CHORD_DESIGNER;
    static const string WIDGET_CLASS_CHORD_RULES;
    static const string WIDGET_CLASS_SCALE_PICKER;
    static const string WIDGET_CLASS_SCALE_TABLE;
    static const string WIDGET_CLASS_CHORD_TABLE;
    static const string WIDGET_CLASS_NOTES_TABLE;
    static const string WIDGET_CLASS_STRINGED_INSTRUMENT;
    static const string WIDGET_CLASS_GUITAR;
    static const string WIDGET_CLASS_BASS_GUITAR;
    static const string WIDGET_CLASS_TUTOR;
    static const string WIDGET_CLASS_ABOUT;    
    static const string WIDGET_CLASS_UNIT_TESTS;
    static const string WIDGET_CLASS_MAIN_MENU;
    static const string WIDGET_CLASS_OMNI_MENU;
    static const string WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS;
    static const string WIDGET_CLASS_OMNI_MENU_LINKS;
    static const string WIDGET_CLASS_LICENCE;
    static const string WIDGET_CLASS_GET_STARTED;
    static const string WIDGET_CLASS_NOTIFICATIONS;    
    static const string WIDGET_CLASS_TEXT_EDITOR;    
    
    static const int ICON_WIDGET_CLASS_CHORD_DESIGNER;
    static const int ICON_WIDGET_CLASS_CHORD_WHEEL;
    static const int ICON_WIDGET_CLASS_CHORD_WHEEL_FOR_KEY;    
    static const int ICON_WIDGET_CLASS_KEY_PICKER;
    static const int ICON_WIDGET_CLASS_SCALE_PICKER;
    static const int ICON_WIDGET_CLASS_GUITAR;
    static const int ICON_WIDGET_CLASS_CHORD_BUCKET;
    
    


    // static Aquamarine::widget_map_type getAppWidgetMap();




    static std::function<void ()> registerCustomWidgets();
    static map<string, Aquamarine::Icon*> getIconCacheMap(float scale);

#ifdef TARGET_OF_IOS
    static void setIOSGetDocumentsDirectory(string val);
    static string getIOSGetDocumentsDirectory();
#endif

};

class APP_WIDGET_EVENT {
public:
    static const string SET_SELECTED_KEY;
    static const string ADD_SELECTED_CHORD;
    static const string ADD_SELECTED_NOTE;    
    static const string SET_SELECTED_SCALE;
    static const string SET_HOVERED_CHORD;
};

