
#pragma once
#include "ofxAquamarine.h"
#include "WidgetMusicalComposerSidebar.h"

class WidgetMusicalComposer : public WidgetMusical {
public:
    WidgetMusicalComposer(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
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
        ofxXmlSettings settings = WidgetMusical::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~WidgetMusicalComposer() {

        if (sidebar) 
            ofRemoveListener(sidebar->widgetEventReceived, this, &WidgetMusicalComposer::onSidebarEventReceived);

        if (topMenu)
            ofRemoveListener(topMenu->menuItemSelected, this, &WidgetMusicalComposer::onTopMenuItemSelected);     

        if (pianoRollChorus)
            ofRemoveListener(pianoRollChorus->widgetEventReceived, this, &WidgetMusicalComposer::onPianoRollChorusEventReceived);            
    };

    virtual void onTopMenuItemSelected(Aquamarine::WidgetMenuCollectionArgs & args) {

    }

    virtual void onPianoRollChorusEventReceived(Aquamarine::WidgetEventArgs &args) {
        string event = args.getFullEventName();
    }

    virtual void onSidebarEventReceived(Aquamarine::WidgetEventArgs &args) {
        string event = args.getFullEventName();
    }

    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        string event = args.getFullEventName();
    }

    virtual void setTheme(Aquamarine::WidgetTheme val) override {
        WidgetMusical::setTheme(val);

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
    Aquamarine::WidgetMenuCollection* topMenu = nullptr;;

    WidgetMusicalComposerSidebar* sidebar = nullptr;;

    Aquamarine::WidgetPianoRoll *pianoRollChorus = nullptr;
    Aquamarine::WidgetElmBreadcrumb *breadcrumb = nullptr;

    void initWidget() override {
        setMinWidth(400);
        setMinHeight(250);
  

        string sidebarId = getPersistentId() +  "_SIDEBAR";
        string breadcrumbId = getPersistentId() +  "_BREADCRUMB";
        string pianoRollChorusId = getPersistentId() +  "_PIANO_ROLL_CHOR";


        if (!sidebar) {
            sidebar = new WidgetMusicalComposerSidebar(sidebarId, R"(
                <widget></widget>
                )");

            sidebar->setX_Expr("${PARENT.ABSOLUTE_USABLE_X}-${PADDING}");
            sidebar->setY_Expr("${PARENT.ABSOLUTE_USABLE_Y}-${PADDING}+60+${PADDING}*2");
            sidebar->setHeight_Expr("${PARENT.USABLE_HEIGHT}-60-${PADDING}");            
            sidebar->setWidth_Expr("${PARENT.WIDTH}/3");
            sidebar->setMinWidth(250);
            addChildWidget(*sidebar, true);
            ofAddListener(sidebar->widgetEventReceived, this, &WidgetMusicalComposer::onSidebarEventReceived);            
        }


        if (!breadcrumb) {
            breadcrumb = dynamic_cast<Aquamarine::WidgetElmBreadcrumb*>(addOrLoadWidgetElement(breadcrumb, Aquamarine::WIDGET_ELM_CLASS::BREADCRUMB, breadcrumbId, R"(
                <element></element>
                )"));

            breadcrumb->setX_Expr("${"+sidebarId+".RIGHT}");
            breadcrumb->setY_Expr("${PARENT.TOP}-${PADDING}");
            breadcrumb->setHeight_Expr("30");
            breadcrumb->setWidth_Expr("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");



        }


        if (!pianoRollChorus) {
            pianoRollChorus = new Aquamarine::WidgetPianoRoll(pianoRollChorusId, R"(
                <widget></widget>
                )");

            pianoRollChorus->setX_Expr("${"+sidebarId+".RIGHT}");
            pianoRollChorus->setY_Expr("${"+breadcrumbId+".BOTTOM}");
            pianoRollChorus->setHeight_Expr("${PARENT.USABLE_HEIGHT} + ${PADDING} - ${"+breadcrumbId+".HEIGHT}");            
            pianoRollChorus->setWidth_Expr("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");
            //addChildWidget(*pianoRollChorus, true);
            ofAddListener(pianoRollChorus->widgetEventReceived, this, &WidgetMusicalComposer::onPianoRollChorusEventReceived);            
        }





        if (!topMenu) {
            // getSidebarWidth() =

           topMenu = new Aquamarine::WidgetMenuCollection("TOP_MENU", R"(
                <widget>
                    <bounds xExpr="${PARENT.ABSOLUTE_USABLE_X}" yExpr="${PARENT.ABSOLUTE_USABLE_Y}" widthExpr="${PARENT.WIDTH}-${PADDING}*2"  />
                    <properties menuType="TAB" />
                </widget>
                )");


            
            Aquamarine::Icon i = Aquamarine::IconCache::getIcon("REG_QUEUE_MUSIC");

            topMenu->setMenuCollection( {
                Aquamarine::WidgetMenuCollectionItem("VERSE", nullptr, "Verse", i),
                Aquamarine::WidgetMenuCollectionItem("PRE", nullptr, "Pre Chorus", i),
                Aquamarine::WidgetMenuCollectionItem("CHORUS", pianoRollChorus, "Chorus", i),
                Aquamarine::WidgetMenuCollectionItem("BRIDGE", nullptr, "Bridge", i),
                Aquamarine::WidgetMenuCollectionItem("DROP", nullptr, "Drop", i)
            });  

            topMenu->setItemXExpression("${PARENT.ABSOLUTE_USABLE_X}+${"+sidebarId+".WIDTH}");
            topMenu->setItemWidthExpression("${PARENT.USABLE_WIDTH}-${"+sidebarId+".WIDTH}");
            

            addChildWidget(*topMenu, true);    
            ofAddListener(topMenu->menuItemSelected, this, &WidgetMusicalComposer::onTopMenuItemSelected);                               
        }

        setStaticTopTitleBarSize(40);
        
        setTitle("Composer");
        
    }
    

};