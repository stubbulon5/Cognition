
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "../uiViz/widget/uiVizWidgetMenu.h"
#include "uiVizWidgetMusical.h"
#include "uiVizWidgetKeyPicker.h"
#include "uiVizWidgetScalePicker.h"
#include "uiVizWidgetChordWheel.h"
#include "uiVizWidgetChordDesigner.h"
#include "uiVizWidgetDialog.h"
#include "uiVizWidgetNotesTable.h"
#include "uiVizWidgetMusicalHelper.h"

//------------------------------ Stringed Instrument base --------------------------------

/***********************************************************************************

 
 ***********************************************************************************/
class uiVizWigetStringedInstrumentString
{
public:
    vizNote note;
    vizNote highestNoteAdded;
    vizNote lowestNoteAdded;

    int thickness;
    int offset = 0;
    bool isEnabled = true;
    bool dontPlay = false;
    uiVizElm path;
    ofColor color = ofColor(0, 0, 0, 180);
    ofColor disabledColor = ofColor(0, 0, 0, 45);
    uiVizWigetStringedInstrumentString() {}
    uiVizWigetStringedInstrumentString(vizNote note, int thickness) : note(note), thickness(thickness) {}
    uiVizWigetStringedInstrumentString(vizNote note, int thickness, int offset) : note(note), thickness(thickness), offset(offset) {}
    uiVizWigetStringedInstrumentString(vizNote note, int thickness, ofColor color) : note(note), thickness(thickness), color(color) {}
    uiVizWigetStringedInstrumentString(vizNote note, int thickness, int offset, ofColor color) : note(note), thickness(thickness), offset(offset), color(color) {}

    void setStartFret(int val)
    {
        mStartFret = val;
    }

    int getStartFret()
    {
        return mStartFret;
    }

    void setEndFret(int val)
    {
        mEndFret = val;
    }

    int getEndFret()
    {
        return mEndFret;
    }

    void setFretPoints_CSV(string fretPoints_CSV)
    {
        mFretPoints_CSV = fretPoints_CSV;
        //cout << "SETTING FRETPOINTS FOR [" <<  note.getNoteName() << ofToString(note.getNoteOctave()) << "] :" << fretPoints_CSV << "\n";
        //cout << ",---------------------------------------------";
    }

    string getFretPoints_CSV()
    {
        return mFretPoints_CSV;
    }

    ~uiVizWigetStringedInstrumentString()
    {
    }

private:
    int mStartFret = 0;
    int mEndFret = 3;
    string mFretPoints_CSV = "";
};

class uiVizWigetStringedInstrumentFret
{
public:
    uiVizElm path;
    uiVizElm inlayPath;
    bool hasInlay = false;
    float fretPos = 0.0f;
    float prevFretDist = 0.0f;
    float fretDist = 0.0f;
    uiVizElm fretArea;

    ofColor color = ofColor(0, 0, 0, 180);
    ofColor disabledColor = ofColor(0, 0, 0, 45);

    ~uiVizWigetStringedInstrumentFret()
    {
    }
};

class uiVizWigetStringedInstrumentPoint
{
public:
    uiVizWigetStringedInstrumentString *instrumentstring;
    int fret;
    bool isHovered = false;
    bool isSelected = false;
    uiVizElm path, highlightPath;
    ofColor color = ofColor(255, 255, 255, 180);
    string pointLabelText = "";
    ofRectangle pointLabelRect;
    bool isExtended = false;
    int sequenceNumber = 0;

    uiVizWigetStringedInstrumentPoint(uiVizWigetStringedInstrumentString *string, int fret) : instrumentstring(string), fret(fret) { initNote(string, fret); }
    uiVizWigetStringedInstrumentPoint(uiVizWigetStringedInstrumentString *string, int fret, bool isExtended) : instrumentstring(string), fret(fret), isExtended(isExtended) { initNote(string, fret); }
    uiVizWigetStringedInstrumentPoint(uiVizWigetStringedInstrumentString *string, int fret, bool isExtended, int sequenceNumber) : instrumentstring(string), fret(fret), isExtended(isExtended), sequenceNumber(sequenceNumber) { initNote(string, fret); }
    uiVizWigetStringedInstrumentPoint(uiVizWigetStringedInstrumentString *string, int fret, ofColor color) : instrumentstring(string), fret(fret), color(color) { initNote(string, fret); }

    vizNote getNoteForPoint(bool useSharp)
    {
        //vizNote note = instrumentstring->note.getCalculatedNoteForOffset(fret, useSharp);
        return note;
    }

    int getNoteOctave()
    {
        return note.getNoteOctave();
    }

    bool getIsMouseHovered()
    {

        int mouseX = ofGetMouseX();
        int mouseY = ofGetMouseY();

        return false;
    }

    void setHighlightPathSet(bool val)
    {
        highlightPathSet = val;
    }

    bool getHighlightPathSet()
    {
        return highlightPathSet;
    }

    ~uiVizWigetStringedInstrumentPoint()
    {
    }

private:
    vizNote note;
    bool highlightPathSet = false;
    void initNote(uiVizWigetStringedInstrumentString *string, int fret)
    {
        note = instrumentstring->note.getCalculatedNoteForOffset(fret, false);
        note.setSequenceNumber(sequenceNumber);
    }
};

class uiVizWigetStringedInstrument : public uiVizWidgetMusical
{

public:
    /*
    enum Orientation {
        HORIZONTAL,
        VERTICAL
    };
     */

    uiVizWigetStringedInstrument(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML)
    {
        initWidget();

        /************************************
         DOES NOT loadState(string widgetXML) from constructor
         -------------------------------------------------------------
         We do NOT load state inside uiVizWigetStringedInstrument constructor since it's acts more like an
         interface. It is up to the derriving widget eg uiVizWidgetGuitar to load it's state from it's own
         constructor.
        ************************************/
    }

    virtual bool loadState(string widgetXML) override
    {
        uiVizWidgetMusical::loadState(widgetXML);

        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str()))
        {
            return false;
        }

        settings.pushTag("widget");
        settings.pushTag("properties");

        if (settings.getAttribute("musicData", "isChordDiagramMode", 0) > 0)
        {
            setChordDiagramNumFrets(getInstrumentRule("stringed", "chordDiagramNumFrets", getChordDiagramNumFrets()));
            setIsChordDiagramMode(settings.getAttribute("musicData", "isChordDiagramMode", 0));
        }

        vector<uiVizWigetStringedInstrumentString> strings = getStringsFromXML(settings);

        setStrings(strings, true);
        calculatePoints();

        settings.popTag(); // properties
        settings.popTag(); // widget

        return true;
    }

    virtual ofxXmlSettings saveState() override
    {
        ofxXmlSettings settings = uiVizWidgetMusical::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        if (getIsChordDiagramMode())
        {
            settings.setAttribute("musicData", "isChordDiagramMode", getIsChordDiagramMode(), 0);
            setInstrumentRule("stringed", "chordDiagramNumFrets", getChordDiagramNumFrets());
        }

        // Add the strings
        appendStringsToXML(settings, getStrings());


        settings.popTag(); // properties
        settings.popTag(); // widget

        return settings;
    }



    virtual ~uiVizWigetStringedInstrument()
    {

        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu) 
            ofRemoveListener(menu->menuItemSelected, this, &uiVizWigetStringedInstrument::onMenuItemSelected);

        uiVizWidgetMenu *menuMini = static_cast<uiVizWidgetMenu *>(instrumentContextMenuMini);
        if (menu) 
            ofRemoveListener(menuMini->menuItemSelected, this, &uiVizWigetStringedInstrument::onMenuItemSelected);            

        if (keyPickerMenuItem)
            ofRemoveListener(keyPickerMenuItem->keySelected, this, &uiVizWigetStringedInstrument::onKeyPickerMenuKeySelected);
        
        if(chordDesignerMenuItem) {
            ofRemoveListener(chordDesignerMenuItem->noteSelected, this, &uiVizWigetStringedInstrument::onChordDesignerMenuNoteSelected);
            ofRemoveListener(chordDesignerMenuItem->userDefinedChordNameChanged, this, &uiVizWigetStringedInstrument::onUserDefinedChordNameChanged);
            ofRemoveListener(chordDesignerMenuItem->rulesChanged, this, &uiVizWigetStringedInstrument::onRulesChanged);            
        }


        if(scalePickerMenuItem) {
            ofRemoveListener(scalePickerMenuItem->noteSelected, this, &uiVizWigetStringedInstrument::onScalePickerMenuNoteSelected);
            ofRemoveListener(scalePickerMenuItem->rulesChanged, this, &uiVizWigetStringedInstrument::onRulesChanged);
        } 


        mStrings.clear();
        mPoints.clear();
        mFrets.clear();
        if(instrumentContextMenu) instrumentContextMenu->deleteThisWidget();
        if(instrumentContextMenuMini) instrumentContextMenuMini->deleteThisWidget();
        
    }

    static void appendStringsToXML(ofxXmlSettings &settings, vector<uiVizWigetStringedInstrumentString> strings) {

        settings.removeTag("strings");

        settings.addTag("strings");

        // Tuning
        if (strings.size() > 0 && strings[0].note.getNoteTags().size() > 0)
        {
            settings.setAttribute("strings", "tuning", strings[0].note.getNoteTags()[0], 0);
        }
        else
        {
            settings.setAttribute("strings", "tuning", "Standard", 0);
        }

        // Strings
        settings.pushTag("strings");
        for (int j = 0; j < strings.size(); j++)
        {
            settings.addTag("string");
            settings.setAttribute("string", "enabled", strings[j].isEnabled, j);
            settings.setAttribute("string", "note", strings[j].note.getNoteName(), j);
            settings.setAttribute("string", "octave", strings[j].note.getNoteOctave(), j);
            settings.setAttribute("string", "startFret", strings[j].getStartFret(), j);
            settings.setAttribute("string", "endFret", strings[j].getEndFret(), j);
            settings.setAttribute("string", "thickness", strings[j].thickness, j);

            if (strings[j].getFretPoints_CSV() != "")
            {
                string points = strings[j].getFretPoints_CSV();
                settings.setAttribute("string", "fretPoints", points, j);
            }
        }
        settings.popTag(); // strings
    }

    vector<uiVizWigetStringedInstrumentString> getStringsFromXML(ofxXmlSettings &settings)
    {

        vector<uiVizWigetStringedInstrumentString> strings = vector<uiVizWigetStringedInstrumentString>();

        // The block below specially accomodates getting strings from
        // rules XML object.
        TiXmlElement *rootElm = settings.doc.RootElement();
        if (rootElm == NULL)
            return strings;
        string tagName = rootElm->Value();
        if (tagName == "rules")
        {
            while (settings.popTag() > 0)
                ; // pop to top!
            settings.pushTag("rules");
        }

        // Tuning
        string tuning = "Standard";
        if (getStrings().size() > 0 && getStrings()[0].note.getNoteTags().size() > 0)
        {
            tuning = settings.getAttribute("strings", "tuning", getStrings()[0].note.getNoteTags()[0], 0);
        }

        // Strings
        if (settings.pushTag("strings"))
        {
            if (settings.getNumTags("string") > 0)
            {

                for (int j = 0; j < settings.getNumTags("string"); j++)
                {

                    uiVizWigetStringedInstrumentString string = uiVizWigetStringedInstrumentString(
                        vizNote(settings.getAttribute("string", "note", "C", j),
                                settings.getAttribute("string", "octave", 3, j),
                                1,
                                {tuning}),
                        settings.getAttribute("string", "thickness", 3, j),
                        0);

                    string.isEnabled = settings.getAttribute("string", "enabled", false, j);
                    string.setStartFret(settings.getAttribute("string", "startFret", 0, j));
                    string.setEndFret(settings.getAttribute("string", "endFret", 3, j));
                    string.setFretPoints_CSV(settings.getAttribute("string", "fretPoints", "", j));
                    strings.push_back(string);
                }
            }
            settings.popTag(); // strings
        }
        else
        {
            strings = getStrings();
        }

        return strings;
    }

    void setBoundsForOrientation(TheoryVizOrientationMode orientation)
    {
        setOrientationSize();
        setFretboardSizeRatio();
    }

    int getSize()
    {
        return mSize;
    }

    void setSize(int val)
    {
        mSize = val;
    }

    bool getIsChordDiagramMode()
    {
        return mIsChordDiagramMode;
    }

    void setIsChordDiagramMode(bool val)
    {

        //if (getIsChordDiagramMode() == val && getChordDiagramNumFrets() !=) return; // no state to change

        mIsChordDiagramMode = val;
        if (getIsChordDiagramMode())
        {
            int lowestStartingFret = getLowestStartingFret();
            int chordDiagramNumFrets = getChordDiagramNumFrets();
            setIsFixedFretWidth(true, chordDiagramNumFrets);            
            setStartFret(lowestStartingFret, true, true);
            setEndFret(lowestStartingFret + chordDiagramNumFrets, true, true);
            setFretWidthToHeightRatio(1.5f);
        }
        else
        {
            setFretWidthToHeightRatio(getFretWidthToHeightRatioFull());
            setIsFixedFretWidth(false, DEFAULT_FRETS);
        }

        updateWidget();
        setNeedsUpdate(true);
        setWidgetNeedsUpdate(true);
    }

    virtual float getFretWidthToHeightRatioFull() {
        return 6.0f;
    }

    bool getIsFixedFretWidth()
    {
        return mIsFixedFretWidth;
    }

    void setIsFixedFretWidth(bool val, int totalFrets)
    {
        mIsFixedFretWidth = val;
        mTotalFrets = totalFrets;
        setNeedsUpdate(true);
    }

    void setOrientationSize()
    {
        // This ratio might be different per instrument (ie num strings etc)
        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            if (getWidth_Expr() == "") setWidth(getSize());
            break;
        case TheoryVizOrientationMode::VERTICAL:
            if (getHeight_Expr() == "") setHeight(getSize());
            break;
        }
    }

    void setFretboardSizeRatio()
    {
        
        // This ratio might be different per instrument (ie num strings etc)
        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            setSize(getWidth());
            if (getHeight_Expr() == "") setHeight(getSize() / mFRET_WIDTH_TO_HEIGHT_RATIO);
            break;
        case TheoryVizOrientationMode::VERTICAL:
            setSize(getHeight());
            if (getWidth_Expr() == "") setWidth(getSize() / mFRET_WIDTH_TO_HEIGHT_RATIO);
            break;
        }
    }

    int getUsableFretboardWidth()
    {
        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            return getUsableHeight();
            break;
        case TheoryVizOrientationMode::VERTICAL:
            return getUsableWidth();
            break;
        }
        return getUsableHeight();
    }

    int getUsableFretboardLength()
    {
        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            return getUsableWidth();
            break;
        case TheoryVizOrientationMode::VERTICAL:
            return getUsableHeight();
            break;
        }
        return getUsableWidth();
    }

    float getNormalizedFretboardWidth()
    {
        return mSIZE_NORMALIZED / (float)mFRET_WIDTH_TO_HEIGHT_RATIO;
    }

    virtual void updateFretboard(float sizingRatio)
    {
        fretboard.setRectangle(scale(getUsableX()), scale(getUsableY()), scale(getUsableWidth()), scale(getUsableHeight()),
                               getFretboardColor());
    }

    virtual void updateNut(float sizingRatio)
    {
        int nutWidth = scale(7) * sizingRatio;
        float nutPos = isLefty() ? scale(getUsableWidth()) - nutWidth : 0;
        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            nut.setRectangle(scale(getUsableX()) + nutPos, scale(getUsableY()), nutWidth, scale(getUsableHeight()), getNutColor());
            break;
        case TheoryVizOrientationMode::VERTICAL:
            nut.setRectangle(scale(getUsableX()), scale(getUsableY()), scale(getUsableWidth()), nutWidth, getNutColor());
            break;
        }
    }

    ofColor getFretboardColor() {
        return mFretboardColor;
    }

    void setFretboardColor(ofColor color) {
        mFretboardColor = color;
    }    

    ofColor getNutColor() {
        return mNutColor;
    }

    void setNutColor(ofColor color) {
        mNutColor = color;
    }    

    ofColor getFretColor(bool enabled) {
        return (enabled ? ofColor(mFretColor.r, mFretColor.g, mFretColor.b, 160) : ofColor(mFretColor.r, mFretColor.g, mFretColor.b, 45));
    }

    void setFretColor(ofColor color) {
        mFretColor = color;
    }    

    ofColor getFretboardInlayColor() {
        return mFretboardInlayColor;
    }

    void setFretboardInlayColor(ofColor color) {
        mFretboardInlayColor = color;
    }    

    ofColor getFretboardLabelColor() {
        return mFretboardLabelColor;
    }

    void setFretboardLabelColor(ofColor color) {
        mFretboardLabelColor = color;
    }    

    ofColor getFretboardPointStrokeColor() {
        return mFretboardPointStrokeColor;
    }

    void setFretboardPointStrokeColor(ofColor color) {
        mFretboardPointStrokeColor = color;
    }

    virtual void setIsBlackAndWhiteMode(bool val) override {
        
        if(val) {
            setFretboardColor(ofColor(255, 255, 255, 255)); 
            setNutColor(ofColor(0, 0, 0, 255));
            setFretColor(ofColor(0, 0, 0, 255));
            setFretboardInlayColor(ofColor(0, 0, 0, 255));
            setFretboardLabelColor(ofColor(0, 0, 0, 255));
            setFretboardPointStrokeColor(ofColor(0, 0, 0, 255));      
        } else {
            setFretboardColor(ofColor(138, 51, 36, 200)); // https://en.wikipedia.org/wiki/Shades_of_brown
            setNutColor(ofColor(255, 255, 255, 180));
            setFretColor(ofColor(255, 255, 255, 160));
            setFretboardInlayColor(ofColor(255, 255, 255, 180));
            setFretboardLabelColor(ofColor(0, 0, 0, 255));
            setFretboardPointStrokeColor(ofColor(255, 255, 255, 255));            
        }
        setNeedsUpdate(true);
    } 

    float getNeckRemainder()
    {
        float totalRemaining = 0;
        float oldFretDist = scale(getSize());
        float newFretDist = 0;

        for (int i = 1; i <= mTotalFrets; i++)
        {
            newFretDist = oldFretDist / FRET_RATIO;
            oldFretDist = newFretDist;
        }
        return newFretDist;
    }

    int getLowestStartingFret()
    {
        int val = 1000; // bug when using mTotalFrets !!
        for (int i = 0; i < getStrings().size(); i++)
        {
            if (getStrings()[i].getStartFret() < val)
                val = getStrings()[i].getStartFret();
        }
        return val;
    }

    int getHighestEndingFret()
    {
        int val = 0;
        for (int i = 0; i < getStrings().size(); i++)
        {
            if (getStrings()[i].getEndFret() > val)
                val = getStrings()[i].getEndFret();
        }
        return val;
    }

    int getLowestStartingFretWithPoint()
    {
        int val = 1000;
        for (int i = 0; i < getPoints().size(); i++)
        {
            if (getPoints()[i].fret < val)
                val = getPoints()[i].fret;
        }
        return val;
    }

    int getHighestEndingFretWithPoint()
    {
        int val = 0;
        for (int i = 0; i < getPoints().size(); i++)
        {
            if (getPoints()[i].fret > val)
                val = getPoints()[i].fret;
        }
        return val;
    }

    virtual int getUsableX() override
    {
        bool buttonsShowing = (buttonDown && buttonDown->getIsVisible());

        if (getTheoryVizOrientationMode() == TheoryVizOrientationMode::VERTICAL && getIsChordDiagramMode())
        {
            return uiVizWidget::getUsableX(true) + mTOOLBAR_WIDTH;
        }
        else
        {
            return uiVizWidget::getUsableX();
        }
    }

    virtual int getUsableWidth() override
    {
        bool buttonsShowing = (buttonDown && buttonDown->getIsVisible());

        if (getTheoryVizOrientationMode() == TheoryVizOrientationMode::VERTICAL && getIsChordDiagramMode())
        {
            return uiVizWidget::getUsableWidth() - mTOOLBAR_WIDTH;
        }
        else
        {
            return uiVizWidget::getUsableWidth();
        }
    }

    virtual void updateFrets(float sizingRatio)
    {
        mFrets.clear();

        float fretWidth = scale(mFRET_SIZE) * sizingRatio;
        float sizeToUse = getIsFixedFretWidth() ? scale(getUsableFretboardLength()) : scale(getSize());

        float neckRemainder = 0.0f;
        if (mUseFullNeck)
        {
            neckRemainder = getNeckRemainder();
            sizeToUse = getIsFixedFretWidth() ? sizeToUse : sizeToUse + neckRemainder;
        }

        float oldFretDist = sizeToUse;

        /***********************************************************************************************
		 The number of frets past the neckRemainder (in lefty mode!). At the given ratio, 4 frets get 
		 chopped off, so we subtract the neckRemainder and 4 * fretWidth from the fret x position!
		 JC helped me with this :)
		***********************************************************************************************/
        float magicFretMultiplier = 4.0f;

        int lowestStartingFret = getLowestStartingFret();
        int highestEndingFret = getHighestEndingFret();

        for (int i = 1; i <= mTotalFrets; i++)
        {
            float newFretDist = (getIsFixedFretWidth() ? oldFretDist - (sizeToUse / (float)mTotalFrets) : oldFretDist / FRET_RATIO);

            float fretPos;

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                fretPos = isLefty() ? (getIsFixedFretWidth() ? newFretDist - fretWidth * 2 : newFretDist - (magicFretMultiplier * fretWidth) - neckRemainder) : sizeToUse + (newFretDist * -1);
                break;
            case TheoryVizOrientationMode::VERTICAL:
                fretPos = sizeToUse + (newFretDist * -1); // <--- this works!!
                break;
            }

            uiVizWigetStringedInstrumentFret f = uiVizWigetStringedInstrumentFret();
            f.prevFretDist = oldFretDist;
            f.fretDist = newFretDist;
            f.fretPos = isLefty() ? fretPos : fretPos + fretWidth;

            bool isInFretRange = getIsChordDiagramMode() ? (i + lowestStartingFret - 1 <= highestEndingFret) : (i >= lowestStartingFret - 1 && i <= highestEndingFret);

            ofColor fretColor = getFretColor(isInFretRange);

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                f.path.setRectangle(scale(getUsableX()) + fretPos + fretWidth, scale(getUsableY()), fretWidth, scale(getUsableHeight()), fretColor);

                f.fretArea.setRectangle(
                    isLefty() ? scale(getUsableX()) + fretPos + fretWidth * 2 : scale(getUsableX()) + fretPos - (oldFretDist - newFretDist) + fretWidth * 2,
                    scale(getUsableY()),
                    isLefty() ? (oldFretDist - newFretDist) - fretWidth : oldFretDist - newFretDist - fretWidth, // scale(getUsableX()) + fretPos - fretWidth,
                    scale(getUsableHeight()), getFretColor(true));
                break;
            case TheoryVizOrientationMode::VERTICAL:
                f.path.setRectangle(scale(getUsableX()), scale(getUsableY()) + fretPos + fretWidth, scale(getUsableWidth()), fretWidth, fretColor);

                f.fretArea.setRectangle(
                    scale(getUsableX()),
                    scale(getUsableY()) + fretPos - (oldFretDist - newFretDist) + fretWidth * 2,
                    scale(getUsableWidth()),
                    oldFretDist - newFretDist - fretWidth, getFretColor(true));

                break;
            }

            f.hasInlay = false;

            mFrets.push_back(f);
            if (!getIsChordDiagramMode())
                updateFretboardInlay(&mFrets[i - 1], sizingRatio, i, fretWidth);

            oldFretDist = newFretDist;
        }
    }

    virtual void updateFretboardInlay(uiVizWigetStringedInstrumentFret *f, float sizingRatio, int fretNum, float fretWidth)
    {

        if (fretNum == 3 || fretNum == 5 || fretNum == 7 || fretNum == 9 || fretNum == 12 ||
            fretNum == 15 || fretNum == 17 || fretNum == 19 || fretNum == 21 || fretNum == 24)
        {

            uiVizElm::vizRect rect = f->path.getRectangle();

            int tmpINLAY_SIZE = mINLAY_SIZE;
            if (fretNum >= 12)
                tmpINLAY_SIZE = mINLAY_SIZE * 0.5f;

            float defaultInlaySize = sizingRatio * scale(tmpINLAY_SIZE);

            float fretPos = getFretPos(sizingRatio, fretNum, false, defaultInlaySize);

            // ???????????? ALIENS ????????????
            if (fretNum >= 12 && isLefty())
                fretPos += fretWidth + defaultInlaySize / 2.0f;
            // ???????????? ALIENS ????????????

            ofColor pointColor = getFretboardInlayColor();

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                f->inlayPath.setCircle(scale(getUsableX()) + fretPos + (isLefty() ? fretWidth + defaultInlaySize * 1.5f : +defaultInlaySize / (float)2),
                                       rect.y + (rect.height - defaultInlaySize) / (float)2 + defaultInlaySize / (float)2,
                                       defaultInlaySize,
                                       defaultInlaySize,
                                       pointColor);
                break;
            case TheoryVizOrientationMode::VERTICAL:
                f->inlayPath.setCircle(scale(getUsableX()) + (rect.width - defaultInlaySize) / (float)2,
                                       scale(getUsableY()) + fretPos + (isLefty() ? fretWidth + defaultInlaySize * 1.5f : +defaultInlaySize / (float)2),
                                       defaultInlaySize,
                                       defaultInlaySize,
                                       pointColor);
                break;
            }

            f->hasInlay = true;
        }
        else
        {
            f->hasInlay = false;
        }
    }

    virtual void updateStrings(float sizingRatio, int fretboardWidth)
    {

        if (getStrings().size() == 0)
            return;

        int startString = 0;
        int endString = getStrings().size();

        int totalStringSizes = 0;
        for (int i = 0; i < getStrings().size(); i++)
        {
            totalStringSizes += std::max(getStrings()[i].thickness * sizingRatio, 1.0f);
            ;
        }

        for (int i = 0; i < getStrings().size(); i++)
        {
            int rawStringWidth = getStrings()[i].thickness * sizingRatio;
            rawStringWidth = std::max(rawStringWidth, 1);

            int stringWidth = scale(rawStringWidth);
            int stringSpacing = scale(fretboardWidth) / (float)getStrings().size();
            int stringPos = (i * stringSpacing) + (scale(getStrings()[i].offset) * sizingRatio) + (scale(fretboardWidth - totalStringSizes) / getStrings().size()) - stringWidth * 1.5f;

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                mStrings[i].path.setRectangle(scale(getUsableX()),
                                              scale(getUsableY()) + (isLefty() ? stringPos : scale(fretboardWidth) - stringWidth - stringPos),
                                              scale(getUsableWidth()),
                                              stringWidth,
                                              getStrings()[i].isEnabled ? getStrings()[i].color : getStrings()[i].disabledColor);
                break;
            case TheoryVizOrientationMode::VERTICAL:
                mStrings[i].path.setRectangle(scale(getUsableX()) + (isLefty() ? scale(fretboardWidth) - stringWidth - stringPos : stringPos),
                                              scale(getUsableY()),
                                              stringWidth,
                                              scale(getUsableHeight()),
                                              getStrings()[i].isEnabled ? getStrings()[i].color : getStrings()[i].disabledColor);
                break;
            }
        }
    }

    float getFretPos(float sizingRatio, int fret, bool drawPointOnFret, float pointSize)
    {
        if (fret == 0 || mFrets.size() == 0)
        {
            return isLefty() && getTheoryVizOrientationMode() == TheoryVizOrientationMode::HORIZONTAL ? scale(getUsableWidth()) - pointSize : 0;
        }

        if (fret - 1 > mFrets.size() - 1 || mFrets.size() == 0)
        {
            return -1;
        }

        float fretWidth = scale(mFRET_SIZE) * sizingRatio;
        float fretPos = mFrets[fret - 1].fretPos;
        float midFretOffset = (mFrets[fret - 1].fretDist - mFrets[fret - 1].prevFretDist) / (float)2;
        float halfPointSize = fretWidth / (float)2; // works with 10

        return fretPos + (isLefty() ? pointSize / (float)2 - fretWidth : fretWidth - pointSize / (float)2) - halfPointSize - (drawPointOnFret ? 0 : isLefty() && getTheoryVizOrientationMode() == TheoryVizOrientationMode::HORIZONTAL ? midFretOffset
                                                                                                                                                                                                                                       : midFretOffset * -1);
    }

    virtual void updatePoints(float sizingRatio, int fretboardWidth)
    {
        if (getPoints().size() == 0)
            return;

        pointSmallLabelRectSingle = fontSmall->rect("4");

        int highestEndingFret = getHighestEndingFret();
        int lowestStartingFret = getLowestStartingFret();

        // int lowestStartingFretWithPoint = getLowestStartingFretWithPoint();
        // int highestEndingFretWithPoint = getHighestEndingFretWithPoint();

        for (int i = 0; i < getPoints().size(); i++)
        {
            uiVizElm::vizRect stringRect = mPoints[i].instrumentstring->path.getRectangle();
            uiVizElm::vizRect pointRect = mPoints[i].path.getRectangle();
            int fretNum = mPoints[i].fret;
            float pointSize = sizingRatio * scale(mPOINT_SIZE);

            int offsetFret = std::max(mPoints[i].fret - (getIsChordDiagramMode() ? lowestStartingFret : 0), 0);
            if (lowestStartingFret > 0 && mPoints[i].fret > 0 && getIsChordDiagramMode())
                offsetFret++; // open string
            float fretPos = getFretPos(sizingRatio, offsetFret, getDrawPointsOnFrets(), pointSize);

            // Calculated point overshot the fretboard!
            if (fretPos <= -1)
                continue;

            vizNote note = mPoints[i].instrumentstring->note.getCalculatedNoteForOffset(mPoints[i].fret, getIsSelectedKeySharp());

            // Color stuff
            ofColor pointColor;
            if (getSelectedKey().getNoteName() != "")
            {

                pointColor = getSliceColorForState(getSelectedKey().getNoteName(),
                                                   note.getNoteName(),
                                                   getSelectedKey().getInterval(note.getNoteName()) + 1, false, mPoints[i].isExtended);
            }
            else
            {
                pointColor = mPoints[i].color;
            }

            // Label stuff
            mPoints[i].pointLabelText = getPointLabelForState(note, mPoints[i]);
            mPoints[i].pointLabelRect = font->rect(mPoints[i].pointLabelText);

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                mPoints[i].path.setRectangle(scale(getUsableX()) + fretPos,
                                             stringRect.y - pointRect.height / 2 + stringRect.height / 2,
                                             pointSize,
                                             pointSize,
                                             pointColor);
                break;
            case TheoryVizOrientationMode::VERTICAL:
                mPoints[i].path.setRectangle(stringRect.x - pointRect.width / 2 + stringRect.width / 2,
                                             scale(getUsableY()) + fretPos,
                                             pointSize,
                                             pointSize,
                                             pointColor);
                break;
            }

            if (note.isEnharmonicallyEquivalent(getSelectedKey().getNoteName()) || note.getIsPlaying())
            {
                int highlightStrokeWidth = scale(2);
                uiVizElm::vizRect r = mPoints[i].path.getRectangle();

                mPoints[i].highlightPath.setRectangle(r.x - highlightStrokeWidth,
                                                      r.y - highlightStrokeWidth,
                                                      r.width + highlightStrokeWidth * 2,
                                                      r.height + highlightStrokeWidth * 2,
                                                      //ofColor::fromHsb(pointColor.getHue(), pointColor.getSaturation(), pointColor.getBrightness() >= 255 ? pointColor.getBrightness()*0.7f : pointColor.getBrightness()*1.3f));
                                                      //ofColor::fromHsb(pointColor.getHue(), pointColor.getBrightness() >= 255 ? pointColor.getSaturation()*0.7f :  pointColor.getSaturation(), pointColor.getSaturation(), 255)
                                                      getFretboardPointStrokeColor());
                mPoints[i].setHighlightPathSet(true);
            }
        }
    }

    virtual void update(uiVizWidgetContext context) override
    {
        //  calculatePoints();
        setFretboardSizeRatio();
        
        int fretboardWidth = getUsableFretboardWidth();
        int normalizedFretboardWidth = getNormalizedFretboardWidth();
        float sizingRatio = fretboardWidth / (float)normalizedFretboardWidth;

        sizingRatio = sizingRatio * (getIsChordDiagramMode() ? 3.5f : getSize() >= 550 ? 1.2f
                                                                                       : 1.0f);
        fontLarge = fontLarge = getLargeFontSizedForDimensions(std::min(240, getUsableWidth()), getUsableHeight());

        /***************** FRETBOARD *****************/
        updateFretboard(sizingRatio);

        /***************** NUT *****************/
        updateNut(sizingRatio);

        /***************** FRETS *****************/
        updateFrets(sizingRatio);

        /***************** STRINGS *****************/
        updateStrings(sizingRatio, fretboardWidth);
        synchronizeStringsEnabledPropertyWithMenu();

        /***************** POINTS *****************/
        updatePoints(sizingRatio, fretboardWidth);

        font = getFontSizedForDimensions(getUsableWidth(), getUsableHeight());

        if (context.drawContext == uiVizWidgetContext::DrawContext::IMAGE)
        {
            setButtonsVisibility(false);
        }
    }

    bool needsUpdateBeforeDraw(bool shouldResetTimer) override
    {

        bool needsUpdate = false;

        if (getTimerMillis() >= 2000)
        {
            if (shouldResetTimer)
                resetTimer();
            bool labelNeedsUpdate = AlternateTheoryVizLabelMode();
            bool colorNeedsUpdate = AlternateTheoryVizColorMode();
            needsUpdate = labelNeedsUpdate || colorNeedsUpdate;
        }

        return needsUpdate;
    }

    virtual void draw(uiVizWidgetContext context) override
    {

        // Draw the fretboard
        fretboard.draw();
        nut.draw();

        int lowestStartingFret = getLowestStartingFret();

        for (int i = 0; i < getFrets().size(); i++)
        {

            if (getFrets()[i].hasInlay)
            {
                getFrets()[i].inlayPath.draw();
            }

            getFrets()[i].path.draw();
        }

        for (int i = 0; i < getStrings().size(); i++)
        {

            if ((!getIsUserEditing() && getStrings()[i].dontPlay) || !getStrings()[i].isEnabled)
            {
                getString(i)->path.setColor(getStrings()[i].disabledColor);
            }
            else
            {
                getString(i)->path.setColor(getStrings()[i].color);
            }

            getStrings()[i].path.draw();
        }

        for (int i = 0; i < getPoints().size(); i++)
        {
            // Point
            uiVizWigetStringedInstrumentPoint fretPoint = getPoints()[i];

            ofColor pointLabelColor = getFontColorForState(getSelectedKey().getNoteName(), fretPoint.isExtended);

            if (
                // Open strings (should always be playable)
                (fretPoint.fret == 0) ||
                // Fret range
                (fretPoint.instrumentstring->isEnabled && fretPoint.fret >= fretPoint.instrumentstring->getStartFret() && fretPoint.fret <= fretPoint.instrumentstring->getEndFret()))
            {

                if (fretPoint.getHighlightPathSet() || fretPoint.getNoteForPoint(false).getIsPlaying())
                {
                    fretPoint.highlightPath.setColor(getSelectedFontColor(getSelectedKey().getNoteName()));
                    fretPoint.highlightPath.draw();
                }

                fretPoint.path.draw();


                

                if (fretPoint.pointLabelText == "")
                    continue;

                // Label
                ofPushStyle();
                ofSetColor(pointLabelColor);

                if (getShowOctaveInLabel() /* && getUsableFretboardLength() > 950 */)
                {
                    int verticalOffset = fretPoint.pointLabelRect.height * 0.5f;

                    font->draw(fretPoint.pointLabelText,
                               fretPoint.path.getRectangle().x + (fretPoint.path.getRectangle().width - fretPoint.pointLabelRect.width) / 2,
                               fretPoint.path.getRectangle().y + verticalOffset * -1 + fretPoint.pointLabelRect.height + (fretPoint.path.getRectangle().height - fretPoint.pointLabelRect.height) / 2);

                    fontSmall->draw(ofToString(fretPoint.getNoteOctave()),
                                    fretPoint.path.getRectangle().x + (fretPoint.path.getRectangle().width - pointSmallLabelRectSingle.width) - scale(2),
                                    fretPoint.path.getRectangle().y + verticalOffset + fretPoint.pointLabelRect.height + (fretPoint.path.getRectangle().height - fretPoint.pointLabelRect.height) / 2);
                }
                else
                {
                    font->draw(fretPoint.pointLabelText,
                               fretPoint.path.getRectangle().x + (fretPoint.path.getRectangle().width - fretPoint.pointLabelRect.width) / 2,
                               fretPoint.path.getRectangle().y + fretPoint.pointLabelRect.height + (fretPoint.path.getRectangle().height - fretPoint.pointLabelRect.height) / 2);
                }

                ofPopStyle();
            }
        }

        // Diagram mode label
        if (getFrets().size() > 0 && lowestStartingFret > 0 && getIsChordDiagramMode()) 
        {
            ofPushStyle();
            ofSetColor(getFretboardLabelColor());
            string label = ofToString(lowestStartingFret);
            fontLarge->draw(label,
                            scale(uiVizWidget::getUsableX()) + (label.length() >= 2 ? getNonScaledPadding() * -1.0f : getToolbarWidth() / 2.0f),
                            getFrets()[0].path.getRectangle().y - fontLarge->rect(label).height / 2);
            ofPopStyle();
        }

    }

    void onWidgetClicked(ofMouseEventArgs &e) override
    {

        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        float sizingRatio = getUsableFretboardWidth() / (float)getNormalizedFretboardWidth();

        // Enable / disable strings by clicking them in the NUT area :P

        int marginOfErrorX = scale(5) * (float)sizingRatio;
        int marginOfErrorY = scale(5) * (float)sizingRatio;

        switch (getTheoryVizOrientationMode())
        {
        case TheoryVizOrientationMode::HORIZONTAL:
            marginOfErrorX = 0;
            break;
        case TheoryVizOrientationMode::VERTICAL:
            marginOfErrorY = 0;
            break;
        }

        bool nutIsHovered = nut.isHovered_Rect();

        // Click to add notes
        bool pointWasAdded = false;

        int lowestStartingFret = getLowestStartingFret();
        int highestEndingFret = getHighestEndingFret();
        int middleFretPos = (lowestStartingFret + highestEndingFret) / 2;

        for (int i = 0; i < getStrings().size(); i++)
        {

            if (getStrings()[i].path.isHovered_Rect(marginOfErrorX, marginOfErrorY))
            {

                for (int j = 0; j < getFrets().size(); j++)
                {

                    if ((getFrets()[j].fretArea.isHovered_Rect() || nutIsHovered))
                    {   // &&
                        // j >= getStrings()[i].getStartFret() && j < getStrings()[i].getEndFret()) {

                        if (getStrings()[i].isEnabled && !pointWasAdded)
                        {
                            //cout << "string " << ofToString(i+1) << ", fret " << ofToString(nutIsHovered ? 0 : j+1) << " clicked\n";

                            setIsUserEditing(true);
                            ofColor color = mStrings[i].note.calculateNoteKeyColor(i);

                            int clickedFret = (getIsChordDiagramMode() ? lowestStartingFret + j : j) + 1;
                            if (lowestStartingFret > 0 && getIsChordDiagramMode())
                                clickedFret--;

                            // Expand fret range if needed!
                            if (!nutIsHovered)
                            {
                                // Strings are easily played as open, so no need to extend fret to nut!
                                if (clickedFret - 1 < getStrings()[i].getStartFret())
                                    setStartFret(clickedFret - 1, true, true);
                            }
                            if (clickedFret > getStrings()[i].getEndFret() - 1)
                                setEndFret(clickedFret, true, true);

                            uiVizWigetStringedInstrumentPoint point = uiVizWigetStringedInstrumentPoint(getString(i), nutIsHovered ? 0 : clickedFret, color);

                            bool rule_showExtendedNoteNames = getInstrumentRule("general", "showExtendedNoteNames", true);
                            bool rule_strictExtendedNotes = getInstrumentRule("general", "strictExtendedNotes", true); // notes MUST be greater than the root octave

                            vizNote lowestRootNote = vizChord::findLowestRootNote(getSelectedKey(), getSelectedNotes());
                            bool isExtended = calculateIfExtendedNote(lowestRootNote, getSelectedNotes(), point.getNoteForPoint(getIsSelectedKeySharp()), rule_strictExtendedNotes);
                            point.isExtended = isExtended;

                            bool shiftPressed = isKeyPressed(OF_KEY_SHIFT);

                            // Up and down arrow - inc/dec   noteSequenceNumer
                            if (shiftPressed) {
                                point.sequenceNumber = mSequencedNoteNumber; //getTotalSequencedPoints()+1; 
                            }
                            
                            pointWasAdded = addPoint(point);

                            setInstrumentRule_RemoveGeneralBlock();
                            setUserDefinedChordName("");
                            calculatePoints();

                            setNeedsUpdate(true);
                            setWidgetNeedsUpdate(true);

                            if (menu) {
                                switch (getTheoryVizInstrumentTheoryContentMode())
                                {
                                    case TheoryVizInstrumentTheoryContentMode::CHORD:
                                    {
                                        // Disable string if the note was toggled off and no other notes on string
                                        if (!pointWasAdded && getNumNotesAddedToString(getString(i), getPoints()) == 0)
                                        {
                                            menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true);
                                            return;
                                        }
                                        else
                                        {
                                            return;
                                        }
                                    }

                                    case TheoryVizInstrumentTheoryContentMode::SCALE:
                                    {
                                        getStrings()[i].isEnabled ? menu->deselectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true) : menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true);
                                        return;
                                    }
                                }                                
                            }

                        }
                    }
                }

                
                if (menu) {
                    switch (getTheoryVizInstrumentTheoryContentMode())
                    {
                        case TheoryVizInstrumentTheoryContentMode::CHORD:
                        {
                            // ENABLE string if no notes added, but it's clicked
                            if (!getStrings()[i].isEnabled && getNumNotesAddedToString(getString(i), getPoints()) == 0)
                            {
                                menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true);
                            }
                            break;
                        }

                        case TheoryVizInstrumentTheoryContentMode::SCALE:
                        {
                            getStrings()[i].isEnabled ? menu->deselectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true) : menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_STRINGS, i, true);
                            break;
                        }
                    }
                }



            }
        }

        // Fret range
        for (int i = 0; i < getStrings().size(); i++)
        {
            if (!getStrings()[i].path.isHovered_Rect())
            {
                for (int j = 0; j < getFrets().size(); j++)
                {

                    if (!getIsChordDiagramMode())
                    {

                        if (getFrets()[j].path.isHovered_Rect() || nutIsHovered)
                        {
                            int clickedFret = j + 1;
                            if (nutIsHovered)
                                clickedFret = 0;
                            bool shouldSetEndFret = (!nutIsHovered && clickedFret > middleFretPos) || (highestEndingFret - lowestStartingFret == 0);
                            //bool shouldSetEndFret = (clickedFret > lowestStartingFret);
                            if (shouldSetEndFret)
                                clickedFret++;
                            if (menu) menu->selectMenuItem(shouldSetEndFret ? MENU_GROUP_1::MENU_TAB_END_FRET : MENU_GROUP_1::MENU_TAB_START_FRET, clickedFret, true);
                            return;
                        }
                    }
                    else
                    {

                        if (getFrets()[j].path.isHovered_Rect() || nutIsHovered)
                        {
                            int clickedFret = j + lowestStartingFret + 1;
                            if (nutIsHovered)
                                clickedFret = 0;
                            if (clickedFret > 0)
                            {
                                if (menu) menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_END_FRET, clickedFret, true);
                            }

                            return;
                        }
                    }
                }
            }
        }
    }

    void updateRules(ofxXmlSettings rules, bool updateInstrument, bool notify, string optionalReasonDesc)
    {

        uiVizInstrumentRuleArgs args(rules);

        /*
over here - append instrument rules instead of set
ie setInstrumetnRules(getInstrumentRules())
append so that when stuff is dragged, full rules persist!
*/

        setInstrumentRules(args.rules, false);

        // Sync rules with current String config too
        ofxXmlSettings settings = saveState();

        TiXmlElement *rootElm = settings.doc.RootElement();
        TiXmlElement *propertiesElm = rootElm->FirstChildElement("properties");

        if (propertiesElm != NULL)
        {
            TiXmlElement *stringsElm = propertiesElm->FirstChildElement("strings");
            appendInstrumentRules(stringsElm, true, false);
        }

        string rulesXML = getInstrumentRulesXMLString();

        //cout << optionalReasonDesc << "->[" << getPersistentId() << "] RULES CHANGED:\n" << rulesXML;

        //int rule_startingInversion = getInstrumentRule("general", "startingInversion", 0);

        // the above is working - however chords and scales logic are not reading from it
        // they are rather reading from vizChord and vizScale rules
        // fix this...

        /*
        setStrings(strings);
        setStartFret(getLowestStartingFret(), true);
        setEndFret(getHighestEndingFret(), true);
*/
        if (updateInstrument)
        {
            switch (getTheoryVizInstrumentTheoryContentMode())
            {
            case TheoryVizInstrumentTheoryContentMode::CHORD:
            {
                if (!chordDesignerMenuItem)
                    return;
                vizChord chord = vizChord(chordDesignerMenuItem->getCalculatedChordName(), chordDesignerMenuItem->getSelectedNotes(), true);
                if (chord.isChordValid())
                {
                    addSelectedChord(chord, true, true);
                }

                chordDesignerMenuItem->setInstrumentRules(args.rules, false);

                break;
            }

            case TheoryVizInstrumentTheoryContentMode::SCALE:
            {
                if (!scalePickerMenuItem)
                    return;
                vizScale scale = scalePickerMenuItem->getSelectedScale();
                if (scale.isScaleValid())
                {
                    setSelectedScale(scale, true);
                }

                scalePickerMenuItem->setInstrumentRules(args.rules, false);

                break;
            }
            }
        }

        if (notify)
            ofNotifyEvent(rulesChanged, args);
    }

    virtual void onRulesChanged(uiVizInstrumentRuleArgs &args) override
    {
        updateRules(args.rules, true, true, "onRulesChanged");
    }

    bool hasNoteBeenAddedToPoints(vizNote note, vector<vizNote> notesAdded)
    {

        for (vizNote currNote : notesAdded)
        {

            if (note.isEnharmonicallyEquivalent(currNote.getNoteNameNormalized()))
            {

                if (note.getIsExtended() == currNote.getIsExtended())
                {
                    return true;
                }
                if (note.getNoteOctave() == currNote.getNoteOctave())
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool allNotesBeenAddedToPoints(vector<vizNote> chordNotes, vector<vizNote> notesAdded)
    {
        for (vizNote currChordNote : chordNotes)
        {
            bool noteHasBeenAdded = false;

            for (vizNote currAddedNote : notesAdded)
            {

                if (currAddedNote.isEnharmonicallyEquivalent(currChordNote.getNoteNameNormalized()) && currAddedNote.getIsExtended() == currChordNote.getIsExtended())
                {
                    noteHasBeenAdded = true;
                }
            }

            if (!noteHasBeenAdded)
                return false;
        }
        return true;
    }

    int getNumNotesAddedToString(uiVizWigetStringedInstrumentString *string, vector<uiVizWigetStringedInstrumentPoint> points)
    {
        int notesAddedToThisString = 0;
        for (int i = 0; i < points.size(); i++)
        {
            if (points[i].instrumentstring == string)
            {
                notesAddedToThisString++;
            }
        }
        return notesAddedToThisString;
    }

    bool calculateIfExtendedNote(vizNote chordRootNote, vector<vizNote> notesAdded, vizNote noteToAdd, bool strictOctave)
    {
        return vizChord::calculateIfExtendedNote(chordRootNote, notesAdded, noteToAdd, strictOctave, false);
    }

    vector<uiVizWigetStringedInstrumentPoint> getPointsForNotes(vector<vizNote> notes, vizNote rootNote, vizTheoryBase theoryObj)
    {
        vector<vizNote> notesNormalized = vizChord::getDistinctNotesAscending(rootNote, notes);
        ;

        if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::SCALE)
        {
            // NOTE TO FUTURE DEV: Because we iterate each NOTE in the notes vector
            // when there is note repetition, the repeated note gets counted as an added note
            // which causes only one note to be added per string.

            // For now, we simply normalize the scale notes, but another solution could have been to check
            // already added notes to the string, and only cout +1 if it has not already been added - more computation...
            notes = notesNormalized;
        }

        for (int s = 0; s < notes.size(); s++)
        {
            cout << notes[s].getNoteName() << ",";
        }

        // Enable all strings to begin with
        for (int s = 0; s < getStrings().size(); s++)
        {
            getString(s)->dontPlay = false;
        }

        int numNotes = notes.size();
        int numDistinctNotes = vizChord::numDistinctNotes(notes);

        // RULES (defaulted for chord)
        int rule_startingString = theoryObj.getInstrumentRule("stringed", "startingString", -1); // -1 = start on any string, 0 for lowest

        // ^^ implement this - simple solution - change the fret number to the matching note of the inversion note!!!

        int rule_startingInversion = theoryObj.getInstrumentRule("general", "startingInversion", 0); // -1 = start on any inversion, 0 for no inv, 1 for 1st inversion
        int rule_notesPerString = theoryObj.getInstrumentRule("stringed", "notesPerString", 1);
        bool rule_allowNoteRepetition = theoryObj.getInstrumentRule("general", "allowNoteRepetition", true);                        /// eg C4 and C3 is allowed to be added in chord mode (when in scale mode it's C3==C3)
        bool rule_allowNoteRepetitionExactOctave = theoryObj.getInstrumentRule("general", "allowNoteRepetitionExactOctave", false); /// eg C3 and C3 wont be aded twice
        bool rule_exactOctaveMatch = theoryObj.getInstrumentRule("general", "exactOctaveMatch", false);
        bool rule_showExtendedNoteNames = theoryObj.getInstrumentRule("general", "showExtendedNoteNames", true);
        bool rule_strictExtendedNotes = theoryObj.getInstrumentRule("general", "strictExtendedNotes", true);      // notes MUST be greater than the root octave
        bool rule_enforceAscendingNotes = theoryObj.getInstrumentRule("general", "enforceAscendingNotes", false); // next note MUST be greater than the previous

        // Fallback - inversions don't work so well with more complex chords....
        if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::CHORD)
        {
            if (numDistinctNotes > 3 /* and it's a chord */)
            {
                rule_startingInversion = -1;
            }
        }

        /***********************************************/
        // Determine values for inversion calculations (if applicable):
        int noteDegreeForStartingInversion = vizTheory::DegreeName::majorUnison;
        int noteDegreeForLastInversion = -1;
        int stringWhichNoteDegreeForStartingInversionWasAddedTo = getStrings().size() - 1;
        if (rule_startingInversion > -1 && rule_startingInversion < notesNormalized.size())
        {

            string noteNameForStartingInversion = notesNormalized[rule_startingInversion].getNoteName();
            string noteNameForLastInversion = notesNormalized[notesNormalized.size() - 1].getNoteName();

            noteDegreeForStartingInversion = rootNote.getInterval(noteNameForStartingInversion);
            noteDegreeForLastInversion = rootNote.getInterval(noteNameForLastInversion);
        }
        /**********************************************/

        vector<vizNote> notesAdded;
        vector<uiVizWigetStringedInstrumentPoint> points = {};

        int lowestOctave = getString(0)->note.getNoteOctave();
        int highestOctave = getString(getStrings().size() - 1)->note.getNoteOctave();
        int middleOctave = (lowestOctave + highestOctave) / 2;
        bool startingInversionNoteHasBeenAdded = false;
        bool lastInversionNoteHasBeenAdded = false;

        for (int notesPass = 1; notesPass <= 2; notesPass++)
        { // this algo needs 2 passes

            vizNote prevStringAddedNote;

            if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::SCALE && notesPass > 1)
            {
                // We only want ONE pass for scales!
                // continue;
            }

            for (int s = 0; s < getStrings().size(); s++)
            {
                // Starting with lowest / thickest string and working to highest / thinnest string
                if (!getStrings()[s].isEnabled)
                {
                    // If this string is not enabled, don't go any further with this iteration...
                    continue;
                }

                if (rule_startingInversion > -1 && notesPass == 2 && s < stringWhichNoteDegreeForStartingInversionWasAddedTo)
                {
                    // This condition is here to prevent non-starting inversion notes from being added
                    // on the SECOND pass
                    continue;
                }

                vizNote stringStartNote = getString(s)->note;
                int notesAddedToThisString = getNumNotesAddedToString(getString(s), points);

                /***********************************************/
                // Determine the directon of the vector:
                int fretVector;
                int f;
                //   f --> fretVector (ascending -OR- descending)
                bool isAscending;
                if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::CHORD)
                {
                    if (stringStartNote.getNoteOctave() > middleOctave)
                    {
                        // this string has a higher octave than the average
                        // we want to ASCEND when picking up notes...
                        fretVector = getString(s)->getEndFret();
                        f = getString(s)->getStartFret() - 1; // -1 offset to Zero
                        isAscending = true;
                    }
                    else
                    {
                        // this string has a lower or equal octave to the average
                        // we want to DESCEND when picking up notes...
                        fretVector = getString(s)->getStartFret();
                        f = getString(s)->getEndFret() + 1; // +1 offset to End fret
                        isAscending = false;
                    }
                }
                else
                {
                    // For scales we always want to ascend!
                    fretVector = getString(s)->getEndFret();
                    f = getString(s)->getStartFret() - 1; // -1 offset to Zero
                    isAscending = true;
                }
                /**********************************************/
                // cout << "---------------------------------:" << getString(s)->note.getNoteName() << ofToString(getString(s)->note.getNoteOctave()) << " | PREV STRING highest Note " <<  (s > 0 ? getString(s-1)->highestNoteAdded.getNoteName() : "none")
                // << " | Pass:" << ofToString(notesPass) << "---------------------------------\n";

                while (f != fretVector)
                {

                    (f > fretVector) ? f-- : f++;

                    // ------ RULE: Notes per string ------
                    if (notesAddedToThisString >= rule_notesPerString)
                    {
                        continue;
                    }

                    vizNote currStringNote = stringStartNote.getCalculatedNoteForOffset(f, getIsSelectedKeySharp());
                    prevStringAddedNote = (s > 0 ? getString(s - 1)->highestNoteAdded : vizNote("C", -1, 0, vector<string>{""}));

                    for (int i = 0; i < notes.size(); i++)
                    {

                        string noteName = notes[i].getNoteNameNormalized();
                        bool matchesOctave = notes[i].getNoteOctave() == currStringNote.getNoteOctave();

                        if (currStringNote.isEnharmonicallyEquivalent(noteName) && (!rule_exactOctaveMatch || (rule_exactOctaveMatch && matchesOctave)))
                        {
                            int noteDegree = rootNote.getInterval(noteName);
                            bool hasNoteBeenAdded = hasNoteBeenAddedToPoints(notes[i], notesAdded);
                            bool allNotesBeenAdded = allNotesBeenAddedToPoints(notes, notesAdded);

                            bool isCurStringNoteHigherThanPrevStringNote = points.size() == 0 || (currStringNote.getNoteOctave() > prevStringAddedNote.getNoteOctave()) ||
                                                                           (currStringNote.getNoteOctave() == prevStringAddedNote.getNoteOctave() && currStringNote.getPositionInChromaticScale() > prevStringAddedNote.getPositionInChromaticScale());

                            //string curr = "CURR: " + currStringNote.getNoteName() + ofToString(currStringNote.getNoteOctave()) + ":"  + ofToString(currStringNote.getPositionInChromaticScale());
                            //string prev ="PREV: " + prevStringAddedNote.getNoteName() + ofToString(prevStringAddedNote.getNoteOctave()) + ":"  + ofToString(prevStringAddedNote.getPositionInChromaticScale());
                            //cout << ofToString(f) << "->" << ofToString(fretVector) << " STR:" << getString(s)->note.getNoteName() << ofToString(getString(s)->note.getNoteOctave()) << ": " << curr << " | " << prev << " | " << ofToString(isCurStringNoteHigherThanPrevStringNote) << "\n";

                            if (
                                (
                                    ((rule_startingInversion == -1 || (startingInversionNoteHasBeenAdded && (noteDegree > noteDegreeForStartingInversion || lastInversionNoteHasBeenAdded))) &&
                                         (!hasNoteBeenAdded) ||
                                     (!startingInversionNoteHasBeenAdded && noteDegree == noteDegreeForStartingInversion)) ||
                                    // All notes are added and rule allows note repe
                                    ((allNotesBeenAdded && rule_allowNoteRepetition && startingInversionNoteHasBeenAdded) || (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::SCALE && (notesAddedToThisString < rule_notesPerString)))) &&
                                ((!rule_enforceAscendingNotes || (rule_enforceAscendingNotes && (isCurStringNoteHigherThanPrevStringNote || (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::SCALE && rule_allowNoteRepetition))))))
                            {
                                uiVizWigetStringedInstrumentPoint pointToAdd = uiVizWigetStringedInstrumentPoint(getString(s), f, currStringNote.getNoteColor());
                                if (!pointExistsInVector(pointToAdd, points))
                                {
                                    points.push_back(pointToAdd);
                                }

                                notesAddedToThisString++;
                                if (noteDegree == noteDegreeForStartingInversion)
                                {

                                    if (!startingInversionNoteHasBeenAdded)
                                    {
                                        stringWhichNoteDegreeForStartingInversionWasAddedTo = s;
                                    }

                                    startingInversionNoteHasBeenAdded = true;
                                }
                                if (noteDegree == noteDegreeForLastInversion)
                                    lastInversionNoteHasBeenAdded = true;

                                vizNote noteToAdd = pointToAdd.getNoteForPoint(getIsSelectedKeySharp());
                                notesAdded.push_back(noteToAdd);
                                //prevStringAddedNote = noteToAdd;

                                if (notesPass == 1)
                                {
                                    if (isAscending)
                                    {
                                        if (notesAddedToThisString == 1)
                                        {
                                            getString(s)->lowestNoteAdded = noteToAdd;
                                            getString(s)->highestNoteAdded = noteToAdd;
                                        }
                                        else
                                        {
                                            getString(s)->highestNoteAdded = noteToAdd;
                                        }
                                    }
                                    else
                                    {
                                        if (notesAddedToThisString == 1)
                                        {
                                            getString(s)->highestNoteAdded = noteToAdd;
                                            getString(s)->lowestNoteAdded = noteToAdd;
                                        }
                                        else
                                        {
                                            getString(s)->lowestNoteAdded = noteToAdd;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::SCALE && notesPass == 2 && notesAddedToThisString < rule_notesPerString)
                    {
                        //cout << "bumping fretVector from " << ofToString(fretVector) << " to ";
                        (isAscending) ? fretVector++ : fretVector--;
                        //cout << " " << ofToString(fretVector) << "\n";
                    }
                }
            }
        }

        // After 2 passes, if we still don't have a nnote on the string, flag it as 'dontPlay'
        for (int s = 0; s < getStrings().size(); s++)
        {
            if (getNumNotesAddedToString(getString(s), points) == 0)
            {
                getString(s)->dontPlay = true;
            }
        }

        /***********************************************/
        // Apply extended note names (if applicable)
        if (getTheoryVizInstrumentTheoryContentMode() == TheoryVizInstrumentTheoryContentMode::CHORD)
        {
            if (rule_showExtendedNoteNames)
            {
                vizNote lowestRootNote = vizChord::findLowestRootNote(rootNote, notesAdded);
                //   vizNote lowestrootNote = rootNote;

                for (uiVizWigetStringedInstrumentPoint &point : points)
                {
                    if (calculateIfExtendedNote(lowestRootNote, notesAdded, point.getNoteForPoint(getIsSelectedKeySharp()), rule_strictExtendedNotes))
                    {
                        point.isExtended = true;
                        // the method needs a tweak (for even better coverage) :
                        // additional logic : study the combination qualities to determins (eg 6 vs 11th!) ie if(1 && 3 && 5 && 6) then false...
                        // NEXT : add this same logic for CLICK TO ADD NOTE
                        // check this against the flat 7th (eg for 9ths!)
                    }
                }
            }
        }
        /**********************************************/

        return points;
    }

    bool pointExistsInVector(uiVizWigetStringedInstrumentPoint pointToAdd, vector<uiVizWigetStringedInstrumentPoint> points)
    {
        for (int p = 0; p < points.size(); p++)
        {
            if (points[p].instrumentstring == pointToAdd.instrumentstring && points[p].fret == pointToAdd.fret)
                return true;
        }
        return false;
    }

    bool addSelectedNotesFromPointsForChord(bool isUserDefinedPoints)
    {
        vizChord soughtChord = getSelectedChordByIndex(0);

        clearSelectedNotes();

        // Add selected notes in ascending order as they appear from the thckest string to thinnest
        if (getPoints().size() == 0)
            return false;

        for (int s = 0; s < getStrings().size(); s++)
        {
            for (int p = 0; p < getPoints().size(); p++)
            {
                uiVizWigetStringedInstrumentString *currString = getPoints()[p].instrumentstring;

                if (currString == getString(s))
                {
                    vizNote currNote = getPoints()[p].getNoteForPoint(getIsSelectedKeySharp()); 
                    addSelectedNote(currNote, true); // prevent it adding redundant / duplicate notes
                }
            }
        }

        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));
        string calculatedChordName = getCalculatedChordName();
        string titleName = getUserDefinedChordName() != "" ? getSelectedKey().getNoteName() + getUserDefinedChordName() : calculatedChordName;
        setTitle(titleName + " - " + ofToString(getLowestStartingFret()) + " to " + ofToString(getHighestEndingFret()) + " [" + getTuningName(false) + "]");

        vizChord chord = vizChord(calculatedChordName, getSelectedNotes(), false);
        vizChord chordNormalized = vizChord(calculatedChordName, getNormalizedNotes(getSelectedNotes(), true), true);

        chord.setChordName_UserDefined(getUserDefinedChordName());
        chordNormalized.setChordName_UserDefined(getUserDefinedChordName());
        if(chordDesignerMenuItem) chordDesignerMenuItem->setUserDefinedChordName(getUserDefinedChordName());

        vizNotes notes = vizNotes(getSelectedKey(), "unknown", getSelectedNotes());
        //setDragData(notes.getXML());

        chord.setIsUserDefinedPoints(isUserDefinedPoints || getIsUserEditing());
        chordNormalized.setIsUserDefinedPoints(isUserDefinedPoints || getIsUserEditing());

        if ((chord.isChordValid() || chordNormalized.isChordValid()))
        {
            //chordDesignerMenuItem->addSelectedChordByName(calculatedChordName, getSelectedKey(), false);
            if (chordDesignerMenuItem) chordDesignerMenuItem->addSelectedChord(chord, true, false);
            clearSelectedChords();
            if (chord.isChordValid())
            {
                uiVizWidgetMusical::addSelectedChord(chord, true, true);
                chord.setInstrumentRules(getInstrumentRules());
                chord.setIsUserDefinedPoints(true);
                setDragData(chord.getXML());

                if (soughtChord.isChordValid() && soughtChord.getChordName() == chord.getChordName())
                {
                    return true; // exact match
                }
                else
                {
                    return false;
                }
            }
            else
            {
                uiVizWidgetMusical::addSelectedChord(chordNormalized, true, true);
                chordNormalized.setInstrumentRules(getInstrumentRules());
                chordNormalized.setIsUserDefinedPoints(true);
                setDragData(chordNormalized.getXML());
            }
        }
        else
        {
            clearSelectedChords();

            // Unknown chord
            string unknownChordName = getSelectedKey().getNoteName();
            vizChord unknownChord = vizChord(unknownChordName, getSelectedNotes(), false);

            if (chordDesignerMenuItem) chordDesignerMenuItem->addSelectedChord(unknownChord, true, false);

            unknownChord.setIsUserDefinedPoints(true);
            unknownChord.setChordName_UserDefined("???");
            uiVizWidgetMusical::addSelectedChord(unknownChord, true, true);
            unknownChord.setInstrumentRules(getInstrumentRules());
            setDragData(unknownChord.getXML());
        }

        return false;
    }

    bool addSelectedNotesFromPointsForScale()
    {

        vizScale soughtScale = getSelectedScale();

        clearSelectedNotes();

        // Add selected notes in ascending order as they appear from the thckest string to thinnest
        if (getPoints().size() == 0)
            return false;

        for (int s = 0; s < getStrings().size(); s++)
        {
            for (int p = 0; p < getPoints().size(); p++)
            {
                uiVizWigetStringedInstrumentString *currString = getPoints()[p].instrumentstring;

                if (currString == getString(s))
                {
                    vizNote currNote = getPoints()[p].getNoteForPoint(getIsSelectedKeySharp());
                    addSelectedNote(currNote, true); // prevent it adding redundant / duplicate notes
                }
            }
        }

        string calculatedScaleName = getSelectedScale().getName();
        string key = getSelectedScale().getKey().getNoteName();
        setTitle(key + " " + getSelectedScale().getNamePretty() + " - " + ofToString(getLowestStartingFret()) + " to " + ofToString(getHighestEndingFret()) + " [" + getTuningName(false) + "]");

        vizScale scale = vizScale(key, calculatedScaleName, getSelectedNotes());
        vizScale scaleNormalized = vizScale(key, calculatedScaleName);

        if (scale.isScaleValid() || scaleNormalized.isScaleValid())
        {

            if(scalePickerMenuItem) scalePickerMenuItem->addSelectedScaleByName(calculatedScaleName, getSelectedScale().getKey(), false);
            clearSelectedScale();

            if (scale.isScaleValid())
            {
                uiVizWidgetMusical::setSelectedScale(scale, true);
                scale.setInstrumentRules(getInstrumentRules());
                setDragData(scale.getXML());

                /*
                if (soughtScale.isScaleValid() && soughtScale.getScaleName()  == Scale.getScaleName()) {
                    return true; // exact match
                } else {
                    return false;
                }
                */
                return true;
            }
            else
            {
                uiVizWidgetMusical::setSelectedScale(scaleNormalized, true);
                scaleNormalized.setInstrumentRules(getInstrumentRules());
                setDragData(scaleNormalized.getXML());
            }
        }
        else
        {
            if(scalePickerMenuItem) scalePickerMenuItem->clearSelectedNotesAndInitWithUnknown();
        }

        return false;
    }

    void calculatePoints()
    {
        //plotDiagnosticPoints(); return;

        // DO !NOT! set setStartFret or setEndFret in here, as it creates infinite loop (setStartFret calls calculatePoints)
        // setStartFret(getOriginalLowestStartingFret(), false, false);
        // setEndFret(getOriginalHighestEndingFret(), false, false);

        switch (getTheoryVizInstrumentTheoryContentMode())
        {
        case TheoryVizInstrumentTheoryContentMode::CHORD:
        {
            calculatePointsForChord();
            break;
        }

        case TheoryVizInstrumentTheoryContentMode::SCALE:
        {
            calculatePointsForScale();
            break;
        }
        }
    }

    vector<uiVizWigetStringedInstrumentPoint> trimStringPointsOutsideFretRange(
        vector<uiVizWigetStringedInstrumentPoint> userDefinedFretPoints, int lowestStartingFret, int highestEndingFret)
    {

        vector<uiVizWigetStringedInstrumentPoint> tmp_userDefinedFretPoints;
        for (uiVizWigetStringedInstrumentPoint point : userDefinedFretPoints)
        {
            if (point.fret == 0 || (point.fret >= lowestStartingFret && point.fret <= highestEndingFret))
            {
                tmp_userDefinedFretPoints.push_back(point);
            }
        }
        return tmp_userDefinedFretPoints;
    }

    void optimizeFretRangeForCurrentStringPoints()
    {
        int mOriginalLowestStartingFret = 1000;
        int mOriginalHighestEndingFret = 0;
        for (uiVizWigetStringedInstrumentString currString : getStrings())
        {
            vector<uiVizWigetStringedInstrumentPoint> stringPoints = getFretPointsForString_From_CSV(&currString);
            for (int j = 0; j < stringPoints.size(); j++)
            {
                uiVizWigetStringedInstrumentPoint fretPoint = stringPoints[j];
                if (fretPoint.fret > 0 && fretPoint.fret < mOriginalLowestStartingFret)
                    mOriginalLowestStartingFret = fretPoint.fret;
                if (fretPoint.fret > mOriginalHighestEndingFret)
                    mOriginalHighestEndingFret = fretPoint.fret;
            }
        }
        mOriginalLowestStartingFret = mOriginalLowestStartingFret == 1000 ? 0 : mOriginalLowestStartingFret;
        mOriginalHighestEndingFret = mOriginalHighestEndingFret == 0 ? 3 : mOriginalHighestEndingFret;
        setStartFret(mOriginalLowestStartingFret, true, false);
        setEndFret(mOriginalHighestEndingFret, true, false);
    }

    void calculatePointsForChord()
    {

        //setUserDefinedChordName("");

        bool isUserDefinedPoints = (getSelectedChords().size() > 0 && getSelectedChords()[0].getIsUserDefinedPoints()) || getIsUserEditing();

        if (isUserDefinedPoints)
        {

            vector<uiVizWigetStringedInstrumentPoint> userDefinedFretPoints;

            for (int s = 0; s < getStrings().size(); s++)
            {
                uiVizWigetStringedInstrumentString *currString = getString(s);
                vector<uiVizWigetStringedInstrumentPoint> fretPoints = getFretPointsForString_From_CSV(currString);
                userDefinedFretPoints.insert(userDefinedFretPoints.end(), fretPoints.begin(), fretPoints.end());
            }

            // if (isUserDefinedPoints)
            // {
                if (getIsChordDiagramMode())
                {
                    //  userDefinedFretPoints = trimStringPointsOutsideFretRange(userDefinedFretPoints, getLowestStartingFret(), getHighestEndingFret());
                }
                if (!getIsChordDiagramMode() && getIsUserEditing()) {
                    optimizeFretRangeForCurrentStringPoints();
                } 
                addPoints(userDefinedFretPoints);
            // }

            addSelectedNotesFromPointsForChord(isUserDefinedPoints);
            return;
        }

        /* TODO:
         
         problems:
         1.) Dragging Extended eg A13 from FB to Chord Designer or Bucket - loses Extended property
         2.) Custom chord (eg made up, which doesn't have a name) - provide name and save selected notes
            eg D13 @ 5th fret (the 13th note - 3 or 5 note missing IS valid!
         4.) Update stringedInstrument to scroll to selected chord name in menu
         5.) D6 is a good example of where calculate extended chord fails!
         6.) WHEN Formulating D13 (for example - see 5th fret position), if you omit the 5, or the 3, the chord becomes "unknown" !
         7.) Rules data - persist!
         8.) Fix extended cal function
         9.) Fix Shaps / flats calc...
         11.) When comparing chord names - use like for like (ie consistent stored name vs ::determine output)
         12.) D 7#11 - drags fine onto FB, but fails to in chord bucket!
         13.) String enabled property inn rule data!
         
         MAJOR BUG - dragging A Maj13 to chord designer doesn't select correct notes! think it's to do with the flat notes!
         
         
         
         //todo - rules around 6/9 chords etc... where no 7th added.... should not show extended!
         //(using strict should mitigate this, but test...)
         
         // rule_strictExtendedNotes = true;
         
         // TODO:
         // rule chordFretRange (eg stretch) default it to 3 (different to start/end fret)
         //  may produce more than one chord - show arrow - next pref
         
         
         //chord designer bug fixes (odd chords)
         // blue book
         
         

         
         Chord mode | scale mode!
         
         */

        // User is not editing, clear notes and then calculate points to add

        // there is a discreppancy with endFret coloring...
        // ie click fret number 2 - the 3rd gets highlighted....

        // optimization
        // VIOLIN ??
        // Simplified mode (for chord diags)
        // Acoustic strings :P
        // Zoom, rotate, focus keyboard only
        // sitar

        clearPoints();
        clearSelectedNotes();

        // Revert any strings set not to be played
        for (int s = 0; s < getStrings().size(); s++)
        {
            getString(s)->dontPlay = false;
        }

        if (getSelectedChordsSize() > 0)
        {
            vizChord chord = getSelectedChordByIndex(0);

            if (chord.isChordValid())
            {

                // NOT IN USE?? chord.setInstrumentRule("general", "allowInversions", false);
                chord.setInstrumentRules(getInstrumentRules());
                chord.setInstrumentRule("stringed", "notesPerString", 1);

                int rule_startingInversion = chord.getInstrumentRule("general", "startingInversion", 0);

                int attemptNum = 1;
                int maxAttempts = 10;
                bool exactMatchFound = false;
                bool searchForExactChordMatch = getInstrumentRule("general", "searchForExactChordMatch", false);                              // Move this to a global musicalWidget bool variable for performance reasons
                bool searchForExactChordMatchDownwards = (getInstrumentRule("general", "searchForExactChordMatchDirection", "up") == "down"); // up | down

                if (!searchForExactChordMatch)
                    maxAttempts = 1;

                vector<vizNote> notes = chord.getNotes();
                vizNote chordRootNote = chord.getChordRootNote();

                while (attemptNum <= maxAttempts && !exactMatchFound)
                {
                    attemptNum++;
                    setSelectedKey(chord.getChordRootNote());
                    clearPoints();
                    addPoints(getPointsForNotes(notes, chordRootNote, chord));

                    exactMatchFound = addSelectedNotesFromPointsForChord(false);

                    if (!exactMatchFound && searchForExactChordMatch)
                    {

                        if (searchForExactChordMatchDownwards && getLowestStartingFret() < 0)
                        {
                            setStartFret(getOriginalLowestStartingFret(), false, false);
                            setEndFret(getOriginalHighestEndingFret(), false, false);
                            searchForExactChordMatchDownwards = false;
                        }
                        else if (!searchForExactChordMatchDownwards && getHighestEndingFret() > mTotalFrets)
                        {
                            setStartFret(getOriginalLowestStartingFret(), false, false);
                            setEndFret(getOriginalHighestEndingFret(), false, false);
                            searchForExactChordMatchDownwards = true;
                        }

                        setStartFret(getLowestStartingFret() + (searchForExactChordMatchDownwards ? -1 : 1), false, false);
                        setEndFret(getHighestEndingFret() + (searchForExactChordMatchDownwards ? -1 : 1), false, false);
                    }
                }
            }
        }
    }

    void calculatePointsForScale()
    {
        vizScale scale = getSelectedScale();
        if (scale.getName() != "" && scale.getKey().getNoteName() != "")
        {
            setSelectedKey(scale.getKey());

            vector<vizNote> notes = scale.getNotes();
            vizNote scaleRootNote = scale.getKey();

            scale.setInstrumentRules(getInstrumentRules());
            int rule_notesPerString = getInstrumentRule("stringed", "notesPerString", 3);
            if (rule_notesPerString < 3)
                rule_notesPerString = 3;

            bool rule_allowNoteRepetition = getInstrumentRule("general", "allowNoteRepetition", false); //(Repetition of exact notes and octave eg C3==C3)

            scale.setInstrumentRule("general", "startingInversion", -1); // -1 = start on any inversion, 0 for no inv, 1 for 1st inversion
            scale.setInstrumentRule("stringed", "notesPerString", rule_notesPerString);
            scale.setInstrumentRule("general", "allowNoteRepetition", rule_allowNoteRepetition); // slight problem: 1.) when this is true, scale doesnt always start on root. 2.) starting inversion --- move up fretboard searching (like chord does)
            scale.setInstrumentRule("general", "allowNoteRepetitionExactOctave", false);         // slight problem: 1.) when this is true, scale doesnt always start on root. 2.) starting inversion --- move up fretboard searching (like chord does)
            scale.setInstrumentRule("general", "exactOctaveMatch", false);
            scale.setInstrumentRule("general", "showExtendedNoteNames", false);
            scale.setInstrumentRule("general", "strictExtendedNotes", false);  // notes MUST be greater than the root octave
            scale.setInstrumentRule("general", "enforceAscendingNotes", true); // next note MUST be greater than the previous

            clearPoints();
            clearSelectedNotes();
            addPoints(getPointsForNotes(notes, scaleRootNote, scale));
            bool exactMatchFound = addSelectedNotesFromPointsForScale();
        }
    }

    void plotDiagnosticPoints()
    {
        // Diagnostics: plot a point on every single fret
        vector<uiVizWigetStringedInstrumentPoint> diagnosticPoints = {};
        for (int i = 0; i <= mTotalFrets; i++)
        {
            for (int j = 0; j < mStrings.size(); j++)
            {
                ofColor color = mStrings[j].note.calculateNoteKeyColor(i);
                diagnosticPoints.push_back(uiVizWigetStringedInstrumentPoint(getString(j), i, color));
            }
        }
        addPoints(diagnosticPoints);

        setTitle(getTuningName(true));
    }

    virtual string getTuningName(bool includeNoteNames)
    {
        if (getStrings().size() > 0)
        {

            if(ofIsStringInString(getStrings()[0].note.getNoteTags()[0], "CUSTOM")) {
                return "CUSTOM: (" + getTuningNoteNames(getStrings(), true) + ")";
            }

            return getStrings()[0].note.getNoteTagsString("|") + (includeNoteNames ? " (" + getTuningNoteNames(getStrings(), true) + ")" : "");
        }
        return "unknown";
    }

    string getPointLabelForState(vizNote note, uiVizWigetStringedInstrumentPoint point)
    {
        string additionalText = "";

        if(point.sequenceNumber > 0) {
            additionalText = "*" + ofToString(point.sequenceNumber);
        }

        switch (getTheoryVizLabelMode())
        {
        case TheoryVizLabelMode::NONE:
            return "";
            break;

        case TheoryVizLabelMode::KEYS:
            return note.getNoteName() + additionalText;
            break;

        case TheoryVizLabelMode::DEGREES:
            if (getSelectedKey().getNoteName() != "")
            {
                return (note.getIsExtended() || point.isExtended ? getSelectedKey().getNoteNameRomanExtended(note.getNoteName()) : getSelectedKey().getNoteNameRoman(note.getNoteName())) + additionalText;
            }
            else
            {
                return note.getNoteName() + additionalText;
            }
            break;
        };

        return "?";
    }

    virtual void updateMinimized() override
    {
    }

    virtual void drawMinimized() override
    {
    }

    void performOperationForKeyPress(int key)
    {
        switch (key)
        {

        case VIZ_KEY_NUMBER_3: // Toggling orientation

            switch (getTheoryVizOrientationMode())
            {
            case TheoryVizOrientationMode::HORIZONTAL:
                setTheoryVizOrientationMode(TheoryVizOrientationMode::VERTICAL);
                break;
            case TheoryVizOrientationMode::VERTICAL:
                setTheoryVizOrientationMode(TheoryVizOrientationMode::HORIZONTAL);
                break;
            }
            setBoundsForOrientation(getTheoryVizOrientationMode());
            setWidgetNeedsUpdate(true);
            break;

        case VIZ_KEY_NUMBER_4: // Toggling lefty mode
            setIsLefty(!isLefty());
            setBoundsForOrientation(getTheoryVizOrientationMode());
            setWidgetNeedsUpdate(true);
            setNeedsUpdate(true);
            break;

        case VIZ_KEY_NUMBER_5: // Chord Diagram mode
            setIsChordDiagramMode(!getIsChordDiagramMode());       
            break;

        // Sequenced note inc/dec
        case OF_KEY_UP: 
            if (mSequencedNoteNumber < 5) mSequencedNoteNumber++;
            setTitle("Note Seq: " + ofToString(mSequencedNoteNumber));
            break;      

        case OF_KEY_DOWN: 
            if (mSequencedNoteNumber > 1) mSequencedNoteNumber--;
            setTitle("Note Seq: " + ofToString(mSequencedNoteNumber));
            break;

        }

        setNeedsUpdate(true);
    }

    virtual void onWidgetKeyPressed(ofKeyEventArgs &e) override
    {
        uiVizWidgetMusical::onWidgetKeyPressed(e);
        performOperationForKeyPress(e.key);
    }

    //todo - add the 7,8 stringg options

    vector<uiVizWigetStringedInstrumentFret> getFrets()
    {
        return mFrets;
    }

    void setFrets(vector<uiVizWigetStringedInstrumentFret> frets)
    {
        mFrets = frets;
    }

    virtual vector<uiVizWigetStringedInstrumentString> getStrings()
    {
        return mStrings;
    }

    vector<uiVizWigetStringedInstrumentString> getStringsFromRules()
    {
        ofxXmlSettings settings = getInstrumentRules();
        return getStringsFromXML(settings);
    }

    vector<uiVizWigetStringedInstrumentString> getStringsFromRules(vizTheoryBase theoryObj)
    {
        ofxXmlSettings settings = theoryObj.getInstrumentRules();
        //cout << theoryObj.getInstrumentRulesXMLString();
        return getStringsFromXML(settings);
    }

    virtual uiVizWigetStringedInstrumentString *getString(int string)
    {
        return &mStrings[string];
    }

    virtual void setStrings(vector<uiVizWigetStringedInstrumentString> strings, bool shouldUpdateRules)
    {

        if (strings.size() == 0)
            return;

        mStrings.clear();

        for (int i = 0; i < strings.size(); i++)
        {
            mStrings.push_back(strings[i]);
        }

        synchronizeMenuWithStringsEnabledProperty();
        synchronizeMenuWithTuning();

        mOriginalLowestStartingFret = getLowestStartingFret();
        mOriginalHighestEndingFret = getHighestEndingFret();

        setStartFret(mOriginalLowestStartingFret, true, false);
        setEndFret(mOriginalHighestEndingFret, true, false);

        if (shouldUpdateRules)
        {
            updateRules(getInstrumentRules(), false, false, "setStrings");
        }
    }

    void synchronizeMenuWithTuning()
    {
        string tuning = getTuningName(false);

        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu == NULL || menu == nullptr)
            return;

        menu->selectMenuItem(MENU_GROUP_1::MENU_TAB_TUNINGS, tuning, false);
    }

    // todo - move this functionality to a generic menu method *(elect by tag value...)
    void synchronizeStringsEnabledPropertyWithMenu()
    {
        // Enable / disable strings
        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu == NULL || menu == nullptr)
            return;

        vector<uiVizWidgetMenuSlice> *menuSlices = menu->getMenuTabSlice(MENU_GROUP_1::MENU_TAB_STRINGS);
        vector<uiVizWidgetMenuSlice> &menuSlicesRef = *menuSlices;

        if (menuSlices != NULL && menuSlices->size() > 0 && menuSlices->size() == mStrings.size())
        {
            for (int i = 0; i < mStrings.size(); i++)
            {
                mStrings[i].isEnabled = menuSlicesRef[i].menuItem.isSelected;
            }
        }
    }

    void synchronizeMenuWithStringsEnabledProperty()
    {
        // Enable / disable strings
        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu == NULL || menu == nullptr)
            return;

        vector<uiVizWidgetMenuSlice> *menuSlices = menu->getMenuTabSlice(MENU_GROUP_1::MENU_TAB_STRINGS);
        vector<uiVizWidgetMenuSlice> &menuSlicesRef = *menuSlices;

        for (int i = 0; i < mStrings.size(); i++)
        {
            if (menuSlices != NULL && menuSlices->size() > 0 && menuSlices->size() == mStrings.size())
            {
                menuSlicesRef[i].menuItem.isSelected = mStrings[i].isEnabled;
            }
        }
    }

    void synchronizeMenuWithStartFretProperty()
    {
        // Enable / disable strings
        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu == NULL || menu == nullptr)
            return;

        int fretNum = getLowestStartingFret();

        vector<uiVizWidgetMenuSlice> *menuSlices = menu->getMenuTabSlice(MENU_GROUP_1::MENU_TAB_START_FRET);
        vector<uiVizWidgetMenuSlice> &menuSlicesRef = *menuSlices;

        for (int i = 0; i <= mTotalFrets; i++)
        {
            if (menuSlices != NULL && menuSlices->size() >= fretNum)
            {
                menuSlicesRef[i].menuItem.isSelected = (i == fretNum);
            }
        }
    }

    void synchronizeMenuWithEndFretProperty()
    {
        // Enable / disable strings
        uiVizWidgetMenu *menu = static_cast<uiVizWidgetMenu *>(instrumentContextMenu);
        if (menu == NULL || menu == nullptr)
            return;

        int fretNum = getHighestEndingFret();

        vector<uiVizWidgetMenuSlice> *menuSlices = menu->getMenuTabSlice(MENU_GROUP_1::MENU_TAB_END_FRET);
        vector<uiVizWidgetMenuSlice> &menuSlicesRef = *menuSlices;

        for (int i = 0; i <= mTotalFrets; i++)
        {
            if (menuSlices != NULL && menuSlices->size() >= fretNum)
            {
                menuSlicesRef[i].menuItem.isSelected = (i == fretNum);
            }
        }
    }

    void enableAllStrings()
    {
        for (int i = 0; i < mStrings.size(); i++)
        {
            mStrings[i].isEnabled = true;
        }
    }

    vector<uiVizWigetStringedInstrumentPoint> getFretPointsForString(uiVizWigetStringedInstrumentString *currString)
    {
        vector<uiVizWigetStringedInstrumentPoint> stringPoints;
        for (int i = 0; i < getPoints().size(); i++)
        {
            if (getPoints()[i].instrumentstring == currString)
            {
                stringPoints.push_back(getPoints()[i]);
            }
        }
        return stringPoints;
    }

    vector<uiVizWigetStringedInstrumentPoint> getFretPointsForString_From_CSV(uiVizWigetStringedInstrumentString *currString)
    {
        vector<uiVizWigetStringedInstrumentPoint> stringPoints;

        vector<string> points = ofSplitString(currString->getFretPoints_CSV(), "|");
        for (string point : points)
        {
            if (point == "")
                continue;

            // Extended note?
            bool isExtendedNote = false;
            if (ofIsStringInString(point, "x"))
            {
                isExtendedNote = true;
                ofStringReplace(point, "x", "");
            }

            // Note sequence?
            int sequenceNumber = 0;
            if (ofIsStringInString(point, "+1"))
            {
                ofStringReplace(point, "+1", "");                
                sequenceNumber = 1;
                
            }   

            if (ofIsStringInString(point, "+2"))
            {
                ofStringReplace(point, "+2", "");                
                sequenceNumber = 2;
                
            }   

            if (ofIsStringInString(point, "+3"))
            {
                ofStringReplace(point, "+3", "");                
                sequenceNumber = 3;
                
            }   

            if (ofIsStringInString(point, "+4"))
            {
                ofStringReplace(point, "+4", "");                
                sequenceNumber = 4;
                
            }   

            if (ofIsStringInString(point, "+5"))
            {
                ofStringReplace(point, "+5", "");                
                sequenceNumber = 5;
                
            }                                       







            if (ofTrim(point) == "0")
            {
                stringPoints.push_back(uiVizWigetStringedInstrumentPoint(currString, 0, isExtendedNote, sequenceNumber));
            }
            else
            {
                int intVal = std::atoi(point.c_str());
                if (intVal != 0)
                    stringPoints.push_back(uiVizWigetStringedInstrumentPoint(currString, intVal, isExtendedNote, sequenceNumber));
            }
        }
        return stringPoints;
    }

    string getFretPointsForString_CSV(uiVizWigetStringedInstrumentString *currString)
    {
        vector<uiVizWigetStringedInstrumentPoint> stringPoints = getFretPointsForString(currString);
        string fretPoints = "";
        for (int i = 0; i < stringPoints.size(); i++)
        {
            uiVizWigetStringedInstrumentPoint fretPoint = stringPoints[i];
            fretPoints += "|" + ofToString(fretPoint.fret) + (fretPoint.isExtended ? "x" : "");
            if(fretPoint.sequenceNumber > 0) fretPoints += "+" + ofToString(fretPoint.sequenceNumber);
        }
        if (fretPoints != "")
            fretPoints += "|";

        return fretPoints;
    }

    vector<uiVizWigetStringedInstrumentPoint> getPoints()
    {
        return mPoints;
    }

    int getTotalSequencedPoints() {
        int sequencedPoints = 0;
        for(uiVizWigetStringedInstrumentPoint point:mPoints) {
            if (point.sequenceNumber > 0) {
                sequencedPoints++;
            }
        }
        return sequencedPoints;
    }


    int getTotalSequencedPointsForString(uiVizWigetStringedInstrumentString *string) {
        int sequencedPoints = 0;
        for(uiVizWigetStringedInstrumentPoint point:getFretPointsForString(string)) {
            if (point.sequenceNumber > 0) {
                sequencedPoints++;
            }
        }
        return sequencedPoints;
    }    

    void addPoints(vector<uiVizWigetStringedInstrumentPoint> points)
    {
        mPoints = points;

        // Set the calculated points for the string
        for (int s = 0; s < getStrings().size(); s++)
        {
            uiVizWigetStringedInstrumentString *currString = getString(s);
            string fretPoints_CSV = getFretPointsForString_CSV(currString);
            vector<uiVizWigetStringedInstrumentPoint> fretPoints = getFretPointsForString(currString);
            currString->setFretPoints_CSV(fretPoints_CSV);
        }

        updateRules(getInstrumentRules(), false, false, "addPoints");
    }

    int getNumPointsOnString(uiVizWigetStringedInstrumentString *string, bool includeSequencedNotes)
    {
        int numPointsOnString = 0;
        for (int i = 0; i < getPoints().size(); i++)
        {
            if (getPoints()[i].instrumentstring == string) {
                
                if (getPoints()[i].sequenceNumber > 0 && includeSequencedNotes || getPoints()[i].sequenceNumber == 0) {
                    numPointsOnString++;
                }
            }
                
        }
        return numPointsOnString;
    }

    bool addPoint(uiVizWigetStringedInstrumentPoint point)
    {

        int maxPointsPerString = getInstrumentRule("stringed", "notesPerString", 1);

        // Remove / toggle it if it was already there
        for (int i = 0; i < getPoints().size(); i++)
        {
            uiVizWigetStringedInstrumentPoint currExistingPoint = getPoints()[i];
            if (currExistingPoint.instrumentstring == point.instrumentstring)
            {

                int numPointsOnString = getNumPointsOnString(point.instrumentstring, false);

                if (currExistingPoint.fret == point.fret)
                {
                    mPoints.erase(mPoints.begin() + i);
                    addPoints(mPoints);
                    return false;
                }

                if (numPointsOnString >= maxPointsPerString && point.sequenceNumber == 0) // Adding a non sequenced note!
                {
                    if (currExistingPoint.sequenceNumber == 0) {
                        mPoints.erase(mPoints.begin() + i);
                    }
                }
            }
        }

        mPoints.push_back(point);

        addPoints(mPoints);
        return true;
    }

    void clearPoints()
    {
        mPoints = vector<uiVizWigetStringedInstrumentPoint>();
    }

    bool getDrawPointsOnFrets()
    {
        return mDrawPointsOnFrets;
    }

    void setDrawPointsOnFrets(bool val)
    {
        mDrawPointsOnFrets = val;
    }

    void setFretWidthToHeightRatio(float val)
    {
        mFRET_WIDTH_TO_HEIGHT_RATIO = val;
    }

    void setSizeNormalized(float val)
    {
        mSIZE_NORMALIZED = val;
    }

    string getTuningNoteNames(vector<uiVizWigetStringedInstrumentString> strings, bool includeOctaves)
    {
        string tmp = "";
        if (getStrings().size() > 0)
        {
            for (int i = 0; i < strings.size(); i++)
            {
                if (i > 0)
                    tmp += "-";
                tmp += strings[i].note.getNoteName();
                if (includeOctaves)
                    tmp += ofToString(strings[i].note.getNoteOctave());
            }
            return tmp;
        }
        return "";
    }

    /************ MENU ************/
    uiVizWidget *getPopoutWidgetForMenuTag(int menuTag) override
    {
        switch (menuTag)
        {
        case uiVizIconCache::IconTag::WIDGET_SETTINGS:
            return instrumentContextMenu;
        case uiVizIconCache::IconTag::WIDGET_SETTINGS_MINI:
            return instrumentContextMenuMini;            
        default:
            return nullptr;
        }
    }

    void onWidgetMousePressed(ofMouseEventArgs &e) override
    {
        if (e.button == OF_MOUSE_BUTTON_RIGHT && getUserCanInvokeContextMenu())
        {
            instrumentContextMenuMini->setIsVisible(false);
            showContextMenu(uiVizIconCache::IconTag::WIDGET_SETTINGS, deScale(ofGetMouseX()) - 20, deScale(ofGetMouseY()) - 20);

            /*
            uiVizWidget* w = getPopoutWidgetForMenuTag(uiVizIconCache::IconTag::WIDGET_SETTINGS);
            w->popoutFrom(getX() + getWidth() / 2, getY(), PopoutDirection::UP);
*/
        }
    }

    /******************************/

    virtual vector<vector<uiVizWigetStringedInstrumentString>> getTunings()
    {

        return {};
    }

    virtual vector<uiVizWidgetMenuItem> getTuningsMenuItems()
    {

        vector<uiVizWidgetMenuItem> tuningsMenuItems = {};
        vector<vector<uiVizWigetStringedInstrumentString>> tunings = getTunings();

        for (int i = 0; i < tunings.size(); i++)
        {
            if (i == 0) {
                tuningsMenuItems.push_back(
                    uiVizWidgetMenuItem("Custom...", -1, false, false)
                );
            }

            vector<uiVizWigetStringedInstrumentString> strings = tunings[i];

            if (strings.size() > 0)
            {
                tuningsMenuItems.push_back(
                    uiVizWidgetMenuItem(strings[0].note.getNoteTagsString("|") + " (" + getTuningNoteNames(strings, true) + ")", strings[0].note.getNoteTagsString("|"), i, false, i == 0));
            }
        }

        return tuningsMenuItems;
    }

    virtual vector<uiVizWidgetMenuItem> getStringsMenuItems()
    {

        vector<uiVizWidgetMenuItem> stringsMenuItems = {};
        vector<uiVizWigetStringedInstrumentString> strings = getStrings();

        for (int i = 0; i < strings.size(); i++)
        {
            stringsMenuItems.push_back(
                uiVizWidgetMenuItem(strings[i].note.getNoteName() + " string", i, true, strings[i].isEnabled));
        }
        return stringsMenuItems;
    }

    virtual vector<uiVizWidgetMenuItem> getStartFretMenuItems()
    {

        vector<uiVizWidgetMenuItem> fretItems = {};

        for (int i = 0; i <= mTotalFrets; i++)
        {
            fretItems.push_back(
                uiVizWidgetMenuItem("Fret " + ofToString(i), i, false, i == 0));
        }
        return fretItems;
    }

    virtual vector<uiVizWidgetMenuItem> getEndFretMenuItems()
    {

        vector<uiVizWidgetMenuItem> fretItems = {};

        for (int i = 0; i <= mTotalFrets; i++)
        {
            fretItems.push_back(
                uiVizWidgetMenuItem("Fret " + ofToString(i), i, false, i == 0));
        }
        return fretItems;
    }

    virtual void onKeyChanged(vizNote note) override
    {

        // Set the selected note from the sender
        switch (getTheoryVizInstrumentTheoryContentMode())
        {
        case TheoryVizInstrumentTheoryContentMode::CHORD:
        {
            setSelectedKey(note, true);
            if (chordDesignerMenuItem) {
                chordDesignerMenuItem->setSelectedKey(note);
                vizChord chord = vizChord(chordDesignerMenuItem->getCalculatedChordName(), chordDesignerMenuItem->getSelectedNotes(), true);
                addSelectedChord(chord, true, true, true);
            }

            setNeedsUpdate(true);
            break;
        }

        case TheoryVizInstrumentTheoryContentMode::SCALE:
        {
            setSelectedKey(note, true);
            if(scalePickerMenuItem) {
                vizScale scale = vizScale(note.getNoteName(), scalePickerMenuItem->getCalculatedScaleName());
                setSelectedScale(scale, true);
            }

            setNeedsUpdate(true);
            break;
        }
        }
        setNeedsUpdate(true);
    }

    void onKeyPickerMenuKeySelected(uiVizNoteSelectedArgs &args)
    {
        onKeyChanged(args.note);
    }

    void onChordDesignerMenuNoteSelected(uiVizNoteSelectedArgs &args)
    {
        // Add / remove selected Note
        setUserDefinedChordName("");

        vizChord chord = vizChord(chordDesignerMenuItem->getCalculatedChordName(), chordDesignerMenuItem->getSelectedNotes(), true);
        if (chord.isChordValid())
        {
            addSelectedChord(chord, true, true, false);
            setNeedsUpdate(true);
        }
        else
        {
            vizChord chordNormalized = vizChord(chordDesignerMenuItem->getSelectedKey().getNoteName(), getNormalizedNotes(chordDesignerMenuItem->getSelectedNotes(), false), true);
            addSelectedChord(chordNormalized, true, true, false);
            setNeedsUpdate(true);
        }
    }

    virtual void setUserDefinedChordName(string val) override
    {
        uiVizWidgetMusical::setUserDefinedChordName(val);
        vizChord *chord = getSelectedChordByIndexRef(0);
        if (chord)
        {
            chord->setChordName_UserDefined(val);
            setDragData(chord->getXML());
        }
    }

    void onUserDefinedChordNameChanged(uiVizTextChangedArgs &args)
    {
        setUserDefinedChordName(args.text);
        string calculatedChordName = getCalculatedChordName();
        string titleName = getUserDefinedChordName() != "" ? getSelectedKey().getNoteName() + getUserDefinedChordName() : calculatedChordName;
        setTitle(titleName + " - " + ofToString(getLowestStartingFret()) + " to " + ofToString(getHighestEndingFret()) + " [" + getTuningName(false) + "]");
    }

    void onScalePickerMenuNoteSelected(uiVizNoteSelectedArgs &args)
    {
        vizScale scale = vizScale(scalePickerMenuItem->getSelectedKey().getNoteName(), scalePickerMenuItem->getCalculatedScaleName());
        setSelectedScale(scale, true);
        setNeedsUpdate(true);
    }

    /*--------------------------------------------------*/

    void addSelectedChord(vizChord &chord, bool onlyAddIfNotFound, bool includeInstrumentRules, bool updateChordDesignerMenuItem)
    {
        setIsUserEditing(false);
        clearSelectedChords();
        setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode::CHORD);

        //if (!chord.isChordValid()) return;

        setSelectedKey(chord.isChordValid() ? chord.getChordRootNote() : getSelectedKey(), true); ///dfgdsfgdfs slows it down!!!

        uiVizWidgetMusical::addSelectedChord(chord, onlyAddIfNotFound, includeInstrumentRules);
        vector<uiVizWigetStringedInstrumentString> ruleStrings = getStringsFromRules(chord);

        if (ruleStrings.size() == 0)
            ruleStrings = getStrings();

        setStrings(ruleStrings, false);
        calculatePoints();
        setNeedsUpdate(true);
        setWidgetNeedsUpdate(true);

        if (updateChordDesignerMenuItem && chordDesignerMenuItem)
        {

            if (chord.isChordValid())
            {
                //chordDesignerMenuItem->setSelectedKey(getSelectedKey());
                chordDesignerMenuItem->addSelectedChord(chord, onlyAddIfNotFound, includeInstrumentRules);
                chordDesignerMenuItem->setNeedsUpdate(true);
            }
            else
            {

                vizChord normalizedChord = vizChord(getSelectedKey().getNoteName(), chord.getNotes(), true);
                chordDesignerMenuItem->addSelectedChord(chord, onlyAddIfNotFound, includeInstrumentRules);
                chordDesignerMenuItem->setNeedsUpdate(true);
            }
        }
    }

    void addSelectedChord(vizChord &chord, bool onlyAddIfNotFound, bool includeInstrumentRules) override
    {
        addSelectedChord(chord, onlyAddIfNotFound, includeInstrumentRules, true);
    }

    virtual void setSelectedScale(vizScale scale, bool includeInstrumentRules) override
    {
        if (
            getSelectedScale().getKey().getNoteName() == scale.getKey().getNoteName() &&
            getSelectedScale().getName() == scale.getName()
            ) return;
        setIsUserEditing(false);
        setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode::SCALE);
        uiVizWidgetMusical::setSelectedScale(scale, includeInstrumentRules);
        vector<uiVizWigetStringedInstrumentString> ruleStrings = getStringsFromRules(scale);

        if (ruleStrings.size() == 0)
            ruleStrings = getStrings();

        setStrings(ruleStrings, false);
        calculatePoints();
        setNeedsUpdate(true);
        setWidgetNeedsUpdate(true);

        if(scalePickerMenuItem) {
            scalePickerMenuItem->setSelectedScale(scale.getName(), includeInstrumentRules);
            scalePickerMenuItem->setNeedsUpdate(true);
        }

    }

    void setSelectedKey(vizNote val, bool updateMenuControls)
    {
        uiVizWidgetMusical::setSelectedKey(val);

        if (updateMenuControls)
        {
            if (keyPickerMenuItem)
            {
                keyPickerMenuItem->setSelectedKey(val);
                keyPickerMenuItem->setNeedsUpdate(true);
            }

            if (chordWheelMenuItem)
            {
                chordWheelMenuItem->clearSelectedChordsAndSelectChordWithKey(val);
                chordWheelMenuItem->setNeedsUpdate(true);
            }

            if (chordDesignerMenuItem)
            {
                chordDesignerMenuItem->setSelectedKey(val);
                chordDesignerMenuItem->setNeedsUpdate(true);
            }

            if (scalePickerMenuItem)
            {
                scalePickerMenuItem->setSelectedKey(val);
                scalePickerMenuItem->setNeedsUpdate(true);
            }
        }
    }

    virtual void setSelectedKey(vizNote val) override
    {
        setSelectedKey(val, false);
    }

    void initMenu()
    {
        if (!getUserCanInvokeContextMenu()) return;

        if (!GUIT_DIALOG) {

           GUIT_DIALOG = new uiVizWidgetDialog("GUIT_DIALOG_" + ofToUpper(getWidgetId()), R"(
                <widget>
                    <bounds width="500" height="300" />
                </widget>
                )");           

             uiVizWidgetManager::addWidgetForPopout(*GUIT_DIALOG, getWidgetId(), false);

        }    

        if (!NOTES_TABLE) {

           NOTES_TABLE = new uiVizWidgetNotesTable("NOTES_TABLE_" + ofToUpper(getWidgetId()), R"(
                <widget>
                    <bounds width="500" height="300" />
                </widget>
                )");
            NOTES_TABLE->setShouldCloseUponSelection(true);                

            uiVizWidgetManager::addWidgetForPopout(*NOTES_TABLE, getWidgetId(), true);
        }        


        string menuId = +"SI_MENU1_" + ofToUpper(getWidgetId());

        if (!instrumentContextMenu)
        {

            keyPickerMenuItem = new uiVizWidgetKeyPicker(
                getWidgetId() + "_MENU_KEY_PICKER",
                "<widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/></widget>");

            ofAddListener(keyPickerMenuItem->keySelected, this, &uiVizWigetStringedInstrument::onKeyPickerMenuKeySelected);

            /*
            right clicking in bottom right - widget content overlaps left of menu
            rework all widget menus to get populated from base (eg getKeySelectedMenuTab....)
            and handle all those events on the base too
            bug: right click - as appearing selects the menu tab which is currently hovered!
            -------------------------------------------
            ... THEN move back to sharps/flats bug and chord determination of degrees
            and saving of chord rules ...
            -------------------------------------------
            
            selecteding key ---> should update fretboard with correct chord
            changing from minor to major - > fretboard loses notes
            actually - clicking thge same degree on the desinger "toggles" FB notes/.... weird!
            */

            chordWheelMenuItem = new uiVizWidgetChordWheel(
                getWidgetId() + "_MENU_CHORD_WHEEL",
                "<widget><bounds minWidth='500' minHeight='200' width='500'/><appearance /></widget>");


            chordDesignerMenuItem = new uiVizWidgetChordDesigner(
                getWidgetId() + "_MENU_CHORD_DESIGNER",
                "<widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/></widget>");            


            buttonOpenVariations = dynamic_cast<uiVizWidgetElmButton *>(chordDesignerMenuItem->addOrLoadWidgetElement(buttonOpenVariations, WIDGET_ELM_CLASS::BUTTON, "ARROW_UP", R"(
                <element>
                <bounds width="27" height="27" xExpr="${PARENT.LEFT}" yExpr="${PARENT.BOTTOM}" />
                <properties icon="MED_CONTENT_ARROW_UP"/>
                </element>
                )"));

            buttonOpenSettings = dynamic_cast<uiVizWidgetElmButton *>(chordDesignerMenuItem->addOrLoadWidgetElement(buttonOpenSettings, WIDGET_ELM_CLASS::BUTTON, "ARROW_SETTINGS", R"(
                <element>
                <bounds width="27" height="27" xExpr="${PARENT.RIGHT}" yExpr="${PARENT.BOTTOM}" />
                <properties icon="MED_CONTENT_SETTINGS"/>
                </element>
                )"));

            buttonOpenSettings->handlePressed([this]() {
                uiVizWidgetMenu* menu = dynamic_cast<uiVizWidgetMenu*>(chordDesignerMenuItem->getPopoutWidgetForMenuTag(uiVizIconCache::IconTag::WIDGET_SETTINGS));
                menu->setActiveMenuTabId((int)chordDesignerMenuItem->MENU_GROUP_1::MENU_TAB_CHORD_RULES);                
                menu->popoutFrom(buttonOpenSettings, PopoutDirection::UP, false); 
            });

            buttonOpenVariations->handlePressed([this]() {

                vizChord origChord = getSelectedChordByIndex(0);
                int origStartFret = getLowestStartingFret();
                int origEndFret = getHighestEndingFret();


                string widgetPersistentId = uiVizWidgetManager::getSuggestedNewWidgetPersistentId(APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET);
                chordBucket = dynamic_cast<uiVizWidgetMusical*>(uiVizWidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET, widgetPersistentId, R"(

                <widget shouldPersist="1">
                    <title style="TOP_STATIC" autohide="0" staticSize="20">Chord Bucket</title>
                    <bounds width="600" height="500" maxWidth="28660" maxHeight="17920" minWidth="75" minHeight="75" />
                    <behaviour draggable="1" resizable="1" drawWidgetChrome="1" drawWidgetTitle="1" />
                    <appearance visible="1" shadow="1" roundedRectangle="1" lockAspectRatio="0" aspectRatio="1" minimized="0" />
                    <properties showTopMenu="0" sideBarWidth="0" isSmallerDiagrams="1">
                        <musicData drawMode="RIGHT" chordViewMode="STRINGED_CHORD_DIAGRAM" colorMode="KEYS" colorAlternateMode="NONE" labelMode="KEYS" labelAlternateMode="NONE" noteMode="DEFAULT" labelShowOctave="0" isLefty="0" isBlackAndWhiteMode="0" labelModeChord="KEYS" colorModeEmbedded="KEYS" labelModeEmbedded="KEYS">
                            <selectedKey name="C" />
                            <selectedChords>
                            </selectedChords>
                        </musicData>
                    </properties>
                </widget>
                )"));
                chordBucket->setSelectedKey(getSelectedKey());
                uiVizWidgetManager::addWidget(*chordBucket, true);
                uiVizWidgetManager::centerWidget(chordBucket);

                int chordsAdded = 0;

                vizChord chordNormalized;
                vizChord prevChord;

                vector<uiVizWigetStringedInstrumentString> ruleStrings;
                vector<uiVizWigetStringedInstrumentString> prev_ruleStrings;

                for (int fret = 0; fret<= DEFAULT_FRETS-3; fret++) {
                    setStartFret(fret, false, false);
                    setEndFret(fret+3, false, false);

                    // if(chordsAdded > 5) continue;

                    if (fret == 0) {

                        chordNormalized = vizChord(chordDesignerMenuItem->getSelectedKey().getNoteName(), getNormalizedNotes(chordDesignerMenuItem->getSelectedNotes(), false), true);

                        // setInstrumentRule("general", "startingInversion", -1);
                        setInstrumentRule("general", "searchForExactChordMatch", false); 
                        setInstrumentRule("stringed", "notesPerString", 1);
                        setInstrumentRule("general", "searchForExactChordMatchDirection", "up"); // up | down

                        // addSelectedChord(chordNormalized, true, false, false);

                    }

// rules to scales bug
// embed midi in HTML export (chord bucket)
// new widget -> give it a chord and it gives variations eg Em -> Em7 Emsus etc

                    clearSelectedChords();
                    addSelectedChord(chordNormalized, true, false, false);
                    calculatePointsForChord();

                    vizChord chord = getSelectedChordByIndex(0);


                    ruleStrings = getStringsFromRules(chord);

                    // Dont add if exactly the same as last ...
                    bool isDuplicate = false;
                    if (ruleStrings.size() == prev_ruleStrings.size()) {
                        isDuplicate = true;
                        for (int s=0; s<ruleStrings.size(); s++) {
                            if (ruleStrings[s].getFretPoints_CSV() != prev_ruleStrings[s].getFretPoints_CSV()) {
                                isDuplicate = false;
                            }
                        }
                    }

                    if (!isDuplicate && chord.isChordValid() && chord.getChordName().size() > 1) {
                        chordBucket->populateTargetMusicalWidget(chordBucket, chord.getXML());
                        chordsAdded++;
                        prevChord = chord;
                        prev_ruleStrings = ruleStrings;
                    }

                }

                setStartFret(origStartFret, false, false);
                setEndFret(origEndFret, false, false);
                clearSelectedChords();
                addSelectedChord(origChord, true, true);


            });            


            ofAddListener(chordDesignerMenuItem->rulesChanged, this, &uiVizWigetStringedInstrument::onRulesChanged);
            ofAddListener(chordDesignerMenuItem->noteSelected, this, &uiVizWigetStringedInstrument::onChordDesignerMenuNoteSelected);
            ofAddListener(chordDesignerMenuItem->userDefinedChordNameChanged, this, &uiVizWigetStringedInstrument::onUserDefinedChordNameChanged);

            scalePickerMenuItem = new uiVizWidgetScalePicker(
                getWidgetId() + "_MENU_SCALE_PICKER",
                "<widget><bounds minWidth='100' minHeight='100' width='300' height='300'/><appearance lockAspectRatio='1' aspectRatio='1'/></widget>");
            ofAddListener(scalePickerMenuItem->rulesChanged, this, &uiVizWigetStringedInstrument::onRulesChanged);
            ofAddListener(scalePickerMenuItem->noteSelected, this, &uiVizWigetStringedInstrument::onScalePickerMenuNoteSelected);


            buttonOpenSettingsScale = dynamic_cast<uiVizWidgetElmButton *>(scalePickerMenuItem->addOrLoadWidgetElement(buttonOpenSettingsScale, WIDGET_ELM_CLASS::BUTTON, "ARROW_SETTINGS", R"(
                <element>
                <bounds width="27" height="27" xExpr="${PARENT.RIGHT}" yExpr="${PARENT.BOTTOM}" />
                <properties icon="MED_CONTENT_SETTINGS"/>
                </element>
                )"));

            buttonOpenSettingsScale->handlePressed([this]() {
                uiVizWidgetMenu* menu = dynamic_cast<uiVizWidgetMenu*>(scalePickerMenuItem->getPopoutWidgetForMenuTag(uiVizIconCache::IconTag::WIDGET_SETTINGS));
                menu->popoutFrom(buttonOpenSettingsScale, PopoutDirection::UP, false); 
            });            

            instrumentContextMenu = new uiVizWidgetMenu(menuId, "<widget><bounds width='100' height='300'/></widget>", getWidgetId(),
            uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {

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
                // uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
            }),

            // ----------------------------------------------------------------------------
            // Octave mode menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("OCTAVE"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_THEORY_OCTAVE_MODE, {
                uiVizWidgetMenuItem(uiVizShared::lang("NONE"), 0, false, true), uiVizWidgetMenuItem(uiVizShared::lang("SHOW_OCTAVE"), 1)
                //uiVizWidgetMenuItem("Scale", (int)TheoryVizColorMode::SCALES)
            }),

            // ----------------------------------------------------------------------------
            // Tunings menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("TUNINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_TUNINGS, getTuningsMenuItems()),

            // ----------------------------------------------------------------------------
            // Start Fret menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("START_FRET"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_START_FRET, getStartFretMenuItems()),

            // ----------------------------------------------------------------------------
            // End Fret menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("END_FRET"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_END_FRET, getEndFretMenuItems()),

            // ----------------------------------------------------------------------------
            // Strings menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("STRINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_STRINGS, getStringsMenuItems()),

            // ----------------------------------------------------------------------------
            // Chord view mode
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("CHORD_VIEW"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE, {uiVizWidgetMenuItem(uiVizShared::lang("REGULAR"), (int)TheoryVizInstrumentChordViewMode::UNSET), uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(3), 3), uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(4), 4), uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(5), 5), uiVizWidgetMenuItem(uiVizShared::lang("STRINGED_CHORD_DIAGRAM") + " " + ofToString(6), 6)}),

            // ----------------------------------------------------------------------------
            // Settings menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("SETTINGS"), uiVizIconCache::getIcon("MED_CONTENT_SETTINGS"), MENU_GROUP_1::MENU_TAB_SETTINGS, {uiVizWidgetMenuItem(uiVizShared::lang("SOUND"), 1, true, true), uiVizWidgetMenuItem(uiVizShared::lang("LEFT_HAND"), 2, true, false), uiVizWidgetMenuItem(uiVizShared::lang("FLIP_ORIENTATION"), 3, true, false), uiVizWidgetMenuItem(uiVizShared::lang("SWITCH_VIEW"), 4, true, false), uiVizWidgetMenuItem(uiVizShared::lang("EXPORT_PNG"), 5), uiVizWidgetMenuItem(uiVizShared::lang("EXPORT_XML"), 6)}),

            uiVizWidgetMenuTab(uiVizShared::lang("EVENT_LISTENER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_SETTINGS, getWidgetEventListenerConfig()), 
            uiVizWidgetMenuTab(uiVizShared::lang("EVENT_LISTENER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_SETTINGS, uiVizWidgetMusicalHelper::getWidgetEventListenerMusicalConfig(this)) // OR DO WE NEED ?? instrumentContextMenu

            // ----------------------------------------------------------------------------
            // Key Picker menu
            // ----------------------------------------------------------------------------
            // uiVizWidgetMenuTab(uiVizShared::lang("KEY_PICKER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_KEY_PICKER, keyPickerMenuItem)//,

            // ----------------------------------------------------------------------------
            // Chord Wheel menu
            // ----------------------------------------------------------------------------
            // uiVizWidgetMenuTab(uiVizShared::lang("CHORD_WHEEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_WHEEL, chordWheelMenuItem),

            // ----------------------------------------------------------------------------
            // Chord Designer menu
            // ----------------------------------------------------------------------------
            //uiVizWidgetMenuTab(uiVizShared::lang("CHORD_DESIGNER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER, chordDesignerMenuItem),

            // ----------------------------------------------------------------------------
            // Scale Designer menu
            // ----------------------------------------------------------------------------
            //uiVizWidgetMenuTab(uiVizShared::lang("SCALE_PICKER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_SCALE_PICKER, scalePickerMenuItem)

            });

            ofAddListener(dynamic_cast<uiVizWidgetMenu *>(instrumentContextMenu)->menuItemSelected, this, &uiVizWigetStringedInstrument::onMenuItemSelected);


            // Mini menu -------------------------------------------------

            instrumentContextMenuMini = new uiVizWidgetMenu(menuId+"_mini", "<widget><bounds width='100' height='300'/></widget>", getWidgetId(),
            uiVizWidgetMenu::PreferredPopoutDirection::DOWN, {

            // ----------------------------------------------------------------------------
            // Key Picker menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("KEY_PICKER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_KEY_PICKER, keyPickerMenuItem),

            // ----------------------------------------------------------------------------
            // Chord Designer menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("CHORD_DESIGNER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_DESIGNER, chordDesignerMenuItem),

            // ----------------------------------------------------------------------------
            // Scale Designer menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("SCALE_PICKER"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_SCALE_PICKER, scalePickerMenuItem),

            // ----------------------------------------------------------------------------
            // Chord Wheel menu
            // ----------------------------------------------------------------------------
            uiVizWidgetMenuTab(uiVizShared::lang("CHORD_WHEEL"), uiVizIconCache::getIcon("MED_CONTENT_THEORY_LABEL"), MENU_GROUP_1::MENU_TAB_CHORD_WHEEL, chordWheelMenuItem) 

            });

            ofAddListener(dynamic_cast<uiVizWidgetMenu *>(instrumentContextMenuMini)->menuItemSelected, this, &uiVizWigetStringedInstrument::onMenuItemSelected);


            uiVizWidget* chordMenu = chordDesignerMenuItem->getPopoutWidgetForMenuTag((int)uiVizIconCache::IconTag::WIDGET_SETTINGS);
            if (chordMenu) {
                chordMenu->setMaxHeight(100);
                chordMenu->setHeight(100);
                chordMenu->setIsAutoResizeToContentsHeight(false);                
            }

            instrumentContextMenu->setMaxHeight(100);
            instrumentContextMenu->setHeight(100);
            instrumentContextMenu->setIsAutoResizeToContentsHeight(false);
            uiVizWidgetManager::addWidget(*instrumentContextMenu, false, getWidgetId());
            uiVizWidgetManager::addWidget(*instrumentContextMenuMini, false, getWidgetId());

        }
    }

    void setStartFret(int val, bool storePriorVal, bool purgeOutOfRangePoints)
    {
        if (storePriorVal)
            mOriginalLowestStartingFret = val;

        // Chord digram validation
        if (getIsChordDiagramMode())
        {
            int highestEndingFret = getHighestEndingFret();
            if (val == 0)
            {
                if (highestEndingFret > getChordDiagramNumFrets())
                {
                    setEndFret(getChordDiagramNumFrets() + 1, true, true);
                    calculatePoints();
                    setNeedsUpdate(true);
                }
            }
            else
            {
                if (highestEndingFret > (val + getChordDiagramNumFrets() - 1))
                {
                    setEndFret(val + getChordDiagramNumFrets() - 1, true, true);
                    calculatePoints();
                    setNeedsUpdate(true);
                }
            }
        }

        for (int j = 0; j < mStrings.size(); j++)
        {
            mStrings[j].setStartFret(val);
            mStrings[j].highestNoteAdded = vizNote("C", -1, 0, vector<string>{""});
            mStrings[j].lowestNoteAdded = vizNote("C", -1, 0, vector<string>{""});
        }

        if (purgeOutOfRangePoints)
        {
            vector<uiVizWigetStringedInstrumentPoint> inBoundsPoints;
            for (int j = 0; j < mPoints.size(); j++)
            {
                if (mPoints[j].fret >= val)
                    inBoundsPoints.push_back(mPoints[j]);
            }
            addPoints(inBoundsPoints);
        }

        synchronizeMenuWithStartFretProperty();
        updateRules(getInstrumentRules(), false, false, "setStartFret");
    }

    void setEndFret(int val, bool storePriorVal, bool purgeOutOfRangePoints)
    {
        if (storePriorVal)
            mOriginalHighestEndingFret = val;

        // Chord digram validation
        if (getIsChordDiagramMode())
        {
            int lowestStartingFret = getLowestStartingFret();
            if (lowestStartingFret < (val - getChordDiagramNumFrets()))
            {
                setStartFret(val - getChordDiagramNumFrets(), true, true);
                calculatePoints();
                setNeedsUpdate(true);
            }
        }

        for (int j = 0; j < mStrings.size(); j++)
        {
            mStrings[j].setEndFret(val);
            mStrings[j].highestNoteAdded = vizNote("C", -1, 0, vector<string>{""});
            mStrings[j].lowestNoteAdded = vizNote("C", -1, 0, vector<string>{""});
        }

        if (purgeOutOfRangePoints)
        {
            vector<uiVizWigetStringedInstrumentPoint> inBoundsPoints;
            for (int j = 0; j < mPoints.size(); j++)
            {
                if (mPoints[j].fret <= val)
                    inBoundsPoints.push_back(mPoints[j]);
            }
            addPoints(inBoundsPoints);
        }

        synchronizeMenuWithEndFretProperty();
        updateRules(getInstrumentRules(), false, false, "setEndFret");
    }

    int getOriginalLowestStartingFret()
    {
        return mOriginalLowestStartingFret;
    }

    int getOriginalHighestEndingFret()
    {
        return mOriginalHighestEndingFret;
    }

    enum MENU_GROUP_1
    {
        MENU_TAB_THEORY_LABEL_MODE = 0,
        MENU_TAB_THEORY_COLOR_MODE = 1,
        MENU_TAB_THEORY_OCTAVE_MODE = 2,
        MENU_TAB_TUNINGS = 3,

        MENU_TAB_START_FRET = 4,
        MENU_TAB_END_FRET = 5,

        MENU_TAB_STRINGS = 6,
        MENU_TAB_CHORD_VIEW_MODE = 7,
        MENU_TAB_SETTINGS = 8,

        MENU_TAB_KEY_PICKER = 9,
        MENU_TAB_CHORD_WHEEL = 10,
        MENU_TAB_CHORD_DESIGNER = 11,
        MENU_TAB_SCALE_PICKER = 12

    };

    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override
    {
        uiVizWidgetMusical::onWidgetEventReceived(args);
        string event = args.getFullEventName();

        if (args.eventName == WIDGET_EVENT::CLICK && buttonUp && args.sender.getPersistentId() == buttonUp->getPersistentId())
        {
            setIsUserEditing(false);
            enableAllStrings();
            int lowestStartingFret = getLowestStartingFret();
            int highestEndingFret = getHighestEndingFret();
            if (lowestStartingFret <= 0)
                return;
            setStartFret(lowestStartingFret - 1, true, true);
            setEndFret(highestEndingFret - 1, true, true);
            //setInstrumentRule("general", "startingInversion", -1);
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
        }
        else if (args.eventName == WIDGET_EVENT::CLICK && buttonDown && args.sender.getPersistentId() == buttonDown->getPersistentId())
        {
            setIsUserEditing(false);
            enableAllStrings();
            int lowestStartingFret = getLowestStartingFret();
            int highestEndingFret = getHighestEndingFret();
            setStartFret(lowestStartingFret + 1, true, true);
            setEndFret(highestEndingFret + 1, true, true);
            //setInstrumentRule("general", "startingInversion", -1);
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
        }
        else if (args.eventName == WIDGET_EVENT::CLICK && buttonPlay && args.sender.getPersistentId() == buttonPlay->getPersistentId())
        {
            // Todo - handle scales, etc
            if (getSelectedChordsSize() > 0) {
                auditionChord(getSelectedChords()[0]);
                clearAuditioning();
            }
            
        }        

        
    }

    int getToolbarWidth()
    {
        return mTOOLBAR_WIDTH;
    }

    void setChordDiagramNumFrets(int val)
    {
        bool valChanged = (mChordDiagramNumFrets = val);
        mChordDiagramNumFrets = val;

        if (valChanged && getSelectedChordsSize() > 0) {
            enableAllStrings();
        }

        if (val >= 24)
        {
            deleteInstrumentRule("stringed", "chordDiagramNumFrets");
            setIsChordDiagramMode(false);
        }
        else
        {
            setInstrumentRule("stringed", "chordDiagramNumFrets", val);
            setIsChordDiagramMode(true);
        }

        if (valChanged && getSelectedChordsSize() > 0) {
            calculatePoints();  //gotta set drag data here! sometimes it's not a valid chord (when reducing the num strings) sort it!
         }
    }

    int getChordDiagramNumFrets()
    {
        return mChordDiagramNumFrets;
    }


    void setNumStrings(int val)
    {
        mNumStrings = val;

        setStrings(getTunings()[0], true);

        setNeedsUpdate(true);
        setWidgetNeedsUpdate(true);

    }

    int getNumStrings()
    {
        return mNumStrings;
    }    

private:

    uiVizWidgetNotesTable* getNoteTable() {
        return NOTES_TABLE;
    }

    uiVizWidget *instrumentContextMenu = nullptr;
    uiVizWidget *instrumentContextMenuMini = nullptr;
    
    uiVizWidgetKeyPicker *keyPickerMenuItem = nullptr;
    uiVizWidgetChordWheel *chordWheelMenuItem = nullptr;
    uiVizWidgetChordDesigner *chordDesignerMenuItem = nullptr;
    uiVizWidgetScalePicker *scalePickerMenuItem = nullptr;

    uiVizElm fretboard;
    uiVizElm nut;

    ofColor mFretboardColor = ofColor(138, 51, 36, 200); // https://en.wikipedia.org/wiki/Shades_of_brown
    ofColor mNutColor = ofColor(255, 255, 255, 180);
    ofColor mFretColor = ofColor(255, 255, 255, 160);
    ofColor mFretboardInlayColor = ofColor(255, 255, 255, 180);
    ofColor mFretboardLabelColor = ofColor(0, 0, 0, 255);
    ofColor mFretboardPointStrokeColor = ofColor(255, 255, 255, 255);
    uiVizWidgetDialog* GUIT_DIALOG = nullptr;   
    uiVizWidgetNotesTable* NOTES_TABLE = nullptr;  
    uiVizWidgetMusical* chordBucket = nullptr;  

    bool isInitial = true;
    float mSize = 600.0f;
    float mSIZE_NORMALIZED = 600.0f;
    float mFRET_SIZE = 5.0f;
    float mPOINT_SIZE = 18.0f;
    float mINLAY_SIZE = 5.0f;

    int mStartFret = 0;
    int mEndFret = 3;
    int mOriginalLowestStartingFret = 0;
    int mOriginalHighestEndingFret = 3;
    int mTotalFrets = 24;
    int DEFAULT_FRETS = 24;    
    bool mIsFixedFretWidth = false;
    bool mIsChordDiagramMode = false;
    int mChordDiagramNumFrets = 5;
    int mNumStrings = 6;
    bool mDrawPointsOnFrets = false;
    bool mUseFullNeck = true;

    float mFRET_WIDTH_TO_HEIGHT_RATIO = 4.1f;
    int mTOOLBAR_WIDTH = 37;
    uiVizWidgetElmTextbox *userDefinedChordName = nullptr;
    uiVizWidgetElmButton *buttonDown = nullptr;
    uiVizWidgetElmButton *buttonUp = nullptr;
    uiVizWidgetElmButton *buttonChordSettings = nullptr;

    uiVizWidgetElmButton *buttonPlay = nullptr;    
    uiVizWidgetElmButton *buttonOpenVariations = nullptr;   
    uiVizWidgetElmButton *buttonOpenSettings = nullptr;   
    uiVizWidgetElmButton *buttonOpenSettingsScale = nullptr;   
    
     
    int mSequencedNoteNumber = 1;
    

    // https://en.wikipedia.org/wiki/Guitar
    float FRET_RATIO = 1.059463f; // ie L0 = 25.500, L1 25.069, L2 = 22.718

    vector<uiVizWigetStringedInstrumentString> mStrings = {};
    vector<uiVizWigetStringedInstrumentPoint> mPoints = {};
    vector<uiVizWigetStringedInstrumentFret> mFrets{};

    shared_ptr<ofxSmartFont> font = getFontSizedForDimensions(getUsableWidth(), getUsableHeight());
    shared_ptr<ofxSmartFont> fontSmall = getMediumFontSizedForDimensions(getUsableWidth(), getUsableHeight());
    shared_ptr<ofxSmartFont> fontLarge = getLargeFontSizedForDimensions(std::min(240, getUsableWidth()), getUsableHeight());

    ofRectangle pointSmallLabelRectSingle;

    void onMenuItemSelected(uiVizWidgetMenuItemArgs &args)
    {

        switch (args.activeMenuTabId)
        {
        case MENU_GROUP_1::MENU_TAB_THEORY_LABEL_MODE:
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

        case MENU_GROUP_1::MENU_TAB_THEORY_OCTAVE_MODE:
            setShowOctaveInLabel(!getShowOctaveInLabel());
            setNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_TUNINGS:
        {

            int currStartFret = mStrings[0].getStartFret();
            int currEndFret = mStrings[0].getEndFret();


            if (args.menuItem->uniqueID == -1) {

                    GUIT_DIALOG->showDialog(
                        "Custom Tuning",
                        "", 
                        true,
                        "Ok", 
                        "BTN_OK",
                        false,
                        [&, this](uiVizWidgetEventArgs args) {
                            if (args.widgetId == "BTN_OK") {

                                vector<uiVizWigetStringedInstrumentString> defaultTuning = this->getTunings()[0]; // Use this for string widths...


                                vector<uiVizWigetStringedInstrumentString> customTuning;
                                vector<int> stringThickness;

                                if (defaultTuning.size() == 8) {
                                    stringThickness = {6, 6, 5, 4, 3, 3, 2, 2};
                                } else if (defaultTuning.size() == 7) {
                                    stringThickness = {   6, 5, 4, 3, 3, 2, 2};
                                } else if (defaultTuning.size() == 6) {
                                    stringThickness = {      5, 4, 3, 3, 2, 2};
                                } else if (defaultTuning.size() == 5) {
                                    stringThickness = {         4, 3, 3, 2, 2};                              
                                } else {
                                    stringThickness = {         4, 3, 3, 2   };                                
                                }

                                for(int i=0; i<defaultTuning.size(); i++) {
                                    string buttonId = "STRING_" + ofToString(i);
                                    string noteName = GUIT_DIALOG->getButton(buttonId)->getTitle();
                                    vizNote n = vizNote::noteFromString(noteName);
                                    if (i == 0) n.setNoteTags({"CUSTOM:"});
                                    customTuning.push_back(uiVizWigetStringedInstrumentString(n, stringThickness[i]));
                                }

                                setStrings(customTuning, true);
                                calculatePoints();
                                setNeedsUpdate(true);
                                setWidgetNeedsUpdate(true);
                            }

                        }          
                    );         

                    vector<uiVizWigetStringedInstrumentString> defaultTuning = getStrings();
                    string lastId = "";

                    for(int i=0; i<defaultTuning.size(); i++) {
                        string buttonTitle = defaultTuning[i].note.getNoteName() + ofToString(defaultTuning[i].note.getNoteOctave());
                        string buttonId = "STRING_" + ofToString(i);

                        uiVizWidgetElmButton *b = dynamic_cast<uiVizWidgetElmButton*>(GUIT_DIALOG->addOrLoadWidgetElement(nullptr, WIDGET_ELM_CLASS::BUTTON, buttonId, R"(
                            <element>
                            </element>
                            )"));
                            
                        lastId == "" ? b->setX_Expr("${PARENT.LEFT}") : b->setX_Expr("${"+lastId+".X}+${SELF.WIDTH}+${PADDING}");
                        b->setY_Expr("${PARENT.TOP}+${PADDING}");
                        b->setHeight_Expr("60");
                        b->setWidth_Expr("${PARENT.WIDTH}/"+ofToString(defaultTuning.size())+"-${PADDING}-${PADDING}/"+ofToString(defaultTuning.size()));
                        b->setTitle(buttonTitle);
                        b->setPopoutWidget(NOTES_TABLE, PopoutDirection::DOWN);
                        b->setMetadata("STRING_NUM", i);
                        lastId = ofToUpper(buttonId);

                        b->setPopoutWidgetShownCallback([&, b]() {
                            vizNote note = vizNote::noteFromString(b->getTitle());
                            this->getNoteTable()->setSelectedNote(note, true, true);
                        });

                        b->setPopoutWidgetClosedCallback([&](uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, const string s) {
                            uiVizWidgetNotesTable *notesTable = static_cast<uiVizWidgetNotesTable *>(closedWidget);
                            uiVizWidgetElmButton *button = static_cast<uiVizWidgetElmButton *>(sender);

                            vector<uiVizWigetStringedInstrumentString> currentStrings = getStrings();                            
                            if (notesTable->getSelectedNotes().size() > 0) {
                                vizNote note = notesTable->getSelectedNotes()[0];
                                button->setTitle(note.getNoteName()+ofToString(note.getNoteOctave()));
                                currentStrings[button->getMetadataInt("STRING_NUM")].note = note;
                                currentStrings[0].note.setNoteTags({"CUSTOM:"});
                                setStrings(currentStrings, true);
                            }
                        });                        
                        
                    }                               


            } else {
                setStrings(getTunings()[args.menuItem->uniqueID], true);
            }            

            // if (getIsUserEditing())
            // {
            //     clearPoints();
            //     clearSelectedNotes();
            //     clearSelectedChords();
            // }

            // setStartFret(currStartFret, true, false);
            // setEndFret(currEndFret, true, false);

            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
        }
        break;

        case MENU_GROUP_1::MENU_TAB_START_FRET:
            setStartFret(args.menuItem->uniqueID, true, true);
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_END_FRET:
            setEndFret(args.menuItem->uniqueID, true, true);
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_STRINGS:
            mStrings[args.menuItem->uniqueID].isEnabled = args.menuItem->isSelected;
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
            break;

        case MENU_GROUP_1::MENU_TAB_CHORD_VIEW_MODE:
            if ((TheoryVizInstrumentChordViewMode)args.menuItem->uniqueID == TheoryVizInstrumentChordViewMode::UNSET) {
                setChordDiagramNumFrets(DEFAULT_FRETS);
            } else {
                setChordDiagramNumFrets(args.menuItem->uniqueID);
            }        
            
            updateRules(getInstrumentRules(), false, false, "MENU_TAB_CHORD_VIEW_MODE");
            calculatePoints();
            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);

            break;

        case MENU_GROUP_1::MENU_TAB_SETTINGS:

            if (args.menuItem->uniqueID == 2)
            {
                performOperationForKeyPress(VIZ_KEY_NUMBER_4); // SWITCH_LEFTY
            }
            else if (args.menuItem->uniqueID == 3)
            {
                performOperationForKeyPress(VIZ_KEY_NUMBER_3); // FLIP_ORIENTATION
            }
            else if (args.menuItem->uniqueID == 4)
            {
                performOperationForKeyPress(VIZ_KEY_NUMBER_5); // SWITCH_VIEW
            }
            else if (args.menuItem->uniqueID == 5)
            {
                // SAVE AS PNG ...

                uiVizWidgetManager::showSaveDialog("", vizTheory::extractFileSystemSafeName(getTitle() + ".png"),
                                                   [&](string filePath)
                                                   {
                                                       this->saveWidgetContentsToImageFile(filePath, uiVizWidgetContext::SCREEN);
                                                   });
            }
            else if (args.menuItem->uniqueID == 6)
            {
                // SAVE AS XML ...
                uiVizWidgetManager::showSaveDialog("", vizTheory::extractFileSystemSafeName(getTitle() + ".xml"),
                                                   [&](string filePath)
                                                   {
                                                       this->saveWidgetXMLToFile(filePath);
                                                   });
            }

            setNeedsUpdate(true);
            setWidgetNeedsUpdate(true);
            break;
        }
    }

    void setButtonsVisibility(bool val)
    {
        if (buttonDown && buttonUp)
        {
            bool origVal = buttonDown->getIsVisible();
            buttonDown->setIsVisible(val);
            buttonUp->setIsVisible(val);
            buttonPlay->setIsVisible(val);

            if (instrumentContextMenu) {
                buttonChordSettings->setIsVisible(val);
            }

            if (origVal != val) {
                setWidgetNeedsUpdate(true);
            }
            
        }
    }

    void onWidgetUnhovered(uiVizWidgetEventArgs &args) override
    {
        setButtonsVisibility(false);
    }

    void onWidgetHovered(uiVizWidgetEventArgs &args) override
    {
        if (getIsChordDiagramMode() && getTheoryVizOrientationMode() == TheoryVizOrientationMode::VERTICAL)
        {
            setButtonsVisibility(true);
        }
    }

    void initWidget() override
    {
        //setIsBlackAndWhiteMode(true);
        setIsAutoUpdateWhenActive(false);
        setTitleStyle(uiVizWidget::TitleStyle::TOP_OVERLAY);

        setTheoryVizInstrumentDrawMode(TheoryVizInstrumentDrawMode::RIGHT); // DEFAULT TO RIGHT HANDED
        setTheoryVizOrientationMode(TheoryVizOrientationMode::HORIZONTAL);  // DEFAULT TO HORIZONTAL

        setBoundsForOrientation(TheoryVizOrientationMode::HORIZONTAL);

        buttonDown = dynamic_cast<uiVizWidgetElmButton *>(addOrLoadWidgetElement(buttonDown, WIDGET_ELM_CLASS::BUTTON, "ARROW_DOWN", R"(
            <element>
            <bounds width="27" height="27" />
            <properties icon="MED_CONTENT_ARROW_DOWN"/>
            </element>
            )"));
        buttonDown->setIsVisible(false);

        buttonDown->setX_Expr("${PARENT.LEFT} - " + ofToString(mTOOLBAR_WIDTH));
        buttonDown->setY_Expr("${PARENT.BOTTOM}");
        buttonDown->setShouldPersist(false);

        buttonUp = dynamic_cast<uiVizWidgetElmButton *>(addOrLoadWidgetElement(buttonUp, WIDGET_ELM_CLASS::BUTTON, "ARROW_UP", R"(
            <element>
            <bounds width="27" height="27" />
            <properties icon="MED_CONTENT_ARROW_UP"/>
            </element>
            )"));
        buttonUp->setIsVisible(false);

        buttonUp->setX_Expr("${PARENT.LEFT} - " + ofToString(mTOOLBAR_WIDTH));
        buttonUp->setY_Expr("${PARENT.BOTTOM}-${PADDING}-27");
        buttonUp->setShouldPersist(false);


        buttonPlay = dynamic_cast<uiVizWidgetElmButton *>(addOrLoadWidgetElement(buttonPlay, WIDGET_ELM_CLASS::BUTTON, "BUTTON_PLAY", R"(
            <element>
            <bounds width="27" height="27" />
            <properties icon="MED_PLAY_BUTTON"/>
            </element>
            )"));
        buttonPlay->setIsVisible(false);

        buttonPlay->setX_Expr("${PARENT.LEFT} - " + ofToString(mTOOLBAR_WIDTH));
        buttonPlay->setY_Expr("${PARENT.BOTTOM}-${PADDING}*2-(27*2)");
        buttonPlay->setShouldPersist(false);



        buttonChordSettings = dynamic_cast<uiVizWidgetElmButton *>(addOrLoadWidgetElement(buttonChordSettings, WIDGET_ELM_CLASS::BUTTON, "ARROW_SETTINGS", R"(
            <element>
            <bounds width="27" height="27" xExpr="${PARENT.RIGHT}" yExpr="${PARENT.BOTTOM}" />
            <properties icon="MED_CONTENT_SETTINGS"/>
            </element>
            )"));
        buttonChordSettings->setIsVisible(false);

        buttonChordSettings->setX_Expr("${PARENT.LEFT} - " + ofToString(mTOOLBAR_WIDTH));
        buttonChordSettings->setY_Expr("${PARENT.BOTTOM}-${PADDING}*3-(27*3)");
        buttonChordSettings->setShouldPersist(false);            

        buttonChordSettings->handlePressed([this]() {
            uiVizWidgetMenu *menuMini = static_cast<uiVizWidgetMenu *>(instrumentContextMenuMini);
            if(menuMini) {
                showContextMenu(uiVizIconCache::IconTag::WIDGET_SETTINGS_MINI, deScale(ofGetMouseX()) - 20, deScale(ofGetMouseY()) - 20);
            }
        });


        if (isInitial)
        {
            isInitial = false;
            setInstrumentRule("stringed", "notesPerString", 1);
            setInstrumentRule("general", "searchForExactChordMatch", true);          // performance penalty!
            setInstrumentRule("general", "searchForExactChordMatchDirection", "up"); // up | down

            setStartFret(0, true, true);
            setEndFret(3, true, true);
            setSelectedKey(vizNote("C", 3, 3));
        }
    }

//     implement b and w
// Triads
// Tab
// 3 notes 
// chord bucket (key - transpose, show cord degrees)
// fix sharp / flat 

};
