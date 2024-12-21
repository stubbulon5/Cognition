
#pragma once
#include "ofxAquamarine.h"
#include "uiVizWidgetKeyPicker.h"
#include "uiVizWidgetScaleTable.h"
#include "uiVizWidgetChordDesigner.h"


class uiVizWidgetMusicalComposerSidebar : public uiVizWidgetMusical {
public:
    uiVizWidgetMusicalComposerSidebar(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
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
        ofxXmlSettings settings = uiVizWidgetMusical::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_MUSICAL_COMPOSER, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~uiVizWidgetMusicalComposerSidebar() {
         
    };

    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        string event = args.getFullEventName();
    }


protected:

private:
    Aquamarine::uiVizWidgetTable *tablePartPicker = nullptr;
    Aquamarine::uiVizWidgetTable *tableVariatPicker = nullptr;
    uiVizWidgetKeyPicker *keyPicker = nullptr;
    uiVizWidgetScaleTable *scaleTable = nullptr;
    uiVizWidgetChordDesigner *chordDesigner = nullptr; 


    Aquamarine::uiVizWidgetElmButton *b1 = nullptr;
    Aquamarine::uiVizWidgetElmButton *b2 = nullptr;
    Aquamarine::uiVizWidgetElmButton *b3 = nullptr;

    void initWidget() override {

        if (!tablePartPicker) {

           tablePartPicker = new Aquamarine::uiVizWidgetTable("TABLE_PART_PICKER", R"(
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

           scaleTable = new uiVizWidgetScaleTable(getPersistentId() + "_SCALE_PICKER", R"(
                <widget>
                    <bounds width="300" height="200" maxWidth="300" maxHeight="200" />
                    <properties autoResizeHeight="1" autoResizeWidth="1"/>
                </widget>
                )");

            Aquamarine::uiVizWidgetManager::addWidgetForPopout(*scaleTable, getWidgetId(), false);

        }   

        if (!chordDesigner) {

           chordDesigner = new uiVizWidgetChordDesigner(getPersistentId() + "_CHORD_DESIGNER", R"(
                <widget>
                    <bounds width="300" height="200" maxWidth="300" maxHeight="200" />
                    <properties autoResizeHeight="1" autoResizeWidth="1"/>
                </widget>
                )");

            Aquamarine::uiVizWidgetManager::addWidgetForPopout(*chordDesigner, getWidgetId(), true);

        }

        if (!keyPicker) {
           keyPicker = new uiVizWidgetKeyPicker(getPersistentId() + "_KEY_PICKER", R"(
                <widget>
                    <bounds width="200" height="200" />
                </widget>
                )");

             Aquamarine::uiVizWidgetManager::addWidgetForPopout(*keyPicker, getWidgetId(), true);
        }                                 

        if(!b1) {
            b1 = dynamic_cast<Aquamarine::uiVizWidgetElmButton*>(addOrLoadWidgetElement(b1, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B1", R"(
                <element>
                <bounds x="0" y="50" />
                </element>
                )"));

            b1->setTitle("Key");
            b1->setPopoutWidget(keyPicker, PopoutDirection::UP);

        }

        if(!b2) {
            b2 = dynamic_cast<Aquamarine::uiVizWidgetElmButton*>(addOrLoadWidgetElement(b2, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B2", R"(
                <element>
                <bounds x="150" y="150" />
                </element>
                )"));

            b2->setTitle("Scale");
            b2->setPopoutWidget(scaleTable, PopoutDirection::RIGHT);

        }

        if(!b3) {
            b3 = dynamic_cast<Aquamarine::uiVizWidgetElmButton*>(addOrLoadWidgetElement(b3, Aquamarine::WIDGET_ELM_CLASS::BUTTON, "B3", R"(
                <element>
                <bounds x="150" y="250" />
                </element>
                )"));

            b3->setTitle("Chord");
            b3->setPopoutWidget(chordDesigner, PopoutDirection::RIGHT);

        }        


    }
    

};