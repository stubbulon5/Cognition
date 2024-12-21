#pragma once
#include "ofxAquamarine.h"

class uiVizWidgetOmniMenuSearchResults : public Aquamarine::uiVizWidget {
    
public:

    uiVizWidgetOmniMenuSearchResults(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_SEARCH_RESULTS, 0);
        return mWidgetXML;
    }

    virtual ~uiVizWidgetOmniMenuSearchResults() {
    }
    
    void update(Aquamarine::uiVizWidgetContext context) override {
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
    }

    
private:

    void initWidget() override {  

        
    }
};


