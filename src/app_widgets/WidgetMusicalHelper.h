//
//  WidgetMusical.h
//  bloom-macos
//
//
#pragma once

#include "WidgetMusical.h"
#include "WidgetEventListenerMusical.h"

class WidgetMusicalHelper :  public WidgetMusical {

public:
    WidgetMusicalHelper(string persistentId, string widgetXML) : WidgetMusical(persistentId, widgetXML) {
        init();
        loadState(widgetXML);
    }

    static WidgetEventListenerMusical* getWidgetEventListenerMusicalConfig(WidgetMusical* owner) {
        Widget* w = owner->getChildWidgetByPersistentId(owner->getWidgetId() + "_EVENT_LISTENER_CONFIG_MUSICAL");

        if (w != nullptr) {
            return dynamic_cast<WidgetEventListenerMusical*>(w);
        } else {
            WidgetEventListenerMusical *mWidgetEventListenerConfigMusical = new WidgetEventListenerMusical(
                owner->getWidgetId() + "_EVENT_LISTENER_CONFIG_MUSICAL",
                "<widget ownerWidgetId='" + owner->getWidgetId() + "'><bounds minWidth='500' minHeight='200' width='500'/><appearance /></widget>"
                );

            mWidgetEventListenerConfigMusical->setSourceEventsList(
                {
                    APP_WIDGET_EVENT::SET_SELECTED_KEY,
                    APP_WIDGET_EVENT::ADD_SELECTED_CHORD,
                    APP_WIDGET_EVENT::ADD_SELECTED_NOTE,
                    APP_WIDGET_EVENT::SET_SELECTED_SCALE,
                    APP_WIDGET_EVENT::SET_HOVERED_CHORD,
                    Aquamarine::WIDGET_EVENT::RECEIVE_DRAG_AND_DROP_DATA,
                    Aquamarine::WIDGET_EVENT::DRAG_AND_DROP_DATA_SET                    
                }
            );

            mWidgetEventListenerConfigMusical->setTargetEventsList(mWidgetEventListenerConfigMusical->getSourceEventsList());
            mWidgetEventListenerConfigMusical->setOwnerWidgetId(owner->getWidgetId());
            return mWidgetEventListenerConfigMusical;
        }
    };      
    
private:
    void init() {
    }
    
};


