#pragma once
#include "../uiViz/widget/uiVizWidget.h"

class uiVizWidgetOmniMenuSearchResults : public uiVizWidget {
    
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
    
    void update(uiVizWidgetContext context) override {
    }
    
    void draw(uiVizWidgetContext context) override {
    }

    
private:

    void initWidget() override {  

        
    }
};


