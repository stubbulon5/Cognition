
#pragma once
#include "ofxAquamarine.h"
#include "WidgetKeyPicker.h"


class WidgetKeyPickerPopout : public WidgetKeyPicker {
public:
    WidgetKeyPickerPopout(string persistentId, string widgetXML) : WidgetKeyPicker(persistentId, widgetXML) {
        initWidget();
        loadState(widgetXML);
    }

    virtual bool loadState(string widgetXML) override {
        WidgetKeyPicker::loadState(widgetXML);
        ofxXmlSettings settings = ofxXmlSettings();
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        return true;
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings settings = WidgetKeyPicker::saveState();
        settings.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_KEY_PICKER_POPOUT, 0);

        settings.pushTag("widget");
        settings.pushTag("properties");

        // TODO
        
        settings.popTag(); // properties
        settings.popTag(); // widget
        
        return settings;
    }

    virtual ~WidgetKeyPickerPopout() {

        if (getkeyPicker())
            ofRemoveListener(getkeyPicker()->keySelected, this, &WidgetKeyPickerPopout::onKeyPickerMenuKeySelected);            
         
    };    

    WidgetKeyPicker* getkeyPicker() {
        return popout;
    }

    virtual void setSelectedKey(vizNote val) override {

        if (getSelectedKey().getNoteName() != val.getNoteName()) {
            WidgetKeyPicker::setSelectedKey(val);
            getkeyPicker()->setSelectedKey(val);
            getkeyPicker()->setNeedsUpdate(true);
            setNeedsUpdate(true); 
        }
    } 

    void onKeyPickerMenuKeySelected(vizNoteSelectedArgs &args) {
        WidgetKeyPicker::setSelectedKey(args.note);
        setNeedsUpdate(true); 
        if(!getkeyPicker()->getIsWidgetPinned()) getkeyPicker()->closeThisWidget();
    }  


private:
    WidgetKeyPicker *popout = nullptr;
  
    void initWidget() override {
        setIsMinimized(true);
        if (!popout) {
            popout = new WidgetKeyPicker(getPersistentId() + "_KEY_PICKER", R"(
                    <widget>
                        <bounds width="200" height="200" />
                    </widget>
                    )");

            popout->setTitleStyle(TitleStyle::BOTTOM_STATIC);
            popout->setShowWidgetPin(true);

            Aquamarine::WidgetManager::addWidgetForPopout(*popout, getWidgetId(), false);

            this->handleMousePressed([this](ofMouseEventArgs e) {
                getkeyPicker()->popoutFrom(this, PopoutDirection::DOWN);
            });   

            ofAddListener(getkeyPicker()->keySelected, this, &WidgetKeyPickerPopout::onKeyPickerMenuKeySelected);
        }
    }

};