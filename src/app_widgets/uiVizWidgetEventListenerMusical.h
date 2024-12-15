
#pragma once
#include "../uiViz/widget/uiVizWidgetEventListener.h"
#include "uiVizWidgetMusicalHelper.h"
#include "uiVizWidgetKeyPicker.h"

class uiVizWidgetEventListenerMusical : public uiVizWidgetEventListener {
    
public:
    
    uiVizWidgetEventListenerMusical(string persistentId, string widgetXML) : uiVizWidgetEventListener(persistentId, widgetXML) {

    }
    
    virtual ~uiVizWidgetEventListenerMusical() {
    }

    virtual void update(uiVizWidgetContext context) override {    
        uiVizWidgetEventListener::update(context);
    }

	virtual void onWidgetWasJustInitialized() override {
    
    }
    
    void draw(uiVizWidgetContext context) override {


        if(context.isInitialDraw) {
        uiVizWidgetEventListener::onWidgetWasJustInitialized();

        uiVizWidgetMenu* settingsMenu = getSettingsMenu();
        if (settingsMenu != nullptr) {
            settingsMenu->addOrUpdateMenuTab(
                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, 
                keyPickerMenuItem
                // {
                //     uiVizWidgetMenuItem(uiVizShared::lang("NONE"), 1), 
                //     uiVizWidgetMenuItem(uiVizShared::lang("KEY"), 1, false, true), 
                //     uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), 1), 
                //     uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                // }
                )
            );
        }                
        }

        uiVizWidgetEventListener::draw(context);
    }

    void onMenuItemSelected(uiVizWidgetMenuItemArgs &args) override
    {

        uiVizWidgetEventListener::onMenuItemSelected(args);

        uiVizWidget* owner = getOwnerWidget();
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
    //     uiVizWidgetEventListener::onWidgetLoaded();

    //     uiVizWidgetMenu* settingsMenu = getSettingsMenu();
    //     if (settingsMenu != nullptr) {
    //         settingsMenu->addOrUpdateMenuTab(
    //             // ----------------------------------------------------------------------------
    //             // Label mode menu
    //             // ----------------------------------------------------------------------------
    //             uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
    //                 uiVizWidgetMenuItem(uiVizShared::lang("NONE"), 1), 
    //                 uiVizWidgetMenuItem(uiVizShared::lang("KEY"), 1, false, true), 
    //                 uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), 1), 
    //                 uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
    //             })
    //         );
    //     }        
    // }        
 



private:

    uiVizWidgetKeyPicker *keyPickerMenuItem = nullptr;

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
            "uiVizWidgetMusical",
            "uiVizWidgetMusicalComposer",
            "uiVizWidgetChordWheel",
            "uiVizWidgetChordProgression",
            "uiVizWidgetChordBucket",
            "uiVizWidgetChordBucketSuggester",
            "uiVizWidgetChordDesigner",
            "uiVizWidgetChordRules",
            "uiVizWidgetScalePicker",
            "uiVizWidgetScaleTable",
            "uiVizWidgetChordTable",
            "uiVizWidgetNotesTable",
            "uiVizWidgetKeyPicker",
            "uiVizWidgetKeyPickerPopout",
            "uiVizWigetStringedInstrument",
            "uiVizWidgetGuitar",
            "uiVizWidgetBassGuitar"
        });  


            keyPickerMenuItem = new uiVizWidgetKeyPicker(
                getWidgetId() + "_MENU_KEY_PICKER",
                "<widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/></widget>");


    }

};


