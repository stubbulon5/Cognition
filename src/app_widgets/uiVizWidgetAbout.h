//
//  uiVizWidgetChordWheel.h
//  bloom-macos
//
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "uiVizWidgetLicence.h"
#include "uiVizWidgetMenuCollection.h"

class uiVizWidgetAbout : public Aquamarine::uiVizWidget {
    
public:
    
    uiVizWidgetAbout(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
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

    virtual void onChildWidgetsLoaded() override {
        uiVizWidget* w = getChildWidgetByPersistentId("ABOUT_TAB_TEXT_HOLDER");
        if (w) {
            Aquamarine::uiVizWidgetElmTextarea* TXT_ABOUT = w->getTextarea("TXT_ABOUT");
            if(TXT_ABOUT) {
                string replaceText = TXT_ABOUT->getValue();
                Licence licence = Licence::getLicence();
                ofStringReplace(replaceText, "${APP_VER}", APP_CONSTANTS::APPLICATION_VERSION);
                ofStringReplace(replaceText, "${REGISTERED_TO}", licence.isValid ? "Registered to " + licence.username : "No valid licence found");
                TXT_ABOUT->setValue(replaceText);                
            }
        }


        if (!loaded) {
            ABOUT_TABS = dynamic_cast<Aquamarine::uiVizWidgetMenuCollection*>(Aquamarine::uiVizWidgetManager::getWidgetByPersistentId(this, "ABOUT_TABS"));
            ABOUT_TAB_ATTRIBUTIONS = dynamic_cast<Aquamarine::uiVizWidgetTable*>(Aquamarine::uiVizWidgetManager::getWidgetByPersistentId(this, "ABOUT_TAB_ATTRIBUTIONS"));
        }  

    }       

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_ABOUT, 0);
        return mWidgetXML;
    }
    
    virtual ~uiVizWidgetAbout() {
       // ofRemoveListener(ABOUT_TABS->widgetEventReceived, this, &uiVizWidgetAbout::onAboutTabsEventReceived);                  
    }
    
    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        string parentWidgetId = args.sender.getParentPersistentId();
        string event = args.getFullEventName();

        if (args.sender.matchesWidgetOrParent(ABOUT_TAB_ATTRIBUTIONS)) {
            //cout << "zzz";
            //add content
        } else if (args.sender.matchesWidgetOrChildOf(this)) {
            if (event == "OK." + Aquamarine::WIDGET_EVENT::CLICK) {
                closeThisWidget();
            }            
        }

    }

    
private:
    Aquamarine::uiVizWidgetMenuCollection* ABOUT_TABS;
    Aquamarine::uiVizWidgetTable* ABOUT_TAB_ATTRIBUTIONS;
    bool loaded = false;

    void initWidget() override {
      
    }
    
};


