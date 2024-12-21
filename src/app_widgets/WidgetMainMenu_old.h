//
//  uiVizMainMenu.h
//  bloom-macos
//
//  Created by Stuart Barnes on 12/04/2019.
//
#pragma once
#include "../uiViz/widget/Widget.h"

#include "WidgetChordWheel.h"
#include "WidgetChordBucket.h"
#include "WidgetChordBucketSuggester.h"
#include "WidgetChordDesigner.h"
#include "WidgetScalePicker.h"
#include "WidgetKeyPicker.h"
#include "WidgetStringedInstrument.h"
#include "WidgetGuitar.h"
#include "WidgetBassGuitar.h"
#include "WidgetTutor.h"
#include "WidgetUnitTests.h"
#include "WidgetLicence.h"
#include "WidgetScaleTable.h"
#include "WidgetOmniMenu.h"

#include "ofxAquamarine.h"
#include "../core/gp_parser/gp_parser.h"


class WidgetMainMenu_old : public Widget {
    
public:
    
    WidgetMainMenu_old(string persistentId, string widgetXML) : Widget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~WidgetMainMenu_old() {
        ofRemoveListener(contextMenu->widgetUnhovered, this,  &WidgetMainMenu_old::onMenuUnhovered);
        ofRemoveListener(contextMenu->widgetHovered, this,  &WidgetMainMenu_old::onMenuHovered);
    }
    
    virtual bool loadState(string widgetXML) override {
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU, 0);
        return mWidgetXML;
    }
    
    void update(Aquamarine::WidgetContext context) override {
        mainMenuIcon.setScaledPos(scale(getX()), scale(getY()));
        
        if (parent()) {
            contextMenu->setHeight_Expr("${" + parent()->getPersistentId() + ".USABLE_HEIGHT} - ${PADDING}*2");
        }
    }
    
    void draw(Aquamarine::WidgetContext context) override {
       
        mainMenuIcon.drawSvg();

        if (!contextMenu->getIsVisible()) {
            mUICurrentMenuLeft = 1;
        }
        
        if (getIsActiveWidget() && mainMenuIcon.isHovered() && getIsMousePressedAndReleasedOverWidget(false)) {
            mMenuHasBeenHovered = false;
            contextMenu->setIsVisible(!contextMenu->getIsVisible());
            if (contextMenu->getIsVisible()) {
                contextMenu->setActiveWidget();
            } else {
                setActiveWidget();
            }
        }
        
        bool menuHovered = (mainMenuIcon.isHovered() || contextMenu->isWidgetHovered());

        if (contextMenu->getIsVisible()) {
            
            int visibilityColor =  (mUICurrentMenuLeft / (float)contextMenu->getWidth()) * 255;
            contextMenu->getTheme().setWidgetAlphas(visibilityColor, visibilityColor, visibilityColor);
            
            
            /*
            if (parent()) {
                contextMenu->setX(getX());
                contextMenu->setIsVisible(true);
            } else {
               */
                if (getX() + mUICurrentMenuLeft < getX() + contextMenu->getWidth() && menuHovered) {
                    mUICurrentMenuLeft = scaleAnimationForUI(getWidgetId() + "_main_menu_left_in", mUICurrentMenuLeft, contextMenu->getWidth(), 0.3f);
                    contextMenu->setX(getX() + mUICurrentMenuLeft - contextMenu->getWidth());
                    contextMenu->setWidgetNeedsUpdate(true);
                    setNeedsUpdate(true);
                } else {
                    if (!menuHovered) {
                        mUICurrentMenuLeft = scaleAnimationForUI(getWidgetId() + "_main_menu_left_out", mUICurrentMenuLeft, 1, 0.2f);
                        contextMenu->setX(getX() + mUICurrentMenuLeft - contextMenu->getWidth());
                        contextMenu->setWidgetNeedsUpdate(true);
                        setNeedsUpdate(true);
                        
                        if (mUICurrentMenuLeft <= getX()+1) {
                            contextMenu->setIsVisible(false);
                        }
                    }
                }
          // }
            
 
        }
    }
    
    void clearExistingWidgets() {
        WidgetManager::removeAllWidgetsExcept(this);
    }
    
    Widget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case IconCache::IconTag::WIDGET_SETTINGS:
                return contextMenu;
            default:
                return nullptr;
        }
    }
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {
            showContextMenu(IconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }

    void onMenuItemSelected(Aquamarine::WidgetMenuItemArgs & args) {
        bool clearSelection = true;

        switch(args.activeMenuTabId) {
                
            case IconCache::IconTag::ADD_CIRCLE:
                switch(args.menuItem->uniqueID) {
                    case 0:
                        addKeyPicker(false); break; // Circle of Fifths
                    case 1:
                        addChordDesigner(false); break; // Chord Factory
                    case 2:
                        addChordWheel(false); break; // Diatonic Chord Wheel
                    case 3:
                        addChordBucket(false); break; // Chord Bucket
                    case 4:
                        addGuitar(false, 6); break;
                    case 5:
                        addGuitar(true, 6); break;
                    case 6:
                        addBassGuitar(false, 4); break;
                    case 7:
                        addBassGuitar(true, 4); break;
                    case 8:
                        addScalePicker(false); break;
                    case 9:
                        addMatrix(false); break;
                    case 10:
                        addPianoRoll(false); break;
                    case 11:
                        addScaleTable(false); break;        
                    case 12:
                        addSequencer(false); break;    
                    case 13:
                        addVideoPlayer(false); break;        
                    case 14:
                        addSoundPlayer(false); break;       
                    case 15:
                        addImageView(false); break;     
                    case 16:
                        addVideoGrabber(false); break;    
                    case 17:
                        addFileExplorer(false); break;     
                    case 18:
                        addFileLoad(false); break; 
                    case 19:
                        addFileSave(false); break;
                    case 20:
                        addTextEditor(false); break;   
                    case 21:
                        addThemeEditor(false); break;                                                  
                }
                break;

            case IconCache::IconTag::BOOK_CONTENT:
                clearSelection = false;
                switch(args.menuItem->uniqueID) {
                    case 4:
                        addDeveloperTools(); break;
                    case 5:
                        WidgetManager::drawDebugInfo(args.menuItem->isSelected); break;
                }
                break;
                
            case IconCache::IconTag::WIDGET_SETTINGS:
                switch(args.menuItem->uniqueID) {
                    case 0: // New
                        newProject(); break;
                    case 1: // save
                        saveProject(false); break;
                    case 2: // save as
                        saveProject(true); break;
                    case 3: // load
                        loadProject(); break;
                    case 4: // settings
                        settings(); break;
                    case 5: // licence
                        licence(); break;
                    case 6: // about
                        about(); break;
                    case -1000: {
                        clearExistingWidgets();
                        OF_EXIT_APP(0); 
                        break;
                    }
                        
                }
                break;
       }
        
        
        if (clearSelection) contextMenu->clearSelectedMenuItems(args.activeMenuTabId);
    }

    void onMenuUnhovered(WidgetEventArgs &args) {
        if (!mMenuHasBeenHovered) return;
        setActiveWidget();
        popoutMenuShouldHide();
    }
    
    void popoutMenuShouldHide() {
        mMenuHasBeenHovered = true;
        mUICurrentMenuLeft--;
        setNeedsUpdate(true);
    }
    
    void onMenuHovered(WidgetEventArgs &args) {
        mMenuHasBeenHovered = true;
    }
    
    
    void centerWidget(Widget* w) {
        w->setX_Expr("${WINDOW.WIDTH}/2 - ${SELF.USABLE_WIDTH}/2");
        w->setY_Expr("${WINDOW.HEIGHT}/2 - ${SELF.USABLE_HEIGHT}/2");
        WidgetManager::recalculateWidgetExpressions(*w);
        w->clearWidgetLayoutExpressions();
    }
    
    WidgetKeyPicker* addKeyPicker(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "KEY_PICKER" + ofToString(exitingCount + 1);
        
        WidgetKeyPicker* w = dynamic_cast<WidgetKeyPicker*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="250" height="250" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }
                                                                      
    WidgetChordDesigner* addChordDesigner(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_DESIGNER" + ofToString(exitingCount + 1);

        WidgetChordDesigner* w = dynamic_cast<WidgetChordDesigner*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }

    WidgetScalePicker* addScalePicker(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SCALE_PICKER" + ofToString(exitingCount + 1);

        WidgetScalePicker* w = dynamic_cast<WidgetScalePicker*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        //WidgetManager::showModal(w, true);     
        return w;
    }

    WidgetVideoPlayer* addVideoPlayer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_VIDEO_PLAYER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "VIDEO_PLAYER" + ofToString(exitingCount + 1);

        WidgetVideoPlayer* w = dynamic_cast<WidgetVideoPlayer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties file="/home/zabba/Downloads/caring-is-creepy.mp4" doesRespondToFileDrop="1" />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        w->play();
        return w;
    }  

    WidgetVideoGrabber* addVideoGrabber(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_VIDEO_GRABBER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "VIDEO_GRABBER" + ofToString(exitingCount + 1);

        WidgetVideoGrabber* w = dynamic_cast<WidgetVideoGrabber*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties file="/home/zabba/Downloads/caring-is-creepy.mp4" doesRespondToFileDrop="1" />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        w->play();
        return w;
    }        

    WidgetSoundPlayer* addSoundPlayer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_SOUND_PLAYER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SOUND_PLAYER" + ofToString(exitingCount + 1);

        WidgetSoundPlayer* w = dynamic_cast<WidgetSoundPlayer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties file="/home/zabba/Downloads/sample.mp3" doesRespondToFileDrop="1" />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        w->play();
        return w;
    }   

    WidgetImageView* addImageView(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_IMAGE_VIEW;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "IMAGE_VIEW" + ofToString(exitingCount + 1);

        WidgetImageView* w = dynamic_cast<WidgetImageView*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties file="/home/zabba/Desktop/shins1.jpg" doesRespondToFileDrop="1" />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }       


    WidgetFileExplorer* addFileExplorer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_EXPLORER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_EXPLORER" + ofToString(exitingCount + 1);

        WidgetFileExplorer* w = dynamic_cast<WidgetFileExplorer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties path="/home/zabba/projects/Batch-BQ-to-S3-Exporter"/>
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }  

    WidgetFileLoad* addFileLoad(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_LOAD;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_LOAD" + ofToString(exitingCount + 1);

        WidgetFileLoad* w = dynamic_cast<WidgetFileLoad*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties path="/home/zabba/projects/Batch-BQ-to-S3-Exporter"/>
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        w->setPathSelectedCallback([&](string filePath) {
            WidgetManager::load(filePath, false, w);
        });
        return w;
    }  


    WidgetFileSave* addFileSave(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_SAVE;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_SAVE" + ofToString(exitingCount + 1);

        WidgetFileSave* w = dynamic_cast<WidgetFileSave*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties path="/home/zabba/projects/Batch-BQ-to-S3-Exporter"/>
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }   

    WidgetTextEditor* addTextEditor(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_TEXT_EDITOR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_SAVE" + ofToString(exitingCount + 1);

        WidgetTextEditor* w = dynamic_cast<WidgetTextEditor*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }         

    WidgetThemeEditor* addThemeEditor(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_THEME_EDITOR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "THEME_EDITOR" + ofToString(exitingCount + 1);

        WidgetThemeEditor* w = dynamic_cast<WidgetThemeEditor*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }                  
    
    WidgetChordWheel* addChordWheel(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_WHEEL" + ofToString(exitingCount + 1);

        WidgetChordWheel* w = dynamic_cast<WidgetChordWheel*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="600" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }

    WidgetChordBucket* addChordBucket(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_BUCKET" + ofToString(exitingCount + 1);

        WidgetChordBucket* w = dynamic_cast<WidgetChordBucket*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="320" height="500" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }
                                                                              
    WidgetGuitar* addGuitar(bool docked, int strings) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_GUITAR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "GUITAR" + ofToString(exitingCount + 1);
        
        WidgetGuitar* w = dynamic_cast<WidgetGuitar*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
               <bounds height="200" minWidth="75" minHeight="75"  />
            </widget>
            )"));
               
        strings = std::min(strings, 6);
        strings = std::max(strings, 8);
                                                                
        WidgetManager::addWidget(*w, true);
        if (!docked) centerWidget(w);
                                                                
        if (docked) {
            w->setY_Expr("${WINDOW.HEIGHT} - ${" + widgetPersistentId + ".HEIGHT}");
            w->setWidth_Expr("${WINDOW.WIDTH}");
            w->setIsTitleAutohide(true);
        }
        return w;

    }


    WidgetBassGuitar* addBassGuitar(bool docked, int strings) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "BASS_GUITAR" + ofToString(exitingCount + 1);

        WidgetBassGuitar* w = dynamic_cast<WidgetBassGuitar*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
               <bounds height="200" minWidth="75" minHeight="75"  />
            </widget>
            )"));

        strings = std::min(strings, 4);
        strings = std::max(strings, 4);

        WidgetManager::addWidget(*w, true);
        if (!docked) centerWidget(w);

        if (docked) {
            w->setY_Expr("${WINDOW.HEIGHT} - ${" + widgetPersistentId + ".HEIGHT}");
            w->setWidth_Expr("${WINDOW.WIDTH}");
            w->setIsTitleAutohide(true);
        }
        return w;
    }

    WidgetMatrix* addMatrix(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_MATRIX;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "MATRIX" + ofToString(exitingCount + 1);

        WidgetMatrix* w = dynamic_cast<WidgetMatrix*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_MATRIX, widgetPersistentId, R"(
        <widget>
            <bounds height="200" width="300" minWidth="75" minHeight="75"  />
            <properties autoResizeHeight="1" autoResizeWidth="1">
                <header>
                        <cell width="200"></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                </header>
                <rows>
                    <row>
                        <cell key="kick">Kick</cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                    </row>
                    <row>
                        <cell key="clap">Clap</cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                    </row>
                    <row>
                        <cell key="hat">Hat</cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                    </row>
                    <row>
                        <cell key="snare">Snare</cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                        <cell></cell><cell></cell><cell></cell><cell></cell>
                    </row>                                    
                
                </rows>
            </properties>
        </widget>
            )"));            
        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }    

    WidgetSequencer* addSequencer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_SEQUENCER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SEQUENCER" + ofToString(exitingCount + 1);

        WidgetSequencer* w = dynamic_cast<WidgetSequencer*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_SEQUENCER, widgetPersistentId, R"(
        <widget>
            <bounds height="200" width="800" minWidth="75" minHeight="75"  />
            <properties>
            </properties>
        </widget>
            )"));            
        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }       

    WidgetPianoRoll* addPianoRoll(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_PIANO_ROLL;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "PIANO_ROLL" + ofToString(exitingCount + 1);

        WidgetPianoRoll* w = dynamic_cast<WidgetPianoRoll*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_PIANO_ROLL, widgetPersistentId, R"(
        <widget>
            <bounds height="200" minWidth="75" minHeight="75"  />
            <properties>
            </properties>
        </widget>
            )"));            
        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }   

    WidgetScaleTable* addScaleTable(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SCALE_TABLE" + ofToString(exitingCount + 1);

        WidgetScaleTable* w = dynamic_cast<WidgetScaleTable*>(WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE, widgetPersistentId, R"(
        <widget>
            <bounds height="200" minWidth="75" minHeight="75"  />
            <properties>
            </properties>
        </widget>
            )"));            
        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }       


    void addWIPWidget() {
        //return;
/*
        for(int i=1; i<=2; i++) {
            // Infinite loop
            WidgetManager::load(ofToDataPath("big.jam", true), true);

        }*/
       // WidgetManager::removeAllWidgets();

/*
        addScalePicker(false);
        addGuitar(true, 6);
        addBassGuitar(false, 4);
        */
        //addFileExplorer(false);

      //  addFileLoad(false);
      //  addChordWheel(true);

       // addThemeEditor(false);
        
        //addFileSave(false);

    }

    void onTableCellInitialized(WidgetTableArgs & args) {
        if (args.cell.key == "WIDGET" && args.cell.cellWidget != nullptr) {
            WidgetKeyPicker* scalePicker = dynamic_cast<WidgetKeyPicker*>(args.cell.cellWidget);
            //scalePicker->setSelectedScale(args.row.key);
            scalePicker->setSelectedKey(vizNote("D", 3, 3));
            scalePicker->setNeedsUpdate(true);
        }
    }

    void addDeveloperTools() {

        WidgetUnitTests* w = dynamic_cast<WidgetUnitTests*>(WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS, "UNIT_TESTS", R"(
            <widget>
               <bounds height="200" height="200" minWidth="75" minHeight="75"  />
            </widget>
            )"));
                                                                      
        WidgetManager::addWidget(*w, false);
        centerWidget(w);

    }
          
    void newProject() {
        clearExistingWidgets();
        WidgetManager::initWidgetManager(
            APP_CONSTANTS::APPLICATION_NAME,
            APP_CONSTANTS::APPLICATION_VERSION,
            APP_CONSTANTS::APPLICATION_FILE_EXTENSION
            true,
        );
    }
                                                                      
    void saveProject(bool saveAs) {
        WidgetManager::ProjectProperties existingProject = WidgetManager::getCurrentProjectProperties();
        string proposedFileName = "";
        string currFileName = WidgetManager::getCurrentProjectProperties().fileName;
        
        if (saveAs || currFileName == "untitled.jam") {

            string classType = WidgetManager::WIDGET_CLASS_FILE_SAVE;
            int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
            string widgetPersistentId = "PROJECT_SAVE" + ofToString(exitingCount + 1);

            WidgetFileSave* w = dynamic_cast<WidgetFileSave*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                        <widget>
                                        <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                        </widget>
                                        )"));

            w->setSavePathSelectedCallback([&, w](string filePath) {
  
                Shared::removeFileExtension(filePath);
                filePath += ".jam";

                if (WidgetManager::save(filePath)) {
                    // Success...
                }
            });

            string recentDir = WidgetFileLocationsList::getMostRecentDirectory();
            w->setSize(deScale(ofGetWindowWidth()*0.7f), deScale(ofGetWindowHeight()*0.7f));            
            w->setPath(recentDir);
            WidgetManager::showModal(w, true);     

            //ofFileDialogResult r = ofSystemSaveDialog(existingProject.fileName, "Save Project (.jam file)");
            //RegularExpression rex(".*.[jam|JAM]");
            
        } else {
            proposedFileName = WidgetManager::getCurrentProjectProperties().absolutePath;
        }
        
        if (proposedFileName != "") {
            if (WidgetManager::save(proposedFileName)) {
                    // Success...
            }
        }
    }

    void licence() {
        string classType = APP_CONSTANTS::WIDGET_CLASS_LICENCE;
        string widgetPersistentId = "LICENCE";

        WidgetLicence* w = dynamic_cast<WidgetLicence*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="250" height="450" minWidth="75" minHeight="75"  />
            </widget>
        )"));

        WidgetManager::addWidget(*w, true);

        WidgetElmTextbox* TXT_LICENCE = w->getTextbox("TXT_LICENCE");
        if (TXT_LICENCE) TXT_LICENCE->setValue("1.0.0-9999999-ABCDEFGHJI", true);
 
        w->setTitleStyle(TitleStyle::NONE);
        w->setScrollAction(ScrollAction::SCROLL);
        w->setMinHeight(20);
        w->setWidth(250);
                                                                  
        w->popoutFrom(300, 0, PopoutDirection::DOWN);
        w->setIsResizable(true);
                                                                  
    }

    void settings() {
        
        string classType = WidgetManager::WIDGET_CLASS_SETTINGS;
        string widgetPersistentId = "APP_SETTINGS";

        /*
        const TitleStyle TitleStyleVector[] {
            Widget::TitleStyle::NONE,
            Widget::TitleStyle::TOP_STATIC,
            Widget::TitleStyle::TOP_OVERLAY,
            Widget::TitleStyle::TOP_OVERLAY_FULL,
            Widget::TitleStyle::TOP_WITH_WIDGET_RESIZE,
            Widget::TitleStyle::BOTTOM_STATIC,
            Widget::TitleStyle::BOTTOM_OVERLAY,
            Widget::TitleStyle::BOTTOM_OVERLAY_FULL,
            Widget::TitleStyle::BOTTOM_WITH_WIDGET_RESIZE,
            Widget::TitleStyle::LEFT_STATIC,
            Widget::TitleStyle::LEFT_OVERLAY,
            Widget::TitleStyle::LEFT_OVERLAY_FULL,
            Widget::TitleStyle::LEFT_WITH_WIDGET_RESIZE,
            Widget::TitleStyle::RIGHT_STATIC,
            Widget::TitleStyle::RIGHT_OVERLAY,
            Widget::TitleStyle::RIGHT_OVERLAY_FULL,
            Widget::TitleStyle::RIGHT_WITH_WIDGET_RESIZE
        };
        
        int x = 0;
        int y = 0;
        int z = 0;
        for (TitleStyle titleStyle : TitleStyleVector) {
            z++;
            WidgetSettings* w = dynamic_cast<WidgetSettings*>(WidgetManager::loadWidget(classType, widgetPersistentId + ofToString(z), R"(
               <widget>
               <bounds width="150" height="150" minWidth="75" minHeight="75"  />
               </widget>
               )"));

            w->setTitleStyle(titleStyle);
            WidgetManager::addWidget(*w, true);
            w->setWidgetBounds(x, y, 150, 150);
            x += 160;
            if (x >= 750) { x = 0; y += 200; }
            
        }
        */

            WidgetSettings* w = dynamic_cast<WidgetSettings*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                   <widget>
                   <bounds width="150" height="150" minWidth="75" minHeight="75"  />
                   </widget>
                   )"));
        
            WidgetManager::addWidget(*w, false);
            //WidgetManager::showModal(w, true);     
            centerWidget(w);
                                                                        
    }

    void about() {
        /*
        string xml = getWidgetXMLFromFile("about.xml");
        Widget* w = WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS, "ABOUT_APP", xml);
        WidgetManager::addWidget(*w, true);
        
        w->setTitleStyle(Widget::TitleStyle::NONE);
        
        w->setWidgetSize(300, 500, false);
        
        w->popoutFrom(6000, 0, PopoutDirection::DOWN);
*/
        caring_is_creepy();
    }

    void caring_is_creepy() {


        // Chords used
        WidgetChordBucket* chordBucket = dynamic_cast<WidgetChordBucket*>( WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET, "CHORD_BUCKET", "<widget><bounds width='500' height='500'/></widget>"));
        WidgetManager::addWidget(*chordBucket, false);
        gp_parser::Parser p = gp_parser::Parser(ofFilePath::getAbsolutePath("The Shins - Caring Is Creepy.gp5", true).c_str());

        gp_parser::Track guitarTrack = p.tracks[0];

        for(gp_parser::Measure measure: guitarTrack.measures) {
            for (gp_parser::Beat beat: measure.beats) {
                if (beat.chord.name != "") {
                    vizChord chord(beat.chord.name);
                    if (chord.getChordName() != "") {
                        chordBucket->addSelectedChord(chord, true, true);
                    }
                }
            }
        }

        //
        Widget* w = WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS, "LYRICS", R"(
        <widget><bounds width='500' height='500'/>
        <elements>
        <element id="TXT_LYRICS_AUTHOR" class="WidgetElmTextarea">
        <bounds xExpr="${PARENT.LEFT}" yExpr="${PARENT.TOP}" widthExpr="${PARENT.USABLE_WIDTH}" heightExpr="40" />
        </element>
        <element id="TXT_LYRICS" class="WidgetElmTextarea">
        <bounds xExpr="${PARENT.LEFT}" yExpr="${TXT_LYRICS_AUTHOR.BOTTOM}" widthExpr="${PARENT.USABLE_WIDTH}" heightExpr="${PARENT.USABLE_HEIGHT} - ${TXT_LYRICS_AUTHOR.HEIGHT} - ${PADDING}" />
        </element>
        </elements>        
        </widget>
        )");
        WidgetManager::addWidget(*w, true);
        w->getTextarea("TXT_LYRICS_AUTHOR")->setValue("<xlarge>" + p.artist + " - " +  p.title + "</xlarge><br/><large>" + p.album + "</large>");
        w->getTextarea("TXT_LYRICS")->setValue(p.lyric.lyric);


    }

                                                                        
    void loadProject() {
        /*
        ofFileDialogResult r = ofSystemLoadDialog("Load Project (.jam file)", false, ofDirectory("").getAbsolutePath());
        RegularExpression rex(".*.[jam|JAM|xml|XML]");

        if (r.getPath() != "" && rex.match(r.getName())) {
          clearExistingWidgets();
          if (WidgetManager::load(r.filePath, false)) {
              setActiveWidget();
              popoutMenuShouldHide();
              return r.getName();
          }
        }
        return "";
        */


        string classType = WidgetManager::WIDGET_CLASS_FILE_LOAD;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "PROJECT_LOAD" + ofToString(exitingCount + 1);

        WidgetFileLoad* w = dynamic_cast<WidgetFileLoad*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        w->setPathSelectedCallback([w](string filePath) {
            WidgetManager::load(filePath, true, w);
        });


        string recentDir = WidgetFileLocationsList::getMostRecentDirectory();
        w->setSize(deScale(ofGetWindowWidth()*0.7f), deScale(ofGetWindowHeight()*0.7f));
        w->setPath(recentDir);
        WidgetManager::showModal(w, true);     
    }
                                                                      
    
private:
    WidgetMenu *contextMenu = nullptr;
    WidgetOmniMenu *omniMenuMenuItem = nullptr;
    Icon mainMenuIcon = Icon("", Coord::vizBounds(0,0,0,0), 1.0f, Icon::IconSize::REGULAR, ofColor::white, 0);;
    bool mMenuHasBeenHovered = false;
    float mUICurrentMenuLeft = 0.0f;
    
    bool loaded = false;
                                                                        
    void initWidget() override {
        setIsPermanentWidget(true);
        
        setX(0);
        setY(0);

        setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));
        setIgnoreThemeChanges(true);
        setIsRoundedRectangle(false);
        
        mainMenuIcon = IconCache::getIcon("MED_MENU");
        mainMenuIcon.setScaledPos(scale(getUsableX()), scale(getUsableY()));
        mainMenuIcon.setColor(getTheme().TypographyPrimaryColor_withAlpha(getTheme().HoveredTitleAlpha));
        
        setDrawWidgetChrome(true);
        setDrawWidgetTitle(false);
        setIsResizable(false);
        setIsDraggable(false);
        setTitleStyle(TitleStyle::NONE);
        setScrollAction(ScrollAction::NONE);
        setWidth(deScale(mainMenuIcon.getScaledBounds().width));
        setHeight(deScale(mainMenuIcon.getScaledBounds().height));
        

        if (!omniMenuMenuItem) {
           omniMenuMenuItem = new WidgetOmniMenu(
                getWidgetId() + "_OMNI_MENU",
                "<widget><bounds  width='300' height='300' minWidth='300' minHeight='400'/><appearance/></widget>"
            );
// xExpr='${PARENT.ABSOLUTE_USABLE_X}' yExpr='${PARENT.ABSOLUTE_USABLE_Y}'
        }

        
        if (!contextMenu) {

            contextMenu = new WidgetMenu(getWidgetId() + "_MAIN_MENU", "<widget><bounds width='100' heightExpr='${WINDOW.HEIGHT}'/></widget>", getWidgetId()
                                            , WidgetMenu::PreferredPopoutDirection::DOWN, {


            // ----------------------------------------------------------------------------
            // Omni Menu
            // ----------------------------------------------------------------------------
            WidgetMenuTab(Aquamarine::Shared::lang("NewFunc"), IconCache::getIcon("MED_ADD_CIRCLE"),
                            12345,
                            omniMenuMenuItem
                            ),          
                                                                 
            // ----------------------------------------------------------------------------
            // Add... (to be deprecated...)
            // ----------------------------------------------------------------------------
            WidgetMenuTab("Add", IconCache::getIcon("MED_ADD_CIRCLE"),
                                IconCache::IconTag::ADD_CIRCLE, {
                                    WidgetMenuItem("Circle of Fifths", 0),
                                    WidgetMenuItem("Chord Factory", 1),
                                    WidgetMenuItem("Scale Picker", 8),
                                    WidgetMenuItem("Diatonic Chord Wheel", 2),
                                    WidgetMenuItem("Chord Bucket", 3),
                                    WidgetMenuItem("Guitar", 4),
                                    WidgetMenuItem("Guitar (docked)", 5),
                                    WidgetMenuItem("Bass Guitar", 6),
                                    WidgetMenuItem("Bass Guitar (docked)", 7),
                                    WidgetMenuItem("Matrix", 9),
                                    WidgetMenuItem("Sequencer", 12),
                                    WidgetMenuItem("Piano Roll", 10),
                                    WidgetMenuItem("Scale Table", 11),
                                    WidgetMenuItem("Video Player", 13),
                                    WidgetMenuItem("Sound Player", 14),
                                    WidgetMenuItem("Image View", 15),
                                    WidgetMenuItem("Video Recorder", 16),
                                    WidgetMenuItem("File Browser", 17),
                                    WidgetMenuItem("File Load", 18),
                                    WidgetMenuItem("File Save", 19),
                                    WidgetMenuItem("Text Editor", 20),
                                    WidgetMenuItem("Theme Editor", 21)
                                }),
                                                
            // ----------------------------------------------------------------------------
            // Content...
            // ----------------------------------------------------------------------------
            WidgetMenuTab("Content", IconCache::getIcon("MED_BOOK_CONTENT"),
                                IconCache::IconTag::BOOK_CONTENT, { // <---- TODO
                                    WidgetMenuItem("About the Color system...", 1),
                                    WidgetMenuItem("Borrowed Chords", 2),
                                    WidgetMenuItem("bla", 3),
                                    WidgetMenuItem("Unit Tests", 4),
                                    WidgetMenuItem("Debug Info", 5, true, false)
                                }),
            // ----------------------------------------------------------------------------
            // Main Menu
            // ----------------------------------------------------------------------------
            WidgetMenuTab("File", IconCache::getIcon("MED_CONTENT_SETTINGS"),
                                IconCache::IconTag::WIDGET_SETTINGS, {
                                    WidgetMenuItem("New", 0),
                                    WidgetMenuItem("Save", 1),
                                    WidgetMenuItem("Save as...", 2),
                                    WidgetMenuItem("Load...", 3),
                                    WidgetMenuItem("Settings...", 4),
                                    WidgetMenuItem("Enter Licence Key...", 5),
                                    WidgetMenuItem("About this app", 6),
                                    WidgetMenuItem("Exit", -1000)
                                })
            
        });
            contextMenu->setIsPermanentWidget(true);
            
            ofAddListener(dynamic_cast<Aquamarine::WidgetMenu*>(contextMenu)->menuItemSelected, this, &WidgetMainMenu_old::onMenuItemSelected);
    
            contextMenu->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));
            contextMenu->setIgnoreThemeChanges(true);
            
            WidgetManager::addWidget(*contextMenu, false);
            setIsAutoUpdateWhenActive(true);

            contextMenu->setIsVisible(false);
            contextMenu->setIsDraggable(false);
            contextMenu->setIsResizable(false);
            contextMenu->setWidgetPosition(0, deScale(mainMenuIcon.getScaledBounds().height), false);
            contextMenu->setIsRoundedRectangle(false);
            contextMenu->setShowMenuPin(false);

            ofAddListener(contextMenu->widgetUnhovered, this,  &WidgetMainMenu_old::onMenuUnhovered);
            ofAddListener(contextMenu->widgetHovered, this,  &WidgetMainMenu_old::onMenuHovered);
        }
        

        if (!loaded) {
            if (getViz()->getAutoLoadMostRecentProject()) {
                string mostRecentProject = WidgetFileLocationsList::getMostRecentProject();
                if (mostRecentProject != "") { 
                    WidgetManager::load(mostRecentProject, true, this);
                }
            }

            addWIPWidget();
            loaded = true;
        }
        
        
    //  todo - make menu disappear after click, and avoid selections ... (extra mode ... eg - toggle | selectable | diabled | divider)
        // add harmony pad logo at the bottom
        /*
        harmonyJam overlay with colour background
        -- upodate available
        -- news
        -- user login / licenced to....
          show octave below!!
         
         implement:
         drag to left, right bottom, top - glue them (ie - make an expression!)
                      todo: do saving operation animation
         
         known bugs
         MAJOR BUG : widget menus don't get cleaned up after close!
         development log / plan
         ideas / vote / submit idea
         fubmit bug, submit feetback
         key / licence management
         
         */
    }
};


