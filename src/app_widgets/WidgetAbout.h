//
//  WidgetChordWheel.h
//  bloom-macos
//
//
#pragma once

namespace Aquamarine
{

    class WidgetAbout : public Widget
    {

    public:
        WidgetAbout(string persistentId, string widgetXML) : Widget(persistentId, widgetXML)
        {
            initWidget();
            loadState(widgetXML);
        }

        virtual bool loadState(string widgetXML) override
        {
            Widget::loadState(widgetXML);

            ofxXmlSettings widgetSettings = ofxXmlSettings();
            if (!widgetSettings.loadFromBuffer(widgetXML.c_str()))
            {
                return false;
            }

            return true;
        }

        virtual void onChildWidgetsLoaded() override
        {
            Widget *w = getChildWidgetByPersistentId("ABOUT_TAB_TEXT_HOLDER");
            if (w)
            {
                WidgetElmTextarea *TXT_ABOUT = w->getTextarea("TXT_ABOUT");
                if (TXT_ABOUT)
                {

                }
            }

            if (!loaded)
            {
                ABOUT_TABS = dynamic_cast<WidgetMenuCollection *>(WidgetManager::getWidgetByPersistentId(this, "ABOUT_TABS"));
                ABOUT_TAB_ATTRIBUTIONS = dynamic_cast<WidgetTable *>(WidgetManager::getWidgetByPersistentId(this, "ABOUT_TAB_ATTRIBUTIONS"));
            }
        }

        virtual ofxXmlSettings saveState() override
        {
            ofxXmlSettings mWidgetXML = Widget::saveState();
            mWidgetXML.setAttribute("widget", "class", "WidgetAbout", 0);
            return mWidgetXML;
        }

        virtual ~WidgetAbout()
        {
            // ofRemoveListener(ABOUT_TABS->widgetEventReceived, this, &WidgetAbout::onAboutTabsEventReceived);
        }

        virtual void onWidgetEventReceived(WidgetEventArgs &args) override
        {
            string parentWidgetId = args.sender.getParentPersistentId();
            string event = args.getFullEventName();

            if (args.sender.matchesWidgetOrParent(ABOUT_TAB_ATTRIBUTIONS))
            {
                // cout << "zzz";
                // add content
            }
            else if (args.sender.matchesWidgetOrChildOf(this))
            {
                if (event == "OK." + WIDGET_EVENT::CLICK)
                {
                    closeThisWidget();
                }
            }
        }

    private:
        WidgetMenuCollection *ABOUT_TABS;
        WidgetTable *ABOUT_TAB_ATTRIBUTIONS;
        bool loaded = false;

        void initWidget() override
        {
        }
    };

}