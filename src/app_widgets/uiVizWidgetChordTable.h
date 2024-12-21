//
//  uiVizWidgetTable.h
//  bloom-macos
//
//
#pragma once
#include "uiVizWidgetTable.h"

class uiVizWidgetChordTable : public Aquamarine::uiVizWidgetTable {
public:
    uiVizWidgetChordTable(string persistentId, string widgetXML) : uiVizWidgetTable(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);        
    }

    virtual bool loadState(string widgetXML) override {
        uiVizWidgetTable::loadState(widgetXML);
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
    vector<string> scales = MusicTheory::Scale::getAllScalesData();

        Aquamarine::uiVizWidgetTableRow headerRow = Aquamarine::uiVizWidgetTableRow("Header", {
            Aquamarine::uiVizWidgetTableCell("chord", "Chord", "center")
        });

        vector<string> chords = MusicTheory::Chord::getAllKnownChords();
        
        vector<Aquamarine::uiVizWidgetTableRow> tableRows = vector<Aquamarine::uiVizWidgetTableRow>();
        
        int rowIndex=0;
        for (string chord:chords) {
            tableRows.push_back(
                Aquamarine::uiVizWidgetTableRow(chord, {
                    Aquamarine::uiVizWidgetTableCell("", chord, "center")
                })
            );
            rowIndex++;
        }

        setHeaderRow(headerRow);
        setTableRows(tableRows);

        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE, 0);
        return mWidgetXML;
    }

    virtual ~uiVizWidgetChordTable() {
    };
 

    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        uiVizWidgetTable::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED) {
                Aquamarine::uiVizWidgetTableRow* eventRow = getTableRow(args.eventXML);
                mSelectedChord = vizChord("C"+eventRow->key);
                setDragData(mSelectedChord.getXML());
            }
        }
    }  

    vizChord getSelectedChord() {
        return mSelectedChord;
    }


private:
    shared_ptr<ofxSmartFont> font;
    vizChord mSelectedChord;


    void initWidget() override {
        setIsAutoResizeToContentsWidth(true);
        setIsAutoResizeToContentsHeight(false);
        setHeight(400);
    }

};