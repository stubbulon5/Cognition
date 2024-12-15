//
//  uiVizWidgetMusical.h
//  bloom-macos
//
//
#pragma once
// UI stuff
#include "../uiViz/widget/uiVizWidget.h"
#include "../uiViz/widget/uiVizWidgetMenu.h"
#include "../uiViz/widget/system/uiVizWidgetDialog.h"
#include "../uiViz/widget/uiVizWidgetEventListener.h"

#include "uiVizTheory.h"
#include "appConstants.h"

// Sound stuff
#include "sdMidiShared.h"


//------------------------------ EVENT ARGS  (Rules) --------------------------------
class uiVizInstrumentRuleArgs : public ofEventArgs {
public:
    uiVizInstrumentRuleArgs(ofxXmlSettings rules) : rules(rules) {}
    ofxXmlSettings rules;
    string getXMLString() {
        string retVal = "";
        TiXmlPrinter printer;
        TiXmlElement* rootElm = rules.doc.RootElement();
        if (rootElm != NULL) {
            rootElm->Accept( &printer );
            retVal = printer.CStr();    
        }
        return retVal;    
    }
};

//------------------------------ EVENT ARGS (move this to uiVizWidgetBaseMusic ) --------------------------------

class uiVizTextChangedArgs : public ofEventArgs {
public:
    uiVizTextChangedArgs(string widgetId, string text)
    :widgetId(widgetId)
    ,text(text){}
    
    string widgetId;
    string text;
};

class uiVizNoteSelectedArgs : public ofEventArgs {
public:
    uiVizNoteSelectedArgs(string widgetId, vizNote note)
    :widgetId(widgetId)
    ,note(note){}
    
    string widgetId;
    vizNote note;
};

class uiVizChordSelectedArgs : public ofEventArgs {
public:
    uiVizChordSelectedArgs(string widgetId, vizChord chord)
    :widgetId(widgetId)
    ,chord(chord){}
    
    string widgetId;
    vizChord chord;
};

class uiVizWidgetMusical :  public uiVizWidget {
    
public:
    
    // Events
    ofEvent<uiVizInstrumentRuleArgs>    rulesChanged;    
    ofEvent<uiVizNoteSelectedArgs>      keySelected;
    ofEvent<uiVizNoteSelectedArgs>      noteSelected;
    ofEvent<uiVizChordSelectedArgs>     chordSelected;
    ofEvent<uiVizTextChangedArgs>       userDefinedChordNameChanged;
    
    enum class TheoryMode {
        KEY_CENTRIC,    // One distinct color for each DEGREE
        DEGREE_CENTRIC  // One distinct color for each KEY     (degrees are portrayed in BRIGHTNESS)
    };
    
    enum class TheoryVizColorMode {
        NONE,
        KEYS,
        DEGREES,
        SCALES
    };
    
    enum class TheoryVizColorAlternateMode {
        NONE,
        ALTERNATE_KEYS_DEGREES
    };
    
    enum class TheoryVizLabelMode {
        NONE,
        KEYS,
        DEGREES,
        // KEYS_AND_DEGREES, have a toggle somewhere which when enabled shows the inverse of the selected somewhere else (ie if Keys selected, show Kegrees and visa versa)
        SCALES
    };
    
    enum class TheoryVizNoteMode {
        DEFAULT,
        SHARP,
        FLAT
    };

    enum class TheoryVizLabelAlternateMode {
        NONE,
        ALTERNATE_KEYS_DEGREES
    };
    
    enum class TheoryVizShapeMode {
        MINIMAL,
        CIRCLE,
        TABLE,
        DOTS,
        SQUARES
    };
    
    enum class TheoryVizOrientationMode {
        VERTICAL,
        HORIZONTAL,
        UNSET
    };
    
    string getTheoryVizOrientationModeString(TheoryVizOrientationMode val) {
        switch(val) {
            case TheoryVizOrientationMode::VERTICAL: return "VERTICAL";
            case TheoryVizOrientationMode::HORIZONTAL: return "HORIZONTAL";
            default: return "UNSET";
        }
    };
    
    TheoryVizOrientationMode getTheoryVizOrientationModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "VERTICAL") return TheoryVizOrientationMode::VERTICAL;
        if (val == "HORIZONTAL") return TheoryVizOrientationMode::HORIZONTAL;
        return TheoryVizOrientationMode::UNSET;
    };
    
    enum class TheoryVizInstrumentDrawMode {
        LEFT,
        RIGHT,
        UNSET
    };
    
    string getTheoryVizInstrumentDrawModeString(TheoryVizInstrumentDrawMode val) {
        switch(val) {
            case TheoryVizInstrumentDrawMode::LEFT: return "LEFT";
            case TheoryVizInstrumentDrawMode::RIGHT: return "RIGHT";
            default: return "UNSET";
        }
    };
    
    TheoryVizInstrumentDrawMode getTheoryVizInstrumentDrawModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "LEFT") return TheoryVizInstrumentDrawMode::LEFT;
        if (val == "RIGHT") return TheoryVizInstrumentDrawMode::RIGHT;
        return TheoryVizInstrumentDrawMode::UNSET;
    };
    
    enum class TheoryVizInstrumentTheoryContentMode {
        NOTE,
        CHORD,
        SCALE,
        UNSET
    };
    
    string getTheoryVizInstrumentTheoryContentModeString(TheoryVizInstrumentTheoryContentMode val) {
        switch(val) {
            case TheoryVizInstrumentTheoryContentMode::NOTE: return "NOTE";
            case TheoryVizInstrumentTheoryContentMode::CHORD: return "CHORD";
            case TheoryVizInstrumentTheoryContentMode::SCALE: return "SCALE";
            default: return "UNSET";
        }
    };
    
    TheoryVizInstrumentTheoryContentMode getTheoryVizInstrumentTheoryContentModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "NOTE") return TheoryVizInstrumentTheoryContentMode::NOTE;
        if (val == "CHORD") return TheoryVizInstrumentTheoryContentMode::CHORD;
        if (val == "SCALE") return TheoryVizInstrumentTheoryContentMode::SCALE;
        return TheoryVizInstrumentTheoryContentMode::UNSET;
    };

    enum class TheoryVizInstrumentChordViewMode {
        UNSET,
        STRINGED_CHORD_DIAGRAM
    };
    
    string getTheoryVizInstrumentChordViewModeString(TheoryVizInstrumentChordViewMode val) {
        switch(val) {
            case TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM: return "STRINGED_CHORD_DIAGRAM";
            default: return "UNSET";
        }
    };
    
    TheoryVizInstrumentChordViewMode getTheoryVizInstrumentChordViewModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "STRINGED_CHORD_DIAGRAM") return TheoryVizInstrumentChordViewMode::STRINGED_CHORD_DIAGRAM;
        return TheoryVizInstrumentChordViewMode::UNSET;
    };    

    virtual vector<TheoryVizShapeMode> getMusicalWidgetAvailableShapeModes() {
        // For the menu popout to call...
        return  vector<TheoryVizShapeMode>();
    }
 
    uiVizWidgetMusical(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        init();
        loadState(widgetXML);
    }
    
    string getTheoryVizColorModeString(TheoryVizColorMode val) {
        switch(val) {
            case TheoryVizColorMode::NONE: return "NONE";
            case TheoryVizColorMode::KEYS: return "KEYS";
            case TheoryVizColorMode::DEGREES: return "DEGREES";
            case TheoryVizColorMode::SCALES: return "SCALES";
            default: return "KEYS";
        }
    };
    
    TheoryVizColorMode getTheoryVizColorModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "NONE") return TheoryVizColorMode::NONE;
        if (val == "KEYS") return TheoryVizColorMode::KEYS;
        if (val == "DEGREES") return TheoryVizColorMode::DEGREES;
        if (val == "SCALES") return TheoryVizColorMode::SCALES;
        return TheoryVizColorMode::NONE;
    };

    string getTheoryVizColorAlternateModeString(TheoryVizColorAlternateMode val) {
        switch(val) {
            case TheoryVizColorAlternateMode::NONE: return "NONE";
            case TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES: return "ALTERNATE_KEYS_DEGREES";
            default: return "NONE";
        }
    };
    
    TheoryVizColorAlternateMode getTheoryVizColorAlternateModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "NONE") return TheoryVizColorAlternateMode::NONE;
        if (val == "ALTERNATE_KEYS_DEGREES") return TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES;
        return TheoryVizColorAlternateMode::NONE;
    };

    string getTheoryVizLabelModeString(TheoryVizLabelMode val) {
        switch(val) {
            case TheoryVizLabelMode::NONE: return "NONE";
            case TheoryVizLabelMode::KEYS: return "KEYS";
            case TheoryVizLabelMode::DEGREES: return "DEGREES";
            case TheoryVizLabelMode::SCALES: return "SCALES";
            default: return "KEYS";
        }
    };
    
    TheoryVizLabelMode getTheoryVizLabelModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "NONE") return TheoryVizLabelMode::NONE;
        if (val == "KEYS") return TheoryVizLabelMode::KEYS;
        if (val == "DEGREES") return TheoryVizLabelMode::DEGREES;
        if (val == "SCALES") return TheoryVizLabelMode::SCALES;
        return TheoryVizLabelMode::NONE;
    };
 
    string getTheoryVizNoteModeString(TheoryVizNoteMode val) {
        switch(val) {
            case TheoryVizNoteMode::DEFAULT: return "DEFAULT";
            case TheoryVizNoteMode::SHARP: return "SHARP";
            case TheoryVizNoteMode::FLAT: return "FLAT";
            default: return "DEFAULT";
        }
    };
    
    TheoryVizNoteMode getTheoryVizNoteModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "DEFAULT") return TheoryVizNoteMode::DEFAULT;
        if (val == "SHARP") return TheoryVizNoteMode::SHARP;
        if (val == "FLAT") return TheoryVizNoteMode::FLAT;
        return TheoryVizNoteMode::DEFAULT;
    };

    string getTheoryVizLabelAlternateModeString(TheoryVizLabelAlternateMode val) {
        switch(val) {
            case TheoryVizLabelAlternateMode::NONE: return "NONE";
            case TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES: return "ALTERNATE_KEYS_DEGREES";
            default: return "NONE";
        }
    };
    
    TheoryVizLabelAlternateMode getTheoryVizLabelAlternateModeEnum(string val) {
        val = ofToUpper(val);
        if (val == "NONE") return TheoryVizLabelAlternateMode::NONE;
        if (val == "ALTERNATE_KEYS_DEGREES") return TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES;
        return TheoryVizLabelAlternateMode::NONE;
    };


    uiVizWidgetElmBreadcrumb* getWidgetBreadCrumbBar() {
        if (mWidgetElmBreadcrumb == nullptr && getBreadcrumbItemItems().size() > 0) {
            mWidgetElmBreadcrumb = dynamic_cast<uiVizWidgetElmBreadcrumb*>(addOrLoadWidgetElement(mWidgetElmBreadcrumb, WIDGET_ELM_CLASS::BREADCRUMB, "_widgetBreadcrumb", R"(
                <element id="___TOP_BREADCRUMB" class="uiVizWidgetElmBreadcrumb" shouldPersist="0">
                <bounds xExpr="${PARENT.LEFT}" yExpr="${PARENT.TOP_FIXED}" widthExpr="${PARENT.USABLE_WIDTH}" />
                </element>
            )"));

            mWidgetElmBreadcrumb->setBreadcrumbItemItems(getBreadcrumbItemItems());
        }
        return mWidgetElmBreadcrumb;
    };

    void setBreadcrumbItemItems(vector<uiVizWidgetElmBreadcrumbItem> items) {
        mBreadcrumbItemItems = items;
        getWidgetBreadCrumbBar()->setBreadcrumbItemItems(items);
    }

    void setBreadcrumbItemItemsVisibility(bool visible) {
        uiVizWidgetElmBreadcrumb* bar = getWidgetBreadCrumbBar();
        if(bar) {
            bar->setIsVisible(visible);
        }
    }    

    vector<uiVizWidgetElmBreadcrumbItem> getBreadcrumbItemItems() {
        return mBreadcrumbItemItems;
    }   

    uiVizWidgetEventListener* getWidgetEventListenerConfig() {
        if (mWidgetEventListenerConfig == nullptr) {
            mWidgetEventListenerConfig = new uiVizWidgetEventListener(
                getWidgetId() + "_EVENT_LISTENER_CONFIG",
                "<widget ownerWidgetId='" + getWidgetId() + "'><bounds minWidth='500' minHeight='200' width='500'/><appearance /></widget>"
                );

            mWidgetEventListenerConfig->setOwnerWidgetId(getWidgetId());
        }
        return mWidgetEventListenerConfig;
    };   
      

    int getUsableHeight() override {
        uiVizWidgetElmBreadcrumb* bar = getWidgetBreadCrumbBar();
        if(bar && bar->getIsVisible() && !getIsMinimized()) {
            return uiVizWidget::getUsableHeight() - bar->getHeight() - getScaledPadding();
        } else {
            return uiVizWidget::getUsableHeight();
        }
    }

    int getUsableY() override {
        uiVizWidgetElmBreadcrumb* bar = getWidgetBreadCrumbBar();
        if(bar && bar->getIsVisible() && !getIsMinimized()) {
            return uiVizWidget::getUsableY() + bar->getHeight() + getScaledPadding();
        } else {
            return uiVizWidget::getUsableY();
        }
    }    

     
    virtual bool loadState(string widgetXML) override {
        uiVizWidget::loadState(widgetXML);
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        settings.pushTag("widget");

        setUserCanInvokeContextMenu(settings.getAttribute("properties", "userCanInvokeContextMenu",  getUserCanInvokeContextMenu(), 0));

        settings.pushTag("properties");
        
        // Visualization Modes

        setTheoryVizInstrumentDrawMode(getTheoryVizInstrumentDrawModeEnum(settings.getAttribute("musicData", "drawMode", getTheoryVizInstrumentDrawModeString(getTheoryVizInstrumentDrawMode()), 0)));


        TheoryVizInstrumentTheoryContentMode instrumentContentMode = getTheoryVizInstrumentTheoryContentModeEnum(settings.getAttribute("musicData", "instrumentContentMode", getTheoryVizInstrumentTheoryContentModeString(getTheoryVizInstrumentTheoryContentMode()), 0));
        setTheoryVizInstrumentTheoryContentMode(instrumentContentMode);

        TheoryVizInstrumentChordViewMode chordViewMode = getTheoryVizInstrumentChordViewModeEnum(settings.getAttribute("musicData", "chordViewMode", getTheoryVizInstrumentChordViewModeString(getTheoryVizInstrumentChordViewMode()), 0));
        setTheoryVizInstrumentChordViewMode(chordViewMode);        

        setTheoryVizOrientationMode(getTheoryVizOrientationModeEnum(settings.getAttribute("musicData", "orientation", getTheoryVizOrientationModeString(getTheoryVizOrientationMode()), 0)));
        
        setTheoryVizColorMode(getTheoryVizColorModeEnum(settings.getAttribute("musicData", "colorMode", getTheoryVizColorModeString(getTheoryVizColorMode()), 0)));
        
        setTheoryVizColorAlternateMode(getTheoryVizColorAlternateModeEnum(settings.getAttribute("musicData", "colorAlternateMode", getTheoryVizColorAlternateModeString(getTheoryVizColorAlternateMode()), 0)));

        setTheoryVizLabelMode(getTheoryVizLabelModeEnum(settings.getAttribute("musicData", "labelMode", getTheoryVizLabelModeString(getTheoryVizLabelMode()), 0)));

        setTheoryVizLabelAlternateMode(getTheoryVizLabelAlternateModeEnum(settings.getAttribute("musicData", "labelAlternateMode", getTheoryVizLabelAlternateModeString(getTheoryVizLabelAlternateMode()), 0)));
        
        setTheoryVizNoteMode(getTheoryVizNoteModeEnum(settings.getAttribute("musicData", "noteMode", getTheoryVizNoteModeString(getTheoryVizNoteMode()), 0)));
        
        
        setShowOctaveInLabel(settings.getAttribute("musicData", "labelShowOctave", getShowOctaveInLabel()));


        setGMInstrumentNumber(settings.getAttribute("musicData", "generalMidiInstrumentNumber", getGMInstrumentNumber()));

        setUserDefinedChordName(settings.getAttribute("musicData", "userDefinedChordName", getUserDefinedChordName()));

        setIsLefty(settings.getAttribute("musicData", "isLefty", isLefty()));
        setIsBlackAndWhiteMode(settings.getAttribute("musicData", "isBlackAndWhiteMode", isBlackAndWhiteMode()));

        settings.pushTag("musicData");
        
       
        // Selected Key
        string selectedKeyName = settings.getAttribute("selectedKey", "name", getSelectedKey().getNoteName(), 0);
        if (selectedKeyName != "") {
            setSelectedKey(vizNote("<note name='" + selectedKeyName + "' octave='3' />"));
        }

        // Selected Scale
        string scaleName = "";
        if (settings.pushTag("selectedScale")) {
            scaleName = settings.getValue("name", "", 0);
            string scaleKey = settings.getValue("key", "", 0);
            if (scaleName != "") {
                if(scaleKey != "") {
                    vizScale scale = vizScale(scaleKey, scaleName);
                    setSelectedScale(scale, true);
                } else {
                    vizScale scale = vizScale(scaleName);
                    setSelectedScale(scale, true);
                }
            }
            settings.popTag();
        }


        settings.popTag(); // musicData

        /**** Music data collections ****/
        TiXmlElement* rootElm = settings.doc.RootElement();
        TiXmlElement* propertiesElm = rootElm->FirstChildElement("properties");
        
        if (propertiesElm != NULL) {
            TiXmlElement* musicDataElm = propertiesElm->FirstChildElement("musicData");
            if (musicDataElm != NULL) {

                loadRules(musicDataElm);

                loadNotes(musicDataElm);

                switch(instrumentContentMode) {
                    case TheoryVizInstrumentTheoryContentMode::NOTE: {
                        break;
                    }

                    case TheoryVizInstrumentTheoryContentMode::CHORD: {
                        loadScale(musicDataElm);
                        loadChords(musicDataElm);
                        break;
                    }

                    case TheoryVizInstrumentTheoryContentMode::SCALE: {
                        loadChords(musicDataElm);
                        loadScale(musicDataElm);                        
                        break;
                    }

                    default: {
                        loadScale(musicDataElm);
                        loadChords(musicDataElm);                        
                    }        
                }

            }
        }

        settings.popTag(); // properties
        
        settings.popTag(); // widget

        return true;
    }

    void loadRules(TiXmlElement* musicDataElm) {
        if (musicDataElm == NULL) return;
        TiXmlElement* rulesElm = musicDataElm->FirstChildElement("rules");
        if (rulesElm != NULL) {
            TiXmlPrinter printer;
            rulesElm->Accept( &printer );
            string rulesXML = printer.CStr();
            setInstrumentRules(rulesXML, true);
        }        
    }

    void loadNotes(TiXmlElement* musicDataElm) {
        if (musicDataElm == NULL) return;
        TiXmlElement* selectedNotesElm = musicDataElm->FirstChildElement("selectedNotes");
        if (selectedNotesElm != NULL) {
            
            clearSelectedNotes();

            // Notes ...
            for(TiXmlNode* child = selectedNotesElm->FirstChild(); child; child = child->NextSibling() ) {
                TiXmlPrinter printer;
                child->Accept( &printer );
                string elmXML = printer.CStr();
                vizNote note = vizNote(elmXML);
                addSelectedNote(note, true);
            }
            
        }        
    }

    void loadScale(TiXmlElement* musicDataElm) {
        if (musicDataElm == NULL) return;

        TiXmlElement* selectedScaleElm = musicDataElm->FirstChildElement("selectedScale");
        if (selectedScaleElm != NULL) {

            clearSelectedScale();

            TiXmlPrinter printer;
            selectedScaleElm->Accept( &printer );
            string scaleXML = printer.CStr();

            vizScale scale = vizScale(scaleXML, "selectedScale", false);

            if(scale.isScaleValid()) {
                setSelectedScale(scale, false);
                uiVizInstrumentRuleArgs ruleArgs = uiVizInstrumentRuleArgs(scale.getInstrumentRules());
                onRulesChanged(ruleArgs);
            }

        }
    }   

    void loadChords(TiXmlElement* musicDataElm) {
        if (musicDataElm == NULL) return;
        TiXmlElement* selectedChordsElm = musicDataElm->FirstChildElement("selectedChords");
        if (selectedChordsElm != NULL) {
            
            clearSelectedChords();

            // Chords ...
            int key = 1;
            for(TiXmlNode* child = selectedChordsElm->FirstChild(); child; child = child->NextSibling() ) {
                TiXmlPrinter printer;
                child->Accept( &printer );
                string elmXML = printer.CStr();
                vizChord chord = vizChord(elmXML, false);
                addSelectedChord(chord, false, false);
               
                // Set selected key to 1st chord if no Key set...
                if (key == 1 && getSelectedKey().getNoteName() == "") setSelectedKey(chord.getChordRootNote());

                // We only want to apply rules if getIsUserDefinedPoints is false 
                if (!chord.getIsUserDefinedPoints()) {
                    uiVizInstrumentRuleArgs ruleArgs = uiVizInstrumentRuleArgs(chord.getInstrumentRules());
                    onRulesChanged(ruleArgs);                    
                }

                key++;
            }
            
        }
    }  

    void appendInstrumentRulesToXMLNode(ofxXmlSettings* xml, int index) {
        ofxXmlSettings rules = getInstrumentRules();
        TiXmlElement* rulesElm = rules.doc.RootElement();
        uiVizShared::appendXMLToTarget(rulesElm, xml, true);
    }

    virtual void onRulesChanged(uiVizInstrumentRuleArgs &args) {
        // Descendent widgets can respond to rules being changed!
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = uiVizWidget::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL, 0);
        
        settings.pushTag("widget");

        if (getUserCanInvokeContextMenu() == false) {
            settings.setAttribute("properties", "userCanInvokeContextMenu",  getUserCanInvokeContextMenu(), 0);
        }

        settings.pushTag("properties");
        settings.addTag("musicData");
 
        
        // Visualization Modes
        if (getTheoryVizInstrumentDrawMode() != TheoryVizInstrumentDrawMode::UNSET) {
            settings.setAttribute("musicData", "drawMode",  getTheoryVizInstrumentDrawModeString(getTheoryVizInstrumentDrawMode()), 0);
        }
        
        if (getTheoryVizInstrumentTheoryContentMode() != TheoryVizInstrumentTheoryContentMode::UNSET) {
            settings.setAttribute("musicData", "instrumentContentMode",  getTheoryVizInstrumentTheoryContentModeString(getTheoryVizInstrumentTheoryContentMode()), 0);
        }

        if (getTheoryVizInstrumentChordViewMode() != TheoryVizInstrumentChordViewMode::UNSET) {
            settings.setAttribute("musicData", "chordViewMode",  getTheoryVizInstrumentChordViewModeString(getTheoryVizInstrumentChordViewMode()), 0);
        }        

        if (getTheoryVizOrientationMode() != TheoryVizOrientationMode::UNSET) {
            settings.setAttribute("musicData", "orientation",  getTheoryVizOrientationModeString(getTheoryVizOrientationMode()), 0);
        }
        
        settings.setAttribute("musicData", "colorMode",  getTheoryVizColorModeString(getTheoryVizColorMode()), 0);
        settings.setAttribute("musicData", "colorAlternateMode", getTheoryVizColorAlternateModeString(getTheoryVizColorAlternateMode()), 0);
        settings.setAttribute("musicData", "labelMode",  getTheoryVizLabelModeString(getTheoryVizLabelMode()), 0);
        settings.setAttribute("musicData", "labelAlternateMode", getTheoryVizLabelAlternateModeString(getTheoryVizLabelAlternateMode()), 0);
        settings.setAttribute("musicData", "noteMode", getTheoryVizNoteModeString(getTheoryVizNoteMode()), 0);
        settings.setAttribute("musicData", "labelShowOctave", getShowOctaveInLabel(), false);
        settings.setAttribute("musicData", "generalMidiInstrumentNumber", getGMInstrumentNumber(), 0);

        settings.setAttribute("musicData", "isLefty", isLefty(), 0);
        settings.setAttribute("musicData", "isBlackAndWhiteMode", isBlackAndWhiteMode(), 0);        

        if(getUserDefinedChordName() != "") {
            settings.setAttribute("musicData", "userDefinedChordName", getUserDefinedChordName(), 0);
        }   
        
        settings.pushTag("musicData");
        
        // Rules
        if (getSelectedScale().getName() != "") {     
            appendInstrumentRulesToXMLNode(&settings, 0);
        }

        // Selected Scale
        if (getSelectedScale().getName() != "") {
            settings.addTag("selectedScale");
            settings.pushTag("selectedScale");            
            settings.setValue("name", getSelectedScale().getName(), 0);
            settings.setValue("prettyName", getSelectedScale().getNamePretty(), 0);
            settings.setValue("key", getSelectedScale().getKey().getNoteName(), 0);
            getSelectedScale().appendInstrumentRulesToXMLNode(&settings, 0);
            settings.popTag();

        }
        
        // Selected Key
        if (getSelectedKey().getNoteName() != "") {
            settings.addTag("selectedKey");
            settings.setAttribute("selectedKey", "name", getSelectedKey().getNoteName(), 0);
        }
        
        // Selected Keys
        if (m_selectedKeys.size() > 0) {
            settings.addTag("selectedKeys");
            settings.pushTag("selectedKeys");
            for(int i=0; i< getSelectedKeys().size(); i++) {
                if (getSelectedKeys()[i].getNoteName() != "") {
                    settings.addTag("key");
                    settings.setAttribute("key", "name", getSelectedKeys()[i].getNoteName(), i);
                }
            }
            settings.popTag(); // selectedKeys
        }
       
        // Selected Chords
        if (getSelectedChords().size() > 0) {
            settings.addTag("selectedChords");
            settings.pushTag("selectedChords");
            for (int i=0; i< getSelectedChords().size(); i++) {
                getSelectedChords()[i].appendToXMLNode(&settings, i);
            }
            settings.popTag(); // selectedChords
        }
        
        // Selected Notes
        if (getSelectedNotes().size() > 0) {
            settings.addTag("selectedNotes");
            settings.pushTag("selectedNotes");
            for(int i=0; i< getSelectedNotes().size(); i++) {
                if (getSelectedNotes()[i].getNoteName() != "") {
                    settings.addTag("note");
                    settings.setAttribute("note", "name", getSelectedNotes()[i].getNoteName(), i);
                    settings.setAttribute("note", "octave", getSelectedNotes()[i].getNoteOctave(), i);
                }
            }
            settings.popTag(); // selectedKeys
        }
        
        // vizScale - make compatible with uiVizChordPicker
        
        // nuke getSelectedNote ??
        
        settings.popTag(); // musicData
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        
        
        return settings;
    }
    
    TheoryMode getTheoryMode() {
        return mTheoryMode;
    }
    
    void setTheoryMode(TheoryMode theoryMode) {
        mTheoryMode = theoryMode;
    }
    
    TheoryVizColorMode getTheoryVizColorMode() {
        return mTheoryVizColorMode;
    }
    
    void setTheoryVizColorMode(TheoryVizColorMode theoryVizColorMode) {
        mTheoryVizColorMode = theoryVizColorMode;
    }
    
    TheoryVizColorAlternateMode getTheoryVizColorAlternateMode() {
        return mTheoryVizColorAlternateMode;
    }
    
    void setTheoryVizColorAlternateMode(TheoryVizColorAlternateMode theoryVizColorAlternateMode) {
        mTheoryVizColorAlternateMode = theoryVizColorAlternateMode;
    }

    TheoryVizLabelMode getTheoryVizLabelMode() {
        return mTheoryVizLabelMode;
    }
    
    void setTheoryVizLabelMode(TheoryVizLabelMode theoryVizLabelMode) {
        mTheoryVizLabelMode = theoryVizLabelMode;
    }
    
    TheoryVizNoteMode getTheoryVizNoteMode() {
        return mTheoryVizNoteMode;
    }
    
    virtual void setTheoryVizNoteMode(TheoryVizNoteMode theoryVizNoteMode) {
        mTheoryVizNoteMode = theoryVizNoteMode;
    }
 
    TheoryVizLabelAlternateMode getTheoryVizLabelAlternateMode() {
        return mTheoryVizLabelAlternateMode;
    }
    
    void setTheoryVizLabelAlternateMode(TheoryVizLabelAlternateMode theoryVizLabelAlternateMode) {
        mTheoryVizLabelAlternateMode = theoryVizLabelAlternateMode;
    }
    
    TheoryVizShapeMode getTheoryVizShapeMode() {
        return mTheoryVizShapeMode;
    }
    
    void setTheoryVizShapeMode(TheoryVizShapeMode theoryVizShapeMode) {
        mTheoryVizShapeMode = theoryVizShapeMode;
    }
    
    TheoryVizOrientationMode getTheoryVizOrientationMode() {
        return mTheoryVizOrientationMode;
    }
    
    void setTheoryVizOrientationMode(TheoryVizOrientationMode theoryVizOrientationMode) {
        mTheoryVizOrientationMode = theoryVizOrientationMode;
    }

    TheoryVizInstrumentDrawMode getTheoryVizInstrumentDrawMode() {
        return mTheoryVizInstrumentDrawMode;
    }
    
    void setTheoryVizInstrumentDrawMode(TheoryVizInstrumentDrawMode theoryVizInstrumentDrawMode) {
        mTheoryVizInstrumentDrawMode = theoryVizInstrumentDrawMode;
    }

    TheoryVizInstrumentTheoryContentMode getTheoryVizInstrumentTheoryContentMode() {
        return mTheoryVizInstrumentTheoryContentMode;
    }
    
    virtual void setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode theoryVizInstrumentTheoryContentMode) {
        mTheoryVizInstrumentTheoryContentMode = theoryVizInstrumentTheoryContentMode;
    }    

    virtual virtual TheoryVizInstrumentChordViewMode getTheoryVizInstrumentChordViewMode() {
        return mTheoryVizInstrumentChordViewMode;
    }
    
    virtual void setTheoryVizInstrumentChordViewMode(TheoryVizInstrumentChordViewMode theoryVizInstrumentChordViewMode) {
        mTheoryVizInstrumentChordViewMode = theoryVizInstrumentChordViewMode;
    }      

    bool isLefty() {
        return getTheoryVizInstrumentDrawMode() == TheoryVizInstrumentDrawMode::LEFT;
    }
    
    virtual void setIsLefty(bool val) {
        setTheoryVizInstrumentDrawMode(val ? TheoryVizInstrumentDrawMode::LEFT : TheoryVizInstrumentDrawMode::RIGHT);
    }

    bool isBlackAndWhiteMode() {
        return mIsBlackAndWhiteMode;
    }
    
    virtual void setIsBlackAndWhiteMode(bool val) {
        mIsBlackAndWhiteMode = val;
    }    

    bool AlternateTheoryVizLabelMode() {
        bool needsUpdate = false;
        
        switch(getTheoryVizLabelAlternateMode()) {
                
            case TheoryVizLabelAlternateMode::NONE:
                needsUpdate = false;
                break;
                
            case TheoryVizLabelAlternateMode::ALTERNATE_KEYS_DEGREES:
                setTheoryVizLabelMode(getTheoryVizLabelMode() == TheoryVizLabelMode::KEYS ? TheoryVizLabelMode::DEGREES : TheoryVizLabelMode::KEYS);
                needsUpdate = true;
                break;
        }
        
        return needsUpdate;
    }
    
    bool AlternateTheoryVizColorMode() {
        bool needsUpdate = false;
        
        switch(getTheoryVizColorAlternateMode()) {
                
            case TheoryVizColorAlternateMode::NONE:
                needsUpdate = false;
                break;
                
            case TheoryVizColorAlternateMode::ALTERNATE_KEYS_DEGREES:
                setTheoryVizColorMode(getTheoryVizColorMode() == TheoryVizColorMode::KEYS ? TheoryVizColorMode::DEGREES : TheoryVizColorMode::KEYS);
                needsUpdate = true;
                break;
        }
        
        return needsUpdate;
    }
    
    string getUserDefinedChordName() {
        return mUserDefinedChordName;
    }

    virtual void setUserDefinedChordName(string val) {
        if (val != "") {
            mUserDefinedChordName = val;
            uiVizTextChangedArgs args(getWidgetId(), mUserDefinedChordName);
            ofNotifyEvent(userDefinedChordNameChanged, args);
        } else {
            mUserDefinedChordName = val;
        }
    }    

    /****** These are not permanenelty persisted for now ******/
    bool getUserCanSetChordName() {
        return mUserCanSetChordName;
    }

    void setUserCanSetChordName(bool val) {
        mUserCanSetChordName = val;
    }


    bool getUserCanInvokeContextMenu() {
        return mUserCanInvokeContextMenu;
    }

    void setUserCanInvokeContextMenu(bool val) {
        mUserCanInvokeContextMenu = val;
    } 

    bool getUserCanSetSelectedKey() {
        return mUserCanSetSelectedKey;
    }

    void setUserCanSetSelectedKey(bool val) {
        mUserCanSetSelectedKey = val;
    }   

    bool getUserCanAddSelectedNote() {
        return mUserCanAddSelectedNote;
    }

    void setUserCanAddSelectedNote(bool val) {
        mUserCanAddSelectedNote = val;
    }     

    bool getUserCanAddSelectedChord() {
        return mUserCanAddSelectedChord;
    }

    void setUserCanAddSelectedChord(bool val) {
        mUserCanAddSelectedChord = val;
    }

    bool getUserCanAddSelectedScale() {
        return mGetUserCanAddSelectedScale;
    }

    void setUserCanAddSelectedScale(bool val) {
        mGetUserCanAddSelectedScale = val;
    }
    /****** ------------------------------------------- ******/     
    
    virtual ~uiVizWidgetMusical() {
    }
    
    vizNote getSelectedKey() {
        return m_selectedKey;
    }
    
    virtual void setSelectedKey(vizNote val) {

        if(val.getNoteName() == m_selectedKey.getNoteName()) return;

        m_selectedKey = val;

        addToEventTransmitQueue(
            APP_WIDGET_EVENT::SET_SELECTED_KEY, 
            "<event>" + m_selectedKey.getXML() + "</event>"
        );

        m_KeyChangedFunc(val);    
    }

    void handleKeyChanged(const std::function<void(vizNote &)> &func) {
        m_KeyChangedFunc = func;
    }
    
    void clearSelectedKey() {
        m_selectedKey = vizNote();
    }
    
    /* Selected Keys */
    bool isSelectedKey(string name) {
        for(auto key:m_selectedKeys){
            if (key.getNoteName()==name) return true;
        }
        return false;
    }
    
    vector<vizNote> getSelectedKeys() {
        return m_selectedKeys;
    }
    
    vizNote getSelectedKey(string name)  {
        for(auto key:m_selectedKeys){
            if (key.getNoteName()==name) return key;
        }
        return vizNote(); // return empty
    }
    
    bool getIsSelectedKeySharp() {
        return getSelectedKey().getIsNoteSharp();
    }
    
    vizNote getSelectedKeyByIndex(int index)  {
        
        if (getSelectedKeysSize() == 0) return vizNote(); // return empty
        
        index = std::min(index, getSelectedKeysSize() - 1);
        index = std::max(index, 0);
        
        return m_selectedKeys[index];
    }
    
    int getSelectedKeysSize() {
        return m_selectedKeys.size();
    }
    
    virtual void addSelectedKey(vizNote &key) {
        if (getSelectedKey(key.getNoteName()).getNoteName() == "") { // wasn't found, add it
            m_selectedKeys.push_back(key);
        }
    }
    
    virtual void removeSelectedKey(vizNote &key) {
        removeSelectedKey(key.getNoteName());
    }
    
    void removeSelectedKey(string name) {
        m_selectedKeys.erase(std::remove_if(
                                            m_selectedKeys.begin(), m_selectedKeys.end(),
                                            [&](vizNote /*const*/ & key) {
                                                return key.getNoteName() == name;
                                            }),  m_selectedKeys.end());
    }
    
    vizNote getDraggingKey() {
        return m_draggingKey;
    }
    
    void setDraggingKey(vizNote val) {
        m_draggingKey = val;
    }
    
    void clearDraggingKey() {
        m_draggingKey = vizNote();
    }
    
    vizNote getHoveredKey() {
        return m_hoveredKey;
    }
    
    void clearHoveredKey() {
        clearAuditioning();
        m_hoveredKey = vizNote();
    }
    
    void setHoveredKey(vizNote val) {
        if (m_hoveredKey.getNote() != nullptr && val.getNote() != m_hoveredKey.getNote()) {
            clearAuditioning();
        }
        
        m_hoveredKey = val;
    }
    
    bool isSelectedNoteExact(string name) {
        for(auto currNote:getSelectedNotes()){
            if (currNote.getNoteName() == name) return true;
        }
        return false;
    }
    
    bool matchesSelectedNote(vizNote note) {
        
        if (getSelectedNotesSize() == 0) {
            return false;
        }
        
        for(auto currNote:getSelectedNotes()){
            if (currNote.isEnharmonicallyEquivalent(note.getNoteNameNormalized()) && currNote.getIsExtended() == note.getIsExtended()) return true;
        }
        return false;
    }

    vector<vizNote> getSelectedNotes() {
        return m_selectedNotes;
    }
    
    /** NEW FUNCTION  ---> Mimics what the old "hardwired normalized" addSelectedNote used to do!! **/
    // Used by getSelectedNotesDeque when attempting to assert chord types 
    vector<vizNote> getSelectedNotesNormalized() {
        vector<vizNote> notes = {};
        vector<vizNote> nonNormalizedNotes = getSelectedNotes();
        for(auto currNote:getSelectedNotes()) {
            bool shouldAdd = true;
            for(auto note:notes) {
                if (currNote.isEnharmonicallyEquivalent(note.getNoteNameNormalized()) && currNote.getIsExtended() == note.getIsExtended()) {
                    shouldAdd = false;
                    continue;
                }
            }
            if (shouldAdd) notes.push_back(currNote);
        }
        return notes;
    }

    vector<vizNote> getSelectedNotesDistinct() {
        vector<vizNote> countedNotes = {};
        for (vizNote currNote:getSelectedNotes()) {
            bool found = false;
            for (vizNote countedNote:countedNotes) {
                if (countedNote.isEnharmonicallyEquivalent(currNote.getNoteNameNormalized())) {
                    found = true;
                }
            }
            if (!found) countedNotes.push_back(currNote);
        }
        return countedNotes;
    }
    
    deque<MusicTheory::NotePtr> getSelectedNotesDeque(bool distinct, bool normalizeNotes, bool removeExactDuplicates, bool simplifiedChordCalculation) {
        deque <MusicTheory::NotePtr> notes;
         
        vector<vizNote> selectedNotes = (distinct ? getSelectedNotesDistinct() : getSelectedNotesNormalized());
        if (normalizeNotes) {
            selectedNotes = getNormalizedNotes(selectedNotes, simplifiedChordCalculation);
        }

        if(removeExactDuplicates) {

            vizNote lowestRootNote = vizChord::findLowestRootNote(getSelectedKey(), selectedNotes);
            string lowestRootNoteName = lowestRootNote.getNoteNameNormalized();

            vector<vizNote> countedNotes;

            for(auto currNote:selectedNotes) {
                if (!vizChord::noteFound(currNote, countedNotes)) {
                    notes.push_back(currNote.getNote());
                    countedNotes.push_back(currNote);
                }
            }             
        } else {
            for(auto currNote:selectedNotes){
                notes.push_back(currNote.getNote());
            }
        }
        
        return notes;
    }
    
    static int numDistinctNotes(vector<vizNote> notes) {
        vector<vizNote> countedNotes = {};
        for (vizNote currNote:notes) {
            bool found = false;
            for (vizNote countedNote:countedNotes) {
                if (countedNote.isEnharmonicallyEquivalent(currNote.getNoteNameNormalized())) {
                    found = true;
                }
            }
            if (!found) countedNotes.push_back(currNote);
        }
        return countedNotes.size();
    }
    
    void clearSelectedNotes() {
        m_selectedNotes.clear();
    }
    
    vizNote getSelectedNote(string name, bool isExtended)  {
        for(auto note:m_selectedNotes){
            if (note.isEnharmonicallyEquivalent(name) && note.getIsExtended() == isExtended) return note;
        }
        return vizNote(); // return empty
    }

    vizNote getSelectedNote(string name, bool isExtended, int octave)  {
        for(auto note:m_selectedNotes){
            if (note.isEnharmonicallyEquivalent(name) && note.getIsExtended() == isExtended && note.getNoteOctave() == octave) return note;
        }
        return vizNote(); // return empty
    }    
    
    vizNote getSelectedNoteByIndex(int index)  {
        
        if (getSelectedNotesSize() == 0) return vizNote(); // return empty
        
        index = std::min(index, getSelectedNotesSize() - 1);
        index = std::max(index, 0);
        
        return m_selectedNotes[index];
    }

    int getSelectedNotesLowestOctave() {
        int val = 1000;
        for(auto note:m_selectedNotes){
            if (note.getNoteOctave() < val) val = note.getNoteOctave();
        }
        return val;
    }
    
    int getSelectedNotesHighestOctave() {
        int val = -1000;
        for(auto note:m_selectedNotes){
            if (note.getNoteOctave() > val) val = note.getNoteOctave();
        }
        return val;
    }
    
    int getSelectedNotesSize() {
        return m_selectedNotes.size();
    }
    
    void setSelectedNotes(vector<vizNote> notes) {
        m_selectedNotes = notes;
    }
    
    virtual void addSelectedNote(vizNote &note, bool normalize, bool clearExisting) {

        if(clearExisting) m_selectedNotes.clear();

        if (normalize) {
            if (getSelectedNote(note.getNoteNameNormalized(), note.getIsExtended(), note.getNoteOctave()).getNoteName() == "") { // wasn't found, add it  
                m_selectedNotes.push_back(note);

                addToEventTransmitQueue(
                    APP_WIDGET_EVENT::ADD_SELECTED_NOTE, 
                    "<event>" + note.getXML() + "</event>"
                ); 

            }
        } else {
            m_selectedNotes.push_back(note);

            addToEventTransmitQueue(
                APP_WIDGET_EVENT::ADD_SELECTED_NOTE, 
                "<event>" + note.getXML() + "</event>"
            ); 

        }
    }

    virtual void addSelectedNote(vizNote &note, bool normalize) {
        addSelectedNote(note, normalize, false);
    }

    virtual void addSelectedNote(string note, int octave, bool clearExisting) {
        if (vizTheory::isValidKey(note)) {
            vizNote noteToAdd(note, octave, 1);
            addSelectedNote(noteToAdd, false, clearExisting);
        }
    }    
    
    void removeSelectedNote(string name, bool isExtended) {
        m_selectedNotes.erase(std::remove_if(
                                              m_selectedNotes.begin(), m_selectedNotes.end(),
                                              [&](vizNote /*const*/ & note) {
                                                  return note.isEnharmonicallyEquivalent(name) && note.getIsExtended() == isExtended;
                                              }),  m_selectedNotes.end());
    }

    void removeSelectedNote(vizNote &note, bool isExtended) {
        m_selectedNotes.erase(std::remove_if(
                                              m_selectedNotes.begin(), m_selectedNotes.end(),
                                              [&](vizNote /*const*/ & currNote) {
                                                  return currNote.isEnharmonicallyEquivalent(note.getNoteNameNormalized()) && currNote.getIsExtended() == isExtended;
                                              }),  m_selectedNotes.end());
    }
    
    void removeSelectedNoteByDegree(int degree, bool isExtended, vizNote forKey) {
        m_selectedNotes.erase(std::remove_if(
                                             m_selectedNotes.begin(), m_selectedNotes.end(),
                                             [&](vizNote /*const*/ & currNote) {
                                                 return forKey.getInterval(currNote.getNoteName()) == degree && currNote.getIsExtended() == isExtended;
                                             }),  m_selectedNotes.end());
    }
    
    vector<vizNote> getNormalizedNotes(vector<vizNote> notesAdded, bool simplifiedChordCalculation) {
        vizNote lowestChordRootNote = vizChord::findLowestRootNote(getSelectedKey(), notesAdded);
        
        for (vizNote &currNote:notesAdded) {
            bool isExtended = vizChord::calculateIfExtendedNote(lowestChordRootNote, notesAdded, currNote, false, simplifiedChordCalculation); // rule_strictExtendedNotes
            currNote.setNoteOctave(isExtended ? 4 : 3); // Normalize note octaves...
            currNote.setIsExtended(isExtended);
        }
        
        vector<vizNote> normalizedNotes = vector<vizNote>();
    
        for (int degree=0; degree<=11; degree++) {
            for (vizNote currNote:notesAdded) {
                if (currNote.getNoteOctave() == 3 && getSelectedKey().getInterval(currNote.getNoteName()) == degree) {
                    normalizedNotes.push_back(currNote);
                }
            }
        }

        for (int degree=0; degree<=11; degree++) {
            for (vizNote currNote:notesAdded) {
                if (currNote.getNoteOctave() == 4 && getSelectedKey().getInterval(currNote.getNoteName()) == degree) {
                    normalizedNotes.push_back(currNote);
                }
            }
        }

        return normalizedNotes;
    }
    
    
    vizChord getChordFromSelectedNotes(vizNote root, bool allowInversions, bool allowPolyChords, bool normalizeNotes) {

        string chordName = getChordNameFromSelectedNotesPretty(root, allowInversions, allowPolyChords, normalizeNotes);
        string xml = "<chord><name>" + chordName + "</name>";
        for (vizNote note:m_selectedNotes) {
            xml += note.getXML();
        }
        xml += "</chord>";
        
        return vizChord(xml, true);
    }
    
    string getChordNameFromSelectedNotesPretty(vizNote root, bool allowInversions, bool allowPolyChords, bool normalizeNotes) {
        
        deque<MusicTheory::NotePtr> notes = getSelectedNotesDeque(false, normalizeNotes, true, true);
        
        vector<string> names = MusicTheory::Chord::determine(notes, true, allowInversions, allowPolyChords);
        if (names.size() > 0) {
            for (int i=0; i< names.size(); i++) {
            
                string chordName = names[i];
                string chordRoot = vizTheory::extractRootFromChord(chordName);

                if (root.isEnharmonicallyEquivalent(chordRoot)) {
                    ofStringReplace(chordName, "M", "maj");
                    return chordName;
                }
 
            }
            return "unknown";
        } else {
            return "unknown";
        }
    }
    
    string getCalculatedChordName() {
        return mCalculatedChordName;
    }
    
    virtual void setCalculatedChordName(string val) {
        mCalculatedChordName = val;
    }

    string getCalculatedScaleName() {
        return mCalculatedScaleName;
    }

    virtual void setCalculatedScaleName(string val) {
        mCalculatedScaleName = val;
    }
    
    vizNote getDraggingNote() {
        return m_draggingNote;
    }
    
    void setDraggingNote(vizNote val) {
        m_draggingNote = val;
    }
     
    void clearDraggingNote() {
        m_draggingNote = vizNote();;
    }
    
    /* Selected Chords */
    bool isSelectedChord(string name) {
        for(auto chord:m_selectedChords){
            if (chord.getChordName()==name) return true;
        }
        return false;
    }
    
    bool isSelectedChordRoot(string name) {
        for(auto chord:m_selectedChords){
            if (chord.getChordRoot()==name) return true;
        }
        return false;
    }
    
    bool matchesSelectedChordRoot(vizChord chord) {
        
        if (getSelectedChordsSize() == 0) {
            return false;
        }
        
        for(auto currChord:getSelectedChords()){
            if (currChord.getChordRoot() == chord.getChordRoot()) return true;
        }
        return false;
    }

    bool getIsExtendedChordMode() {
        return mIsExtendedChordMode;
    }    
    
    virtual void setIsExtendedChordMode(bool val) {
        mIsExtendedChordMode = val;
        setNeedsUpdate(true);
    }    
    
    bool matchesSelectedKey(vizNote note) {
        return note.isEnharmonicallyEquivalent(getSelectedKey().getNoteNameNormalized());
    }
    
    vector<vizChord> getSelectedChords() {
        return m_selectedChords;
    }
    
    void clearSelectedChords() {
        m_selectedChords.clear();
    }
    
    vizChord getSelectedChord(string name)  {
        for(auto chord:m_selectedChords){
            if (chord.getChordName()==name) return chord;
        }
        return vizChord(); // return empty
    }
    
    vizChord getSelectedChordByIndex(int index)  {
        
        if (getSelectedChordsSize() == 0) return vizChord(); // return empty
        
        index = std::min(index, getSelectedChordsSize() - 1);
        index = std::max(index, 0);
        
        return m_selectedChords[index];
    }

    bool setSelectedChordAtIndex(int index, vizChord chord)  {
        
        if (getSelectedChordsSize() == 0) return false; // return empty
        
        index = std::min(index, getSelectedChordsSize() - 1);
        index = std::max(index, 0);
        
        m_selectedChords[index] = chord;
        return true;
    }

    vizChord* getSelectedChordByIndexRef(int index)  {
        
        if (getSelectedChordsSize() == 0) return nullptr; // return empty
        
        index = std::min(index, getSelectedChordsSize() - 1);
        index = std::max(index, 0);
        
        return &m_selectedChords[index];
    }    
    
    int getSelectedChordsSize() {
        return m_selectedChords.size();
    }
    
    virtual void addSelectedChord(vizChord &chord, bool onlyAddIfNotFound, bool includeInstrumentRules) {
        bool added = false;
        if (onlyAddIfNotFound) {
            if (getSelectedChord(chord.getChordName()).getChordName() == "") { // wasn't found, add it
                if (includeInstrumentRules) chord.setInstrumentRules(getInstrumentRules());
                m_selectedChords.push_back(chord);
                added = true;
            }
        } else {
            if (includeInstrumentRules) chord.setInstrumentRules(getInstrumentRules());
            m_selectedChords.push_back(chord);
            added = true;
        }

        if (added) {
            addToEventTransmitQueue(
                APP_WIDGET_EVENT::ADD_SELECTED_CHORD, 
                "<event>" + chord.getXML() + "</event>"
            ); 
        }

    }
    
    void removeSelectedChord(string name) {
        m_selectedChords.erase(std::remove_if(
                                              m_selectedChords.begin(), m_selectedChords.end(),
                                              [&](vizChord /*const*/ & chord) {
                                                  return chord.getChordName() == name;
                                              }),  m_selectedChords.end());
    }

    void removeSelectedChord(int index) {
        if (index >= 0 && index < m_selectedChords.size()) {
            m_selectedChords.erase(m_selectedChords.begin()+index);
        }
    }    
    
    void removeSelectedChordRoot(vizChord &chord) {
        m_selectedChords.erase(std::remove_if(
                                              m_selectedChords.begin(), m_selectedChords.end(),
                                              [&](vizChord /*const*/ & currChord) {
                                                  return currChord.getChordRoot() == chord.getChordRoot();
                                              }),  m_selectedChords.end());
    }
    
    vizChord getHoveredChord() {
        return m_hoveredChord;
    }
    
    void setHoveredChord(vizChord val) {
        
        if (m_hoveredChord.getChord() != nullptr && val.getChord() != m_hoveredChord.getChord()) {
            clearAuditioning();
        }

        if (val.matchesChord(m_hoveredChord, true, true)) return; 

        m_hoveredChord = val;

        addToEventTransmitQueue(
            APP_WIDGET_EVENT::SET_HOVERED_CHORD, 
            "<event>" + m_hoveredChord.getXML() + "</event>"
        );         
    }
    
    void clearHoveredChord() {
        clearAuditioning();
        m_hoveredChord = vizChord();;
    }
    
    vizChord getDraggingChord() {
        return m_draggingChord;
    }

    void setHoveredChordIndex(int val) {
        vizChord *chord = getSelectedChordByIndexRef(val);
        mHoveredChordIndexPrev = getHoveredChordIndex();
        if (chord) {
            setHoveredChord(*chord);
            mHoveredChordIndex = val;
            if (mHoveredChordIndex != mHoveredChordIndexPrev) setNeedsUpdate(true);
        }              
    }
    
    void clearHoveredChordIndex() {
        mHoveredChordIndex = -1;
        clearHoveredChord();
        setNeedsUpdate(true);
    }
    
    int getHoveredChordIndex() {
        return mHoveredChordIndex;
    }

    void setHoveredChordIndexPrev(int val) {
        mHoveredChordIndexPrev = val;
    }

    int getHoveredChordIndexPrev() {
        return mHoveredChordIndexPrev;
    }    

    void setDraggingChord(vizChord val) {
        m_draggingChord = val;
    }
    
    void clearDraggingChord() {
        m_draggingChord = vizChord();;
    }
    
    vizScale getSelectedScale() {
        return m_selectedScale;
    }

    virtual void setSelectedScale(vizScale val, bool includeInstrumentRules) {
        if (includeInstrumentRules) val.setInstrumentRules(getInstrumentRules());
        
        if (m_selectedScale.matchesScale(val)) {
            return;         
        }
        
        m_selectedScale = val;

        addToEventTransmitQueue(
            APP_WIDGET_EVENT::SET_SELECTED_SCALE, 
            "<event>" + m_selectedScale.getXML() + "</event>"
        ); 

    }
    
    virtual void setSelectedScale(string val, bool includeInstrumentRules) {
        vizScale scale;
        
        if (getSelectedKey().getNoteName() != "") {
            scale = vizScale(getSelectedKey().getNoteName(), val);
        } else {
            scale = vizScale(val);
        }
        
        setSelectedScale(scale, includeInstrumentRules);
    }

    string getSelectedScaleName() {
        return m_selectedScale.getName();
    }
    
    virtual string getSelectedScaleNamePretty() {
        return m_selectedScale.getNamePretty();
    }

    string getScaleNameFromSelectedNotesPretty(vizNote root, bool normalizeNotes, bool includeKeyInName) {
        deque<MusicTheory::NotePtr> notes = getSelectedNotesDeque(false, normalizeNotes, false, false);
        string scaleName = MusicTheory::Scale::determineFromDictionary(notes);

        std::vector<std::string> scaleNameParts = ofSplitString(scaleName, " "); 

        if (!includeKeyInName && scaleNameParts.size() > 1) {
            string pureScaleName = "";
            for (int i=1; i<scaleNameParts.size(); i++) {
                pureScaleName.append(scaleNameParts[i] + "-");
            }
            pureScaleName = ofTrim(pureScaleName);
            return pureScaleName;
        } else {
            return scaleName;
        }
    }
    
    void clearSelectedScale() {
        m_selectedScale = vizScale();
    }
    
    vizScale getDraggingScale() {
        return m_draggingScale;
    }
    
    void setDraggingScale(vizScale val) {
        m_draggingScale = val;
    }
    
    void clearDraggingScale() {
        m_draggingScale = vizScale();
    }

    // Sequence stuff

    virtual void startPlaying() {
        m_IsPlaying = true;
    }

    virtual void stopPlaying() {
        m_IsPlaying = false;
    }    
    
    bool isPlaying() {
        return m_IsPlaying;
    }   

    vizChord getPlayingChord() {
        return m_PlayingChord;
    }

    void setPlayingChordIndex(int val) {
        mPlayingChordIndex = val;
        vizChord *chord = getSelectedChordByIndexRef(val);
        mPlayingChordIndexPrev = getPlayingChordIndex();
        if (chord) {
            m_PlayingChord = *chord;
        }              
    }

    void clearPlayingChordIndex() {
        mPlayingChordIndex = -1;
    }
    
    int getPlayingChordIndex() {
        return mPlayingChordIndex;
    }

    void setPlayingChordIndexPrev(int val) {
        mPlayingChordIndexPrev = val;
    }

    int getPlayingChordIndexPrev() {
        return mPlayingChordIndexPrev;
    }   

    void setPlayingTempoBPM(int val) {
        mPlayingTempoBPM = val;
    }

    int getPlayingTempoBPM() {
        return mPlayingTempoBPM;
    }


    void resetPlayingTimer() {
        mElapsedPlayingTimerMillis = 0;
    }
    
    uint64_t getPlayingTimerMillis() {
        if (mElapsedPlayingTimerMillis == 0) mElapsedPlayingTimerMillis = ofGetSystemTimeMillis();
        return ofGetSystemTimeMillis() - mElapsedPlayingTimerMillis;
    }   

    int getMillisDurationForBPM(int val) {
        return (1000*60)/(val > 0 ? val : 1);
    }        


    bool fontColorRequiresInversion(string key) {
        return key == "D" || key == "A" || key == "E" || key == "B" || key == "F#" || key == "Gb";
    }

    ofColor getFaintFontColor() {
        return ofColor(255, 255, 255, 60);
    }

    ofColor getSelectedFontColor() {
        return ofColor(255, 255, 255, 200);
    } 

    ofColor getHoveredFontColor() {
        return ofColor(255, 255, 255, 180);
    }           

    ofColor getFaintFontColor(string key) {
        if (getTheme().IsDark) {
            return (fontColorRequiresInversion(key) ? ofColor(255, 255, 255, 160) : ofColor(255, 255, 255, 120));
        } else {
            return (fontColorRequiresInversion(key) ? ofColor(255, 255, 255, 120) : ofColor(255, 255, 255, 60));
        }
    }
    
    ofColor getMediumFontColor(string key) {
        return (fontColorRequiresInversion(key) ? ofColor(0, 0, 0, 170) : ofColor(255, 255, 255, 170));
    }         

    ofColor getHoveredFontColor(string key) {
        return (fontColorRequiresInversion(key) ? ofColor(0, 0, 0, 180) : ofColor(255, 255, 255, 180));
    }

    ofColor getSelectedFontColor(string key) {
        if (getTheme().IsDark) {
            return (fontColorRequiresInversion(key) ? ofColor(0, 0, 0, 255) : ofColor(255, 255, 255, 255));
        } else {
            return (fontColorRequiresInversion(key) ? ofColor(0, 0, 0, 255) : ofColor(255, 255, 255, 255));
        }
    }



    ofColor getFaintFontColor_Dark() {
        return ofColor(0, 0, 0, 60);
    }

    ofColor getSelectedFontColor_Dark() {
        return ofColor(0, 0, 0, 200);
    } 

    ofColor getHoveredFontColor_Dark() {
        return ofColor(0, 0, 0, 180);
    }           


    ofColor getFaintFontColor_Dark(string key) {
        return (fontColorRequiresInversion(key) ? ofColor(200, 200, 200, 60) : ofColor(0, 0, 0, 60));
    }    

    ofColor getHoveredFontColor_Dark(string key) {
        return (fontColorRequiresInversion(key) ? ofColor(200, 200, 200, 180) : ofColor(0, 0, 0, 180));
    }

    ofColor getSelectedFontColor_Dark(string key) {
        return (fontColorRequiresInversion(key) ? ofColor(200, 200, 200, 200) : ofColor(0, 0, 0, 200));
    }    


    void drawFontWithShadow(shared_ptr<ofxSmartFont> font, string text, int x, int y, ofColor color, ofColor shadowColor) {
        // Draw shadow 1st!
        
        int shadowOffset = 
            (font->size() <= scale(14) ? scale(1) : scale(2));
        
        ofPushStyle();              
        ofSetColor(shadowColor);
        font->draw(text, x+shadowOffset, y+shadowOffset);
        

        ofSetColor(color);
        font->draw(text, x, y);
        ofPopStyle();         
    }



    ofColor getSliceColorForState(string selectedRoot, string sliceRoot, int sliceDegree, bool selected, bool isExtendedNote) {
        ofColor color;
        switch (getTheoryVizColorMode()) {
                
            case TheoryVizColorMode::NONE:
                color = ofColor::white;
                break;
                
            case TheoryVizColorMode::KEYS: /* FOR HARMINIZATION */
                if (selectedRoot != "") {
                    color = vizTheory::getColorForKey_DegreeBrightness(selectedRoot, sliceDegree, selected);
                }
                else {
                    color = vizTheory::getColorForKey_DegreeBrightness(sliceRoot, sliceDegree, selected);
                }
                break;
            case TheoryVizColorMode::DEGREES:
                color = vizTheory::getColorForDegree_KeyBrightness(sliceDegree, sliceRoot, selected);
                break;
                
            case TheoryVizColorMode::SCALES:
                color = vizTheory::getColorForDegree_ScaleFocus(sliceDegree, selected);
                break;
        };

        // If extended degree, we divide the brightness by 2!
        if (isExtendedNote) {
            return  ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness()/2);;
        } else {
            return color;
        }
        
    }

    ofColor getSliceColorForState(string selectedRoot, string sliceRoot, int sliceDegree, bool selected) {
        return getSliceColorForState(selectedRoot, sliceRoot, sliceDegree, selected, false);
    }

    ofColor getFontColorForState(string sliceRoot, bool isExtendedNote) {
        ofColor color;
        switch (getTheoryVizColorMode()) {
                
            case TheoryVizColorMode::NONE:
                color = ofColor::black;
                break;
                
            case TheoryVizColorMode::KEYS: {
                if (isExtendedNote) {
                    return getSelectedFontColor(sliceRoot);
                } else {
                    return getSelectedFontColor(sliceRoot);
                }                
            }
            break;

            case TheoryVizColorMode::DEGREES: {
                if (isExtendedNote) {
                    return getSelectedFontColor(sliceRoot);
                } else {
                    return getSelectedFontColor(sliceRoot);
                }                
            }
            break;
                
            case TheoryVizColorMode::SCALES: {
                if (isExtendedNote) {
                    return getSelectedFontColor(sliceRoot);
                } else {
                    return getSelectedFontColor(sliceRoot);
                }                
            }
            break;
        };
        return color;
    }    
    
    ofColor getFontColorForState(string selectedRoot) {
        return getFontColorForState(selectedRoot, false);
    }

    ofColor getFontColorForState(string selectedRoot, int alpha) {
        ofColor c = getFontColorForState(selectedRoot, false);
        return ofColor(c.r, c.g, c.b, alpha);
    }    

    bool needsUpdateBeforeDraw(bool shouldResetTimer) override {
        bool needsUpdate = false;
        if (getTimerMillis() >= 2000) {
            bool labelNeedsUpdate = AlternateTheoryVizLabelMode();
            bool colorNeedsUpdate = AlternateTheoryVizColorMode();
            needsUpdate = labelNeedsUpdate || colorNeedsUpdate;
            if (shouldResetTimer) resetTimer();
        }
        return needsUpdate;
    }
    
    /*
     void onWidgetMouseContentDragged(ofMouseEventArgs &e) override {
     
     //ofDrawRectangle(deScale(ofGetMouseX()), deScale(ofGetMouseY()), 100, 100);
     
     if (getSelectedKey().getNoteName() != "") {
     setDraggingNote(getSelectedKey());
     setDragData(getSelectedKey().getXML());
     }
     
     
     // todo : why not seeing draggableπ
     // bug hover activates even if title is overlayed
     // content behind in general
     // aeolian - why not correct
     // highlight resize bounds when hovered and fade out!!! will look awesome
     // file drag active widget!!
     }
     */
    
    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
        string event = args.eventName;
        if (event == WIDGET_EVENT::RECEIVE_DRAG_AND_DROP_DATA) {
            populateTargetMusicalWidget(this, args.getXMLString(true));
        } else if (event == APP_WIDGET_EVENT::SET_SELECTED_KEY) {
            populateTargetMusicalWidget(this, args.getXMLString(true));
        } else if (event == APP_WIDGET_EVENT::ADD_SELECTED_CHORD) {
            populateTargetMusicalWidget(this, args.getXMLString(true));
        } else if (event == APP_WIDGET_EVENT::ADD_SELECTED_NOTE) {
            populateTargetMusicalWidget(this, args.getXMLString(true));            
        } else if (event == APP_WIDGET_EVENT::SET_SELECTED_SCALE) {
            populateTargetMusicalWidget(this, args.getXMLString(true));
        }

    }

    void onWidgetMouseContentDragReleased(ofMouseEventArgs &e, string dragData) override {

        if (getTargetDropWidgetId() == getWidgetId()) {
            // Dragging around stuff in same widget, do something different (do nothing for now
            return;
        }

        //cout << "[" << getPersistentId() << "->" << widgetTarget->getPersistentId() << 
        //    "] RECEIVING DRAG DATA:\n" << dragData;   

        uiVizWidget* widgetTarget = uiVizWidgetManager::getWidget(getTargetDropWidgetId());
        uiVizWidgetMusical* musicalWidgetTarget = dynamic_cast<uiVizWidgetMusical*>(uiVizWidgetManager::getWidget(getTargetDropWidgetId()));
        if (musicalWidgetTarget == NULL) return;

        populateTargetMusicalWidget(musicalWidgetTarget, dragData);

        clearDraggingNote(); 
        clearDraggingChord();        
        clearDraggingScale();    

    }

    static string getTheoryTypeForDragData(string dragData) {
        string type = ""; 
        ofxXmlSettings xml = ofxXmlSettings();
        if (xml.loadFromBuffer(dragData.c_str())) {
            TiXmlElement* rootElm = xml.doc.RootElement();
            if (rootElm != NULL) type = ofToLower(rootElm->ValueStr());
        }
        return type;   
    }


    static vizNote noteFromDragData(string dragData) {
        return vizNote(dragData);
    }

    static vizChord chordFromDragData(string dragData) {
        vizChord draggedChordNormalized = vizChord(dragData, true);            
        vizChord draggedChord = vizChord(dragData, false);
        if (draggedChordNormalized.getChordName() != "") {
            return draggedChord.isChordValid() ? draggedChord : draggedChordNormalized;
        }
        return vizChord();    
    }    

    static vizScale scaleFromDragData(string dragData) {
        return vizScale(dragData, false);
    }    

    static void populateTargetMusicalWidget(uiVizWidgetMusical* musicalWidgetTarget, string dragData) {
        // ofSystemAlertDialog("You dragged something from widgetId " + getWidgetId() + " to " + getTargetDropWidgetId() + "- do something cool here...");

        if (musicalWidgetTarget != nullptr) {
            string type = getTheoryTypeForDragData(dragData); 

            if (type == "note") {
                vizNote draggedNote = vizNote(dragData); // getDraggingNote(); //
                if (draggedNote.getNoteName() != "") {
                    
                    switch(draggedNote.getNoteMode()) {
                        case vizTheory::NoteMode::DEFAULT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::DEFAULT);
                            break;
                        case vizTheory::NoteMode::SHARP:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::SHARP);
                            break;
                        case vizTheory::NoteMode::FLAT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::FLAT);
                            break;
                    }
                    
                    musicalWidgetTarget->setIsUserEditing(false);
                    musicalWidgetTarget->setSelectedKey(draggedNote);
                    musicalWidgetTarget->onKeyChanged(draggedNote);
                    uiVizWidgetManager::setCurrentProjectIsDirty(true);
                }
            }

            
            if (type == "chord") {
                vizChord draggedChordNormalized = vizChord(dragData, true);            
                vizChord draggedChord = vizChord(dragData, false);
                
                if (draggedChordNormalized.getChordName() != "") {
                    
                    switch(draggedChordNormalized.getChordRootNote().getNoteMode()) {
                        case vizTheory::NoteMode::DEFAULT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::DEFAULT);
                            break;
                        case vizTheory::NoteMode::SHARP:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::SHARP);
                            break;
                        case vizTheory::NoteMode::FLAT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::FLAT);
                            break;
                    }
                    
                    musicalWidgetTarget->setIsUserEditing(false);

                    //cout << "THE FOLLOWING CHORD IS BEING POPULATED : " << draggedChord.getXML();
                    bool isChordValid = draggedChord.isChordValid();
                    musicalWidgetTarget->setInstrumentRules(draggedChord.getInstrumentRules(), true);
                    musicalWidgetTarget->addSelectedChord(isChordValid ? draggedChord : draggedChordNormalized, false, true);
                    if (musicalWidgetTarget->getWidgetClassType() != APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET) {
                        // Chord bucket is for multiple chords...
                        musicalWidgetTarget->setUserDefinedChordName(draggedChord.getChordName_UserDefined());              
                    }
                    
                    musicalWidgetTarget->setNeedsUpdate(true);
                    uiVizWidgetManager::setCurrentProjectIsDirty(true);
                }                
            }            

            if (type == "scale") {
                vizScale draggedScale = vizScale(dragData, false); // getDraggingScale();
                if (draggedScale.getName() != "") {
                    
                    switch(draggedScale.getKey().getNoteMode()) {
                        case vizTheory::NoteMode::DEFAULT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::DEFAULT);
                            break;
                        case vizTheory::NoteMode::SHARP:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::SHARP);
                            break;
                        case vizTheory::NoteMode::FLAT:
                            musicalWidgetTarget->setTheoryVizNoteMode(TheoryVizNoteMode::FLAT);
                            break;
                    }
                    
                    //cout << "THE FOLLOWING SCALE IS BEING POPULATED : " << draggedScale.getXML();
                    musicalWidgetTarget->setIsUserEditing(false);
                    musicalWidgetTarget->setInstrumentRules(draggedScale.getInstrumentRules(), true);
                    musicalWidgetTarget->setSelectedScale(draggedScale, true);

                    musicalWidgetTarget->setNeedsUpdate(true);
                    uiVizWidgetManager::setCurrentProjectIsDirty(true);
                }                  
            }
          
        }
           
    }

    virtual void onKeyChanged(vizNote note) {    
    }
    
    virtual vector<string> getFilesForExternalDropOperation(string dragData) override {
        vector<string> dragFiles; 

        // We don't want to drag externally unless SHIFT key is held down or IsDefaultDragBehaviourForExternalDrop = true
        if (!ofGetKeyPressed(OF_KEY_SHIFT) || getIsDefaultDragBehaviourForExternalDrop()) {
            return dragFiles;
        }

        bool foundChordOrScale = false;

        vizChord draggedChord = vizChord(dragData, false);
        if (draggedChord.getChordName() != "") {
            string savedFile = draggedChord.saveToMidiFile();
            if (savedFile != "") dragFiles.push_back(savedFile);
            foundChordOrScale = true;
        }

        // todo : guitar, add strum...

        vizScale draggedScale = vizScale(dragData, false); // getDraggingScale();
        if (draggedScale.getName() != "") {
            string savedFile = draggedScale.saveToMidiFile();
            if (savedFile != "") dragFiles.push_back(savedFile);
            foundChordOrScale = true;
        }   

        if (!foundChordOrScale) {
            vizNotes draggedNotes = vizNotes(dragData, false);
            string notesXML = draggedNotes.getXML();
            if (draggedNotes.getNotes().size() > 0) {
                string savedFile = draggedNotes.saveToMidiFile();
                if (savedFile != "") dragFiles.push_back(savedFile);
            }     
        }

        return dragFiles;        
        
    }

     bool getIsDefaultDragBehaviourForExternalDrop() {
         return mIsDefaultDragBehaviourForExternalDrop;
     }

     void setIsDefaultDragBehaviourForExternalDrop(bool val) {
         mIsDefaultDragBehaviourForExternalDrop = val;
     }     
    
    virtual void onWidgetKeyPressed(ofKeyEventArgs &e) override {
        int key = e.key;
        
        switch (key) {
                
            case VIZ_KEY_NUMBER_1: // Toggling Labels
                
                switch (getTheoryVizLabelMode()) {
                    case TheoryVizLabelMode::NONE:
                        setTheoryVizLabelMode(TheoryVizLabelMode::KEYS);
                        setWidgetNeedsUpdate(true);
                        break;
                    case TheoryVizLabelMode::KEYS:
                        setTheoryVizLabelMode(TheoryVizLabelMode::DEGREES);
                        setWidgetNeedsUpdate(true);
                        break;
                    case TheoryVizLabelMode::DEGREES:
                        setTheoryVizLabelMode(TheoryVizLabelMode::NONE);
                        setWidgetNeedsUpdate(true);
                        break;
                }
                break;
                
            case VIZ_KEY_NUMBER_2: // Toggling colors
                
                switch (getTheoryVizColorMode()) {
                    case TheoryVizColorMode::NONE:
                        setTheoryVizColorMode(TheoryVizColorMode::KEYS);
                        setWidgetNeedsUpdate(true);
                        break;
                    case TheoryVizColorMode::KEYS:
                        setTheoryVizColorMode(TheoryVizColorMode::DEGREES);
                        setWidgetNeedsUpdate(true);
                        break;
                    case TheoryVizColorMode::DEGREES:
                        setTheoryVizColorMode(TheoryVizColorMode::NONE);
                        setWidgetNeedsUpdate(true);
                        break;
                }
        }
    }
    
    void clearAuditioning() {
        isAuditioning = false;
    }
    
    void auditionNote(vizNote note) {
        if (getIsActiveWidget() && !isAuditioning) {
            isAuditioning = true;
            note.audition(getGMInstrumentNumber());
        }
    }
    void auditionChord(vizChord chord, int bpm = 120, bool threaded = true) {
        // if (getIsActiveWidget() && !isAuditioning) {
        //     isAuditioning = true;
        //     chord.audition(getGMInstrumentNumber());
        // }

        if (!isAuditioning || isPlaying()) {
            isAuditioning = true;


            if (threaded) {
                if (isThreadRunning() || auditioningChord.getIsPlaying()) {
                    auditioningChord.setIsPlaying(false);
                    stopThread();
                }
                auditioningChordBPM = bpm;
                auditioningChord = chord;                
                startThread(true);
            } else {
                chord.audition(getGMInstrumentNumber(), bpm);
            }
        }

    }

    vizChord getAuditioningChord() {
        return auditioningChord;
    }


    void threadedFunction(){
        while(isThreadRunning()) {
            if (!auditioningChord.getIsPlaying()) {
                // lock();
                auditioningChord.audition(getGMInstrumentNumber(), auditioningChordBPM);
                // unlock();
            }

            if (!auditioningChord.getIsPlaying()) {    
                stopThread();    
            }
        }
    }

    void onWidgetKeyReleased(ofKeyEventArgs &e) override {
    }
    
    bool getIsUserEditing() {
        return mIsUserEditing;
    }
    
    void setIsUserEditing(bool val) {
        mIsUserEditing = val;
    }
    
    bool getShowOctaveInLabel() {
        return mShowOctaveInLabel;
    }
    
    void setShowOctaveInLabel(bool val) {
        mShowOctaveInLabel = val;
    }
    
    
    
    /* todo : populate / load this from the loadState / saveState methods */
    
    /* Rules for this Music Widget */
    ofxXmlSettings getInstrumentRules() {
        return mInstrumentRules;
    }

    string getInstrumentRulesXMLString() {
        string retVal = "";
        TiXmlPrinter printer;
        TiXmlElement* rootElm = mInstrumentRules.doc.RootElement();
        if (rootElm != NULL) {
            rootElm->Accept( &printer );
            retVal = printer.CStr();    
        }
        return retVal;    
    }    
    
    virtual void setInstrumentRules(ofxXmlSettings rules, bool fireEvent) {
        
        TiXmlElement* rootElm = rules.doc.RootElement();
        if (rootElm == NULL)  {
            return;
        } 

        TiXmlPrinter printer;
        rootElm->Accept( &printer );
        string newRulesXMLString = printer.CStr();    

        if (!mInstrumentRules.loadFromBuffer(newRulesXMLString)) {
            cout << "Error Loading new rules : \n" << newRulesXMLString << "\n";
        }

        if(fireEvent) {
            uiVizInstrumentRuleArgs ruleArgs = uiVizInstrumentRuleArgs(rules);
            ofNotifyEvent(rulesChanged, ruleArgs);
        }         
    }

    void setInstrumentRules(string rules, bool fireEvent) {
        ofxXmlSettings rulesXML;  
        if (rulesXML.loadFromBuffer(rules.c_str())) {
            setInstrumentRules(rulesXML, fireEvent);
        }            
    }  

    void appendInstrumentRules(TiXmlElement* rules, bool overwite, bool fireEvent) {
        
        ofxXmlSettings rulesTarget;  
        rulesTarget.loadFromBuffer(getInstrumentRulesXMLString());

        if (!rulesTarget.pushTag("rules")) {
            rulesTarget.addTag("rules");
            rulesTarget.pushTag("rules");
        }

        if (overwite && rules != NULL) {
            string tagName = rules->Value();   
            rulesTarget.removeTag(tagName, 0);
        }

        uiVizShared::appendXMLToTarget(rules, &rulesTarget, true);

        rulesTarget.popTag();
        setInstrumentRules(rulesTarget, fireEvent);  
    }      


    /* This function will remove any instrument specific rules */
    void setInstrumentRule_Genericize() {

        while (mInstrumentRules.popTag() > 0); // pop to top!

        if (!mInstrumentRules.pushTag("rules")) {
            mInstrumentRules.addTag("rules");
            mInstrumentRules.pushTag("rules");
        }        

        mInstrumentRules.removeTag("stringed");
        mInstrumentRules.removeTag("strings");
        mInstrumentRules.removeTag("keyed");
        // ... add more instrument stuff here

    }

    void setInstrumentRule_RemoveGeneralBlock() {

        while (mInstrumentRules.popTag() > 0); // pop to top!

        if (!mInstrumentRules.pushTag("rules")) {
            mInstrumentRules.addTag("rules");
            mInstrumentRules.pushTag("rules");
        }        

        mInstrumentRules.removeTag("general");

    }    

    void setInstrumentRule(string instrument, string tag, string value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    void setInstrumentRule(string instrument, string tag, int value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    void setInstrumentRule(string instrument, string tag,  double value) {
        pushToInstrumentRulesTag(instrument);
        mInstrumentRules.tagExists(tag, 0) ? mInstrumentRules.setValue(tag, value, 0) : mInstrumentRules.addValue(tag, value);
    }
    
    string getInstrumentRule(string instrument, string tag, string defaultVal) {
        pushToInstrumentRulesTag(instrument);
        string val = mInstrumentRules.getValue(tag, defaultVal, 0);
        return val;
    }
    
    int getInstrumentRule(string instrument, string tag, int defaultVal) {
        pushToInstrumentRulesTag(instrument);
        int val = mInstrumentRules.getValue(tag, defaultVal, 0);
        return val;
    }
    
    double getInstrumentRule(string instrument, string tag,  double defaultVal) {
        pushToInstrumentRulesTag(instrument);
        double val = mInstrumentRules.setValue(tag, defaultVal, 0);
        return val;
    }
    
    void deleteInstrumentRule(string instrument, string tag) {
        while (mInstrumentRules.popTag() > 0); // pop to top!
        mInstrumentRules.removeTag(tag, 0);
    }

    void pushToInstrumentRulesTag(string instrument) {
        
        while (mInstrumentRules.popTag() > 0); // pop to top!

        /*
        if (!mInstrumentRules.bDocLoaded) {
            mInstrumentRules = ofxXmlSettings();
        }

        // Pop to root
        while(mInstrumentRules.getPushLevel() > 0) {
            mInstrumentRules.popTag();
        }
        */
       
        if (!mInstrumentRules.pushTag("rules")) {
            mInstrumentRules.addTag("rules");
            mInstrumentRules.pushTag("rules");
        }
        
        if (!mInstrumentRules.pushTag(instrument)) {
            mInstrumentRules.addTag(instrument);
            mInstrumentRules.pushTag(instrument);
        }
    }
    
    uiVizWidgetMenu* getPopoutMenu(int menuTag) {
        uiVizWidget* widget = getPopoutWidgetForMenuTag(menuTag);
        if (widget == nullptr) return nullptr;
        uiVizWidgetMenu* widgetMenu = dynamic_cast<uiVizWidgetMenu*>(widget);
        return widgetMenu;
    }

    int getGMInstrumentNumber() {
        return mGMInstrumentNumber;
    }

    void setGMInstrumentNumber(int val) {
        mGMInstrumentNumber = val;
    }

    bool getShowHelpIcon() {
        return mShowHelpIcon;
    }

    void setShowHelpIcon(bool val) {
        mShowHelpIcon = val;
    }

    bool getShowSettingsIcon() {
        return mShowSettingsIcon;
    }

    void setShowSettingsIcon(bool val) {
        mShowSettingsIcon = val;
    }    

    virtual vector<uiVizIcon> getWidgetTitleIcons() override {
        vector<uiVizIcon> icons = uiVizWidget::getWidgetTitleIcons();

        if (getShowHelpIcon()) {
            icons.push_back(uiVizIconCache::getIcon("REG_WIDGET_HELP"));
        }

        if (getShowSettingsIcon()) {
            icons.push_back(uiVizIconCache::getIcon("REG_WIDGET_SETTINGS"));
        }        
        
        return icons;
    }    


    virtual void titleIconClicked(int iconTag, uiVizCoord::vizBounds deScaledClickBounds) override {

        uiVizCoord::vizBounds iconBounds = getPopoutScaledBoundsForTitleIcon(iconTag);            

        if (iconTag == uiVizIconCache::IconTag::WIDGET_HELP) {
            if (mWidgetTextEditorHelp == nullptr) {
                mWidgetTextEditorHelp = new uiVizWidgetDialog(getPersistentId() + "__HELP", R"(
                <widget>
                    <bounds width="500" height="300" />
                </widget>
                )");   

                uiVizWidgetManager::addWidgetForPopout(*mWidgetTextEditorHelp, getWidgetId(), true);
            }
            
            mWidgetTextEditorHelp->setTitle("Help");  
            mWidgetTextEditorHelp->setMessage(getViz()->langHelp(getWidgetClassType()), true);
            mWidgetTextEditorHelp->setButtons("Close", "BTN_CANCEL");

            mWidgetTextEditorHelp->popoutFrom(
                deScale(iconBounds.x), 
                deScale(iconBounds.y), 
                getSuggestedPopoutDirectionFromWidgetTitleBar()
            );
            mWidgetTextEditorHelp->setTheme(getViz()->getThemeManager()->getContrastingSystemTheme(getTheme(), true));
        } else {  // eg iconTag == uiVizIconCache::IconTag::WIDGET_SETTINGS
            uiVizWidget* w = getPopoutWidgetForMenuTag(iconTag);
            if (w != nullptr) {
                w->setTheme(getViz()->getThemeManager()->getContrastingSystemTheme(getTheme(), true));          
                w->popoutFrom(
                    deScale(iconBounds.x), 
                    deScale(iconBounds.y), 
                    getSuggestedPopoutDirectionFromWidgetTitleBar()
                );
                w->setIsDraggable(true);
            }
        }
        uiVizWidget::titleIconClicked(iconTag, deScaledClickBounds);
    }


private:
    TheoryMode mTheoryMode = TheoryMode::KEY_CENTRIC;
    TheoryVizColorMode mTheoryVizColorMode = TheoryVizColorMode::KEYS;
    TheoryVizLabelMode mTheoryVizLabelMode = TheoryVizLabelMode::KEYS;
    TheoryVizNoteMode mTheoryVizNoteMode = TheoryVizNoteMode::DEFAULT;
    TheoryVizColorAlternateMode mTheoryVizColorAlternateMode = TheoryVizColorAlternateMode::NONE;
    TheoryVizLabelAlternateMode mTheoryVizLabelAlternateMode = TheoryVizLabelAlternateMode::NONE;
    TheoryVizShapeMode mTheoryVizShapeMode = TheoryVizShapeMode::CIRCLE;
    TheoryVizOrientationMode mTheoryVizOrientationMode = TheoryVizOrientationMode::UNSET;
    TheoryVizInstrumentDrawMode mTheoryVizInstrumentDrawMode = TheoryVizInstrumentDrawMode::UNSET;
    TheoryVizInstrumentTheoryContentMode mTheoryVizInstrumentTheoryContentMode = TheoryVizInstrumentTheoryContentMode::UNSET;
    TheoryVizInstrumentChordViewMode mTheoryVizInstrumentChordViewMode = TheoryVizInstrumentChordViewMode::UNSET;
    
    string mUserDefinedChordName = "";
    bool mUserCanSetChordName = true;
    bool mUserCanInvokeContextMenu = true;
    bool mUserCanSetSelectedKey = true;
    bool mUserCanAddSelectedNote = true;
    bool mUserCanAddSelectedChord = true;
    bool mGetUserCanAddSelectedScale = true;

    bool mIsBlackAndWhiteMode = false;
    bool mShowHelpIcon = true;
    bool mShowSettingsIcon = true;

    vizNote m_selectedKey;
    vizNote m_hoveredKey;
    vector<vizNote> m_selectedKeys;
    vizNote m_draggingKey;
    vector<vizNote> m_selectedNotes;
    vizNote m_draggingNote;
    vector<vizChord> m_selectedChords;
    vizChord m_hoveredChord;
    vizChord m_draggingChord;
    vizScale m_selectedScale;
    vizScale m_draggingScale;
    int mHoveredChordIndex = -1;
    int mHoveredChordIndexPrev = -1;

    vizChord m_PlayingChord;
    int mPlayingChordIndex = -1;
    int mPlayingChordIndexPrev = -1;

    uiVizWidgetElmBreadcrumb *mWidgetElmBreadcrumb = nullptr;
    vector<uiVizWidgetElmBreadcrumbItem> mBreadcrumbItemItems;

    uiVizWidgetDialog *mWidgetTextEditorHelp = nullptr;
    uiVizWidgetEventListener *mWidgetEventListenerConfig = nullptr;
    
    std::function<void(vizNote &)> m_KeyChangedFunc = [this](vizNote &){};
    

    // Sequencer stuff
    bool m_IsPlaying = false;
    uint64_t mElapsedPlayingTimerMillis = 0;
    int mPlayingTempoBPM = 80;    
    
    bool isAuditioning = false;
    bool mIsUserEditing = false;
    bool mShowOctaveInLabel = false;
    bool mIsDefaultDragBehaviourForExternalDrop = false;
    int mGMInstrumentNumber = vizTheory::GeneralMidiInstrument::Acoustic_Grand_Piano;
    
    string mCalculatedChordName = "";
    bool mIsExtendedChordMode = false;
    string mCalculatedScaleName = "";
    ofxXmlSettings mInstrumentRules = ofxXmlSettings();

    int auditioningChordBPM = 120;
    vizChord auditioningChord;    
    
    void init() {
        m_selectedKey = vizNote();
        m_selectedKeys = vector<vizNote>();
        m_hoveredKey = vizNote();
        m_draggingKey = vizNote();
        m_selectedNotes = vector<vizNote>();
        m_draggingNote = vizNote();
        m_selectedChords = vector<vizChord>();
        m_hoveredChord = vizChord();
        m_draggingChord = vizChord();
        m_selectedScale = vizScale();
        m_draggingScale = vizScale();
        // setBreadcrumbItemItems({uiVizWidgetElmBreadcrumbItem("a", "A123"), uiVizWidgetElmBreadcrumbItem("b", "Bsfsdf"), uiVizWidgetElmBreadcrumbItem("c", "Csdgasasfd")});
    }
    
};


