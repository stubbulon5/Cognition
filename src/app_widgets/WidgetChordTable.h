//
//  WidgetTable.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"

class WidgetChordTable : public Aquamarine::WidgetTable {
public:
    WidgetChordTable(string persistentId, string widgetXML) : WidgetTable(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);        
    }

    virtual bool loadState(string widgetXML) override {
        WidgetTable::loadState(widgetXML);
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
    vector<string> scales = MusicTheory::Scale::getAllScalesData();

        Aquamarine::WidgetTableRow headerRow = Aquamarine::WidgetTableRow("Header", {
            Aquamarine::WidgetTableCell("chord", "Chord", "center")
        });

        vector<string> chords = MusicTheory::Chord::getAllKnownChords();
        
        vector<Aquamarine::WidgetTableRow> tableRows = vector<Aquamarine::WidgetTableRow>();
        
        int rowIndex=0;
        for (string chord:chords) {
            tableRows.push_back(
                Aquamarine::WidgetTableRow(chord, {
                    Aquamarine::WidgetTableCell("", chord, "center")
                })
            );
            rowIndex++;
        }

        setHeaderRow(headerRow);
        setTableRows(tableRows);

        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_SCALE_TABLE, 0);
        return mWidgetXML;
    }

    virtual ~WidgetChordTable() {
    };
 

    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        WidgetTable::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED) {
                Aquamarine::WidgetTableRow* eventRow = getTableRow(args.eventXML);
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