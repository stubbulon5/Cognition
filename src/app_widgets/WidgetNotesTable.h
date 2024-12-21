//
//  WidgetNotesTable.h
//  bloom-macos
//
//
#pragma once
#include "ofxAquamarine.h"

class WidgetNotesTable : public Aquamarine::WidgetTable {
public:
    WidgetNotesTable(string persistentId, string widgetXML) : WidgetTable(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);        
    }

    virtual bool loadState(string widgetXML) override {
        WidgetTable::loadState(widgetXML);
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }

        Aquamarine::WidgetTableRow headerRow = Aquamarine::WidgetTableRow("Header", {
            Aquamarine::WidgetTableCell("note", "Note", "center"),
            Aquamarine::WidgetTableCell("octave", "Octave", "center")
        });

        vector<Aquamarine::WidgetTableRow> tableRows = vector<Aquamarine::WidgetTableRow>();
        
        int rowIndex=0;
        for (int octave=0; octave<=5; octave++) {
            string strOctave = ofToString(octave);

            for (string note:vizTheory::getChromaticScaleSharps()) {
                tableRows.push_back(
                    Aquamarine::WidgetTableRow(note + "_" + strOctave, {
                        Aquamarine::WidgetTableCell(note, note, "center"),
                        Aquamarine::WidgetTableCell(strOctave, strOctave, "center")
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
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_NOTES_TABLE, 0);
        return mWidgetXML;
    }

    virtual ~WidgetNotesTable() {
    };


    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        WidgetTable::onWidgetEventReceived(args);
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
            Aquamarine::WidgetTableRow row = getSelectedRows()[0];
            Aquamarine::WidgetTableCell cellNote = row.cells[0];
            Aquamarine::WidgetTableCell cellOctave = row.cells[1];
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