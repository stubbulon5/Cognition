
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "../uiViz/widget/uiVizWidgetPianoRoll.h"
#include "uiVizWidgetMenuCollection.h"
#include "uiVizWidgetMusicalComposerSidebar.h"

class uiVizWidgetMusicalComposer : public uiVizWidgetMusical {
public:
    uiVizWidgetMusicalComposer(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = uiVizWidgetMusical::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~uiVizWidgetMusicalComposer() {

        if (sidebar) 
            ofRemoveListener(sidebar->widgetEventReceived, this, &uiVizWidgetMusicalComposer::onSidebarEventReceived);

        if (topMenu)
            ofRemoveListener(topMenu->menuItemSelected, this, &uiVizWidgetMusicalComposer::onTopMenuItemSelected);     

        if (pianoRollChorus)
            ofRemoveListener(pianoRollChorus->widgetEventReceived, this, &uiVizWidgetMusicalComposer::onPianoRollChorusEventReceived);            
    };

    virtual void onTopMenuItemSelected(uiVizWidgetMenuCollectionArgs & args) {

    }

    virtual void onPianoRollChorusEventReceived(uiVizWidgetEventArgs &args) {
        string event = args.getFullEventName();
    }

    virtual void onSidebarEventReceived(uiVizWidgetEventArgs &args) {
        string event = args.getFullEventName();
    }

    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
        string event = args.getFullEventName();
    }

    virtual void setTheme(uiVizWidgetTheme val) override {
        uiVizWidgetMusical::setTheme(val);

        // Theme overrides...

        if (breadcrumb) {
            breadcrumb->setIsRoundedRectangle(false);      
        }

        if(pianoRollChorus) {
            pianoRollChorus->setIsRoundedRectangle(false);
        }
    }


protected:

private:
    uiVizWidgetMenuCollection* topMenu = nullptr;;

    uiVizWidgetMusicalComposerSidebar* sidebar = nullptr;;

    uiVizWidgetPianoRoll *pianoRollChorus = nullptr;
    uiVizWidgetElmBreadcrumb *breadcrumb = nullptr;

    void initWidget() override {
        setMinWidth(400);
        setMinHeight(250);
  

        string sidebarId = getPersistentId() +  "_SIDEBAR";
        string breadcrumbId = getPersistentId() +  "_BREADCRUMB";
        string pianoRollChorusId = getPersistentId() +  "_PIANO_ROLL_CHOR";


        if (!sidebar) {
            sidebar = new uiVizWidgetMusicalComposerSidebar(sidebarId, R"(
                <widget></widget>
                )");

            sidebar->setX_Expr("${PARENT.ABSOLUTE_USABLE_X}-${PADDING}");
            sidebar->setY_Expr("${PARENT.ABSOLUTE_USABLE_Y}-${PADDING}+60+${PADDING}*2");
            sidebar->setHeight_Expr("${PARENT.USABLE_HEIGHT}-60-${PADDING}");            
            sidebar->setWidth_Expr("${PARENT.WIDTH}/3");
            sidebar->setMinWidth(250);
            addChildWidget(*sidebar, true);
            ofAddListener(sidebar->widgetEventReceived, this, &uiVizWidgetMusicalComposer::onSidebarEventReceived);            
        }


        if (!breadcrumb) {
            breadcrumb = dynamic_cast<uiVizWidgetElmBreadcrumb*>(addOrLoadWidgetElement(breadcrumb, WIDGET_ELM_CLASS::BREADCRUMB, breadcrumbId, R"(
                <element></element>
                )"));

            breadcrumb->setX_Expr("${"+sidebarId+".RIGHT}");
            breadcrumb->setY_Expr("${PARENT.TOP}-${PADDING}");
            breadcrumb->setHeight_Expr("30");
            breadcrumb->setWidth_Expr("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");



        }


        if (!pianoRollChorus) {
            pianoRollChorus = new uiVizWidgetPianoRoll(pianoRollChorusId, R"(
                <widget></widget>
                )");

            pianoRollChorus->setX_Expr("${"+sidebarId+".RIGHT}");
            pianoRollChorus->setY_Expr("${"+breadcrumbId+".BOTTOM}");
            pianoRollChorus->setHeight_Expr("${PARENT.USABLE_HEIGHT} + ${PADDING} - ${"+breadcrumbId+".HEIGHT}");            
            pianoRollChorus->setWidth_Expr("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");
            //addChildWidget(*pianoRollChorus, true);
            ofAddListener(pianoRollChorus->widgetEventReceived, this, &uiVizWidgetMusicalComposer::onPianoRollChorusEventReceived);            
        }





        if (!topMenu) {
            // getSidebarWidth() =

           topMenu = new uiVizWidgetMenuCollection("TOP_MENU", R"(
                <widget>
                    <bounds xExpr="${PARENT.ABSOLUTE_USABLE_X}" yExpr="${PARENT.ABSOLUTE_USABLE_Y}" widthExpr="${PARENT.WIDTH}-${PADDING}*2"  />
                    <properties menuType="TAB" />
                </widget>
                )");


            
            uiVizIcon i = uiVizIconCache::getIcon("REG_QUEUE_MUSIC");

            topMenu->setMenuCollection( {
                uiVizWidgetMenuCollectionItem("VERSE", nullptr, "Verse", i),
                uiVizWidgetMenuCollectionItem("PRE", nullptr, "Pre Chorus", i),
                uiVizWidgetMenuCollectionItem("CHORUS", pianoRollChorus, "Chorus", i),
                uiVizWidgetMenuCollectionItem("BRIDGE", nullptr, "Bridge", i),
                uiVizWidgetMenuCollectionItem("DROP", nullptr, "Drop", i)
            });  

            topMenu->setItemXExpression("${PARENT.ABSOLUTE_USABLE_X}+${"+sidebarId+".WIDTH}");
            topMenu->setItemWidthExpression("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");
            

            addChildWidget(*topMenu, true);    
            ofAddListener(topMenu->menuItemSelected, this, &uiVizWidgetMusicalComposer::onTopMenuItemSelected);                               
        }

        setStaticTopTitleBarSize(40);
        
        setTitle("Composer");
        
    }
    

};