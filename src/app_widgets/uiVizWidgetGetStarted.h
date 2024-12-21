
//
//  uiVizWidgetChordWheel.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "uiVizWidgetLicence.h"

class uiVizWidgetGetStarted : public Aquamarine::uiVizWidget {
    
public:
    
    uiVizWidgetGetStarted(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual void onChildWidgetsLoaded() override {
        if (!loaded) {
            GETTING_STARTED_TABS = dynamic_cast<Aquamarine::uiVizWidgetMenuCollection*>(Aquamarine::WidgetManager::getWidgetByPersistentId(this, "GETTING_STARTED_TABS"));
            GENERAL_TAB_TABLE = dynamic_cast<Aquamarine::uiVizWidgetTable*>(Aquamarine::WidgetManager::getWidgetByPersistentId(this, "GENERAL_TAB_TABLE"));            
            GUITAR_TAB_TABLE = dynamic_cast<Aquamarine::uiVizWidgetTable*>(Aquamarine::WidgetManager::getWidgetByPersistentId(this, "GUITAR_TAB_TABLE"));
            BASS_TAB_TABLE = dynamic_cast<Aquamarine::uiVizWidgetTable*>(Aquamarine::WidgetManager::getWidgetByPersistentId(this, "BASS_TAB_TABLE"));


            settingsWidget = dynamic_cast<uiVizWidget*>(Aquamarine::WidgetManager::loadWidgetFromFile(APP_CONSTANTS::WIDGET_CLASS, "getStartedSettings", "ui/widgets/getStartedSettings.xml"));
            Aquamarine::WidgetManager::addWidgetForPopout(*settingsWidget, getWidgetId(), false);
            settingsWidget->setShouldCloseIfOtherWidgetClicked(true);

            SETTINGS = getButton("SETTINGS");
            SETTINGS->setPopoutWidget(settingsWidget, PopoutDirection::UP);


            settingsWidget->getButton("OK")->handlePressed([this]() {

                Aquamarine::uiVizWidgetMenuCollection* GETTING_STARTED_TABS = dynamic_cast<Aquamarine::uiVizWidgetMenuCollection*>(settingsWidget->getChildWidgetByPersistentId("GETTING_STARTED_TABS"));
                uiVizWidgetKeyPicker* settingsWidgetKey = dynamic_cast<uiVizWidgetKeyPicker*>(GETTING_STARTED_TABS->getWidgetForTag("key"));
                uiVizWidgetChordTable* settingsWidgetChordTable = dynamic_cast<uiVizWidgetChordTable*>(GETTING_STARTED_TABS->getWidgetForTag("chord"));
                uiVizWidgetScaleTable* settingsWidgetScaleTable = dynamic_cast<uiVizWidgetScaleTable*>(GETTING_STARTED_TABS->getWidgetForTag("scale"));
                uiVizWidgetChordRules* settingsFretboardRules = dynamic_cast<uiVizWidgetChordRules*>(GETTING_STARTED_TABS->getWidgetForTag("fretboardRules"));

                vizNote key = settingsWidgetKey->getSelectedKey();
                vizChord chord = settingsWidgetChordTable->getSelectedChord();
                vizScale scale = settingsWidgetScaleTable->getSelectedScale();


// get settings going into loaded widgets 
// (use a metadata block in the document ??)

                

            });



            ofAddListener(GETTING_STARTED_TABS->menuItemSelected, this, &uiVizWidgetGetStarted::onGettingStartedTabsMenuItemSelected);    
            loaded = true;        
        }  

    }       


    virtual ~uiVizWidgetGetStarted() {
       // ofRemoveListener(GETTING_STARTED_TABS->widgetEventReceived, this, &uiVizWidgetGetStarted::onAboutTabsEventReceived);          
       ofRemoveListener(GETTING_STARTED_TABS->menuItemSelected, this, &uiVizWidgetGetStarted::onGettingStartedTabsMenuItemSelected);                    
    }
    
    bool anyRowSelected() {
        return   
            loaded && (          
            (GENERAL_TAB_TABLE != nullptr && GENERAL_TAB_TABLE->getSelectedRows().size()) > 0 ||
            (GUITAR_TAB_TABLE != nullptr && GUITAR_TAB_TABLE->getSelectedRows().size()) > 0 ||
            (BASS_TAB_TABLE != nullptr && BASS_TAB_TABLE->getSelectedRows().size()) > 0
            );
    }

    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        string parentWidgetId = args.sender.getParentPersistentId();
        string event = args.getFullEventName();

        string selectedTag = GETTING_STARTED_TABS != nullptr ? GETTING_STARTED_TABS->getSelectedTag() : "";
        bool stringedInstrument = selectedTag == "guitar" || selectedTag == "bass";

        if (args.sender.matchesWidgetOrParent(GETTING_STARTED_TABS)) {

            GENERAL_TAB_TABLE->clearSelectedRows();
            GUITAR_TAB_TABLE->clearSelectedRows();
            BASS_TAB_TABLE->clearSelectedRows();

        
        } else if (args.sender.matchesWidgetOrParent(GUITAR_TAB_TABLE)) {
            //cout << "zzz";
            //add content
        } else if (args.sender.matchesWidgetOrChildOf(this)) {
            if (event == "CANCEL." + Aquamarine::WIDGET_EVENT::CLICK) {
                closeThisWidget();
            } else  if (event == "OK." + Aquamarine::WIDGET_EVENT::CLICK) {


                if (selectedTag == "general") {
                    if (GENERAL_TAB_TABLE->getSelectedRows().size() == 0) return;
                    string fileName = GENERAL_TAB_TABLE->getSelectedRows()[0].key;
                    mGetStartedCallback("<new type='file' value='"+fileName+"'/>");


                } else if (selectedTag == "guitar") {
                    string fileName = GUITAR_TAB_TABLE->getSelectedRows()[0].key;
                    mGetStartedCallback("<new type='file' value='"+fileName+"'/>");


                } else if (selectedTag == "bass") {
                    string fileName = GUITAR_TAB_TABLE->getSelectedRows()[0].key;

                    
                    mGetStartedCallback("<new type='file' value='"+fileName+"'/>");
                }


                closeThisWidget();
            }            
        }

        Aquamarine::uiVizWidgetElmButton* OK = getButton("OK");
        if (OK) OK->setIsVisible(anyRowSelected());

        Aquamarine::uiVizWidgetElmButton* SETTINGS = getButton("SETTINGS");
        if (SETTINGS) SETTINGS->setIsVisible(anyRowSelected() && stringedInstrument);


    }

    virtual void onGettingStartedTabsMenuItemSelected(Aquamarine::uiVizWidgetMenuCollectionArgs &args) {
        cout << args.activeMenuTabId;

    }  

    void setGetStartedCallback(const std::function<void(const string &)> &callback) { 
        mGetStartedCallback = callback; 
        //mGetStartedCallback("<XML>some context</XML>");
    }

    
private:
    Aquamarine::uiVizWidgetMenuCollection* GETTING_STARTED_TABS = nullptr;
    Aquamarine::uiVizWidgetTable* GENERAL_TAB_TABLE = nullptr;
    Aquamarine::uiVizWidgetTable* GUITAR_TAB_TABLE = nullptr;
    Aquamarine::uiVizWidgetTable* BASS_TAB_TABLE = nullptr;
    Aquamarine::uiVizWidgetElmButton* SETTINGS = nullptr;
    Aquamarine::uiVizWidget* settingsWidget = nullptr;
    bool loaded = false;
    std::function<void(const string &)> mGetStartedCallback;   

    void initWidget() override {
      
    }
    
};


