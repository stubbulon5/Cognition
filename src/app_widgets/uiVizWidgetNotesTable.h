//
//  uiVizWidgetNotesTable.h
//  bloom-macos
//
//
#pragma once
#include "uiVizWidgetTable.h"

class uiVizWidgetNotesTable : public Aquamarine::uiVizWidgetTable {
public:
    uiVizWidgetNotesTable(string persistentId, string widgetXML) : uiVizWidgetTable(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);        
    }

    virtual bool loadState(string widgetXML) override {
        uiVizWidgetTable::loadState(widgetXML);
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }

        Aquamarine::uiVizWidgetTableRow headerRow = Aquamarine::uiVizWidgetTableRow("Header", {
            Aquamarine::uiVizWidgetTableCell("note", "Note", "center"),
            Aquamarine::uiVizWidgetTableCell("octave", "Octave", "center")
        });

        vector<Aquamarine::uiVizWidgetTableRow> tableRows = vector<Aquamarine::uiVizWidgetTableRow>();
        
        int rowIndex=0;
        for (int octave=0; octave<=5; octave++) {
            string strOctave = ofToString(octave);

            for (string note:vizTheory::getChromaticScaleSharps()) {
                tableRows.push_back(
                    Aquamarine::uiVizWidgetTableRow(note + "_" + strOctave, {
                        Aquamarine::uiVizWidgetTableCell(note, note, "center"),
                        Aquamarine::uiVizWidgetTableCell(strOctave, strOctave, "center")
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
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE, 0);
        return mWidgetXML;
    }

    virtual ~uiVizWidgetNotesTable() {
    };


    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        uiVizWidgetTable::onWidgetEventReceived(args);
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED) {
                vizNote note = getSelectedNotes()[0];
                setSelectedNote(note, false, false);
                note.audition(vizTheory::GeneralMidiInstrument::Acoustic_Grand_Piano);
            }
        }
    }

    void setSelectedNote(vizNote &note, bool normalize, bool scrollToSelection) {
        selectRowByKey(note.getNoteName() + "_" + ofToString(note.getNoteOctave()), scrollToSelection, false);
        setDragData(note.getXML());    
        // cout << note.getXML();
    }

    vector<vizNote> getSelectedNotes() {
        if (getSelectedRows().size() > 0) {
            Aquamarine::uiVizWidgetTableRow row = getSelectedRows()[0];
            Aquamarine::uiVizWidgetTableCell cellNote = row.cells[0];
            Aquamarine::uiVizWidgetTableCell cellOctave = row.cells[1];
            vizNote note(cellNote.key, ofToInt(cellOctave.key), 1);
            return {note};
        }
        return {};
    }    



private:
    shared_ptr<ofxSmartFont> font;

    void initWidget() override {
        setIsAutoResizeToContentsWidth(true);
        setIsAutoResizeToContentsHeight(false);
        setHeight(400);
    }

};