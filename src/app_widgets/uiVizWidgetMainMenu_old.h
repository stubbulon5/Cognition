//
//  uiVizMainMenu.h
//  bloom-macos
//
//  Created by Stuart Barnes on 12/04/2019.
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"

#include "uiVizWidgetChordWheel.h"
#include "uiVizWidgetChordBucket.h"
#include "uiVizWidgetChordBucketSuggester.h"
#include "uiVizWidgetChordDesigner.h"
#include "uiVizWidgetScalePicker.h"
#include "uiVizWidgetKeyPicker.h"
#include "uiVizWigetStringedInstrument.h"
#include "uiVizWidgetGuitar.h"
#include "uiVizWidgetBassGuitar.h"
#include "uiVizWidgetTutor.h"
#include "uiVizWidgetUnitTests.h"
#include "uiVizWidgetLicence.h"
#include "uiVizWidgetScaleTable.h"
#include "uiVizWidgetOmniMenu.h"

#include "ofxAquamarine.h"
#include "../core/gp_parser/gp_parser.h"


class uiVizWidgetMainMenu_old : public uiVizWidget {
    
public:
    
    uiVizWidgetMainMenu_old(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~uiVizWidgetMainMenu_old() {
        ofRemoveListener(contextMenu->widgetUnhovered, this,  &uiVizWidgetMainMenu_old::onMenuUnhovered);
        ofRemoveListener(contextMenu->widgetHovered, this,  &uiVizWidgetMainMenu_old::onMenuHovered);
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
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU, 0);
        return mWidgetXML;
    }
    
    void update(Aquamarine::uiVizWidgetContext context) override {
        mainMenuIcon.setScaledPos(scale(getX()), scale(getY()));
        
        if (parent()) {
            contextMenu->setHeight_Expr("${" + parent()->getPersistentId() + ".USABLE_HEIGHT} - ${PADDING}*2");
        }
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
       
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
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return contextMenu;
            default:
                return nullptr;
        }
    }
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {
            showContextMenu(uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }

    void onMenuItemSelected(Aquamarine::uiVizWidgetMenuItemArgs & args) {
        bool clearSelection = true;

        switch(args.activeMenuTabId) {
                
            case uiVizIconCache::IconTag::ADD_CIRCLE:
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

            case uiVizIconCache::IconTag::BOOK_CONTENT:
                clearSelection = false;
                switch(args.menuItem->uniqueID) {
                    case 4:
                        addDeveloperTools(); break;
                    case 5:
                        WidgetManager::drawDebugInfo(args.menuItem->isSelected); break;
                }
                break;
                
            case uiVizIconCache::IconTag::WIDGET_SETTINGS:
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

    void onMenuUnhovered(uiVizWidgetEventArgs &args) {
        if (!mMenuHasBeenHovered) return;
        setActiveWidget();
        popoutMenuShouldHide();
    }
    
    void popoutMenuShouldHide() {
        mMenuHasBeenHovered = true;
        mUICurrentMenuLeft--;
        setNeedsUpdate(true);
    }
    
    void onMenuHovered(uiVizWidgetEventArgs &args) {
        mMenuHasBeenHovered = true;
    }
    
    
    void centerWidget(uiVizWidget* w) {
        w->setX_Expr("${WINDOW.WIDTH}/2 - ${SELF.USABLE_WIDTH}/2");
        w->setY_Expr("${WINDOW.HEIGHT}/2 - ${SELF.USABLE_HEIGHT}/2");
        WidgetManager::recalculateWidgetExpressions(*w);
        w->clearWidgetLayoutExpressions();
    }
    
    uiVizWidgetKeyPicker* addKeyPicker(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "KEY_PICKER" + ofToString(exitingCount + 1);
        
        uiVizWidgetKeyPicker* w = dynamic_cast<uiVizWidgetKeyPicker*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="250" height="250" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }
                                                                      
    uiVizWidgetChordDesigner* addChordDesigner(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_DESIGNER" + ofToString(exitingCount + 1);

        uiVizWidgetChordDesigner* w = dynamic_cast<uiVizWidgetChordDesigner*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }

    uiVizWidgetScalePicker* addScalePicker(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SCALE_PICKER" + ofToString(exitingCount + 1);

        uiVizWidgetScalePicker* w = dynamic_cast<uiVizWidgetScalePicker*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        //WidgetManager::showModal(w, true);     
        return w;
    }

    uiVizWidgetVideoPlayer* addVideoPlayer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_VIDEO_PLAYER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "VIDEO_PLAYER" + ofToString(exitingCount + 1);

        uiVizWidgetVideoPlayer* w = dynamic_cast<uiVizWidgetVideoPlayer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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

    uiVizWidgetVideoGrabber* addVideoGrabber(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_VIDEO_GRABBER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "VIDEO_GRABBER" + ofToString(exitingCount + 1);

        uiVizWidgetVideoGrabber* w = dynamic_cast<uiVizWidgetVideoGrabber*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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

    uiVizWidgetSoundPlayer* addSoundPlayer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_SOUND_PLAYER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SOUND_PLAYER" + ofToString(exitingCount + 1);

        uiVizWidgetSoundPlayer* w = dynamic_cast<uiVizWidgetSoundPlayer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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

    uiVizWidgetImageView* addImageView(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_IMAGE_VIEW;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "IMAGE_VIEW" + ofToString(exitingCount + 1);

        uiVizWidgetImageView* w = dynamic_cast<uiVizWidgetImageView*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties file="/home/zabba/Desktop/shins1.jpg" doesRespondToFileDrop="1" />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }       


    uiVizWidgetFileExplorer* addFileExplorer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_EXPLORER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_EXPLORER" + ofToString(exitingCount + 1);

        uiVizWidgetFileExplorer* w = dynamic_cast<uiVizWidgetFileExplorer*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties path="/home/zabba/projects/Batch-BQ-to-S3-Exporter"/>
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }  

    uiVizWidgetFileLoad* addFileLoad(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_LOAD;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_LOAD" + ofToString(exitingCount + 1);

        uiVizWidgetFileLoad* w = dynamic_cast<uiVizWidgetFileLoad*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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


    uiVizWidgetFileSave* addFileSave(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_FILE_SAVE;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_SAVE" + ofToString(exitingCount + 1);

        uiVizWidgetFileSave* w = dynamic_cast<uiVizWidgetFileSave*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       <properties path="/home/zabba/projects/Batch-BQ-to-S3-Exporter"/>
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }   

    uiVizWidgetTextEditor* addTextEditor(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_TEXT_EDITOR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "FILE_SAVE" + ofToString(exitingCount + 1);

        uiVizWidgetTextEditor* w = dynamic_cast<uiVizWidgetTextEditor*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }         

    uiVizWidgetThemeEditor* addThemeEditor(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_THEME_EDITOR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "THEME_EDITOR" + ofToString(exitingCount + 1);

        uiVizWidgetThemeEditor* w = dynamic_cast<uiVizWidgetThemeEditor*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }                  
    
    uiVizWidgetChordWheel* addChordWheel(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_WHEEL" + ofToString(exitingCount + 1);

        uiVizWidgetChordWheel* w = dynamic_cast<uiVizWidgetChordWheel*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="600" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }

    uiVizWidgetChordBucket* addChordBucket(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "CHORD_BUCKET" + ofToString(exitingCount + 1);

        uiVizWidgetChordBucket* w = dynamic_cast<uiVizWidgetChordBucket*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="320" height="500" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        WidgetManager::addWidget(*w, true);
        centerWidget(w);
        return w;
    }
                                                                              
    uiVizWidgetGuitar* addGuitar(bool docked, int strings) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_GUITAR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "GUITAR" + ofToString(exitingCount + 1);
        
        uiVizWidgetGuitar* w = dynamic_cast<uiVizWidgetGuitar*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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


    uiVizWidgetBassGuitar* addBassGuitar(bool docked, int strings) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "BASS_GUITAR" + ofToString(exitingCount + 1);

        uiVizWidgetBassGuitar* w = dynamic_cast<uiVizWidgetBassGuitar*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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

    uiVizWidgetMatrix* addMatrix(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_MATRIX;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "MATRIX" + ofToString(exitingCount + 1);

        uiVizWidgetMatrix* w = dynamic_cast<uiVizWidgetMatrix*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_MATRIX, widgetPersistentId, R"(
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

    uiVizWidgetSequencer* addSequencer(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_SEQUENCER;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SEQUENCER" + ofToString(exitingCount + 1);

        uiVizWidgetSequencer* w = dynamic_cast<uiVizWidgetSequencer*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_SEQUENCER, widgetPersistentId, R"(
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

    uiVizWidgetPianoRoll* addPianoRoll(bool docked) {
        string classType = WidgetManager::WIDGET_CLASS_PIANO_ROLL;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "PIANO_ROLL" + ofToString(exitingCount + 1);

        uiVizWidgetPianoRoll* w = dynamic_cast<uiVizWidgetPianoRoll*>(WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS_PIANO_ROLL, widgetPersistentId, R"(
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

    uiVizWidgetScaleTable* addScaleTable(bool docked) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE;
        int exitingCount = WidgetManager::getCountOfWidgetClassType(classType);
        string widgetPersistentId = "SCALE_TABLE" + ofToString(exitingCount + 1);

        uiVizWidgetScaleTable* w = dynamic_cast<uiVizWidgetScaleTable*>(WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE, widgetPersistentId, R"(
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

    void onTableCellInitialized(uiVizWidgetTableArgs & args) {
        if (args.cell.key == "WIDGET" && args.cell.cellWidget != nullptr) {
            uiVizWidgetKeyPicker* scalePicker = dynamic_cast<uiVizWidgetKeyPicker*>(args.cell.cellWidget);
            //scalePicker->setSelectedScale(args.row.key);
            scalePicker->setSelectedKey(vizNote("D", 3, 3));
            scalePicker->setNeedsUpdate(true);
        }
    }

    void addDeveloperTools() {

        uiVizWidgetUnitTests* w = dynamic_cast<uiVizWidgetUnitTests*>(WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_UNIT_TESTS, "UNIT_TESTS", R"(
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

            uiVizWidgetFileSave* w = dynamic_cast<uiVizWidgetFileSave*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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

            string recentDir = uiVizWidgetFileLocationsList::getMostRecentDirectory();
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

        uiVizWidgetLicence* w = dynamic_cast<uiVizWidgetLicence*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="250" height="450" minWidth="75" minHeight="75"  />
            </widget>
        )"));

        WidgetManager::addWidget(*w, true);

        uiVizWidgetElmTextbox* TXT_LICENCE = w->getTextbox("TXT_LICENCE");
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
            uiVizWidget::TitleStyle::NONE,
            uiVizWidget::TitleStyle::TOP_STATIC,
            uiVizWidget::TitleStyle::TOP_OVERLAY,
            uiVizWidget::TitleStyle::TOP_OVERLAY_FULL,
            uiVizWidget::TitleStyle::TOP_WITH_WIDGET_RESIZE,
            uiVizWidget::TitleStyle::BOTTOM_STATIC,
            uiVizWidget::TitleStyle::BOTTOM_OVERLAY,
            uiVizWidget::TitleStyle::BOTTOM_OVERLAY_FULL,
            uiVizWidget::TitleStyle::BOTTOM_WITH_WIDGET_RESIZE,
            uiVizWidget::TitleStyle::LEFT_STATIC,
            uiVizWidget::TitleStyle::LEFT_OVERLAY,
            uiVizWidget::TitleStyle::LEFT_OVERLAY_FULL,
            uiVizWidget::TitleStyle::LEFT_WITH_WIDGET_RESIZE,
            uiVizWidget::TitleStyle::RIGHT_STATIC,
            uiVizWidget::TitleStyle::RIGHT_OVERLAY,
            uiVizWidget::TitleStyle::RIGHT_OVERLAY_FULL,
            uiVizWidget::TitleStyle::RIGHT_WITH_WIDGET_RESIZE
        };
        
        int x = 0;
        int y = 0;
        int z = 0;
        for (TitleStyle titleStyle : TitleStyleVector) {
            z++;
            uiVizWidgetSettings* w = dynamic_cast<uiVizWidgetSettings*>(WidgetManager::loadWidget(classType, widgetPersistentId + ofToString(z), R"(
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

            uiVizWidgetSettings* w = dynamic_cast<uiVizWidgetSettings*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
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
        uiVizWidget* w = WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS, "ABOUT_APP", xml);
        WidgetManager::addWidget(*w, true);
        
        w->setTitleStyle(uiVizWidget::TitleStyle::NONE);
        
        w->setWidgetSize(300, 500, false);
        
        w->popoutFrom(6000, 0, PopoutDirection::DOWN);
*/
        caring_is_creepy();
    }

    void caring_is_creepy() {


        // Chords used
        uiVizWidgetChordBucket* chordBucket = dynamic_cast<uiVizWidgetChordBucket*>( WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET, "CHORD_BUCKET", "<widget><bounds width='500' height='500'/></widget>"));
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
        uiVizWidget* w = WidgetManager::loadWidget(WidgetManager::WIDGET_CLASS, "LYRICS", R"(
        <widget><bounds width='500' height='500'/>
        <elements>
        <element id="TXT_LYRICS_AUTHOR" class="uiVizWidgetElmTextarea">
        <bounds xExpr="${PARENT.LEFT}" yExpr="${PARENT.TOP}" widthExpr="${PARENT.USABLE_WIDTH}" heightExpr="40" />
        </element>
        <element id="TXT_LYRICS" class="uiVizWidgetElmTextarea">
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

        uiVizWidgetFileLoad* w = dynamic_cast<uiVizWidgetFileLoad*>(WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                                       <widget>
                                       <bounds width="400" height="400" minWidth="75" minHeight="75"  />
                                       </widget>
                                       )"));

        w->setPathSelectedCallback([w](string filePath) {
            WidgetManager::load(filePath, true, w);
        });


        string recentDir = uiVizWidgetFileLocationsList::getMostRecentDirectory();
        w->setSize(deScale(ofGetWindowWidth()*0.7f), deScale(ofGetWindowHeight()*0.7f));
        w->setPath(recentDir);
        WidgetManager::showModal(w, true);     
    }
                                                                      
    
private:
    uiVizWidgetMenu *contextMenu = nullptr;
    uiVizWidgetOmniMenu *omniMenuMenuItem = nullptr;
    uiVizIcon mainMenuIcon = uiVizIcon("", Coord::vizBounds(0,0,0,0), 1.0f, uiVizIcon::IconSize::REGULAR, ofColor::white, 0);;
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
        
        mainMenuIcon = uiVizIconCache::getIcon("MED_MENU");
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
           omniMenuMenuItem = new uiVizWidgetOmniMenu(
                getWidgetId() + "_OMNI_MENU",
                "<widget><bounds  width='300' height='300' minWidth='300' minHeight='400'/><appearance/></widget>"
            );
// xExpr='${PARENT.ABSOLUTE_USABLE_X}' yExpr='${PARENT.ABSOLUTE_USABLE_Y}'
        }

        
        if (!contextMenu) {

            contextMenu = new uiVizWidgetMenu(getWidgetId() + "_MAIN_MENU", "<widget><bounds width='100' heightExpr='${WINDOW.HEIGHT}'/></widget>", getWidgetId()
                                            , uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {


            // ----------------------------------------------------------------------------
            // Omni Menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(Aquamarine::Shared::lang("NewFunc"), uiVizIconCache::getIcon("MED_ADD_CIRCLE"),
                            12345,
                            omniMenuMenuItem
                            ),          
                                                                 
            // ----------------------------------------------------------------------------
            // Add... (to be deprecated...)
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab("Add", uiVizIconCache::getIcon("MED_ADD_CIRCLE"),
                                uiVizIconCache::IconTag::ADD_CIRCLE, {
                                    uiVizWidgetMenuItem("Circle of Fifths", 0),
                                    uiVizWidgetMenuItem("Chord Factory", 1),
                                    uiVizWidgetMenuItem("Scale Picker", 8),
                                    uiVizWidgetMenuItem("Diatonic Chord Wheel", 2),
                                    uiVizWidgetMenuItem("Chord Bucket", 3),
                                    uiVizWidgetMenuItem("Guitar", 4),
                                    uiVizWidgetMenuItem("Guitar (docked)", 5),
                                    uiVizWidgetMenuItem("Bass Guitar", 6),
                                    uiVizWidgetMenuItem("Bass Guitar (docked)", 7),
                                    uiVizWidgetMenuItem("Matrix", 9),
                                    uiVizWidgetMenuItem("Sequencer", 12),
                                    uiVizWidgetMenuItem("Piano Roll", 10),
                                    uiVizWidgetMenuItem("Scale Table", 11),
                                    uiVizWidgetMenuItem("Video Player", 13),
                                    uiVizWidgetMenuItem("Sound Player", 14),
                                    uiVizWidgetMenuItem("Image View", 15),
                                    uiVizWidgetMenuItem("Video Recorder", 16),
                                    uiVizWidgetMenuItem("File Browser", 17),
                                    uiVizWidgetMenuItem("File Load", 18),
                                    uiVizWidgetMenuItem("File Save", 19),
                                    uiVizWidgetMenuItem("Text Editor", 20),
                                    uiVizWidgetMenuItem("Theme Editor", 21)
                                }),
                                                
            // ----------------------------------------------------------------------------
            // Content...
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab("Content", uiVizIconCache::getIcon("MED_BOOK_CONTENT"),
                                uiVizIconCache::IconTag::BOOK_CONTENT, { // <---- TODO
                                    uiVizWidgetMenuItem("About the Color system...", 1),
                                    uiVizWidgetMenuItem("Borrowed Chords", 2),
                                    uiVizWidgetMenuItem("bla", 3),
                                    uiVizWidgetMenuItem("Unit Tests", 4),
                                    uiVizWidgetMenuItem("Debug Info", 5, true, false)
                                }),
            // ----------------------------------------------------------------------------
            // Main Menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab("File", uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                                uiVizIconCache::IconTag::WIDGET_SETTINGS, {
                                    uiVizWidgetMenuItem("New", 0),
                                    uiVizWidgetMenuItem("Save", 1),
                                    uiVizWidgetMenuItem("Save as...", 2),
                                    uiVizWidgetMenuItem("Load...", 3),
                                    uiVizWidgetMenuItem("Settings...", 4),
                                    uiVizWidgetMenuItem("Enter Licence Key...", 5),
                                    uiVizWidgetMenuItem("About this app", 6),
                                    uiVizWidgetMenuItem("Exit", -1000)
                                })
            
        });
            contextMenu->setIsPermanentWidget(true);
            
            ofAddListener(dynamic_cast<Aquamarine::uiVizWidgetMenu*>(contextMenu)->menuItemSelected, this, &uiVizWidgetMainMenu_old::onMenuItemSelected);
    
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

            ofAddListener(contextMenu->widgetUnhovered, this,  &uiVizWidgetMainMenu_old::onMenuUnhovered);
            ofAddListener(contextMenu->widgetHovered, this,  &uiVizWidgetMainMenu_old::onMenuHovered);
        }
        

        if (!loaded) {
            if (getViz()->getAutoLoadMostRecentProject()) {
                string mostRecentProject = uiVizWidgetFileLocationsList::getMostRecentProject();
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


