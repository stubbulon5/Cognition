
#pragma once
#include "WidgetMusical.h"

class WidgetChordRules : public WidgetMusical {
public:

    ofEvent<uiVizInstrumentRuleArgs>     rulesChanged;

    WidgetChordRules(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        settings.pushTag("widget");

        settings.pushTag("properties");        
        settings.popTag(); // properties
        settings.popTag(); // widget

        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = Widget::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_RULES, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    void loadRules(string rulesXML) {
    }

    void addSelectedChord(vizChord &chord, bool onlyAddIfNotFound, bool includeInstrumentRules) override {
        // We use the incoming chord's notes, not the actual chord...
        if (!chord.isChordValid()) return;
        clearSelectedNotes();
        WidgetMusical::setSelectedKey(chord.getChordRootNote());
         
        for (int j=0; j<chord.getNotes().size(); j++) {
            addSelectedNote(chord.getNotes()[j], true);
        }
        setIsExtendedChordMode(getSelectedNotes().size() >= 4);
        
        setCalculatedChordName(getChordNameFromSelectedNotesPretty(getSelectedKey(), false, true, true));

        SLD_startingInversion->setIsEnabled(true);

        if (vizChord::numDistinctNotes(getSelectedNotes()) > 3 && SLD_startingInversion) {
            SLD_startingInversion->setValue(-1, false);
            SLD_startingInversion->setIsEnabled(false);
        }

    }    

/*
    todo
    do scales rules
    degree colours - bug fix
    fix missing chords
    drag rules (in drag data)
    persist and load rules
    add rules to title 
    correct layout for rules depending on CHORD|SCALE
    bring rules over to the Scales widget
    scale rules : allowNoteRepetition
    fix bug with scale always revering to Chromatic

    move some rules to "GENERAL"
    add rules by exact instrument 
        ie GUITAR_<stings>_STRING eg 
        GUITAR_6_STRING
        BASS_4_STRING
        BASS_5_STRING

    if applying and cant find exact, fallback to nearest....
    Persist all of this (for al instruments) when dragging around

    add start and end fret rules
    add tuning start and end fret
    add enables strings

    start thinking about some launch content (eg how chords are constructed from scales scales). WidgetTutuor -> ownerWidgetId
*/
    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {

        string event = args.getFullEventName();
        bool ruleChanged = false;

        if (args.sender.matchesWidget(SLD_startingInversion)) {
            if (getInstrumentRule("general", "startingInversion", 0)+1 != SLD_startingInversion->getValue()) {
                ruleChanged = true;
            }
        }

        // TODO ---- feed the chord into this widget, so we know how many inversion there are...

        if (args.sender.matchesWidget(CHK_allowNoteRepetition)) {
            if (getInstrumentRule("general", "allowNoteRepetition", true) != CHK_allowNoteRepetition->getValue()) {
                ruleChanged = true;
            }
        }        

        if (args.sender.matchesWidget(CHK_exactOctaveMatch)) {
            if (getInstrumentRule("general", "exactOctaveMatch", false) != CHK_exactOctaveMatch->getValue()) {
                ruleChanged = true;
            }
        }        

        if (args.sender.matchesWidget(CHK_showExtendedNoteNames)) {
            if (getInstrumentRule("general", "showExtendedNoteNames", true) != CHK_showExtendedNoteNames->getValue()) {
                ruleChanged = true;
            }
        }

        if (args.sender.matchesWidget(CHK_strictExtendedNotes)) {
            if (getInstrumentRule("general", "strictExtendedNotes", true) != CHK_strictExtendedNotes->getValue()) {
                ruleChanged = true;
            }
        }        

        if (args.sender.matchesWidget(SLD_notesPerString)) {
            if (getInstrumentRule("stringed", "notesPerString", 1) != SLD_notesPerString->getValue()) {
                ruleChanged = true;
            }
        }        


        if (ruleChanged) {

            int inversionVal = SLD_startingInversion->getValue();

            setInstrumentRule("general", "startingInversion", max(inversionVal-1, -1)); // offset
            updateInversionSliderLabel();

            setInstrumentRule("general", "allowNoteRepetition", CHK_allowNoteRepetition->getValue());
            setInstrumentRule("general", "exactOctaveMatch", CHK_exactOctaveMatch->getValue());
            
            setInstrumentRule("general", "showExtendedNoteNames", CHK_showExtendedNoteNames->getValue());
            setInstrumentRule("general", "strictExtendedNotes", CHK_strictExtendedNotes->getValue());
            setInstrumentRule("stringed", "notesPerString", SLD_notesPerString->getValue());

            uiVizInstrumentRuleArgs ruleArgs = uiVizInstrumentRuleArgs(getInstrumentRules());
            ofNotifyEvent(rulesChanged, ruleArgs);
        } 



    }

    void updateInversionSliderLabel() {
        int inversionVal = SLD_startingInversion->getValue() - 1;
        switch(inversionVal) {
            case -1: { SLD_startingInversion->setTitle("Any Inversion"); break; }
            case 0: { SLD_startingInversion->setTitle("No Inversion"); break; }
            case 1: { SLD_startingInversion->setTitle("1st Inversion"); break; }
            case 2: { SLD_startingInversion->setTitle("2nd Inversion"); break; }
            case 3: { SLD_startingInversion->setTitle("3rd Inversion"); break; }
            case 4: { SLD_startingInversion->setTitle("4th Inversion"); break; }
            case 5: { SLD_startingInversion->setTitle("5th Inversion"); break; }     
            default: { SLD_startingInversion->setTitle("Any Inversion"); break; }
        }
    }

    virtual void setInstrumentRules(ofxXmlSettings rules, bool fireEvent) override {
        // Update the UI here!
        WidgetMusical::setInstrumentRules(rules, fireEvent);

        //cout << "SETTING RULES IN UI:\n" << getInstrumentRulesXMLString();

        int inversionVal = getInstrumentRule("general", "startingInversion", 0);
        SLD_startingInversion->setValue(inversionVal+1, false); // offset
        updateInversionSliderLabel();

        
        if (fireEvent) {
            uiVizInstrumentRuleArgs ruleArgs = uiVizInstrumentRuleArgs(getInstrumentRules());
            ofNotifyEvent(rulesChanged, ruleArgs);            
        }
    }

    virtual void setTheoryVizInstrumentTheoryContentMode(TheoryVizInstrumentTheoryContentMode theoryVizInstrumentTheoryContentMode) override {
        WidgetMusical::setTheoryVizInstrumentTheoryContentMode(theoryVizInstrumentTheoryContentMode);

        if (!SLD_notesPerString) return;

        switch(getTheoryVizInstrumentTheoryContentMode()) {
            case TheoryVizInstrumentTheoryContentMode::CHORD: {
                SLD_notesPerString->setIsVisible(false);
                title = Aquamarine::Shared::lang("CHORD_RULES");
                setTitle(title);
                break;
            }

            case TheoryVizInstrumentTheoryContentMode::SCALE: {
                CHK_showExtendedNoteNames->setIsVisible(false);
                CHK_strictExtendedNotes->setIsVisible(false);
                SLD_startingInversion->setIsVisible(false);
                CHK_exactOctaveMatch->setIsVisible(false);
                title = Aquamarine::Shared::lang("SCALE_RULES"); 
                setTitle(title);             
                break;
            }            

        }

        if (breadcrumb != nullptr) breadcrumb->setBreadcrumbItemItems(title + "|General", "|");

    }    



protected:


private:
    Aquamarine::WidgetElmBreadcrumb *breadcrumb = nullptr;
    Aquamarine::WidgetElmSlider* SLD_startingInversion = nullptr;  
    Aquamarine::WidgetElmCheckbox* CHK_allowNoteRepetition = nullptr; 
    Aquamarine::WidgetElmCheckbox* CHK_exactOctaveMatch = nullptr;
    Aquamarine::WidgetElmCheckbox* CHK_showExtendedNoteNames = nullptr; 
    Aquamarine::WidgetElmCheckbox* CHK_strictExtendedNotes = nullptr;    
    Aquamarine::WidgetElmSlider* SLD_notesPerString = nullptr;   
    string title = "";
    

    void initWidget() override {


        setMinWidth(400);
        setMinHeight(300);

        setWidth(400);
        setHeight(300);        

        setStaticTopTitleBarSize(40);
        setIsDraggable(false);
    

        // Instrument, Chord and Scale
        int rule_startingInversion = getInstrumentRule("general", "startingInversion", -1); // -1 = start on any inversion, 0 for no inv, 1 for 1st inversion
        bool rule_allowNoteRepetition = getInstrumentRule("general", "allowNoteRepetition", true); /// eg C4 and C3 is allowed to be added
        
        bool rule_exactOctaveMatch = getInstrumentRule("general", "exactOctaveMatch", false);


        // Instrument, Chord only
        bool rule_showExtendedNoteNames = getInstrumentRule("general", "showExtendedNoteNames", true);
        bool rule_strictExtendedNotes = getInstrumentRule("general", "strictExtendedNotes", true); // notes MUST be greater than the root octave
        
        ///----------------------------------

        // Instrument, Chord Deep search
        bool searchForExactChordMatch = getInstrumentRule("general", "searchForExactChordMatch", false); // Move this to a global musicalWidget bool variable for performance reasons
                
        // todo, when incompatible rules emergem auto change other values in event handler
  
         // Stringed, Chord AND Scale ....
        int rule_startingString = getInstrumentRule("stringed", "startingString", -1); // -1 = start on any string, 0 for lowest      

        
        // Instrument, Scale only (hidden for now)
        bool rule_enforceAscendingNotes = getInstrumentRule("general", "enforceAscendingNotes", false); // next note MUST be greater than the previous
        
        // Stringed, Scale only ....
        int rule_notesPerString = getInstrumentRule("stringed", "notesPerString", 1);    
        
        switch(getTheoryVizInstrumentTheoryContentMode()) {
            case TheoryVizInstrumentTheoryContentMode::CHORD: {
                rule_notesPerString = getInstrumentRule("stringed", "notesPerString", 1);
                break;
            }

            case TheoryVizInstrumentTheoryContentMode::SCALE: {
                rule_notesPerString = getInstrumentRule("stringed", "notesPerString", 3);   
                rule_allowNoteRepetition = getInstrumentRule("general", "allowNoteRepetition", false); /// eg C4 and C3 is allowed to be added  
                break;
            }            

        }
        
        //set user defined name - 2nd inversion

        
        // Hidden
        bool rule_allowNoteRepetitionExactOctave = getInstrumentRule("general", "allowNoteRepetitionExactOctave", false); /// eg C3 and C3 wont be aded twice    
        string searchForExactChordMatchDirection = getInstrumentRule("general", "searchForExactChordMatchDirection", "up"); // up | down
    
        

        string breadcrumbId = getPersistentId() +  "_BREADCRUMB";
        string SLD_startingInversionId = getPersistentId() +  "_SLD_STARTING_INVERSION";   
        string CHK_allowNoteRepetitionId = getPersistentId() +  "_CHK_NOTE_REPETITION";  
        string CHK_exactOctaveMatchId = getPersistentId() +  "_CHK_EXACT_OCTAVE_MATCH";  



        string CHK_showExtendedNoteNamesId = getPersistentId() +  "_CHK_EXTENDED_NOTE_NAMES";   
        string CHK_strictExtendedNotesId = getPersistentId() +  "_CHK_STRICT_EXTENDED_NOTES";       
        string SLD_notesPerStringId = getPersistentId() +  "_SLD_NOTES_PER_STRING";   
         

        if (!breadcrumb) {
            breadcrumb = dynamic_cast<Aquamarine::WidgetElmBreadcrumb*>(addOrLoadWidgetElement(breadcrumb, Aquamarine::WIDGET_ELM_CLASS::BREADCRUMB, breadcrumbId, R"(
                <element>
                </element>
                )"));

            breadcrumb->setX_Expr("${PARENT.LEFT}");
            breadcrumb->setY_Expr("${PARENT.TOP}-${PADDING}");
            breadcrumb->setHeight_Expr("30");
            breadcrumb->setWidth_Expr("${PARENT.USABLE_WIDTH}");
            breadcrumb->setBreadcrumbItemItems(title + "|General", "|"); 

        }

        if (!SLD_startingInversion) {

            SLD_startingInversion = dynamic_cast<Aquamarine::WidgetElmSlider*>(addOrLoadWidgetElement(SLD_startingInversion, Aquamarine::WIDGET_ELM_CLASS::SLIDER, SLD_startingInversionId, R"(
                <element>
                <title>Any Inversion</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            SLD_startingInversion->setX_Expr("${PARENT.LEFT}");
            SLD_startingInversion->setY_Expr("${"+breadcrumbId+".BOTTOM}+${PADDING}"); 
            SLD_startingInversion->setRange(0, 3, 3);
            SLD_startingInversion->setValue(rule_startingInversion, false);
        } 

        if (!CHK_allowNoteRepetition) {

            CHK_allowNoteRepetition = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_allowNoteRepetition, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, CHK_allowNoteRepetitionId, R"(
                <element>
                <title>Note Repetition</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_allowNoteRepetition->setX_Expr("${PARENT.LEFT}");
            CHK_allowNoteRepetition->setY_Expr("${"+SLD_startingInversionId+".BOTTOM}+${PADDING}"); 
            CHK_allowNoteRepetition->setValue(rule_allowNoteRepetition, false, false);
        }

        if (!CHK_exactOctaveMatch) {

            CHK_exactOctaveMatch = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_exactOctaveMatch, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, CHK_exactOctaveMatchId, R"(
                <element>
                <title>Exact Octave Match</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_exactOctaveMatch->setX_Expr("${PARENT.LEFT}");
            CHK_exactOctaveMatch->setY_Expr("${"+CHK_allowNoteRepetitionId+".BOTTOM}+${PADDING}"); 
            CHK_exactOctaveMatch->setValue(rule_exactOctaveMatch, false, false);
            CHK_exactOctaveMatch->setTitleWidth(250);
        }          

        if (!CHK_showExtendedNoteNames) {

            CHK_showExtendedNoteNames = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_showExtendedNoteNames, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, CHK_showExtendedNoteNamesId, R"(
                <element>
                <title>Extended Note Names</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_showExtendedNoteNames->setX_Expr("${PARENT.LEFT}");
            CHK_showExtendedNoteNames->setY_Expr("${"+CHK_exactOctaveMatchId+".BOTTOM}+${PADDING}"); 
            CHK_showExtendedNoteNames->setValue(rule_showExtendedNoteNames, false, false);
            CHK_showExtendedNoteNames->setTitleWidth(250);
        }                               



        if (!CHK_strictExtendedNotes) {

            CHK_strictExtendedNotes = dynamic_cast<Aquamarine::WidgetElmCheckbox*>(addOrLoadWidgetElement(CHK_strictExtendedNotes, Aquamarine::WIDGET_ELM_CLASS::CHECKBOX, CHK_strictExtendedNotesId, R"(
                <element>
                <title>Strict Extended Notes</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            CHK_strictExtendedNotes->setX_Expr("${PARENT.LEFT}");
            CHK_strictExtendedNotes->setY_Expr("${"+CHK_showExtendedNoteNamesId+".BOTTOM}+${PADDING}"); 
            CHK_strictExtendedNotes->setValue(rule_strictExtendedNotes, false, false);
            CHK_strictExtendedNotes->setTitleWidth(250);
        }     




        if (!SLD_notesPerString) {

            SLD_notesPerString = dynamic_cast<Aquamarine::WidgetElmSlider*>(addOrLoadWidgetElement(SLD_notesPerString, Aquamarine::WIDGET_ELM_CLASS::SLIDER, SLD_notesPerStringId, R"(
                <element>
                <title>Notes per string</title>
                <bounds widthExpr="${PARENT.USABLE_WIDTH} - ${PADDING}*2" />
                </element>
                )"));

            SLD_notesPerString->setX_Expr("${PARENT.LEFT}");
            SLD_notesPerString->setY_Expr("${"+CHK_strictExtendedNotesId+".BOTTOM}+${PADDING}"); 
            SLD_notesPerString->setRange(1, 20, 19);
            SLD_notesPerString->setValue(rule_notesPerString, false);
        } 

       if (title == "") title = Aquamarine::Shared::lang("CHORD_RULES");
       setTitle(title);
    }
    

};