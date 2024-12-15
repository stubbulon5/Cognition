//
//  uiVizWidgetMusical.h
//  bloom-macos
//
//
#pragma once

#include "uiVizWidgetMusical.h"
#include "uiVizWidgetEventListenerMusical.h"

class uiVizWidgetMusicalHelper :  public uiVizWidgetMusical {
    
public:
    uiVizWidgetMusicalHelper(string persistentId, string widgetXML) : uiVizWidgetMusical(persistentId, widgetXML) {
        init();
        loadState(widgetXML);
    }

    static uiVizWidgetEventListenerMusical* getMusicalWidgetEventListenerConfigMusical(uiVizWidgetMusical* owner) {
        if (mWidgetEventListenerConfigMusical == nullptr) {
            mWidgetEventListenerConfigMusical = new uiVizWidgetEventListenerMusical(
                getWidgetId() + "_EVENT_LISTENER_CONFIG_MUSICAL",
                "<widget ownerWidgetId='" + getWidgetId() + "'><bounds minWidth='500' minHeight='200' width='500'/><appearance /></widget>"
                );

            mWidgetEventListenerConfigMusical->setSourceEventsList(
                {
                    APP_WIDGET_EVENT::SET_SELECTED_KEY,
                    APP_WIDGET_EVENT::ADD_SELECTED_CHORD,
                    APP_WIDGET_EVENT::ADD_SELECTED_NOTE,
                    APP_WIDGET_EVENT::SET_SELECTED_SCALE,
                    APP_WIDGET_EVENT::SET_HOVERED_CHORD,
                    WIDGET_EVENT::RECEIVE_DRAG_AND_DROP_DATA,
                    WIDGET_EVENT::DRAG_AND_DROP_DATA_SET                    
                }
            );

            mWidgetEventListenerConfigMusical->setTargetEventsList(mWidgetEventListenerConfigMusical->getSourceEventsList());
            mWidgetEventListenerConfigMusical->setOwnerWidgetId(owner->getWidgetId());
        }
        return mWidgetEventListenerConfigMusical;
    };      
    
private:
    uiVizWidgetEventListenerMusical *mWidgetEventListenerConfigMusical = nullptr;
    void init() {
    }
    
};


