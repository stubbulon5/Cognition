//
//  WidgetChordWheel.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "WidgetMusical.h"
#include "WidgetChordDesigner.h"

//------------------------------ Diatonic Chord Wheel widget --------------------------------

/***********************************************************************************
	DIATONIC TRIADS CHORDS WHEEL [https://www.musictheory.net/lessons/43]

	PARAMETERS :
		KEY		 eg. C
		SCALE	 eg Ionian / Major, Melodic Minor, etc

	INCOMING EVENTS :
		SELECTED KEY
		SELECTED CHORD

	OUTGOING EVENTS :
		SELECTED KEY
		SELECTED CHORD


***********************************************************************************/

class WidgetChordWheelSlice {
public:
    vizChord chord;
    vizChord originalChord;
	Aquamarine::Elm path;
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

    bool isHovered = false;
    bool isSelected = false;
    
	bool getIsMouseHovered() {

		int mouseX = ofGetMouseX();
		int mouseY = ofGetMouseY();

        
        /*
         
         slice->startSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(startAngle));
         slice->endSliceX = circX + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(endAngle));
         slice->startSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(startAngle));
         slice->endSliceY = circY + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(endAngle));
         
         
         */
        
		return (
			ofDist(mouseX, mouseY, circX, circY) <= circRadiusX_Begin  && ofDist(mouseX, mouseY, circX, circY) <= circRadiusY_Begin &&
                ofDist(mouseX, mouseY, circX, circY) > circRadiusX_End && ofDist(mouseX, mouseY, circX, circY) > circRadiusY_End 
                
              //   mouseX >= circX+startSliceX // && circY+circRadiusY_Begin >= circRadiusY_Begin
                
                /*
                mouseX >= startSliceX && mouseY >= startSliceY &&
                mouseX < endSliceX && mouseY < endSliceY
                */

                /*
                &&
			ofDist(mouseX, mouseY, circX + distanceFromCentre, circY + distanceFromCentre) <= circRadiusX && ofDist(mouseX, mouseY, circX + distanceFromCentre, circY + distanceFromCentre) <= circRadiusY
                 */
			
			);

		

	//	slice->circRadiusX = circRadiusX;
	//	slice->circRadiusY = circRadiusY;

		//---------- Mouse Hit test  ----------
		   // float dist = ofDist(ofGetMouseX(), ofGetMouseY(), slice.labelPoint.x, slice.labelPoint.y);
			//bool sliceHovered = dist <= ((rectFontHitArea.width*1.5f + rectFontHitArea.height*1.5f) / (float)2);

		//return  (ofGetMouseX() >= startSliceX && ofGetMouseY() >= startSliceY &&
		//	ofGetMouseX() < endSliceX && ofGetMouseY() < endSliceY);
	}

    ~WidgetChordWheelSlice() {
    }
    
};

class WidgetChordWheel : public WidgetMusical {

public:
   
    WidgetChordWheel(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }
    
    virtual bool loadState(string widgetXML) override {
        WidgetMusical::loadState(widgetXML);
        
        ofxXmlSettings widgetSettings = ofxXmlSettings();
        if (!widgetSettings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = WidgetMusical::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_WHEEL, 0);
        return mWidgetXML;
    }
    
    virtual ~WidgetChordWheel() {

        circleSlicesT1.clear();
        circleSlicesT2.clear();
        circleSlicesT3.clear();
        
        chordWheelContextMenu->deleteThisWidget();
    }
    
    void setSliceProperties(WidgetChordWheelSlice *slice,
            int currentSlice, float currentAngle, float angleOffset, float degreesPerSlice,
            float circX, float circY, float circRadiusX, float circRadiusY, int tier, bool forceHiglight) {

        bool isHighlightedChord = false;

        // Default, pretty right?
        ofColor rawColor = vizTheory::getColorForKey(slice->parentKey);
         float hue = std::min((float)255, (float)(255 / (double)360) * (degreesPerSlice*(currentSlice-1))); // mixed colours between shared chords
      //  float hue =  rawColor.getHue() + 255.0f * (255.0f / 360.0f rZ/ degreesPerSlice);


        

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
        

            
            
        // TODO :

        
            // Keyboard only mode - space bar to "insert" hovered chord (can hover chords using arrow keys)
        
            // Fix, no selection allowed on T2 or T3 (only allow focused keys chord palatte to be selected)
            // Add menu to specify : Add the widget picker for : color, label, sharps flats, and shape..., mute/unmute audition chord
            // Add inbound scale (currently chromatic!!)
            // CHORD PALETTE :instrument type [keyboard, stringed, generic] - seperate widget which has:
            // manual picker with "+" symbol to add or drag into palatte area
            
            // Brightness: the higher the brightness, the more "correct" the note!
            // Moving - no need to redraw texture, only reposition it.
            // Only resize needs to update the texture
            
            // Show ticks or cross in middle to select / focus.
        
            // Tabs : Chords, Melody, Bass, Harmony [this would be relative to "overall" key], Drums, "Custom".
            // For each defined type, preconfigure with the most relevand widgets (eg chord: chord wheel), but with the ability to add "downstream" widgets
            // Each "Tab" has a dropdown "part" eg Intro, Verse, Chorus (Defaults to "Part 1") . Once "Part 1" is defined, it shows up under EACH tab's dropdown!!!
            // The sequencer simply shows a list of these parts with a trach for each.
            // When a track is selected in the sequencer, all the tabs switch context to that PART!!!
            
            // WHEN TICKED, just the sector GROWS to fill the area, then the "chord spider" (newfangled widget) shows up to the right
            // optionally a more traditional degree picker shows up
            // when multi selecing, play all selected notes at once!
            // when shift clicked, all ALL avail chords (with their corresponnding key colours to the palette area)
            // eg G and Gsharp!! disonance baby

        
        
        /*
         Attach mode (listen for changes) : Parent Key or Connected widget or disconnected!
         
         // Fix circle size! (aspect ratio must be locked!!)

         VST MODE - Tabbed docks with widgets and draggable midi event data
         COMPOSER MODE - the above, but with build in sequencer which receives these graggable events too, in addition : menus system for new docks, export, analyse and visualize functions!
         
         */
        
        
        // A symbol for each key ?? / webding!!! ?
        
  

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
            case 1:
                slice->circRadiusX_End = circRadiusX * TIER1_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER1_RADIUS_PERC;
                break;
            case 2:
                slice->circRadiusX_End = circRadiusX * TIER2_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER2_RADIUS_PERC;
                break;
            case 3:
                slice->circRadiusX_End = circRadiusX * TIER3_RADIUS_PERC;
                slice->circRadiusY_End = circRadiusY * TIER3_RADIUS_PERC;
                break;
        }
        
		slice->circX = circX;
		slice->circY = circY;
		slice->distanceFromCentre = distanceFromCentre;
    }

    void update(Aquamarine::WidgetContext context) override {
        
        font = getSmallFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontScaleNameLabel = getFontSizedForDimensions(getUsableWidth() * 0.5f, getUsableHeight() * 0.5f);
        
        rectFontHitArea = font->rect("G#");
        circleInner.clear();


        // Are we changing color?
        if (getSelectedChordsSize() > 0 && mUnfocusedChordBrightness < 255.0f) {
            mUnfocusedChordBrightness = scaleAnimation(getWidgetId() + "unfocused_slices", mUnfocusedChordBrightness, 255.0f, 1.0f);
            setNeedsUpdate(true);
        }

        float circX = scale(getUsableX() + getUsableWidth()/2.0f);
        float circY = scale(getUsableY() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth() /2.0f);
        float circRadiusY = scale(getUsableHeight()/2.0f);
        
        float degreesPerSliceT1 = 360 / (float)chordsT1.size();
        float degreesPerSliceT2 = 360 / (float)chordsT2.size();
        float degreesPerSliceT3 = 360 / (float)chordsT3.size();

        float circRadiusXT1 = circRadiusX * TIER1_RADIUS_PERC;
        float circRadiusYT1 = circRadiusY * TIER1_RADIUS_PERC;
        
        float angleOffset = degreesPerSliceT2 / (float)2;
        float circRadiusXT2 = circRadiusX * TIER2_RADIUS_PERC;
        float circRadiusYT2 = circRadiusY * TIER2_RADIUS_PERC;
        
        float circRadiusXT3 = circRadiusX * TIER3_RADIUS_PERC;
        float circRadiusYT3 = circRadiusY * TIER3_RADIUS_PERC;

        
        // DEFAULT STATE WITHOUT ALTERNATION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        for (int i = 1; i <= circleSlicesT1.size() ; i++) {
            // T1
            // The current degrees position
            float currentAngleT1 = ((float)degreesPerSliceT1*i);
            WidgetChordWheelSlice *sliceT1 = &circleSlicesT1[i-1];
            
            
            if (isSelectedChordRoot(sliceT1->originalParentKey)) {
                sliceT1->chord = sliceT1->originalChord;
                sliceT1->parentKey = sliceT1->originalParentKey;
            }
            setSliceProperties(sliceT1, i, currentAngleT1, mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, false);

            
            // T2
            for (int j = i*2-1; j <= i*2 ; j++) {
                // The current degrees position T2
                float currentAngleT2 = ((float)degreesPerSliceT2*j);
                WidgetChordWheelSlice *sliceT2 = &circleSlicesT2[j-1];
                
                if (isSelectedChordRoot(sliceT2->originalParentKey)) {
                    sliceT2->chord = sliceT2->originalChord;
                    sliceT2->parentKey = sliceT2->originalParentKey;
                }
                setSliceProperties(sliceT2, j, currentAngleT2, mWheelOffest + angleOffset, degreesPerSliceT2, circX, circY, circRadiusXT2, circRadiusYT2, 2, false);
            }

            // T3
            // The current degrees position T3
            float currentAngleT3 = ((float)degreesPerSliceT3*i);
            WidgetChordWheelSlice *sliceT3 = &circleSlicesT3[i-1];
            if (isSelectedChordRoot(sliceT3->originalParentKey)) {
                sliceT3->parentKey = sliceT3->originalParentKey;
            }
            setSliceProperties(sliceT3, i, currentAngleT3, mWheelOffest, degreesPerSliceT3, circX, circY, circRadiusXT3, circRadiusYT3, 3, false);
        }

        // ALTERNATED KEYS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        for (int i=T1Alternator; i<=12; i=i+3) {
            
            int keyIndex = i - 1;
            int nextKeyIndex = (keyIndex == 11) ?  0 : (keyIndex + 1);
            int prevKeyIndex = (keyIndex == 0) ?  11 : (keyIndex - 1);
            
            string curKey = chordMatrixCurrent[keyIndex][0].getChordRoot();
            string nextKey = chordMatrixCurrent[nextKeyIndex][0].getChordRoot();
            string prevKey = chordMatrixCurrent[prevKeyIndex][0].getChordRoot();
            
            if (getSelectedChordsSize() == 0 || (getSelectedChordsSize() > 0 && (isSelectedChordRoot(curKey)))) {
            
                // T1 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                vizChord currKeyIChord      = chordMatrixCurrent[keyIndex][0];    // curr I  (same as nextKeyIVChord in Ionian mode)
                vizChord currKeyIIChord     = chordMatrixCurrent[keyIndex][1];    // curr II (same as prevKeyVIChord in Ionian mode)
                vizChord currKeyIIIChord    = chordMatrixCurrent[keyIndex][2];
                vizChord currKeyIVChord     = chordMatrixCurrent[keyIndex][3];
                vizChord currKeyVChord      = chordMatrixCurrent[keyIndex][4];
                vizChord currKeyVIChord     = chordMatrixCurrent[keyIndex][5];
                vizChord currKeyVIIChord    = chordMatrixCurrent[keyIndex][6];

                WidgetChordWheelSlice *sliceT1_I = &circleSlicesT1[keyIndex];
                sliceT1_I->chord = currKeyIChord;
                sliceT1_I->parentKey = curKey;
                sliceT1_I->prevKey = prevKey;
                sliceT1_I->nextKey = nextKey;
                sliceT1_I->degree = vizTheory::DegreeName::majorUnison;
                setSliceProperties(sliceT1_I, i, (float)degreesPerSliceT1*i, mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, true);

                WidgetChordWheelSlice *sliceT1_V = &circleSlicesT1[nextKeyIndex];
                sliceT1_V->chord = currKeyVChord;
                sliceT1_V->parentKey = curKey;
                sliceT1_V->prevKey = prevKey;
                sliceT1_V->nextKey = nextKey;
                sliceT1_V->degree = vizTheory::DegreeName::perfectFifth;
                setSliceProperties(sliceT1_V, i, (float)degreesPerSliceT1*(i+1), mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, true);

                WidgetChordWheelSlice *sliceT1_IV = &circleSlicesT1[prevKeyIndex];
                sliceT1_IV->chord = currKeyIVChord;
                sliceT1_IV->parentKey = curKey;
                sliceT1_IV->prevKey = prevKey;
                sliceT1_IV->nextKey = nextKey;
                sliceT1_IV->degree = vizTheory::DegreeName::perfectFourth;
                setSliceProperties(sliceT1_IV, i, (float)degreesPerSliceT1*(i-1), mWheelOffest, degreesPerSliceT1, circX, circY, circRadiusXT1, circRadiusYT1, 1, true);


                // T2 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                int j = i*2-1;
                int nextKeyIndex2 = (i == 12) ?  24 : (j + 1);
                int nextKeyIndex3 = (i == 12) ?  1 : (j + 2);

                WidgetChordWheelSlice *sliceT2_II = &circleSlicesT2[j-1];
                sliceT2_II->chord = currKeyIIChord;
                sliceT2_II->parentKey = curKey;
                sliceT2_II->prevKey = prevKey;
                sliceT2_II->nextKey = nextKey;
                sliceT2_II->degree = vizTheory::DegreeName::majorSecond;
                setSliceProperties(sliceT2_II, j, (float)degreesPerSliceT2*j, mWheelOffest + angleOffset, degreesPerSliceT2, circX, circY, circRadiusXT2, circRadiusYT2, 2, true);

                WidgetChordWheelSlice *sliceT2_III = &circleSlicesT2[nextKeyIndex2-1];
                sliceT2_III->chord = currKeyIIIChord;
                sliceT2_III->parentKey = curKey;
                sliceT2_III->prevKey = prevKey;
                sliceT2_III->nextKey = nextKey;
                sliceT2_III->degree = vizTheory::DegreeName::majorThird;
                setSliceProperties(sliceT2_III, j+1, (float)degreesPerSliceT2*(j+1), mWheelOffest + angleOffset, degreesPerSliceT2, circX, circY, circRadiusXT2, circRadiusYT2, 2, true);

                WidgetChordWheelSlice *sliceT2_VI = &circleSlicesT2[nextKeyIndex3-1];
                sliceT2_VI->chord = currKeyVIChord;
                sliceT2_VI->parentKey = curKey;
                sliceT2_VI->prevKey = prevKey;
                sliceT2_VI->nextKey = nextKey;
                sliceT2_VI->degree = vizTheory::DegreeName::majorSixth;
                setSliceProperties(sliceT2_VI, j+2, (float)degreesPerSliceT2*(j+2), mWheelOffest + angleOffset, degreesPerSliceT2, circX, circY, circRadiusXT2, circRadiusYT2, 2, true);

                // T3 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                WidgetChordWheelSlice *sliceT3_VII = &circleSlicesT3[keyIndex];
                sliceT3_VII->chord = currKeyVIIChord;
                sliceT3_VII->parentKey = curKey;
                sliceT3_VII->prevKey = prevKey;
                sliceT3_VII->nextKey = nextKey;
                sliceT3_VII->degree = vizTheory::DegreeName::majorSeventh;
                setSliceProperties(sliceT3_VII, i, (float)degreesPerSliceT3*i, mWheelOffest, degreesPerSliceT3, circX, circY, circRadiusXT3, circRadiusYT3, 3, true);
            }
        }


        circleInner.setCircleResolution(360); // Can lower or remove to bump up performance
        circleInner.setFilled(true);
        circleInner.arc(circX, circY, circRadiusX/(float)3, circRadiusY/(float)3, 0, 360);
		vizElm_circleInner.update(circleInner);

        circleInnerPoint.set(circX, circY);
    }

    void drawSlice(int tier, int currentSlice, WidgetChordWheelSlice &slice) {

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
                        if (tier == 1 && getIsMousePressedAndReleasedOverWidget(false)) {
                            
                           if(!matchesSelectedChordRoot(slice.chord)) {
                               
                               int pos = vizTheory::getPositionInCircleOfFifthsForKey(slice.chord.getChordRoot());
                               addSelectedChord(chordMatrixCurrent[pos-1][0], true, true);
                               
                               if (pos == 1 || pos == 4 || pos == 7 || pos == 10) {
                                    T1Alternator = 1;
                                } else  if (pos == 2 || pos == 5 || pos == 8 || pos == 11) {
                                    T1Alternator = 2;
                                }  else  if (pos == 3 || pos == 6 || pos == 9 || pos == 12) {
                                    T1Alternator = 3;
                                }
                                
                            } else {
                                removeSelectedChordRoot(slice.chord);
                            }

                            setNeedsUpdate(true);
                        } else if (getIsMousePressedOverWidget(false)) {
                            setDraggingChord(slice.chord);
                        }
                    }

                    if (tier == 1 && matchesSelectedChordRoot(slice.chord))  {
                        slice.isSelected = true;
                        ofColor innerDotCol = slice.selectedColor;
                        innerDotCol.setSaturation(30);
                        innerDotCol.setBrightness(255);
                        circleInner.setColor(innerDotCol);
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
        
        WidgetMusical::onWidgetKeyPressed(e);
        
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
        bool needsUpdate = WidgetMusical::needsUpdateBeforeDraw(false);

        if (getTimerMillis() >= 2000) {
            if (shouldResetTimer) resetTimer();
            
            T1Alternator++;
            if (T1Alternator > 3) {
                T1Alternator = 1;
            }
            needsUpdate = true;
        }
        
        return needsUpdate;
    }
    
    void draw(Aquamarine::WidgetContext context) override {
        
        // Draw the slices
        for(int i=1; i<=circleSlicesT3.size(); i++){
            drawSlice(3, i, circleSlicesT3[i-1]);
        }
        
        for(int i=1; i<=circleSlicesT2.size(); i++){
            drawSlice(2, i, circleSlicesT2[i-1]);
        }
        
        for(int i=1; i<=circleSlicesT1.size(); i++){
            drawSlice(1, i, circleSlicesT1[i-1]);
        }
        
		vizElm_circleInner.setColor(getLargeLabelStateColor());
		vizElm_circleInner.draw();


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
    
    Widget* getPopoutWidgetForMenuTag(int menuTag) override {
        switch(menuTag) {
            case Aquamarine::IconCache::IconTag::WIDGET_SETTINGS:
                return chordWheelContextMenu;
            default:
                return nullptr;
        }
    }
    
    void onWidgetMousePressed(ofMouseEventArgs &e) override {
        if (e.button == OF_MOUSE_BUTTON_RIGHT) {

            vizChord hoveredChord = getHoveredChord();
            chordDesignerMenuItem->addSelectedChord(hoveredChord, true, true);

            showContextMenu(Aquamarine::IconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX())-20, deScale(ofGetMouseY())-20);
        }
    }
    
    void setSelectedScale(string val, bool includeInstrumentRules) override {
        WidgetMusical::setSelectedScale(val, includeInstrumentRules);
        initScale();
        T1Alternator = 1;
    }

    void setTheoryVizNoteMode(TheoryVizNoteMode theoryVizNoteMode) override {
        WidgetMusical::setTheoryVizNoteMode(theoryVizNoteMode);
        clearSelectedChords();
        initScale();
    }
    
private:
    Widget *chordWheelContextMenu = nullptr;
    WidgetChordDesigner* chordDesignerMenuItem = nullptr;
    
    
    int T1Alternator = 3;
    
	// Get the desired diatoic scale starting on C and convert it to Circle of Fifths

	vector<vizChord> chordsT1; //= getCircleOfFifths();
	vector<vizChord> chordsT2; //= { "Dm", "Em", "Am", "Bm", "Em", "F#m", "Bm", "C#m", "F#m", "G#m", "C#m", "D#m",
							  // "G#m", "A#m", "Ebm", "Fm", "Bbm", "Cm", "Fm", "Gm", "Cm", "Dm", "Gm", "Am" };
	vector<vizChord> chordsT3; //= { "Bdim", "F#dim", "C#dim", "G#dim", "D#dim", "A#dim", "Fdim", "Cdim", "Gdim", "Ddim", "Adim", "Edim" };

    
    vector<vector<vizChord>> chordMatrixSharps;
    vector<vector<vizChord>> chordMatrixFlats;
    vector<vector<vizChord>> chordMatrixCurrent;
    
    float TIER1_RADIUS_PERC = 0.6f;
    float TIER2_RADIUS_PERC = 0.8f;
    float TIER3_RADIUS_PERC = 1.0f;

    vector<WidgetChordWheelSlice> circleSlicesT1;
    vector<WidgetChordWheelSlice> circleSlicesT2;
    vector<WidgetChordWheelSlice> circleSlicesT3;
    
    shared_ptr<ofxSmartFont> font;
    
    // try a font size for each tier
    
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
    float mUnfocusedChordBrightness = 155.0;
    float mFocusedChordBrghtness = 100;
    
    enum MENU_GROUP_1 {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_NOTE_MODE = 2,
        MENU_TAB_CHORD_SCALE = 3,
        MENU_TAB_SETTINGS = 4,
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
        chordsT2.clear();
        chordsT3.clear();
        
        circleSlicesT1.clear();
        circleSlicesT2.clear();
        circleSlicesT3.clear();
        
        for (int key=0; key<chordMatrixCurrent.size(); key++) {
            
            int nextKeyIndex = (key == 11) ?  0 : (key + 1);
            int prevKeyIndex = (key == 0) ?  11 : (key - 1);
            
            string curKey = chordMatrixCurrent[key][0].getChordRoot();
            string nextKey = chordMatrixCurrent[nextKeyIndex][0].getChordRoot();
            string prevKey = chordMatrixCurrent[prevKeyIndex][0].getChordRoot();
            
            vizChord currKeyIChord      = chordMatrixCurrent[key][0];    // curr I  (same as nextKeyIVChord in Ionian mode)
            vizChord currKeyIIChord     = chordMatrixCurrent[key][1];    // curr II (same as prevKeyVIChord in Ionian mode)
            vizChord currKeyIIIChord    = chordMatrixCurrent[key][2];
            vizChord currKeyIVChord     = chordMatrixCurrent[key][3];
            vizChord currKeyVChord      = chordMatrixCurrent[key][4];
            vizChord currKeyVIChord     = chordMatrixCurrent[key][5];
            vizChord currKeyVIIChord    = chordMatrixCurrent[key][6];
            
            WidgetChordWheelSlice sliceT1_I, sliceT2_II, sliceT2_III, sliceT3_VII;
            
            /***********
             * T1 RING *
             ***********/
            
            // I chord
            chordsT1.push_back(currKeyIChord);
            sliceT1_I.chord = currKeyIChord;
            sliceT1_I.originalChord = currKeyIChord;
            sliceT1_I.parentKey = curKey;
            sliceT1_I.originalParentKey = curKey;
            sliceT1_I.prevKey = prevKey;
            sliceT1_I.nextKey = nextKey;
            sliceT1_I.degree = vizTheory::DegreeName::majorUnison;
            sliceT1_I.originalDegree = vizTheory::DegreeName::majorUnison;
            circleSlicesT1.push_back(sliceT1_I);
            
            
            /***********
             * T2 RING *
             ***********/
            
            // II chord
            chordsT2.push_back(currKeyIIChord);
            sliceT2_II.chord = currKeyIIChord;
            sliceT2_II.originalChord = currKeyIIChord;
            sliceT2_II.parentKey = curKey;
            sliceT2_II.originalParentKey = curKey;
            sliceT2_II.prevKey = prevKey;
            sliceT2_II.nextKey = nextKey;
            sliceT2_II.degree = vizTheory::DegreeName::majorSecond;
            sliceT2_II.originalDegree = vizTheory::DegreeName::majorSecond;
            circleSlicesT2.push_back(sliceT2_II);
            
            
            // III chord
            chordsT2.push_back(currKeyIIIChord);
            sliceT2_III.chord = currKeyIIIChord;
            sliceT2_III.originalChord = currKeyIIIChord;
            sliceT2_III.parentKey = curKey;
            sliceT2_III.originalParentKey = curKey;
            sliceT2_III.prevKey = prevKey;
            sliceT2_III.nextKey = nextKey;
            sliceT2_III.degree = vizTheory::DegreeName::majorThird;
            sliceT2_III.originalDegree = vizTheory::DegreeName::majorThird;
            circleSlicesT2.push_back(sliceT2_III);
            
            
            /***********
             * T3 RING *
             ***********/
            
            // VII chord
            chordsT3.push_back(currKeyVIIChord);
            sliceT3_VII.chord = currKeyVIIChord;
            sliceT3_VII.originalChord = currKeyVIIChord;
            sliceT3_VII.parentKey = curKey;
            sliceT3_VII.originalParentKey = curKey;
            sliceT3_VII.prevKey = prevKey;
            sliceT3_VII.nextKey = nextKey;
            sliceT3_VII.degree = vizTheory::DegreeName::majorSeventh;
            sliceT3_VII.originalDegree = vizTheory::DegreeName::majorSeventh;
            circleSlicesT3.push_back(sliceT3_VII);
        }
        
        float degreesOffset = getAngleOffsetForSlice(1);
        mWheelOffest = degreesOffset;
        
      //  setTheoryVizColorMode(WidgetMusical::TheoryVizColorMode::KEYS);
      //  setTheoryVizLabelMode(WidgetMusical::TheoryVizLabelMode::KEYS);
        
        setTitle(getSelectedScaleNamePretty());
        setNeedsUpdate(true);
    }
    
    void initWidget() override {

        if (getSelectedScaleName() == "") {
            setSelectedScale("ionian", true);
        }
        
        if (!chordWheelContextMenu) {

            chordDesignerMenuItem = new WidgetChordDesigner(
                getWidgetId() + "_MENU_CHORD_DESIGNER",
                "<widget><bounds width='300' height='300' minWidth='200' minHeight='200'/><appearance/></widget>"
                );


            chordWheelContextMenu = new Aquamarine::WidgetMenu(getWidgetId() + "_CP_MENU1", "<widget><bounds width='100' height='300'/></widget>", getWidgetId()
                , Aquamarine::WidgetMenu::PreferredPopoutDirection::DOWN, {
                // ----------------------------------------------------------------------------
                // Label mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("LABEL"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE, {
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("NONE"), (int)TheoryVizLabelMode::NONE),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("KEY"), (int)TheoryVizLabelMode::KEYS, false, true),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), (int)TheoryVizLabelMode::DEGREES),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                }),
                
                // ----------------------------------------------------------------------------
                // Color mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("COLOR"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_COLOR"), MENU_GROUP_1::MENU_TAB_THEORY_COLOR_MODE, {
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("NONE"), (int)TheoryVizColorMode::NONE),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("KEY"), (int)TheoryVizColorMode::KEYS, false, true),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("DEGREE"), (int)TheoryVizColorMode::DEGREES),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("ALTERNATE_KEYS_DEGREES"), -1000)
                    //Aquamarine::WidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
                }),
                    
                // ----------------------------------------------------------------------------
                // Note mode menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("NOTE_MODE"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_NOTE_MODE, {
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("DEFAULT"), (int)TheoryVizNoteMode::DEFAULT, false, true),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("SHARP"), (int)TheoryVizNoteMode::SHARP),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("FLAT"), (int)TheoryVizNoteMode::FLAT)
                }),

                // ----------------------------------------------------------------------------
                // Scale / menu mode
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab("Modes Tabs", Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_SCALE"), MENU_GROUP_1::MENU_TAB_CHORD_SCALE, {
                    Aquamarine::WidgetMenuItem("Ionian", 1, false, true),
                    Aquamarine::WidgetMenuItem("Dorian", 2),
                    Aquamarine::WidgetMenuItem("Phrygian", 3),
                    Aquamarine::WidgetMenuItem("Lydian", 4),
                    Aquamarine::WidgetMenuItem("Mixolydian", 5),
                    Aquamarine::WidgetMenuItem("Aeolian", 6),
                    Aquamarine::WidgetMenuItem("Locrian", 7),
                    // ADD DIVIDER, and set degree color for hover state
                    Aquamarine::WidgetMenuItem("Melodic Minor", 8),
                    Aquamarine::WidgetMenuItem("Melodic Minor II", 9),
                    Aquamarine::WidgetMenuItem("Melodic Minor III", 10),
                    Aquamarine::WidgetMenuItem("Melodic Minor IV", 11),
                    Aquamarine::WidgetMenuItem("Melodic Minor V", 12),
                    Aquamarine::WidgetMenuItem("Melodic Minor VI", 13),
                    Aquamarine::WidgetMenuItem("Melodic Minor VII", 14)
                }),

               // ----------------------------------------------------------------------------
                // Chord Designer menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("CHORD_DESIGNER"), Aquamarine::IconCache::getIcon("MED_CONTENT_THEORY_LABEL"),
                                MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER,
                                chordDesignerMenuItem
                                ),                
                
                // ----------------------------------------------------------------------------
                // Settings menu
                // ----------------------------------------------------------------------------
                Aquamarine::WidgetMenuTab(Aquamarine::Shared::lang("SETTINGS"), Aquamarine::IconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("SOUND"), 1, true, true),
                    Aquamarine::WidgetMenuItem(Aquamarine::Shared::lang("SAVE"), 2)
                })
                
            });

            ofAddListener(dynamic_cast<Aquamarine::WidgetMenu*>(chordWheelContextMenu)->menuItemSelected, this, &WidgetChordWheel::onMenuItemSelected);
            
            Aquamarine::WidgetManager::addWidget(*chordWheelContextMenu, false, getWidgetId());
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

    void onMenuItemSelected(Aquamarine::WidgetMenuItemArgs & args) {

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
    
    
    ofColor getLabelStateColor(WidgetChordWheelSlice slice) {
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


