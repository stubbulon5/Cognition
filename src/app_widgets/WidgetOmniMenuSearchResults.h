#pragma once
#include "ofxAquamarine.h"

class WidgetOmniMenuSearchResults : public Aquamarine::Widget {
    
public:

    WidgetOmniMenuSearchResults(string persistentId, string widgetXML) : Widget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS, 0);
        return mWidgetXML;
    }

    virtual ~WidgetOmniMenuSearchResults() {
    }
    
    void update(Aquamarine::WidgetContext context) override {
    }
    
    void draw(Aquamarine::WidgetContext context) override {
    }

    
private:

    void initWidget() override {  

        
    }
};


