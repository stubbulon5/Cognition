#pragma once
#include "ofxAquamarine.h"
#include "AppWidgets.h"
#include "Icon.h"

namespace Aquamarine
{

    class AppCognition : public App
    {
    public:
        AppCognition() : App(
                             "cognition",
                             APP_CONSTANTS::getIconCacheMap(1.0),
                             "1.0.0",
                             "jam",
                             APP_CONSTANTS::DEFAULT_LANGUAGE_XML) {}

        // map<string, Icon *> getCustomIcons(float scale) override
        // {
        //     map<string, Aquamarine::Icon *> iconCacheMap;

        //     int iconSizeFromFile = 48; // The files we are sourcing are sized at 48x48px

        //     int iconSizeReg = 18;
        //     int iconSizeMed = 27;
        //     int iconSizeLrg = 40;

        //     float iconSizeRegScale = ((float)iconSizeReg / (float)iconSizeFromFile) * (float)scale; // When scale is 1, this is the regular size
        //     float iconSizeMedScale = (iconSizeMed / (float)iconSizeFromFile) * (float)scale;
        //     float iconSizeLrgScale = (iconSizeLrg / (float)iconSizeFromFile) * (float)scale;

        //     int iconSizeRegScaledSize = iconSizeFromFile * (float)iconSizeRegScale;
        //     int iconSizeMedScaledSize = iconSizeFromFile * (float)iconSizeMedScale;
        //     int iconSizeLrgScaledSize = iconSizeFromFile * (float)iconSizeLrgScale;

        //     iconCacheMap["MED_CONTENT_THEORY_LABEL"] = new Aquamarine::Icon("ui/svg/ic_info_outline_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
        //     iconCacheMap["MED_CONTENT_THEORY_COLOR"] = new Aquamarine::Icon("ui/svg/ic_color_lens_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
        //     iconCacheMap["MED_CONTENT_THEORY_SCALE"] = new Aquamarine::Icon("ui/svg/ic_tonality_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
        //     iconCacheMap["MED_CONTENT_SETTINGS"] = new Aquamarine::Icon("ui/svg/ic_settings_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::WIDGET_SETTINGS);
        //     iconCacheMap["MED_CONTENT_VIEW"] = new Aquamarine::Icon("ui/svg/ic_view_compact_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, 0);
        //     iconCacheMap["MED_ADD_CIRCLE"] = new Aquamarine::Icon("ui/svg/ic_add_circle_outline_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::ADD_CIRCLE);
        //     iconCacheMap["MED_MENU"] = new Aquamarine::Icon("ui/svg/ic_apps_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MENU);
        //     iconCacheMap["MED_KEY"] = new Aquamarine::Icon("ui/svg/ic_vpn_key_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
        //     iconCacheMap["MED_CONTENT_RULES"] = new Aquamarine::Icon("ui/svg/ic_tune_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
        //     iconCacheMap["MED_CONTENT_EDIT"] = new Aquamarine::Icon("ui/svg/ic_edit_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);
        //     iconCacheMap["MED_CONTENT_TICK"] = new Aquamarine::Icon("ui/svg/ic_check_" + ofToString(iconSizeFromFile) + "px.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, Aquamarine::IconCache::IconTag::MED_KEY);

        //     iconCacheMap["MED_INST_ELECTRIC_GUIT"] = new Aquamarine::Icon("ui/music-icons/electric-guitar.svg", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, 0);

        //     /* Icon images for Widgets - If a custom image / ico is required for a widget, specify it here */
        //     iconCacheMap["WidgetGuitar"] = new Aquamarine::Icon("ui/images/WidgetGuitar.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_GUITAR);
        //     /*
        //         iconCacheMap["WidgetChordDesigner"] = new Aquamarine::Icon("ui/images/WidgetChordDesigner.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_DESIGNER);
        //         iconCacheMap["WidgetChordWheel"] = new Aquamarine::Icon("ui/images/WidgetChordWheel.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_WHEEL);
        //         iconCacheMap["WidgetKeyPicker"] = new Aquamarine::Icon("ui/images/WidgetKeyPicker.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_KEY_PICKER);
        //         iconCacheMap["WidgetScalePicker"] = new Aquamarine::Icon("ui/images/WidgetScalePicker.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_SCALE_PICKER);
        //     */
        //     iconCacheMap["WidgetChordBucket"] = new Aquamarine::Icon("ui/images/WidgetChordBucket.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);
        //     iconCacheMap["MED_CONTENT_BUCKET"] = new Aquamarine::Icon("ui/images/bucket.png", Aquamarine::Coord::vizBounds(0, 0, iconSizeMedScaledSize, iconSizeMedScaledSize), (float)iconSizeMedScale, Aquamarine::Icon::IconSize::MEDIUM, ofColor::white, APP_CONSTANTS::ICON_WIDGET_CLASS_CHORD_BUCKET);

        //     return iconCacheMap;
        // }

        virtual widget_map_type &getRegisteredWidgets() override
        {
            return widgetClassMap;
        }

        void registerCustomWidgets() override
        {

            // registerWidgetType<WidgetMusical>("WidgetMusical");
            // registerWidgetType<WidgetEventListenerMusical>("WidgetEventListenerMusical");
            // registerWidgetType<WidgetMusicalComposer>("WidgetMusicalComposer");
            // registerWidgetType<WidgetChordWheel>("WidgetChordWheel");
            // registerWidgetType<WidgetChordWheelForKey>("WidgetChordWheelForKey");
            // registerWidgetType<WidgetChordProgression>("WidgetChordProgression");
            // registerWidgetType<WidgetChordBucket>("WidgetChordBucket");
            // registerWidgetType<WidgetChordBucketSuggester>("WidgetChordBucketSuggester");
            // registerWidgetType<WidgetChordDesigner>("WidgetChordDesigner");
            // registerWidgetType<WidgetChordRules>("WidgetChordRules");
            // registerWidgetType<WidgetScalePicker>("WidgetScalePicker");
            // registerWidgetType<WidgetScaleTable>("WidgetScaleTable");
            // registerWidgetType<WidgetChordTable>("WidgetChordTable");
            // registerWidgetType<WidgetNotesTable>("WidgetNotesTable");
            // registerWidgetType<WidgetKeyPicker>("WidgetKeyPicker");
            // registerWidgetType<WidgetKeyPickerPopout>("WidgetKeyPickerPopout");
            // registerWidgetType<WidgetStringedInstrument>("WidgetStringedInstrument");
            // registerWidgetType<WidgetGuitar>("WidgetGuitar");
            // registerWidgetType<WidgetBassGuitar>("WidgetBassGuitar");
            // registerWidgetType<WidgetTutor>("WidgetTutor");
        //    registerWidgetType<WidgetAbout>("WidgetAbout");

            // registerWidgetType<WidgetUnitTests>("WidgetUnitTests");



// this doesn't even execute, but sheers fact it's "referenced" it crashes execution!!
// using static registration shows linking issues

            // registerWidgetType<WidgetMainMenu>("WidgetMainMenu");
            // registerWidgetType<WidgetLicence>("WidgetLicence");
            // registerWidgetType<WidgetOmniMenu>("WidgetOmniMenu");
            // registerWidgetType<WidgetOmniMenuSearchResults>("WidgetOmniMenuSearchResults");
            // registerWidgetType<WidgetOmniMenuLinks>("WidgetOmniMenuLinks");
            // registerWidgetType<WidgetGetStarted>("WidgetGetStarted");
            // registerWidgetType<WidgetNotifications>("WidgetNotifications");
        }

    private:
        widget_map_type widgetClassMap;
    };

};