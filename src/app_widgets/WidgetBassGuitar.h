
#pragma once
#include "ofxAquamarine.h"
#include "WidgetStringedInstrument.h"

//------------------------------ Bass Guitar fretboard --------------------------------

/****************************************************icons******************************


 ***********************************************************************************/

class WidgetBassGuitar : public WidgetStringedInstrument {

public:

    WidgetBassGuitar(string persistentId, string widgetXML) : WidgetStringedInstrument(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        WidgetStringedInstrument::loadState(widgetXML);

        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }

        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = WidgetStringedInstrument::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_GUITAR, 0);
        return settings;
    }

    virtual ~WidgetBassGuitar() {
    }

    void update(Aquamarine::WidgetContext context) override {
        WidgetStringedInstrument::update(context);
    }

    void draw(Aquamarine::WidgetContext context) override {
        WidgetStringedInstrument::draw(context);
    }

    void updateMinimized() override {
        WidgetStringedInstrument::updateMinimized();
    }

    void drawMinimized() override {
        WidgetStringedInstrument::drawMinimized();
    }

    vector<vector<WidgetStringedInstrumentString>> getTunings() override {

        switch(getNumStrings()) {
            case 6:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("B", 0, 0, vector<string>{"Standard"}), 6),
                        WidgetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{""}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3)
                    }
                };

            case 5:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("B", 0, 0, vector<string>{"Standard"}), 6),
                        WidgetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{""}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3)
                    }
                };

            default:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{"Standard"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3)
                    }

                };
        }
    }

    virtual float getFretWidthToHeightRatioFull() override {
            switch(getTunings()[0].size()) {
                default:
                    return 6.0f;
                    break;
            }
    }      

private:
    bool isInitial = true;

    void initWidget() override {

        if (isInitial) {
            setNumStrings(4);
            isInitial = false;
            setFretWidthToHeightRatio(getFretWidthToHeightRatioFull());
            setStrings(getTunings()[0], true);
            initMenu();
            setGMInstrumentNumber(vizTheory::GeneralMidiInstrument::Electric_Bass_finger);
        }

    }

};


