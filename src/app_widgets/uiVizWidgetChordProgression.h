//
//  uiVizWidgetChordProgression.h
//  bloom-macos
//
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "../uiViz/widget/uiVizWidgetMenu.h"
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetChordDesigner.h"

class uiVizWidgetChordProgressionSliceNode {
public:
    int index = 0;
    int weight = 1;
    Aquamarine::uiVizElm path;

    uiVizWidgetChordProgressionSliceNode(int index, int weight) : index(index), weight(weight) {};

    ~uiVizWidgetChordProgressionSliceNode() {
    }
    
};
class uiVizWidgetChordProgressionSlice {
public:
    vizChord chord;
    vizChord originalChord;
	Aquamarine::uiVizElm path;
    string label;
    string parentKey = "";
    string originalParentKey = "";
    string prevKey = "";
    string nextKey = "";
    int degree = 0;
    int originalDegree = 0;
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

    float nodeXFrom;
    float nodeYFrom;
    float nodeXTo;
    float nodeYTo;        


    bool isHovered = false;
    bool isSelected = false;

    vector<uiVizWidgetChordProgressionSliceNode> nodes;
    
	bool getIsMouseHovered() {

		int mouseX = ofGetMouseX();
		int mouseY = ofGetMouseY();

		return (
			ofDist(mouseX, mouseY, circX, circY) <= circRadiusX_Begin  && ofDist(mouseX, mouseY, circX, circY) <= circRadiusY_Begin &&
                ofDist(mouseX, mouseY, circX, circY) > circRadiusX_End && ofDist(mouseX, mouseY, circX, circY) > circRadiusY_End 
        );
	}

    ~uiVizWidgetChordProgressionSlice() {
    }
    
};

class uiVizWidgetChordProgression : public uiVizWidgetMusical {

public:
   
    uiVizWidgetChordProgression(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        uiVizWidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_PROGRESSION, 0);
        return mWidgetXML;
    }
    
    virtual ~uiVizWidgetChordProgression() {

        circleSlicesT1.clear();
        
        ChordProgressionContextMenu->deleteThisWidget();
    }
    
    void setSliceProperties(uiVizWidgetChordProgressionSlice *slice,
            int currentSlice, float currentAngle, float angleOffset, float degreesPerSlice,
            float circX, float circY, float circRadiusX, float circRadiusY, int tier, bool forceHiglight) {

        bool isHighlightedChord = false;

        // Default, pretty right?
        ofColor rawColor = vizTheory::getColorForKey(slice->parentKey);
         float hue = std::min((float)255, (float)(255 / (double)360) * (degreesPerSlice*(currentSlice-1))); // mixed colours between shared chords
        // float hue =  rawColor.getHue() + 255.0f * (255.0f / 360.0f / degreesPerSlice);


        

        ofColor color = ofColor::fromHsb(hue, 255, 220 - tier*35);

        /*-*-*-*-*-*-*-*-*-* Default colours *-*-*-*-*-*-*-*-*-*/
        
        float diff = 60;
        if (getSelectedChordsSize() > 0) {
            // At least one chord is selected, we want a very light, subtle style for non focused keys
            slice->regularColor = ofColor::fromHsb(color.getHue(), 100, 200);
            slice->regularFontColor = ofColor::fromHsb(color.getHue(),  100, 180);
            //slice->selectedFontColor = ofColor::fromHsb(slice->selectedFontColor.getHue(), 255, 160);
            
        } else {
            // No chords are selected, make a pretty hue circle of all possible harmonies...
            mUnfocusedChordBrightness = 155.0f;
            
            slice->regularColor = ofColor::fromHsb(color.getHue(), 100, 200);
            slice->regularFontColor = ofColor::fromHsb(color.getHue(),  100, 180);

            slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);
            slice->selectedFontColor = ofColor::fromHsb(color.getHue(), 255, color.getBrightness() - diff);
        }

        string sliceChordRootName = "";

        if (!forceHiglight) {
            slice->hoveredColor = ofColor::fromHsb(color.getHue(), 255, 255); // This enables colours from other scales to be apparent on mouseover
            slice->hoveredFontColor = ofColor::fromHsb(color.getHue(), 255, 160);
        }
        
        for (int selectedChordIndex = getSelectedChordsSize() - 1; selectedChordIndex >= 0; selectedChordIndex--) {
            // Ensure that the key the user clicked first is always fully coloured in it's key color.
            // Achieved by traversing and highlighting the selectedChords vector BACKWARDS.

            vizChord selectedChord = getSelectedChordByIndex(selectedChordIndex);
            sliceChordRootName = slice->chord.getChordRoot();
            
            int sliceInterval = -1;

            if (slice->parentKey == selectedChord.getChordRoot()) {
                sliceInterval = slice->degree;
            } else if(slice->degree == vizTheory::DegreeName::majorUnison && slice->prevKey == selectedChord.getChordRoot()) { // V
                sliceInterval = vizTheory::DegreeName::perfectFifth;
            } else if(slice->degree == vizTheory::DegreeName::majorUnison && slice->nextKey == selectedChord.getChordRoot()) { // IV
                sliceInterval = vizTheory::DegreeName::perfectFourth;
            } else if(slice->degree == vizTheory::DegreeName::majorSecond && slice->prevKey == selectedChord.getChordRoot()) { // VI
                sliceInterval = vizTheory::DegreeName::majorSixth;
            }

            isHighlightedChord = (sliceInterval > -1);

            if (isHighlightedChord) {
                // This chord "part of the family :-)
                color = getSliceColorForState(selectedChord.getChordRoot(), slice->chord.getChordRoot(), sliceInterval + 1, isHighlightedChord);

                slice->regularColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness());
                slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);

                slice->regularFontColor = getMediumFontColor(slice->parentKey);
                slice->selectedFontColor = getMediumFontColor(slice->parentKey);
                
                
                slice->hoveredColor = ofColor::fromHsb(color.getHue(), 255, 255);
                slice->hoveredFontColor = getHoveredFontColor(slice->parentKey);
                
            }
        }
        

            
        if (forceHiglight) {
            isHighlightedChord = true;
            color = getSliceColorForState(slice->parentKey, slice->chord.getChordRoot(), slice->degree+1, false);
  
            slice->regularColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness());
            slice->selectedColor = ofColor::fromHsb(color.getHue(), 255, 255);
            
            slice->regularFontColor = getMediumFontColor(slice->parentKey);
            slice->selectedFontColor = getMediumFontColor(slice->parentKey);
            
        }        

		ofPath c;

		c.setCircleResolution(360);
		// Expensive operation: Keep OUT of draw cycle 
        c.moveTo(circX, circY);
		c.arc(circX, circY, circRadiusX, circRadiusY, (float)currentAngle + (float)angleOffset, degreesPerSlice + (float)angleOffset);
		c.close();
		slice->path.update(c);


        //---------- Label plot calculations for slice ----------
        float midSlice = ((float)degreesPerSlice/2) + (float)currentAngle + (float)angleOffset;
        float distanceFromCentre = 0.85f;
        
        switch(tier) {
            case 1:
                distanceFromCentre = 0.75f;
                break;
            case 2:
                distanceFromCentre = 0.86f;
                break;
            case 3:
                distanceFromCentre = 0.885f;
                break;
        }
        
       
        switch (getTheoryVizLabelMode()) {
            case TheoryVizLabelMode::NONE:
                slice->label = "   ";
                break;
            
            case TheoryVizLabelMode::KEYS:
                if (getSelectedChordsSize() > 0) {
                    slice->label = slice->chord.getChordNameSimplified(true);
                } else {
                    // TODO - OPTION TO HAVE RELATIVE TO CHORD (of 1st selected ie.
                    // getSelectedChordByIndex(0).getChordName()
                    slice->label = slice->chord.getChordNameSimplified(true);
                }
                break;
            
            case TheoryVizLabelMode::DEGREES:
                if (getSelectedChordsSize() > 0) {
                    slice->label = slice->chord.getChordNameRoman(slice->parentKey);
                } else {
                    slice->label = slice->chord.getChordNameSimplified(true);
                }
                break;
        };

        
        ofRectangle rect = font->rect(slice->label);
        float fontWidth = rect.width;
        float fontHeight = rect.height;

        // Now that we have the middle of the slice angle, we use cos, sin on it, and multiply a distanceFromCentre factor on the angle to work
        // out a label coordinate. Finally we have the centre of the font to the x, y coords!

        float plotX = (float)(circX - fontWidth /(float) 2) + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(midSlice));
        float plotY = (float)(circY + fontHeight/(float) 2) + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(midSlice));
        slice->labelPoint = ofPoint(plotX, plotY);

        float nodeXFrom = circX + (circRadiusX*0.75f) * distanceFromCentre * (float)cos((float)ofDegToRad(midSlice));
        float nodeYFrom = circY + (circRadiusY*0.75f) * distanceFromCentre * (float)sin((float)ofDegToRad(midSlice));        
        float nodeXTo = circX + (circRadiusX*0.75f) * distanceFromCentre * (float)cos((float)ofDegToRad(midSlice));
        float nodeYTo = circY + (circRadiusY*0.75f) * distanceFromCentre * (float)sin((float)ofDegToRad(midSlice));                


		// Hit area stuff!
		float startAngle = (float)currentAngle + (float)angleOffset;
		float endAngle = (float)currentAngle + (float)angleOffset + (float)degreesPerSlice;

		slice->startSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(startAngle));
		slice->endSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(endAngle));
		slice->startSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(startAngle));
		slice->endSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(endAngle));
		slice->circRadiusX_Begin = circRadiusX;
		slice->circRadiusY_Begin = circRadiusY;

		slice->nodeXFrom = nodeXFrom;
		slice->nodeYFrom = nodeYFrom;
		slice->nodeXTo = nodeXTo;
		slice->nodeYTo = nodeYTo;        

        
        switch(tier) {
            case 1:
                slice->circRadiusX_End = circRadiusX * TIER1_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER1_RADIUS_PERC;
                break;
        }
        
		slice->circX = circX;
		slice->circY = circY;
		slice->distanceFromCentre = distanceFromCentre;
    }

    void update(Aquamarine::uiVizWidgetContext context) override {
        
        font = getSmallFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontScaleNameLabel = getFontSizedForDimensions(getUsableWidth() * 0.5f, getUsableHeight() * 0.5f);
        
        rectFontHitArea = font->rect("G#");
        circleInner.clear();

        float circX = scale(getUsableX() + getUsableWidth()/2.0f);
        float circY = scale(getUsableY() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth() /2.0f);
        float circRadiusY = scale(getUsableHeight()/2.0f);
        
        float degreesPerSliceT1 = 360 / (float)chordsT1.size();

        float circRadiusXT1 = circRadiusX * TIER1_RADIUS_PERC;
        float circRadiusYT1 = circRadiusY * TIER1_RADIUS_PERC;
    
        // DEFAULT STATE WITHOUT ALTERNATION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        for (int i = 1; i <= circleSlicesT1.size() ; i++) {
            // T1
            // The current degrees position
            float currentAngleT1 = ((float)degreesPerSliceT1*i);
            uiVizWidgetChordProgressionSlice *sliceT1 = &circleSlicesT1[i-1];
            
            
            if (isSelectedChordRoot(sliceT1->originalParentKey)) {
                sliceT1->chord = sliceT1->originalChord;
                sliceT1->parentKey = sliceT1->originalParentKey;
            }
            setSliceProperties(sliceT1, i, currentAngleT1, mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, false);
        }


       ofColor c = getSelectedFontColor(getLargeLabelText());

        for (int i = 1; i <= circleSlicesT1.size() ; i++) {
            uiVizWidgetChordProgressionSlice *slice = &circleSlicesT1[i-1];
                
            for (uiVizWidgetChordProgressionSliceNode& n:slice->nodes) {
                
                uiVizWidgetChordProgressionSlice *targetSlice = &circleSlicesT1[n.index-1];

                n.path.setTriangle(
                    slice->nodeXFrom, slice->nodeYFrom, 
                    slice->nodeXFrom, slice->nodeYFrom, 
                    targetSlice->nodeXTo, targetSlice->nodeYTo
                );
                n.path.setColor(c); 
                n.path.setStroke(scale(10), c);
            }
        }


        circleInner.setCircleResolution(360); // Can lower or remove to bump up performance
        circleInner.setFilled(true);
        circleInner.arc(circX, circY, circRadiusX/(float)3, circRadiusY/(float)3, 0, 360);
		vizElm_circleInner.update(circleInner);

        circleInnerPoint.set(circX, circY);
    }

    void drawSlice(int tier, int currentSlice, uiVizWidgetChordProgressionSlice &slice) {

        slice.path.setColor(slice.regularColor); // Hover

        if (getIsActiveWidget()) {
            //---------- Mouse Hit test  ----------
            float dist = ofDist(ofGetMouseX(), ofGetMouseY(), slice.labelPoint.x, slice.labelPoint.y);
            bool sliceHovered = dist <= ((rectFontHitArea.width*1.5f + rectFontHitArea.height*1.5f) / (float)2);

			//bool sliceHovered = slice.getIsMouseHovered(); //TODO FIX!! (gettin' there)
            slice.isHovered = false;
            slice.isSelected = false;
            if (!getIsDragging()) {
                if (sliceHovered || matchesSelectedChordRoot(slice.chord))  {
                    
                    if (sliceHovered) {
                        slice.path.setColor(slice.hoveredColor); // Hover
                        slice.isHovered = true;
                        setHoveredChord(slice.chord);
                        auditionChord(slice.chord);
                        setDraggingChord(slice.chord);
                        // setHoveredChord(slice.chord);
                        // auditionChord(slice.chord);
                        // if (getIsMousePressedAndReleasedOverWidget(false)) {
                            
                        //    if(!matchesSelectedChordRoot(slice.chord)) {
                        //        int pos = vizTheory::getPositionInCircleOfFifthsForKey(slice.chord.getChordRoot());
                        //        addSelectedChord(chordMatrixCurrent[pos-1][0], true, true);
                        //     } else {
                        //         removeSelectedChordRoot(slice.chord);
                        //     }
                        //     setNeedsUpdate(true);
                        // } else if (getIsMousePressedOverWidget(false)) {
                        //     setDraggingChord(slice.chord);
                        // }


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
    
    void clearSelectedChordsAndSelectChordWithKey(vizNote key) {
        for (int keyIndex=0; keyIndex<12; keyIndex++) {
            if (chordMatrixCurrent[keyIndex][0].getChordRootNote().isEnharmonicallyEquivalent(key.getNoteNameNormalized())) {
                clearSelectedChords();
                addSelectedChord(chordMatrixCurrent[keyIndex][0], true, true);
            }
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
    
    bool isScaleWhichHasAlternateChords() {
        return getSelectedScaleName() != "ionian";
    }

    bool displayAlternateSliceInfo() {
        return (isScaleWhichHasAlternateChords());
    }
    
    
    bool needsUpdateBeforeDraw(bool shouldResetTimer) override {
        bool needsUpdate = uiVizWidgetMusical::needsUpdateBeforeDraw(false);

        if (getTimerMillis() >= 2000) {
            if (shouldResetTimer) resetTimer();
            needsUpdate = true;
        }
        
        return needsUpdate;
    }
    
    void draw(Aquamarine::uiVizWidgetContext context) override {
        
        // Draw the slices
        mAtLeastOneSliceHovered = false;    
        for(int i=1; i<=circleSlicesT1.size(); i++){
            drawSlice(1, i, circleSlicesT1[i-1]);
            if (circleSlicesT1[i-1].isHovered) mAtLeastOneSliceHovered = true;
        }

        // set key ------ TODO ---------
        // show alternatic chords, like 7ths, 9ths, etx

		vizElm_circleInner.setColor(getLargeLabelStateColor());
		vizElm_circleInner.draw(); 

        // Draw progressions (either hovered node, or root, if nothing hovered)
        for(int i=0; i<circleSlicesT1.size(); i++){
            if (circleSlicesT1[i].isHovered || (mAtLeastOneSliceHovered == false && i == 0)) {
                for (uiVizWidgetChordProgressionSliceNode& n:circleSlicesT1[i].nodes) {
                    n.path.draw();
                }
                mAtLeastOneSliceHovered = true;
            }
        }        


		// Large label
		rectLargeLabel = fontLargeLabel->rect(getLargeLabelText());
        rectScaleNameLabel = fontScaleNameLabel->rect(getSelectedScaleNamePretty());
        ofRectangle rectScaleNameLabelHeight = fontScaleNameLabel->rect("ABCxyz");
        
        
        int yLabelOffset = getWidth() > 220 ? rectScaleNameLabelHeight.height + getNonScaledPadding()/2 : 0;
        
        
        drawFontWithShadow(
            fontLargeLabel, getLargeLabelText(), 
			circleInnerPoint.x - rectLargeLabel.width / 2.0f,
			circleInnerPoint.y + rectLargeLabel.height / 2.0f - yLabelOffset / 2,     
            getSelectedFontColor(getLargeLabelText()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));

        if (yLabelOffset > 0 || getSelectedKey().getNoteName() == "") {
            if (getSelectedChordsSize() == 0) yLabelOffset = 0;
            drawFontWithShadow(
                fontScaleNameLabel, getSelectedScaleNamePretty(), 
                circleInnerPoint.x - rectScaleNameLabel.width / 2.0f,
                circleInnerPoint.y + rectScaleNameLabelHeight.height / 2.0f + yLabelOffset * 1.2f,  
                getSelectedFontColor(getLargeLabelText()), getFaintFontColor_Dark(getSelectedKey().getNoteName()));
        }

    }
    
    
    void updateMinimized() override {
        
    }
    
    void drawMinimized() override {
    }
    
    void onWidgetMouseContentDragged(ofMouseEventArgs &e) override {
        if (getDraggingChord().getChordName() != "") {
            setDragData(getDraggingChord().getXML());
        }
    }
    
    uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS:
                return ChordProgressionContextMenu;
            default:
                return nullptr;
        }
    }
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {

            vizChord hoveredChord = getHoveredChord();
            chordDesignerMenuItem->addSelectedChord(hoveredChord, true, true);

            showContextMenu(Aquamarine::uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }
    
    void setSelectedScale(string val, bool includeInstrumentRules) override {
        uiVizWidgetMusical::setSelectedScale(val, includeInstrumentRules);
        initScale();
    }

    void setTheoryVizNoteMode(TheoryVizNoteMode theoryVizNoteMode) override {
        uiVizWidgetMusical::setTheoryVizNoteMode(theoryVizNoteMode);
        clearSelectedChords();
        initScale();
    }
    
private:
    bool mAtLeastOneSliceHovered = false;
    uiVizWidget *ChordProgressionContextMenu = nullptr;
    uiVizWidgetChordDesigner* chordDesignerMenuItem = nullptr;
    uiVizWidgetKeyPicker* keyPickerMenuItem = nullptr;

    
    
	// Get the desired diatoic scale starting on C and convert it to Circle of Fifths

	vector<vizChord> chordsT1; //= getCircleOfFifths();
    
    vector<vector<vizChord>> chordMatrixSharps;
    vector<vector<vizChord>> chordMatrixFlats;
    vector<vector<vizChord>> chordMatrixCurrent;
    
    float TIER1_RADIUS_PERC = 1.0f; //0.6f;

    

    vector<uiVizWidgetChordProgressionSlice> circleSlicesT1;

    
    shared_ptr<ofxSmartFont> font;
    
    // try a font size for each tier
    
    shared_ptr<ofxSmartFont> fontLargeLabel;
    shared_ptr<ofxSmartFont> fontScaleNameLabel;
    
    
    ofPath circleInner;
	Aquamarine::uiVizElm vizElm_circleInner;
    ofRectangle rectLargeLabel;
    ofRectangle rectScaleNameLabel;
    ofColor largeLabelColor;
    ofRectangle rectFontHitArea;
    ofPoint circleInnerPoint;

	float degreesOffset = 0;
    float mWheelOffest = 0;
    float mUnfocusedChordBrightness = 155.0;
    float mFocusedChordBrghtness = 100;
    
    enum MENU_GROUP_1 {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_NOTE_MODE = 2,
        MENU_TAB_CHORD_SCALE = 3,
        MENU_TAB_SETTINGS = 4,
        MENU_TAB_KEY_PICKER = 9,        
        MENU_TAB_CHORD_DESIGNER = 10        
    };
    

    // Set up the slices with Chord data (colors, Chords, etc)
    void initScale() {
        
        setAspectRatio(0.65f);
        setLockAspectRatio(true);
        
        switch(getTheoryVizNoteMode()) {
            case TheoryVizNoteMode::DEFAULT:
                chordMatrixCurrent = vizScale::getDiatonicChordMatrixForScale(getSelectedScaleName(), vizTheory::NoteMode::DEFAULT, true); break;
            case TheoryVizNoteMode::SHARP:
                chordMatrixCurrent = vizScale::getDiatonicChordMatrixForScale(getSelectedScaleName(), vizTheory::NoteMode::SHARP, true); break;
            case TheoryVizNoteMode::FLAT:
                chordMatrixCurrent = vizScale::getDiatonicChordMatrixForScale(getSelectedScaleName(), vizTheory::NoteMode::FLAT, true); break;
            default:
                chordMatrixCurrent = vizScale::getDiatonicChordMatrixForScale(getSelectedScaleName(), vizTheory::NoteMode::DEFAULT, true); break;
        }
        
        chordsT1.clear();
        circleSlicesT1.clear();
    

        int key = 0;
        if (getSelectedKey().getNoteName() != "") {
            key = vizTheory::getPositionInCircleOfFifthsForKey(getSelectedKey().getNoteName()) - 1;
        }
        
        int nextKeyIndex = (key == 11) ?  0 : (key + 1);
        int prevKeyIndex = (key == 0) ?  11 : (key - 1);

        string curKey = chordMatrixCurrent[key][0].getChordRoot();
        string nextKey = chordMatrixCurrent[nextKeyIndex][0].getChordRoot();
        string prevKey = chordMatrixCurrent[prevKeyIndex][0].getChordRoot();
        
        vizChord currKeyIChord      = chordMatrixCurrent[key][0];
        vizChord currKeyIIChord     = chordMatrixCurrent[key][1];
        vizChord currKeyIIIChord    = chordMatrixCurrent[key][2];
        vizChord currKeyIVChord     = chordMatrixCurrent[key][3];
        vizChord currKeyVChord      = chordMatrixCurrent[key][4];
        vizChord currKeyVIChord     = chordMatrixCurrent[key][5];
        vizChord currKeyVIIChord    = chordMatrixCurrent[key][6];
        
        uiVizWidgetChordProgressionSlice slice_I, slice_II, slice_III, slice_IV, slice_V, slice_VI, slice_VII;
        
        /***********
         * T1 RING *
         ***********/
        
        // I chord
        chordsT1.push_back(currKeyIChord);
        slice_I.chord = currKeyIChord;
        slice_I.originalChord = currKeyIChord;
        slice_I.parentKey = curKey;
        slice_I.originalParentKey = curKey;
        slice_I.prevKey = prevKey;
        slice_I.nextKey = nextKey;
        slice_I.degree = vizTheory::DegreeName::majorUnison;
        slice_I.originalDegree = vizTheory::DegreeName::majorUnison;
        circleSlicesT1.push_back(slice_I);



        // II chord
        chordsT1.push_back(currKeyIIChord);
        slice_II.chord = currKeyIIChord;
        slice_II.originalChord = currKeyIIChord;
        slice_II.parentKey = curKey;
        slice_II.originalParentKey = curKey;
        slice_II.prevKey = prevKey;
        slice_II.nextKey = nextKey;
        slice_II.degree = vizTheory::DegreeName::majorSecond;
        slice_II.originalDegree = vizTheory::DegreeName::majorSecond;
        circleSlicesT1.push_back(slice_II);

        // III chord
        chordsT1.push_back(currKeyIIIChord);
        slice_III.chord = currKeyIIIChord;
        slice_III.originalChord = currKeyIIIChord;
        slice_III.parentKey = curKey;
        slice_III.originalParentKey = curKey;
        slice_III.prevKey = prevKey;
        slice_III.nextKey = nextKey;
        slice_III.degree = vizTheory::DegreeName::majorThird;
        slice_III.originalDegree = vizTheory::DegreeName::majorThird;
        circleSlicesT1.push_back(slice_III);            

        // IV chord
        chordsT1.push_back(currKeyIVChord);
        slice_IV.chord = currKeyIVChord;
        slice_IV.originalChord = currKeyIVChord;
        slice_IV.parentKey = curKey;
        slice_IV.originalParentKey = curKey;
        slice_IV.prevKey = prevKey;
        slice_IV.nextKey = nextKey;
        slice_IV.degree = vizTheory::DegreeName::perfectFourth;
        slice_IV.originalDegree = vizTheory::DegreeName::perfectFourth;
        circleSlicesT1.push_back(slice_IV); 

        // V chord
        chordsT1.push_back(currKeyVChord);
        slice_V.chord = currKeyVChord;
        slice_V.originalChord = currKeyVChord;
        slice_V.parentKey = curKey;
        slice_V.originalParentKey = curKey;
        slice_V.prevKey = prevKey;
        slice_V.nextKey = nextKey;
        slice_V.degree = vizTheory::DegreeName::perfectFifth;
        slice_V.originalDegree = vizTheory::DegreeName::perfectFifth;
        circleSlicesT1.push_back(slice_V); 

        // VI chord
        chordsT1.push_back(currKeyVIChord);
        slice_VI.chord = currKeyVIChord;
        slice_VI.originalChord = currKeyVIChord;
        slice_VI.parentKey = curKey;
        slice_VI.originalParentKey = curKey;
        slice_VI.prevKey = prevKey;
        slice_VI.nextKey = nextKey;
        slice_VI.degree = vizTheory::DegreeName::majorSixth;
        slice_VI.originalDegree = vizTheory::DegreeName::majorSixth;
        circleSlicesT1.push_back(slice_VI);    


        // VII chord
        chordsT1.push_back(currKeyVIIChord);
        slice_VII.chord = currKeyVIIChord;
        slice_VII.originalChord = currKeyVIIChord;
        slice_VII.parentKey = curKey;
        slice_VII.originalParentKey = curKey;
        slice_VII.prevKey = prevKey;
        slice_VII.nextKey = nextKey;
        slice_VII.degree = vizTheory::DegreeName::majorSeventh;
        slice_VII.originalDegree = vizTheory::DegreeName::majorSeventh;
        circleSlicesT1.push_back(slice_VII);                            

        
        
        vector<vector<int>> progData = 
        {
            {2, 3, 4, 5, 6, 7},
            {3, 5},
            {2, 4, 6},
            {1, 3, 5},
            {1, 6},
            {2, 4, 5},
            {1}

        };

        for (int chordNum = 0; chordNum < progData.size(); chordNum++) {
            for (int chordDest: progData[chordNum]) {
                circleSlicesT1[chordNum].nodes.push_back(uiVizWidgetChordProgressionSliceNode(chordDest,1));
            }
        } 


        
        degreesOffset = getAngleOffsetForSlice(1);
        mWheelOffest = degreesOffset;


        clearSelectedChords();
        addSelectedChord(currKeyIChord, true, true);
        
      //  setTheoryVizColorMode(uiVizWidgetMusical::TheoryVizColorMode::KEYS);
      //  setTheoryVizLabelMode(uiVizWidgetMusical::TheoryVizLabelMode::KEYS);
        
        setTitle(getSelectedScaleNamePretty());
        setNeedsUpdate(true);
    }
    
    void initWidget() override {

        if (getSelectedScaleName() == "") {
            setSelectedScale("ionian", true);
        }
        
        if (!ChordProgressionContextMenu) {

            chordDesignerMenuItem = new uiVizWidgetChordDesigner(
                getWidgetId() + "_MENU_CHORD_DESIGNER",
                "<widget><bounds width='300' height='300' minWidth='200' minHeight='200'/><appearance/></widget>"
                );


            keyPickerMenuItem = new uiVizWidgetKeyPicker(
                getWidgetId() + "_MENU_KEY_PICKER",
                "<widget><bounds width='300' height='300' minWidth='200' minHeight='200'/><appearance/></widget>"
                );

            keyPickerMenuItem->handleKeyChanged([this](vizNote note) {
                this->setSelectedKey(note);
                initScale();
            });                


            ChordProgressionContextMenu = new Aquamarine::uiVizWidgetMenu(getWidgetId() + "_CP_MENU1", "<widget><bounds width='100' height='300'/></widget>", getWidgetId()
                , Aquamarine::uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("LABEL"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("NONE"), (int)TheoryVizLabelMode::NONE),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                }),
                
                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("COLOR"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("NONE"), (int)TheoryVizColorMode::NONE),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                    //Aquamarine::uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                }),
                    
                // ----------------------------------------------------------------------------
                // Note mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("NOTE_MODE"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_NOTE_MODE, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("DEFAULT"), (int)TheoryVizNoteMode::DEFAULT, false, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("SHARP"), (int)TheoryVizNoteMode::SHARP),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("FLAT"), (int)TheoryVizNoteMode::FLAT)
                }),

                // ----------------------------------------------------------------------------
                // Scale / menu mode
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab("Modes Tabs", Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_SCALE"), MENU_GROUP_1::MENU_TAB_CHORD_SCALE, {
                    Aquamarine::uiVizWidgetMenuItem("Ionian", 1, false, true),
                    Aquamarine::uiVizWidgetMenuItem("Dorian", 2),
                    Aquamarine::uiVizWidgetMenuItem("Phrygian", 3),
                    Aquamarine::uiVizWidgetMenuItem("Lydian", 4),
                    Aquamarine::uiVizWidgetMenuItem("Mixolydian", 5),
                    Aquamarine::uiVizWidgetMenuItem("Aeolian", 6),
                    Aquamarine::uiVizWidgetMenuItem("Locrian", 7),
                    // ADD DIVIDER, and set degree color for hover state
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor", 8),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor II", 9),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor III", 10),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor IV", 11),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor V", 12),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor VI", 13),
                    Aquamarine::uiVizWidgetMenuItem("Melodic Minor VII", 14)
                }),

               // ----------------------------------------------------------------------------
                // Key Picker menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("KEY_PICKER"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"),
                                MENU_GROUP_1::MENU_TAB_KEY_PICKER,
                                keyPickerMenuItem
                                ),

               // ----------------------------------------------------------------------------
                // Chord Designer menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("CHORD_DESIGNER"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"),
                                MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER,
                                chordDesignerMenuItem
                                ),     
                
                // ----------------------------------------------------------------------------
                // Settings menu
                // ----------------------------------------------------------------------------
                Aquamarine::uiVizWidgetMenuTab(Aquamarine::uiVizShared::lang("SETTINGS"), Aquamarine::uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("SOUND"), 1, true, true),
                    Aquamarine::uiVizWidgetMenuItem(Aquamarine::uiVizShared::lang("SAVE"), 2)
                })
                
            });

            ofAddListener(dynamic_cast<Aquamarine::uiVizWidgetMenu*>(ChordProgressionContextMenu)->menuItemSelected, this, &uiVizWidgetChordProgression::onMenuItemSelected);
            
            Aquamarine::uiVizWidgetManager::addWidget(*ChordProgressionContextMenu, false, getWidgetId());
        }
        
        //move the above block to widget manager method :
        // remove the concept of popout widget, use only one widget (the menu one)
        // and govern it's draw from the parent widget (inside the draw widgets area)
        
        
        
        setIsAutoUpdateWhenActive(true);
        initScale();
    }
    
    // TODO : thread and animate
    
    // TODO :
    // ROTATE CHORDS I -> VII (and play) (rotate around selected keys!!!!)
    // show mode name in white dot
    // add other diatonic scales!!
    
    //todo:
    //   add label mode and label menu items to musical widget class
    
    // bug clicking start and end fret when the same - causes glitch -0 buid in validation
    // make alternate functions return bool.
    
    // only if bool, then perform update!
    
    void auditionChordsForMode(bool visually, bool audibly) {
        for (int key = 0; key < 1; key++) {
            for (int j = 0; j <= 6; j++) {
                ofSleepMillis(500);
                chordMatrixCurrent[key][j].audition(getGMInstrumentNumber());
            }
        }
    }

    void onMenuItemSelected(Aquamarine::uiVizWidgetMenuItemArgs & args) {

        switch(args.activeMenuTabId) {
                
            case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE:
                if (((TheoryVizLabelMode)args.menuItem->uniqueID == TheoryVizLabelMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedChordsSize() == 0) {
                    addSelectedChord(chordMatrixCurrent[0][0], true, true); // Select key of 'C'
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
                if (((TheoryVizColorMode)args.menuItem->uniqueID == TheoryVizColorMode::DEGREES || args.menuItem->uniqueID == -1000) && getSelectedChordsSize() == 0) {
                    addSelectedChord(chordMatrixCurrent[0][0], true, true); // Select key of 'C'
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

                
            case MENU_GROUP_1::MENU_TAB_CHORD_SCALE:
            
                string selectedscale = "ionian";
                
                switch(args.menuItem->uniqueID) {
                    case 1: selectedscale = "ionian"; break;
                    case 2: selectedscale = "dorian"; break;
                    case 3: selectedscale = "phrygian"; break;
                    case 4: selectedscale = "lydian"; break;
                    case 5: selectedscale = "mixolydian"; break;
                    case 6: selectedscale = "aeolian"; break;
                    case 7: selectedscale = "locrian"; break;
                    case 8: selectedscale = "melodicMinor"; break;
                    case 9: selectedscale = "melodicMinorII"; break;
                    case 10: selectedscale = "melodicMinorIII"; break;
                    case 11: selectedscale = "melodicMinorIV"; break;
                    case 12: selectedscale = "melodicMinorV"; break;
                    case 13: selectedscale = "melodicMinorVI"; break;
                    case 14: selectedscale = "melodicMinorVII"; break;
                }

                setSelectedScale(selectedscale, true);
                setNeedsUpdate(true);
                auditionChordsForMode(true, true);
                break;

        }
 
    }
    
    
    ofColor getLabelStateColor(uiVizWidgetChordProgressionSlice slice) {
        if (slice.isHovered)  {
            return slice.hoveredFontColor;
        } else if (slice.isSelected) {
            return slice.selectedFontColor;
        } else {
            return slice.regularFontColor;
        }
    }
    
    ofColor getLargeLabelStateColor() {
        if (getSelectedChordsSize() > 0) {
            return getSelectedChords()[0].getChordColor();
        }
        
        if (getHoveredChord().getChordName() != "") {
            return getHoveredChord().getChordColor();
        }
        return ofColor::white;
    }

	string getLargeLabelText() {
		if (getSelectedChordsSize() > 0) {
			return getSelectedChords()[0].getChordRoot();
		}
		return "";
	}
    
    float getAngleOffsetForSlice(int sliceNumber) {
        float degreesPerSlice = 360 / (float)chordsT1.size();
        return 270 - degreesPerSlice - (degreesPerSlice / (float)2) - ((sliceNumber - 1) * (float)degreesPerSlice);
    }
    
};


