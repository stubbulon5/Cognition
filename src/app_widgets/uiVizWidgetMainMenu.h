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


#include "ofxAquamarine.h"


class uiVizWidgetMainMenu : public Aquamarine::uiVizWidgetMenuCollection {
    
public:
    uiVizWidgetMainMenu(string persistentId, string widgetXML) : uiVizWidgetMenuCollection(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~uiVizWidgetMainMenu() {
        ofRemoveListener(omniMenu->cellSelected, this,  &uiVizWidgetMainMenu::onOmniMenuCellCelected);
        ofRemoveListener(notificationMenu->notificationItemsChanged, this,  &uiVizWidgetMainMenu::onNotificationItemsChanged);  
    }
    
    void clearExistingWidgets() {
        Aquamarine::uiVizWidgetManager::removeAllWidgetsExcept(this);
    }
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return fileMenu;
            default:
                return nullptr;
        }
    }
    
    void newProject() {

        string classType = APP_CONSTANTS::WIDGET_CLASS_GET_STARTED;
        string widgetPersistentId = "GET_STARTED";

        uiVizWidgetGetStarted* w = dynamic_cast<uiVizWidgetGetStarted*>(Aquamarine::uiVizWidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/getStarted.xml"));

        w->setGetStartedCallback([w, this](string XML) {
            cout << XML;
            Aquamarine::uiVizWidgetManager::removeAllWidgetsExceptMultiple({this, w});
            Aquamarine::uiVizWidgetManager::initWidgetManager(
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
                if (Aquamarine::uiVizWidgetManager::load(filePath, true, w)) {

                    for(uiVizWidget &widget:Aquamarine::uiVizWidgetManager::getWidgets()) {
                        // do things here
                        
                    }
                    Aquamarine::uiVizWidgetManager::setProjectProperties("Untitled Project", "untitled.jam");                

                }
                
            }

// content ideas -- triads (3x inversions - see book)
            }
        });
        Aquamarine::uiVizWidgetManager::showModal(w, true);  
    }
                                                                      
    void saveProject(bool saveAs) {
        Aquamarine::uiVizWidgetManager::ProjectProperties existingProject = Aquamarine::uiVizWidgetManager::getCurrentProjectProperties();
        string proposedFileName = "";
        string currFileName = Aquamarine::uiVizWidgetManager::getCurrentProjectProperties().fileName;
        
        if (saveAs || currFileName == "untitled.jam") {

            string classType = Aquamarine::uiVizWidgetManager::WIDGET_CLASS_FILE_SAVE;
            string widgetPersistentId = Aquamarine::uiVizWidgetManager::getSuggestedNewWidgetPersistentId(classType);

            Aquamarine::uiVizWidgetFileSave* w = dynamic_cast<Aquamarine::uiVizWidgetFileSave*>(Aquamarine::uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
                <widget>
                <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
                </widget>
                )"));

            w->setProposedFileName(currFileName);

            w->setSavePathSelectedCallback([&, w](string filePath) {
  
                filePath = Aquamarine::uiVizShared::removeFileExtension(filePath);
                filePath += ".jam";

                if (Aquamarine::uiVizWidgetManager::save(filePath)) {
                    // Success...
                }
            });

            string recentDir = Aquamarine::uiVizWidgetFileLocationsList::getMostRecentDirectory();
            
            w->setPath(recentDir);
            Aquamarine::uiVizWidgetManager::showModal(w, true);     

            //ofFileDialogResult r = ofSystemSaveDialog(existingProject.fileName, "Save Project (.jam file)");
            //RegularExpression rex(".*.[jam|JAM]");
            
        } else {
            proposedFileName = Aquamarine::uiVizWidgetManager::getCurrentProjectProperties().absolutePath;
        }
        
        if (proposedFileName != "") {
            if (Aquamarine::uiVizWidgetManager::save(proposedFileName)) {
                    // Success...
            }
        }
    }

                                                     
    void loadProject() {
        string classType = Aquamarine::uiVizWidgetManager::WIDGET_CLASS_FILE_LOAD;
        string widgetPersistentId = Aquamarine::uiVizWidgetManager::getSuggestedNewWidgetPersistentId(classType);

        Aquamarine::uiVizWidgetFileLoad* w = dynamic_cast<Aquamarine::uiVizWidgetFileLoad*>(Aquamarine::uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
            </widget>
            )"));

        w->setPathSelectedCallback([w](string filePath) {
            Aquamarine::uiVizWidgetManager::load(filePath, true, w);
        });


        string recentDir = Aquamarine::uiVizWidgetFileLocationsList::getMostRecentDirectory();
        w->setPath(recentDir);
        Aquamarine::uiVizWidgetManager::showModal(w, true);     
    }    

    void licence() {
        string classType = APP_CONSTANTS::WIDGET_CLASS_LICENCE;
        string widgetPersistentId = "LICENCE";

        uiVizWidgetLicence* w = dynamic_cast<uiVizWidgetLicence*>(
            Aquamarine::uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="300" height="450" minWidth="75" minHeight="75"  />
            </widget>
        )"));

        Aquamarine::uiVizWidgetManager::addWidget(*w, true);
        w->setWidgetSize(600, 500, false);

      //  Aquamarine::uiVizWidgetManager::showModal(w, true);     


                                                                  
        w->popoutFrom(200, 300, PopoutDirection::RIGHT);

        w->setIsResizable(true);
                                                                  
    }

    void settings() {
        string classType = Aquamarine::uiVizWidgetManager::WIDGET_CLASS_SETTINGS;
        string widgetPersistentId = "APP_SETTINGS";
        Aquamarine::uiVizWidgetSettings* w = dynamic_cast<Aquamarine::uiVizWidgetSettings*>(Aquamarine::uiVizWidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="150" height="150" minWidth="75" minHeight="75"  />
            </widget>
            )"));
    
        Aquamarine::uiVizWidgetManager::addWidget(*w, false);  
        Aquamarine::uiVizWidgetManager::centerWidget(w);                                                     
    }

    void tutorials() {
        // Coming soon....
    }

    void about(int displayType) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_ABOUT;
        string widgetPersistentId = "APP_ABOUT";        
        uiVizWidgetAbout* w = dynamic_cast<uiVizWidgetAbout*>(Aquamarine::uiVizWidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/about.xml"));
        w->setTitleStyle(uiVizWidget::TitleStyle::TOP_STATIC);
        w->setWidgetSize(600, 600, false);
        w->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));

        switch(displayType) {
            case 1: { // Regular
                Aquamarine::uiVizWidgetManager::addWidget(*w, false); 
                w->setIsVisible(true);  
                w->setWidgetSize(600, 500, false);   
                 w->setWidgetPosition(300, 300, false);                                                         
                break;
            }

            case 2: { // Popout
                Aquamarine::uiVizWidgetManager::addWidget(*w, false); 
                w->setWidgetSize(600, 500, false);                                             
                w->popoutFrom(200, 300, PopoutDirection::RIGHT);
                w->setIsResizable(true);                
                break;
            }

            case 3: { // Modal
                Aquamarine::uiVizWidgetManager::showModal(w, true); 
                break;
            }                        

            
        }



    }
    
    virtual void onMenuItemSelected(Aquamarine::uiVizWidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_FILE) {
            switch(args.activeMenuTabId) {
                case Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS:
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
                case Aquamarine::uiVizIconCache::IconTag::BOOK_CONTENT:
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
            Aquamarine::uiVizWidgetManager::drawDebugInfo(true); 
        }

    }


    virtual void onMenuItemUnselected(Aquamarine::uiVizWidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_DEBUG) {
            Aquamarine::uiVizWidgetManager::drawDebugInfo(false); 
        }
    }    

    // enter licence key, about this app - loses ...
    void onOmniMenuCellCelected(Aquamarine::uiVizWidgetTableArgs &args) {
        clearSelectedSlice();
        args.sender.clearSelectedRows();
        args.sender.setIsVisible(false);
    }    

    void onNotificationItemsChanged(Aquamarine::uiVizWidgetEventArgs &args) {
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
    }

	virtual void onWidgetOwnedWidgetClosed(Aquamarine::uiVizWidgetBase* closedWidget) override {
        clearSelectedSlice();
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
	}     

private:
    Aquamarine::uiVizWidgetMenu *fileMenu = nullptr;
    uiVizWidgetOmniMenuLinks *omniMenu = nullptr;
    Aquamarine::uiVizWidgetMenu *helpMenu = nullptr;    
    uiVizWidgetLicence *licenceMenu = nullptr;
    uiVizWidgetNotifications* notificationMenu = nullptr;
    uiVizWidgetOmniMenu *omniMenuMenuItem = nullptr;
    Aquamarine::uiVizIcon mainMenuIcon = Aquamarine::uiVizIcon("", Aquamarine::uiVizCoord::vizBounds(0,0,0,0), 1.0f, Aquamarine::uiVizIcon::IconSize::REGULAR, ofColor::white, 0);;

    const string MENU_FILE = "FILE";
    const string MENU_ADD = "ADD";
    const string MENU_HELP = "HELP";    
    const string MENU_NOTIFICATION = "NOTIFICATION";
    const string MENU_DEBUG = "DEBUG";
    
    bool loaded = false;
    Aquamarine::uiVizWidgetTheme theme;

    void overrideAlpha() {
        getTheme().UnhoveredWidgetAlpha = getTheme().HoveredWidgetAlpha;
    }

    virtual void onWidgetThemeChanged(Aquamarine::uiVizWidgetEventArgs args) override {
        Aquamarine::uiVizWidgetMenuCollection::onWidgetThemeChanged(args);
        overrideAlpha();
        applyMenuThemeColor();
    }                  

    void applyMenuThemeColor() {
        theme = getViz()->getThemeManager()->getThemeForMainMenu();
        setTheme(theme);

        if (fileMenu != nullptr) fileMenu->setTheme(theme);
        if (omniMenu  != nullptr) omniMenu->setTheme(theme);
        if (helpMenu != nullptr) helpMenu->setTheme(theme);
        if (licenceMenu != nullptr) licenceMenu->setTheme(theme);
        if (notificationMenu != nullptr) notificationMenu->setTheme(theme);

    }

    void initWidget() override {
        overrideAlpha();
        applyMenuThemeColor();
        
        setIsSystemWidget(true);
        // setIgnoreThemeChanges(true);   
        
        if (!loaded) {
            fileMenu = new Aquamarine::uiVizWidgetMenu(getWidgetId() + "_MAIN_MENU_FILE", "<widget></widget>", getWidgetId()
                , Aquamarine::uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab("File", Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                    Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS, {
                        Aquamarine::uiVizWidgetMenuItem("New", 0),
                        Aquamarine::uiVizWidgetMenuItem("Save", 1),
                        Aquamarine::uiVizWidgetMenuItem("Save as...", 2),
                        Aquamarine::uiVizWidgetMenuItem("Load...", 3),
                        Aquamarine::uiVizWidgetMenuItem("Settings...", 4),
                        Aquamarine::uiVizWidgetMenuItem("Exit", -1000)
                    })
                });

            fileMenu->setTheme(theme);

            omniMenu = new uiVizWidgetOmniMenuLinks(getWidgetId() + "_MAIN_MENU_OMNI", "<widget><bounds width=\"460\" height=\"300\"/></widget>");
            ofAddListener(omniMenu->cellSelected, this,  &uiVizWidgetMainMenu::onOmniMenuCellCelected);
            omniMenu->setTheme(theme);
            
            helpMenu = new Aquamarine::uiVizWidgetMenu(getWidgetId() + "_MAIN_MENU_HELP", "<widget></widget>", getWidgetId()
                , Aquamarine::uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab("File", Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"),
                    Aquamarine::uiVizIconCache::IconTag::BOOK_CONTENT, {
                        Aquamarine::uiVizWidgetMenuItem("Tutorials", 0),
                        Aquamarine::uiVizWidgetMenuItem("Enter Licence Key...", 1),                        
                        Aquamarine::uiVizWidgetMenuItem("About (reg)", 2),
                        Aquamarine::uiVizWidgetMenuItem("About (popout)", 3),
                        Aquamarine::uiVizWidgetMenuItem("About (modal)", 4)                                                
                    })
                });
            helpMenu->setTheme(theme);

            licenceMenu = new uiVizWidgetLicence(getWidgetId() + "_LICENCE", R"(
                <widget>
                <bounds width="300" height="300" minWidth="75" minHeight="75"  />
                </widget>
            )");
            licenceMenu->setTheme(theme);



            // Get news and software updates from website
            // There's a bug with autoResizeWidth=1 and popOut func. research 
            notificationMenu = new uiVizWidgetNotifications(getWidgetId() + "_NOTIFICATION", R"(
                <widget>
                    <bounds height="200" width="550" minWidth="75" minHeight="75"  />
                    <properties autoResizeHeight="0" autoResizeWidth="0" showColumnFilters="0"/>
                </widget>
            )");
            ofAddListener(notificationMenu->notificationItemsChanged, this,  &uiVizWidgetMainMenu::onNotificationItemsChanged);  
            notificationMenu->setTheme(theme);

            /* Let the fun begin... */
            setMenuCollection({
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_FILE, fileMenu, "File"),
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_ADD, omniMenu, "Add...", Aquamarine::uiVizIconCache::getIcon("MED_ADD_CIRCLE"),
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::LEFT, VerticalAlign::CENTER)),
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_HELP, helpMenu, "Help"),                    
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_ADD, licenceMenu, Aquamarine::uiVizIconCache::getIcon("REG_USER"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_NOTIFICATION, notificationMenu, Aquamarine::uiVizIconCache::getIcon("REG_DOT"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),                    
                Aquamarine::uiVizWidgetMenuCollectionItem(MENU_DEBUG, nullptr, Aquamarine::uiVizIconCache::getIcon("REG_BUG"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20)))
            });

            setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());

            bool loadedLastProj = false;
            if (getViz()->getAutoLoadMostRecentProject()) {
                string mostRecentProject = Aquamarine::uiVizWidgetFileLocationsList::getMostRecentProject();
                if (mostRecentProject != "") { 
                    loadedLastProj = Aquamarine::uiVizWidgetManager::load(mostRecentProject, true, this);

                }
            }

            if (!loadedLastProj) {
                newProject();
            }

            loaded = true;
        }


    }
};


