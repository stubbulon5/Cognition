#pragma once
#include "ofxAquamarine.h"



class WidgetOmniMenuLinks : public Aquamarine::WidgetTable {
    
public:

    WidgetOmniMenuLinks(string persistentId, string widgetXML) : WidgetTable(persistentId, widgetXML) {
        initWidget();
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU_LINKS, 0);
        return mWidgetXML;
    }    
    
    virtual ~WidgetOmniMenuLinks() {
    }

    void populateLinks() {
        std::vector<Aquamarine::WidgetTableRow> rows;

        // Header
        vector<Aquamarine::WidgetTableCell> headerCells = vector<Aquamarine::WidgetTableCell>(); 
        headerCells.push_back(
            Aquamarine::WidgetTableCell(
                "ICON",
                "", 
                ICON_WIDTH
            )
        );            

        map<string, string> popWidgets = 
            ((menuItemTypeTabs && menuItemTypeTabs->getSelectedTag() == "SEARCH") ? widgetsSearchResults : widgetsToCache);
        
        std::map<std::string, string>::iterator it = popWidgets.begin();
            
        while (it != popWidgets.end()) {
            string widgetClassTypeRaw = it->first;
            string widgetClassType = "";
            string widgetFilterType = "";
            
            vector<string> widgetData = ofSplitString(widgetClassTypeRaw, "|");
            widgetClassType = widgetData[0];
            if (widgetData.size() > 1) widgetFilterType = widgetData[1];            

            if (getLinksFilter() != "SEARCH") {
                // Filter by selected tab...
                if (widgetFilterType != getLinksFilter()) {
                    it++;
                    continue;
                }
            }

            Aquamarine::WidgetTableCell cell(
                widgetClassTypeRaw, 
                Aquamarine::WidgetManager::getWidgetPrettyName(widgetClassType), 
                "center"
            );

            // Widget specific logic
            if (getLinksFilter() != "SEARCH") {

                vector<string> widgetClassTypeVals = ofSplitString(widgetClassTypeRaw, "|");                
                if(widgetClassType == APP_CONSTANTS::WIDGET_CLASS_GUITAR || widgetClassType == APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR) {
                    if (widgetClassTypeVals.size() > 2) {
                        string numStrings  = widgetClassTypeVals[2];
                        cell.setMetadata("NUM_STRINGS", numStrings);
                        cell.label = Aquamarine::WidgetManager::getWidgetPrettyName(widgetClassType) + " ("+numStrings+")";
                    }
                } else if(widgetClassType == APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET) {
                    if (widgetClassTypeVals.size() > 2) {
                        string bucketOption  = widgetClassTypeVals[2];
                        cell.setMetadata("BUCKET_OPTION", bucketOption);

                        if (bucketOption == "STRINGED") {
                            cell.label = "Chord Diagrams";
                        }
                    }                    
                }           

            }

            if (it->second != "") {
                cell.setMetadata("DRAG_DATA", it->second);
                if (widgetClassType == APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER) {
                    vizScale scale = WidgetMusical::scaleFromDragData(it->second);
                    cell.label = scale.getKey().getNoteName() + " " + scale.getName();
                } else if (widgetClassType == APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER) {
                    vizChord chord = WidgetMusical::chordFromDragData(it->second);
                    cell.label = chord.getChordName();
                }
            }

            rows.push_back(Aquamarine::WidgetTableRow("", {cell}));            
            it++;
        }

        setHeaderRow(Aquamarine::WidgetTableRow("Icons", headerCells));
        rows.push_back(Aquamarine::WidgetTableRow("", headerCells)); 

        setTableRows(rows);
        wrapRows(ICON_WIDTH, ICON_HEIGHT);

        calculateTableBounds();
    }

    virtual void onWidgetResized(int width, int height) override {
        wrapRows(ICON_WIDTH, ICON_HEIGHT);
    }

    virtual void drawCellContent(bool isRowSelected, bool isRowHovered, bool isCellHovered, int absoluteScaledX, int absoluteScaledY, int absoluteScaledLabelX, int absoluteScaledLabelY, int scaledWidth, int scaledHeight, Aquamarine::WidgetTableRow& row, Aquamarine::WidgetTableCell& cell, int rowIndex, int colIndex) override {
        Aquamarine::Icon img = Aquamarine::IconCache::getIcon(cell.key);
        
        if (img.getTag() == Aquamarine::IconCache::IconTag::NOT_FOUND) {
                if (mImgCacheMap.find(cell.key) == mImgCacheMap.end()) {
                    Aquamarine::WidgetCacheData cacheData = cacheMusicalWidgetIcon(cell.key, cell.getMetadata("DRAG_DATA"), 600, 600, false);

                    img = Aquamarine::Icon(
                        cacheData.imagePath, 
                        Aquamarine::Coord::vizBounds(0, 0, 600, 600), 
                        1.0f, Aquamarine::Icon::IconSize::REGULAR , ofColor::white, -1
                    );
                    mImgCacheMap[cell.key] = img;
                } else {
                    img = mImgCacheMap.find(cell.key)->second;
                }
                img.setScaledBounds(absoluteScaledX+scale(25), absoluteScaledY, scaledWidth-scale(50), scaledHeight-scale(25));
                img.draw();
        } else {
            img.setScaledBounds(absoluteScaledX+scale(25), absoluteScaledY, scaledWidth-scale(50), scaledHeight-scale(25));
            img.draw();
        }
        
        ofPushStyle();
        ofSetColor(cell.cellSlice.isHovered() ? getCellLabelSelectedColor() : getCellLabelColor());
        Aquamarine::Coord::vizPoint p = getAlignmentPointForCellLabel(cell, absoluteScaledLabelX, absoluteScaledLabelY + scale(35), scaledWidth, scaledHeight);
        getFont()->draw(cell.label, p.x, p.y);
        ofPopStyle();
    }      

    void cacheWidgetIcons() {
        std::map<std::string, string>::iterator it = widgetsToCache.begin();
        while (it != widgetsToCache.end()) {
            string widgetClass = it->first;

            Widget* w = Aquamarine::WidgetManager::loadWidget(widgetClass, "WIDGET_ICON_CACHE", R"(
                <widget><bounds width="200" height="200" maxWidth="200" maxHeight="200"/>
                    <properties>
                        <musicData colorMode="KEYS" colorAlternateMode="NONE" labelMode="NONE" labelAlternateMode="NONE" noteMode="DEFAULT" labelShowOctave="0"/>
                    </properties>
                </widget>
            )");  
        
            Aquamarine::WidgetManager::addWidget(*w, false);
            string f = ofFilePath::join(Aquamarine::App::APPLICATION_CACHE_FOLDER(), widgetClass+".png");
            w->saveWidgetContentsToImageFile(f, Aquamarine::WidgetContext::THUMBNAIL);
            Aquamarine::WidgetManager::removeWidget(*w);
            it++;
        }
    }

    static string getMusicalWidgetIconFileName(string widgetClass, vizTheoryBase* theory, int width, int height) {
        string filename = "unknown";
        if (theory->isChordType()) {
            vizChord* chord = dynamic_cast<vizChord*>(theory);
            filename = vizTheory::extractFileSystemSafeName(chord->getChordName_UserDefined() != "" ? chord->getChordRoot() + "_" + chord->getChordName_UserDefined() : chord->getChordNameSimplified(false)) + "_chord";
        } else if (theory->isScaleType()) {
            vizScale* scale = dynamic_cast<vizScale*>(theory);
            filename = vizTheory::extractFileSystemSafeName(scale->getKey().getNoteName() + "_" + scale->getName()) + "_scale";
        } else if (theory->isNoteType()) {
            vizNote* note = dynamic_cast<vizNote*>(theory);
            filename = vizTheory::extractFileSystemSafeName(note->getNoteName()) + "_note";
        }
        return filename + "_" + ofToString(width) + "x" + ofToString(height) + ".png";
    }

    Aquamarine::WidgetCacheData cacheMusicalWidgetIcon(string widgetClass, string dragData, int width, int height, bool forceCache) { 
        Aquamarine::WidgetCacheData cacheData;
        widgetClass = ofSplitString(widgetClass, "|")[0];
        string theoryType = WidgetMusical::getTheoryTypeForDragData(dragData);                
        string fileName;
        if (theoryType == "chord") {
            vizChord chord =  WidgetMusical::chordFromDragData(dragData);
            fileName = getMusicalWidgetIconFileName(widgetClass, &chord, width, height);
        } else if (theoryType == "scale") {
            vizScale scale =  WidgetMusical::scaleFromDragData(dragData);
            fileName = getMusicalWidgetIconFileName(widgetClass, &scale, width, height);
        } else if (theoryType == "note") {
            vizNote note =  WidgetMusical::noteFromDragData(dragData);
            fileName = getMusicalWidgetIconFileName(widgetClass, &note, width, height);
        } else {
            fileName = widgetClass + "_" + ofToString(width) + "x" + ofToString(height) + ".png";
        }
        
        string p = ofFilePath::join(Aquamarine::App::APPLICATION_CACHE_FOLDER(), fileName);
        if (!forceCache && ofFile::doesFileExist(p, false)) {
            //cout <<ofToDataPath(p, true); 
            cacheData = Aquamarine::WidgetCacheData(p, widgetClass, Aquamarine::WidgetManager::getWidgetPrettyName(widgetClass));
            return cacheData;
        }

        Widget* w = Aquamarine::WidgetManager::loadWidget(widgetClass, "MUSICAL_WIDGET_ICON_CACHE", R"(
            <widget>
                <properties>
                    <musicData colorMode="KEYS" colorAlternateMode="NONE" labelMode="NONE" labelAlternateMode="NONE" noteMode="DEFAULT" labelShowOctave="0"/>
                </properties>
            </widget>
        )");

        w->setX(width*-1);
        w->setY(height*-1);
        w->setWidgetSize(width, height, false);
        Aquamarine::WidgetManager::addWidget(*w, false);


        if (dynamic_cast<WidgetMusical*>(w)) {
            WidgetMusical::populateTargetMusicalWidget(dynamic_cast<WidgetMusical*>(w), dragData);
        }

        string f = ofToDataPath(p, true);
        w->saveWidgetContentsToImageFile(f, Aquamarine::WidgetContext::THUMBNAIL);
        cacheData = Aquamarine::WidgetCacheData(f, widgetClass, w->getWidgetPrettyName());
        Aquamarine::WidgetManager::removeWidget(*w);
        return cacheData;
    }    


   virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        if (args.sender.getPersistentId() == getPersistentId() && args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_CLICKED) {
            Aquamarine::WidgetTableRow* eventRow = getTableRow(args.eventXML);
            Aquamarine::WidgetTableCell* eventCell = getTableCell(args.eventXML);
            if (eventCell) {
                string classType = ofSplitString(eventCell->key, "|")[0];
                string widgetPersistentId = Aquamarine::WidgetManager::getSuggestedNewWidgetPersistentId(classType);
                
                Widget* w = Aquamarine::WidgetManager::loadWidget(classType, widgetPersistentId, R"(
                    <widget>
                    <bounds width="250" height="250" minWidth="75" minHeight="75"  />
                    </widget>
                    )");

                if (classType == APP_CONSTANTS::WIDGET_CLASS_GUITAR || classType == APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR) {
                    WidgetStringedInstrument* g = dynamic_cast<WidgetStringedInstrument*>(w);
                    int numStrings  = ofToInt(eventCell->getMetadata("NUM_STRINGS"));
                    g->setNumStrings(numStrings);
                    if (CHK_INSTR_DIAGRAM_MODE && CHK_INSTR_DIAGRAM_MODE->getValue())  g->setIsChordDiagramMode(true);
                    if (CHK_INSTR_VERTICAL && CHK_INSTR_VERTICAL->getValue())  g->setTheoryVizOrientationMode(WidgetMusical::TheoryVizOrientationMode::VERTICAL);

                    if (!g->getIsChordDiagramMode()) {
                        switch (g->getTheoryVizOrientationMode()) {
                            case WidgetMusical::TheoryVizOrientationMode::HORIZONTAL: g->setWidth(450); break;
                            case WidgetMusical::TheoryVizOrientationMode::VERTICAL: g->setHeight(450); break;
                        }
                    }
                } else if(classType == APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET) {
                    WidgetChordBucket* b = dynamic_cast<WidgetChordBucket*>(w);
                    string bucketOption = eventCell->getMetadata("BUCKET_OPTION");
                    if (bucketOption == "ADVANCED") {
                        b->setShowTopMenu(true);
                        b->setSize(500, 400);
                    } else if (bucketOption == "STRINGED") {
                        b->setShowTopMenu(true);
                        b->setSize(500, 400);
                        b->setTheoryVizInstrumentChordViewMode(WidgetMusical::TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM);
                    }                              
                } else if (classType == Aquamarine::WidgetManager::WIDGET_CLASS_SOUND_PLAYER || classType == Aquamarine::WidgetManager::WIDGET_CLASS_VIDEO_PLAYER) {
                    
                    Aquamarine::WidgetMediaPlayerBase* player = dynamic_cast<Aquamarine::WidgetMediaPlayerBase*>(w);
                    if (player != nullptr) {
                        player->setDoesRespondToFileDrop(true);    
                    }

                } else if (classType == Aquamarine::WidgetManager::WIDGET_CLASS_IMAGE_VIEW) {
                    Aquamarine::WidgetImageView* img = dynamic_cast<Aquamarine::WidgetImageView*>(w);
                    if (img != nullptr) {
                        img->setDoesRespondToFileDrop(true);    
                    }                    
                } else if (classType == Aquamarine::WidgetManager::WIDGET_CLASS_TEXT_EDITOR) {
                   Aquamarine::WidgetTextEditor* txt = dynamic_cast<Aquamarine::WidgetTextEditor*>(w);
                    if (txt != nullptr) {
                        txt->setDoesRespondToFileDrop(true);    
                    }                    
                }



                Aquamarine::WidgetManager::addWidget(*w, true);

                // Populate it with drag data (if any)
                string dragData = eventCell->getMetadata("DRAG_DATA");

                WidgetMusical* musicalWidgetTarget = dynamic_cast<WidgetMusical*>(w);
                if (musicalWidgetTarget != nullptr) {
                    //musicalWidgetTarget->onWidgetMouseContentDragReleased(e, dragData);
                    WidgetMusical::populateTargetMusicalWidget(musicalWidgetTarget, dragData);
                } else {
                    ofMouseEventArgs e(ofMouseEventArgs::Type::Dragged, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);                    
                    w->onWidgetMouseContentDragReleased(e, dragData);
                }
                Aquamarine::WidgetManager::centerWidget(w);
            }
        } else if(omniSearchBox && args.sender.getPersistentId() == omniSearchBox->getPersistentId() && args.eventName == Aquamarine::WIDGET_EVENT::VALUE_CHANGED) {

            widgetsSearchResults = widgetsToCacheInitial;
            if (omniSearchBox->getValue() != "") {
                widgetsSearchResults.clear();

                string potentialKey = ofToUpper(vizTheory::extractRootFromMusicTheoryContext(omniSearchBox->getValue()));
                if (vizTheory::isValidKey(potentialKey)) {
                    string musicalContext = ofToUpper(vizTheory::extractRemainderFromMusicTheoryContext(potentialKey, omniSearchBox->getValue()));

                    ofStringReplace(musicalContext, " ", "");
                    if (musicalContext.length() > 0) {
                        vector<string> scaleResults = vizScale::searchScales(musicalContext, 2);

                        for (string scaleId:scaleResults) {
                            string scaleMapKey = APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER + "|" + potentialKey + "|" + scaleId;
                            widgetsSearchResults[scaleMapKey] = "<scale><key>" + potentialKey + "</key><name>" + scaleId + "</name></scale>";
                        }    


                        vector<string> chordResults = vizChord::searchChords(musicalContext, 2);

                        for (string chord:chordResults) {
                            string chordMapKey = APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER + "|" + potentialKey + "|" + chord;
                            widgetsSearchResults[chordMapKey] = "<chord><name>" + ofToUpper(potentialKey) + chord + "</name></chord>";
                        }  

                    }
                }

                string searchVal = ofToLower(omniSearchBox->getValue());
                for (auto it = widgetMap.begin(); it != widgetMap.end(); it++) {
                    string widgetClass = it->first;
                    string widgetName = widgetClass;
                    //ofStringReplace(widgetName, "Widget", "");
                    if (ofIsStringInString(ofToLower(widgetClass), searchVal) 
                        && widgetClass != Aquamarine::WidgetManager::WIDGET_CLASS_DEBUG
                        && widgetClass != APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU
                        && widgetClass != APP_CONSTANTS::WIDGET_CLASS_OMNI_MENU
                        && widgetClass != APP_CONSTANTS::WIDGET_CLASS_STRINGED_INSTRUMENT
                    ) { 
                        widgetsSearchResults[widgetClass] = "";
                    }
                }

            } else {
                widgetsToCache = widgetsToCacheInitial;
            }
            populateLinks();
        } else if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_HOVERED && args.sender.getPersistentId() == getPersistentId()) {
            Aquamarine::WidgetTableRow* eventRow = getTableRow(args.eventXML);
            Aquamarine::WidgetTableCell* eventCell = getTableCell( args.eventXML);
            if (eventCell) {
                setDragData(eventCell->getMetadata("DRAG_DATA"));
            }
        }
    }       

    virtual void setTheme(Aquamarine::WidgetTheme val) override {
        Aquamarine::WidgetTable::setTheme(val);
        setCellHoverColor(getTheme().WidgetAccentHighContrast1Color_withAlpha(getTheme().GenericSelectedAlpha));
    }    
    
private:
    Aquamarine::WidgetManager::widget_map_type widgetMap;
    vector<Aquamarine::WidgetTableRow> rows = vector<Aquamarine::WidgetTableRow>();
    Aquamarine::WidgetElmTextbox *omniSearchBox = nullptr;
    vector<string> searchHints = {"C Major", "Gb Minor", "D#m", "Ionian Scale", "Minor Scale"};   
    string omniSearchBoxId; 

    std::map<std::string, Aquamarine::Icon> mImgCacheMap;


    map<string, string> widgetsToCache;
    map<string, string> widgetsSearchResults;

    map<string, string> widgetsToCacheInitial = {
        {APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER+"|GENERAL", ""},            
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER+"|GENERAL", ""},
        {APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER+"|GENERAL", ""},
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL+"|GENERAL", ""},
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL_FOR_KEY+"|GENERAL", ""},
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION+"|GENERAL", ""},
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET+"|GENERAL", ""},
        // {APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET+"|GENERAL|ADVANCED", ""},
        {APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET+"|GENERAL|STRINGED", ""},
        // {APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER+"|GENERAL", ""},   
        {APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER+"|GENERAL", ""},        
                
        {APP_CONSTANTS::WIDGET_CLASS_GUITAR+"|INSTRUMENT"+"|6", ""},
        {APP_CONSTANTS::WIDGET_CLASS_GUITAR+"|INSTRUMENT"+"|7", ""},
        {APP_CONSTANTS::WIDGET_CLASS_GUITAR+"|INSTRUMENT"+"|8", ""},
        {APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR+"|INSTRUMENT"+"|4", ""},
        {APP_CONSTANTS::WIDGET_CLASS_BASS_GUITAR+"|INSTRUMENT"+"|5", ""} 
    };

    int ICON_WIDTH = 150;
    int ICON_HEIGHT = 100;

    Aquamarine::WidgetMenuCollection* menuItemTypeTabs = nullptr;  
    Aquamarine::WidgetElmCheckbox* CHK_INSTR_DIAGRAM_MODE = nullptr;  
    Aquamarine::WidgetElmCheckbox* CHK_INSTR_VERTICAL = nullptr;


    void calculateTableBounds() {
        int footerRowHeight = 0;
        if (menuItemTypeTabs) {
            if (CHK_INSTR_DIAGRAM_MODE) CHK_INSTR_DIAGRAM_MODE->setIsVisible(menuItemTypeTabs->getSelectedTag() == "INSTRUMENT");
            if (CHK_INSTR_VERTICAL != nullptr) CHK_INSTR_VERTICAL->setIsVisible(menuItemTypeTabs->getSelectedTag() == "INSTRUMENT");

            if (getLinksFilter() == "INSTRUMENT") {
                footerRowHeight = menuItemTypeTabs->getHeight() + CHK_INSTR_VERTICAL->getHeight();
            } 
            
        }

        if (omniSearchBox) {
            bool isSearch = (getLinksFilter() == "SEARCH");
            omniSearchBox->setIsFocused(isSearch);
            omniSearchBox->setIsVisible(isSearch);       
            if (isSearch) footerRowHeight = omniSearchBox->getHeight();
        }


        setFixedHeaderRowHeight(
            (menuItemTypeTabs && menuItemTypeTabs->getIsVisible()) ? menuItemTypeTabs->getHeight() + getNonScaledPadding() : 0
        );

        setFixedFooterRowHeight(footerRowHeight); // footerRowHeight

        
    }

    virtual void onMenuItemSelected(Aquamarine::WidgetMenuCollectionArgs & args) {   
        populateLinks(); 
        calculateTableBounds();
    }

    string getLinksFilter() {
        if (menuItemTypeTabs) {
            return menuItemTypeTabs->getSelectedTag();
        } else {
            return "GENERAL";
        }
    }


    virtual void drawCellHeaderRow(bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int absoluteScaledLabelX, int absoluteScaledLabelY, int scaledWidth, int scaledHeight, Aquamarine::WidgetTableRow& row, Aquamarine::WidgetTableCell& cell, int colIndex) override {
        // Draw nothing!
    }  

    virtual void drawCellFooterRow(bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, Aquamarine::WidgetTableRow& row, Aquamarine::WidgetTableCell& cell, int colIndex) {
        if (colIndex == 0) {
            
            Aquamarine::Elm vizElm_cell;
            vizElm_cell.setRectangle(
                absoluteScaledX,
                absoluteScaledY,
                scale(getWidth()),
                scale(getFixedFooterRowHeight()),
                getTheme().WidgetColor_withAlpha(getTheme().HoveredWidgetAlpha)
            );
            vizElm_cell.draw();


        }
    }      

// Add horizontal, Left, Diagram mode radio buttons to bottom of INSTRUMENTS tab ....

    virtual void onWidgetAddedAsChild(Aquamarine::WidgetEventArgs args) override {     
        populateLinks();
    }

    void initWidget() override {  

        widgetsToCache = widgetsToCacheInitial;
        widgetMap = Aquamarine::WidgetManager::getWidgetMap();

        populateLinks();

        omniSearchBoxId = getPersistentId() +  "_OMNI_SEARCH_BOX_TEXT";

        if (!omniSearchBox) {
            omniSearchBox = dynamic_cast<Aquamarine::WidgetElmTextbox*>(addOrLoadWidgetElement(omniSearchBox, Aquamarine::WIDGET_ELM_CLASS::TEXTBOX, omniSearchBoxId, R"(
                <element>
                </element>
                )"));

            omniSearchBox->setX_Expr("${PARENT.LEFT}");
            //omniSearchBox->setY_Expr("${PARENT.TOP_FIXED}");
            //omniSearchBox->setHeight()
            omniSearchBox->setWidth_Expr("${PARENT.USABLE_WIDTH}");
            omniSearchBox->setTitle("\"C Major\", \"Gb Minor\", \"Ionian Scale\", \"Minor Scale\"");
            omniSearchBox->setShouldPersist(false);
            //omniSearchBox->setIsFocused(true);

            omniSearchBox->setY_Expr("${PARENT.BOTTOM}"); 
            omniSearchBox->setIsVisible(false);


        }        


        if (!CHK_INSTR_DIAGRAM_MODE) {
            CHK_INSTR_DIAGRAM_MODE = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_INSTR_DIAGRAM_MODE, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, getWidgetId()+"_CHK_INSTR_DIAGRAM_MODE", R"(
                <element>
                <title>Diagram Mode</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_INSTR_DIAGRAM_MODE->setX_Expr("${PARENT.LEFT}");
            //CHK_INSTR_DIAGRAM_MODE->setY_Expr("${PARENT.BOTTOM}-${PADDING}-30"); 
            CHK_INSTR_DIAGRAM_MODE->setY_Expr("${PARENT.BOTTOM}-${SELF.HEIGHT}"); 
            CHK_INSTR_DIAGRAM_MODE->setShouldPersist(false);
            CHK_INSTR_DIAGRAM_MODE->setIsVisible(false);
            CHK_INSTR_DIAGRAM_MODE->setValue(true, false, false);
        }


        if (!CHK_INSTR_VERTICAL) {
            CHK_INSTR_VERTICAL = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_INSTR_VERTICAL, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, getWidgetId()+"_CHK_INSTR_VERTICAL", R"(
                <element>
                <title>Vertical Mode</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_INSTR_VERTICAL->setX_Expr("${PARENT.LEFT}");
            //CHK_INSTR_VERTICAL->setY_Expr("${PARENT.BOTTOM}-${PADDING}-30"); 
            CHK_INSTR_VERTICAL->setY_Expr("${"+getWidgetId()+"_CHK_INSTR_DIAGRAM_MODE.BOTTOM}"); 
            CHK_INSTR_VERTICAL->setShouldPersist(false);
            CHK_INSTR_VERTICAL->setIsVisible(false);
            CHK_INSTR_VERTICAL->setValue(true, false, false);
        }    

        // This should always come last ...
        if (!menuItemTypeTabs) {
            menuItemTypeTabs = new Aquamarine::WidgetMenuCollection("LINK_TYPE_TAGS", R"(
                <widget>
                    <bounds xExpr="${PARENT.ABSOLUTE_USABLE_X}" yExpr="${PARENT.ABSOLUTE_USABLE_Y}" widthExpr="${PARENT.USABLE_WIDTH}"  />
                    <properties menuType="TAB" />
                </widget>
                )");
            
                            
            menuItemTypeTabs->setIsRoundedRectangle(false);            
            menuItemTypeTabs->setMenuCollection( {
                Aquamarine::WidgetMenuCollectionItem("GENERAL", nullptr, "General", Aquamarine::IconCache::getIcon("REG_BUG")),         
                Aquamarine::WidgetMenuCollectionItem("INSTRUMENT", nullptr, "Instruments", Aquamarine::IconCache::getIcon("REG_BUG")),
                Aquamarine::WidgetMenuCollectionItem("SEARCH", nullptr, "Search...", Aquamarine::IconCache::getIcon("REG_BUG"))
            });
            addChildWidget(*menuItemTypeTabs, true); 
            ofAddListener(menuItemTypeTabs->menuItemSelected, this, &WidgetOmniMenuLinks::onMenuItemSelected);  

            //menuItemTypeTabs->setSelectedTag("INSTRUMENT", true);          
            // todo 1st tab color darker - fix height then searching
            // save / load dialog title "fixes it's colour after drag"
            // fix dark theme tab highlight!

        }

        populateLinks();



        // Uncomment the below line to cache the widgets to png files
        //cacheWidgetIcons();


       // cacheMusicalWidgetIcon("WidgetScalePicker", "<scale><key>A</key><name>phrygian</name></scale>", 200, 200, false);


       // cacheMusicalWidgetIcon("WidgetScalePicker", "<scale><key>C</key><name>ionian</name></scale>", 600, 600, false);
       // cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>G11</name></chord>", 600, 600, false);
       // cacheMusicalWidgetIcon("WidgetKeyPicker", "", 600, 600, false);


       // cacheMusicalWidgetIcon("WidgetScalePicker", "<scale><key>G#</key><name>locrian</name></scale>");
       // cacheMusicalWidgetIcon("WidgetScalePicker", "<scale><key>Gb</key><name>aeolian</name></scale>");
       // cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>Gm</name></chord>", 300, 300, false);
       // cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>Gsus</name></chord>", 300, 300, false);
       // 
       // cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>G13</name></chord>", 300, 300, false);
       // cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>Gsus4</name></chord>", 300, 300, false);
        //cacheMusicalWidgetIcon("WidgetChordDesigner", "<chord><name>Ggammy</name></chord>", 300, 300, false);

        
       // md5hash of the widgetdata for the filename



    }
};


