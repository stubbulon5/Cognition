//
//  uiVizWidgetScalePicker_h
//  bloom-macos
//
//
#pragma once
#include "../uiViz/widget/uiVizWidgetMenu.h"
#include "../uiViz/widget/uiVizWidgetTable.h"
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetScaleTable.h"
#include "uiVizWidgetChordRules.h"

class uiVizWidgetScalePickerSlice {
public:
    vizNote note;
    uiVizElm path;
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
    
    ~uiVizWidgetScalePickerSlice() {
    }
    
};

class uiVizWidgetScalePicker : public uiVizWidgetMusical {
    
public:
    
    uiVizWidgetScalePicker(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        if (getSelectedScaleName() != "" && getSelectedScaleName() != "unknown") {
            explicityPickedScaleName = getSelectedScaleName();
            addSelectedScaleByName(getSelectedScaleName(), getSelectedKey(), false);  
        } else {
            setCalculatedScaleName(getScaleNameFromSelectedNotesPretty(getSelectedKey(), false, false));
        }
        
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_SCALE_PICKER, 0);
        return mWidgetXML;
    }
    
    virtual ~uiVizWidgetScalePicker() {

      try {  
            if (scaleRulesMenuItem != nullptr) {
                ofRemoveListener(scaleRulesMenuItem->rulesChanged, this,  &uiVizWidgetScalePicker::onRulesChanged);
            }

            circleSlicesT1.clear();
            circleSlicesT2.clear();
                        
            if (scalePickerContextMenu != nullptr) {
                scalePickerContextMenu->deleteThisWidget();
            }

        } catch(...) {
            cout << "~uiVizWidgetScalePicker() error removing listeners. Have they already been removed? ";
        }

    }

    
    void setSliceProperties(uiVizWidgetScalePickerSlice *slice,
                            int currentSlice, float currentAngle, float angleOffset, float degreesPerSlice,
                            float circX, float circY, float circRadiusX, float circRadiusY, int tier, bool forceHiglight) {

        ofColor color;
        
        
        switch(tier) {
            case 0:
            case 1: // relative degree color

                if (getSelectedKey().getNoteName() != "") {  
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
        float distanceFromCentre = 0.73f;
        
        
        switch(tier) {
            case 1: distanceFromCentre = 0.73f; break;
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
                            slice->label = getSelectedKey().getNoteNameRoman(slice->note.getNoteName());
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
        if (getDraggingScale().getName() != "") {
            setDragData(getDraggingScale().getXML());
        }
    }
    
    void update(uiVizWidgetContext context) override {
        
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
        float circY = scale(getUsableY() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth() /2.0f);
        float circRadiusY = scale(getUsableHeight()/2.0f);

        float degreesPerSliceT1 = 360 / (float)notesT1.size();
        float degreesPerSliceT2 = 360 / (float)notesT2.size();
        
        float circRadiusXT1 = circRadiusX * TIER1_RADIUS_PERC;
        float circRadiusYT1 = circRadiusY * TIER1_RADIUS_PERC;
        
        float angleOffset = 0; //degreesPerSliceT2 / (float)2;
        float circRadiusXT2 = circRadiusX * TIER2_RADIUS_PERC;
        float circRadiusYT2 = circRadiusY * TIER2_RADIUS_PERC;
        
        for (int i = 1; i <= circleSlicesT1.size() ; i++) {
            // T1
            // The current degrees position
            float currentAngleT1 = ((float)degreesPerSliceT1*i);
            uiVizWidgetScalePickerSlice *sliceT1 = &circleSlicesT1[i-1];
            setSliceProperties(sliceT1, i, currentAngleT1, mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, false);
         }
        
        // T2
        for (int j = 1; j <= circleSlicesT2.size(); j++) {
            // The current degrees position T2
            float currentAngleT2 = ((float)degreesPerSliceT2*j);
            uiVizWidgetScalePickerSlice *sliceT2 = &circleSlicesT2[j-1];
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
            case uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return scalePickerContextMenu;
            default:
                return nullptr;
        }
    }
    
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {
            showContextMenu(uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }

    virtual void setInstrumentRules(ofxXmlSettings rules, bool fireEvent) override {
        uiVizWidgetMusical::setInstrumentRules(rules, fireEvent);        
        scaleRulesMenuItem->setInstrumentRules(rules, fireEvent);
    }

    virtual void onRulesChanged(uiVizInstrumentRuleArgs &args) override {
        setInstrumentRules(args.rules, false);
        // This will correctly set the drag data (incl rules)
        setCalculatedScaleName(getScaleNameFromSelectedNotesPretty(getSelectedKey(), false, false));

        ofNotifyEvent(rulesChanged, args);
    }    

    
    void drawSlice(int tier, int currentSlice, uiVizWidgetScalePickerSlice &slice) {
        
        slice.path.setColor(slice.regularColor); // Hover
        
        if (getIsActiveWidget()) {
            //---------- Mouse Hit test  ----------
            float dist = ofDist(ofGetMouseX(), ofGetMouseY(), slice.labelPoint.x, slice.labelPoint.y);
            bool sliceHovered = dist <= ((rectFontHitArea.width*1.5f + rectFontHitArea.height*1.5f) / (float)2);
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
    
                            
                            if (getIsMousePressedAndReleasedOverWidget(false)) {
                                setSelectedKey(slice.note);
                                uiVizNoteSelectedArgs args("Scale Picker", slice.note);
                                ofNotifyEvent(keySelected, args);
                                ofNotifyEvent(noteSelected, args);
                            }
                        }
                        
                        if (tier == 1 || tier == 0)  { // degrees
                            // do something with the degree
                            if (getIsMousePressedAndReleasedOverWidget(false) && !slice.note.isEnharmonicallyEquivalent(getSelectedKey().getNoteNameNormalized())) {
                                explicityPickedScaleName = "";
                                slice.isSelected = true;
                                applyLogicToExistingNotes(slice.note);
                                setCalculatedScaleName(getScaleNameFromSelectedNotesPretty(getSelectedKey(), false, false));
                                setNeedsUpdate(true);
                                
                                
                                uiVizNoteSelectedArgs args("Scale Picker", slice.note);
                                ofNotifyEvent(noteSelected, args);
                            }
                        }
                        
                    }
                    
                }
            }
        }
        
        ofPushStyle();           
        ofSetColor(getLabelStateColor(slice));        
        slice.path.draw();

        font->draw(slice.label, slice.labelPoint.x, slice.labelPoint.y);
        ofPopStyle();           
    }
    
    virtual void setSelectedKey(vizNote val) override {
        // Reselect the degrees, but for the new key (which are different notes)!
        vector<vizNote> tmpNotes = getSelectedNotes();
        
        uiVizWidgetMusical::setSelectedKey(val);
        addRootNoteIfNoNotesAdded();
        
        if (tmpNotes.size() > 0) {
            vizNote oldScaleRootNote = tmpNotes[0];

            initScale();
            clearSelectedNotes();
            addRootNoteIfNoNotesAdded();
            
            for (int j=0; j<tmpNotes.size(); j++) {
                vizNote oldNote = tmpNotes[j];
                int oldNoteDegree = oldScaleRootNote.getInterval(oldNote.getNoteNameNormalized());
                vizNote noteToAdd = val.getCalculatedNoteForOffset(oldNoteDegree, getIsSelectedKeySharp());
                addSelectedNote(noteToAdd, true);
            }
            
            if (explicityPickedScaleName != "") {
                setCalculatedScaleName(explicityPickedScaleName);
            } else {
                setCalculatedScaleName(getScaleNameFromSelectedNotesPretty(val, false, false));
            }

            

            vizScale targetScale = vizScale(getSelectedKey().getNoteName(), getCalculatedScaleName(), getSelectedNotes());
            uiVizWidgetMusical::setSelectedScale(targetScale, true);

            
            setNeedsUpdate(true);
            
        }
    }

    void applyLogicToExistingNotes(vizNote note) {

        // Toggle
        int noteInterval = getSelectedKey().getInterval(note.getNoteName());
        
        if (getSelectedNotes().size() > 0) {
            if (noteInterval == 0 && !note.getIsExtended()) return; // don't remove root
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

        setSelectedKey(getSelectedKey());
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
    
    void draw(uiVizWidgetContext context) override {
        
        // Draw the slices
        for(int i=1; i<=circleSlicesT2.size(); i++){
            drawSlice(2, i, circleSlicesT2[i-1]);
        }
        
        for(int i=1; i<=circleSlicesT1.size(); i++){
            drawSlice(1, i, circleSlicesT1[i-1]);
        }

        ofColor keyColor = vizTheory::getColorForKey(getSelectedKey().getNoteName(), 255);
        
        vizElm_circleInner.setColor(keyColor);
        vizElm_circleInner.draw();
        
        string scaleName = getCalculatedScaleName();
        rectLargeLabel = fontLargeLabel->rect(getLargeLabelText());
        rectScaleNameLabel = fontScaleNameLabel->rect(scaleName);
        ofRectangle rectScaleNameLabelHeight = fontScaleNameLabel->rect("Bmaj");
        
        int yLabelOffset = getWidth() > 220 ? rectScaleNameLabelHeight.height + getNonScaledPadding()/2 : 0;
        
        drawFontWithShadow(
            fontLargeLabel, getLargeLabelText(), 
            circleInnerPoint.x - rectLargeLabel.width / 2.0f,
            circleInnerPoint.y + rectLargeLabel.height / 2.0f - yLabelOffset / 2,            
            getSelectedFontColor(getSelectedKey().getNoteName()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));

        if (yLabelOffset > 0 || getSelectedKey().getNoteName() == "") {
            drawFontWithShadow(
                fontScaleNameLabel, scaleName, 
                circleInnerPoint.x - rectScaleNameLabel.width / 2.0f,
                circleInnerPoint.y + rectScaleNameLabelHeight.height / 2.0f + yLabelOffset * 1.2f,  
                getSelectedFontColor(getSelectedKey().getNoteName()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));
        }


    }
    
    
    void updateMinimized() override {
        
    }
    
    void drawMinimized() override {
    }
    
    virtual void setSelectedScale(vizScale val, bool includeInstrumentRules) {
        uiVizWidgetMusical::setSelectedScale(val, includeInstrumentRules);

        addSelectedScaleByName(val.getName(), val.getKey(), false);

       if(scaleRulesMenuItem) {
            scaleRulesMenuItem->setSelectedScale(val, includeInstrumentRules);
        }       
    }

    void setSelectedScale(string val, bool includeInstrumentRules) override {
        uiVizWidgetMusical::setSelectedScale(val, includeInstrumentRules);
        
        if(scaleRulesMenuItem) {
            scaleRulesMenuItem->setSelectedScale(val, includeInstrumentRules);
        }        
        
        initScale();
    }
    
    void addRootNoteIfNoNotesAdded() {
        if (getSelectedNotes().size() == 0) {
            vizNote keyNote = getSelectedKey();
            addSelectedNote(keyNote, true);
        }
    }
    
    void addSelectedScaleByName(string scaleName, vizNote key, bool notifyEvents) {
        shared_ptr<MusicTheory::Scale> scale = MusicTheory::Scale::scaleFromDictionary(scaleName, key.getNote());
        
        clearSelectedNotes();
        
        if (!scale) {
            return;
        }

        int noteNum = 0;
        for (MusicTheory::NotePtr note:scale->notes) {
            noteNum++;
            string noteDiatonicName = note->getDiatonicName();
            int noteOctave = note->getOctave();

            vizNote currVizNote(noteDiatonicName, noteOctave, 1);
            int noteInterval = getSelectedKey().getInterval(noteDiatonicName);
            addSelectedNote(currVizNote, true);
        }

        setSelectedKey(key);

        // string calculatedScaleName = getScaleNameFromSelectedNotesPretty(getSelectedKey(), false, false);
        string calculatedScaleName = scale->name;
        setCalculatedScaleName(calculatedScaleName);

        vizScale targetScale = vizScale(getSelectedKey().getNoteName(), calculatedScaleName, getSelectedNotes());
        uiVizWidgetMusical::setSelectedScale(targetScale, true);


        if (notifyEvents) {
            uiVizNoteSelectedArgs args("Scale Picker", getSelectedKey());
            ofNotifyEvent(keySelected, args);
            ofNotifyEvent(noteSelected, args);
        }
        
        setWidgetNeedsUpdate(true);
    }
    
    
    void setCalculatedScaleName(string val) override {
        uiVizWidgetMusical::setCalculatedScaleName(val);

        string scale = "";

        if (explicityPickedScaleName != "") {
            setTitle(val);
            scale = val;
        } else {
            string selectedScaleName = getScaleNameFromSelectedNotesPretty(val, false, false);
            setTitle(selectedScaleName);
            scale = selectedScaleName;
        }

        if (ofToLower(scale) != "unknown" && scale != "") {
            vizScale dragScale = vizScale(getSelectedKey().getNoteName(), scale);
            dragScale.setInstrumentRules(getInstrumentRules());
            setDraggingScale(dragScale);
        } else {
            clearDraggingScale();
        }
        
    }
    
    void clearSelectedNotesAndInitWithUnknown() {
        clearSelectedNotes();
        addRootNoteIfNoNotesAdded();
        setCalculatedScaleName(getScaleNameFromSelectedNotesPretty(getSelectedKey(), false, false));
        setNeedsUpdate(true);
    }
    
    
    enum MENU_GROUP_1 {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_NOTE_MODE = 2,
        MENU_TAB_SCALE = 3,
        MENU_TAB_SETTINGS = 4,
        MENU_TAB_SCALE_RULES = 5        
    };
    
private:
    uiVizWidgetMenu *scalePickerContextMenu = nullptr;
    uiVizWidgetChordRules* scaleRulesMenuItem = nullptr;    

    vector<vizNote> notesActualScale;
    vector<vizNote> notesT1;
    vector<vizNote> notesT2;
    
    float INNER_CIRCLE_RADIUS_PERC = 0.4f;
    float TIER0_RADIUS_PERC = 0.615f; // extended degrees  40+(83-40)/2 = 61.5
    float TIER1_RADIUS_PERC = 0.83f;  // standard degrees
    float TIER2_RADIUS_PERC = 1.0f;

    int mAngleOffsetForDegreesSlices = 0;

    vector<uiVizWidgetScalePickerSlice> circleSlicesT1;
    vector<uiVizWidgetScalePickerSlice> circleSlicesT2;
    
    shared_ptr<ofxSmartFont> font;
    shared_ptr<ofxSmartFont> fontLargeLabel;
    shared_ptr<ofxSmartFont> fontScaleNameLabel;
    
    
    ofPath circleInner;
    uiVizElm vizElm_circleInner;
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

    uiVizWidgetScaleTable* scaleTableMenuItem;
    string explicityPickedScaleName = "";

    
    // Set up the slices with Notes data (colors, degrees, etc)
    void initScale() {
        notesActualScale = vizScale::getNotesForScale(getSelectedKey().getNoteName(), getSelectedScaleName()); // all the degrees of the scale (inner

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

        circleSlicesT1.clear();
        circleSlicesT2.clear();
        
        float degreesOffset = getAngleOffsetForSlice(1);
        mWheelOffest = degreesOffset;

        for (int degree=0; degree<notesT1.size(); degree++) {
            uiVizWidgetScalePickerSlice sliceT1;
            sliceT1.note = notesT1[degree];
            circleSlicesT1.push_back(sliceT1);
            if (degree == 0) addSelectedNote(sliceT1.note, true);
        }
        
        for (int key=0; key<notesT2.size(); key++) {
            uiVizWidgetScalePickerSlice sliceT2;
            sliceT2.note = notesT2[key];
            circleSlicesT2.push_back(sliceT2);
        }
        
        setTitle("Scale Picker");
        setNeedsUpdate(true);
    }
    
    vector<uiVizWidgetMenuItem> getScalesMenuItems() {
        vector<uiVizWidgetMenuItem> scalesMenuItems = { };
        vector<string> scales = MusicTheory::Scale::getAllKnownScales();
        
        for (int i=0; i<scales.size(); i++) {
            scalesMenuItems.push_back(
               uiVizWidgetMenuItem(scales[i], i, false, i==0)
            );
        }
        return scalesMenuItems;
    }
    
    void initWidget() override {
        

/*

        vector<string> scales = MusicTheory::Scale::getAllKnownScales();

        for (string scale:scales) {

            MusicTheory::ScalePtr s = MusicTheory::Scale::getScaleFromString(scale, MusicTheory::Note::create("C"));
            //Scale Id	Scale Name	Origin	Notes	NumNotes

            string notes = "";
            for (MusicTheory::NotePtr n:s->notes) {
                notes += n->name + ",";
            }

            string betterName = scale;
            betterName[0] = toupper(betterName[0]);

            string exportData =  scale + "\t" + betterName + "\tCommon\t" + notes + + "\t" + ofToString(s->notes.size()) + "\n";
            cout << exportData;


        }
      //  MusicTheory::ScalePtr s = MusicTheory::Scale::scaleFromDictionary("arabicScale", MusicTheory::Note::create("C"));
*/

        if (getSelectedKey().getNoteName() == "") {
            vizNote defaultKey = vizNote("C", 2, 0, vector<string>{});
            
            uiVizWidgetMusical::setSelectedKey(defaultKey);
            
            if (getSelectedScaleName() == "") {
                setSelectedScale("chromatic", true);
            }
            
            initScale();
            
            
            addSelectedScaleByName("ionian", defaultKey, false);
            setNeedsUpdate(true);
        }
        


        scaleTableMenuItem = new uiVizWidgetScaleTable(ofToUpper(getWidgetId()) + "_MENU_SCALE_TABLE", R"(
            <widget>
            <bounds width="400" height="400" minWidth="400" minHeight="200"  />
            </widget>
            )");

        scaleTableMenuItem->setIsAutoResizeToContentsHeight(false);
        scaleTableMenuItem->setIsAutoResizeToContentsWidth(true);
        scaleTableMenuItem->setSelectionMode(uiVizWidgetTable::SelectionMode::ROW);
        scaleTableMenuItem->setAllowMultiSelect(false);
        ofAddListener(scaleTableMenuItem->cellSelected, this, &uiVizWidgetScalePicker::onScaleTableMenuItemSelected);



        setTheoryVizColorMode(TheoryVizColorMode::KEYS);
        setTheoryVizLabelMode(TheoryVizLabelMode::DEGREES);
        if (!scalePickerContextMenu) {

            scaleRulesMenuItem = new uiVizWidgetChordRules(
                getWidgetId() + "_MENU_SCALE_RULES",
                "<widget><bounds minWidth='300' minHeight='400'/><appearance/></widget>"
            );

            scaleRulesMenuItem->setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode::SCALE);

            ofAddListener(scaleRulesMenuItem->rulesChanged, this,  &uiVizWidgetScalePicker::onRulesChanged);

            scalePickerContextMenu = new uiVizWidgetMenu(getWidgetId() + "_SP_MENU1", "<widget><bounds width='100' height='300'/></widget>", getWidgetId()
            , uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                
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
                // Note mode menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("NOTE_MODE"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_NOTE_MODE, {
                    uiVizWidgetMenuItem(uiVizShared::lang("DEFAULT"), (int)TheoryVizNoteMode::DEFAULT, false, true),
                    uiVizWidgetMenuItem(uiVizShared::lang("SHARP"), (int)TheoryVizNoteMode::SHARP),
                    uiVizWidgetMenuItem(uiVizShared::lang("FLAT"), (int)TheoryVizNoteMode::FLAT)
                }),
                
                // ----------------------------------------------------------------------------
                // Scales menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("SCALES"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_SCALE"), 
                                    MENU_GROUP_1::MENU_TAB_SCALE,
                                    scaleTableMenuItem
                                    ),
                                                
                // ----------------------------------------------------------------------------
                // Scale Rules menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("SCALE_RULES"), uiVizIconCache::getIcon("MED_CONTENT_RULES"),
                                MENU_GROUP_1::MENU_TAB_SCALE_RULES,
                                scaleRulesMenuItem
                                ),        

                // ----------------------------------------------------------------------------
                // Settings menu
                // ----------------------------------------------------------------------------
                uiVizWidgetMenuTab(uiVizShared::lang("SETTINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {
                    uiVizWidgetMenuItem(uiVizShared::lang("SOUND"), 1, true, true),
                    uiVizWidgetMenuItem(uiVizShared::lang("SAVE"), 2)
                })
                
            });
    
            ofAddListener(dynamic_cast<uiVizWidgetMenu*>(scalePickerContextMenu)->menuItemSelected, this, &uiVizWidgetScalePicker::onMenuItemSelected);

            uiVizWidgetManager::addWidget(*scalePickerContextMenu, false, getWidgetId());
        }

        // need to use :
        // addChildWidget(*scalePickerContextMenu);
        // and fix up widget manager, or move func to recursive .widget.drawWidget() ---> children

        setIsAutoUpdateWhenActive(true);
    }
    
    void auditionScale(bool visually, bool audibly) {
        // Todo playback created
    }

    void onScaleTableMenuItemSelected(uiVizWidgetTableArgs & args) {
        explicityPickedScaleName = args.row.key;
        addSelectedScaleByName(args.row.key, getSelectedKey(), true);
        if (!scalePickerContextMenu->getIsMenuPinned()) {
            scalePickerContextMenu->closeMenu();
        }
    }
    
    void onMenuItemSelected(uiVizWidgetMenuItemArgs & args) {
        
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
                
            case MENU_GROUP_1::MENU_TAB_SCALE: {
                string scaleName = args.menuItem->label;
                addSelectedScaleByName(scaleName, getSelectedKey(), true);
                break;
            }
                
        }
        
    }
    
    ofColor getLabelStateColor(uiVizWidgetScalePickerSlice slice) {
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

    
};
