//
//  uiVizWidgetChordWheel.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "uiVizWidgetMusical.h"


class uiVizWidgetTutor : public uiVizWidgetMusical {
    
public:
    
    uiVizWidgetTutor(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_TUTOR, 0);
        return mWidgetXML;
    }
    
    
    
    virtual ~uiVizWidgetTutor() {
        
    }
    
    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        // To be overridden in derived classes
        //uiVizWidgetManager::load("layout-3.xml", true);
    }

    
private:
    
    void initWidget() override {
    }
    
};


