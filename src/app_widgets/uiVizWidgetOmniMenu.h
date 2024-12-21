#pragma once
#include "ofxAquamarine.h"
#include "uiVizWidgetOmniMenuSearchResults.h"
#include "uiVizWidgetOmniMenuLinks.h"

class uiVizWidgetOmniMenu : public Aquamarine::uiVizWidget {
    
public:

    uiVizWidgetOmniMenu(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU, 0);
        return mWidgetXML;
    }

    virtual ~uiVizWidgetOmniMenu() {
    }
    
    void update(Aquamarine::uiVizWidgetContext context) override {
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
    }

    
private:
    Aquamarine::uiVizWidgetElmTextbox *omniSearchBox = nullptr;
    uiVizWidgetOmniMenuSearchResults *omniSearchResults = nullptr;
    uiVizWidgetOmniMenuLinks *omniLinks = nullptr;

    vector<string> searchHints = {"C Major", "Gb Minor", "D#m", "Ionian Scale", "Minor Scale"};


    void initWidget() override {  

         string omniSearchBoxId = getPersistentId() +  "_OMNI_SEARCH_BOX_TEXT";
         string omniSearchResultsId = getPersistentId() +  "_OMNI_SEARCH_RESULTS";
         string omniLinksId = getPersistentId() +  "_OMNI_LINKS";

        if (!omniSearchBox && 1==2) {
            omniSearchBox = dynamic_cast<Aquamarine::uiVizWidgetElmTextbox*>(addOrLoadWidgetElement(omniSearchBox, Aquamarine::WIDGET_ELM_CLASS::TEXTBOX, omniSearchBoxId, R"(
                <element>
                </element>
                )"));

            omniSearchBox->setX_Expr("${PARENT.LEFT}");
            omniSearchBox->setY_Expr("${PARENT.TOP}");
            omniSearchBox->setHeight_Expr("30"); // 50
            omniSearchBox->setWidth_Expr("${PARENT.USABLE_WIDTH}");
            omniSearchBox->setTitle("");
            omniSearchBox->setShouldPersist(false);

        }
/*
        if (!omniSearchResults) {
           omniSearchResults = new uiVizWidgetOmniMenuSearchResults(
                getWidgetId() + "_OMNI_SEARCH_RESULTS",
                "<widget><bounds minWidth='300' minHeight='400'/><appearance/></widget>"
            );
        }


        if (!omniLinks) {
           omniLinks = new uiVizWidgetOmniMenuLinks(
                getWidgetId() + "_OMNI_LINKS",
                "<widget><bounds minWidth='300' minHeight='400'/><appearance/></widget>"
            );
        }        
*/

        if (!omniLinks) {
            omniLinks = new uiVizWidgetOmniMenuLinks(omniLinksId, R"(
                <widget><bounds width="100"/></widget>
                )");
            omniLinks->setX_Expr("${PARENT.ABSOLUTE_USABLE_X}");
            omniLinks->setY_Expr("${PARENT.ABSOLUTE_USABLE_Y} - ${PADDING}");
            omniLinks->setHeight_Expr("${PARENT.USABLE_HEIGHT} + ${PADDING}");
            omniLinks->setWidth_Expr("${PARENT.USABLE_WIDTH}");
            addChildWidget(*omniLinks, true);
            omniLinks->setIsResizable(false);            
            //ofAddListener(omniLinks->widgetEventReceived, this, &uiVizWidgetFileExplorer::onFileLocationsEventReceived);

        }

        setShowTitleIcons(false);
        setTitle("");
        
    }
};


