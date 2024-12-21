//
//  uiVizWidgetUnitTests.h
//  bloom-macos
//
//  Created by Stuart Barnes on 09/04/2019.
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "uiVizWidgetGuitar.h"


class uiVizWidgetUnitTests : public Aquamarine::uiVizWidget {
    
public:
    
    uiVizWidgetUnitTests(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~uiVizWidgetUnitTests() {
        contextMenu->deleteThisWidget();
    }
    
    virtual bool loadState(string widgetXML) override {
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS, 0);
        return mWidgetXML;
    }
    
    bool needsUpdateBeforeDraw(bool shouldResetTimer) override {
        if (getTimerMillis() >= 100) { // refresh debug info every 1/2 second ...
            if (shouldResetTimer) resetTimer();
            return true;
        }
        return false;
    }
    
    void update(Aquamarine::uiVizWidgetContext context) override {
        debugInfo = debugTemplate;
        setTitle("UNIT TESTS INFO: [....]");

        //ofStringReplace(debugInfo, "${ACTIVE}", getViz()->getActiveWidgetId());
        //ofStringReplace(debugInfo, "${PRIOR}", getViz()->getPriorActiveWidgetId());
        
        debugInfo += "<small-mono>TEST                    STATUS     </small-mono><br/>";
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
        
        ofPushStyle();   
        ofSetColor(ofColor::black);
        
        ofRectangle r = getViz()->getFonts(getTheme())->drawFormattedColumn(
            debugInfo,
            getViz()->scale(getUsableX()),
            getViz()->scale(getUsableY()),
            getViz()->scale(getUsableWidth() - getViz()->getNonScaledPadding()*2.0f)
            );
        
        setContentBoundsScaled(Aquamarine::uiVizCoord::vizBounds(
            r.x,
            r.y,
            r.width,
            r.height)
        );

        ofPopStyle();   
    }
    
    /*
    menu items to test:
    drag data (chords)
    stringed instrument chords
    */
    
    void clearExistingWidgets() {
        for(uiVizWidget &widget:Aquamarine::uiVizWidgetManager::getWidgets()){
            if (widget.getWidgetId() != this->getWidgetId()) {
                Aquamarine::uiVizWidgetManager::removeWidget(widget);
            }
        }
    }
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return contextMenu;
            default:
                return nullptr;
        }
    }
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {
            showContextMenu(Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }
    
    void onMenuItemSelected(Aquamarine::uiVizWidgetMenuItemArgs & args) {
        switch(args.activeMenuTabId) {
            case Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS: {

                switch (args.menuItem->uniqueID) {
                    case 1: testAllChordTypesOnGuitar(); break;

                }
                break;
            }
        }
    }
    
    void testAllChordTypesOnGuitar() {
        clearExistingWidgets();
        uiVizWidgetGuitar* guitar1 = addGuitar1();
        Aquamarine::uiVizWidgetMenu* menu = guitar1->getPopoutMenu(Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
        
        
        int tabSliceIndex = menu->getIndexForTabMenu(guitar1->MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER);
        
        menu->selectMenuItem(guitar1->MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER, 0, true);
        menu->setIsVisible(true);
        
        uiVizWidgetChordDesigner* associatedChordDesigner =
        dynamic_cast<uiVizWidgetChordDesigner*>(menu->getMenuTabs()[tabSliceIndex].tabWidget);
        
        
        Aquamarine::uiVizWidgetMenu* chordDesignerMenu = associatedChordDesigner->getPopoutMenu(Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS);
        chordDesignerMenu->setIsVisible(true);
        
        for (int i=0; i<=10; i++) {
            chordDesignerMenu->selectMenuItem(associatedChordDesigner->MENU_GROUP_1::MENU_TAB_CHORD, i, true);
            ofSleepMillis(1000);
        }
        unlock();

    }
    
    void threadedFunction() override {
       
        while(isThreadRunning()) {
 
        }
        
    }
    
    uiVizWidgetGuitar* addGuitar1() {
        uiVizWidgetGuitar* w = dynamic_cast<uiVizWidgetGuitar*>(Aquamarine::uiVizWidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_GUITAR, "GUITAR1", R"(
            <widget>
            <bounds x="0" height="192" maxWidth="2304" maxHeight="1440" minWidth="75" minHeight="75" yExpr="${WINDOW.HEIGHT} - ${GUITAR1.HEIGHT}" widthExpr="${WINDOW.WIDTH}" />
            </widget>
        )"));
                                                                
        Aquamarine::uiVizWidgetManager::addWidget(*w, false, getWidgetId());
                                                                
        return w;
    }
    
private:
    uiVizWidget *contextMenu = nullptr;
    ofxFontStash2::Style defaultStyle;
    string debugTemplate =
    "<br/>"
    "<medium>------[UNIT TESTS]------</medium><br/>";
    
    std::vector<std::reference_wrapper<uiVizWidget>>* mWidgetMapRef;
    
    string debugInfo = "";
    
    void initWidget() override {
        setWidth(250);
        setHeight(200);
        defaultStyle = getViz()->getSmallFontStyleMono();
        setScrollAction(ScrollAction::SCROLL);
        setEnableScrollYPositive(true);
        setEnableScrollYNegative(true);
        setEnableScrollXPositive(false);
        setEnableScrollXNegative(false);
    
        
       if (!contextMenu) {
        contextMenu = new Aquamarine::uiVizWidgetMenu(getWidgetId() + "_UNIT_TEST_MENU", "<widget><bounds width='100' height='300'/></widget>", getWidgetId()
            , Aquamarine::uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                
                // ----------------------------------------------------------------------------
                // Unit Tests menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab("Unit Tests", Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                    Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS, {
                    Aquamarine::uiVizWidgetMenuItem("Guitar: All chords", 1),
                    Aquamarine::uiVizWidgetMenuItem("Test 2", 2)
                })
                
            });
        
            ofAddListener(dynamic_cast<Aquamarine::uiVizWidgetMenu*>(contextMenu)->menuItemSelected, this, &uiVizWidgetUnitTests::onMenuItemSelected);
            
            addChildWidget(*contextMenu);
       }

        
        //uiVizWidgetManager::addWidget(*contextMenu, false);
        setIsAutoUpdateWhenActive(true);
        
    }
};


