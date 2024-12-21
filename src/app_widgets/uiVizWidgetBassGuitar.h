
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "uiVizWigetStringedInstrument.h"

//------------------------------ Bass Guitar fretboard --------------------------------

/****************************************************icons******************************


 ***********************************************************************************/

class uiVizWidgetBassGuitar : public uiVizWigetStringedInstrument {

public:

    uiVizWidgetBassGuitar(string persistentId, string widgetXML) : uiVizWigetStringedInstrument(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        uiVizWigetStringedInstrument::loadState(widgetXML);

        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }

        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = uiVizWigetStringedInstrument::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_GUITAR, 0);
        return settings;
    }

    virtual ~uiVizWidgetBassGuitar() {
    }

    void update(Aquamarine::uiVizWidgetContext context) override {
        uiVizWigetStringedInstrument::update(context);
    }

    void draw(Aquamarine::uiVizWidgetContext context) override {
        uiVizWigetStringedInstrument::draw(context);
    }

    void updateMinimized() override {
        uiVizWigetStringedInstrument::updateMinimized();
    }

    void drawMinimized() override {
        uiVizWigetStringedInstrument::drawMinimized();
    }

    vector<vector<uiVizWigetStringedInstrumentString>> getTunings() override {

        switch(getNumStrings()) {
            case 6:
                return {
                    {
                        uiVizWigetStringedInstrumentString(vizNote("B", 0, 0, vector<string>{"Standard"}), 6),
                        uiVizWigetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{""}), 5),
                        uiVizWigetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        uiVizWigetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        uiVizWigetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3),
                        uiVizWigetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3)
                    }
                };

            case 5:
                return {
                    {
                        uiVizWigetStringedInstrumentString(vizNote("B", 0, 0, vector<string>{"Standard"}), 6),
                        uiVizWigetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{""}), 5),
                        uiVizWigetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        uiVizWigetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        uiVizWigetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3)
                    }
                };

            default:
                return {
                    {
                        uiVizWigetStringedInstrumentString(vizNote("E", 1, 0, vector<string>{"Standard"}), 5),
                        uiVizWigetStringedInstrumentString(vizNote("A", 1, 0, vector<string>{""}), 4),
                        uiVizWigetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{""}), 3),
                        uiVizWigetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 3)
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


