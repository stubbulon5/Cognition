//
//  WidgetChordWheel.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "WidgetMusical.h"


class WidgetTutor : public WidgetMusical {
    
public:
    
    WidgetTutor(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        WidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = WidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_TUTOR, 0);
        return mWidgetXML;
    }
    
    
    
    virtual ~WidgetTutor() {
        
    }
    
    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        // To be overridden in derived classes
        //WidgetManager::load("layout-3.xml", true);
    }

    
private:
    
    void initWidget() override {
    }
    
};


