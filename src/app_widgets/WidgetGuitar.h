
#pragma once
#include "ofxAquamarine.h"
#include "WidgetStringedInstrument.h"

class WidgetGuitar : public WidgetStringedInstrument {
    
public:
    
    WidgetGuitar(string persistentId, string widgetXML) : WidgetStringedInstrument(persistentId, widgetXML) {
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

    virtual ~WidgetGuitar() {
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
            case 8:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("F#", 1, 0, vector<string>{"Standard"}), 6),
                        WidgetStringedInstrumentString(vizNote("B", 1, 0, vector<string>{""}), 6),
                        WidgetStringedInstrumentString(vizNote("E", 2, 0, vector<string>{""}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("E", 4, 0, vector<string>{""}), 2)
                    }
                };
                
            case 7:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("B", 1, 0, vector<string>{"Standard"}), 6),
                        WidgetStringedInstrumentString(vizNote("E", 2, 0, vector<string>{""}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("E", 4, 0, vector<string>{""}), 2)
                    }
                };

            default:
                return {
                    {
                        WidgetStringedInstrumentString(vizNote("E", 2, 0, vector<string>{"Standard"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("E", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Drop D"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("E", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D#", 2, 0, vector<string>{"Half Step"}), 5),
                        WidgetStringedInstrumentString(vizNote("G#", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("C#", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("F#", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A#", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D#", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Whole Step Down"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("F", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("C#", 2, 0, vector<string>{"1.5 Steps Down"}), 5),
                        WidgetStringedInstrumentString(vizNote("F#", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("E", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G#", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("C#", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("C", 2, 0, vector<string>{"2 Steps Down"}), 5),
                        WidgetStringedInstrumentString(vizNote("F", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("A#", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("D#", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("C", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("C", 2, 0, vector<string>{"Drop C"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("F", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("B", 1, 0, vector<string>{"Drop B"}), 5),
                        WidgetStringedInstrumentString(vizNote("F#", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("B", 2, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("E", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G#", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("C#", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Double Drop D"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Open D"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("F#", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Open D Minor"}), 5),
                        WidgetStringedInstrumentString(vizNote("A", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("F", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Open G"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("B", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("D", 2, 0, vector<string>{"Open G Minor"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("D", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("A#", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("C", 2, 0, vector<string>{"Open C"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("E", 4, 0, vector<string>{""}), 2)
                    },
                    {
                        WidgetStringedInstrumentString(vizNote("C", 2, 0, vector<string>{"Open C Minor"}), 5),
                        WidgetStringedInstrumentString(vizNote("G", 2, 0, vector<string>{""}), 4),
                        WidgetStringedInstrumentString(vizNote("C", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("G", 3, 0, vector<string>{""}), 3),
                        WidgetStringedInstrumentString(vizNote("C", 4, 0, vector<string>{""}), 2),
                        WidgetStringedInstrumentString(vizNote("D#", 4, 0, vector<string>{""}), 2)
                    }

                    
                    
                };
        }
    }

    // todo:add bass 5 string
    // fix tuning menus when changing string numbers!
    // add tabs on menu (eg Instruments, theory, etc)

    virtual float getFretWidthToHeightRatioFull() override {
            // 4, 5 string Bass, Banjo, Mandolin, Ukelele
            switch(getTunings()[0].size()) {
                case 8:
                    return 6.0f;
                    break;
                case 7:
                    return 5.0f;
                    break;
                default:
                    return 4.1f;
                    break;
            }
    }    
    
private:

    bool isInitial = true;

    void initWidget() override {
        if (isInitial) {
            setNumStrings(6);
            isInitial = false;
            setFretWidthToHeightRatio(getFretWidthToHeightRatioFull());
            setStrings(getTunings()[0], true);
            initMenu();
            setGMInstrumentNumber(vizTheory::GeneralMidiInstrument::Electric_Guitar_jazz);
        }

    }
    
};


