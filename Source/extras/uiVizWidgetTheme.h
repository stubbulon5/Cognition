/*
  ==============================================================================

    uiVizWidgetTheme.h
    Created: 18 Mar 2024 7:16:56pm
    Author:  Stuart Barnes

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ofUtils.h"

class uiVizWidgetTheme {
    
public:
    
    uiVizWidgetTheme() {
    }
    
//    bool loadForWidget(uiVizWidgetTheme& fallback, string themeXML) {
//        ofxXmlSettings settings;
//        if (settings.loadFromBuffer(themeXML.c_str())) {
//            if (settings.pushTag("widget")) {
//                RoundedRectangle = settings.getAttribute("appearance", "roundedRectangle", RoundedRectangle, 0);
//                if (settings.pushTag("appearance")) {
//                    populateWidgetTheme(fallback, settings);
//                    settings.popTag(); //appearance
//                }
//                settings.popTag(); //widget
//            }
//            return true;
//        }
//        return false;
//    }
//
//    bool loadForElement(uiVizWidgetTheme& fallback, string themeXML) {
//        ofxXmlSettings settings;
//        if (settings.loadFromBuffer(themeXML.c_str())) {
//            if (settings.pushTag("element")) {
//                ElementRoundedRectangle = settings.getAttribute("appearance", "roundedRectangle", ElementRoundedRectangle, 0);
//                if (settings.pushTag("appearance")) {
//                    populateElementTheme(fallback, settings);
//                    settings.popTag(); //appearance
//                }
//                settings.popTag(); //widget
//            }
//            return true;
//        }
//        return false;
//    }
//
//    bool load(string themeXML) {
//        
//        ofxXmlSettings settings;
//        
//        if (settings.loadFromBuffer(themeXML.c_str()))  {
//            
//            Name = settings.getAttribute("theme", "name", "Unknown");
//            string boolString = ofToLower(settings.getAttribute("theme", "isDark", "false"));
//            IsDark = (boolString == "true" || boolString == "1" || boolString == "yes" || boolString == "on");
//            
//            settings.pushTag("theme");
//
//            // Widgets
//            if (settings.pushTag("widgets")) {
//                RoundedRectangle = settings.getAttribute("appearance", "roundedRectangle", RoundedRectangle, 0);
//                populateWidgetTheme(*this, settings);
//                settings.popTag(); //widgets
//            }
//            
//            // Elements
//            if (settings.pushTag("elements")) {
//                ElementRoundedRectangle = settings.getAttribute("appearance", "roundedRectangle", ElementRoundedRectangle, 0);
//                populateElementTheme(*this, settings);
//                settings.popTag(); //elemets
//            }
//            
//            settings.popTag(); //theme
//            
//            return true;
//        }
//        return false;
//    }
//
//    void populateWidgetTheme(uiVizWidgetTheme& fallback, ofxXmlSettings& settings) {
//        
//        setWidgetColor(settings.getAttribute("widgetColor", "color", ""));
//        setWidgetContentColor(settings.getAttribute("widgetContentColor", "color", ""));
//
//        setWidgetAccent1Color(settings.getAttribute("widgetAccentColor", "color1", ""));
//        setWidgetAccent2Color(settings.getAttribute("widgetAccentColor", "color2", ""));
//        setWidgetAccent3Color(settings.getAttribute("widgetAccentColor", "color3", ""));
//        setWidgetAccent4Color(settings.getAttribute("widgetAccentColor", "color4", ""));
//
//        setWidgetAlternating1Color(settings.getAttribute("widgetAlternatingColor", "color1", ""));
//        setWidgetAlternating2Color(settings.getAttribute("widgetAlternatingColor", "color2", ""));
//
//        setWidgetModalBackgroundColor(settings.getAttribute("widgetModalBackgroundColor", "color", ""));
//
//        HoveredWidgetAlpha = settings.getAttribute("widgetAlpha", "hovered", fallback.HoveredWidgetAlpha);
//        UnhoveredWidgetAlpha = settings.getAttribute("widgetAlpha", "unhovered", fallback.UnhoveredWidgetAlpha);
//        ContentChromeAlpha = settings.getAttribute("widgetAlpha", "contentChrome", fallback.ContentChromeAlpha);
//        
//        setTitleFontColor(settings.getAttribute("titleFontColor", "color", ""));
//        
//        HoveredTitleFontAlpha = settings.getAttribute("titleFontAlpha", "hovered", fallback.HoveredTitleFontAlpha);
//        UnhoveredTitleFontAlpha = settings.getAttribute("titleFontAlpha", "unhovered", fallback.UnhoveredTitleFontAlpha);
//        
//        setTitleColor(settings.getAttribute("titleColor", "color", ""));
//
//        HoveredTitleAlpha = settings.getAttribute("titleAlpha", "hovered", fallback.HoveredTitleAlpha);
//        UnhoveredTitleAlpha = settings.getAttribute("titleAlpha", "unhovered", fallback.UnhoveredTitleAlpha);
//
//        setTitleGradientColors(
//            settings.getAttribute("titleGradientColor", "color1", fallback.getTitleGradientColor1Hex()),
//            settings.getAttribute("titleGradientColor", "color2", fallback.getTitleGradientColor2Hex()),
//            settings.getAttribute("titleGradientColor", "color3", fallback.getTitleGradientColor3Hex()),
//            settings.getAttribute("titleGradientColor", "color4", fallback.getTitleGradientColor4Hex())
//        );
//
//        setTypographyColors(
//            settings.getAttribute("typographyColor", "primary", fallback.getTypographyPrimaryColorHex()),
//            settings.getAttribute("typographyColor", "secondary", fallback.getTypographySecondaryColorHex()),
//            settings.getAttribute("typographyColor", "tertiary", fallback.getTypographyTertiaryColorHex()),
//            settings.getAttribute("typographyColor", "quaternary", fallback.getTypographyQuaternaryColorHex())
//        );
//
//        setSelectionColors(
//            settings.getAttribute("selection", "foreground", fallback.getSelectionForegroundColorHex()),
//            settings.getAttribute("selection", "background", fallback.getSelectionBackgroundColorHex())
//        );
//
//        setHoverColors(
//            settings.getAttribute("hover", "foreground", fallback.getHoverBackgroundColorHex()),
//            settings.getAttribute("hover", "background", fallback.getHoverBackgroundColorHex())
//        );
//       
//    }
//
//    void populateElementTheme(uiVizWidgetTheme& fallback, ofxXmlSettings& settings) {
//        
//        setElementForegroundColor(settings.getAttribute("foregroundColor", "color", ""));
//        
//        ElementHoveredForegroundAlpha = settings.getAttribute("foregroundAlpha", "hovered", fallback.ElementHoveredForegroundAlpha);
//        ElementUnhoveredForegroundAlpha = settings.getAttribute("foregroundAlpha", "unhovered", fallback.ElementUnhoveredForegroundAlpha);
//        
//        setElementBackgroundColor(settings.getAttribute("backgroundColor", "color", ""));
//
//        ElementHoveredBackgroundAlpha = settings.getAttribute("backgroundAlpha", "hovered", fallback.ElementHoveredBackgroundAlpha);
//        ElementUnhoveredBackgroundAlpha = settings.getAttribute("backgroundAlpha", "unhovered", fallback.ElementUnhoveredBackgroundAlpha);
//    }
//    
//    bool isDefaultLight() {
//        return (Name == "System");
//    }
//    
//    bool isDefaultDark() {
//        return (Name == "SystemDark");
//    }
//    
//    bool isDefault() {
//        return (isDefaultLight() || isDefaultDark());
//    }
//
//
//    ofColor TitleFontColor_withAlpha(float alpha) {
//        return ofColor(TitleFontColor.r, TitleFontColor.g, TitleFontColor.b, TitleFontColor.a * alpha);
//    }
//
//    string getTitleFontColorHex() {
//        return "#" + getHexFromInt(TitleFontColor.r) +  getHexFromInt(TitleFontColor.g) + getHexFromInt(TitleFontColor.b) + getHexFromInt(TitleFontColor.a);
//    }
//
//    void setTitleFontColor(ofColor val) {
//        setColorFromSource(TitleFontColor, val);
//    }
//
//    void setTitleFontColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setTitleFontColor(val);
//    }
//    
//    ofColor TitleColor_withAlpha(float alpha) {
//        return ofColor(TitleColor.r, TitleColor.g, TitleColor.b, TitleColor.a * alpha);
//    }
//
//    string getTitleColorHex() {
//        return "#" + getHexFromInt(TitleColor.r) +  getHexFromInt(TitleColor.g) + getHexFromInt(TitleColor.b) + getHexFromInt(TitleColor.a);
//    }
//
//    void setTitleColor(ofColor val) {
//        setColorFromSource(TitleColor, val);
//    }
//
//    void setTitleColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setTitleColor(val);
//    }
//
//    ofColor TitleGradientColor1_withAlpha(float alpha) {
//        return ofColor(TitleGradientColor1.r, TitleGradientColor1.g, TitleGradientColor1.b, TitleGradientColor1.a * alpha);
//    }
//
//    string getTitleGradientColor1Hex() {
//        return "#" + getHexFromInt(TitleGradientColor1.r) +  getHexFromInt(TitleGradientColor1.g) + getHexFromInt(TitleGradientColor1.b) + getHexFromInt(TitleGradientColor1.a);
//    }
//
//    ofColor TitleGradientColor2_withAlpha(float alpha) {
//        return ofColor(TitleGradientColor2.r, TitleGradientColor2.g, TitleGradientColor2.b, TitleGradientColor2.a * alpha);
//    }
//
//    string getTitleGradientColor2Hex() {
//        return "#" + getHexFromInt(TitleGradientColor2.r) +  getHexFromInt(TitleGradientColor2.g) + getHexFromInt(TitleGradientColor2.b) + getHexFromInt(TitleGradientColor2.a);
//    }
//
//    ofColor TitleGradientColor3_withAlpha(float alpha) {
//        return ofColor(TitleGradientColor3.r, TitleGradientColor3.g, TitleGradientColor3.b, TitleGradientColor3.a * alpha);
//    }
//
//    string getTitleGradientColor3Hex() {
//        return "#" + getHexFromInt(TitleGradientColor3.r) +  getHexFromInt(TitleGradientColor3.g) + getHexFromInt(TitleGradientColor3.b) + getHexFromInt(TitleGradientColor3.a);
//    }
//
//    ofColor TitleGradientColor4_withAlpha(float alpha) {
//        return ofColor(TitleGradientColor4.r, TitleGradientColor4.g, TitleGradientColor4.b, TitleGradientColor4.a * alpha);
//    }
//
//    string getTitleGradientColor4Hex() {
//        return "#" + getHexFromInt(TitleGradientColor4.r) +  getHexFromInt(TitleGradientColor4.g) + getHexFromInt(TitleGradientColor4.b) + getHexFromInt(TitleGradientColor4.a);
//    }
//
//    void setTitleGradientColors(ofColor color1, ofColor color2, ofColor color3, ofColor color4) {
//        TitleGradientColor1 = color1;
//        TitleGradientColor2 = color2;
//        TitleGradientColor3 = color3;
//        TitleGradientColor4 = color4;
//        mTitleGradientSet = true;
//    }
//
//    void setTitleGradientColors(string RGBAHexColor1, string RGBAHexColor2, string RGBAHexColor3, string RGBAHexColor4) {
//        if (RGBAHexColor1 == "" && RGBAHexColor2 == "" && RGBAHexColor3 == "" && RGBAHexColor4 == "") return;
//        ofColor color1 = getColor_fromRGBAHex(RGBAHexColor1);
//        ofColor color2 = getColor_fromRGBAHex(RGBAHexColor2);
//        ofColor color3 = getColor_fromRGBAHex(RGBAHexColor3);
//        ofColor color4 = getColor_fromRGBAHex(RGBAHexColor4);
//        setTitleGradientColors(color1, color2, color3, color4);
//    }
//
//    bool getTitleGradientSet() {
//        return mTitleGradientSet;
//    }
//
//    ofColor TypographyPrimaryColor_withAlpha(float alpha) {
//        return ofColor(TypographyPrimaryColor.r, TypographyPrimaryColor.g, TypographyPrimaryColor.b, TypographyPrimaryColor.a * alpha);
//    }
//
//    string getTypographyPrimaryColorHex() {
//        return "#" + getHexFromInt(TypographyPrimaryColor.r) +  getHexFromInt(TypographyPrimaryColor.g) + getHexFromInt(TypographyPrimaryColor.b) + getHexFromInt(TypographyPrimaryColor.a);
//    }
//
//    ofColor TypographySecondaryColor_withAlpha(float alpha) {
//        return ofColor(TypographySecondaryColor.r, TypographySecondaryColor.g, TypographySecondaryColor.b, TypographySecondaryColor.a * alpha);
//    }
//
//    string getTypographySecondaryColorHex() {
//        return "#" + getHexFromInt(TypographySecondaryColor.r) +  getHexFromInt(TypographySecondaryColor.g) + getHexFromInt(TypographySecondaryColor.b) + getHexFromInt(TypographySecondaryColor.a);
//    }
//
//    ofColor TypographyTertiaryColor_withAlpha(float alpha) {
//        return ofColor(TypographyTertiaryColor.r, TypographyTertiaryColor.g, TypographyTertiaryColor.b, TypographyTertiaryColor.a * alpha);
//    }
//
//    string getTypographyTertiaryColorHex() {
//        return "#" + getHexFromInt(TypographyTertiaryColor.r) +  getHexFromInt(TypographyTertiaryColor.g) + getHexFromInt(TypographyTertiaryColor.b) + getHexFromInt(TypographyTertiaryColor.a);
//    }
//
//    ofColor TypographyQuaternaryColor_withAlpha(float alpha) {
//        return ofColor(TypographyQuaternaryColor.r, TypographyQuaternaryColor.g, TypographyQuaternaryColor.b, TypographyQuaternaryColor.a * alpha);
//    }
//
//    string getTypographyQuaternaryColorHex() {
//        return "#" + getHexFromInt(TypographyQuaternaryColor.r) +  getHexFromInt(TypographyQuaternaryColor.g) + getHexFromInt(TypographyQuaternaryColor.b) + getHexFromInt(TypographyQuaternaryColor.a);
//    }
//
//    void setTypographyColors(ofColor primary, ofColor secondary, ofColor tertiary, ofColor quaternary) {
//        TypographyPrimaryColor = primary;
//        TypographySecondaryColor = secondary;
//        TypographyTertiaryColor = tertiary;
//        TypographyQuaternaryColor = quaternary;
//    }
//
//    void setTypographyColors(string RGBAHexPrimary, string RGBAHexSecondary, string RGBAHexTertiary, string RGBAHexQuaternary) {
//        ofColor primary = getColor_fromRGBAHex(RGBAHexPrimary);
//        ofColor secondary = getColor_fromRGBAHex(RGBAHexSecondary);
//        ofColor tertiary = getColor_fromRGBAHex(RGBAHexTertiary);
//        ofColor quaternary = getColor_fromRGBAHex(RGBAHexQuaternary);
//        setTypographyColors(primary, secondary, tertiary, quaternary);
//    }
//
//    ofColor SelectionForegroundColor_withAlpha(float alpha) {
//        return ofColor(SelectionForegroundColor.r, SelectionForegroundColor.g, SelectionForegroundColor.b, SelectionForegroundColor.a * alpha);
//    }
//
//    string getSelectionForegroundColorHex() {
//        return "#" + getHexFromInt(SelectionForegroundColor.r) +  getHexFromInt(SelectionForegroundColor.g) + getHexFromInt(SelectionForegroundColor.b) + getHexFromInt(SelectionForegroundColor.a);
//    }
//
//    ofColor SelectionBackgroundColor_withAlpha(float alpha) {
//        return ofColor(SelectionBackgroundColor.r, SelectionBackgroundColor.g, SelectionBackgroundColor.b, SelectionBackgroundColor.a * alpha);
//    }
//
//    string getSelectionBackgroundColorHex() {
//        return "#" + getHexFromInt(SelectionBackgroundColor.r) +  getHexFromInt(SelectionBackgroundColor.g) + getHexFromInt(SelectionBackgroundColor.b) + getHexFromInt(SelectionBackgroundColor.a);
//    }
//
//    void setSelectionColors(ofColor foreground, ofColor background) {
//        SelectionForegroundColor = foreground;
//        SelectionBackgroundColor = background;
//    }
//
//    void setSelectionColors(string RGBAHexForeground, string RGBAHexBackground) {
//        ofColor foreground = getColor_fromRGBAHex(RGBAHexForeground);
//        ofColor background = getColor_fromRGBAHex(RGBAHexBackground);
//        setSelectionColors(foreground, background);
//    }
//
//    ofColor HoverForegroundColor_withAlpha(float alpha) {
//        return ofColor(HoverForegroundColor.r, HoverForegroundColor.g, HoverForegroundColor.b, HoverForegroundColor.a * alpha);
//    }
//
//    string getHoverForegroundColorHex() {
//        return "#" + getHexFromInt(HoverForegroundColor.r) +  getHexFromInt(HoverForegroundColor.g) + getHexFromInt(HoverForegroundColor.b) + getHexFromInt(HoverForegroundColor.a);
//    }
//
//    ofColor HoverBackgroundColor_withAlpha(float alpha) {
//        return ofColor(HoverBackgroundColor.r, HoverBackgroundColor.g, HoverBackgroundColor.b, HoverBackgroundColor.a * alpha);
//    }
//
//    string getHoverBackgroundColorHex() {
//        return "#" + getHexFromInt(HoverBackgroundColor.r) +  getHexFromInt(HoverBackgroundColor.g) + getHexFromInt(HoverBackgroundColor.b) + getHexFromInt(HoverBackgroundColor.a);
//    }
//
//    void setHoverColors(ofColor foreground, ofColor background) {
//        HoverForegroundColor = foreground;
//        HoverBackgroundColor = background;
//    }
//
//    void setHoverColors(string RGBAHexForeground, string RGBAHexBackground) {
//        ofColor foreground = getColor_fromRGBAHex(RGBAHexForeground);
//        ofColor background = getColor_fromRGBAHex(RGBAHexBackground);
//        setHoverColors(foreground, background);
//    }
//
//    ofColor WidgetColor_withAlpha(float alpha) {
//        return ofColor(WidgetColor.r, WidgetColor.g, WidgetColor.b, WidgetColor.a * alpha);
//    }
//
//    string getWidgetColorHex() {
//        return "#" + getHexFromInt(WidgetColor.r) +  getHexFromInt(WidgetColor.g) + getHexFromInt(WidgetColor.b) + getHexFromInt(WidgetColor.a);
//    }
//
//    void setWidgetColor(ofColor val) {
//        setColorFromSource(WidgetColor, val);
//    }
//
//    void setWidgetColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetColor(val);
//    }
//
//    ofColor WidgetContentColor_withAlpha(float alpha) {
//        return ofColor(WidgetContentColor.r, WidgetContentColor.g, WidgetContentColor.b, WidgetContentColor.a * alpha);
//    }
//
//    string getWidgetContentColorHex() {
//        return "#" + getHexFromInt(WidgetContentColor.r) +  getHexFromInt(WidgetContentColor.g) + getHexFromInt(WidgetContentColor.b) + getHexFromInt(WidgetContentColor.a);
//    }
//
//    void setWidgetContentColor(ofColor val) {
//        setColorFromSource(WidgetContentColor, val);
//    }
//
//    void setWidgetContentColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetContentColor(val);
//    }
//
//    ofColor WidgetAccent1Color_withAlpha(float alpha) {
//        return ofColor(WidgetAccent1Color.r, WidgetAccent1Color.g, WidgetAccent1Color.b, WidgetAccent1Color.a * alpha);
//    }
//
//    string getWidgetAccent1ColorHex() {
//        return "#" + getHexFromInt(WidgetAccent1Color.r) +  getHexFromInt(WidgetAccent1Color.g) + getHexFromInt(WidgetAccent1Color.b) + getHexFromInt(WidgetAccent1Color.a);
//    }
//
//    void setWidgetAccent1Color(ofColor val) {
//        setColorFromSource(WidgetAccent1Color, val);
//    }
//
//    void setWidgetAccent1Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAccent1Color(val);
//    }
//
//    ofColor WidgetAccent2Color_withAlpha(float alpha) {
//        return ofColor(WidgetAccent2Color.r, WidgetAccent2Color.g, WidgetAccent2Color.b, WidgetAccent2Color.a * alpha);
//    }
//
//    string getWidgetAccent2ColorHex() {
//        return "#" + getHexFromInt(WidgetAccent2Color.r) +  getHexFromInt(WidgetAccent2Color.g) + getHexFromInt(WidgetAccent2Color.b) + getHexFromInt(WidgetAccent2Color.a);
//    }
//
//    void setWidgetAccent2Color(ofColor val) {
//        setColorFromSource(WidgetAccent2Color, val);
//    }
//
//    void setWidgetAccent2Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAccent2Color(val);
//    }
//
//    ofColor WidgetAccent3Color_withAlpha(float alpha) {
//        return ofColor(WidgetAccent3Color.r, WidgetAccent3Color.g, WidgetAccent3Color.b, WidgetAccent3Color.a * alpha);
//    }
//
//    string getWidgetAccent3ColorHex() {
//        return "#" + getHexFromInt(WidgetAccent3Color.r) +  getHexFromInt(WidgetAccent3Color.g) + getHexFromInt(WidgetAccent3Color.b) + getHexFromInt(WidgetAccent3Color.a);
//    }
//
//    void setWidgetAccent3Color(ofColor val) {
//        setColorFromSource(WidgetAccent3Color, val);
//    }
//
//    void setWidgetAccent3Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAccent3Color(val);
//    }
//
//    ofColor WidgetAccent4Color_withAlpha(float alpha) {
//        return ofColor(WidgetAccent4Color.r, WidgetAccent4Color.g, WidgetAccent4Color.b, WidgetAccent4Color.a * alpha);
//    }
//
//    string getWidgetAccent4ColorHex() {
//        return "#" + getHexFromInt(WidgetAccent4Color.r) +  getHexFromInt(WidgetAccent4Color.g) + getHexFromInt(WidgetAccent4Color.b) + getHexFromInt(WidgetAccent4Color.a);
//    }
//
//    void setWidgetAccent4Color(ofColor val) {
//        setColorFromSource(WidgetAccent4Color, val);
//    }
//
//    void setWidgetAccent4Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAccent4Color(val);
//    }
//
//    // Eg text
//    ofColor WidgetAccentHighContrast1Color_withAlpha(float alpha) {
//        return WidgetAccent1Color_withAlpha(alpha);
//    }
//
//    // Eg text
//    ofColor WidgetAccentHighContrast2Color_withAlpha(float alpha) {
//        return WidgetAccent2Color_withAlpha(alpha);
//    }
//
//    // Eg highlight BEHIND text
//    ofColor WidgetAccentLowContrast1Color_withAlpha(float alpha) {
//        return WidgetAccent3Color_withAlpha(alpha);
//    }
//
//    // Eg highlight BEHIND text
//    ofColor WidgetAccentLowContrast2Color_withAlpha(float alpha) {
//        return WidgetAccent4Color_withAlpha(alpha);
//    }
//    
//    ofColor WidgetAlternating1Color_withAlpha(float alpha) {
//        return ofColor(WidgetAlternating1Color.r, WidgetAlternating1Color.g, WidgetAlternating1Color.b, WidgetAlternating1Color.a * alpha);
//    }
//
//    string getWidgetAlternating1ColorHex() {
//        return "#" + getHexFromInt(WidgetAlternating1Color.r) +  getHexFromInt(WidgetAlternating1Color.g) + getHexFromInt(WidgetAlternating1Color.b) + getHexFromInt(WidgetAlternating1Color.a);
//    }
//
//    void setWidgetAlternating1Color(ofColor val) {
//        setColorFromSource(WidgetAlternating1Color, val);
//    }
//
//    void setWidgetAlternating1Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAlternating1Color(val);
//    }
//
//    ofColor WidgetAlternating2Color_withAlpha(float alpha) {
//        return ofColor(WidgetAlternating2Color.r, WidgetAlternating2Color.g, WidgetAlternating2Color.b, WidgetAlternating2Color.a * alpha);
//    }
//
//    string getWidgetAlternating2ColorHex() {
//        return "#" + getHexFromInt(WidgetAlternating2Color.r) +  getHexFromInt(WidgetAlternating2Color.g) + getHexFromInt(WidgetAlternating2Color.b) + getHexFromInt(WidgetAlternating2Color.a);
//    }
//
//    void setWidgetAlternating2Color(ofColor val) {
//        setColorFromSource(WidgetAlternating2Color, val);
//    }
//
//    void setWidgetAlternating2Color(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetAlternating2Color(val);
//    }
//
//    ofColor getWidgetModalBackgroundColor() {
//        return ofColor(WidgetModalBackgroundColor.r, WidgetModalBackgroundColor.g, WidgetModalBackgroundColor.b, WidgetModalBackgroundColor.a);
//    }
//
//    string getWidgetModalBackgroundColorHex() {
//        return "#" + getHexFromInt(WidgetModalBackgroundColor.r) +  getHexFromInt(WidgetModalBackgroundColor.g) + getHexFromInt(WidgetModalBackgroundColor.b) + getHexFromInt(WidgetModalBackgroundColor.a);
//    }
//
//    void setWidgetModalBackgroundColor(ofColor val) {
//        setColorFromSource(WidgetModalBackgroundColor, val);
//    }
//
//    void setWidgetModalBackgroundColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setWidgetModalBackgroundColor(val);
//    }
//
//    ofColor ElementForegroundColor_withAlpha(float alpha) {
//        return ofColor(ElementForegroundColor.r, ElementForegroundColor.g, ElementForegroundColor.b, ElementForegroundColor.a * alpha);
//    }
//    
//    string getElementForegroundColorHex() {
//        return "#" + getHexFromInt(ElementForegroundColor.r) +  getHexFromInt(ElementForegroundColor.g) + getHexFromInt(ElementForegroundColor.b) + getHexFromInt(ElementForegroundColor.a);
//    }
//
//    void setElementForegroundColor(ofColor val) {
//        setColorFromSource(ElementForegroundColor, val);
//    }
//
//    void setElementForegroundColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setElementForegroundColor(val);
//    }
//    
//    ofColor ElementBackgroundColor_withAlpha(float alpha) {
//        return ofColor(ElementBackgroundColor.r, ElementBackgroundColor.g, ElementBackgroundColor.b, ElementBackgroundColor.a * alpha);
//    }
//
//    string getElementBackgroundColorHex() {
//        return "#" + getHexFromInt(ElementBackgroundColor.r) +  getHexFromInt(ElementBackgroundColor.g) + getHexFromInt(ElementBackgroundColor.b) + getHexFromInt(ElementBackgroundColor.a);
//    }
//
//    static string getHexFromColor(ofColor c) {
//        return "#" + getHexFromInt(c.r) +  getHexFromInt(c.g) + getHexFromInt(c.b) + getHexFromInt(c.a);
//    }
//
//    static string getHexFromColor(ofColor c, float alpha) {
//        return "#" + getHexFromInt(c.r) +  getHexFromInt(c.g) + getHexFromInt(c.b) + getHexFromInt(255*alpha);
//    }
//
//    void setElementBackgroundColor(ofColor val) {
//        setColorFromSource(ElementBackgroundColor, val);
//    }
//
//    void setElementBackgroundColor(string RGBAHex) {
//        if (RGBAHex == "") return;
//        ofColor val = getColor_fromRGBAHex(RGBAHex);
//        setElementBackgroundColor(val);
//    }
//
//    void setWidgetAlphas(int titleFontColor_a, int titleColor_a, int widgetColor_a) {
//        TitleFontColor.a = titleFontColor_a;
//        TitleColor.a = titleColor_a;
//        WidgetColor.a = widgetColor_a;
//    }
//    
//    void setColorFromSource(ofColor& targetColor, ofColor sourceColor) {
//        targetColor.r = sourceColor.r;
//        targetColor.g = sourceColor.g;
//        targetColor.b = sourceColor.b;
//        targetColor.a = sourceColor.a;
//    }

    static int getR_fromRGBAHex(string RGBAHex) {
        if (RGBAHex.size() >=2) {
            return min((int)ofHexToInt(RGBAHex.substr(0, 2)), 255);
        }
        return 0;
    }

    static int getG_fromRGBAHex(string RGBAHex) {
        if (RGBAHex.size() >=4) {
            return min((int)ofHexToInt(RGBAHex.substr(2, 2)), 255);
        }
        return 0;
    }

    static int getB_fromRGBAHex(string RGBAHex) {
        if (RGBAHex.size() >=6) {
            return min((int)ofHexToInt(RGBAHex.substr(4, 2)), 255);
        }
        return 0;
    }

    static int getA_fromRGBAHex(string RGBAHex) {
        if (RGBAHex.size() >=8) {
            return min((int)ofHexToInt(RGBAHex.substr(6, 2)), 255);
        }
        return 255;
    }

    static juce::Colour getColor_fromRGBAHex(string RGBAHex) {
        ofStringReplace(RGBAHex, "#", "");
        return juce::Colour::fromRGBA(
            getR_fromRGBAHex(RGBAHex),
            getG_fromRGBAHex(RGBAHex),
            getB_fromRGBAHex(RGBAHex),
            getA_fromRGBAHex(RGBAHex)
        );
    }

    static string getHexFromInt(unsigned char c) {
        // Not necessarily the most efficient approach,
        // creating a new stringstream each time.
        // It'll do, though.
        std::stringstream ss;

        // Set stream modes
        ss << std::uppercase << std::setw(2) << std::setfill('0') << std::hex;

        // Stream in the character's ASCII code
        // (using `+` for promotion to `int`)
        ss << +c;

        // Return resultant string content
        return ss.str();
    }

    string Name = "";
    bool IsDark = false;

    // Widget
    bool RoundedRectangle = true;
    float UnhoveredWidgetAlpha = 0.7f;
    float HoveredWidgetAlpha = 0.9f;
    float ContentChromeAlpha = 0.7f;
    
    float UnhoveredTitleAlpha = 0.7f;
    float HoveredTitleAlpha = 0.9f;
    
    float UnhoveredTitleFontAlpha = 0.7f;
    float HoveredTitleFontAlpha = 0.9f;

    // These are not persisted
    float GenericHoveredAlpha = 0.5f;
    float GenericSelectedAlpha = 0.6f;
    
    juce::Colour TitleFontColor = juce::Colour::fromRGBA(0,0,0,238);
    juce::Colour TitleColor = juce::Colour::fromRGBA(254, 254, 254, 255);

    juce::Colour TitleGradientColor1 = juce::Colour::fromRGBA(255, 255, 255, 255);
    juce::Colour TitleGradientColor2 = juce::Colour::fromRGBA(254, 254, 254, 255);
    juce::Colour TitleGradientColor3 = juce::Colour::fromRGBA(254, 254, 254, 255);
    juce::Colour TitleGradientColor4 = juce::Colour::fromRGBA(255, 255, 255, 255);

    juce::Colour TypographyPrimaryColor = juce::Colour::fromRGBA(51, 51, 51, 255);
    juce::Colour TypographySecondaryColor = juce::Colour::fromRGBA(85, 85, 85, 255);
    juce::Colour TypographyTertiaryColor = juce::Colour::fromRGBA(170, 170, 170, 255);
    juce::Colour TypographyQuaternaryColor = juce::Colour::fromRGBA(238, 238, 238, 255);


    juce::Colour SelectionForegroundColor = juce::Colour::fromRGBA(255, 255, 255, 255);
    juce::Colour SelectionBackgroundColor = juce::Colour::fromRGBA(153, 153, 153, 255);
    juce::Colour HoverForegroundColor = juce::Colour::fromRGBA(255, 255, 255, 255);
    juce::Colour HoverBackgroundColor = juce::Colour::fromRGBA(170, 170, 170, 255);


    juce::Colour WidgetColor = juce::Colour::fromRGBA(255, 255, 255, 255);
    juce::Colour WidgetContentColor = juce::Colour::fromRGBA(255, 255, 255, 170);

    juce::Colour WidgetAccent1Color = juce::Colour::fromRGBA(0, 77, 122, 255);
    juce::Colour WidgetAccent2Color = juce::Colour::fromRGBA(5, 25, 55, 255);
    juce::Colour WidgetAccent3Color = juce::Colour::fromRGBA(0, 137, 147, 255);
    juce::Colour WidgetAccent4Color = juce::Colour::fromRGBA(168, 235, 18, 255);

    juce::Colour WidgetAlternating1Color = juce::Colour::fromRGBA(213, 213, 213, 255);
    juce::Colour WidgetAlternating2Color = juce::Colour::fromRGBA(221, 221, 221, 238);
    juce::Colour WidgetModalBackgroundColor = juce::Colour::fromRGBA(0, 0, 0, 180);

    
    // Element
    bool ElementRoundedRectangle = true;

    juce::Colour ElementForegroundColor = juce::Colour::fromRGBA(33, 33, 33, 221);
    juce::Colour ElementBackgroundColor = juce::Colour::fromRGBA(204, 204, 204, 255);
    
    float ElementHoveredForegroundAlpha = 0.95f;
    float ElementHoveredBackgroundAlpha = 0.95f;
    float ElementHoveredAccentAlpha = 0.95f;
    
    float ElementUnhoveredForegroundAlpha = 0.90f;
    float ElementUnhoveredBackgroundAlpha = 0.90f;

private:
    bool mTitleGradientSet = false;
};
