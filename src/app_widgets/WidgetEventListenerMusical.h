
#pragma once
#include "ofxAquamarine.h"
#include "WidgetKeyPicker.h"

class WidgetEventListenerMusical : public Aquamarine::WidgetEventListener {
    
public:
    
    WidgetEventListenerMusical(string persistentId, string widgetXML) : WidgetEventListener(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~WidgetEventListenerMusical() {
    }

    virtual void update(Aquamarine::WidgetContext context) override {    
        WidgetEventListener::update(context);
    }

	virtual void onWidgetWasJustInitialized() override {
    
    }
    
    void draw(Aquamarine::WidgetContext context) override {


        if(context.isInitialDraw) {
            Aquamarine::WidgetEventListener::onWidgetWasJustInitialized();

            Aquamarine::WidgetMenu* settingsMenu = getSettingsMenu();
            if (settingsMenu != nullptr) {
                settingsMenu->addOrUpdateMenuTab(
                    // ----------------------------------------------------------------------------
                    // Label mode menu
                    // ----------------------------------------------------------------------------
                    Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("LABEL"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, 
                    keyPickerMenuItem
                    // {
                    //     WidgetMenuItem(Aquamarine::Shared::lang("NONE"), 1), 
                    //     WidgetMenuItem(Aquamarine::Shared::lang("KEY"), 1, false, true), 
                    //     WidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), 1), 
                    //     WidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                    // }
                    )
                );
            }                
        }

        Aquamarine::WidgetEventListener::draw(context);
    }

    void onMenuItemSelected(Aquamarine::WidgetMenuItemArgs &args) override
    {

        Aquamarine::WidgetEventListener::onMenuItemSelected(args);

        Widget* owner = getOwnerWidget();
        if(!owner) return;


        switch (args.activeMenuTabId)
        {
        case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE:
        //     if (args.menuItem->uniqueID == -1000)
        //     {
        //         setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES);
        //     }
        //     else
        //     {
        //         setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::NONE);
        //         setTheoryVizLabelMode((TheoryVizLabelMode)args.menuItem->uniqueID);
        //     }
        //     setNeedsUpdate(true);
        //     break;

        // case MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE:
        //     if (args.menuItem->uniqueID == -1000)
        //     {
        //         setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES);
        //     }
        //     else
        //     {
        //         setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::NONE);
        //         setTheoryVizColorMode((TheoryVizColorMode)args.menuItem->uniqueID);
        //     }
        //     setNeedsUpdate(true);
        //     break;

        // case MENU_GROUP_1::MENU_TAB_THEORY_OCTAVE_MODE:
        //     setShowOctaveInLabel(!getShowOctaveInLabel());
        //     setNeedsUpdate(true);
        //     break;

    }
    }   


 

    // virtual void onWidgetLoaded() override {

    //     // Implement any behaviour for when a widget has loaded
    //     WidgetEventListener::onWidgetLoaded();

    //     WidgetMenu* settingsMenu = getSettingsMenu();
    //     if (settingsMenu != nullptr) {
    //         settingsMenu->addOrUpdateMenuTab(
    //             // ----------------------------------------------------------------------------
    //             // Label mode menu
    //             // ----------------------------------------------------------------------------
    //             WidgetMenuTab(Aquamarine::Shared::lang("LABEL"), IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
    //                 WidgetMenuItem(Aquamarine::Shared::lang("NONE"), 1), 
    //                 WidgetMenuItem(Aquamarine::Shared::lang("KEY"), 1, false, true), 
    //                 WidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), 1), 
    //                 WidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
    //             })
    //         );
    //     }        
    // }        
 



private:

    WidgetKeyPicker *keyPickerMenuItem = nullptr;

    enum MENU_GROUP_1
    {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_OCTAVE_MODE = 2,
        MENU_TAB_TUNINGS = 3,

        MENU_TAB_START_FRET = 4,
        MENU_TAB_END_FRET = 5,

        MENU_TAB_STRINGS = 6,
        MENU_TAB_CHORD_VIEW_MODE = 7,
        MENU_TAB_SETTINGS = 8,

        MENU_TAB_KEY_PICKER = 9,
        MENU_TAB_CHORD_WHEEL = 10,
        MENU_TAB_CHORD_DESIGNER = 11,
        MENU_TAB_SCALE_PICKER = 12

    };    

    bool loaded = false; 

    void initWidget() override {
        setAllowedWidgetClassTypes({
            "WidgetMusical",
            "WidgetMusicalComposer",
            "WidgetChordWheel",
            "WidgetChordProgression",
            "WidgetChordBucket",
            "WidgetChordBucketSuggester",
            "WidgetChordDesigner",
            "WidgetChordRules",
            "WidgetScalePicker",
            "WidgetScaleTable",
            "WidgetChordTable",
            "WidgetNotesTable",
            "WidgetKeyPicker",
            "WidgetKeyPickerPopout",
            "WidgetStringedInstrument",
            "WidgetGuitar",
            "WidgetBassGuitar"
        });  


            keyPickerMenuItem = new WidgetKeyPicker(
                getWidgetId() + "_MENU_KEY_PICKER",
                "<widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/></widget>");


    }

};


