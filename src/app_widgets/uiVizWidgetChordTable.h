//
//  uiVizWidgetTable.h
//  bloom-macos
//
//
#pragma once
#include "uiVizWidgetTable.h"

class uiVizWidgetChordTable : public uiVizWidgetTable {
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

        uiVizWidgetTableRow headerRow = uiVizWidgetTableRow("Header", {
            uiVizWidgetTableCell("chord", "Chord", "center")
        });

        vector<string> chords = MusicTheory::Chord::getAllKnownChords();
        
        vector<uiVizWidgetTableRow> tableRows = vector<uiVizWidgetTableRow>();
        
        int rowIndex=0;
        for (string chord:chords) {
            tableRows.push_back(
                uiVizWidgetTableRow(chord, {
                    uiVizWidgetTableCell("", chord, "center")
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
 

    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
        uiVizWidgetTable::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == WIDGET_EVENT::TABLE_CELL_SELECTED) {
                uiVizWidgetTableRow* eventRow = getTableRow(args.eventXML);
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