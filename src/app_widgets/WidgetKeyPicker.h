//
//  WidgetKeyPicker.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"
#include "WidgetMusical.h"

//------------------------------ Key Picker widget --------------------------------

class WidgetKeyPickerSlice {
public:
    vizNote note;
	Aquamarine::Elm path;
    ofPoint labelPoint;
    ofColor regularColor;
    ofColor selectedColor;
    ofColor hoveredColor;
    ofColor regularFontColor;
    ofColor selectedFontColor;
    ofColor hoveredFontColor;
    bool isHovered = false;
    bool isSelected = false;
    
    ~WidgetKeyPickerSlice() {
    }
};

class WidgetKeyPicker :  public WidgetMusical {

public:
   
    
    
    WidgetKeyPicker(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
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
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER, 0);
        return mWidgetXML;
    }
    
    virtual ~WidgetKeyPicker() {
        
        keys.clear();
        circleSlices.clear();

    }
    
    void update(Aquamarine::WidgetContext context) override {
        font = getFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        rectFontHitArea = font->rect("G#");
        circleInner.clear();

        float circX = scale(getUsableX() + getUsableWidth()/2.0f);
        float circY = scale(getUsableY() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth() /2.0f);
        float circRadiusY = scale(getUsableHeight()/2.0f);
        
        float degreesPerSlice = (float)360 / (float)keys.size();
        float currentAngle = 0;
  
        for (int i = 1; i <= circleSlices.size() ; i++) {

            WidgetKeyPickerSlice* slice = &circleSlices[i-1];
            
            // The current degrees position
            currentAngle = ((float)degreesPerSlice*i);
           
            ofColor color = vizTheory::getColorForKey(slice->note.getNoteName());
            
 
            //---------- Draw a slice ----------
            slice->regularColor = ofColor::fromHsb(color.getHue(), getSelectedKey().getNoteName() == "" ? 200 : 100, 200);
            slice->hoveredColor = ofColor::fromHsb(color.getHue(), 220, 255);
            slice->selectedColor = ofColor::fromHsb(color.getHue(), 220, 255);
            
            slice->regularFontColor = getSelectedFontColor(slice->note.getNoteName());
            slice->hoveredFontColor = getSelectedFontColor(slice->note.getNoteName());
            slice->selectedFontColor = getSelectedFontColor(slice->note.getNoteName());
            
			ofPath c;
			c.setCircleResolution(360);
			/* Expensive operation: Keep OUT of draw cycle */

            c.moveTo(circX, circY);
			c.arc(circX, circY, circRadiusX, circRadiusY, (float)currentAngle + (float)angleOffset, degreesPerSlice + (float)angleOffset);
			c.close();
			// slice->regularColor = ofColor::fromHsb(color.getHue(), 220, 220);
			slice->path.update(c);
            
            //---------- Label plot calculations for slice ----------
            float midSlice = ((float)degreesPerSlice/2)  + (float)currentAngle + (float)angleOffset;
            float distanceFromCentre = 0.75;
            ofRectangle rect = font->rect(slice->note.getNoteName());
            float fontWidth = rect.width;
            float fontHeight = rect.height;
            
            // Now that we have the middle of the slice angle, we use cos, sin on it, and multiply a distanceFromCentre factor on the angle to work
            // out a label coordinate. Finally we have the centre of the font to the x, y coords!
            
            float plotX = (float)(circX - fontWidth /(float) 2) + circRadiusX * distanceFromCentre * (float)cos((float)ofDegToRad(midSlice));
            float plotY = (float)(circY + fontHeight/(float) 2) + circRadiusY * distanceFromCentre * (float)sin((float)ofDegToRad(midSlice));
            slice->labelPoint = ofPoint(plotX, plotY);
        }

        circleInner.setCircleResolution(360); // Can lower or remove to bump up performance
        circleInner.setFilled(true);
        circleInner.arc(circX, circY, circRadiusX/(float)2, circRadiusY/(float)2, 0, 360);
		vizElm_circleInner.update(circleInner);
        circleInnerPoint.set(circX, circY);
    }
    
    void draw(Aquamarine::WidgetContext context) override {
        // Draw the slices
		bool anyNoteHovered = false;
        for(WidgetKeyPickerSlice& slice:circleSlices){
           // WidgetKeyPickerSlice& slice = circleSlices[i-1];
            
            slice.path.setColor(slice.regularColor); 

            //---------- Mouse Hit test  ----------
            float dist = ofDist(ofGetMouseX(), ofGetMouseY(), slice.labelPoint.x, slice.labelPoint.y);
            bool sliceHovered = dist <= ((rectFontHitArea.width*1.5f + rectFontHitArea.height*1.5f) / (float)2);
            slice.isHovered = false;
            slice.isSelected = false;
            bool doesMatchSelectedKey = matchesSelectedKey(slice.note);
            bool didSelectKey = false;

            if (sliceHovered || doesMatchSelectedKey)  {

                didSelectKey = (sliceHovered && getIsMousePressedOverWidget(false));
                if (doesMatchSelectedKey || didSelectKey)  {
                    slice.isSelected = true;
                    slice.path.setColor(slice.selectedColor);
                    vizElm_circleInner.setColor(slice.selectedColor);
                    
                    if (didSelectKey) {
                        setSelectedKey(slice.note);
                        uiVizNoteSelectedArgs args("Key Picker", slice.note);
                        ofNotifyEvent(keySelected, args);
                    }
                } else {
                    slice.path.setColor(slice.hoveredColor);
                    if (getSelectedKey().getNoteName() == "") vizElm_circleInner.setColor(slice.hoveredColor);                
                    slice.isHovered = true;
                    setHoveredKey(slice.note);
                    if (sliceHovered) {
                        anyNoteHovered = true;
                        auditionNote(slice.note);
                    }
                }
            }

            slice.path.draw();
            // Event Stuff


            ofPushStyle();
            ofSetColor(getLabelStateColor(slice));
            font->draw(slice.note.getNoteName(), slice.labelPoint.x, slice.labelPoint.y);
            ofPopStyle();
			//if (!anyNoteHovered) clearHoveredKey();
        }
    

        // Draw the inner dot
        if (getSelectedKey().getNoteName() != "") {
			vizElm_circleInner.draw();    

            ofPushStyle();            
            ofSetColor(vizTheory::getColorForKey(getSelectedKey().getNoteName()), 255);                    
            rectLargeLabel = fontLargeLabel->rect(getSelectedKey().getNoteName());          
            drawFontWithShadow(
                fontLargeLabel, getSelectedKey().getNoteName(), 
                circleInnerPoint.x - rectLargeLabel.width / 2.0f,
                circleInnerPoint.y + rectLargeLabel.height / 2.0f,
                getLargeLabelStateColor(), 
                getFaintFontColor_Dark(getSelectedKey().getNoteName()));
            ofPopStyle();
		}
		else {
            ofPushStyle();              
			ofSetColor(ofColor::white);
			vizElm_circleInner.draw();
            ofPopStyle();               
		}

    }
    
    
    void updateMinimized() {
        font = getFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
        circleInner.clear();
        
        float circX = scale(getUsableX() + getUsableWidth()/2.0f);
        float circY = scale(getUsableY() + getUsableHeight()/2.0f);
        float circRadiusX = scale(getUsableWidth());
        float circRadiusY = scale(getUsableHeight());
        
        circleInner.setCircleResolution(360); // Can lower or remove to bump up performance
        circleInner.setFilled(true);
        circleInner.arc(circX, circY, circRadiusX/(float)2, circRadiusY/(float)2, 0, 360);
        vizElm_circleInner.setColor(vizTheory::getColorForKey(getSelectedKey().getNoteName()));        
		vizElm_circleInner.update(circleInner);
        circleInnerPoint.set(circX, circY);
        
    }

    virtual void setSelectedKey(vizNote val) override {
        WidgetMusical::setSelectedKey(val);
        setNeedsUpdate(true);
    }    
    
    void drawMinimized() {
        
        if (getSelectedKey().getNoteName() == "") {
            setSelectedKey(vizNote("C", 3, 0, vector<string>{""}));
        }
            
        ofPushStyle();              
        vizElm_circleInner.draw();
        ofPopStyle();               

        ofPushStyle();              
        rectLargeLabel = fontLargeLabel->rect(getSelectedKey().getNoteName());
        
        drawFontWithShadow(
            fontLargeLabel, getSelectedKey().getNoteName(), 
            circleInnerPoint.x - rectLargeLabel.width / 2.0f,
            circleInnerPoint.y + rectLargeLabel.height / 2.0f,
            getLargeLabelStateColor(), 
            getFaintFontColor_Dark(getSelectedKey().getNoteName()));
        ofPopStyle();                 
    }
    
    void onWidgetMouseContentDragged(ofMouseEventArgs &e) override {
        if (getSelectedKey().getNoteName() != "") {
            setDraggingNote(getSelectedKey());
            setDragData(getSelectedKey().getXML());
        }
    }
    

private:
    vector<string> keys = vizTheory::getCircleOfFifths();
    
    /*
    switch(getTheoryVizNoteMode()) {
        case TheoryVizNoteMode::SHARP:
            keys = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::SHARP); break;
        case TheoryVizNoteMode::FLAT:
            keys = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::FLAT); break;
        case TheoryVizNoteMode::DEFAULT:
        default:
            keys = vizScale::getNotesForCircleOfFifths(vizTheory::NoteMode::DEFAULT); break;
    }
    */
    
   //     vector<string> keys = getChromaticScaleSharps();
    vector<WidgetKeyPickerSlice> circleSlices;
    
    shared_ptr<ofxSmartFont> font = getFontSizedForDimensions(getUsableWidth(), getUsableHeight());
    shared_ptr<ofxSmartFont> fontLargeLabel = getLargeFontSizedForDimensions(getUsableWidth(), getUsableHeight());
    
    
    ofPath circleInner;
	Aquamarine::Elm vizElm_circleInner;
    ofRectangle rectLargeLabel;
    ofColor largeLabelColor;
    ofRectangle rectFontHitArea;
    ofPoint circleInnerPoint;

    float degreesOffset = getAngleOffsetForSlice(1);
    float mWheelOffest = degreesOffset; // use for animation
    float angleOffset = mWheelOffest;
    
    // Set up the slices with note data (colors, notes, etc)
    void initWidget() override {

        setIsAutoUpdateWhenActive(true);
        
        for (int i = 1; i <= keys.size() ; i++) {
            WidgetKeyPickerSlice slice;// = new WidgetKeyPickerSlice();
 
            slice.note = vizNote(keys[i-1], 3, i,
                                     vector<string>{"Key of " + keys[i-1]},
                                 vizTheory::getColorForKey(keys[i-1]));
            
            circleSlices.push_back(slice);
        }
    }
    
    ofColor getLabelStateColor(WidgetKeyPickerSlice slice) {
        if (slice.isHovered || slice.isSelected) {
            if (slice.isSelected) {
                return slice.selectedFontColor;
            } else {
                return slice.hoveredFontColor;
            }
        }
        return slice.regularFontColor;
    }
    
    ofColor getLargeLabelStateColor() {
        if (getSelectedKey().getNoteName() != "") {
            return getSelectedFontColor(getSelectedKey().getNoteName());
        }
        
        if (getHoveredKey().getNoteName() != "") {
            return getSelectedFontColor(getHoveredKey().getNoteName());
        }
        return ofColor::white;
    }
    
    float getAngleOffsetForSlice(int sliceNumber) {
        float degreesPerSlice = 360 / (float)keys.size();
        return 270 - degreesPerSlice - (degreesPerSlice / (float)2) - ((sliceNumber - 1) * (float)degreesPerSlice);
    }
    
};


