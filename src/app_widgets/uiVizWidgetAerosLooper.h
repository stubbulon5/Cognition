//
//  uiVizWidgetAerosLooper.h
//
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "uiVizWidgetMenuCollection.h"
#include "uiVizWidgetDialog.h"
#include "uiVizWidgetAerosLooperSong.h"


class uiVizWidgetAerosLooper : public uiVizWidget {
    
public:
    
    uiVizWidgetAerosLooper(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidget::loadState(widgetXML);

        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }   

    virtual void onChildWidgetsLoaded() override {

        if (!hookedEvents) {
            TOOL_TABS = dynamic_cast<uiVizWidgetMenuCollection*>(getChildWidgetByPersistentId("TOOL_TABS"));
            ofAddListener(TOOL_TABS->menuItemSelected, this, &uiVizWidgetAerosLooper::onToolTabsMenuItemSelected);


            IMG_SD_CARD = getImage("IMG_SD_CARD");
            BTN_SD_CARD = getButton("BTN_SD_CARD");
            BC_SD_CARD = getBreadcrumb("BC_SD_CARD");
            IMG_LOGO = getImage("IMG_LOGO");

            BTN_SD_CARD->setPopoutWidgetIgnoreTheme(AEROS_SD_CARD_LOCATIONS, PopoutDirection::DOWN);

            BTN_SAVE_SONG = getButton("BTN_SAVE_SONG");

            AEROS_SD_SONG_LIST = dynamic_cast<uiVizWidgetFileList*>(getChildWidgetByPersistentId("AEROS_SD_SONG_LIST"));
            AEROS_SD_SONG_LIST->clearTableRows(); // want it to be empty initially



            SONG_INFO_TEXT_HOLDER = TOOL_TABS->getWidgetForTag("songInfo");        
            TXT_SONG_INFO = SONG_INFO_TEXT_HOLDER->getTextarea("TXT_SONG_INFO");        
            BTN_EDIT_SONG = SONG_INFO_TEXT_HOLDER->getButton("BTN_EDIT_SONG");

          

            TABLE_PARTS = dynamic_cast<uiVizWidgetTable*>(TOOL_TABS->getWidgetForTag("PARTS"));

            if(TABLE_PARTS) {

                TABLE_PARTS->setSelectionMode(uiVizWidgetTable::SelectionMode::CELL);

                TABLE_PARTS->setFunction_DrawCellHighlight_Hover([this](bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, uiVizWidgetTableRow& row, uiVizWidgetTableCell& cell, int rowIndex, int colIndex) {
                    // TABLE_PARTS->drawCellHighlight_Hover(isRowSelected, isRowHovered, absoluteScaledX, absoluteScaledY, scaledWidth, scaledHeight, row, cell, rowIndex, colIndex);                    
                });

                TABLE_PARTS->setFunction_DrawRowHighlight_Hover([this](bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, uiVizWidgetTableRow& row, int rowIndex) {
                    return;
                });

                TABLE_PARTS->setFunction_DrawCellHighlight_Selected([this](bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, uiVizWidgetTableRow& row, uiVizWidgetTableCell& cell, int rowIndex, int colIndex) {
                   // if (colIndex > 0) TABLE_PARTS->drawCellHighlight_Selected(isRowSelected, isRowHovered, absoluteScaledX, absoluteScaledY, scaledWidth, scaledHeight, row, cell, rowIndex, colIndex);
                });

                TABLE_PARTS->setFunction_DrawRowHighlight_Selected([this](bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, uiVizWidgetTableRow& row, int rowIndex) {
                    return;
                });

                TABLE_PARTS->setFunction_DrawCellContent([this](bool isRowSelected, bool isRowHovered, bool isCellHovered, int absoluteScaledX, int absoluteScaledY, int absoluteScaledLabelX, int absoluteScaledLabelY, int scaledWidth, int scaledHeight, uiVizWidgetTableRow& row, uiVizWidgetTableCell& cell, int rowIndex, int colIndex) {
                    

                    if (colIndex > 0 && isCellHovered) {
                        addIcon.setScaledPos(
                            absoluteScaledX + ((scaledWidth/2 - addIcon.getScaledBounds().width)), 
                            absoluteScaledY + ((scaledHeight - addIcon.getScaledBounds().height)/2)
                        );
                        addIcon.draw();
                    } else {
                        TABLE_PARTS->drawCellContent(isRowSelected, isRowHovered, isCellHovered, absoluteScaledX, absoluteScaledY, absoluteScaledLabelX, absoluteScaledLabelY, scaledWidth, scaledHeight, row, cell, rowIndex, colIndex);                        
                    }

                });
            }

            BTN_EDIT_SONG->setPopoutWidgetIgnoreTheme(AEROS_SONG, PopoutDirection::LEFT);  

                

            hookedEvents = true;

            // While testing....
               
        }  

    }  

    virtual ~uiVizWidgetAerosLooper() {
       ofRemoveListener(TOOL_TABS->menuItemSelected, this, &uiVizWidgetAerosLooper::onToolTabsMenuItemSelected);      
       ofRemoveListener(AEROS_SD_CARD_LOCATIONS->widgetEventReceived, this, &uiVizWidgetAerosLooper::onSDCardLocationsEventReceived);            
    }
    
    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
        string parentWidgetId = args.sender.getParentPersistentId();
        string event = args.getFullEventName();

        cout << event;

        if (args.sender.matchesWidget(BTN_SD_CARD)) {
            AEROS_SD_CARD_LOCATIONS->populateLocations();

        } else if (args.sender.matchesWidget(AEROS_SD_CARD_LOCATIONS)) {

            //loadedSong = loadSong(string songsFolder, string songTitle);
            //initializeUIWithSong(loadedSong);

        } else if (args.sender.matchesWidget(AEROS_SD_SONG_LIST) && args.eventName == WIDGET_EVENT::TABLE_CELL_CLICKED) {

            uiVizWidgetTableRow* eventRow = AEROS_SD_SONG_LIST->getTableRow(args.eventXML);
            uiVizWidgetTableCell* eventCell = AEROS_SD_SONG_LIST->getTableCell( args.eventXML);

            string songProjectFolder = eventRow->cells[1].key;

            if (songProjectFolder == "#%&NEW_SONG") {
                // New song
                //AEROS_SONG->setMode("NEW_SONG")
                
                AEROS_SONG->initializeWithEmptySong();
                AEROS_SONG->popoutFrom(AEROS_SD_SONG_LIST, PopoutDirection::LEFT, true);
                
            } else {
                // Existing song
                if(loadSong(getSongsPath(), songProjectFolder)) {
                    initializeUIWithSong(loadedSong);
                    TOOL_TABS->setSelectedTag("songInfo", false);
                } else {
                    AEROS_DIALOG->showDialog(
                        "Error loading song!",
                        "<xlarge><br/>There was a problem loading song '"+eventRow->key+"' inside "+getSongsPath()+"</xlarge>", 
                        true,
                        "Ok", 
                        "BTN_OK",
                        [&, this](uiVizWidgetEventArgs args) {}          
                    );
                }
            }



                        
        } else if (args.sender.matchesWidget(BTN_SAVE_SONG)) {
            // Save it!!
            saveSong(loadedSong);
             
        } else if (args.sender.matchesWidget(TABLE_PARTS)) {

            uiVizWidgetTableRow* eventRow = TABLE_PARTS->getTableRow(args.eventXML);
            uiVizWidgetTableCell* eventCell = TABLE_PARTS->getTableCell( args.eventXML);

            int rowIndex = args.eventXML.getAttribute("event", "rowIndex", 0);
            int colIndex = args.eventXML.getAttribute("event", "colIndex", 0) - 1; // we disregard the 1st col ...


            // todo - remove LOAD FULL WAV 
            // add file explore
            // add prefix that file is fresh
            if (args.eventName == WIDGET_EVENT::TABLE_CELL_CLICKED) {

                FILE_EXPLORER->popoutFrom(
                    deScale((addIcon.getScaledBounds().x + addIcon.getScaledBounds().width/2)) - TABLE_PARTS->getScrollOffsetX(), 
                    deScale((addIcon.getScaledBounds().y - addIcon.getScaledBounds().height/2)) + TABLE_PARTS->getScrollOffsetY(), 
                    PopoutDirection::UP
                );

                FILE_EXPLORER->setPathSelectedCallback([this, rowIndex, colIndex](string filePath) {
                    cout << "Result was: " << filePath << " to cell ["<< colIndex << "," << rowIndex <<  "]";
                    uiVizWidgetAerosLooperSong::assignAudioFileAbsolutePathToTrackPart(loadedSong, filePath, colIndex, rowIndex);


                    // todo in assignAudioFileAbsolutePathToTrackPart set ticks, etc
                    
                    // then update save method, then READY FOR TESTING!!
                    // update ticks to '0' when clearing....

                    this->initializeUIWithSong(loadedSong);
                    BTN_SAVE_SONG->setIsVisible(true);
                    FILE_EXPLORER->closeThisWidget();
                });

                FILE_EXPLORER->setWidgetClosedCallback([this, rowIndex, colIndex](uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, string result) {
                    cout << "Result was: " << result;
                    if(result == "CANCELLED") {
                        uiVizWidgetAerosLooperSong::assignAudioFileAbsolutePathToTrackPart(loadedSong, "", colIndex, rowIndex);
                        this->initializeUIWithSong(loadedSong);
                        BTN_SAVE_SONG->setIsVisible(true);
                    } 
                });

                setNeedsUpdate(true);

            }
                        
             
        }



    }

    void onSDCardLocationsEventReceived(uiVizWidgetEventArgs &args)  {

        if (args.eventName == WIDGET_EVENT::TABLE_CELL_CLICKED) {
    
            uiVizWidgetTableRow* eventRow = AEROS_SD_CARD_LOCATIONS->getTableRow(args.eventXML);
            uiVizWidgetTableCell* eventCell = AEROS_SD_CARD_LOCATIONS->getTableCell( args.eventXML);

            string selectedRootPath = eventRow->key;
            string selectedRootTitle = eventCell->label;

/*
            1/no songs folder found. Create on in UNTITLED?
            2/<create new song> (top item)
            3/store last location
*/

            AEROS_SD_CARD_LOCATIONS->setIsVisible(false);

            //uiVizWidgetManager::showModal(AEROS_DIALOG, true); 

            ofDirectory dir(ofFilePath::join(selectedRootPath, "songs"));
            if(!dir.exists()) {
                AEROS_DIALOG->showDialog(
                    "Create 'songs' folder? ",
                    "<xlarge><br/>No 'songs' folder found at this location. Create folder?</xlarge>", 
                    true,
                    "Yes|No", 
                    "BTN_YES|BTN_NO",
                    [&, this, selectedRootPath, selectedRootTitle](uiVizWidgetEventArgs args) {
                        cout << "Dialog button clicked: " + args.sender.getPersistentId();
                        if(args.sender.getPersistentId() == "BTN_YES") {
                            ofDirectory dir(ofFilePath::join(selectedRootPath, "songs"));
                            dir.create(true);
                            setSongsPath(ofFilePath::join(selectedRootPath, "songs"), selectedRootTitle);   
                            mSelectedRootTitle = selectedRootTitle;                         
                        }
                    }           
                );
            } else {
                mSelectedRootTitle = selectedRootTitle;
                setSongsPath(ofFilePath::join(selectedRootPath, "songs"), selectedRootTitle);
            }
        }

    }

    void setSongsPath(string path, string name) {
        songsPath = path;
        cout << "PATH SET: " <<  path;
        BC_SD_CARD->setBreadcrumbItemItems({uiVizWidgetElmBreadcrumbItem(name, name), uiVizWidgetElmBreadcrumbItem("songs", "songs")});
        AEROS_SD_CARD_LOCATIONS->setPath(path, false);
        AEROS_SD_SONG_LIST->setPath(path);
        // Make the button brighter ...
        //= ofColor(0, 0, 0, 0);


        // BTN_SD_CARD->getTheme().ElementBackgroundColor = 
        //     BTN_SD_CARD->getTheme().ElementBackgroundColor_withAlpha(BTN_SD_CARD->getCurrentBackgroundAlpha());
        
        AEROS_SD_SONG_LIST->addCustomFileRow("FILE", "#%&NEW_SONG", "<NEW SONG>", 0, "#%&NEW_SONG");
    }

    string getSongsPath() {
       return songsPath; 
    }

    virtual void onToolTabsMenuItemSelected(uiVizWidgetMenuCollectionArgs &args) {
        cout << args.activeMenuTabId;

    }    

    void draw(uiVizWidgetContext context) override {
        
        // if (mCurrentSDCardAlphaIncreasing) {
        //     mCurrentSDCardAlpha = scaleAnimation(getWidgetId() + "_sd_card_in", mCurrentSDCardAlpha, 1.0f, 3.0f);
        // } else {
        //     mCurrentSDCardAlpha = scaleAnimation(getWidgetId() + "_sd_card_out", mCurrentSDCardAlpha, 0.0f, 3.0f);
        // }

        // mCurrentSDCardAlphaIncreasing = (mCurrentSDCardAlpha < 1.0f);

        // ofColor newColor(
        //     BTN_SD_CARD->getTheme().ElementBackgroundColor.r,
        //     BTN_SD_CARD->getTheme().ElementBackgroundColor.g,
        //     BTN_SD_CARD->getTheme().ElementBackgroundColor.b,
        //     255*mCurrentSDCardAlpha
        // );
        
        // BTN_SD_CARD->getTheme().ElementBackgroundColor = newColor;                

        // BTN_SD_CARD->setNeedsUpdate(true);

    }


    bool populateSongTable() {
    
        vector<uiVizWidgetTableRow> rows;

        // Header
        vector<uiVizWidgetTableCell> headerCells = vector<uiVizWidgetTableCell>({
                uiVizWidgetTableCell(
                    "TRACK",
                    "TRACK #",
                    95,
                    0
                )
            }
        ); 

        int tracks = 6;
        int parts = 6;

        if (loadedSong.mode_2x2_enabled()) {
            // 2z2
            tracks = 2;
            parts = 2;    
                    
        } else {
            // 6x6
            tracks = 6;
            parts = 6;            
        }

        
        string rowKey = "";

        if (TABLE_PARTS) {


            for (int t = 1; t <= tracks; t++) {


                vector<uiVizWidgetTableCell> cells = vector<uiVizWidgetTableCell>({
                        uiVizWidgetTableCell(
                            "TRACK_" + ofToString(t),
                            "TRACK " + ofToString(t)
                        ),
                    }
                );

                for (int p = 1; p <= parts; p++) {

                    const ::Singul::Part* part = (loadedSong.parts_size() >= p ? loadedSong.mutable_parts(p-1) : loadedSong.add_parts());
                    
                    
                    const ::Singul::Track* track = (part->tracks_size() >= t ? loadedSong.mutable_parts(p-1)->mutable_tracks(t-1) : loadedSong.mutable_parts(p-1)->add_tracks());

                    if (t == 1) {
                        headerCells.push_back(
                            uiVizWidgetTableCell(
                                "PART " + ofToString(p),
                                "PART " + ofToString(p)
                            )
                        );
                    }

                    rowKey = "P_" + ofToString(p) + "T_" + ofToString(t);

                    string label = (track->loop_a().filename() == "" ? "empty" : track->loop_a().filename());
                    ofStringReplace(label, "!|UPDATED|!", "");
                    if (label != "") label = ofFilePath::getFileName(label); // just extract the file name


                    cells.push_back(                            
                        uiVizWidgetTableCell(
                            "File",
                            label
                        )
                    );

                }

                rows.push_back(uiVizWidgetTableRow(rowKey, cells));                            
            }
            
            TABLE_PARTS->clearTableRows();
            TABLE_PARTS->setHeaderRow(uiVizWidgetTableRow("TRACK_KEY", headerCells));
            TABLE_PARTS->setTableRows(rows);
            TABLE_PARTS->setNeedsUpdate(true);  

        }

        return true;
    }

    void populateSongInfo() {
        string songLogInfo = "<xxlarge><br/>SONG: " + loadedSong.title() + "</xxlarge><large><br/>";
        songLogInfo += uiVizWidgetAerosLooperSong::getSongInfoLog(loadedSong);
        songLogInfo += uiVizWidgetAerosLooperSong::getTracksInfoLog("", loadedSong);
        songLogInfo += "</large><br/><br/>";

        TXT_SONG_INFO->setValue(songLogInfo);
        BTN_EDIT_SONG->setIsVisible(true);

        BTN_EDIT_SONG->setPopoutWidgetShownCallback([this]() {
            cout << "Loading song into form: " << this->getLoadedSong()->title();
            AEROS_SONG->populateWidgetFromSong(*this->getLoadedSong());
        });

        BTN_EDIT_SONG->setPopoutWidgetClosedCallback([this](uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, string result) {
            cout << "Result was: " << result;
            if(result == "SUCCESS") {
                Singul::Song song = AEROS_SONG->populateSongFromWidget();
                saveSong(song);
            } 

        });           

    }

    bool initializeUIWithSong(Singul::Song song) {
        loadedSong = song;
        populateSongInfo();
        populateSongTable();
        BTN_SAVE_SONG->setIsVisible(false);
        return true;
    }


    bool loadSong(string songsFolder, string songTitle) {
        loadedSong = uiVizWidgetAerosLooperSong::loadSong(songsFolder, songTitle);
        return true;
    }

    bool saveSong(Singul::Song &aerosSong) {
        uiVizWidgetAerosLooperSong::saveSong(this->getSongsPath(), aerosSong);
        initializeUIWithSong(aerosSong);
        setSongsPath(this->getSongsPath(), getSelectedRootTitle());
    }    

    Singul::Song* getLoadedSong() {
        return &loadedSong;
    }

    string getSelectedRootTitle() {
        return mSelectedRootTitle;
    }
    
private:
    uiVizWidgetMenuCollection* TOOL_TABS = nullptr;
    bool hookedEvents = false;
    float mCurrentSDCardAlpha = 0.0f;
    bool mCurrentSDCardAlphaIncreasing = true;

    uiVizWidgetElmImage* IMG_SD_CARD = nullptr;
    uiVizWidgetElmButton* BTN_SD_CARD = nullptr;
    uiVizWidgetFileLocationsList*  AEROS_SD_CARD_LOCATIONS = nullptr;
    uiVizWidgetFileList*  AEROS_SD_SONG_LIST = nullptr;
    uiVizWidgetElmButton* BTN_SAVE_SONG = nullptr;
    uiVizWidgetElmBreadcrumb* BC_SD_CARD = nullptr;
    uiVizWidgetDialog* AEROS_DIALOG = nullptr;
    uiVizWidgetElmImage* IMG_LOGO = nullptr;

    // Song info tab
    uiVizWidget* SONG_INFO_TEXT_HOLDER = nullptr;
    uiVizWidgetElmTextarea* TXT_SONG_INFO = nullptr;
    uiVizWidgetElmButton* BTN_EDIT_SONG = nullptr;

    //uiVizWidget* AEROS_SONG_ABOUT = nullptr;

    // Song details
    uiVizWidgetAerosLooperSong* AEROS_SONG = nullptr;
    Singul::Song loadedSong;
    string songsPath = "";
    string mSelectedRootTitle = "";

    uiVizWidgetFileLoad* FILE_EXPLORER = nullptr;

    uiVizWidgetTable* TABLE_PARTS = nullptr;

    uiVizIcon addIcon = uiVizIconCache::getIcon("MED_ADD_CIRCLE");

    void initWidget() override {
      
        if (!AEROS_SD_CARD_LOCATIONS) {
            AEROS_SD_CARD_LOCATIONS = new uiVizWidgetFileLocationsList(getPersistentId() + "_FILE_LOCATIONS", R"(
                <widget>
                    <bounds width="200" height="250" />
                </widget>
                )");

            uiVizWidgetManager::addWidgetForPopout(*AEROS_SD_CARD_LOCATIONS, getWidgetId(), true);
            AEROS_SD_CARD_LOCATIONS->setTheme(getViz()->getThemeManager()->getSystemThemeLight(true));            
            AEROS_SD_CARD_LOCATIONS->setRowBGColor(ofColor(0,0,0,0));
            AEROS_SD_CARD_LOCATIONS->setRowAltBGColor(ofColor(0,0,0,0));
            //AEROS_SD_CARD_LOCATIONS->setTitleStyle(TitleStyle::NONE);
            ofAddListener(AEROS_SD_CARD_LOCATIONS->widgetEventReceived, this, &uiVizWidgetAerosLooper::onSDCardLocationsEventReceived);

        } 

        if (!AEROS_DIALOG) {
           AEROS_DIALOG = new uiVizWidgetDialog("AEROS_DIALOG", R"(
                <widget>
                    <bounds width="500" height="300" />
                </widget>
                )");

             uiVizWidgetManager::addWidgetForPopout(*AEROS_DIALOG, getWidgetId(), true);

        }

        if (!AEROS_SONG) {
            AEROS_SONG = new uiVizWidgetAerosLooperSong("APP_AEROS_SONG", "");
            uiVizWidgetManager::loadWidgetFromFileToExisting("ui/widgets/uiVizWidgetAerosLooperSong.xml", *AEROS_SONG);
            AEROS_SONG->setTitleStyle(uiVizWidget::TitleStyle::TOP_STATIC);
            AEROS_SONG->setWidgetSize(500, 300, false);
            AEROS_SONG->setTheme(getViz()->getThemeManager()->getSystemThemeLight(true));
            AEROS_SONG->getTheme().UnhoveredWidgetAlpha = 0.95f;
            AEROS_SONG->getTheme().HoveredWidgetAlpha = 0.95f;
            uiVizWidgetManager::addWidgetForPopout(*AEROS_SONG, getWidgetId(), true);
        }

        if(!FILE_EXPLORER) {
            
            FILE_EXPLORER = new uiVizWidgetFileLoad("FILE_EXPLORER", R"(
                <widget>
                <bounds minWidth="75" minHeight="75"  />
                <properties/>
                </widget>
                )"
            );  

            uiVizWidgetManager::addWidgetForPopout(*FILE_EXPLORER, getWidgetId(), true);
            FILE_EXPLORER->setWidth(500);
            FILE_EXPLORER->setHeight(300);
            FILE_EXPLORER->setTheme(getViz()->getThemeManager()->getSystemThemeLight(true));
            FILE_EXPLORER->setFileExtensionFilter("|.wav|");
            
        }    



    }

    
};


