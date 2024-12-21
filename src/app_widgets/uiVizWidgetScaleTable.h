//
//  uiVizWidgetTable.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"

class uiVizWidgetScaleTable : public Aquamarine::uiVizWidgetTable {
public:
    uiVizWidgetScaleTable(string persistentId, string widgetXML) : uiVizWidgetTable(persistentId, widgetXML) {
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
            Aquamarine::uiVizWidgetTableCell("scale", "Scale", "center"),
            Aquamarine::uiVizWidgetTableCell("origin", "Origin"),
            Aquamarine::uiVizWidgetTableCell("notes", "Notes"),
            Aquamarine::uiVizWidgetTableCell("numNotes", "#")
        });

        vector<Aquamarine::uiVizWidgetTableRow> tableRows = vector<Aquamarine::uiVizWidgetTableRow>();
        
        int rowIndex=0;
        for (string scale:scales) {
            vector<string> scale_parts = ofSplitString(scale, "|");

            string scaleId = "", scaleName = "", origin = "", notes = "", numNotes = "";

            scaleId = (scale_parts.size() > 0) ? scale_parts[0] : "???";
            scaleName = (scale_parts.size() > 1) ? scale_parts[1] : "???";
            origin = (scale_parts.size() > 2) ? scale_parts[2] : "???";
            notes = (scale_parts.size() > 3) ? scale_parts[3] : "???";
            numNotes = (scale_parts.size() > 4) ? scale_parts[4] : "???";

            if (scaleId != "" && scaleId != "???" && notes != "???") {

                tableRows.push_back(
                    Aquamarine::uiVizWidgetTableRow(scaleId, {
                        Aquamarine::uiVizWidgetTableCell("", scaleName, "center"),
                        Aquamarine::uiVizWidgetTableCell("", origin),
                        Aquamarine::uiVizWidgetTableCell("", notes),
                        Aquamarine::uiVizWidgetTableCell("", numNotes)
                    })
                );
                rowIndex++;
            }
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

    virtual ~uiVizWidgetScaleTable() {
    };
 

    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        uiVizWidgetTable::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED) {
                Aquamarine::uiVizWidgetTableRow* eventRow = getTableRow(args.eventXML);
                mSelectedScale = vizScale("C", eventRow->key, 3);
                setDragData(mSelectedScale.getXML());
            }
        }
    }  

    vizScale getSelectedScale() {
        return mSelectedScale;
    }


private:
    shared_ptr<ofxSmartFont> font;
    vizScale mSelectedScale;

    void initWidget() override {
        setIsAutoResizeToContentsWidth(true);
        setIsAutoResizeToContentsHeight(false);
        setHeight(400);
    }

};