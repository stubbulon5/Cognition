
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "uiVizWidgetKeyPicker.h"


class uiVizWidgetKeyPickerPopout : public uiVizWidgetKeyPicker {
public:
    uiVizWidgetKeyPickerPopout(string persistentId, string widgetXML) : uiVizWidgetKeyPicker(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        uiVizWidgetKeyPicker::loadState(widgetXML);
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = uiVizWidgetKeyPicker::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~uiVizWidgetKeyPickerPopout() {

        if (getkeyPicker())
            ofRemoveListener(getkeyPicker()->keySelected, this, &uiVizWidgetKeyPickerPopout::onKeyPickerMenuKeySelected);            
         
    };    

    uiVizWidgetKeyPicker* getkeyPicker() {
        return popout;
    }

    virtual void setSelectedKey(vizNote val) override {

        if (getSelectedKey().getNoteName() != val.getNoteName()) {
            uiVizWidgetKeyPicker::setSelectedKey(val);
            getkeyPicker()->setSelectedKey(val);
            getkeyPicker()->setNeedsUpdate(true);
            setNeedsUpdate(true); 
        }
    } 

    void onKeyPickerMenuKeySelected(uiVizNoteSelectedArgs &args) {
        uiVizWidgetKeyPicker::setSelectedKey(args.note);
        setNeedsUpdate(true); 
        if(!getkeyPicker()->getIsWidgetPinned()) getkeyPicker()->closeThisWidget();
    }  


private:
    uiVizWidgetKeyPicker *popout = nullptr;
  
    void initWidget() override {
        setIsMinimized(true);
        if (!popout) {
            popout = new uiVizWidgetKeyPicker(getPersistentId() + "_KEY_PICKER", R"(
                    <widget>
                        <bounds width="200" height="200" />
                    </widget>
                    )");

            popout->setTitleStyle(TitleStyle::BOTTOM_STATIC);
            popout->setShowWidgetPin(true);

            Aquamarine::uiVizWidgetManager::addWidgetForPopout(*popout, getWidgetId(), false);

            this->handleMousePressed([this](ofMouseEventArgs e) {
                getkeyPicker()->popoutFrom(this, PopoutDirection::DOWN);
            });   

            ofAddListener(getkeyPicker()->keySelected, this, &uiVizWidgetKeyPickerPopout::onKeyPickerMenuKeySelected);
        }
    }

};