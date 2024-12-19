//
//  uiVizChordBucket_h
//  bloom-macos
//
//
#pragma once
#include "../uiViz/widget/uiVizWidgetMenu.h"
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetChordDesigner.h"
#include "uiVizWidgetGuitar.h"
#include "uiVizWidgetMenuCollection.h"
#include "uiVizWidgetKeyPickerPopout.h"

class uiVizNoteSlice
{
public:
    uiVizCoord::vizPoint labelPoint = uiVizCoord::vizPoint(0, 0);
    uiVizCoord::vizBounds bounds = uiVizCoord::vizBounds(0, 0, 0, 0);
    string label;
    uiVizElm path;

    /*
    ofColor regularColor;
    ofColor selectedColor;
    ofColor hoveredColor;
     */
    ofColor regularFontColor;
    /*
    ofColor selectedFontColor;
    ofColor hoveredFontColor;
     */

    ~uiVizNoteSlice()
    {
    }
};

class uiVizChordSlice
{
public:
    vizChord chord;
    uiVizCoord::vizPoint labelPoint = uiVizCoord::vizPoint(0, 0);
    uiVizCoord::vizBounds bounds = uiVizCoord::vizBounds(0, 0, 0, 0);
    ofRectangle chordFontRect;
    string label;
    uiVizElm path;

    ofFbo fbo;

    /*
     ofColor regularColor;
     ofColor selectedColor;
     ofColor hoveredColor;
     */
    ofColor regularFontColor;
    /*
     ofColor selectedFontColor;
     ofColor hoveredFontColor;
     */
    std::vector<uiVizNoteSlice> notes;

    std::vector<uiVizCoord::vizPoint> subLabelPoints;
    ofxFontStash2::Style chordFontStyle;
    ofxFontStash2::Style notesFontStyle;

    bool showChordName = true; // add a detail level property to uiVizWidgetMusical
    bool showNoteNames = true; // add a detail level property to uiVizWidgetMusical

    bool isHovered = false;
    bool isSelected = false;

    bool getIsMouseHovered()
    {
        return path.isHovered_Rect();
    }

    void drawToFbo(uiVizWidgetMusical::TheoryVizInstrumentChordViewMode mode, vizChord* chordRef) {
        //hord.getFbo().destroy();

        if (chordRef->getFboNeedsUpdate() ) { // || chordRef->getFbo().isAllocated == false

           // if (!chordRef->getFbo().isAllocated()) { -- optimization: only allocate if dimensions changed ....
                chordRef->getFbo().allocate(uiVizShared::getViz()->scale(path.getRectangle().width), uiVizShared::getViz()->scale(path.getRectangle().height),  GL_RGBA, 16); // GL_RGBA32F, 32);
           // }

            chordRef->getFbo().begin();
            ofPushMatrix();
            ofTranslate(-1*path.getRectangle().x, -1*path.getRectangle().y);                
            ofClear(0, 0, 0, 0);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            draw(false, mode);
            ofPopMatrix();
            chordRef->getFbo().end();

            chordRef->setFboNeedsUpdate(false); 


            //fix regular fbo drawing 
        }
    }

    void draw(bool shouldDrawFbo, uiVizWidgetMusical::TheoryVizInstrumentChordViewMode mode)
    {

        int chordNameHeight = 0;

        if (showChordName)
        {
            path.draw();
            chordNameHeight = chordFontRect.height;
            chordFontStyle.color = regularFontColor;
            uiVizShared::getViz()->getFonts()->draw(label, chordFontStyle, labelPoint.x, labelPoint.y);
        }

        int noteNamesHeight = 0;

        if (showNoteNames)
        {
            for (uiVizNoteSlice note : notes)
            {
                note.path.draw();
                notesFontStyle.color = note.regularFontColor;
                noteNamesHeight = note.path.getRectangle().height;
                uiVizShared::getViz()->getFonts()->draw(note.label, notesFontStyle, note.labelPoint.x, note.labelPoint.y);
            }
        }

        if (shouldDrawFbo)
        {
            switch (mode)
            {
                case uiVizWidgetMusical::TheoryVizInstrumentChordViewMode::UNSET:            
                    chord.getFbo().draw(
                        path.getRectangle().x,
                        path.getRectangle().y,
                        uiVizShared::getViz()->scale(path.getRectangle().width),
                        uiVizShared::getViz()->scale(path.getRectangle().height));                
                    break;

                case uiVizWidgetMusical::TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
                {
                    chord.getFbo().draw(
                        path.getRectangle().x,
                        path.getRectangle().y + noteNamesHeight + uiVizShared::getViz()->scale(2),
                        path.getRectangle().width,
                        path.getRectangle().height - noteNamesHeight - chordNameHeight - uiVizShared::getViz()->scale(2) * 2.0f);
                    break;
                }
            };            
        }

    }

    ~uiVizChordSlice()
    {
    }
};

class uiVizWidgetChordBucket : public uiVizWidgetMusical
{

public:
    uiVizWidgetChordBucket(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML)
    {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override
    {
        uiVizWidgetMusical::loadState(widgetXML);

        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str()))
        {
            return false;
        }

        setCorrectDiagramWidgets();
        setIsLefty(isLefty());
        setIsBlackAndWhiteMode(isBlackAndWhiteMode());

        widgetSettings.pushTag("widget");

        setShowTopMenu(widgetSettings.getAttribute("properties", "showTopMenu", getShowTopMenu(), false));
        setSidebarWidth(widgetSettings.getAttribute("properties", "sideBarWidth", getSidebarWidth(), 0)); 
        setIsSmallerDiagrams(widgetSettings.getAttribute("properties", "isSmallerDiagrams", getIsSmallerDiagrams(), false));

        widgetSettings.pushTag("properties");
        
        setTheoryVizLabelModeChordLabel(getTheoryVizLabelModeEnum(widgetSettings.getAttribute("musicData", "labelModeChord", getTheoryVizLabelModeString(getTheoryVizLabelModeChordLabel()))));        

        switch (getTheoryVizInstrumentChordViewMode())
        {
            case TheoryVizInstrumentChordViewMode::UNSET:
                break;

            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
            {
                if (stringedInstrument)
                {
                    stringedInstrument->setTheoryVizColorMode(getTheoryVizColorModeEnum(widgetSettings.getAttribute("musicData", "colorModeEmbedded", getTheoryVizColorModeString(stringedInstrument->getTheoryVizColorMode()), 0)));
                    stringedInstrument->setTheoryVizLabelMode(getTheoryVizLabelModeEnum(widgetSettings.getAttribute("musicData", "labelModeEmbedded", getTheoryVizLabelModeString(stringedInstrument->getTheoryVizLabelMode()), 0)));
                }
                break;
            }
        };

        widgetSettings.popTag();
        widgetSettings.popTag();

        return true;
    }

    virtual ofxXmlSettings saveState() override
    {
        ofxXmlSettings mWidgetXML = uiVizWidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET, 0);

        mWidgetXML.pushTag("widget");

        mWidgetXML.setAttribute("properties", "showTopMenu", getShowTopMenu(), 0);
        mWidgetXML.setAttribute("properties", "sideBarWidth", getSidebarWidth(), 0);    
        mWidgetXML.setAttribute("properties", "isSmallerDiagrams", getIsSmallerDiagrams(), 0);
        
        mWidgetXML.pushTag("properties");

        mWidgetXML.setAttribute("musicData", "labelModeChord",  getTheoryVizLabelModeString(getTheoryVizLabelModeChordLabel()), 0);        

        switch (getTheoryVizInstrumentChordViewMode())
        {
            case TheoryVizInstrumentChordViewMode::UNSET:
                break;

            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
            {
                if (stringedInstrument)
                {
                    mWidgetXML.setAttribute("musicData", "colorModeEmbedded", getTheoryVizColorModeString(stringedInstrument->getTheoryVizColorMode()), 0);
                    mWidgetXML.setAttribute("musicData", "labelModeEmbedded", getTheoryVizLabelModeString(stringedInstrument->getTheoryVizLabelMode()), 0);
                }
                break;
            }
        };

        mWidgetXML.popTag();
        mWidgetXML.popTag();

        return mWidgetXML;
    }

    virtual ~uiVizWidgetChordBucket()
    {
        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(chordBucketContextMenu);
        if (chordBucketContextMenu)
            ofRemoveListener(menu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);
        ofRemoveListener(chordDesignerMenuItem->userDefinedChordNameChanged, this, &uiVizWidgetChordBucket::onUserDefinedChordNameChanged);

        ofRemoveListener(chordDesignerMenuItemStringed->widgetEventReceived, this, &uiVizWidgetChordBucket::onChordDesignerMenuItemStringedEventReceived);

        if (topMenu)
            ofRemoveListener(topMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onTopMenuItemSelected);     

        if (scalePickerMenuItem) 
            ofRemoveListener(scalePickerMenuItem->noteSelected, this, &uiVizWidgetChordBucket::onScalePickerMenuNoteSelected);   

        uiVizWidgetMenu *menu2 = static_cast<uiVizWidgetMenu *>(chordBucketContextMenu2);
        if (menu2)
            ofRemoveListener(menu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);  

        if (chordRulesMenuItem)
            ofRemoveListener(chordRulesMenuItem->rulesChanged, this,  &uiVizWidgetChordBucket::onChordBucketRulesChanged);

        if (stringedBucketContextMenu)
            ofRemoveListener(stringedBucketContextMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);       

        if (chordBucketToolsMenu)
            ofRemoveListener(chordBucketToolsMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);                  


    }

    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
        // Caution - removing this empty override causes duplicate chord to be added!
        if (args.sender.matchesWidget(SLD_tempo)) { //  && args.eventName == WIDGET_EVENT::VALUE_CHANGED
            setPlayingTempoBPM(SLD_tempo->getValue());
            cout << "VALUE CHANGED : " << SLD_tempo->getValue();
        }
    }

    virtual void onChordDesignerMenuItemStringedEventReceived(uiVizWidgetEventArgs &args) {
        if (args.eventName == WIDGET_EVENT::DRAG_AND_DROP_DATA_SET && chordDesignerMenuItemStringed->getIsVisible()) {
            if (chordDesignerMenuItemStringed->getSelectedChords().size() > 0) {
                vizChord chord = chordDesignerMenuItemStringed->getSelectedChords()[0];
                setSelectedChordAtIndex(mContextMenuChordIndex, chord);
                setNeedsUpdate(true);
            }
        }

        chordDesignerMenuItemStringed->setDrawWidgetTitle(true);
        chordDesignerMenuItemStringed->setTitleStyle(TitleStyle::TOP_STATIC);
        chordDesignerMenuItemStringed->setTitle(chordDesignerMenuItemStringed->getCalculatedChordName());
    }    

    void onWidgetMouseContentDragged(ofMouseEventArgs &e) override
    {
        if (getDraggingChord().getChordName() != "")
        {
            setDragData(getDraggingChord().getXML());
        }
    }

    uiVizWidget *getPopoutWidgetForMenuTag(int menuTag) override
    {
        switch (menuTag)
        {
        case uiVizIconCache::IconTag::WIDGET_SETTINGS:
            return chordBucketContextMenu;
        default:
            return nullptr;
        }
    }

    virtual void onWidgetKeyPressed(ofKeyEventArgs &e) override {
        
        uiVizWidgetMusical::onWidgetKeyPressed(e);
        
        int key = e.key;
        
        switch (key) {
            case OF_KEY_BACKSPACE: removeSelectedChord(getHoveredChordIndex()); break; 
        }
        setNeedsUpdate(true);
    }

// todo:
// bucket only showing degrees now\!
// add scale and chord LIST
    void onWidgetMousePressed(ofMouseEventArgs &e) override
    {

        if (e.button == OF_MOUSE_BUTTON_RIGHT)
        {

            for (int i = 0; i < chordSlices.size(); i++)
            {
                uiVizChordSlice chordSlice = chordSlices[i];
                // chordSlice.draw();

                if (getIsActiveWidget() && !getIsDragging())
                {
                    if (chordSlice.getIsMouseHovered())
                    {
                        mContextMenuChordIndex = i;
                        chordDesignerMenuItem->addSelectedChord(chordSlice.chord, true, true);

                        if (chordDesignerMenuItemStringed && stringedInstrument) {
                            chordDesignerMenuItemStringed->setDrawWidgetTitle(true);
                            chordDesignerMenuItemStringed->setTitleStyle(TitleStyle::TOP_STATIC);
                                                        
                            chordDesignerMenuItemStringed->setStrings(stringedInstrument->getStringsFromRules(chordSlice.chord), false);
                            int chordDiagramNumFrets = chordSlice.chord.getInstrumentRule("stringed", "chordDiagramNumFrets", 5);
                            chordDesignerMenuItemStringed->setChordDiagramNumFrets(chordDiagramNumFrets);
                            chordDesignerMenuItemStringed->setInstrumentRules(chordSlice.chord.getInstrumentRules(), false);
                            chordDesignerMenuItemStringed->addSelectedChord(chordSlice.chord, false, true, false);

                            chordDesignerMenuItemStringed->setTitle(chordDesignerMenuItemStringed->getCalculatedChordName());
                            chordDesignerMenuItemStringed->updateWidget();

                        }

                        showContextMenu(uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX()) - 20, deScale(ofGetMouseY()) - 20);
                    }
                }
            }
        }
    }

    virtual void setTheoryVizInstrumentChordViewMode(TheoryVizInstrumentChordViewMode theoryVizInstrumentChordViewMode) override {
        uiVizWidgetMusical::setTheoryVizInstrumentChordViewMode(theoryVizInstrumentChordViewMode);
        if (topMenu) topMenu->setMenuItem_Visibility("GUITAR", theoryVizInstrumentChordViewMode == TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM);
    }     

    void forceGuitarDiagramRefresh()
    {
        for (int chordIndex = 0; chordIndex < getSelectedChords().size(); chordIndex++)
        {
            vizChord *chord = getSelectedChordByIndexRef(chordIndex);
            chord->setFboNeedsUpdate(true);
        }
        setNeedsUpdate(true);
    }

    virtual void onWidgetResizingByUserEnded(int width, int height) override
    {
        forceGuitarDiagramRefresh();
    }

    virtual void update(uiVizWidgetContext context) override
    {
        int cols = (getIsSmallerDiagrams() ? 5 : 3);

        switch (getTheoryVizInstrumentChordViewMode())
        {
            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
            {
                if (getUsableWidth() > 550)
                    cols++;
                if (getUsableWidth() > 650)
                    cols++;
                break;
            }
            default:
            {
                if (getUsableWidth() > 400)
                    cols++;
                if (getUsableWidth() > 500)
                    cols++;
                break;
            }            
        };
        


        int chordWidthCalc = getUsableWidth() / cols - getNonScaledPadding() / ((float)cols - 1) - 1; // 100;
        if (chordWidthCalc < 100)
            chordWidthCalc = 100;
        int chordWidth = chordWidthCalc;

        int chordHeight;

        int max_calculatedOffsetY = 0;
        int max_calculatedOffsetX = 0;

        bool drawFbo = false;

        switch (getTheoryVizInstrumentChordViewMode())
        {
            case TheoryVizInstrumentChordViewMode::UNSET:
                chordHeight = chordWidth / 2.0f;
                drawFbo = false;
                break;

            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
            {
                chordHeight = chordWidth * 1.5f;
                drawFbo = true;
                break;
            }
        };

        int calculatedOffsetX = 0;
        int calculatedOffsetY = 0;

        int calculatedWidth = 0;
        int calculatedHeight = chordHeight;

        vector<uiVizChordSlice> chordSlices_current = chordSlices;

        chordSlices.clear();

        // Label
        if(!getShowTopMenu() && getSelectedChords().size() == 0) {
            setBreadcrumbItemItems({uiVizWidgetElmBreadcrumbItem("", "Drag chords here...")});
            setBreadcrumbItemItemsVisibility(true);
        } else {
            setBreadcrumbItemItemsVisibility(false);
        }

        for (int chordIndex = 0; chordIndex < getSelectedChords().size(); chordIndex++)
        {

            vizChord *chord = getSelectedChordByIndexRef(chordIndex);

            //chordIndex++;
            uiVizChordSlice chordSlice;

            switch (getTheoryVizInstrumentChordViewMode())
            {
            case TheoryVizInstrumentChordViewMode::UNSET:
                chordSlice.drawToFbo(getTheoryVizInstrumentChordViewMode(), chord);
                break;

            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
            {
                if (!stringedInstrument)
                {
                    setCorrectDiagramWidgets();
                }
                if (!stringedInstrument->getIsVisible())
                    stringedInstrument->setIsVisible(true);
                    
                if (chord->getFboNeedsUpdate())
                {
                    stringedInstrument->setInstrumentRules(chord->getInstrumentRules(), false);
                    stringedInstrument->setX(-300);
                    stringedInstrument->setWidgetSize(240, 360, false);
                    stringedInstrument->setUserCanInvokeContextMenu(false);

                    int chordDiagramNumFrets = chord->getInstrumentRule("stringed", "chordDiagramNumFrets", 5);
                    if (stringedInstrument->getChordDiagramNumFrets() != chordDiagramNumFrets)
                    {
                        stringedInstrument->setChordDiagramNumFrets(chordDiagramNumFrets);
                    }

                    stringedInstrument->setStrings(stringedInstrument->getStringsFromRules(*chord), false);

                    stringedInstrument->addSelectedChord(*chord, false, true, false);

                    if (stringedInstrument->getSelectedChords().size() > 0) {
                        // Update the notes to reflect the notes on  Fretboard...
                        string userDefinedChordName = chord->getChordName_UserDefined();
                        bool userDefinedPoints = chord->getIsUserDefinedPoints();

                        setSelectedChordAtIndex(chordIndex, stringedInstrument->getSelectedChords()[0]);
                        chord = getSelectedChordByIndexRef(chordIndex);
                        chord->setChordName_UserDefined(userDefinedChordName);
                        chord->setIsUserDefinedPoints(userDefinedPoints);
                    }

                    chord->setFbo(stringedInstrument->saveWidgetContentsToFbo());
                    break;
                }
            };
            }


            bool notesFontStyleCalculated = false;

            // Calculate notes slices
            int notes = chord->getNotes().size();
            int notesWidth = scale(chordWidth / (float)notes);

            chordWidth = deScale(notesWidth) * notes;

            chordSlice.showChordName = true;
            chordSlice.showNoteNames = getTheoryVizLabelMode() != TheoryVizLabelMode::NONE;

            // Calculate chord slices
            chordSlice.chord = *chord;
            chordSlice.labelPoint = uiVizCoord::vizPoint(0, 0);
            chordSlice.bounds = uiVizCoord::vizBounds(0, 0, chordWidth, chordHeight);
            chordSlice.path.setRectRounded(
                scale(getUsableX() + calculatedOffsetX),
                scale(getUsableY() + calculatedOffsetY),
                scale(chordWidth),
                scale(chordHeight),
                getScaledPadding(),
                chord->getChordColor());

            chordSlice.chordFontStyle = getViz()->getLargeStyleFontSizedForDimensions(scale(chordWidth), scale(chordWidth));

            if (getTheoryVizLabelModeChordLabel() == TheoryVizLabelMode::DEGREES) {
                chordSlice.label = chord->getChordNameRoman(getSelectedKey().getNoteName());
                
            } else {
                chordSlice.label = chord->getChordNameForDisplay(false);
            }

            chordSlice.regularFontColor = ofColor::fromHsb(chord->getChordColor().getHue(), 180, 140);
            ofRectangle chordFontRect =
                getViz()->getFonts()->getTextBounds(chordSlice.label, chordSlice.chordFontStyle, chordSlice.path.getRectangle().x, chordSlice.path.getRectangle().y);

            chordSlice.chordFontRect = chordFontRect;

            chordSlice.labelPoint = uiVizCoord::vizPoint(
                chordSlice.path.getRectangle().x + (scale(chordWidth) - chordFontRect.width) / 2,
                chordSlice.path.getRectangle().y + (drawFbo ? (scale(chordHeight) - chordFontRect.height / 2.5f) : (chordSlice.showNoteNames ? scale(chordHeight) / 1.25f + chordFontRect.height / 6.0f : // bottom
                                                                                                                        scale(chordHeight) / 2 + chordFontRect.height / 2.5f                              // middle
                                                                                                                    )));

            int notesHeight = drawFbo ? chordFontRect.height : (chordSlice.showNoteNames ? chordHeight / (chordSlice.showChordName ? 2 : 1) : 0);

            switch (getTheoryVizInstrumentChordViewMode())
            {
                case TheoryVizInstrumentChordViewMode::UNSET:
                    break;

                case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
                    if (getViz()->getResolutionMultiplier() > 1) {
                        notesHeight = notesHeight * 0.5f; // want even less height if stringed diagram... 
                    }
                    // ^^ for some reason it's too small if not using higher resolution...
            }



            for (int i = 0; i < notes; i++)
            {

                vizNote note = chord->getNotes()[i];
                uiVizNoteSlice noteSlice;

                string chordRootName = chord->getChordRoot();

                ofColor noteColor = getSliceColorForState(chordRootName,
                                                          note.getNoteName(),
                                                          chord->getChordRootNote().getInterval(note.getNoteName()) + 1, false);

                noteSlice.regularFontColor = getFontColorForState(chordRootName, 100);

                if (!notesFontStyleCalculated)
                {
                    chordSlice.notesFontStyle = getViz()->getLargeStyleFontSizedForDimensions(scale(notesWidth), scale(notesWidth));
                    notesFontStyleCalculated = true;
                }

                noteSlice.path.setRectRounded(
                    notesWidth * i + scale(getUsableX() + calculatedOffsetX),
                    scale(getUsableY() + calculatedOffsetY),
                    notesWidth,
                    scale(notesHeight),
                    i == 0 ? getScaledPadding() : 0,
                    i == chord->getNotes().size() - 1 ? getScaledPadding() : 0,
                    !chordSlice.showChordName && i == chord->getNotes().size() - 1 ? getScaledPadding() : 0,
                    !chordSlice.showChordName && i == 0 ? getScaledPadding() : 0);
                noteSlice.path.setColor(noteColor);

                switch (getTheoryVizLabelMode())
                {
                case TheoryVizLabelMode::NONE:
                    noteSlice.label = "   ";
                    break;

                case TheoryVizLabelMode::KEYS:
                    noteSlice.label = note.getNoteName() + ofToString(note.getNoteOctave());
                    break;

                case TheoryVizLabelMode::DEGREES:
                    noteSlice.label = chord->getChordRootNote().getNoteNameRoman(note.getNoteName());
                    break;
                };

                //noteSlice.label =  note.getNoteName();
                ofRectangle noteFontRect =
                    getViz()->getFonts()->getTextBounds(noteSlice.label, chordSlice.notesFontStyle, noteSlice.path.getRectangle().x, noteSlice.path.getRectangle().y);

                noteSlice.labelPoint = uiVizCoord::vizPoint(
                    noteSlice.path.getRectangle().x + (noteSlice.path.getRectangle().width - noteFontRect.width) / 2,
                    noteSlice.path.getRectangle().y + (noteFontRect.height / 2.5f + noteSlice.path.getRectangle().height / 2));

                chordSlice.notes.push_back(noteSlice);
            }
            chordSlices.push_back(chordSlice);

            if (calculatedOffsetX + chordWidth * 2 > getUsableWidth())
            {
                // New row
                calculatedOffsetY += chordHeight + getNonScaledPadding();
                calculatedOffsetX = 0;
            }
            else
            {
                calculatedOffsetX += chordWidth + getNonScaledPadding();
            }

            max_calculatedOffsetY = std::max(calculatedOffsetY, max_calculatedOffsetY);
            max_calculatedOffsetX = std::max(calculatedOffsetX, max_calculatedOffsetX);

        }

        // Hide the diagram generators!
        if (stringedInstrument)
            stringedInstrument->setIsVisible(false);

        setContentBoundsScaled(uiVizCoord::vizBounds(getContentBoundsScaled().x,
                                                     getContentBoundsScaled().y,
                                                     scale(getUsableWidth()),
                                                     scale(max_calculatedOffsetY+chordHeight)));


        bucketIcon.setScaledBounds(
            scale(getUsableX()),
            scale(getUsableY()),
            scale(getUsableWidth()),
            scale(getUsableHeight()));
    }

    virtual void draw(uiVizWidgetContext context) override
    {

        if(context.drawContext == uiVizWidgetContext::DrawContext::THUMBNAIL) {
            if (topMenu) {
                topMenu->setIsVisible(false);
            }
            setBreadcrumbItemItemsVisibility(false);
            bucketIcon.draw();
        }

        bool drawFbo = true;
            //getTheoryVizInstrumentChordViewMode() == TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM;

        // Auditioning for playing chord
        if (isPlaying()) {
            if (mShouldChangePlayingChord) {
                mShouldChangePlayingChord = false;

                if (getPlayingChordIndex() < getSelectedChords().size() - 1) {
                    int playingChordIndex = getPlayingChordIndex();
                    setPlayingChordIndex(playingChordIndex+1);
                } else {
                    setPlayingChordIndex(0);
                }
            }
        }


        for (int i = 0; i < chordSlices.size(); i++)
        {
            uiVizChordSlice chordSlice = chordSlices[i];

            if (i == getHoveredChordIndex() || (i == getPlayingChordIndex() && isPlaying())) {
                int p = getScaledPadding()*0.75f;
                uiVizElm highlight;
                highlight.setRectRounded(
                    chordSlice.path.getRectangle().x-p,
                    chordSlice.path.getRectangle().y-p,
                    chordSlice.path.getRectangle().width+p*2,
                    chordSlice.path.getRectangle().height+p*2,
                    getScaledPadding(),
                    getTheme().TitleFontColor_withAlpha(0.95f));
                highlight.draw();

                chordSlice.chord.getFbo().draw(
                scale(getUsableX() + getWidth()-getSidebarWidth()),
                scale(uiVizWidget::getY() + (topMenu ? topMenu->getHeight() + getNonScaledPadding()*3 : 0)), 
                scale(getSidebarWidth()),
                scale(360*1.5f));

            }

            chordSlice.draw(true, getTheoryVizInstrumentChordViewMode());

        

            if (!chordBucketContextMenu->getIsVisible() && getIsActiveWidget() && !getIsDragging())
            {
                if ((chordSlice.getIsMouseHovered() && !isPlaying()) || i == getPlayingChordIndex() && isPlaying())
                {
                    setDraggingChord(chordSlice.chord);
                    setHoveredChordIndex(i);              

                    if (getHoveredChordIndex() != getHoveredChordIndexPrev())
                    {
                        clearAuditioning();
                        setHoveredChordIndexPrev(getHoveredChordIndex());
                        setDragData(getDraggingChord().getXML());
                        auditionChord(chordSlice.chord, getPlayingTempoBPM(), true);
                    }
                }
            }
        }

    }




    bool getShowTopMenu() {
        return mShowTopMenu;
    }

    void setShowTopMenu(bool val) {
        mShowTopMenu = val;



        if (!topMenu && val) {
            // getSidebarWidth() =
                    // <elements>
                    //     <element id="SELECT_A_SCALE" class="uiVizWidgetElmBreadcrumb">
                    //     <items><item key="Label">Add chords for a scale...</item></items>
                    //     <bounds xExpr="${PARENT.LEFT}" yExpr="${PARENT.TOP}" widthExpr="${PARENT.USABLE_WIDTH}" />
                    //     </element>                         
                    // </elements>   
            scalePickerMenuItem = new uiVizWidgetScalePicker(
                getWidgetId() + "_MENU_SCALE_PICKER", R"(
                <widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/>
                </widget>
                )");    
            scalePickerMenuItem->setBreadcrumbItemItems({uiVizWidgetElmBreadcrumbItem("", "Add chords for a scale...")});
            scalePickerMenuItem->setShouldPersist(true);            
            ofAddListener(scalePickerMenuItem->noteSelected, this, &uiVizWidgetChordBucket::onScalePickerMenuNoteSelected);


            keyPickerMin = new uiVizWidgetKeyPickerPopout(getPersistentId() + "_KEY_PICKER_MIN", R"(
                    <widget>
                        <bounds widthExpr="35" heightExpr="35" xExpr="${PARENT.RIGHT}-${SELF.WIDTH}-${PADDING}" yExpr="${PARENT.ABSOLUTE_USABLE_Y_FIXED}" />
                        <appearance minimized="1" />
                    </widget>
                    )");

            addChildWidget(*keyPickerMin, true);

            keyPickerMin->handleKeyChanged([this](vizNote note) {
                this->setSelectedKey(note);
                if (mUserSelectedDegreesLabelMode) this->setTheoryVizLabelModeChordLabel(TheoryVizLabelMode::DEGREES);
            });
            if (getSelectedKey().getNoteName() != "") keyPickerMin->setSelectedKey(getSelectedKey());
            keyPickerMin->setNeedsUpdate(true);

           topMenu = new uiVizWidgetMenuCollection("TOP_MENU", R"(
                <widget>
                    <bounds xExpr="${PARENT.ABSOLUTE_USABLE_X}" yExpr="${PARENT.ABSOLUTE_USABLE_Y_FIXED}" widthExpr="${PARENT.WIDTH}-${PADDING}*3-35"  />
                    <properties menuType="MENU" />
                </widget>
                )");

                chordBucketContextMenu2 = new uiVizWidgetMenu(getWidgetId() + "_CB_MENU2", "<widget><bounds width='100' height='300'/></widget>", getWidgetId(), uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {

                // ----------------------------------------------------------------------------
                // Layout
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LAYOUT"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_LAYOUT, {
                    uiVizWidgetMenuItem(uiVizShared::lang("SIDEBAR"), 0, true, false), 
                    uiVizWidgetMenuItem(uiVizShared::lang("SMALLER_DIAGRAMS"), 1, true, false),
                    uiVizWidgetMenuItem(uiVizShared::lang("BLACK_AND_WHITE"), 2, true, false)
                }),

                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizLabelMode::NONE), 
                    uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true), 
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES), 
                    uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                }),

                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("COLOR"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizColorMode::NONE), 
                    uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true), 
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES), 
                    uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                    //uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                }),

                // ----------------------------------------------------------------------------
                // Chord view mode
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD_VIEW"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("REGULAR"), (int)TheoryVizInstrumentChordViewMode::UNSET), 
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM"), (int)TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM),
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES, true, false)
                }),
            });
            ofAddListener(dynamic_cast<uiVizWidgetMenu *>(chordBucketContextMenu2)->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);


            SLD_tempo = dynamic_cast<uiVizWidgetElmSlider*>(addOrLoadWidgetElement(SLD_tempo, WIDGET_ELM_CLASS::SLIDER, "SLD_tempo", R"(
                <element>
                <title>TEMPO</title>
                </element>
                )"));


            SLD_tempo->setX_Expr("${PARENT.LEFT}");
            SLD_tempo->setY_Expr("${PARENT.BOTTOM}"); 
            SLD_tempo->setWidth_Expr("${PARENT.WIDTH}-${PADDING}*2"); 
            SLD_tempo->setRange(1, 300, 300);
            SLD_tempo->setShouldPersist(true);

            


            chordRulesMenuItem = new uiVizWidgetChordRules(
                getWidgetId() + "_MENU_CHORD_RULES",
                "<widget><bounds minWidth='300' minHeight='400'/><appearance/></widget>"
            );

            chordRulesMenuItem->setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode::CHORD);            
            ofAddListener(chordRulesMenuItem->rulesChanged, this,  &uiVizWidgetChordBucket::onChordBucketRulesChanged);

            chordBucketToolsMenu = new uiVizWidgetMenu(getWidgetId() + "_CB_TOOLS_MENU", "<widget><bounds width='100' height='300'/></widget>", getWidgetId(), uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                uiVizWidgetMenuTab(uiVizShared::lang("SETTINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {
                    uiVizWidgetMenuItem(uiVizShared::lang("EXPORT_PNG"), 5), 
                    uiVizWidgetMenuItem(uiVizShared::lang("EXPORT_HTML"), 6)
                })
            });

            ofAddListener(chordBucketToolsMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);                     

            stringedBucketContextMenu = new uiVizWidgetMenu(getWidgetId() + "_CB_TOOLS_MENU", "<widget><bounds width='100' height='300'/></widget>", getWidgetId(), uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {

                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE_INSTR, {
                    uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizLabelMode::NONE), 
                    uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true), 
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES)
                }),

                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("COLOR"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE_INSTR, {
                    uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizColorMode::NONE), 
                    uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true), 
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES)
                    //uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                }) ,

                // ----------------------------------------------------------------------------
                // Chord Rules
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD_RULES"), uiVizIconCache::getIcon("MED_CONTENT_RULES"),
                                0,
                                chordRulesMenuItem
                    ),

                // ----------------------------------------------------------------------------
                // Strings menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("STRINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_STRINGS, !stringedInstrument ? vector<uiVizWidgetMenuItem>() : stringedInstrument->getStringsMenuItems()),

                // ----------------------------------------------------------------------------
                // Chord view mode
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD_VIEW"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(3), 3), 
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(4), 4), 
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(5), 5), 
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(6), 6)
                })         


            });

            ofAddListener(stringedBucketContextMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);          


            topMenu->setIsRoundedRectangle(false);            
            topMenu->setMenuCollection( {
                uiVizWidgetMenuCollectionItem("TOOLS", chordBucketToolsMenu, "Tools", uiVizIconCache::getIcon("MED_CONTENT_SETTINGS")),
                uiVizWidgetMenuCollectionItem("VIEW", chordBucketContextMenu2, "View", uiVizIconCache::getIcon("MED_CONTENT_VIEW")),
                uiVizWidgetMenuCollectionItem("GUITAR", stringedBucketContextMenu, "Stringed", uiVizIconCache::getIcon("MED_INST_ELECTRIC_GUIT")),
                uiVizWidgetMenuCollectionItem("SCALE_PICKER", scalePickerMenuItem, uiVizIconCache::getIcon("MED_ADD_CIRCLE")),
                uiVizWidgetMenuCollectionItem("TEMPO", nullptr, uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL")),
                uiVizWidgetMenuCollectionItem("PLAY_BUTTON", nullptr, uiVizIconCache::getIcon("REG_REG_PLAY_BUTTON")),
                uiVizWidgetMenuCollectionItem("STOP_BUTTON", nullptr, uiVizIconCache::getIcon("REG_REG_STOP_BUTTON"))                

            });      

            topMenu->setMenuItem_Visibility("STOP_BUTTON", false);   

            addChildWidget(*topMenu, true);  
            // try removing set active widget id  
            ofAddListener(topMenu->menuItemSelected, this, &uiVizWidgetChordBucket::onTopMenuItemSelected);    



            setTheoryVizInstrumentChordViewMode(getTheoryVizInstrumentChordViewMode());


        } else if (!val) {
            if (scalePickerMenuItem) {
                scalePickerMenuItem->setIsVisible(false);
            } 
            
        }


    }    

    virtual void onChordBucketRulesChanged(uiVizInstrumentRuleArgs &args) {
        for (int i=0; i< getSelectedChords().size(); i++) {
            vizChord *chord = getSelectedChordByIndexRef(i);
            chord->setInstrumentRules(args.rules);
            chord->setFboNeedsUpdate(true);
        }

        setNeedsUpdate(true);
    }    


    int getSidebarWidth() {
        return mSidebarWidth;
    }

    void setSidebarWidth(int val) {
        mSidebarWidth = val;
    }  

    bool getIsSmallerDiagrams() {
        return mIsSmallerDiagrams;
    }

    void setIsSmallerDiagrams(bool val) {
        mIsSmallerDiagrams = val;
    }

      
                

    virtual int getUsableWidth() override {
        return uiVizWidgetMusical::getUsableWidth() - getSidebarWidth();
    }  

    virtual int getUsableY() override {
        return uiVizWidget::getUsableY() + (topMenu ? topMenu->getHeight() + getNonScaledPadding() : 0);
    }        
    

    void onUserDefinedChordNameChanged(uiVizTextChangedArgs &args)
    {
        vizChord *chord = getSelectedChordByIndexRef(mContextMenuChordIndex);
        if (chord)
        {
            chord->setChordName_UserDefined(args.text);
        }
        setNeedsUpdate(true);
    }

    bool needsUpdateBeforeDraw(bool shouldResetTimer) override
    {
        bool needsUpdate = uiVizWidgetMusical::needsUpdateBeforeDraw(false);

       if (isPlaying() && getPlayingTimerMillis() > getMillisDurationForBPM(getPlayingTempoBPM()) && !getAuditioningChord().getIsPlaying()) {

            resetPlayingTimer();
            mShouldChangePlayingChord = true;
            shouldResetTimer = true;
        }

        if (shouldResetTimer) resetTimer();

        return needsUpdate || mShouldChangePlayingChord;
    }

    virtual void setSelectedKey(vizNote val) override {
        if(keyPickerMin) {
            keyPickerMin->setSelectedKey(val);
            keyPickerMin->setNeedsUpdate(true);        
        }

        uiVizWidgetMusical::setSelectedKey(val);
        setNeedsUpdate(true);
    }

    virtual void addChordsFromScale(vizScale val) {
        clearSelectedChords();
        setSelectedKey(val.getKey());

        vector<vizChord> chords = vizScale::getDiatonicChordsForScale(val.getKey().getNoteName(), val.getName());
        
        for (vizChord chord:chords) {
            addSelectedChord(chord, false, false);
        }
        setNeedsUpdate(true);
    }


    enum MENU_GROUP_1
    {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,

        MENU_TAB_THEORY_LABEL_MODE_INSTR = 2,
        MENU_TAB_THEORY_COLOR_MODE_INSTR = 3,

        MENU_TAB_CHORD_VIEW_MODE = 4,
        MENU_TAB_SETTINGS = 5,
        MENU_TAB_CHORD_RULES = 6,  
        MENU_TAB_CHORD_DESIGNER = 10,
        MENU_TAB_CHORD_DESIGNER_STRINGED = 11,  
        MENU_TAB_LAYOUT = 12,
        MENU_TAB_STRINGS = 13,          
    };

private:
    uiVizWidgetMenuCollection* topMenu = nullptr;;
    uiVizWidget *chordBucketContextMenu = nullptr;
    uiVizWidget *chordBucketContextMenu2 = nullptr;
    uiVizWidgetMenu *stringedBucketContextMenu = nullptr;
    
    
    uiVizWidgetChordDesigner *chordDesignerMenuItem = nullptr;
    uiVizWidgetGuitar *chordDesignerMenuItemStringed = nullptr;
    uiVizWidgetGuitar *stringedInstrument = nullptr;
    uiVizWidgetScalePicker *scalePickerMenuItem = nullptr;

    uiVizWidgetMenu *chordBucketToolsMenu = nullptr;
    uiVizWidgetChordRules* chordRulesMenuItem = nullptr;
    uiVizWidgetKeyPickerPopout* keyPickerMin = nullptr;
    

    bool mShowTopMenu = false;
    int mSidebarWidth = 0; // 360
    bool mIsSmallerDiagrams = false;
    bool mUserSelectedDegreesLabelMode = false;

    vector<uiVizChordSlice> chordSlices;
    int mContextMenuChordIndex = -1;
    uiVizIcon bucketIcon;

    bool mShouldChangePlayingChord = false;

    uiVizWidgetElmSlider* SLD_tempo = nullptr;
    TheoryVizLabelMode mTheoryVizLabelModeChordLabel = TheoryVizLabelMode::KEYS;  

    virtual void onTopMenuItemSelected(uiVizWidgetMenuCollectionArgs & args) {
        if (args.menuTag == "PLAY_BUTTON" && !isPlaying()) {
            SLD_tempo->setIsVisible(true);
            startPlaying();
            topMenu->setMenuItem_Visibility("PLAY_BUTTON", false);
            topMenu->setMenuItem_Visibility("STOP_BUTTON", true);
        } else if (args.menuTag == "STOP_BUTTON") {
            SLD_tempo->setIsVisible(false);
            topMenu->setMenuItem_Visibility("PLAY_BUTTON", true);
            topMenu->setMenuItem_Visibility("STOP_BUTTON", false);
            stopPlaying();
        }            
    }

    void onScalePickerMenuNoteSelected(uiVizNoteSelectedArgs &args) {
        vizScale scale = vizScale(scalePickerMenuItem->getSelectedKey().getNoteName(), scalePickerMenuItem->getCalculatedScaleName(), 3);
        addChordsFromScale(scale);
    }

    // still saving Gb
    // option to switch between degrees and notes


    void initWidget() override
    {
        bucketIcon = uiVizIconCache::getIcon("MED_CONTENT_BUCKET");

        setTitle(uiVizShared::lang("CHORD_BUCKET"));
        setScrollAction(ScrollAction::SCROLL);
        setEnableScrollYPositive(true);
        setEnableScrollYNegative(true);
        setEnableScrollXPositive(false);
        setEnableScrollXNegative(false);        

        if (!chordBucketContextMenu)
        {


            chordDesignerMenuItemStringed =  new uiVizWidgetGuitar(getWidgetId() + "_MENU_STRINGED_CHORD", R"(
                        <widget>
                            <bounds width='300' height='300' minWidth='200' minHeight='200' />
                            <properties>
                                <musicData drawMode="RIGHT" instrumentContentMode="CHORD" orientation="VERTICAL" colorMode="KEYS" colorAlternateMode="NONE" labelMode="KEYS" labelAlternateMode="NONE" noteMode="DEFAULT" labelShowOctave="0" isChordDiagramMode="1">
                                    <rules>
                                        <general>
                                            <showExtendedNoteNames>1</showExtendedNoteNames>
                                        </general>
                                    </rules>
                                </musicData>
                            </properties>
                        </widget>
                        )");
            ofAddListener(chordDesignerMenuItemStringed->widgetEventReceived, this, &uiVizWidgetChordBucket::onChordDesignerMenuItemStringedEventReceived);


            chordDesignerMenuItem = new uiVizWidgetChordDesigner(
                getWidgetId() + "_MENU_CHORD_DESIGNER",
                "<widget><bounds width='300' height='300' minWidth='200' minHeight='200'/><appearance/></widget>");

            ofAddListener(chordDesignerMenuItem->userDefinedChordNameChanged, this, &uiVizWidgetChordBucket::onUserDefinedChordNameChanged);

            chordDesignerMenuItem->setUserCanInvokeContextMenu(false);
            chordDesignerMenuItem->setUserCanSetSelectedKey(false);
            chordDesignerMenuItem->setUserCanAddSelectedNote(false);

            chordBucketContextMenu = new uiVizWidgetMenu(getWidgetId() + "_CB_MENU1", "<widget><bounds width='100' height='300'/></widget>", getWidgetId(), uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {

                // ----------------------------------------------------------------------------
                // Layout
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LAYOUT"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_LAYOUT, {
                    uiVizWidgetMenuItem(uiVizShared::lang("SIDEBAR"), 0, true, false), 
                    uiVizWidgetMenuItem(uiVizShared::lang("SMALLER_DIAGRAMS"), 1, true, false),
                    uiVizWidgetMenuItem(uiVizShared::lang("BLACK_AND_WHITE"), 2, true, false)
                }),

                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizLabelMode::NONE), 
                    uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true), 
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES), 
                    uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000
                )}),

                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("COLOR"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE, {
                                                                                                                                                                uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizColorMode::NONE), uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true), uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES), uiVizWidgetMenuItem(uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                                                                                                                                                                //uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                                                                                                                                                            }),

                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("LABEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE_INSTR, {uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizLabelMode::NONE), uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true), uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES)}),

                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("COLOR"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE_INSTR, {
                                                                                                                                                                        uiVizWidgetMenuItem(uiVizShared::lang("NONE"), (int)TheoryVizColorMode::NONE), uiVizWidgetMenuItem(uiVizShared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true), uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES)
                                                                                                                                                                        //uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                                                                                                                                                                    }),

                // ----------------------------------------------------------------------------
                // Chord view mode
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD_VIEW"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE, 
                    {uiVizWidgetMenuItem(uiVizShared::lang("REGULAR"), (int)TheoryVizInstrumentChordViewMode::UNSET), 
                    uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM"), (int)TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM),
                    uiVizWidgetMenuItem(uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES, false, false)
                    }
                ),

                // ----------------------------------------------------------------------------
                // Chord Designer menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER, chordDesignerMenuItem),


                // ----------------------------------------------------------------------------
                // Chord Designer menu (stringed)
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("CHORD"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER_STRINGED, chordDesignerMenuItemStringed),                

                // ----------------------------------------------------------------------------
                // Settings menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("SETTINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {uiVizWidgetMenuItem(uiVizShared::lang("LEFT_HAND"), 0, true, false), uiVizWidgetMenuItem(uiVizShared::lang("DELETE"), 1)})

            });
            ofAddListener(dynamic_cast<uiVizWidgetMenu *>(chordBucketContextMenu)->menuItemSelected, this, &uiVizWidgetChordBucket::onMenuItemSelected);

            uiVizWidgetManager::addWidget(*chordBucketContextMenu, false, getWidgetId());
        }

    }    


    virtual void onWidgetLoaded() override {
        configureLayout();
    }    

    void configureLayout() {
        
        if (SLD_tempo) {
            SLD_tempo->setIsVisible(false);
        }

    }

    void setCorrectDiagramWidgets()
    {

        // Default instrument
        setGMInstrumentNumber(vizTheory::GeneralMidiInstrument::Acoustic_Grand_Piano);

        switch (getTheoryVizInstrumentChordViewMode())
        {
        case TheoryVizInstrumentChordViewMode::UNSET:

            break;

        case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM:
        {
            setGMInstrumentNumber(vizTheory::GeneralMidiInstrument::Electric_Guitar_jazz);
            if (!stringedInstrument)
            {
                stringedInstrument = new uiVizWidgetGuitar(getWidgetId() + "_DIAGRAM_CREATOR", R"(
                        <widget>
                            <bounds x="-300" y="0" />
                            <properties>
                                <musicData drawMode="RIGHT" instrumentContentMode="CHORD" orientation="VERTICAL" colorMode="KEYS" colorAlternateMode="NONE" labelMode="KEYS" labelAlternateMode="NONE" noteMode="DEFAULT" labelShowOctave="0" isChordDiagramMode="1">
                                    <rules>
                                        <general>
                                            <showExtendedNoteNames>1</showExtendedNoteNames>
                                        </general>
                                    </rules>
                                </musicData>
                            </properties>
                        </widget>
                        )");

                uiVizWidgetManager::addWidget(*stringedInstrument, false, getWidgetId());
            }
// todo
// menu not being filled with items
// change selected scale - clear stringed rules
//        todo - save the degrees part too and add a dropdown..

// Scale picker on guitar fretboard - RULES NOT WORKING
// move rules to ROOT MENU ....


// NEXT::
// when changing key or scale - apply "global" rule / rules - set globally - so when changing it "remembers"
// ------------- sub menu INSIDE widget / // Fix hover buttons!!


// Todo:
// consider save savestate menu statuses ..... !!! (tabs work ....)
// Fret range …. (Apply across) - for stringed instrument
// regular chord view not working for rules

// chord modes:
// todo : rename this class to uiVizWidgetChord, which supports (hosts) following child widgets (derrived off of uiVizWidgetElement:
// uiVizWidgetStringedInstrument
// uiVizWidgetGenericChord (move this fonctionality to it!)



            if (stringedInstrument != nullptr && stringedBucketContextMenu != nullptr) {            
                    stringedBucketContextMenu->addOrUpdateMenuTab(
                        uiVizWidgetMenuTab(uiVizShared::lang("STRINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), 
                        MENU_GROUP_1::MENU_TAB_STRINGS,  stringedInstrument->getStringsMenuItems())                    
                    );
            }

            forceGuitarDiagramRefresh();
            break;
        }
        };
    }

    void onWidgetUnhovered(uiVizWidgetEventArgs &args) override
    {
        setHoveredChordIndexPrev(-100);
    }

    virtual void setIsLefty(bool val) override {
        uiVizWidgetMusical::setIsLefty(val);
        if (stringedInstrument)
        {
            stringedInstrument->setIsLefty(isLefty());
            forceGuitarDiagramRefresh();
        }        
    }

    virtual void setIsBlackAndWhiteMode(bool val) override {
        
        uiVizWidgetMusical::setIsBlackAndWhiteMode(val);
        if (stringedInstrument)
        {
            stringedInstrument->setIsBlackAndWhiteMode(val);
            forceGuitarDiagramRefresh();
        }   
    }

    TheoryVizLabelMode getTheoryVizLabelModeChordLabel() {
        return mTheoryVizLabelModeChordLabel;
    }
    
    void setTheoryVizLabelModeChordLabel(TheoryVizLabelMode theoryVizLabelModeChordLabel) {
        mTheoryVizLabelModeChordLabel = theoryVizLabelModeChordLabel;

        if(topMenu) {
            topMenu->setMenuItemSelectedVal("VIEW", (int)MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE, (int)TheoryVizLabelMode::DEGREES, theoryVizLabelModeChordLabel == TheoryVizLabelMode::DEGREES, false);
        }

        setNeedsUpdate(true);
    }        

    void onMenuItemSelected(uiVizWidgetMenuItemArgs &args)
    {

        switch (args.activeMenuTabId)
        {


        case MENU_GROUP_1::MENU_TAB_LAYOUT: {
            switch(args.menuItem->uniqueID) {
                case 0: {
                    setSidebarWidth(getSidebarWidth() > 0 ? 0 : 360);
                    setNeedsUpdate(true);  
                    break;                        
                }
                case 1: {
                    setIsSmallerDiagrams(!getIsSmallerDiagrams());
                    setNeedsUpdate(true);  
                    break;   
                }
                case 2: {
                    setIsBlackAndWhiteMode(!isBlackAndWhiteMode());
                    setNeedsUpdate(true);  
                    break;   
                }                
            }
            break;            
        }

        case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE:
            if (((TheoryVizLabelMode)args.menuItem->uniqueID == TheoryVizLabelMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedKey().getNoteName() == "")
            {
            }

            if (args.menuItem->uniqueID == -1000)
            {
                setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES);
            }
            else
            {
                setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::NONE);
                setTheoryVizLabelMode((TheoryVizLabelMode)args.menuItem->uniqueID);
            }

            setNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE:
            if (((TheoryVizColorMode)args.menuItem->uniqueID == TheoryVizColorMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedKey().getNoteName() == "")
            {
            }

            if (args.menuItem->uniqueID == -1000)
            {
                setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES);
            }
            else
            {
                setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::NONE);
                setTheoryVizColorMode((TheoryVizColorMode)args.menuItem->uniqueID);
            }

            setNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE_INSTR:
            if (stringedInstrument)
                stringedInstrument->setTheoryVizLabelMode((TheoryVizLabelMode)args.menuItem->uniqueID);
            forceGuitarDiagramRefresh();
            break;

        case MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE_INSTR:
            if (stringedInstrument)
                stringedInstrument->setTheoryVizColorMode((TheoryVizColorMode)args.menuItem->uniqueID);
            forceGuitarDiagramRefresh();
            break;

        case MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE: {
            TheoryVizInstrumentChordViewMode mode = (TheoryVizInstrumentChordViewMode)args.menuItem->uniqueID;

            if (mode == TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM || mode == TheoryVizInstrumentChordViewMode::UNSET) {
                setCorrectDiagramWidgets();
                setTheoryVizInstrumentChordViewMode(mode);                
            } else {
                if (args.menuItem->uniqueID >=3 && args.menuItem->uniqueID <= 6) {
                    int chordDiagramNumFrets = args.menuItem->uniqueID;
                    for (int chordIndex = 0; chordIndex < getSelectedChords().size(); chordIndex++) {
                        vizChord *chord = getSelectedChordByIndexRef(chordIndex);

                        chord->setInstrumentRule("stringed", "chordDiagramNumFrets", chordDiagramNumFrets);
                        chord->setIsUserDefinedPoints(false);
                        ofxXmlSettings rules = chord->getInstrumentRules();
                        chord->setInstrumentRules(rules);
                        vizChord simplifiedChord = vizChord(chord->getChordName(), chord->getNotes(), true); 
                        setSelectedChordAtIndex(chordIndex, *chord);
                    }
                }
            }

            // Switch between Chord degree (relative to selected scale) or Chord key/root name
            if (args.menuItem->uniqueID == (int)TheoryVizLabelMode::DEGREES) {
                mUserSelectedDegreesLabelMode = false;
                if (args.menuItem->isSelected) {
                    setTheoryVizLabelModeChordLabel(TheoryVizLabelMode::DEGREES);
                    mUserSelectedDegreesLabelMode = true;
                } else {
                    setTheoryVizLabelModeChordLabel(TheoryVizLabelMode::KEYS);                    
                }
            }

            //TheoryVizColorMode::DEGREES /* TODO */
            
            setNeedsUpdate(true);
            break;
        }

        case MENU_GROUP_1::MENU_TAB_STRINGS: {
            
            for (int chordIndex = 0; chordIndex < getSelectedChords().size(); chordIndex++) {
                vizChord *chord = getSelectedChordByIndexRef(chordIndex);
                ofxXmlSettings rules = chord->getInstrumentRules();
                vector<uiVizWigetStringedInstrumentString> strings = stringedInstrument->getStringsFromXML(rules);
                strings[args.menuItem->uniqueID].isEnabled = args.menuItem->isSelected;
                uiVizWigetStringedInstrument::appendStringsToXML(rules, strings);

                stringedInstrument->setStrings(strings, true);
                chord->setInstrumentRules(rules);
                chord->setIsUserDefinedPoints(false);
                vizChord simplifiedChord = vizChord(chord->getChordName(), chord->getNotes(), true);
                stringedInstrument->addSelectedChord(simplifiedChord, false, true, false);
                setSelectedChordAtIndex(chordIndex, (stringedInstrument->getSelectedChords()[0]));
            }


// if chord no longer valid, recalculate here .....
// also set userdefinedpoints fals when doing this....
// then onto chord diagram size (3,4,5,6)
// store root

            forceGuitarDiagramRefresh();
            break;
        }


        case MENU_GROUP_1::MENU_TAB_SETTINGS:

            string fileName = "Some Chords";
            if (getSelectedKey().getNoteName() != "") fileName += " in the Key of " + getSelectedKey().getNoteName();


            if (args.menuItem->uniqueID == 0) {
                setIsLefty(!isLefty());
            } else if  (args.menuItem->uniqueID == 1) {
                // Delete
                removeSelectedChord(mContextMenuChordIndex);
                setNeedsUpdate(true);
            } else if (args.menuItem->uniqueID == 5)
            {
                // SAVE AS PNG ...

                uiVizWidgetManager::showSaveDialog("", vizTheory::extractFileSystemSafeName(fileName + ".png"),
                                                   [&](string filePath)
                                                   {
                                                       this->saveWidgetContentsToImageFile(filePath, uiVizWidgetContext::SCREEN);
                                                   });
            } else if (args.menuItem->uniqueID == 6)
            {
                // SAVE AS HTML ...
                uiVizWidgetManager::showSaveDialog("", vizTheory::extractFileSystemSafeName(fileName),
                                                   [&](string filePath)
                                                   {
                                                        uiVizShared::removeFileExtension(filePath);
                                                        filePath += ".html";
                                                        this->saveWidgetContentsToHTMLFile(filePath);
                                                   });
            }
            break;
        }     

        setCorrectDiagramWidgets();
    }


    virtual void saveWidgetContentsToHTMLFile(string fileName) override { 

        TheoryVizLabelMode originalLabelMode = stringedInstrument != nullptr ? stringedInstrument->getTheoryVizLabelMode() : getTheoryVizLabelMode();

        string title = ofFilePath::getFileName(fileName);
        title = uiVizShared::removeFileExtension(title);

        string contentHTML = "<html><body>";
        contentHTML += "<style>";
        contentHTML += "div { float:left; width:95px; font-family: Arial !important } div h3 { display:block; text-align:center; margin-bottom:3px; font-family: Arial !important} div img { float:left; clear:both; width:100%;  }";

        uiVizWidgetTheme t = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();
        if (!isBlackAndWhiteMode()) {
            ofColor bgCol1Col = t.WidgetAccent1Color;
            ofColor bgCol2Col = t.WidgetAccent2Color;
            ofColor bgCol3Col = t.WidgetAccent3Color;
            ofColor bgCol4Col = t.WidgetAccent4Color;            

            if (t.IsDark) {
                bgCol1Col.setBrightness(255);
                bgCol2Col.setBrightness(255);
                bgCol3Col.setBrightness(255);
                bgCol4Col.setBrightness(255);                
            } else {
                bgCol1Col.setBrightness(200);
                bgCol2Col.setBrightness(200);
                bgCol3Col.setBrightness(200);
                bgCol4Col.setBrightness(200);
            }
      
            string bgCol1 = uiVizWidgetTheme::getHexFromColor(bgCol1Col, 0.7f);
            string bgCol2 = uiVizWidgetTheme::getHexFromColor(bgCol2Col, 0.7f);
            string bgCol3 = uiVizWidgetTheme::getHexFromColor(bgCol3Col, 0.7f);
            string bgCol4 = uiVizWidgetTheme::getHexFromColor(bgCol4Col, 0.7f);        

            contentHTML += "body {";
            contentHTML += "background: linear-gradient(150deg, "+bgCol1+", "+bgCol2+" 70.71%),";
            contentHTML += "            linear-gradient(195deg, "+bgCol2+", "+bgCol3+" 70.71%),";
            contentHTML += "            linear-gradient(240deg, "+bgCol3+", "+bgCol4+" 70.71%)";
            contentHTML += "            ;";
            contentHTML += "}";
        }


        contentHTML += "@media print { .no-print, .no-print * { display: none !important; }";
        
        contentHTML += "</style>";
        contentHTML += "<div style=\"float:left;width:100%;\">";
        // point labels= 
        contentHTML += "<select class=\"no-print\" style=\"float:right;\" onchange=\"for(chordIndex=0;chordIndex<="+ofToString(getSelectedChords().size())+";chordIndex++){for(i=1;i<=3;i++){document.getElementById(i+'_'+chordIndex).style.display=((event.target.value==String(i))?'block':'none');}}  \"><option value='1'>None</option><option value='2'>Notes</option><option value='3'>Degrees</option></select>";
        // size
        contentHTML += "<select class=\"no-print\" style=\"float:right;\" onchange=\"document.styleSheets[0].removeRule('div');document.styleSheets[0].insertRule('div {float:left; clear:none; width:'+event.target.value+'}');\"><option value='95px'>Small</option><option value='130px'>Medium</option><option value='160px'>Large</option></select>";

        if (getSelectedKey().getNoteName() != "")  {
            contentHTML += "<select class=\"no-print\" style=\"float:right;\" onchange=\"for(chordIndex=0;chordIndex<="+ofToString(getSelectedChords().size())+";chordIndex++){for(i=1;i<=3;i++){document.getElementById(i+'_'+chordIndex).querySelector('#n').style.display='none';document.getElementById(i+'_'+chordIndex).querySelector('#d').style.display='none';document.getElementById(i+'_'+chordIndex).querySelector(event.target.value).style.display='block';}}  \"><option value='#n'>Chord Name</option><option value='#d'>Chord Degree</option></select>";
        }
        contentHTML += "<h1 style=\"font-family: Arial !important\">"+title+"</h1></div>"; // Title


        // Key
        if (getSelectedKey().getNoteName() != "")  {
            ofBuffer tmpBuff;
            keyPickerMin->saveWidgetContentsToBuffer(tmpBuff, uiVizWidgetContext::SCREEN);
            string base64PNGString = uiVizShared::base64EncodeString(tmpBuff);
            contentHTML += "<div style='float:left;clear:both;width:110px;'>";    
            contentHTML += "<img style=\"width:30px;height:30px;float:right\" alt=\"Key: "+getSelectedKey().getNoteName()+"\" src=\"data:image/png;base64,"+base64PNGString+"\" /><span style=\"display:block;float:left;font-size:25px;font-family: Arial !important;\">Key of</span>";                
            contentHTML += "</div>";
        }

        contentHTML += "<div style='float:left;clear:both;width:100%;'>";  
        for (int i=1; i<=3; i++) {
            
            if (stringedInstrument != nullptr) {
                switch(i) {
                    case 1: {
                        stringedInstrument->setTheoryVizLabelMode(TheoryVizLabelMode::NONE);
                        break;
                    }                
                    case 2: {
                        stringedInstrument->setTheoryVizLabelMode(TheoryVizLabelMode::KEYS);
                        break;
                    }
                    case 3: {
                        stringedInstrument->setTheoryVizLabelMode(TheoryVizLabelMode::DEGREES);
                        break;
                    }                
                }

                forceGuitarDiagramRefresh();
                update(uiVizWidgetContext());
            }


            for (int chordIndex = 0; chordIndex < getSelectedChords().size(); chordIndex++) {
                vizChord *chord = getSelectedChordByIndexRef(chordIndex);
                ofBuffer tmpBuff;

                if (stringedInstrument != nullptr) {
                    chord->saveFboToBuffer(tmpBuff, 240, 360); //getFbo()    
                } else {
                    // How do we save chord slice to FBO ??
                    //chord->saveFboToBuffer(tmpBuff, 240, 150);

                    chord->saveFboToBuffer(tmpBuff, 240, 150); //getFbo() 
// todo and then back to "new" wizard

                }                

                string base64PNGString = uiVizShared::base64EncodeString(tmpBuff);
                string chordName = chord->getChordNameForDisplay(true);
                string chordDegree = "";

                if (getSelectedKey().getNoteName() != "")  {                
                    chordDegree = chord->getChordNameRoman(getSelectedKey().getNoteName());
                }

                string display = (i == 1 ? "block" : "none");

                string uid = ofToString(i)+"_"+ofToString(chordIndex);

                contentHTML += "<div id='"+uid+"' style='display:"+display+"'><h3 id='n'>" + chordName + "</h3><h3 id='d' style='display:none;'>" + chordDegree + "</h3>";        
                contentHTML += "<img alt=\""+chordName+"\" src=\"data:image/png;base64,"+base64PNGString+"\" />";
                contentHTML += "</div>";
            }

        }

        contentHTML += "</div>";

        contentHTML += "</body></html>";        


        ofBuffer buffer(contentHTML.c_str(), contentHTML.length());        
        ofBufferToFile(fileName, buffer);

        string localFileURL = fileName;
        uiVizShared::launchBrowser(localFileURL);

        if (stringedInstrument != nullptr) {
            stringedInstrument->setTheoryVizLabelMode(originalLabelMode);
            forceGuitarDiagramRefresh();
            update(uiVizWidgetContext());
        }

    }  

    virtual ofFbo getContentDragIconFbo() override {
        return getDraggingChord().getFbo();
    }       

};

  