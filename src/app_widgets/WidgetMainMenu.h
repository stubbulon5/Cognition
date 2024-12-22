//
//  vizMainMenu.h
//  bloom-macos
//
//  Created by Stuart Barnes on 12/04/2019.
//
#pragma once
#include "../viz/widget/Widget.h"

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
#include "WidgetAbout.h"
#include "WidgetUnitTests.h"
#include "WidgetLicence.h"
#include "WidgetScaleTable.h"
#include "WidgetOmniMenu.h"
#include "WidgetGetStarted.h"
#include "WidgetNotifications.h"


#include "ofxAquamarine.h"


class WidgetMainMenu : public Aquamarine::WidgetMenuCollection {
    
public:
    WidgetMainMenu(string persistentId, string widgetXML) : WidgetMenuCollection(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~WidgetMainMenu() {
        ofRemoveListener(omniMenu->cellSelected, this,  &WidgetMainMenu::onOmniMenuCellCelected);
        ofRemoveListener(notificationMenu->notificationItemsChanged, this,  &WidgetMainMenu::onNotificationItemsChanged);  
    }
    
    void clearExistingWidgets() {
        Aquamarine::WidgetManager::removeAllWidgetsExcept(this);
    }
    
    Widget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::IconCache::IconTag::WIDGET_SETTINGS:
                return fileMenu;
            default:
                return nullptr;
        }
    }
    
    void newProject() {

        string classType = APP_CONSTANTS::WIDGET_CLASS_GET_STARTED;
        string widgetPersistentId = "GET_STARTED";

        WidgetGetStarted* w = dynamic_cast<WidgetGetStarted*>(Aquamarine::WidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/getStarted.xml"));

        w->setGetStartedCallback([w, this](string XML) {
            cout << XML;
            
            Aquamarine::WidgetManager::removeAllWidgetsExceptMultiple({this, w});
            Aquamarine::WidgetManager::initWidgetManager(
                Aquamarine::App::APPLICATION_NAME(),
                Aquamarine::App::APPLICATION_VERSION(),
                Aquamarine::App::DOCUMENT_FILE_EXTENSION(),
                true
            );

            ofxXmlSettings mWidgetXML = ofxXmlSettings();
            

            if (mWidgetXML.loadFromBuffer(XML.c_str())) {

            string type = mWidgetXML.getAttribute("new", "type", "");
            string value = mWidgetXML.getAttribute("new", "value", "");
            if (type == "file") {
                string filePath = ofToDataPath(value, true);
                if (Aquamarine::WidgetManager::load(filePath, true, w)) {

                    for(Widget &widget:Aquamarine::WidgetManager::getWidgets()) {
                        // do things here
                        
                    }
                    Aquamarine::WidgetManager::setProjectProperties("Untitled Project", "untitled.jam");                

                }
                
            }

// content ideas -- triads (3x inversions - see book)
            }
        });
        Aquamarine::WidgetManager::showModal(w, true);  
    }
                                                                      
    void saveProject(bool saveAs) {
        Aquamarine::WidgetManager::ProjectProperties existingProject = Aquamarine::WidgetManager::getCurrentProjectProperties();
        string proposedFileName = "";
        string currFileName = Aquamarine::WidgetManager::getCurrentProjectProperties().fileName;
        
        if (saveAs || currFileName == "untitled.jam") {

            string classType = Aquamarine::WidgetManager::WIDGET_CLASS_FILE_SAVE;
            string widgetPersistentId = Aquamarine::WidgetManager::getSuggestedNewWidgetPersistentId(classType);

            Aquamarine::WidgetFileSave* w = dynamic_cast<Aquamarine::WidgetFileSave*>(Aquamarine::WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                <widget>
                <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
                </widget>
                )"));

            w->setProposedFileName(currFileName);

            w->setSavePathSelectedCallback([&, w](string filePath) {
  
                filePath = Aquamarine::Shared::removeFileExtension(filePath);
                filePath += ".jam";

                if (Aquamarine::WidgetManager::save(filePath)) {
                    // Success...
                }
            });

            string recentDir = Aquamarine::WidgetFileLocationsList::getMostRecentDirectory();
            
            w->setPath(recentDir);
            Aquamarine::WidgetManager::showModal(w, true);     

            //ofFileDialogResult r = ofSystemSaveDialog(existingProject.fileName, "Save Project (.jam file)");
            //RegularExpression rex(".*.[jam|JAM]");
            
        } else {
            proposedFileName = Aquamarine::WidgetManager::getCurrentProjectProperties().absolutePath;
        }
        
        if (proposedFileName != "") {
            if (Aquamarine::WidgetManager::save(proposedFileName)) {
                    // Success...
            }
        }
    }

                                                     
    void loadProject() {
        string classType = Aquamarine::WidgetManager::WIDGET_CLASS_FILE_LOAD;
        string widgetPersistentId = Aquamarine::WidgetManager::getSuggestedNewWidgetPersistentId(classType);

        Aquamarine::WidgetFileLoad* w = dynamic_cast<Aquamarine::WidgetFileLoad*>(Aquamarine::WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds widthExpr="${WINDOW.WIDTH}/2" heightExpr="${WINDOW.HEIGHT}/2" minWidth="75" minHeight="75"  />
            </widget>
            )"));

        w->setPathSelectedCallback([w](string filePath) {
            Aquamarine::WidgetManager::load(filePath, true, w);
        });


        string recentDir = Aquamarine::WidgetFileLocationsList::getMostRecentDirectory();
        w->setPath(recentDir);
        Aquamarine::WidgetManager::showModal(w, true);     
    }    

    void licence() {
        string classType = APP_CONSTANTS::WIDGET_CLASS_LICENCE;
        string widgetPersistentId = "LICENCE";

        WidgetLicence* w = dynamic_cast<WidgetLicence*>(
            Aquamarine::WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="300" height="450" minWidth="75" minHeight="75"  />
            </widget>
        )"));

        Aquamarine::WidgetManager::addWidget(*w, true);
        w->setWidgetSize(600, 500, false);

      //  Aquamarine::WidgetManager::showModal(w, true);     


                                                                  
        w->popoutFrom(200, 300, PopoutDirection::RIGHT);

        w->setIsResizable(true);
                                                                  
    }

    void settings() {
        string classType = Aquamarine::WidgetManager::WIDGET_CLASS_SETTINGS;
        string widgetPersistentId = "APP_SETTINGS";
        Aquamarine::WidgetSettings* w = dynamic_cast<Aquamarine::WidgetSettings*>(Aquamarine::WidgetManager::loadWidget(classType, widgetPersistentId, R"(
            <widget>
            <bounds width="150" height="150" minWidth="75" minHeight="75"  />
            </widget>
            )"));
    
        Aquamarine::WidgetManager::addWidget(*w, false);  
        Aquamarine::WidgetManager::centerWidget(w);                                                     
    }

    void tutorials() {
        // Coming soon....
    }

    void about(int displayType) {
        string classType = APP_CONSTANTS::WIDGET_CLASS_ABOUT;
        string widgetPersistentId = "APP_ABOUT";        
        WidgetAbout* w = dynamic_cast<WidgetAbout*>(Aquamarine::WidgetManager::loadWidgetFromFile(classType, widgetPersistentId, "ui/widgets/about.xml"));
        w->setTitleStyle(Widget::TitleStyle::TOP_STATIC);
        w->setWidgetSize(600, 600, false);
        w->setTheme(getViz()->getThemeManager()->getSystemThemeDark(true));

        switch(displayType) {
            case 1: { // Regular
                Aquamarine::WidgetManager::addWidget(*w, false); 
                w->setIsVisible(true);  
                w->setWidgetSize(600, 500, false);   
                 w->setWidgetPosition(300, 300, false);                                                         
                break;
            }

            case 2: { // Popout
                Aquamarine::WidgetManager::addWidget(*w, false); 
                w->setWidgetSize(600, 500, false);                                             
                w->popoutFrom(200, 300, PopoutDirection::RIGHT);
                w->setIsResizable(true);                
                break;
            }

            case 3: { // Modal
                Aquamarine::WidgetManager::showModal(w, true); 
                break;
            }                        

            
        }



    }
    
    virtual void onMenuItemSelected(Aquamarine::WidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_FILE) {
            switch(args.activeMenuTabId) {
                case Aquamarine::IconCache::IconTag::WIDGET_SETTINGS:
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
                case Aquamarine::IconCache::IconTag::BOOK_CONTENT:
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
            Aquamarine::WidgetManager::drawDebugInfo(true); 
        }

    }


    virtual void onMenuItemUnselected(Aquamarine::WidgetMenuCollectionArgs & args) override {
        if (args.menuTag == MENU_DEBUG) {
            Aquamarine::WidgetManager::drawDebugInfo(false); 
        }
    }    

    // enter licence key, about this app - loses ...
    void onOmniMenuCellCelected(Aquamarine::WidgetTableArgs &args) {
        clearSelectedSlice();
        args.sender.clearSelectedRows();
        args.sender.setIsVisible(false);
    }    

    void onNotificationItemsChanged(Aquamarine::WidgetEventArgs &args) {
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
    }

	virtual void onWidgetOwnedWidgetClosed(Aquamarine::WidgetBase* closedWidget) override {
        clearSelectedSlice();
        if (notificationMenu) setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());
	}     

private:
    Aquamarine::WidgetMenu *fileMenu = nullptr;
    WidgetOmniMenuLinks *omniMenu = nullptr;
    Aquamarine::WidgetMenu *helpMenu = nullptr;    
    WidgetLicence *licenceMenu = nullptr;
    WidgetNotifications* notificationMenu = nullptr;
    WidgetOmniMenu *omniMenuMenuItem = nullptr;
    Aquamarine::Icon mainMenuIcon = Aquamarine::Icon("", Aquamarine::Coord::vizBounds(0,0,0,0), 1.0f, Aquamarine::Icon::IconSize::REGULAR, ofColor::white, 0);;

    const string MENU_FILE = "FILE";
    const string MENU_ADD = "ADD";
    const string MENU_HELP = "HELP";    
    const string MENU_NOTIFICATION = "NOTIFICATION";
    const string MENU_DEBUG = "DEBUG";
    
    bool loaded = false;
    Aquamarine::WidgetTheme theme;

    void overrideAlpha() {
        getTheme().UnhoveredWidgetAlpha = getTheme().HoveredWidgetAlpha;
    }

    virtual void onWidgetThemeChanged(Aquamarine::WidgetEventArgs args) override {
        Aquamarine::WidgetMenuCollection::onWidgetThemeChanged(args);
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
            fileMenu = new Aquamarine::WidgetMenu(getWidgetId() + "_MAIN_MENU_FILE", "<widget></widget>", getWidgetId()
                , Aquamarine::WidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab("File", Aquamarine::IconCache::getIcon("MED_CONTENT_SETTINGS"),
                    Aquamarine::IconCache::IconTag::WIDGET_SETTINGS, {
                        Aquamarine::WidgetMenuItem("New", 0),
                        Aquamarine::WidgetMenuItem("Save", 1),
                        Aquamarine::WidgetMenuItem("Save as...", 2),
                        Aquamarine::WidgetMenuItem("Load...", 3),
                        Aquamarine::WidgetMenuItem("Settings...", 4),
                        Aquamarine::WidgetMenuItem("Exit", -1000)
                    })
                });

            fileMenu->setTheme(theme);

            omniMenu = new WidgetOmniMenuLinks(getWidgetId() + "_MAIN_MENU_OMNI", "<widget><bounds width=\"460\" height=\"300\"/></widget>");
            ofAddListener(omniMenu->cellSelected, this,  &WidgetMainMenu::onOmniMenuCellCelected);
            omniMenu->setTheme(theme);
            
            helpMenu = new Aquamarine::WidgetMenu(getWidgetId() + "_MAIN_MENU_HELP", "<widget></widget>", getWidgetId()
                , Aquamarine::WidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // File Menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab("File", Aquamarine::IconCache::getIcon("MED_CONTENT_SETTINGS"),
                    Aquamarine::IconCache::IconTag::BOOK_CONTENT, {
                        Aquamarine::WidgetMenuItem("Tutorials", 0),
                        Aquamarine::WidgetMenuItem("Enter Licence Key...", 1),                        
                        Aquamarine::WidgetMenuItem("About (reg)", 2),
                        Aquamarine::WidgetMenuItem("About (popout)", 3),
                        Aquamarine::WidgetMenuItem("About (modal)", 4)                                                
                    })
                });
            helpMenu->setTheme(theme);

            licenceMenu = new WidgetLicence(getWidgetId() + "_LICENCE", R"(
                <widget>
                <bounds width="300" height="300" minWidth="75" minHeight="75"  />
                </widget>
            )");
            licenceMenu->setTheme(theme);



            // Get news and software updates from website
            // There's a bug with autoResizeWidth=1 and popOut func. research 
            notificationMenu = new WidgetNotifications(getWidgetId() + "_NOTIFICATION", R"(
                <widget>
                    <bounds height="200" width="550" minWidth="75" minHeight="75"  />
                    <properties autoResizeHeight="0" autoResizeWidth="0" showColumnFilters="0"/>
                </widget>
            )");
            ofAddListener(notificationMenu->notificationItemsChanged, this,  &WidgetMainMenu::onNotificationItemsChanged);  
            notificationMenu->setTheme(theme);

            /* Let the fun begin... */
            setMenuCollection({
                Aquamarine::WidgetMenuCollectionItem(MENU_FILE, fileMenu, "File"),
                Aquamarine::WidgetMenuCollectionItem(MENU_ADD, omniMenu, "Add...", Aquamarine::IconCache::getIcon("MED_ADD_CIRCLE"),
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::LEFT, VerticalAlign::CENTER)),
                Aquamarine::WidgetMenuCollectionItem(MENU_HELP, helpMenu, "Help"),                    
                Aquamarine::WidgetMenuCollectionItem(MENU_ADD, licenceMenu, Aquamarine::IconCache::getIcon("REG_USER"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),
                Aquamarine::WidgetMenuCollectionItem(MENU_NOTIFICATION, notificationMenu, Aquamarine::IconCache::getIcon("REG_DOT"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20))),                    
                Aquamarine::WidgetMenuCollectionItem(MENU_DEBUG, nullptr, Aquamarine::IconCache::getIcon("REG_BUG"), 
                    DisplayOptions(DisplayType::POPOUT, HorizontalAlign::RIGHT, VerticalAlign::CENTER, NonScaledPadding(0, 20, 0, 20)))
            });

            setMenuItem_RequiresAttention(MENU_NOTIFICATION, notificationMenu->getNewItemsFound());

            bool loadedLastProj = false;
            if (getViz()->getAutoLoadMostRecentProject()) {
                string mostRecentProject = Aquamarine::WidgetFileLocationsList::getMostRecentProject();
                if (mostRecentProject != "") { 
                    loadedLastProj = Aquamarine::WidgetManager::load(mostRecentProject, true, this);

                }
            }

            if (!loadedLastProj) {
                newProject();
            }

            loaded = true;
        }


    }
};


