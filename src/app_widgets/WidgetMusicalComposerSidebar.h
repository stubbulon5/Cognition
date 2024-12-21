
#pragma once
#include "ofxAquamarine.h"
#include "WidgetKeyPicker.h"
#include "WidgetScaleTable.h"
#include "WidgetChordDesigner.h"


class WidgetMusicalComposerSidebar : public WidgetMusical {
public:
    WidgetMusicalComposerSidebar(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = WidgetMusical::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~WidgetMusicalComposerSidebar() {
         
    };

    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override {
        string event = args.getFullEventName();
    }


protected:

private:
    Aquamarine::WidgetTable *tablePartPicker = nullptr;
    Aquamarine::WidgetTable *tableVariatPicker = nullptr;
    WidgetKeyPicker *keyPicker = nullptr;
    WidgetScaleTable *scaleTable = nullptr;
    WidgetChordDesigner *chordDesigner = nullptr; 


    Aquamarine::WidgetElmButton *b1 = nullptr;
    Aquamarine::WidgetElmButton *b2 = nullptr;
    Aquamarine::WidgetElmButton *b3 = nullptr;

    void initWidget() override {

        if (!tablePartPicker) {

           tablePartPicker = new Aquamarine::WidgetTable("TABLE_PART_PICKER", R"(
                <widget><bounds width="200" height="150" />
                    <properties autoResizeHeight="1" autoResizeWidth="1">
                        <header>
                            <cell>Part</cell>
                        </header>
                    </properties>
                </widget>
                )");

        //  addChildWidget(*tablePartPicker, true);   
           // tablePartPicker->popoutFrom(200, 300, PopoutDirection::RIGHT);   
            

        }

        if (!scaleTable) {

           scaleTable = new WidgetScaleTable(getPersistentId() + "_SCALE_PICKER", R"(
                <widget>
                    <bounds width="300" height="200" maxWidth="300" maxHeight="200" />
                    <properties autoResizeHeight="1" autoResizeWidth="1"/>
                </widget>
                )");

            Aquamarine::WidgetManager::addWidgetForPopout(*scaleTable, getWidgetId(), false);

        }   

        if (!chordDesigner) {

           chordDesigner = new WidgetChordDesigner(getPersistentId() + "_CHORD_DESIGNER", R"(
                <widget>
                    <bounds width="300" height="200" maxWidth="300" maxHeight="200" />
                    <properties autoResizeHeight="1" autoResizeWidth="1"/>
                </widget>
                )");

            Aquamarine::WidgetManager::addWidgetForPopout(*chordDesigner, getWidgetId(), true);

        }

        if (!keyPicker) {
           keyPicker = new WidgetKeyPicker(getPersistentId() + "_KEY_PICKER", R"(
                <widget>
                    <bounds width="200" height="200" />
                </widget>
                )");

             Aquamarine::WidgetManager::addWidgetForPopout(*keyPicker, getWidgetId(), true);
        }                                 

        if(!b1) {
            b1 = dynamic_cast<Aquamarine::WidgetElmButton*>(addOrLoadWidgetElement(b1, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B1", R"(
                <element>
                <bounds x="0" y="50" />
                </element>
                )"));

            b1->setTitle("Key");
            b1->setPopoutWidget(keyPicker, PopoutDirection::UP);

        }

        if(!b2) {
            b2 = dynamic_cast<Aquamarine::WidgetElmButton*>(addOrLoadWidgetElement(b2, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B2", R"(
                <element>
                <bounds x="150" y="150" />
                </element>
                )"));

            b2->setTitle("Scale");
            b2->setPopoutWidget(scaleTable, PopoutDirection::RIGHT);

        }

        if(!b3) {
            b3 = dynamic_cast<Aquamarine::WidgetElmButton*>(addOrLoadWidgetElement(b3, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B3", R"(
                <element>
                <bounds x="150" y="250" />
                </element>
                )"));

            b3->setTitle("Chord");
            b3->setPopoutWidget(chordDesigner, PopoutDirection::RIGHT);

        }        


    }
    

};