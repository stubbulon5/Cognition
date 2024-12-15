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
#include "uiVizWidgetAbout.h"
#include "uiVizWidgetUnitTests.h"
#include "uiVizWidgetLicence.h"
#include "uiVizWidgetScaleTable.h"
#include "uiVizWidgetOmniMenu.h"
#include "uiVizWidgetGetStarted.h"
#include "uiVizWidgetNotifications.h"


#include "../uiViz/widget/uiVizWidgetSettings.h"
#include "../uiViz/widget/uiVizWidgetTable.h"
#include "../uiViz/widget/uiVizWidgetTextEditor.h"
#include "../uiViz/widget/uiVizWidgetMatrix.h"
#include "../uiViz/widget/uiVizWidgetSequencer.h"
#include "../uiViz/widget/uiVizWidgetPianoRoll.h"
#include "../uiViz/widget/uiVizWidgetVideoPlayer.h"
#include "../uiViz/widget/uiVizWidgetVideoGrabber.h"
#include "../uiViz/widget/uiVizWidgetSoundPlayer.h"
#include "../uiViz/widget/uiVizWidgetImageView.h"
#include "../uiViz/widget/system/uiVizWidgetFileExplorer.h"
#include "../uiViz/widget/system/uiVizWidgetFileLoad.h"
#include "../uiViz/widget/system/uiVizWidgetFileSave.h"
#include "../uiViz/widget/system/uiVizWidgetThemeEditor.h"

#include "../uiViz/widget/uiVizWidgetMenuCollection.h"
//#include "uiVizWidgetAerosLooper.h"


class uiVizWidgetMainMenu : public uiVizWidgetMenuCollection {
    
public:
    uiVizWidgetMainMenu(string persistentId, string widgetXML) : uiVizWidgetMenuCollection(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~uiVizWidgetMainMenu() {
        ofRemoveListener(omniMenu->cellSelected, this,  &uiVizWidgetMainMenu::onOmniMenuCellCelected);
        ofRemoveListener(notificationMenu->notificationItemsChanged, this,  &uiVizWidgetMainMenu::onNotificationItemsChanged);  
    }
    
    void clearExistingWidgets() {
        uiVizWidgetManager::removeAllWidgetsExcept(this);
    }
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return fileMenu;
            default:
                return nullptr;
        }
    }
    
    void newProject() {

        string classType = APP_CONSTANTS::WIDGET_CLASS_GET_STARTED;
        string widgetPersistentId = "GET_STARTED";

        uiVizWidgetGetStarted* w = dynamic_cast<uiVizWidgetGetStarted*>(uiVizWidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/getStarted.xml"));

        w->setGetStartedCallback([w, this](string XML) {
            cout << XML;
            uiVizWidgetManager::removeAllWidgetsExceptMultiple({this, w});
            uiVizWidgetManager::initWidgetManager(
                APP_CONSTANTS::APPLICATION_NAME,
                APP_CONSTANTS::APPLICATION_VERSION,
                APP_CONSTANTS::APPLICATION_FILE_EXTENSION
            );

            ofxXmlSettings mWidgetXML = ofxXmlSettings();
            

            if (mWidgetXML.loadFromBuffer(XML.c_str())) {

            string type = mWidgetXML.getAttribute("new", "type", "");
            string value = mWidgetXML.getAttribute("new", "value", "");
            if (type == "file") {
                string filePath = ofToDataPath(value, true);
                if (uiVizWidgetManager::load(filePath, true, w)) {

                    for(uiVizWidget &widget:uiVizWidgetManager::getWidgets()) {
                        // do things here
                        
                    }
                    uiVizWidgetManager::setProjectProperties("Untitled Project", "untitled.jam");                

                }
                
            }

// content ideas -- triads (3x inversions - see book)
            }
        });
        uiVizWidgetManager::showModal(w, true);  
    }
                                                                      
    void saveProject(bool saveAs) {
        uiVizWidgetManager::ProjectProperties existingProject = uiVizWidgetManager::getCurrentProjectProperties();
        string proposedFileName = "";
        string currFileName = uiVizWidgetManager::getCurrentProjectProperties().fileName;
        
        if (saveAs || currFileName == "untitled.jam") {

            string classType = uiVizWidgetManager::WIDGET_CLASS_FILE_SAVE;
            string widgetPersistentId = uiVizWidgetManager::getSuggestedNewWidgetPersistentId(classType);

            uiVizWidgetFileSave* w = dynamic_cast<uiVizWidgetFileSave*>(uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
                <widget>
                <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
                </widget>
                )"));

            w->setProposedFileName(currFileName);

            w->setSavePathSelectedCallback([&, w](string filePath) {
  
                filePath = uiVizShared::removeFileExtension(filePath);
                filePath += ".jam";

                if (uiVizWidgetManager::save(filePath)) {
                    // Success...
                }
            });

            string recentDir = uiVizWidgetFileLocationsList::getMostRecentDirectory();
            
            w->setPath(recentDir);
            uiVizWidgetManager::showModal(w, true);     

            //ofFileDialogResult r = ofSystemSaveDialog(existingProject.fileName, "Save Project (.jam file)");
            //RegularExpression rex(".*.[jam|JAM]");
            
        } else {
            proposedFileName = uiVizWidgetManager::getCurrentProjectProperties().absolutePath;
        }
        
        if (proposedFileName != "") {
            if (uiVizWidgetManager::save(proposedFileName)) {
                    // Success...
            }
        }
    }

                                                     
    void loadProject() {
        string classType = uiVizWidgetManager::WIDGET_CLASS_FILE_LOAD;
        string widgetPersistentId = uiVizWidgetManager::getSuggestedNewWidgetPersistentId(classType);

        uiVizWidgetFileLoad* w = dynamic_cast<uiVizWidgetFileLoad*>(uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
            </widget>
            )"));

        w->setPathSelectedCallback([w](string filePath) {
            uiVizWidgetManager::load(filePath, true, w);
        });


        string recentDir = uiVizWidgetFileLocationsList::getMostRecentDirectory();
        w->setPath(recentDir);
        uiVizWidgetManager::showModal(w, true);     
    }    

    void licence() {
        string classType = APP_CONSTANTS::WIDGET_CLASS_LICENCE;
        string widgetPersistentId = "LICENCE";

        uiVizWidgetLicence* w = dynamic_cast<uiVizWidgetLicence*>(
            uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="300" height="450" minWidth="75" minHeight="75"  />
            </widget>
        )"));

        uiVizWidgetManager::addWidget(*w, true);
        w->setWidgetSize(600, 500, false);

      //  uiVizWidgetManager::showModal(w, true);     


                                                                  
        w->popoutFrom(200, 300, PopoutDirection::RIGHT);

        w->setIsResizable(true);
                                                                  
    }

    void settings() {
        string classType = uiVizWidgetManager::WIDGET_CLASS_SETTINGS;
        string widgetPersistentId = "APP_SETTINGS";
        uiVizWidgetSettings* w = dynamic_cast<uiVizWidgetSettings*>(uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="150" height="150" minWidth="75" minHeight="75"  />
            </widget>
            )"));
    
        uiVizWidgetManager::addWidget(*w, false);  
        uiVizWidgetManager::centerWidget(w);                                                     
    }

    void tutorials() {
        // Coming soon....
    }

    void about(int displayType) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_ABOUT;
        string widgetPersistentId = "APP_ABOUT";        
        uiVizWidgetAbout* w = dynamic_cast<uiVizWidgetAbout*>(uiVizWidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/about.xml"));
        w->setTitleStyle(uiVizWidget::TitleStyle::TOP_STATIC);
        w->setWidgetSize(600, 600, false);
        w->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));

        switch(displayType) {
            case 1: { // Regular
                uiVizWidgetManager::addWidget(*w, false); 
                w->setIsVisible(true);  
                w->setWidgetSize(600, 500, false);   
                 w->setWidgetPosition(300, 300, false);                                                         
                break;
            }

            case 2: { // Popout
                uiVizWidgetManager::addWidget(*w, false); 
                w->setWidgetSize(600, 500, false);                                             
                w->popoutFrom(200, 300, PopoutDirection::RIGHT);
                w->setIsResizable(true);                
                break;
            }

            case 3: { // Modal
                uiVizWidgetManager::showModal(w, true); 
                break;
            }                        

            
        }



    }
    
    virtual void onMenuItemSelected(uiVizWidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_FILE) {
            switch(args.activeMenuTabId) {
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
                        case -1000: {
                            clearExistingWidgets();
                            OF_EXIT_APP(0); 
                            break;
                        }
                    }
                break;
            }
        } else if (args.menuTag == MENU_HELP) {
            switch(args.activeMenuTabId) {
                case uiVizIconCache::IconTag::BOOK_CONTENT:
                    switch(args.menuItem->uniqueID) {
                        case 0: // tutorials
                            tutorials(); break;
                        case 1: // licence
                            licence(); break;
                        case 2: // about
                            about(1); break;   
                        case 3: // about
                            about(2); break;    
                        case 4: // about
                            about(3); break;                                                         
                    }
                break;
            }
        } else if (args.menuTag == MENU_DEBUG) {
            uiVizWidgetManager::drawDebugInfo(true); 
        }

    }


    virtual void onMenuItemUnselected(uiVizWidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_DEBUG) {
            uiVizWidgetManager::drawDebugInfo(false); 
        }
    }    

    // enter licence key, about this app - loses ...
    void onOmniMenuCellCelected(uiVizWidgetTableArgs &args) {
        clearSelectedSlice();
        args.sender.clearSelectedRows();
        args.sender.setIsVisible(false);
    }    

    void onNotificationItemsChanged(uiVizWidgetEventArgs &args) {
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
    }

	virtual void onWidgetOwnedWidgetClosed(uiVizWidgetBase* closedWidget) override {
        clearSelectedSlice();
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
	}     

private:
    uiVizWidgetMenu *fileMenu = nullptr;
    uiVizWidgetOmniMenuLinks *omniMenu = nullptr;
    uiVizWidgetMenu *helpMenu = nullptr;    
    uiVizWidgetLicence *licenceMenu = nullptr;
    uiVizWidgetNotifications* notificationMenu;
    uiVizWidgetOmniMenu *omniMenuMenuItem = nullptr;
    uiVizIcon mainMenuIcon = uiVizIcon("", uiVizCoord::vizBounds(0,0,0,0), 1.0f, uiVizIcon::IconSize::REGULAR, ofColor::white, 0);;

    const string MENU_FILE = "FILE";
    const string MENU_ADD = "ADD";
    const string MENU_HELP = "HELP";    
    const string MENU_NOTIFICATION = "NOTIFICATION";
    const string MENU_DEBUG = "DEBUG";
    
    bool loaded = false;

    void overrideAlpha() {
        getTheme().UnhoveredWidgetAlpha = getTheme().HoveredWidgetAlpha;
    }

    virtual void onWidgetThemeChanged(uiVizWidgetEventArgs args) override {
        uiVizWidgetMenuCollection::onWidgetThemeChanged(args);
        overrideAlpha();
    }                  

    void initWidget() override {
        overrideAlpha();
        //setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));
        //setIgnoreThemeChanges(true);   
        
        if (!loaded) {
            fileMenu = new uiVizWidgetMenu(getWidgetId() + "_MAIN_MENU_FILE", "<widget></widget>", getWidgetId()
                , uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab("File", uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                    uiVizIconCache::IconTag::WIDGET_SETTINGS, {
                        uiVizWidgetMenuItem("New", 0),
                        uiVizWidgetMenuItem("Save", 1),
                        uiVizWidgetMenuItem("Save as...", 2),
                        uiVizWidgetMenuItem("Load...", 3),
                        uiVizWidgetMenuItem("Settings...", 4),
                        uiVizWidgetMenuItem("Exit", -1000)
                    })
                });

            omniMenu = new uiVizWidgetOmniMenuLinks(getWidgetId() + "_MAIN_MENU_OMNI", "<widget><bounds width=\"460\" height=\"300\"/></widget>");
            ofAddListener(omniMenu->cellSelected, this,  &uiVizWidgetMainMenu::onOmniMenuCellCelected);
            
            helpMenu = new uiVizWidgetMenu(getWidgetId() + "_MAIN_MENU_HELP", "<widget></widget>", getWidgetId()
                , uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab("File", uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                    uiVizIconCache::IconTag::BOOK_CONTENT, {
                        uiVizWidgetMenuItem("Tutorials", 0),
                        uiVizWidgetMenuItem("Enter Licence Key...", 1),                        
                        uiVizWidgetMenuItem("About (reg)", 2),
                        uiVizWidgetMenuItem("About (popout)", 3),
                        uiVizWidgetMenuItem("About (modal)", 4)                                                
                    })
                });

            licenceMenu = new uiVizWidgetLicence(getWidgetId() + "_LICENCE", R"(
                <widget>
                <bounds width="300" height="300" minWidth="75" minHeight="75"  />
                </widget>
            )");



            // Get news and software updates from website
            // There's a bug with autoResizeWidth=1 and popOut func. research 
            notificationMenu = new uiVizWidgetNotifications(getWidgetId() + "_NOTIFICATION", R"(
                <widget>
                    <bounds height="200" width="550" minWidth="75" minHeight="75"  />
                    <properties autoResizeHeight="0" autoResizeWidth="0" showColumnFilters="0"/>
                </widget>
            )");
            ofAddListener(notificationMenu->notificationItemsChanged, this,  &uiVizWidgetMainMenu::onNotificationItemsChanged);  

            /* Let the fun begin... */
            setMenuCollection({
                uiVizWidgetMenuCollectionItem(MENU_FILE, fileMenu, "File"),
                uiVizWidgetMenuCollectionItem(MENU_ADD, omniMenu, "Add...", uiVizIconCache::getIcon("MED_ADD_CIRCLE"),
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::LEFT, VerticalAlign::CENTER)),
                uiVizWidgetMenuCollectionItem(MENU_HELP, helpMenu, "Help"),                    
                uiVizWidgetMenuCollectionItem(MENU_ADD, licenceMenu, uiVizIconCache::getIcon("REG_USER"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),
                uiVizWidgetMenuCollectionItem(MENU_NOTIFICATION, notificationMenu, uiVizIconCache::getIcon("REG_DOT"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),                    
                uiVizWidgetMenuCollectionItem(MENU_DEBUG, nullptr, uiVizIconCache::getIcon("REG_BUG"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20)))
            });

            setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());

            bool loadedLastProj = false;
            if (getViz()->getAutoLoadMostRecentProject()) {
                string mostRecentProject = uiVizWidgetFileLocationsList::getMostRecentProject();
                if (mostRecentProject != "") { 
                    loadedLastProj = uiVizWidgetManager::load(mostRecentProject, true, this);

                }
            }

            if (!loadedLastProj) {
                newProject();
            }

            loaded = true;
        }

        // aerosLooper();

    }

    // void aerosLooper()  {
    //     // Temp while testing / developing Aeros Util
    //     uiVizWidgetAerosLooper* w = new uiVizWidgetAerosLooper("APP_AEROS", "");
    //     uiVizWidgetManager::loadWidgetFromFileToExisting("ui/widgets/uiVizWidgetAerosLooper.xml", *w);

    //     // uiVizWidgetAerosLooperSong* w = new uiVizWidgetAerosLooperSong("APP_AEROS", "");
    //     // uiVizWidgetManager::loadWidgetFromFileToExisting("ui/widgets/uiVizWidgetAerosLooperSong.xml", *w);

    //     w->setTitleStyle(uiVizWidget::TitleStyle::TOP_STATIC);
    //     w->setWidgetSize(600, 600, false);
    //     w->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));
    //     uiVizWidgetManager::showModal(w, true); 
    //     //uiVizWidgetManager::addWidget(*w, false);         
    // }
};


