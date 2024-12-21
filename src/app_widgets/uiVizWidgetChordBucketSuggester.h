//
//  uiVizWidgetChordBucketSuggester_h
//  bloom-macos
//
//
#pragma once
#include "uiVizWidgetChordBucket.h"

class uiVizWidgetChordBucketSuggester : public uiVizWidgetChordBucket
{

public:
    uiVizWidgetChordBucketSuggester(string persistentId, string widgetXML) : uiVizWidgetChordBucket(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {    
        uiVizWidgetChordBucket::loadState(widgetXML);
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetChordBucket::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_CHORD_BUCKET_SUGGESTER, 0);        
        return mWidgetXML;
    }

    virtual ~uiVizWidgetChordBucketSuggester() {
        ofRemoveListener(scalePicker->noteSelected, this, &uiVizWidgetChordBucketSuggester::onScalePickerNoteSelected);

    }
    

    virtual void setSelectedScale(vizScale val, bool includeInstrumentRules) override {
        clearSelectedChords();
        uiVizWidgetChordBucket::setSelectedScale(val, includeInstrumentRules);
        setSelectedKey(val.getKey());

        vector<vizChord> chords = vizScale::getDiatonicChordsForScale(val.getKey().getNoteName(), val.getName());
        
        for (vizChord chord:chords) {
            addSelectedChord(chord, false, false);
        }

        setTitle(ofToString(getSelectedChordsSize()) + " chords from " + val.getKey().getNoteName() + " "  + val.getName());

        setNeedsUpdate(true);
//yodo : add multiple scale selectors
    }

    void onScalePickerNoteSelected(uiVizNoteSelectedArgs &args) {
        vizScale scale = vizScale(scalePicker->getSelectedKey().getNoteName(), scalePicker->getCalculatedScaleName(), 3);
        setSelectedScale(scale, true);
    }

private:
    uiVizWidgetScalePicker *scalePicker = nullptr;

    void initWidget() override {
        setTitle(Aquamarine::Shared::lang("CHORD_BUCKET_SUGGESTER"));

        if (!scalePicker)
        {

            scalePicker = new uiVizWidgetScalePicker(
                getWidgetId() + "_SCALE_PICKER",R"(
                <widget>
                    <bounds widthExpr="100" heightExpr="100" xExpr="${PARENT.ABSOLUTE_USABLE_X}" yExpr="${PARENT.ABSOLUTE_USABLE_Y}"/><appearance/></widget>
                </widget>
                )");

            addChildWidget(*scalePicker, true); 
            ofAddListener(scalePicker->noteSelected, this, &uiVizWidgetChordBucketSuggester::onScalePickerNoteSelected);
            //ofAddListener(scalePicker->addSelectedScaleByName, this, &uiVizWidgetOmniMenuLinks::onMenuItemSelected);  
            // todo add scale name in text ... (label)
            // bug - when loading state ...

        }
    }    

};
