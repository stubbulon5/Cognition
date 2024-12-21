//
//  uiVizChordDesigner_h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetChordRules.h"

class uiVizWidgetChordDesignerSlice {
public:
    vizNote note;
    Aquamarine::Elm path;
    string label;
    int degree = 0;
    ofPoint labelPoint;
    ofColor regularColor;
    ofColor selectedColor;
    ofColor hoveredColor;
    ofColor regularFontColor;
    ofColor selectedFontColor;
    ofColor hoveredFontColor;
    float startSliceX;
    float endSliceX;
    float startSliceY;
    float endSliceY;
    float circRadiusX_Begin;
    float circRadiusY_Begin;
    float circRadiusX_End;
    float circRadiusY_End;
    float circX;
    float circY;
    float distanceFromCentre;
    
    bool isHovered = false;
    bool isSelected = false;
    
    bool getIsMouseHovered() {
        
        int mouseX = ofGetMouseX();
        int mouseY = ofGetMouseY();
    
        
        return (
                ofDist(mouseX, mouseY, circX, circY) <= circRadiusX_Begin  && ofDist(mouseX, mouseY, circX, circY) <= circRadiusY_Begin &&
                ofDist(mouseX, mouseY, circX, circY) > circRadiusX_End && ofDist(mouseX, mouseY, circX, circY) > circRadiusY_End
                );
    }
    
    ~uiVizWidgetChordDesignerSlice() {
    }
    
};

class uiVizWidgetChordDesigner : public uiVizWidgetMusical {
    
public:
    uiVizWidgetChordDesigner(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        calculateExtendedNotesFromCurrentNotes();
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
        
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_DESIGNER, 0);
        return mWidgetXML;
    }
    
    virtual ~uiVizWidgetChordDesigner() {
        circleSlicesT0.clear();
        circleSlicesT1.clear();
        circleSlicesT2.clear();
        
      try {  
            if (chordRulesMenuItem != nullptr) {
                ofRemoveListener(chordRulesMenuItem->rulesChanged, this,  &uiVizWidgetChordDesigner::onRulesChanged);
            }
            
            if (chordDesignerContextMenu) {
                ofRemoveListener(dynamic_cast<Aquamarine::uiVizWidgetMenu*>(chordDesignerContextMenu)->menuItemSelected, this, &uiVizWidgetChordDesigner::onMenuItemSelected);
                chordDesignerContextMenu->deleteThisWidget();
            }
        } catch(...) {
            cout << "~uiVizWidgetChordDesigner() error removing listeners. Have they already been removed? ";
        }


        
    }
    
    void calculateExtendedNotesFromCurrentNotes() {
        // Apply advanced logic based on selected notes
        vector<vizNote> tmpNotes = getSelectedNotesNormalized();
        clearSelectedNotes();
        
        if (tmpNotes.size() > 1) {
            vizNote chordRootNote = tmpNotes[0];
            for (int j=0; j<tmpNotes.size(); j++) {
                vizNote noteToAdd = tmpNotes[j];
                //bool isNoteExtended = noteToAdd.getNoteOctave() > 3;
                bool isNoteExtended = vizChord::calculateIfExtendedNote(chordRootNote, tmpNotes, noteToAdd, true, false);
                noteToAdd.setIsExtended(isNoteExtended);
                addSelectedNote(noteToAdd, true);
            }
        }
        setIsExtendedChordMode(determineIfShouldDisplayExtendedChordMode(getSelectedNotes().size()));
    }
    
    void setSliceProperties(uiVizWidgetChordDesignerSlice *slice,
                            int currentSlice, float currentAngle, float angleOffset, float degreesPerSlice,
                            float circX, float circY, float circRadiusX, float circRadiusY, int tier, bool forceHiglight) {

        ofColor color;
        
        
        switch(tier) {
            case 0:
            case 1: // relative degree color

                if (getSelectedKey().getNoteName() != "") {
                    
                    /*
                    color = (getIsExtendedChordMode() ?
                             vizTheory::getColorForDegree_KeyBrightness(currentSlice, getSelectedKey().getNoteName(), true) :
                             vizTheory::getColorForDegree_KeyBrightness(currentSlice, getSelectedKey().getNoteName(), true)
                             );
                    
                    */
                    
                    color = getSliceColorForState(getSelectedKey().getNoteName(), slice->note.getNoteName(), currentSlice, true);
                    
       
                    
                    
                } else {
                    color = ofColor::white;
                }
                
                break;
            case 2: // parent key
                color = vizTheory::getColorForKey(slice->note.getNoteName());
                break;
                
        }
        
        bool isHighlightedNote = false;
        
        /*-*-*-*-*-*-*-*-*-* Default colours *-*-*-*-*-*-*-*-*-*/
        
        float diff = 60;
        
        slice->hoveredColor = color;


        if (tier == 2) {
            // The key picker "outer rim"
            slice->hoveredFontColor = getHoveredFontColor(slice->note.getNoteName());
        } else {
            // Chord degrees
            slice->hoveredFontColor = getHoveredFontColor(getSelectedKey().getNoteName());
        }

        
        
        if (getSelectedKey().getNoteName() != "") {
            //Key is selected, we want a very light, subtle style for non focused keys
            slice->regularColor = ofColor::fromHsb(color.getHue(), 50, 200);
            slice->regularFontColor = getFaintFontColor();
            
        } else {
            // No key selected, make a pretty hue circle of all possible harmonies...
            mUnfocusedNoteBrightness = 155.0f;
            slice->regularColor = ofColor::fromHsb(color.getHue(), 100, 200);
            slice->regularFontColor = getFaintFontColor(slice->note.getNoteName());
            slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);
            slice->selectedFontColor = getSelectedFontColor(slice->note.getNoteName());
        }

        
        // Regular degrees
        if (forceHiglight || (tier == 1 && !slice->note.getIsExtended() && matchesSelectedNote(slice->note)) || (tier == 2 && matchesSelectedKey(slice->note))) {
            isHighlightedNote = true;
            slice->regularColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness());
            slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);
            slice->regularFontColor = getSelectedFontColor(getSelectedKey().getNoteName());
            slice->selectedFontColor = getSelectedFontColor(getSelectedKey().getNoteName());
        }
        
        // Extended degrees
        if (forceHiglight || (tier == 0 && slice->note.getIsExtended() && matchesSelectedNote(slice->note))) {
            isHighlightedNote = true;
            slice->regularColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness()/2);
            slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);
            slice->regularFontColor = getFaintFontColor();
            slice->selectedFontColor = getSelectedFontColor();
        }
        
        
        ofPath c;
        c.setCircleResolution(360);
        /* Expensive operation: Keep OUT of draw cycle */
        c.moveTo(circX, circY);
        c.arc(circX, circY, circRadiusX, circRadiusY, (float)currentAngle + (float)angleOffset, degreesPerSlice + (float)angleOffset);
        c.close();
        slice->path.update(c);
        
        //---------- Label plot calculations for slice ----------
        float midSlice = ((float)degreesPerSlice/2) + (float)currentAngle + (float)angleOffset;
        float distanceFromCentre = 0.85f;
        
        
        switch(tier) {
            case 0: distanceFromCentre = 0.8f; break;
            case 1: distanceFromCentre = getIsExtendedChordMode() ? 0.87f : 0.73f; break;
            case 2: distanceFromCentre = 0.91f; break;
        }
        
        
        switch(tier) {
            case 0:
            case 1: // standard degrees
                switch (getTheoryVizLabelMode()) {
                    case TheoryVizLabelMode::NONE:
                        slice->label = "   ";
                        break;
                        
                    case TheoryVizLabelMode::KEYS:
                        slice->label =slice->note.getNoteName();
                        break;
                        
                    case TheoryVizLabelMode::DEGREES:
                        if (getSelectedKey().getNoteName() != "") {
                            slice->label = (tier == 0 && getIsExtendedChordMode() ?
                                            getSelectedKey().getNoteNameRomanExtended(slice->note.getNoteName()) :
                                            getSelectedKey().getNoteNameRoman(slice->note.getNoteName())
                                            );
                        } else {
                            slice->label = slice->note.getNoteName();
                        }
                        break;
                };
                
                break;
            case 2: // outer ring
                switch (getTheoryVizLabelMode()) {
                    case TheoryVizLabelMode::NONE:
                        slice->label = "   ";
                        break;
                        
                    default:
                        slice->label = slice->note.getNoteName();
                        break;
                };
                
                break;
        }

        ofRectangle rect = font->rect(slice->label);
        float fontWidth = rect.width;
        float fontHeight = rect.height;
        
        // Now that we have the middle of the slice angle, we use cos, sin on it, and multiply a distanceFromCentre factor on the angle to work
        // out a label coordinate. Finally we have the centre of the font to the x, y coords!
        
        float plotX = (float)(circX - fontWidth /(float) 2) + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(midSlice));
        float plotY = (float)(circY + fontHeight/(float) 2) + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(midSlice));
        slice->labelPoint = ofPoint(plotX, plotY);
        
        // Hit area stuff!
        float startAngle = (float)currentAngle + (float)angleOffset;
        float endAngle = (float)currentAngle + (float)angleOffset + (float)degreesPerSlice;
        
        slice->startSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(startAngle));
        slice->endSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(endAngle));
        slice->startSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(startAngle));
        slice->endSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(endAngle));
        slice->circRadiusX_Begin = circRadiusX;
        slice->circRadiusY_Begin = circRadiusY;
        
        switch(tier) {
            case 0:
                slice->circRadiusX_End = circRadiusX * TIER0_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER0_RADIUS_PERC;
                break;
            case 1:
                slice->circRadiusX_End = circRadiusX * TIER1_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER1_RADIUS_PERC;
                break;
            case 2:
                slice->circRadiusX_End = circRadiusX * TIER2_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER2_RADIUS_PERC;
                break;
        }
        
        slice->circX = circX;
        slice->circY = circY;
        slice->distanceFromCentre = distanceFromCentre;
    }
    
    void onWidgetMouseContentDragged(ofMouseEventArgs &e) override {
        if (getDraggingChord().getChordName() != "") {
            setDragData(getDraggingChord().getXML());
        }
    }
    
    void update(Aquamarine::uiVizWidgetContext context) override {
        
        font = getSmallFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontScaleNameLabel = getFontSizedForDimensions(getUsableWidth() * 0.5f, getUsableHeight() * 0.5f);
        
        rectFontHitArea = font->rect("G#");
        circleInner.clear();
        
        
        // Are we changing color?
        if (getSelectedKey().getNoteName() != "" && mUnfocusedNoteBrightness < 255.0f) {
            mUnfocusedNoteBrightness = scaleAnimation(getWidgetId() + "unfocused_slices", mUnfocusedNoteBrightness, 255.0f, 1.0f);
            setNeedsUpdate(true);
        }
        
        float circX = scale(getUsableX() + getUsableWidth()/2.0f);
        float circY = scale(getUsableY_Custom() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth() /2.0f);
        float circRadiusY = scale(getUsableHeight()/2.0f);
        
        float degreesPerSliceT0 = 360 / (float)notesT0.size();
        float degreesPerSliceT1 = 360 / (float)notesT1.size();
        float degreesPerSliceT2 = 360 / (float)notesT2.size();

        float circRadiusXT0 = circRadiusX * TIER0_RADIUS_PERC;
        float circRadiusYT0 = circRadiusY * TIER0_RADIUS_PERC;
        
        float circRadiusXT1 = circRadiusX * TIER1_RADIUS_PERC;
        float circRadiusYT1 = circRadiusY * TIER1_RADIUS_PERC;
        
        float angleOffset = 0; //degreesPerSliceT2 / (float)2;
        float circRadiusXT2 = circRadiusX * TIER2_RADIUS_PERC;
        float circRadiusYT2 = circRadiusY * TIER2_RADIUS_PERC;
        
        for (int i = 1; i <= circleSlicesT0.size() ; i++) {
            // T0
            // The current degrees position (extended)
            float currentAngleT0 = ((float)degreesPerSliceT0*i);
            uiVizWidgetChordDesignerSlice *sliceT0 = &circleSlicesT0[i-1];
            setSliceProperties(sliceT0, i, currentAngleT0, mWheelOffest, degreesPerSliceT0, circX, circY, circRadiusXT0, circRadiusYT0, 0, false);
        }
        
        for (int i = 1; i <= circleSlicesT1.size() ; i++) {
            // T1
            // The current degrees position
            float currentAngleT1 = ((float)degreesPerSliceT1*i);
            uiVizWidgetChordDesignerSlice *sliceT1 = &circleSlicesT1[i-1];
            setSliceProperties(sliceT1, i, currentAngleT1, mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, false);
         }
        
        // T2
        for (int j = 1; j <= circleSlicesT2.size(); j++) {
            // The current degrees position T2
            float currentAngleT2 = ((float)degreesPerSliceT2*j);
            uiVizWidgetChordDesignerSlice *sliceT2 = &circleSlicesT2[j-1];
            setSliceProperties(sliceT2, j, currentAngleT2, mWheelOffest, degreesPerSliceT2, circX, circY, circRadiusXT2, circRadiusYT2, 2, false);
        }
        
        circleInner.setCircleResolution(360); // Can lower or remove to bump up performance
        circleInner.setFilled(true);
        circleInner.arc(circX, circY, circRadiusX*INNER_CIRCLE_RADIUS_PERC, circRadiusY*INNER_CIRCLE_RADIUS_PERC, 0, 360);
        vizElm_circleInner.update(circleInner);
        
        circleInnerPoint.set(circX, circY);

       
    }
    
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::IconCache::IconTag::WIDGET_SETTINGS:
                return chordDesignerContextMenu;
            default:
                return nullptr;
        }
    }
    
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT && getUserCanInvokeContextMenu()) {
            showContextMenu(Aquamarine::IconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }

    virtual void setInstrumentRules(ofxXmlSettings rules, bool fireEvent) override {
        uiVizWidgetMusical::setInstrumentRules(rules, fireEvent);
        chordRulesMenuItem->setInstrumentRules(rules, fireEvent);
    }

    virtual void onRulesChanged(uiVizInstrumentRuleArgs &args) override {
        setInstrumentRules(args.rules, false);

        // This will correctly set the drag data (incl rules)
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));

        ofNotifyEvent(rulesChanged, args);
    }
    
    void drawSlice(int tier, int currentSlice, uiVizWidgetChordDesignerSlice &slice) {
        
        slice.path.setColor(slice.regularColor); // Hover
        
        if (getIsActiveWidget()) {
            //---------- Mouse Hit test  ----------
            float dist = ofDist(ofGetMouseX(), ofGetMouseY(), slice.labelPoint.x, slice.labelPoint.y);
            bool sliceHovered = dist <= ((rectFontHitArea.width*1.5f + rectFontHitArea.height*1.5f) / (float)2);


            if ((tier == 2 && !getUserCanSetSelectedKey()) || ((tier == 1 ||  tier == 0) && !getUserCanAddSelectedNote())) {
                sliceHovered = false;
            }

            //bool sliceHovered = slice.getIsMouseHovered(); //TODO FIX!! (gettin' there)
            slice.isHovered = false;
            slice.isSelected = false;
            if (!getIsDragging()) {
                bool sliceMatchesSelectedNote = matchesSelectedNote(slice.note);                
                if (sliceHovered  || sliceMatchesSelectedNote)  {
                    
                    if (sliceHovered) {
                        slice.path.setColor(slice.hoveredColor); // Hover
                        slice.isHovered = true;
                        setHoveredKey(slice.note);
                        if (sliceMatchesSelectedNote) auditionNote(slice.note);

                        
                        if (tier == 2)  { // key
                            slice.isSelected = true;
    
                            
                            if (getUserCanSetSelectedKey() && getIsMousePressedAndReleasedOverWidget(false)) {
                                setSelectedKey(slice.note);
                                uiVizNoteSelectedArgs args("Chord Designer", slice.note);
                                ofNotifyEvent(keySelected, args);
                                ofNotifyEvent(noteSelected, args);
                            }
                        }
                        
                        if (tier == 1 || tier == 0)  { // degrees
                            // do something with the degree
                            if (getUserCanAddSelectedNote() && getIsMousePressedAndReleasedOverWidget(false)) {

/*
                                if (slice.note.isEnharmonicallyEquivalent(getSelectedKey().getNoteNameNormalized())) {

                                }

*/
                                slice.isSelected = true;
                                applyLogicToExistingNotes(slice.note);
                                setUserDefinedChordName("");
                                setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
                                setNeedsUpdate(true);
                                
                                uiVizNoteSelectedArgs args("Chord Designer", slice.note);
                                ofNotifyEvent(noteSelected, args);
                            }
                        }
                        
                    }
                    
                }
            }
        }
        
        slice.path.draw();

        ofPushStyle();
        ofSetColor(getLabelStateColor(slice));
        font->draw(slice.label, slice.labelPoint.x, slice.labelPoint.y);
        ofPopStyle();     
    }
    
    virtual void setUserDefinedChordName(string val) override {
        uiVizWidgetMusical::setUserDefinedChordName(val);
        if(userDefinedChordName) {
            userDefinedChordName->setValue(val, false);
        }
    }

    virtual void setSelectedKey(vizNote val) override {
        // Reselect the degrees, but for the new key (which are different notes)!
        // vizNote oldChordRootNote = getSelectedKey();
        vector<vizNote> tmpNotes = getSelectedNotes(); 
        
        uiVizWidgetMusical::setSelectedKey(val);
        addRootNoteIfNoNotesAdded();
        
        if (tmpNotes.size() > 0) {
            vizNote oldChordRootNote = tmpNotes[0];

            initScale();
            clearSelectedNotes();
            addRootNoteIfNoNotesAdded();
            
            for (int j=0; j<tmpNotes.size(); j++) {
                vizNote oldNote = tmpNotes[j];
                int oldNoteDegree = oldChordRootNote.getInterval(oldNote.getNoteNameNormalized());
                vizNote noteToAdd = val.getCalculatedNoteForOffset(oldNoteDegree, getIsSelectedKeySharp());
                
                noteToAdd.setIsExtended(oldNote.getIsExtended());
                noteToAdd.setNoteOctave(oldNote.getNoteOctave());
                addSelectedNote(noteToAdd, true);
            }
            
            setCalculatedChordName(getChordNameFromSelectedNotesPretty(val, false, true, true));
            setNeedsUpdate(true);
            
        }
        
        
    }
    
    void applyLogicToExistingNotes(vizNote note) {

        // Toggle
        int noteInterval = getSelectedKey().getInterval(note.getNoteName());
        
        if (getSelectedNotes().size() > 0) {
          //  if (noteInterval == 0 && !note.getIsExtended()) return; // don't remove root
        }
        
        matchesSelectedNote(note) ? removeSelectedNote(note, note.getIsExtended()) : addSelectedNote(note, true);

        vector<vizNote> tmpNotes = getSelectedNotes();
        clearSelectedNotes();
        
        // Regular degrees
        for (int degree=0; degree<notesT1.size(); degree++) {
            for (int j=0; j<tmpNotes.size(); j++) {
                if (notesT1[degree].isEnharmonicallyEquivalent(tmpNotes[j].getNoteNameNormalized()) && !tmpNotes[j].getIsExtended()) {
                    addSelectedNote(tmpNotes[j], true);
                }
            }
        }

        //flats / sharps menu option
        
        // Extended degrees
        bool foundExtendedDegree = false;
        for (int degree=0; degree<notesT0.size(); degree++) {
            for (int j=0; j<tmpNotes.size(); j++) {
                if (notesT0[degree].isEnharmonicallyEquivalent(tmpNotes[j].getNoteNameNormalized()) && tmpNotes[j].getIsExtended()) {
                    addSelectedNote(tmpNotes[j], true);
                    foundExtendedDegree = true;
                }
            }
        }

        updateShowExtendedNoteNamesRule(foundExtendedDegree);

/*
        // This logic, is inherintly gammy, think minor 13 chord!!
        if (getShouldValidateChords()) {
            switch(noteInterval) {
                case vizTheory::DegreeName::majorUnison:
                    break;
                case vizTheory::DegreeName::augmentedUnison_minorSecond:
                    break;
                case vizTheory::DegreeName::majorSecond:
                    break;
                case vizTheory::DegreeName::augmentedSecond_minorThird:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::majorThird, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::majorThird, false, getSelectedKey());
                   }
                    break;
                case vizTheory::DegreeName::majorThird:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::augmentedSecond_minorThird, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::augmentedSecond_minorThird, false, getSelectedKey());
                   }
                    break;
                case vizTheory::DegreeName::perfectFourth:
                    break;
                case vizTheory::DegreeName::augmentedFourth_minorFifth:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::perfectFifth, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::perfectFifth, false, getSelectedKey());
                   }
                    break;
                case vizTheory::DegreeName::perfectFifth:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::augmentedFourth_minorFifth, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::augmentedFourth_minorFifth, false, getSelectedKey());
                   }
                    break;
                case vizTheory::DegreeName::augmentedFifth_minorSixth:
                    break;
                case vizTheory::DegreeName::majorSixth:
                    break;
                case vizTheory::DegreeName::augmentedSixth_minorSeventh:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::majorSeventh, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::majorSeventh, false, getSelectedKey());
                   }
                    break;
                case vizTheory::DegreeName::majorSeventh:
                   if (!note.getIsExtended() && vizScale::getIsDegreeFound(vizTheory::DegreeName::augmentedSixth_minorSeventh, getSelectedNotes(), getSelectedKey())) {
                       removeSelectedNoteByDegree(vizTheory::DegreeName::augmentedSixth_minorSeventh, false, getSelectedKey());
                   }
                   
                    break;
                case vizTheory::DegreeName::dominantThirteenth:
                    break;
            }
        }
        */
        setIsExtendedChordMode(determineIfShouldDisplayExtendedChordMode(getSelectedNotes().size()));
    }
    
    bool determineIfShouldDisplayExtendedChordMode(int numNotesSelected) {
        if (numNotesSelected >= 4) {
            return true;
        } else {
            for(auto currNote:getSelectedNotes()) {
                if (currNote.getIsExtended()) return true;
            } 
            return false;
        }
    }

    
    virtual void onWidgetKeyPressed(ofKeyEventArgs &e) override {
        
        uiVizWidgetMusical::onWidgetKeyPressed(e);
        
        int key = e.key;
        
        switch (key) {
                
            case 53: setSelectedScale("ionian", true); break;
            case 54: setSelectedScale("dorian", true); break;
            case 55: setSelectedScale("phrygian", true); break;
            case 56: setSelectedScale("lydian", true); break;
            case 57: setSelectedScale("mixolydian", true); break;
            case 48: setSelectedScale("aeolian", true); break; // 0
            case 45: setSelectedScale("locrian", true); break;  // -
        }
        setNeedsUpdate(true);
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
        
        // Draw the slices
        for(int i=1; i<=circleSlicesT2.size(); i++){
            drawSlice(2, i, circleSlicesT2[i-1]);
        }
        
        for(int i=1; i<=circleSlicesT1.size(); i++){
            drawSlice(1, i, circleSlicesT1[i-1]);
        }
        
        if (getIsExtendedChordMode()) {
            for(int i=1; i<=circleSlicesT0.size(); i++){
                drawSlice(0, i, circleSlicesT0[i-1]);
            }
        }
        
        ofColor keyColor = vizTheory::getColorForKey(getSelectedKey().getNoteName(), 255);
        
        vizElm_circleInner.setColor(keyColor);
        vizElm_circleInner.draw();
        

        string tmpUserDefinedChordName = "";
        if(getUserDefinedChordName() != "") {
            tmpUserDefinedChordName = getSelectedKey().getNoteName() + getUserDefinedChordName();
        }

        string chordName = tmpUserDefinedChordName != "" ? tmpUserDefinedChordName : getCalculatedChordName();
        rectLargeLabel = fontLargeLabel->rect(getLargeLabelText());
        rectScaleNameLabel = fontScaleNameLabel->rect(chordName);
        ofRectangle rectScaleNameLabelHeight = fontScaleNameLabel->rect("Bmaj");
        
        int yLabelOffset = getWidth() > 220 ? rectScaleNameLabelHeight.height + getNonScaledPadding()/2 : 0;
        

        drawFontWithShadow(
            fontLargeLabel, getLargeLabelText(), 
            circleInnerPoint.x - rectLargeLabel.width / 2.0f,
            circleInnerPoint.y + rectLargeLabel.height / 2.0f - yLabelOffset / 2,            
            getSelectedFontColor(getSelectedKey().getNoteName()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));

        if (yLabelOffset > 0 || getSelectedKey().getNoteName() == "") {
            drawFontWithShadow(
                fontScaleNameLabel, chordName, 
                circleInnerPoint.x - rectScaleNameLabel.width / 2.0f,
                circleInnerPoint.y + rectScaleNameLabelHeight.height / 2.0f + yLabelOffset * 1.2f,  
                getSelectedFontColor(getSelectedKey().getNoteName()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));
        }

        editIcon.setScaledPos(scale(getUsableX() + getUsableWidth()) - editIcon.getScaledBounds().width , scale(getUsableY()));
        tickIcon.setScaledPos(scale(getUsableX() + getUsableWidth()) - tickIcon.getScaledBounds().width , scale(getUsableY()));
        //Coord::vizBounds iconBounds = editIcon.getScaledBounds();
        //editIcon.scaleSvg(mUIIconScale, mUIIconScale);
        
        
        // -------------------- Chord renaming --------------------
        if(getIsActiveWidget()) {

            editIcon.setIsVisible(false);
            tickIcon.setIsVisible(false);   

            if (!userDefinedChordName->getIsVisible()) {
                editIcon.setIsVisible(true);
                if(editIcon.isHovered()) {
                    editIcon.setColor(getTheme().TypographySecondaryColor_withAlpha(1));
                    if(userDefinedChordName && getIsMousePressedAndReleasedOverWidget(false)) {
                        userDefinedChordName->setIsVisible(true);
                        userDefinedChordName->setIsFocused(true);
                        setWidgetNeedsUpdate(true);                 
                    }
                } else {
                    editIcon.setColor(getTheme().TypographySecondaryColor_withAlpha(0.8f));
                }
                editIcon.drawSvg();


            } else {
                tickIcon.setIsVisible(true);
                if(tickIcon.isHovered()) {
                    tickIcon.setColor(getTheme().TypographySecondaryColor_withAlpha(1));
                    if(userDefinedChordName && getIsMousePressedAndReleasedOverWidget(false)) {
                        userDefinedChordName->setIsVisible(false);
                        setWidgetNeedsUpdate(true);                 
                    }
                } else {
                    tickIcon.setColor(getTheme().TypographySecondaryColor_withAlpha(0.8f));
                }
                tickIcon.drawSvg();
            }
        }
    }
    
    
    void updateMinimized() override {
        
    }
    
    void drawMinimized() override {
    }
    
    void setSelectedScale(string val, bool includeInstrumentRules) override {
        uiVizWidgetMusical::setSelectedScale(val, includeInstrumentRules);
        initScale();
    }
    

    
    void clearExtendedNotes() {
        for (int degree=0; degree<notesT0.size(); degree++) {
            removeSelectedNote(notesT0[degree], true);
        }
    }
    
    virtual void setIsExtendedChordMode(bool val) override {
        uiVizWidgetMusical::setIsExtendedChordMode(val);
        if (!val) clearExtendedNotes();
        setNeedsUpdate(true);
    }
    
    void addRootNoteIfNoNotesAdded() {
        if (getSelectedNotes().size() == 0) {
            vizNote keyNote = getSelectedKey();
            addSelectedNote(keyNote, true);
        }
    }
    
   
    void addSelectedChord(vizChord &rawChord, bool onlyAddIfNotFound, bool includeInstrumentRules) override {
        // We use the incoming chord's notes, not the actual chord...
        
        vizChord chord = vizChord(rawChord.getChordName(), rawChord.getNotes(), true);
        chord.setInstrumentRules(rawChord.getInstrumentRules());
        setUserDefinedChordName(rawChord.getChordName_UserDefined());

        //if (!chord.isChordValid()) return;
        clearSelectedNotes();
        uiVizWidgetMusical::setSelectedKey(rawChord.getChordRootNote());
        initScale();
      
        for (int j=0; j<chord.getNotes().size(); j++) {
            addSelectedNote(chord.getNotes()[j], true);
        }
        /*

        vector<vizNote> normalizedNotes = getNormalizedNotes(chord.getNotes(), false);

        for (vizNote currNote:normalizedNotes) {
            addSelectedNote(currNote, true);
        }*/

        setIsExtendedChordMode(determineIfShouldDisplayExtendedChordMode(getSelectedNotes().size()));
        
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));

        if(chordRulesMenuItem) {
            chordRulesMenuItem->addSelectedChord(chord, true, true);
        }
    }
    
    
    
    void addSelectedChordByName(string chordName, vizNote key, bool notifyEvents) {
        MusicTheory::ChordPtr chord = MusicTheory::Chord::getChordFromString(chordName);
        if (!vizTheory::isChordValid(chord)) return;
        
        setUserDefinedChordName("");

        clearSelectedNotes();
        
        setSelectedKey(key);
        
        int rootOctave = getSelectedKey().getNoteOctave();
        int numNotes = chord->getAllNotes().size();
        setIsExtendedChordMode(determineIfShouldDisplayExtendedChordMode(numNotes));
        
        int noteNum = 0;
        for (MusicTheory::NotePtr note:chord->getAllNotes()) {
            noteNum++;
            string noteDiatonicName = note->getDiatonicName();
            int noteOctave = note->getOctave();
            vizNote currVizNote(noteDiatonicName, noteOctave, 1);
            int noteInterval = getSelectedKey().getInterval(noteDiatonicName);
            /*
             if (noteNum > 4) {
             currVizNote.setIsExtended(true);
             }*/
            addSelectedNote(currVizNote, true);
        }
        
        calculateExtendedNotesFromCurrentNotes();
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
        if (notifyEvents) {
            uiVizNoteSelectedArgs args("Chord Designer", getSelectedKey());
            ofNotifyEvent(keySelected, args);
            ofNotifyEvent(noteSelected, args);
        }
        
    }
    
    bool hasExtendedDegreeSelected() {
        if (!getIsExtendedChordMode()) return false;
        vector<vizNote> tmpNotes = getSelectedNotesNormalized();
        for (int degree=0; degree<notesT0.size(); degree++) {
            for (int j=0; j<tmpNotes.size(); j++) {
                if (notesT0[degree].isEnharmonicallyEquivalent(tmpNotes[j].getNoteNameNormalized()) && tmpNotes[j].getIsExtended()) {
                    addSelectedNote(tmpNotes[j], true);
                    return true;
                }
            }
        }
        return false;
    }


    void updateShowExtendedNoteNamesRule(bool hasExtendedDegree) {
        deleteInstrumentRule("general", "showExtendedNoteNames");
        if (hasExtendedDegree) {
            setInstrumentRule("general", "showExtendedNoteNames", hasExtendedDegree);
            setInstrumentRules(getInstrumentRules(), false);
        }
    }

    
    void setCalculatedChordName(string val) override {
        uiVizWidgetMusical::setCalculatedChordName(val);
        
        //if (font) setTitle(val + "[" + ofToString(font->size()) + "]-" + ofToString(getUsableWidth()));
        if (font) setTitle(val);
        
        setInstrumentRule_Genericize();

        // Extended degrees?
        bool foundExtendedDegree = hasExtendedDegreeSelected();
        updateShowExtendedNoteNamesRule(foundExtendedDegree);
        

        if (ofToLower(getCalculatedChordName()) != "unknown" && getCalculatedChordName() != "") {
            vizChord dragChord = vizChord(getCalculatedChordName(), getSelectedNotes(), true);
            dragChord.setInstrumentRules(getInstrumentRules());
            if(getUserDefinedChordName() != "") dragChord.setChordName_UserDefined(getUserDefinedChordName());
            setDraggingChord(dragChord);

            addToEventTransmitQueue(
                APP_WIDGET_EVENT::ADD_SELECTED_CHORD, 
                "<event>" + dragChord.getXML() + "</event>"
            ); 

        } else {

            vizChord dragChord = vizChord(getSelectedKey().getNoteName(), getSelectedNotes(), true);
            dragChord.setInstrumentRules(getInstrumentRules());
            if(getUserDefinedChordName() != "") dragChord.setChordName_UserDefined(getUserDefinedChordName());
            setDraggingChord(dragChord);

            addToEventTransmitQueue(
                APP_WIDGET_EVENT::ADD_SELECTED_CHORD, 
                "<event>" + dragChord.getXML() + "</event>"
            ); 
        }
        
    }
    
    void clearSelectedNotesAndInitWithUnknown() {
        clearSelectedNotes();
        addRootNoteIfNoNotesAdded();
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
        setNeedsUpdate(true);
    }

    uiVizWidgetChordRules* getChordRulesMenuItem() {
        return chordRulesMenuItem;
    }
    
    enum MENU_GROUP_1 {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_NOTE_MODE = 2,
        MENU_TAB_CHORD_SCALE = 3,
        MENU_TAB_CHORD = 4,
        MENU_TAB_SETTINGS = 5,
        MENU_TAB_CHORD_RULES = 6
    };

    
private:
    Aquamarine::uiVizWidget *chordDesignerContextMenu = nullptr;
    uiVizWidgetChordRules* chordRulesMenuItem = nullptr;

    Aquamarine::uiVizWidgetElmTextbox *userDefinedChordName = nullptr;
    Aquamarine::Icon editIcon;
    Aquamarine::Icon tickIcon;

    bool mShouldValidateChords = true;
    
    
    vector<vizNote> notesT0;
    vector<vizNote> notesT1;
    vector<vizNote> notesT2;
    
    float INNER_CIRCLE_RADIUS_PERC = 0.4f;
    float TIER0_RADIUS_PERC = 0.615f; // extended degrees  40+(83-40)/2 = 61.5
    float TIER1_RADIUS_PERC = 0.83f;  // standard degrees
    float TIER2_RADIUS_PERC = 1.0f;

    int mAngleOffsetForDegreesSlices = 0;
    
    vector<uiVizWidgetChordDesignerSlice> circleSlicesT0;
    vector<uiVizWidgetChordDesignerSlice> circleSlicesT1;
    vector<uiVizWidgetChordDesignerSlice> circleSlicesT2;
    
    shared_ptr<ofxSmartFont> font;
    shared_ptr<ofxSmartFont> fontLargeLabel;
    shared_ptr<ofxSmartFont> fontScaleNameLabel;
    
    
    ofPath circleInner;
    Aquamarine::Elm vizElm_circleInner;
    ofRectangle rectLargeLabel;
    ofRectangle rectScaleNameLabel;
    ofColor largeLabelColor;
    ofRectangle rectFontHitArea;
    ofPoint circleInnerPoint;
    
    float degreesOffset = 0;
    float mWheelOffest = 0;
    float mT1AngleOffest = 0;
    float mUnfocusedNoteBrightness = 155.0;
    float mFocusedNoteBrghtness = 100;

    
    // Set up the slices with Notes data (colors, degrees, etc)
    void initScale() {
        
        notesT0 = vizScale::getNotesForScale(getSelectedKey().getNoteName(), "chromatic", 4); // all the extended degrees of the scale (inner
        notesT1 = vizScale::getNotesForScale(getSelectedKey().getNoteName(), "chromatic", 3); // all the degrees of the scale (inner ring)
        
        switch(getTheoryVizNoteMode()) {
            case TheoryVizNoteMode::DEFAULT:
                notesT2 = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::DEFAULT); break;
            case TheoryVizNoteMode::SHARP:
                notesT2 = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::SHARP); break;
            case TheoryVizNoteMode::FLAT:
                notesT2 = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::FLAT); break;
            default:
                notesT2 = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::DEFAULT); break;
        }
        
        
        circleSlicesT0.clear();
        circleSlicesT1.clear();
        circleSlicesT2.clear();
        
        float degreesOffset = getAngleOffsetForSlice(1);
        mWheelOffest = degreesOffset;
    
        for (int degree=0; degree<notesT0.size(); degree++) {
            uiVizWidgetChordDesignerSlice sliceT0;
            notesT0[degree].setNoteOctave(4);
            sliceT0.note = notesT0[degree];
            sliceT0.note.setIsExtended(true);
            circleSlicesT0.push_back(sliceT0);
        }
        
        for (int degree=0; degree<notesT1.size(); degree++) {
            uiVizWidgetChordDesignerSlice sliceT1;
            notesT1[degree].setNoteOctave(3);
            sliceT1.note = notesT1[degree];
            circleSlicesT1.push_back(sliceT1);
            if (degree == 0) addSelectedNote(sliceT1.note, true);
        }
        
        for (int key=0; key<notesT2.size(); key++) {
            uiVizWidgetChordDesignerSlice sliceT2;
            sliceT2.note = notesT2[key];
            circleSlicesT2.push_back(sliceT2);
        }
        
        setTitle(getCalculatedChordName());
        setNeedsUpdate(true);
    }

    virtual void setTitle(string title) override {
        if(getUserDefinedChordName() != "") {
            uiVizWidget::setTitle(getSelectedKey().getNoteName() + getUserDefinedChordName());
        } else {
            uiVizWidget::setTitle(title);
        }
    }

    vector<Aquamarine::uiVizWidgetMenuItem> getChordsMenuItems() {
        vector<Aquamarine::uiVizWidgetMenuItem> chordsMenuItems = { };
        vector<string> chords = MusicTheory::Chord::getAllKnownChords();
        
        for (int i=0; i<chords.size(); i++) {
            chordsMenuItems.push_back(
               Aquamarine::uiVizWidgetMenuItem(chords[i], i, false, i==0)
            );
        }
        return chordsMenuItems;
    }
    
    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        uiVizWidgetMusical::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (userDefinedChordName && args.sender.getPersistentId() == userDefinedChordName->getPersistentId()) {
            setUserDefinedChordName(userDefinedChordName->getValue());
            setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
        }
    }

    void initWidget() override {
        
        
        editIcon = Aquamarine::IconCache::getIcon("MED_CONTENT_EDIT");
        tickIcon = Aquamarine::IconCache::getIcon("MED_CONTENT_TICK");
        editIcon.setIsVisible(true);
        tickIcon.setIsVisible(false);

        if (!userDefinedChordName) {
            userDefinedChordName = dynamic_cast<Aquamarine::uiVizWidgetElmTextbox*>(addOrLoadWidgetElement(userDefinedChordName, Aquamarine::WIDGET_ELM_CLASS::TEXTBOX, getPersistentId() + "_customChordName", R"(
                <element>
                </element>
                )"));

            userDefinedChordName->setX_Expr("${PARENT.LEFT}+${PADDING}");
            userDefinedChordName->setY_Expr("${PARENT.TOP}+${PADDING}");
            userDefinedChordName->setHeight_Expr("30");
            userDefinedChordName->setWidth_Expr("${PARENT.USABLE_WIDTH}-${PADDING}*2-25");
            userDefinedChordName->setTitle("Chord name...");
            userDefinedChordName->setMaxLength(7);
            userDefinedChordName->setShouldPersist(false);
            userDefinedChordName->setIsVisible(false);

        }


        if (getSelectedKey().getNoteName() == "") {
            vizNote defaultKey = vizNote("C", 3, 0, vector<string>{});
            
            uiVizWidgetMusical::setSelectedKey(defaultKey);
            
            if (getSelectedScaleName() == "") {
                setSelectedScale("chromatic", true);
            }
            
            initScale();
            
            
            addSelectedChordByName("CM", defaultKey, false);
            setNeedsUpdate(true);
        }
        


        setTheoryVizColorMode(TheoryVizColorMode::KEYS);
        setTheoryVizLabelMode(TheoryVizLabelMode::DEGREES);
        if (!chordDesignerContextMenu) {

            chordRulesMenuItem = new uiVizWidgetChordRules(
                getWidgetId() + "_MENU_CHORD_RULES",
                "<widget><bounds minWidth='300' minHeight='400'/><appearance/></widget>"
            );

            chordRulesMenuItem->setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode::CHORD);

            ofAddListener(chordRulesMenuItem->rulesChanged, this,  &uiVizWidgetChordDesigner::onRulesChanged);

            chordDesignerContextMenu = new Aquamarine::uiVizWidgetMenu(getWidgetId() + "_CD_MENU1", "<widget><bounds width='100' height='300'/></widget>", getWidgetId()
            , Aquamarine::uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                
                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("LABEL"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("NONE"), (int)TheoryVizLabelMode::NONE),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                }),
                
                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("COLOR"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("NONE"), (int)TheoryVizColorMode::NONE),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                    //Aquamarine::uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                }),
                
                
                // ----------------------------------------------------------------------------
                // Note mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("NOTE_MODE"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_NOTE_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("DEFAULT"), (int)TheoryVizNoteMode::DEFAULT, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("SHARP"), (int)TheoryVizNoteMode::SHARP),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("FLAT"), (int)TheoryVizNoteMode::FLAT)
                }),
                
                // ----------------------------------------------------------------------------
                // Chords menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("CHORDS"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_SCALE"), MENU_GROUP_1::MENU_TAB_CHORD,
                                    getChordsMenuItems()
                                    ),

                // ----------------------------------------------------------------------------
                // Chord Rules menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("CHORD_RULES"), Aquamarine::IconCache::getIcon("MED_CONTENT_RULES"),
                                MENU_GROUP_1::MENU_TAB_CHORD_RULES,
                                chordRulesMenuItem
                                ),                                    
                
                // ----------------------------------------------------------------------------
                
                // Settings menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::Shared::lang("SETTINGS"), Aquamarine::IconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("SOUND"), 1, true, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::Shared::lang("SAVE"), 2)
                })
                
            });
    
            ofAddListener(dynamic_cast<Aquamarine::uiVizWidgetMenu*>(chordDesignerContextMenu)->menuItemSelected, this, &uiVizWidgetChordDesigner::onMenuItemSelected);

        // addChildWidget(*chordDesignerContextMenu); // bug when not using below line, this submenu diesnt display when this widget (itself) is a child widget!! - ie from the fretboard
            Aquamarine::WidgetManager::addWidget(*chordDesignerContextMenu, false, getWidgetId());
        }

        setIsAutoUpdateWhenActive(true);
    }
    
    void auditionChord(bool visually, bool audibly) {
        // Todo playback created chord
    }
    
    int getUsableHeight() override {
        if(userDefinedChordName && userDefinedChordName->getIsVisible()) {
            return uiVizWidgetMusical::getUsableHeight() - userDefinedChordName->getHeight() - getScaledPadding();
        } else {
            return uiVizWidgetMusical::getUsableHeight();
        }
    }

    int getUsableY_Custom() {
        if(userDefinedChordName && userDefinedChordName->getIsVisible()) {
            return uiVizWidgetMusical::getUsableY() + userDefinedChordName->getHeight() + getScaledPadding();
        } else {
            return uiVizWidgetMusical::getUsableY();
        }
    }

    
    /*
     MAJOR BUGS
     
     
     
     1.) everything here seems to be sharps, find the correct logic of WHEN to use a sharp and when to use a flat in a chord and fix! This applies to the following functions:
     getCalculatedNoteForOffset and applies to the fretboard as well as the chord designer (and eventually chord bucket)
     - the chord designer - when showing Keys, shows only sharps!
     - the fretboard - when showing notes dragged
     drad to and from chord bucket  (fretboard)
     drad to and from chord designer  (fretboard)
     

     
     2.) CAN WE USE ROMAN NOTATION in chord library
     chord bucket context menu : transpose !
     chord bucket: show exended notes
     chord bucket: show correct flat / sharp notes ...




    save / laod state chord designer

     0.)
     extended still not working -------------------------------------------------------
     D#maj6 drag from chord bucket to chord designer fine, but to fretboard - show's 13- an example of a 4 note chord which as NO EXTENDED NOTES!!
     
     
     problem chords :
     PROBLEM TYPE 1 (the flat 3 incrorrectly classified as #9) :
     classic example! : m7 - b3 moves to #9 !!, m9, m9 / 11
     
     PROBLEM TYPE 2:
     m11b5, m13, m6/9, m6/9/11
     
     PROBLEM TYPE 3:
     incorrectly the bii is used instead of b9
     sus4b9
     susb9
     
     ----------------------------------------------------------------------------------
     */
    
    void onMenuItemSelected(Aquamarine::uiVizWidgetMenuItemArgs & args) {
        
        switch(args.activeMenuTabId) {
                
            case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE:
                if (((TheoryVizLabelMode)args.menuItem->uniqueID == TheoryVizLabelMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedKey().getNoteName() == "") {
                }
                
                if (args.menuItem->uniqueID == -1000) {
                    setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES);
                } else {
                    setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode::NONE);
                    setTheoryVizLabelMode((TheoryVizLabelMode)args.menuItem->uniqueID);
                }
                
                setNeedsUpdate(true);
                break;
                
            case MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE:
                if (((TheoryVizColorMode)args.menuItem->uniqueID == TheoryVizColorMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedKey().getNoteName() == "") {
     
                }
                
                
                if (args.menuItem->uniqueID == -1000) {
                    setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES);
                } else {
                    setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode::NONE);
                    setTheoryVizColorMode((TheoryVizColorMode)args.menuItem->uniqueID);
                }
                
                setNeedsUpdate(true);
                break;
                
            case MENU_GROUP_1::MENU_TAB_THEORY_NOTE_MODE:
                setTheoryVizNoteMode((TheoryVizNoteMode)args.menuItem->uniqueID);
                initScale();
                setNeedsUpdate(true);
                break;
                
            case MENU_GROUP_1::MENU_TAB_CHORD: {
                string proposedChord = getSelectedKey().getNoteName() + args.menuItem->label;
                addSelectedChordByName(proposedChord, getSelectedKey(), true);
                break;
            }
                
        }
        
    }
    
    ofColor getLabelStateColor(uiVizWidgetChordDesignerSlice slice) {
        if (slice.isHovered)  {
            return slice.hoveredFontColor;
        } else if (slice.isSelected) {
            return slice.selectedFontColor;
        } else {
            return slice.regularFontColor;
        }
    }
    
    string getLargeLabelText() {
        if (getSelectedKey().getNoteName() != "") {
            return getSelectedKey().getNoteName();
        }
        return "";
    }
    
    float getAngleOffsetForSlice(int sliceNumber) {
        float degreesPerSlice = 360 / (float)notesT2.size();
        return 270 - degreesPerSlice - (degreesPerSlice / (float)2) - ((sliceNumber - 1) * (float)degreesPerSlice);
    }
    
    int getGetAngleOffsetForDegreesSlices() {
        return mAngleOffsetForDegreesSlices;
    }
    
    void setGetAngleOffsetForDegreesSlices(int val) {
        mAngleOffsetForDegreesSlices = val;
    }
    
    bool getShouldValidateChords() {
        return mShouldValidateChords;
    }

    void setShouldValidateChords(bool val) {
        mShouldValidateChords = val;
    }
    
};


/* todo
 Chord dictionary
 Drag data
 fix more chord types
 # / b / default notes mode (plus xml persist)
 missing chord types (MusicTheory::Chord)
 Start on chromatic (always use) - the selected scale simply highlights the correct notes
 Selectign note marks it with a white dot
fix middle white dot when dragging chord
 
 
 chord rule (per instrument type)
 stringed instrument - one note per string
 

 store degree with vizNote
 highlight
 spin (1,3,5 then 2,4,6 then 3,5,7)
 spin key initially!

 https://en.wikibooks.org/wiki/Music_Theory/Complete_List_of_Chord_Patterns
 
 Major
 Notes    Full Name    Abbreviations    Scale/Mode
 1 3 5    major    major, (none), M    Ionian
 1 3 (5) 7    major seventh    maj7, Δ7, ma7, M7, Δ    Ionian
 1 3 (5) 7 9    major ninth    maj9    Ionian
 1 3 (5) 7 (9) (11) 13    major thirteenth    maj13    Ionian
 1 3 (5) 6    sixth    6, add6, add13    Ionian
 1 3 (5) 6 9    sixth/ninth    6/9, 69    Ionian
 1 3 (5) (7) ♯11 (9,13..)    lydian    maj♯4, Δ♯4, Δ♯11    Lydian
 1 3 (5) (7) (9) (b13), (11)    major seventh ♭6, or b13    maj7♭6, ma7♭6, M7♭6    Harmonic Maj

 
 
 
 
 Dominant/Seventh
 Normal
 
 Notes    Full Name    Abbreviations    Scale/Mode
 1 3 (5) ♭7    dominant seventh    7, dom    Mixolydian
 1 3 (5) ♭7 9    dominant ninth    9    Mixolydian
 1 3 (5) ♭7 (9) 13    dominant thirteenth    13    Mixolydian
 1 3 (5) ♭7 ♯11 (9,13..)    lydian dominant seventh    7♯11, 7♯4    Lydian Dominant (melodic minor 4th mode)
 The dominant seventh is sometimes just called the "seventh", even though it contains a minor seventh and not a major seventh.
 
 Altered
 
 Notes    Full Name    Abbreviations    Scale/Mode
 1 3 (5) ♭7 ♭9 (♯9,♭5,6..)    dominant ♭9    7♭9    Half-tone/tone (8 note scale), 1/2 step/whole step Diminished scale, Octatonic scale.
 1 3 (5) ♭7 ♯9    dominant ♯9    7♯9    Mixolydian with ♭3
 1 3 ♭7 (♭9) (♭5,♭6,♯9..)    altered    alt7    Locrian ♭4 (super-locrian)
 Suspended
 
 Notes    Full Name    Abbreviations    Scale/Mode
 1 4 (5)    suspended 4th    sus4    Usually mixolydian
 1 2 (5)    suspended 2nd    sus2    Usually mixolydian
 1 4 (5) ♭7    suspended 4th seventh    7sus4    Usually mixolydian
 1 (5) ♭7 (9) 11    eleventh    11, sus, Bb/C for C11    Usually mixolydian
 1 4 (5) ♭7 (9) 11    eleventh (special voicing)    11    Mixolydian
 1 4 (5) ♭9    suspended 4th ♭9    ♭9sus, phryg    Phrygian or phrygian ♯6
 
 
 
 
 Minor
 Normal
 
 Notes    Full Name    Abbreviations    Scale/Mode
 1 ♭3 5    minor    min, m, -    Dorian or aeolian
 1 ♭3 (5) ♭7    minor seventh    mi7, min7, m7, -7    Dorian or aeolian
 1 ♭3 (5) 7 (9, 13)    minor/major seventh    m/ma7, m/maj7, mM7, m/M7, -Δ7, mΔ    Minor melodic (ascending)
 1 ♭3 (5) 7 (9, b13)    minor/major seventh    m/ma7, m/maj7, mM7, m/M7, -Δ7, mΔ    Harmonic Minor
 1 ♭3 (5) 6    minor sixth    m6    Dorian
 1 ♭3 (5) ♭7 9    minor ninth    m9    Dorian or aeolian
 1 ♭3 (5) ♭7 (9) 11    minor eleventh    m11    Dorian or aeolian
 1 ♭3 (5) ♭7 (9) 13    minor thirteenth    m13    Dorian
 Diminished
 
 Notes    Full Name    Abbreviations    Scale/Mode
 1 ♭3 ♭5    diminished    dim, °    Tone/Half-tone (8 note scale)
 1 ♭3 ♭5 ♭♭7    diminished seventh    dim7, °, °7    Tone/Half-tone (8 note scale)
 1 ♭3 ♭5 ♭7 (♭9 or 9,11,13..)    half-diminished    m7♭5, ø    Locrian or locrian ♯2

 
 
 Other
 Notes    Full Name    Abbreviations    Scale/Mode
 1 5    fifth    5, (no 3rd)    None
 1 3 ♯5    augmented    aug, +    Whole tone (6 note scale)
 1 3 ♯5 7    augmented seventh    7♯5, maj7+5    Whole tone (6 note scale)

 
 9th, 11th, and 13th chords
 
 Notes    Full Name    Abbreviation
 1 3 (5) 7 9 ♯11    major ♯11 (lydian)    maj7♯11, Δ♯11, Δ♯4
 1 3 (5) ♭7 ♯9    dominant ♯9    7♯9
 1 4 (5) ♭7 ♭9    suspended ♭9 (phrygian)    ♭9sus
 1 3 (5) ♭7 ♭9 ♯9 ♯11 b13    dominant altered (super-locrian)    7alt, alt

 
 
 
 Polychords
 
 Notes    Polychord notation    Voicing for
 2 ♯4 6 | 1 3 7    D|Cmaj7    Cmaj13(♯11)
 2 ♯4 6 | 1 3 ♭7    D|C7    C13(♯11)
 6 b2 3 | 1 3 ♭7    A|C7    C13(♭9)
 ♯4 7 b2 | 1 3 ♭7    F♯7|C(bass)    C7♭9♭5
 ♭6 1 ♭3 | 1 3 ♭7    Ab|C7    C7alt = C7(#5,#9)
 ♭7 2 4 | 1 3 ♭5    Bb|Cdim    Cø11
 5 ♭7 2 | 1 b 5    Gm|C    C9
 5 7 2 | 1 b 5    G|C    Cmaj9
 5 ♭7 2 | 1 b 5    Gm|Cm    Cm9
 5 7 2 | 1 ♭3 5    G|Cm    Cm,maj9

 
 
 
 Quartal Chords
 Some arrangements use chords based on fourths, often two fourths in the upper notes with an independent bass, which gives the following possibilities:
 
 Notes    Suggested notation    Voicing for
 ♭7 b10 b13 / 1    B♭7sus4/C    Cm7♭6(aeolian)
 4 ♭7 b10 / 1 (5)    F7sus4/C    Cm11
 1 4 ♭7 / 1 (5)    C7sus4/C    C7sus4
 5 8 11 / 1 (5)    G7sus4/C    Csus4
 2 5 8 / 1 (5)    D7sus4/C    Csus2
 6 9 12 / 1 (5)    A7sus4/C    C6sus2
 3 6 9 / 1 (5)    E7sus4/C    C69
 7 10 13 / 1 (5)    ♭7sus4/C    Cmaj13
 ♯4 7 10 / 1 (5)    F♯7sus4/C    Cmaj13♯11

 
*/
