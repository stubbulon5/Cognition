/*
  ==============================================================================

    uiVizWidget.h
    Created: 17 Mar 2024 8:10:33am
    Author:  Zabba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "uiVizWidgetBase.h"

//==============================================================================
/*
*/
class uiVizWidget  : public uiVizWidgetBase
{
public:
    uiVizWidget()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    uiVizWidget(juce::String persistentId, juce::String widgetXML) : uiVizWidgetBase(persistentId, widgetXML) {
        loadState(widgetXML);
    }    
    

    ~uiVizWidget() override
    {
    }

    virtual void paint (juce::Graphics& g) override
    {
        uiVizWidgetBase::paint(g);
        
        g.setColour (juce::Colours::orange);
        g.fillRect(getBounds());
    }

    virtual void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        uiVizWidgetBase::resized();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (uiVizWidget)
};





////------------------------------ uiVizWidget : derive all widgets which require rich interactivity --------------------------------
//class uiVizWidget : public uiVizWidgetBase {
//    
//public:
//    element_map_type elmClassMap;
//
//
//    void mapElements() {
//        elmClassMap[WIDGET_ELM_CLASS::TEXTBOX] = &createElement<uiVizWidgetElmTextbox>;
//        elmClassMap[WIDGET_ELM_CLASS::TEXTAREA] = &createElement<uiVizWidgetElmTextarea>;
//        elmClassMap[WIDGET_ELM_CLASS::LABEL] = &createElement<uiVizWidgetElmLabel>;
//        elmClassMap[WIDGET_ELM_CLASS::BUTTON] = &createElement<uiVizWidgetElmButton>;
//        elmClassMap[WIDGET_ELM_CLASS::SLIDER] = &createElement<uiVizWidgetElmSlider>;
//        elmClassMap[WIDGET_ELM_CLASS::CHECKBOX] = &createElement<uiVizWidgetElmCheckbox>;
//        elmClassMap[WIDGET_ELM_CLASS::DROPDOWN] = &createElement<uiVizWidgetElmDropdown>;
//        elmClassMap[WIDGET_ELM_CLASS::BREADCRUMB] = &createElement<uiVizWidgetElmBreadcrumb>;        
//        elmClassMap[WIDGET_ELM_CLASS::IMAGE] = &createElement<uiVizWidgetElmImage>;
//        elmClassMap[WIDGET_ELM_CLASS::PROGRESS_BAR] = &createElement<uiVizWidgetElmProgressBar>;
//    }
//    
//    enum class TitleStyle { /* C++ 11 */
//        NONE,
//        TOP_STATIC,
//        TOP_OVERLAY,
//        TOP_OVERLAY_FULL,
//        TOP_WITH_WIDGET_RESIZE,
//        BOTTOM_STATIC,
//        BOTTOM_OVERLAY,
//        BOTTOM_OVERLAY_FULL,
//        BOTTOM_WITH_WIDGET_RESIZE,
//        LEFT_STATIC,
//        LEFT_OVERLAY,
//        LEFT_OVERLAY_FULL,
//        LEFT_WITH_WIDGET_RESIZE,
//        RIGHT_STATIC,
//        RIGHT_OVERLAY,
//        RIGHT_OVERLAY_FULL,
//        RIGHT_WITH_WIDGET_RESIZE
//    };
//
//    string getTitleStyleString(TitleStyle val) {
//        switch(val) {
//            case TitleStyle::NONE: return "NONE";
//            case TitleStyle::TOP_STATIC: return "TOP_STATIC";
//            case TitleStyle::TOP_OVERLAY: return "TOP_OVERLAY";
//            case TitleStyle::TOP_OVERLAY_FULL: return "TOP_OVERLAY_FULL";
//            case TitleStyle::TOP_WITH_WIDGET_RESIZE: return "TOP_WITH_WIDGET_RESIZE";
//            case TitleStyle::BOTTOM_STATIC: return "BOTTOM_STATIC";
//            case TitleStyle::BOTTOM_OVERLAY: return "BOTTOM_OVERLAY";
//            case TitleStyle::BOTTOM_OVERLAY_FULL: return "BOTTOM_OVERLAY_FULL";
//            case TitleStyle::BOTTOM_WITH_WIDGET_RESIZE: return "BOTTOM_WITH_WIDGET_RESIZE";
//            case TitleStyle::LEFT_STATIC: return "LEFT_STATIC";
//            case TitleStyle::LEFT_OVERLAY: return "LEFT_OVERLAY";
//            case TitleStyle::LEFT_OVERLAY_FULL: return "LEFT_OVERLAY_FULL";
//            case TitleStyle::LEFT_WITH_WIDGET_RESIZE: return "LEFT_WITH_WIDGET_RESIZE";
//            case TitleStyle::RIGHT_STATIC: return "RIGHT_STATIC";
//            case TitleStyle::RIGHT_OVERLAY: return "RIGHT_OVERLAY";
//            case TitleStyle::RIGHT_OVERLAY_FULL: return "RIGHT_OVERLAY_FULL";
//            case TitleStyle::RIGHT_WITH_WIDGET_RESIZE: return "RIGHT_WITH_WIDGET_RESIZE";
//            default: return "NONE";
//        }
//    };
//    
//    TitleStyle getTitleStyleEnum(string val) {
//        if (val == "NONE") return TitleStyle::NONE;
//        if (val == "TOP_STATIC") return TitleStyle::TOP_STATIC;
//        if (val == "TOP_OVERLAY") return TitleStyle::TOP_OVERLAY;
//        if (val == "TOP_OVERLAY_FULL") return TitleStyle::TOP_OVERLAY_FULL;
//        if (val == "TOP_WITH_WIDGET_RESIZE") return TitleStyle::TOP_WITH_WIDGET_RESIZE;
//        if (val == "BOTTOM_STATIC") return TitleStyle::BOTTOM_STATIC;
//        if (val == "BOTTOM_OVERLAY") return TitleStyle::BOTTOM_OVERLAY;
//        if (val == "BOTTOM_OVERLAY_FULL") return TitleStyle::BOTTOM_OVERLAY_FULL;
//        if (val == "BOTTOM_WITH_WIDGET_RESIZE") return TitleStyle::BOTTOM_WITH_WIDGET_RESIZE;
//        if (val == "LEFT_STATIC") return TitleStyle::LEFT_STATIC;
//        if (val == "LEFT_OVERLAY") return TitleStyle::LEFT_OVERLAY;
//        if (val == "LEFT_OVERLAY_FULL") return TitleStyle::LEFT_OVERLAY_FULL;
//        if (val == "LEFT_WITH_WIDGET_RESIZE") return TitleStyle::LEFT_WITH_WIDGET_RESIZE;
//        if (val == "RIGHT_STATIC") return TitleStyle::RIGHT_STATIC;
//        if (val == "RIGHT_OVERLAY") return TitleStyle::RIGHT_OVERLAY;
//        if (val == "RIGHT_OVERLAY_FULL") return TitleStyle::RIGHT_OVERLAY_FULL;
//        if (val == "RIGHT_WITH_WIDGET_RESIZE") return TitleStyle::RIGHT_WITH_WIDGET_RESIZE;
//        return TitleStyle::NONE;
//    };
//
//    enum class AdditionalState {
//        NONE,
//        SELECTED
//    };
//
//	enum class FboMode {
//		LOW,
//		MEDIUM,
//		HIGH,
//		ULTRA
//	};
//   
//    uiVizWidget(string persistentId, string widgetXML) : uiVizWidgetBase(persistentId, widgetXML) {
//        init();
//        loadState(widgetXML);
//    }
//    
//    uiVizWidget(string persistentId, string widgetXML, string ownerWidgetId) : uiVizWidgetBase(persistentId, widgetXML, ownerWidgetId) {
//        init();
//        loadState(widgetXML);
//    }        
//
//     virtual ~uiVizWidget() {
//        // NOTE ON VIRTUAL DESTRUCTOR : For this exampe: Base *myObj = new Derived(); delete myObj; If your derived class destructor is NOT virtual then
//        // only base class object will get deleted (because pointer is of base class "Base *myObj"). So there will be memory leak for derived object.
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
//        cout << "[" << getPersistentId() << "]~uiVizWidget()->clearChildWidgets(); /************************/ \n";
//        #endif     
//        clearChildWidgets();
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
//        cout << "[" << getPersistentId() << "]~uiVizWidget()->clearWidgetElements();  /************************/ \n";
//        #endif 
//        clearWidgetElements();
//    }
//    
//    virtual void setTheme(uiVizWidgetTheme val) override {
//        if (getIgnoreThemeChanges()) return;
//        uiVizWidgetBase::setTheme(val);
//        uiVizWidgetTheme theme = getTheme();
//        
//        setIsRoundedRectangle(theme.RoundedRectangle);
//        
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            elm.setTheme(val);
//        }
//
//        for(uiVizWidget &childWidget:getChildWidgets()) {
//            childWidget.setTheme(val); // this will set child elements
//        }
//    }
//
//    virtual void setIsHighlighted(bool val) override {
//        uiVizWidgetBase::setIsHighlighted(val);
//
//        if (val) {
//            vizElm_WIDGET_UI_SHADOW.setRectGradient(getTheme().WidgetAccent1Color_withAlpha(getTheme().ElementHoveredForegroundAlpha), getTheme().WidgetAccent1Color_withAlpha(getTheme().ElementHoveredForegroundAlpha), getTheme().WidgetAccent1Color_withAlpha(getTheme().ElementHoveredForegroundAlpha), getTheme().WidgetAccent2Color_withAlpha(getTheme().ElementHoveredForegroundAlpha));              
//        } else {
//            ofColor shadowDarkest = ofColor(0, 0, 0, getIsActiveWidget() ? 40 : 20);
//            ofColor shadowMedium = ofColor(0, 0, 0, getIsActiveWidget() ? 15 : 10);
//            ofColor shadowLightest = ofColor(0, 0, 0, getIsActiveWidget() ? 10 : 5);                  
//            vizElm_WIDGET_UI_SHADOW.setRectGradient(shadowMedium, shadowDarkest, shadowMedium, shadowLightest);  
//        }
//    }
//
//	virtual void setWasJustInitialized(bool val) override {
//        uiVizWidgetBase::setWasJustInitialized(val);
//        if (val) {
//		    mUICurrentWidgetAlpha = 0.2f;
//        }
//	}    
//    
//    virtual void onWidgetLoaded() override {
//        // Implement any behaviour for when a widget has loaded
//    }
//
//    virtual bool loadState(string widgetXML) override {
//        
//        uiVizWidgetBase::loadState(widgetXML);
//        
//        ofxXmlSettings mWidgetXML = ofxXmlSettings();
//       
//        long start = ofGetSystemTimeMillis();
//       
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//             cout << "[" << getPersistentId() << "]uiVizWidget->loadState()\n"; 
//        #endif
//        if (!mWidgetXML.loadFromBuffer(widgetXML.c_str())) {
//            #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//                cout << "[" << getPersistentId() << "]uiVizWidget->Unable to load XML\n" << widgetXML.c_str() << "\n";
//            #endif            
//            return false;
//        }
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//            cout << "[" << getPersistentId() << "]uiVizWidget->Loaded XML in \n" + ofToString(ofGetSystemTimeMillis() - start) + "ms\n";
//        #endif        
//        
//        mWidgetXML.pushTag("widget"); 
//     
//        /**** Title ****/
//        string titleStyle = ofToUpper(mWidgetXML.getAttribute("title", "style", getTitleStyleString(getTitleStyle()), 0));
//        setTitleStyle(getTitleStyleEnum(titleStyle));
//        setIsTitleAutohide(mWidgetXML.getAttribute("title", "autohide", getIsTitleAutohide()));
//
//        if (isTitleStatic()) {
//            if (getTitleStyle() != TitleStyle::TOP_STATIC || getTitleStyle() != TitleStyle::BOTTOM_STATIC ||  
//                getTitleStyle() != TitleStyle::LEFT_STATIC || getTitleStyle() != TitleStyle::RIGHT_STATIC) {
//                    setTitleStyle(TitleStyle::TOP_STATIC);
//                }
//            int size = mWidgetXML.getAttribute("title", "staticSize", getStaticTitleBarSize(false));
//            switch(getTitleStyle()) {
//                case TitleStyle::TOP_STATIC: setStaticTopTitleBarSize(size); break;
//                case TitleStyle::BOTTOM_STATIC: setStaticBottomTitleBarSize(size); break;
//                case TitleStyle::LEFT_STATIC: setStaticLeftTitleBarSize(size); break;
//                case TitleStyle::RIGHT_STATIC: setStaticRightTitleBarSize(size); break;
//            }
//        } 
//  
//        /**** Bounds ****/
//        setWidgetSize(
//            mWidgetXML.getAttribute("bounds", "width", getWidth()),
//            mWidgetXML.getAttribute("bounds", "height", getHeight()),
//            true
//        );
//        
//        setWidgetPosition(
//            mWidgetXML.getAttribute("bounds", "x", getX()),
//            mWidgetXML.getAttribute("bounds", "y", getY()),
//            true
//        );
//
//        /**** Behaviour ****/
//        setDrawWidgetChrome(mWidgetXML.getAttribute("behaviour", "drawWidgetChrome", getDrawWidgetChrome()));
//        setDrawWidgetTitle(mWidgetXML.getAttribute("behaviour", "drawWidgetTitle", getDrawWidgetTitle()));
//        
//        /**** Appearance ****/
//        setIsMinimized(mWidgetXML.getAttribute("appearance", "minimized", getIsMinimized(), 0));
//
//        uiVizWidgetTheme theme = getTheme();
//        
//        if (mWidgetXML.pushTag("appearance")) {
//            theme.loadForWidget(theme, widgetXML);
//            setTheme(theme);
//            mWidgetXML.popTag(); //appearance
//        }
//        
//        
//        mWidgetXML.popTag(); //widget
//
//        /**** Elements collection ****/            
//        TiXmlElement* rootElm = mWidgetXML.doc.RootElement();
//        if (rootElm == NULL) {
//            cout << "[" << getPersistentId() << "]uiVizWidget XML is invalid\n";
//            return false;
//        }
//        TiXmlElement* elementsElm = rootElm->FirstChildElement( "elements" );
//        
//        if (elementsElm != NULL) {
//            for(TiXmlNode* child = elementsElm->FirstChild(); child; child = child->NextSibling() ) {
//                TiXmlPrinter printer;
//                child->Accept( &printer );
//                string elmXML = printer.CStr();
//                
//                ofxXmlSettings elementSettings = ofxXmlSettings();
//                if (elementSettings.loadFromBuffer(elmXML)) {
//                    string elmId = elementSettings.getAttribute("element", "id", "");
//                    string elmClass = elementSettings.getAttribute("element", "class", "");
//
//                    if (elmClass != "" && elmId != "") {
//                        uiVizWidgetElm* existingElm = getWidgetElement(elmId);
//
//                        if (existingElm != nullptr) {
//                            existingElm->loadState(elmXML);
//                        } else {
//                            uiVizWidgetElm* e = addWidgetElement(elmClass, elmId, elmXML);                            
//                        }
//                        //cout << "element [" << this->getPersistentId() << "." << e->getPersistentId() << "] (" << elmClass << ") loaded\n";
//                    }
//                }
//            }
//            
//            for(uiVizWidgetElm &elm:mWidgetElements){
//                elm.setAllSiblingElementsLoaded(true);
//                elm.onAllSiblingElementsLoaded();
//            }
//        }
//
//        onWidgetLoaded();
//
//        return true;
//    }
//
//    static vector<uiVizWidgetSignature> getChildWidgetsList(string widgetXML) {
//
//        vector<uiVizWidgetSignature> widgets;
//
//        ofxXmlSettings mWidgetXML = ofxXmlSettings();
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//             cout << "uiVizWidget->getChildWidgetsList()\n"; 
//        #endif
//        if (!mWidgetXML.loadFromBuffer(widgetXML.c_str())) {
//            #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//                cout << "uiVizWidget->Unable to load XML\n" << widgetXML.c_str() << "\n";
//            #endif            
//            return widgets;
//        }
//
//        /**** Child Widgets collection ****/  
//        TiXmlElement* rootElm = mWidgetXML.doc.RootElement();
//        if (rootElm != NULL) {
//            TiXmlElement* childWidgetsElm = rootElm->FirstChildElement( "childWidgets" );
//            
//            if (childWidgetsElm != NULL) {
//                for(TiXmlNode* child = childWidgetsElm->FirstChild(); child; child = child->NextSibling() ) {
//                    TiXmlPrinter printer;
//                    child->Accept( &printer );
//                    string widgetXML = printer.CStr();
//                    
//                    ofxXmlSettings widgetSettings = ofxXmlSettings();
//                    if (widgetSettings.loadFromBuffer(widgetXML)) {
//                        string persistentId = widgetSettings.getAttribute("widget", "id", "");
//                        string widgetClass = widgetSettings.getAttribute("widget", "class", "");
//                        widgets.push_back(uiVizWidgetSignature(persistentId, widgetClass, widgetXML));
//                    }
//                }
//            } 
//        }
//       
//       return widgets;
//    }
//    
//    virtual ofxXmlSettings saveState() override {
//        
//        ofxXmlSettings mWidgetXML = uiVizWidgetBase::saveState();
//        mWidgetXML.setAttribute("widget", "class", "uiVizWidget", 0);
//        mWidgetXML.pushTag("widget");
//        
//        /**** Title ****/
//        mWidgetXML.setAttribute("title", "style", getTitleStyleString(getTitleStyle()), 0);
//
//        /*
//         NONE,
//         TOP_STATIC, TOP_OVERLAY, TOP_OVERLAY_FULL, TOP_WITH_WIDGET_RESIZE,
//         BOTTOM_STATIC, BOTTOM_OVERLAY, BOTTOM_OVERLAY_FULL, BOTTOM_WITH_WIDGET_RESIZE,
//         LEFT_STATIC, LEFT_OVERLAY, LEFT_OVERLAY_FULL, LEFT_WITH_WIDGET_RESIZE,
//         RIGHT_STATIC, RIGHT_OVERLAY, RIGHT_OVERLAY_FULL, RIGHT_WITH_WIDGET_RESIZE
//         */
//         mWidgetXML.setAttribute("title", "autohide", getIsTitleAutohide(), 0);
//        if (isTitleStatic()) {
//            mWidgetXML.setAttribute("title", "staticSize", getStaticTitleBarSize(false), 0);
//        }
//
//        /**** Behaviour ****/
//        mWidgetXML.setAttribute("behaviour", "drawWidgetChrome", getDrawWidgetChrome(), 0);
//        mWidgetXML.setAttribute("behaviour", "drawWidgetTitle", getDrawWidgetTitle(), 0);
//        
//        /**** Appearance ****/
//        mWidgetXML.setAttribute("appearance", "minimized", getIsMinimized(), 0);
//   
//        if (getShouldPersistTheme()) {
//            mWidgetXML.pushTag("appearance");
//            mWidgetXML.addTag("widgetColor");
//            mWidgetXML.setAttribute("widgetColor", "color", getTheme().getWidgetColorHex(), 0);
//
//            mWidgetXML.addTag("widgetContentColor");
//            mWidgetXML.setAttribute("widgetContentColor", "color", getTheme().getWidgetContentColorHex(), 0);
//
//            mWidgetXML.addTag("widgetAccentColor");
//            mWidgetXML.setAttribute("widgetAccentColor", "color1", getTheme().getWidgetAccent1ColorHex(), 0);
//            mWidgetXML.setAttribute("widgetAccentColor", "color2", getTheme().getWidgetAccent2ColorHex(), 0);
//            mWidgetXML.setAttribute("widgetAccentColor", "color3", getTheme().getWidgetAccent3ColorHex(), 0);
//            mWidgetXML.setAttribute("widgetAccentColor", "color4", getTheme().getWidgetAccent4ColorHex(), 0);
//
//            mWidgetXML.addTag("widgetAlternatingColor");
//            mWidgetXML.setAttribute("widgetAlternatingColor", "color1", getTheme().getWidgetAlternating1ColorHex(), 0);
//            mWidgetXML.setAttribute("widgetAlternatingColor", "color1", getTheme().getWidgetAlternating2ColorHex(), 0);            
//
//            mWidgetXML.addTag("widgetModalBackgroundColor");
//            mWidgetXML.setAttribute("widgetModalBackgroundColor", "color", getTheme().getWidgetModalBackgroundColorHex(), 0);
//
//            mWidgetXML.addTag("widgetAlpha");
//            mWidgetXML.setAttribute("widgetAlpha", "hovered", getTheme().HoveredWidgetAlpha, 0);
//            mWidgetXML.setAttribute("widgetAlpha", "unhovered", getTheme().UnhoveredWidgetAlpha, 0);
//            mWidgetXML.setAttribute("widgetAlpha", "contentChrome", getTheme().ContentChromeAlpha, 0);
//            
//            mWidgetXML.addTag("titleFontColor");
//            mWidgetXML.setAttribute("titleFontColor", "color", getTheme().getTitleFontColorHex(), 0);
//
//            mWidgetXML.addTag("titleFontAlpha");
//            mWidgetXML.setAttribute("titleFontAlpha", "hovered", getTheme().HoveredTitleFontAlpha, 0);
//            mWidgetXML.setAttribute("titleFontAlpha", "unhovered", getTheme().UnhoveredTitleFontAlpha, 0);
//            
//            mWidgetXML.addTag("titleColor");
//            mWidgetXML.setAttribute("titleColor", "color", getTheme().getTitleColorHex(), 0);
//            
//            mWidgetXML.addTag("titleAlpha");
//            mWidgetXML.setAttribute("titleAlpha", "hovered", getTheme().HoveredTitleAlpha, 0);
//            mWidgetXML.setAttribute("titleAlpha", "unhovered", getTheme().UnhoveredTitleAlpha, 0);
//            
//            mWidgetXML.addTag("titleGradientColor");
//            mWidgetXML.setAttribute("titleGradientColor", "color1", getTheme().getTitleGradientColor1Hex(), 0);
//            mWidgetXML.setAttribute("titleGradientColor", "color2", getTheme().getTitleGradientColor2Hex(), 0);
//            mWidgetXML.setAttribute("titleGradientColor", "color3", getTheme().getTitleGradientColor3Hex(), 0);
//            mWidgetXML.setAttribute("titleGradientColor", "color4", getTheme().getTitleGradientColor4Hex(), 0);
//            
//            mWidgetXML.addTag("typographyColor");
//            mWidgetXML.setAttribute("typographyColor", "primary", getTheme().getTypographyPrimaryColorHex(), 0);
//            mWidgetXML.setAttribute("typographyColor", "secondary", getTheme().getTypographySecondaryColorHex(), 0);
//            mWidgetXML.setAttribute("typographyColor", "tertiary", getTheme().getTypographyTertiaryColorHex(), 0);
//            mWidgetXML.setAttribute("typographyColor", "quaternary", getTheme().getTypographyQuaternaryColorHex(), 0);
//
//            mWidgetXML.addTag("selection");
//            mWidgetXML.setAttribute("selection", "foreground", getTheme().getSelectionForegroundColorHex(), 0);
//            mWidgetXML.setAttribute("selection", "background", getTheme().getSelectionBackgroundColorHex(), 0);
//
//            mWidgetXML.addTag("hover");
//            mWidgetXML.setAttribute("hover", "foreground", getTheme().getHoverForegroundColorHex(), 0);
//            mWidgetXML.setAttribute("hover", "background", getTheme().getHoverBackgroundColorHex(), 0);
//
//            mWidgetXML.popTag(); // appearance            
//        }
//
//        mWidgetXML.addTag("elements");
// 
//        TiXmlElement* rootElm = mWidgetXML.doc.RootElement();
//        TiXmlElement* elementsElm = rootElm->FirstChildElement( "elements" );
//        
//        if (elementsElm != NULL) {
//            for(uiVizWidgetElm &elm:mWidgetElements){
//                ofxXmlSettings elmSettings = elm.saveState();
//                string elmXML;
//                elmSettings.copyXmlToString(elmXML);
//                
//                TiXmlElement* elmNode = new TiXmlElement("element");
//                elmNode->Parse( elmXML.c_str(), 0, TIXML_DEFAULT_ENCODING);
//                elementsElm->InsertEndChild(*elmNode);
//            }
//        }
//        mWidgetXML.popTag(); // widget
//
//        return mWidgetXML;
//    }
//    
//    virtual void replaceExpressions(uiVizWidget* w, string& exprStr) {
//        ofStringReplace(exprStr, " ", "");
//
//        string thisPersistentId = w->getPersistentId();
//        string parentPersistentId = "";
//
//        if (w->getPersistentId() == thisPersistentId) {
//            ofStringReplace(exprStr, "${SELF.", "${" + w->getPersistentId() + ".");
//
//            if (w->parent()) {
//                parentPersistentId = w->parent()->getPersistentId();
//                ofStringReplace(exprStr, "${PARENT.", "${" + parentPersistentId + ".");
//                // possible optimization : only if ${PARENT. found .... maybe not though, what if sub widgets to it rely on parent?
//                replaceExpressions(w->parent(), exprStr);
//            }
//
//            if (w->root()) {
//                string rootPersistentId = w->root()->getPersistentId();
//                ofStringReplace(exprStr, "${ROOT.", "${" + rootPersistentId + ".");
//            }
//        }
//
//        if (w->getPersistentId() != "") {
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".X}", ofToString(w->getWidgetStateX()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".Y}", ofToString(w->getWidgetStateY()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".WIDTH}", ofToString(w->getWidgetStateWidth()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".HEIGHT}", ofToString(w->getWidgetStateHeight()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".RIGHT}", ofToString(w->getWidgetStateX()+w->getWidgetStateWidth()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".BOTTOM}", ofToString(w->getWidgetStateY()+w->getWidgetStateHeight()));
//
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_X}", ofToString(w->getX()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_Y}", ofToString(w->getY()));
//
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_USABLE_X_FIXED}", ofToString(w->getUsableX(false)));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_USABLE_Y_FIXED}", ofToString(w->getUsableY(false)));
//
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_USABLE_X}", ofToString(w->getUsableX()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".ABSOLUTE_USABLE_Y}", ofToString(w->getUsableY()));
//
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".USABLE_WIDTH}", ofToString(w->getUsableWidth()));
//            ofStringReplace(exprStr, "${" + thisPersistentId + ".USABLE_HEIGHT}", ofToString(w->getUsableHeight()));
//            
//            ofStringReplace(exprStr, "${WINDOW.WIDTH}", ofToString(w->getViz()->deScale(ofGetWindowWidth()) - w->getScreenPadding()));
//            ofStringReplace(exprStr, "${WINDOW.HEIGHT}", ofToString(w->getViz()->deScale(ofGetWindowHeight()) - w->getScreenPadding()));
//            ofStringReplace(exprStr, "${PADDING}", ofToString(w->getNonScaledPadding()));
//
//            // This is for sibling widgets referencing each other
//            for(uiVizWidget &exprWidget:w->getChildWidgets()) {
//                if (exprWidget.getPersistentId() != "") {
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".X}", ofToString(exprWidget.getX()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".Y}", ofToString(exprWidget.getY()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".WIDTH}", ofToString(exprWidget.getWidgetStateWidth()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".HEIGHT}", ofToString(exprWidget.getWidgetStateHeight()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".RIGHT}", ofToString(exprWidget.getX()+exprWidget.getWidgetStateWidth()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".RIGHT_USABLE_WIDTH}", ofToString(w->getUsableWidth()-exprWidget.getX()-exprWidget.getWidgetStateWidth()+w->getUsableX()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".BOTTOM}", ofToString(exprWidget.getY()+exprWidget.getWidgetStateHeight()));
//                    ofStringReplace(exprStr, "${" + exprWidget.getPersistentId() + ".BOTTOM_USABLE_HEIGHT}", ofToString(w->getUsableHeight()-exprWidget.getY()-exprWidget.getWidgetStateHeight()+w->getUsableY())); 
//                }
//            }
//
//            // This is for sibling elements referencing each other
//            for(uiVizWidgetElm &exprElm:w->getWidgetElements()) {
//                if (exprElm.getPersistentId() != "") {
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".X}", ofToString(exprElm.getX()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".Y}", ofToString(exprElm.getY()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".WIDTH}", ofToString(exprElm.getWidth()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".HEIGHT}", ofToString(exprElm.getHeight()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".RIGHT}", ofToString(exprElm.getX()+exprElm.getWidth()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".RIGHT_USABLE_WIDTH}", ofToString(w->getUsableWidth()-exprElm.getX()-exprElm.getWidth()+w->getUsableX()));                     
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".BOTTOM}", ofToString(exprElm.getY()+exprElm.getHeight()));
//                    ofStringReplace(exprStr, "${" + exprElm.getPersistentId() + ".BOTTOM_USABLE_HEIGHT}", ofToString(w->getUsableHeight()-exprElm.getY()-exprElm.getHeight()+w->getUsableY())); 
//                }
//            }
//
//        }
//    }
//
//    virtual bool getIsMousePressedAndReleasedOverWidget(bool includeWidgetChromeElements) override {
//        bool isMousePressedAndReleasedOverWidget = uiVizWidgetBase::getIsMousePressedAndReleasedOverWidget(includeWidgetChromeElements);
//        if (isMousePressedAndReleasedOverWidget && !includeWidgetChromeElements && isTitleHovered()) {
//            return false;
//        } else {
//            return isMousePressedAndReleasedOverWidget;
//        }
//    }    
// 
//    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {
//        // Override this in derrived widget to handle incoming events from uiVizElements, etc
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//            string xml; args.eventXML.copyXmlToString(xml);
//            ofLogNotice("uiVizWidget") << "[" + getPersistentId() + "] received unhandled event " << args.widgetId << "." << args.eventName << " with data \n" << xml;
//        #endif
//    }
//
//    void recalculateElementExpressions(uiVizWidgetElm* elm) {
//        
//        if (getIgnoreExpr_Layout()) return;
//
//        if (elm->getX_Expr() != "" || elm->getY_Expr() != "" || elm->getWidth_Expr() != "" || elm->getHeight_Expr() != "") {
//            
//            // replace string tokens ${SCREEN.WIDTH}, ${PERSISTENTID.RIGHT}, etc
//            string exprStringX = elm->getX_Expr();
//            string exprStringY = elm->getY_Expr();
//            string exprStringWidth = elm->getWidth_Expr();
//            string exprStringHeight = elm->getHeight_Expr();
//            
//            ofStringReplace(exprStringX, " ", "");
//            ofStringReplace(exprStringY, " ", "");
//            ofStringReplace(exprStringWidth, " ", "");
//            ofStringReplace(exprStringHeight, " ", "");
//            
//            if (exprStringX != "") replaceElementExpressions(elm, exprStringX);
//            if (exprStringY != "") replaceElementExpressions(elm, exprStringY);
//            if (exprStringWidth != "") replaceElementExpressions(elm, exprStringWidth);
//            if (exprStringHeight != "") replaceElementExpressions(elm, exprStringHeight);
//            
//            if (exprStringX != "") {
//                if (calculator.compile(exprStringX.c_str(), expression)) {
//                    elm->setX(expression.value());
//                    //ofLogNotice("uiVizWidgetElm") << elm->getPersistentId() << ".setX(): \"" << elm->getX_Expr() << "\" [ELM:---->" + exprStringX + "<----] = " << ofToString(expression.value());
//                } else {
//                    ofLogWarning("uiVizWidgetElm") << elm->getPersistentId() << ".setX(): failed to evaluate expression \"" << elm->getX_Expr() << "\" [ELM:---->" + exprStringX + "<----] : " << calculator.error().c_str();
//                }
//            }
//            
//            if (exprStringY != "") {
//                if (calculator.compile(exprStringY.c_str(), expression)) {
//                    elm->setY(expression.value());
//                    //ofLogNotice("uiVizWidgetElm") << elm->getPersistentId() << ".setY(): \"" << elm->getY_Expr() << "\" [ELM:---->" + exprStringY + "<----] = " << ofToString(expression.value());
//                } else {
//                    ofLogWarning("uiVizWidgetElm") << elm->getPersistentId() << ".setY: failed to evaluate expression \"" << elm->getY_Expr() << "\" [ELM:---->" + exprStringY + "<----] : " << calculator.error().c_str();
//                }
//            }
//            
//            if (exprStringWidth != "") {
//                if (calculator.compile(exprStringWidth.c_str(), expression)) {
//                    elm->setWidth(expression.value());
//                    //ofLogNotice("uiVizWidgetElm") << elm->getPersistentId() << ".setWidth(): \"" << elm->getWidth_Expr() << "\" [ELM:---->" + exprStringWidth + "<----] = " << ofToString(expression.value());
//                } else {
//                    ofLogWarning("uiVizWidgetElm") << elm->getPersistentId() << ".setWidth: failed to evaluate expression \"" << elm->getWidth_Expr() << "\" [ELM:---->" + exprStringWidth + "<----] : " << calculator.error().c_str();
//                }
//            }
//            
//            if (exprStringHeight != "") {
//                if (calculator.compile(exprStringHeight.c_str(), expression)) {
//                    elm->setHeight(expression.value());
//                    //ofLogNotice("uiVizWidgetElm") << elm->getPersistentId() << ".setHeight(): \"" << elm->getHeight_Expr() << "\" [ELM:---->" + exprStringHeight + "<----] = " << ofToString(expression.value());
//                } else {
//                    ofLogWarning("uiVizWidgetElm") << elm->getPersistentId() << ".setHeight(): failed to evaluate expression \"" << elm->getHeight_Expr() << "\" [ELM:---->" + exprStringHeight + "<----] : " << calculator.error().c_str();
//                }
//            }
//
//        }
//    }
//
//    void replaceElementExpressions(uiVizWidgetElm* elm, string& exprStr) {
//
//        int absoluteX = elm->getX();
//        int absoluteY = elm->getY();
//
//        if (elm->parent()) {
//            absoluteX = 0;
//            absoluteY = 0;
//        }
//  
//        string thisPersistentId = elm->getPersistentId();
//        if (elm->getPersistentId() == thisPersistentId) {
//            ofStringReplace(exprStr, "${SELF.", "${" + thisPersistentId + ".");
//        }
//
//
//        ofStringReplace(exprStr, "${PARENT.ABSOLUTE_X}", ofToString(absoluteX));
//        ofStringReplace(exprStr, "${PARENT.ABSOLUTE_Y}", ofToString(absoluteY));
//        /*      
//        ofStringReplace(exprStr, "${PARENT.ABSOLUTE_USABLE_X}", ofToString(this->getUsableX()));
//        ofStringReplace(exprStr, "${PARENT.ABSOLUTE_USABLE_Y}", ofToString(this->getUsableY()));
//        */
//
//        ofStringReplace(exprStr, "${PARENT.USABLE_WIDTH}", ofToString(this->getUsableWidth()));
//        ofStringReplace(exprStr, "${PARENT.USABLE_HEIGHT}", ofToString(this->getUsableHeight()));
//        
//        ofStringReplace(exprStr, "${PARENT.WIDTH}", ofToString(this->getWidgetStateWidth()));
//        ofStringReplace(exprStr, "${PARENT.HEIGHT}", ofToString(this->getWidgetStateHeight()));
//        ofStringReplace(exprStr, "${PADDING}", ofToString(getNonScaledPadding()));
// 
//        int relativeX = this->getUsableX() - this->getX();
//        int relativeY = this->getUsableY() - this->getY();
//        int relativeX_Fixed = this->getUsableX(false) - this->getX();
//        int relativeY_Fixed = this->getUsableY(false) - this->getY();
//
//
//        ofStringReplace(exprStr, "${PARENT.CENTER_X}", ofToString((getCoreUsableWidth() - (float)elm->getWidth())/2 + relativeX));
//        ofStringReplace(exprStr, "${PARENT.CENTER_Y}", ofToString((getCoreUsableHeight() - (float)elm->getHeight())/2 + relativeY));
//        ofStringReplace(exprStr, "${PARENT.LEFT}", ofToString(relativeX));
//        ofStringReplace(exprStr, "${PARENT.RIGHT}", ofToString(getWidgetStateWidth() - elm->getWidth() - getNonScaledPadding() - (isTitleRight() ? (isTitleResize() ? mUICurrentTitleBarSize : getUnhoveredTitleBarSize(false)) : 0)));
//        ofStringReplace(exprStr, "${PARENT.TOP}", ofToString(relativeY));
//        ofStringReplace(exprStr, "${PARENT.BOTTOM}", ofToString(getWidgetStateHeight() - (float)elm->getHeight() - (float)getNonScaledPadding() - (isTitleBottom() ? (isTitleResize() ? mUICurrentTitleBarSize : getUnhoveredTitleBarSize(false)) : 0)));
//        
//        ofStringReplace(exprStr, "${PARENT.LEFT_FIXED}", ofToString(relativeX_Fixed));
//        ofStringReplace(exprStr, "${PARENT.TOP_FIXED}", ofToString(relativeY_Fixed));
//
//
//        for(uiVizWidget &exprWidget:getChildWidgets()) {
//            if (exprWidget.getPersistentId() != "") {
//                string exprWidgetId = exprWidget.getPersistentId();
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".X}", ofToString(exprWidget.getX()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".Y}", ofToString(exprWidget.getY()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".WIDTH}", ofToString(exprWidget.getWidgetStateWidth()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".HEIGHT}", ofToString(exprWidget.getWidgetStateHeight()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".RIGHT}", ofToString(exprWidget.getX()+exprWidget.getWidgetStateWidth()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".RIGHT_USABLE_WIDTH}", ofToString(getUsableWidth()-(exprWidget.getX()+exprWidget.getWidgetStateWidth())+getUsableX()));               
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".BOTTOM}", ofToString(exprWidget.getY()+exprWidget.getWidgetStateHeight()));
//                ofStringReplace(exprStr, "${" + exprWidgetId + ".BOTTOM_USABLE_HEIGHT}", ofToString(getUsableHeight()-(exprWidget.getY()+exprWidget.getWidgetStateHeight())+getUsableY()));
//            }
//        }
//
//        for(uiVizWidgetElm &exprElm:mWidgetElements) {
//            if (exprElm.getPersistentId() != "") {
//                string exprElmId = exprElm.getPersistentId();
//                ofStringReplace(exprStr, "${" + exprElmId + ".X}", ofToString(exprElm.getRelativeX()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".Y}", ofToString(exprElm.getRelativeY()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".WIDTH}", ofToString(exprElm.getWidgetStateWidth()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".HEIGHT}", ofToString(exprElm.getWidgetStateHeight()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".RIGHT}", ofToString(exprElm.getRelativeX()+exprElm.getWidgetStateWidth()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".RIGHT_USABLE_WIDTH}", ofToString(getUsableWidth()-(exprElm.getX()+exprElm.getWidgetStateWidth())+getUsableX()));                
//                ofStringReplace(exprStr, "${" + exprElmId + ".BOTTOM}", ofToString(exprElm.getRelativeY()+exprElm.getWidgetStateHeight()));
//                ofStringReplace(exprStr, "${" + exprElmId + ".BOTTOM_USABLE_HEIGHT}", ofToString(getUsableHeight()-(exprElm.getY()+exprElm.getWidgetStateHeight())+getUsableY()));
//                                  
//            }
//        }
//    }
//    
//    uiVizWidgetElm* addOrLoadWidgetElement(uiVizWidgetElm* elm, string ELM_CLASS, string persistentId, string widgetXML) {
//        mapElements();
//         // Does the class exist in the map?
//        if (elmClassMap.count(ELM_CLASS) > 0) {
//
//            uiVizWidgetElm* existingElm = getWidgetElement(persistentId);
//
//            if (existingElm != nullptr) {
//                // existingElm->loadState(widgetXML); don't do this - causes dynamically loaded elms to lose their value!
//                elm = existingElm;
//            } else {
//                elm = elmClassMap[ELM_CLASS](persistentId, widgetXML, this);   
//                addWidgetElement(*elm);                    
//            }
//            
//            return elm;
//        } else {
//            ofLogWarning("uiVizWidget") << "[Element:" << persistentId << "] of class \"" << ELM_CLASS << "\" failed to load. [" + widgetXML + "]";
//        }
//
//        return elm;
//    }
//
//    uiVizWidgetElm* getWidgetElement(string persistentId) {
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            if (ofToLower(elm.getPersistentId()) == ofToLower(persistentId)) {
//                return &elm;
//            }
//        }
//        #if VIZ_DEBUG_LEVEL >= 1 && VIZ_DEBUG_LEVEL < 2
//        ofLogError("uiVizWidget") << "Expected element [" << getPersistentId() << "->" << "" << persistentId << "] was NOT found! (Segfault likely!)";
//        #endif
//        return nullptr;
//    }
//    
//    virtual int getWidgetElementIndex(string persistentId) override {
//        int idx = 0;
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            if (ofToLower(elm.getPersistentId()) == ofToLower(persistentId)) {
//                return idx;
//            }
//            idx++;
//        }
//        return 0;
//    }
//
//    virtual int getWidgetElementSize() override {
//        return mWidgetElements.size();
//    }    
//    
//    bool focusWidgetElement(uiVizWidgetElm &e) {
//        return focusWidgetElement(e.getPersistentId());
//    }
//    
//    bool focusNextWidgetElement() {
//        if (getDidMoveFocus()) return false;
//        bool nextElmShouldFocus = false;
//        if (mWidgetElements.size() > 0) {
//            
//            for(uiVizWidgetElm &elm:mWidgetElements){
//                
//                if (nextElmShouldFocus) {
//
//                    if (elm.getIsVisible()) {
//                        focusWidgetElement(elm.getPersistentId());
//                        setDidMoveFocus(true);
//                        return true;
//                    }
//                }
//                
//                if (elm.getIsFocused(false)) {
//                    nextElmShouldFocus = true;
//                }
//            }
//            
//            // We didn't focus the next, back to 1st...
//            for(uiVizWidgetElm &elm:mWidgetElements) {
//                focusWidgetElement(elm.getPersistentId());
//                setDidMoveFocus(true);
//                return true;
//            }
//            
//        }
//        return false;
//    }
//    
//    bool focusWidgetElement(string persistentId) {
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            elm.setIsFocused(false);
//            elm.setIsSiblingFocused(false);
//        }
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            if (elm.getPersistentId() == persistentId) {
//                elm.setActiveWidget();
//                elm.setWidgetNeedsUpdate(true);
//                elm.setNeedsUpdate(true);
//                setWidgetNeedsUpdate(true);
//                setNeedsUpdate(true);
//                
//                // Let all siblings know that one of them is focused...
//                for(uiVizWidgetElm &elmSib:mWidgetElements){
//                    elmSib.setIsSiblingFocused(true);
//                }
//                
//                elm.setIsFocused(true);
//                elm.setIsSiblingFocused(false);
//                
//                return true;
//            }
//        }
//        return false;
//    }
//    
//    uiVizWidgetElmLabel* getLabel(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmLabel*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmButton* getButton(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmButton*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmTextarea* getTextarea(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmTextarea*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmTextbox* getTextbox(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmTextbox*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmSlider* getSlider(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmSlider*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmCheckbox* getCheckbox(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmCheckbox*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmDropdown* getDropdown(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmDropdown*>(getWidgetElement(persistentId));
//    }
//    
//    uiVizWidgetElmBreadcrumb* getBreadcrumb(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmBreadcrumb*>(getWidgetElement(persistentId));
//    }    
//    
//    uiVizWidgetElmImage* getImage(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmImage*>(getWidgetElement(persistentId));
//    }    
//    
//    uiVizWidgetElmProgressBar* getProgressBar(string persistentId) {
//        return dynamic_cast<uiVizWidgetElmProgressBar*>(getWidgetElement(persistentId));
//    }    
//
//    void removeWidgetElement(uiVizWidgetElm* e) {
//        
//        if (e == nullptr || mWidgetElements.size() == 0) return;
//        
//        for(uiVizWidgetElm &elm:mWidgetElements){
//            if (ofToLower(elm.getPersistentId()) == ofToLower(e->getPersistentId())) {
//
//                #if VIZ_DEBUG_LEVEL >= 1 && VIZ_DEBUG_LEVEL < 2
//                    cout << "REMOVING ELEMENT [" << e->getPersistentId() << "] FROM WIDGET: [" << getPersistentId() << "]\n";
//                #endif                    
//                
//                mWidgetElements.erase(std::remove_if(
//                                              mWidgetElements.begin(), mWidgetElements.end(),
//                                              [&](uiVizWidgetElm &element) {
//                                                  return ofToLower(element.getPersistentId()) == ofToLower(e->getPersistentId());
//                                              }),  mWidgetElements.end());
//
//                delete &elm;
//                return;
//                
//            }
//        }
//    }
//
//    uiVizWidget* parentWidget() {
//        return mParent;
//    }  
//
//    uiVizWidget* rootWidget() {
//        uiVizWidget* r = this;
//        uiVizWidget* w = parentWidget();
//        while(w) {
//            w = w->parentWidget();
//            r = w;
//        }   
//        return r; 
//    }        
//    
//    virtual void update(uiVizWidgetContext context) override {
//        // Implemented by descendant class...
//    }
//    
//    virtual bool needsUpdateBeforeDraw(bool shouldResetTimer) {
//        // Implemented by descendant class if needed...
//        return false;
//    }
//    
//    virtual void draw(uiVizWidgetContext context) override {
//        // Implemented by descendant class...
//    }
//    
//    virtual void updateMinimized() {
//        // Implemented by descendant class...
//    }
//    
//    virtual void drawMinimized() {
//        // Implemented by descendant class...
//    }
//
//    bool isWidgetHovered() override {
//        //if (!getIsVisible()) return false;
//        return widgetFrame.isHovered_Rect();
//    }
//    
//    bool isTitleHovered() {
//        return widgetTitle.isHovered_Rect();
//    }
//    
//    bool isInsideWidgetBounds(int x, int y, int width, int height) {
//        return y >= getUsableY(false) && y + height < getUsableY(false) + getUsableHeight();
//        //& x >= getUsableX(false) && x + width < getUsableX(false) + getUsableWidth();
//    }
//
//    bool isInsideWidgetBoundsY(int y, int height) {
//        return y >= getUsableY(false) && y + height < getUsableY(false) + getUsableHeight();
//    }    
//    
//    virtual void setExpressionRecalculationRequired(bool val) override {
//        uiVizWidgetBase::setExpressionRecalculationRequired(val);
//        for(uiVizWidget &widget:mChildWidgets) {
//            widget.uiVizWidgetBase::setExpressionRecalculationRequired(val);
//        }
//    }
//
//    void clearChildWidgets() {
//        while(mChildWidgets.size() > 0) {
//            for(uiVizWidget &widget:mChildWidgets) {
//                removeChildWidget(widget);
//            }
//        }
//    }    
//    
//    void setChildWidgetsVisibility(bool val) {
//        for(uiVizWidget &widget:mChildWidgets){
//            widget.setIsVisible(val);
//        }
//    }
//    
//    uiVizWidget* parent() {
//        return mParent;
//    }
//
//    uiVizWidget* getChildWidget(string widgetId) {
//        for(uiVizWidget &widget:mChildWidgets){
//            if (widget.getWidgetId() == widgetId) return &widget;
//        }
//        return nullptr;
//    }
//
//    uiVizWidget* getChildWidgetByPersistentId(string persistentId) {
//        for(uiVizWidget &widget:mChildWidgets){
//            if (widget.getPersistentId() == persistentId) return &widget;
//        }
//        return nullptr;
//    }    
//
//    //! Is called when a child is added to this widget. Use this method to manipulate child widgets after they are added
//    virtual void onChildWidgetAdded(uiVizWidget &widget) {
//    }
//
//    //! Is called when all child widgets have been loaded to this widget by WidgetManager. Use this method to manipulate child widgets after they are added
//    virtual void onChildWidgetsLoaded() {
//    }    
//
//    void addChildWidget(uiVizWidget &widget) {
//        addChildWidget(widget, false);
//    }
//
//    void addChildWidget(uiVizWidget &widget, bool hideTitleBar) {
//        addChildWidgetDocked(widget, DockLocation::NONE, false, hideTitleBar);
//    }
//    
//    void addChildWidgetDocked(uiVizWidget &widget, DockLocation dockLocation, bool usePadding, bool hideTitleBar) {
//        removeChildWidget(widget);
//
//        switch(dockLocation) {
//            case DockLocation::TOP:
//                widget.setX_Expr("${PARENT.ABSOLUTE_USABLE_X}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setY_Expr("${PARENT.ABSOLUTE_USABLE_Y}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setWidth_Expr("${PARENT.USABLE_WIDTH}" + std::string(!usePadding ? " + ${PADDING}*2" : ""));
//                break;
//            case DockLocation::BOTTOM:
//                widget.setX_Expr("${PARENT.ABSOLUTE_USABLE_X}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setY_Expr("${PARENT.BOTTOM} - ${SELF.HEIGHT}" + std::string(usePadding ? " - ${PADDING}" : ""));
//                widget.setWidth_Expr("${PARENT.USABLE_WIDTH}" + std::string(!usePadding ? " + ${PADDING}*2" : ""));
//                break;
//            case DockLocation::LEFT:
//                widget.setX_Expr("${PARENT.ABSOLUTE_USABLE_X}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setY_Expr("${PARENT.ABSOLUTE_USABLE_Y}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setHeight_Expr("${PARENT.USABLE_HEIGHT}" + std::string(!usePadding ? " + ${PADDING}*2" : ""));
//                break;
//            case DockLocation::RIGHT:
//                widget.setX_Expr("${PARENT.RIGHT} - ${SELF.WIDTH}" + std::string(usePadding ? " - ${PADDING}" : ""));
//                widget.setY_Expr("${PARENT.ABSOLUTE_USABLE_Y}" + std::string(!usePadding ? " - ${PADDING}" : ""));
//                widget.setHeight_Expr("${PARENT.USABLE_HEIGHT}" + std::string(!usePadding ? " + ${PADDING}*2" : ""));
//                break;
//            case DockLocation::NONE:
//                break;
//        }
//
//        if (dockLocation != DockLocation::NONE || hideTitleBar) {
//            if (!usePadding) widget.setIsRoundedRectangle(getIsRoundedRectangle());
//            widget.setIsDraggable(false);
//            widget.setIsResizable(false);
//            widget.setTitleStyle(TitleStyle::NONE);
//        }
//        
//        widget.mParent = this;
//        widget.setIsShadow(false);
//        mChildWidgets.push_back(widget);
//        widget.setWasJustInitialized(true);
//        ofAddListener(widget.widgetEventReceived, this, &uiVizWidget::onWidgetEventReceived);
//        uiVizWidgetEventArgs args = uiVizWidgetEventArgs(getWidgetId(), *this);
//        widget.onWidgetAddedAsChild(args);
//        onChildWidgetAdded(widget);        
//    }
//    
//    void removeChildWidget(string widgetId) {
//        
//        for(uiVizWidget &widget:mChildWidgets){
//            if (widget.getWidgetId() == widgetId) {
//
//                ofRemoveListener(widget.widgetEventReceived, this, &uiVizWidget::onWidgetEventReceived);
//
//                std::vector<std::reference_wrapper<uiVizWidget>> childrenWidgets = widget.getChildWidgets();
//
//                widget.beforeDelete();
//                mChildWidgets.erase(std::remove_if(
//                                              mChildWidgets.begin(), mChildWidgets.end(),
//                                              [&](uiVizWidget &widget) {
//                                                  return widget.getWidgetId() == widgetId;
//                                              }),  mChildWidgets.end());
//                
//                delete &widget;
//
//                for(uiVizWidget &childOfWidget:childrenWidgets) {
//                    #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
//                    cout << "<----[" << widget.getPersistentId() << "." << childOfWidget.getPersistentId() << "]~ChildWidget()\n";     
//                    #endif                    
//                
//                    childOfWidget.deleteThisWidget();
//                    childOfWidget.clearChildWidgets();
//                }
//
//
//
//                return;
//            }
//        }
//    }
//
//    void removeChildWidgetByPersistentId(string persistentId) {
//        for(uiVizWidget &widget:mChildWidgets) {
//            if (widget.getPersistentId() == persistentId) {
//                removeChildWidget(widget.getWidgetId());
//                return;
//            }
//        }
//    }    
//
//    void removeChildWidget(uiVizWidget &w) {
//        for(uiVizWidget &widget:mChildWidgets){
//            if (widget.getWidgetId() == w.getWidgetId()) {
//                removeChildWidget(w.getWidgetId());
//            }
//        } 
//    }
//
//    uiVizWidget* findChildWidget(string widgetId) {
//        for(uiVizWidget& childWidget:getChildWidgets()){
//            uiVizWidget* w = findChildWidget(&childWidget, widgetId);
//            if (w) return w;
//        } 
//        return nullptr;
//    } 
//
//    uiVizWidget* findChildWidget(uiVizWidget* parentWidget, string widgetId) {
//        if (parentWidget && parentWidget->matchesWidgetId(widgetId)) {
//            return parentWidget;
//        }
//
//        for(uiVizWidget& childWidget:parentWidget->getChildWidgets()){
//            uiVizWidget* w = findChildWidget(&childWidget, widgetId);
//            if (w) {
//                return w;
//            }
//        } 
//        return nullptr;
//    }     
//
//    virtual std::vector<std::reference_wrapper<uiVizWidget>> getChildWidgets() {
//        // Implemented by descendant class...
//        return mChildWidgets;
//    }
//
//    bool hasActiveChildWidgets() {
//        for(uiVizWidget &widget:getChildWidgets()){
//            if (widget.getIsActiveWidget()) {
//                return true;
//            }
//        }
//        return false;
//    }      
//
//    void updateWidget() {
//        if (!getIsVisible()) {
//            setWidgetNeedsUpdate(false);
//            return;
//        }
//        
//        // if (getIsMinimized()) {
//        //     setWidgetNeedsUpdate(false);
//        //     updateMinimized();
//
//        // }
//
//        if (!widgetNeedsUpdate()){
//            return;
//        }
//       // updateWidgetPopoutArrow();        
//        setWidgetNeedsUpdate(false);
//        updateWidgetUI();
//        if (!getIsMinimized()) {
//            update(this->context);
//        } else {
//            updateMinimized();
//        }
//        updateWidgetElements();
//    }
//    
//    void drawWidgetContentBlock(int x, int y, int width, int height) {
//        getIsRoundedRectangle() ? vizElm_WIDGET_CONTENT_BLOCK.setRectRounded(scale(x), scale(y), scale(width), scale(height), getScaledPadding(), getTheme().WidgetContentColor) :
//            vizElm_WIDGET_CONTENT_BLOCK.setRectangle(scale(x), scale(y), scale(width), scale(height), getTheme().WidgetContentColor);
//
//        vizElm_WIDGET_CONTENT_BLOCK.draw();
//    }
//
//    void drawWidgetContentBlock() {
//        getIsRoundedRectangle() ? vizElm_WIDGET_CONTENT_BLOCK.setRectRounded(scale(getUsableX()), scale(getUsableY()), scale(getUsableWidth()), scale(getUsableHeight()), getScaledPadding(), getTheme().WidgetContentColor) :
//            vizElm_WIDGET_CONTENT_BLOCK.setRectangle(scale(getUsableX()), scale(getUsableY()), scale(getUsableWidth()), scale(getUsableHeight()), getTheme().WidgetContentColor);
//
//        vizElm_WIDGET_CONTENT_BLOCK.draw();
//    }
//
//    void coreBeforeDraw() {
//        if (!needsUpdate()) setNeedsUpdate(needsUpdateBeforeDraw(true));
//    }
//    
//    void coreDraw() {
//               
//        bool widgetContentUpdated = false;
//
//        if (needsUpdate()) {
//            getWidgetTelemetry()->startUpdate(); //////////////////////////////////////////////////////////
//            // This is needed for automatic resize widgets
//            setNeedsUpdate(false);
//            if (!getIsMinimized()) {
//                update(this->context); 
//            } else {
//                updateMinimized();
//            }
//            updateWidgetElements();
//            widgetContentUpdated = true;
//            getWidgetTelemetry()->endUpdate(); //////////////////////////////////////////////////////////
//        }
//        
//        if (widgetNeedsUpdate()) {
//            updateWidget();
//            updateWidgetUI();
//
//            if (widgetContentUpdated || getWidgetStateWidth() != mFboAllocatedWidth || getWidgetStateHeight() != mFboAllocatedHeight) {
//                // Only update content if the bounds of the widget have changed
//                widgetContentUpdated = true;
//            }
//        } 
//               
//        if (!getIsDragging() && !getIsResizing()) {
//            ofPushStyle();
//            drawWidgetUI(!isTitleStatic());
//            ofPopStyle();
//            
//            coreDrawWidgetContent(widgetContentUpdated);
//            
//            //--------------------------- TITLE HOVER (OVERLAY) -----------------------------------
//           if (!isTitleStatic()) {
//                ofPushStyle();
//                drawWidgetUITitle(false);
//                ofPopStyle();
//            }
//            
//        } else {       
//
//            coreDrawWidgetContent(widgetContentUpdated);         
//
//            ofPushStyle();
//            drawWidgetUI(false);
//            ofPopStyle();
//
//   
//        }
//        
//        if (getIsActiveWidget() && getScrollAction() == ScrollAction::SCROLL) coreDrawWidgetScrollbars(getTheme().WidgetAccentHighContrast1Color_withAlpha(0.5f)); // drawWidgetScrollbars(getTitleColor(getContentChromeAlpha()));
//
///*
//        if (getWidgetId() == getTargetDropWidgetId()) {
//            drawPotentiallyDropTargetIndication();
//        }
//*/
// 
//    }
//    
//    
//    void clearWidgetElements() {
//        while(mWidgetElements.size() > 0) {
//            for(uiVizWidgetElm &elm:mWidgetElements) {
//                removeWidgetElement(&elm);
//            }
//        }
//    }
//    
//    void drawWidgetElements() {
//        for(uiVizWidgetElm &elm:mWidgetElements) {
//    
//            if (elm.getIsVisible()) {
//                elm.coreDraw();
//                
//                if (getDidMoveFocus()) {
//                    // Reset the flag, and jump out
//                    setDidMoveFocus(false);
//                    return;
//                }
//            }
//        }
//    }
//    
//    virtual vector<reference_wrapper<uiVizWidgetElm>> getWidgetElements() {
//        return mWidgetElements;
//    }
//    
//    bool isWidgetElementActive() {
//        //if (!getIsActiveWidget()) return false; // if mouse loses focus from one widget directly onto an ELM, it doesn't activate if this line is uncommented
//        mTransitioningAlpha = false;
//        for(uiVizWidgetElm &elm:mWidgetElements) {
//            if (elm.needsUpdate()) {
//                if (elm.parent()) elm.parent()->setNeedsUpdate(true);
//                elm.setNeedsUpdate(false);
//            }
//            if (elm.getIsFocused(true) && elm.parent()->isTopLevel()) return true; // focused and PARENT widget is active
//            if (elm.isTransitioningAlpha()) mTransitioningAlpha = true;
//            if (elm.getIsActiveWidget() || (elm.parent()->isTopLevel() && elm.isWidgetHovered())) {
//                //elm.setZindex(0);
//                //elm.getIsActiveWidget();
//                return true;
//            }
//        }
//        return false;
//    }
//    
//    void updateWidgetElements() {
//        for(uiVizWidgetElm &elm:mWidgetElements) {
//            recalculateElementExpressions(&elm);
//            elm.setShouldRedetermineElementVisibility(true);
//            if (elm.getIsVisible()) {
//                elm.update(this->context);
//            }
//        }
//    }
//    
//    void coreDrawWidgetContent(bool widgetContentUpdated) {
//        if (!getUseFbo()) {
//            /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//             Draw directly to screen
//             -------------------------
//             Slower, more beautiful
//             *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
//            getWidgetTelemetry()->startDraw(); //////////////////////////////////////////////////////////
//                
//            ofPushStyle();
//            if (getIsMinimized()) {
//                drawMinimized();
//            } else {
//                draw(this->context);
//
//                ofPushStyle();
//                drawWidgetUITitle(false);
//                ofPopStyle();
//
//                drawWidgetElements();
//            }
//            ofPopStyle();
//            getWidgetTelemetry()->endDraw(); //////////////////////////////////////////////////////////        
//        } else {
//            /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//             Draw using a Frame Buffer
//             -------------------------
//             Slightly less beautiful (color accuracy), faster performance
//             *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
//            
//            // NOTE: because we refresh the fbo if getIsActiveWidget(), it means that if the widget is
//            // hovered, updates will take place... consider optimization in the future
//            
//            if ((getIsActiveWidget() && getIsAutoUpdateWhenActive()) || widgetContentUpdated || isWidgetElementActive() || isTransitioningAlpha()) {
//                
//                getWidgetTelemetry()->startDraw(); //////////////////////////////////////////////////////////
//
//                allocateFbo(false);
//                
//                fbo.begin();
//                ofClear(0, 0, 0, 0);
//                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//                
//                ofPushMatrix();
//                ofTranslate(-1*scale(getWidgetStateX()), -1*scale(getWidgetStateY()));
//                ofPushStyle();
//                if (getIsMinimized()) {
//                    drawMinimized();
//                } else {
//                    draw(this->context);
//
//                    ofPushStyle();
//                    drawWidgetUITitle(false);
//                    ofPopStyle();
//
//                    drawWidgetElements();
//                }
//                ofPopStyle();
//                ofPopMatrix();
//                fbo.end();
//
//                getWidgetTelemetry()->endDraw(); //////////////////////////////////////////////////////////        
//            }
//			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//            fbo.draw(scale(getWidgetStateX()), scale(getWidgetStateY()), mFboAllocatedWidth, mFboAllocatedHeight);
//            ofEnableAlphaBlending();
//        }
//    }
//
//    virtual void drawWidget() {
//        if (!getIsVisible()) {
//            return;
//        }
//        
//        coreBeforeDraw();
//        handleDrawEvents();
//        coreDraw();
//    }  
//
//    void handleDrawEvents() {
//        uiVizWidgetEventArgs args = uiVizWidgetEventArgs(getWidgetId(), *this);
//        
//        bool hovered = isWidgetHovered();
//        
//        if (hovered) {
//            setTargetDropWidgetId();
//        }
//        
//        if (hovered && !getIsDragging() && !getIsResizing() && !getViz()->getIsAnyWidgetDraggingOrResizing()) {
//            setUpdatedSinceUnhovered(false);
//            ofNotifyEvent(widgetHovered, args);
//            
//            if (getIsTitleAutohide()) {
//                mDidUpdateForAutohide = false;
//            }
//
///*
//            todo
//            file picker save
//            color (transparrency of menus)
//            ne wproject wizzard
//            package DMG - missing files
//            RELEASE 
//
//*/            
//
//            uiVizWidgetBase* r = root();
//
//            if ((isTopLevel() || getActiveWidgetId() == "") || (r && getViz()->getTopmostActiveRootWidgetId() == r->getWidgetId())) {
//                if (!getIsActiveWidget() && getIsNextInLineForFocus()) {
//                    setActiveWidget();
//                    onWidgetHovered(args);
//                    /*
//
//                    // At one point the above line and below commented were at odds with each other:
//                    // With above line active and below commented, sometimes there are cases where 
//                    // context menu, when clicked would allow a widget (behind the top active widget)
//                    // to "jump forward" in Zindex. Below fixed that. Howevever, with below uncommented
//                    // context menus for clipboard dont respond, because it doesnt become active!!
//
//                    if (parentWidget()) {
//                        // Dealing with a child widget
//                        if (parentWidget()->getIsActiveWidget()) setActiveWidget();
//                    } else {
//                        setActiveWidget();
//                    }//*/
//
//                    for(uiVizWidget &childWidget:getChildWidgets()) {
//                        if (childWidget.isWidgetHovered()) {
//                            getViz()->setActiveChildWidgetId(childWidget.getWidgetId());
//                            childWidget.setUpdatedSinceUnhovered(false);
//                        } else {
//                            if (!childWidget.getUpdatedSinceUnhovered()) {
//                                childWidget.setNeedsUpdate(true);
//                                childWidget.setUpdatedSinceUnhovered(true);
//                                //cout << "updating child..." + childWidget.getPersistentId() + "_" + ofToString(ofGetSystemTimeMillis());
//                            }
//                        }
//                    }
//
//                }
//
//                onWidgetMouseOver(args);
//                if (ofGetMousePressed()) ofNotifyEvent(widgetClicked, args);
//            }
//            
//        } else if (!getViz()->getIsAnyWidgetDraggingOrResizing() && getIsActiveWidget()) {
//            clearTargetDropWidgetId();
//            
//            if (!getUpdatedSinceUnhovered()) {
//                setNeedsUpdate(true);
//                setUpdatedSinceUnhovered(true);
//                //cout << "updating PARENT..." + getPersistentId() + "_" + ofToString(ofGetSystemTimeMillis());
//            }
//
//            ofNotifyEvent(widgetUnhovered, args);
//            onWidgetUnhovered(args);
//            if (ofGetMousePressed()) {         
//                ofNotifyEvent(widgetLostFocus, args);
//                clearActiveWidgetId();               
//            } else if (getIsUnhoverLoseFocus()) {
//                clearActiveWidgetId();
//            }
//        } else {
//            // This is an inactive widget
//            if (!getIsActiveWidget() && getShouldCloseIfOtherWidgetClicked() && ofGetMousePressed() && !getIsDragging() && !getIsResizing()) {
//                closeThisWidget("CLOSED_DEFOCUSED");
//            }     
//        }
//        
//    }
//    
//    virtual vector<uiVizIcon> getWidgetTitleIcons() {
//        // Override in descendant to modify...
//        if (!getShowTitleIcons()) return vector<uiVizIcon>();
//        
//        if (getShowWidgetPin()) {
//            return {
//                uiVizIconCache::getIcon("REG_WIDGET_CLOSE"),
//                getIsWidgetPinned() ? uiVizIconCache::getIcon("REG_REG_RADIO_BUTTON_CHECKED") :
//                                    uiVizIconCache::getIcon("REG_REG_RADIO_BUTTON_UNCHECKED")
//            };
//        } else {
//            return {
//                uiVizIconCache::getIcon("REG_WIDGET_CLOSE")
//            };
//        }
//    }
//
//    vector<uiVizIcon> getPositionedTitleIcons() {
//        return mPositionedTitleIcons;
//    }    
//    
//    virtual vector<uiVizIcon> getWidgetTitleHoveredIcons() {
//        // Override in descendant to modify...
//        if (!getShowTitleIcons()) return vector<uiVizIcon>();
//        
//        return getWidgetTitleIcons();
//    }
//    
//    virtual vector<uiVizIcon> getWidgetTitleMinimizedIcons() {
//        // Override in descendant to modify...
//        if (!getShowTitleIcons()) return vector<uiVizIcon>();
//        
//        return {
//            uiVizIconCache::getIcon("REG_WIDGET_EXPAND_UP")
//        };
//    }
//
//    virtual void titleIconClicked(int iconTag, uiVizCoord::vizBounds deScaledClickBounds) {
//        switch(iconTag) {
//            case uiVizIconCache::IconTag::WIDGET_CLOSE: 
//                closeThisWidget();
//                break;
//            case uiVizIconCache::IconTag::WIDGET_EXPAND_DOWN:
//                setIsMinimized(true);
//                break;
//            case uiVizIconCache::IconTag::WIDGET_EXPAND_UP:
//                setIsMinimized(false);
//                break;
//            case uiVizIconCache::IconTag::WIDGET_PIN:
//                setIsWidgetPinned(false);
//                break;
//            case uiVizIconCache::IconTag::WIDGET_UNPIN:
//                setIsWidgetPinned(true);
//                break;
//        }
//    }
//    
//    virtual void titleIconHovered(int iconTag, uiVizCoord::vizBounds deScaledClickBounds) {
//
//        if(!getShowPopoutWidgetWhenTitleMenuIconHovered()) return;
//
//        uiVizWidget* w = getPopoutWidgetForMenuTag(iconTag);
//        if (w != nullptr && w != NULL) {
//
//            w->setMinWidth(8);
//            w->setMinHeight(8);
//
//            
//            w->setWidgetMinimizedSize(deScale(deScaledClickBounds.width),
//                                      deScale(deScaledClickBounds.height));
//            
//            w->setWidgetBounds(deScaledClickBounds.x,
//                               deScaledClickBounds.y,
//                               deScaledClickBounds.width,
//                               deScaledClickBounds.height);
//            
//
//
//            w->setIsVisible(true);
//            w->setNeedsUpdate(true);
//            w->setActiveWidget();
//        }
//        
//    }
//
//    bool getShowPopoutWidgetWhenTitleMenuIconHovered() {
//        return mShowPopoutWidgetWhenTitleMenuIconHovered;
//    }
//
//    void setShowPopoutWidgetWhenTitleMenuIconHovered(bool val) {
//        mShowPopoutWidgetWhenTitleMenuIconHovered = val;
//    }    
//    
//    virtual uiVizWidget* getPopoutWidgetForMenuTag(int menuTag) {
//        // Override in descendant...
//        return nullptr;
//    }
//
//    PopoutDirection getSuggestedPopoutDirectionFromWidgetTitleBar() {
//        if (isTitleTop()) {
//            return PopoutDirection::DOWN;
//        }
//        else if (isTitleBottom()) {
//            return PopoutDirection::UP;
//        }
//        else if (isTitleLeft()) {
//            return PopoutDirection::RIGHT;
//        }
//        else if (isTitleRight()) {
//            return PopoutDirection::LEFT;
//        }
//        return PopoutDirection::DOWN;
//    }
//
//    uiVizCoord::vizBounds getPopoutScaledBoundsForTitleIcon(int iconTag) {
//
//        uiVizIcon icon = getWidgetTitleIconByTag(iconTag);
//
//        uiVizCoord::vizBounds iconBounds(0, 0, 0, 0);
//
//
//        if (isTitleTop()) {
//            iconBounds = uiVizCoord::vizBounds(
//                icon.getScaledBounds().x + icon.getScaledBounds().width / 2, 
//                icon.getScaledBounds().y + icon.getScaledBounds().height + getScaledPadding() * 4, 
//                icon.getScaledBounds().width,
//                icon.getScaledBounds().height
//            );
//        }
//        else if (isTitleBottom()) {
//            iconBounds = uiVizCoord::vizBounds(
//                icon.getScaledBounds().x + icon.getScaledBounds().width / 2, 
//                icon.getScaledBounds().y - getScaledPadding() * 4, 
//                icon.getScaledBounds().width,
//                icon.getScaledBounds().height
//            );
//        }
//        else if (isTitleLeft()) {
//            iconBounds = uiVizCoord::vizBounds(
//                icon.getScaledBounds().x + icon.getScaledBounds().width + getScaledPadding() * 4, 
//                icon.getScaledBounds().y + icon.getScaledBounds().height / 2, 
//                icon.getScaledBounds().width,
//                icon.getScaledBounds().height
//            );
//        }
//        else if (isTitleRight()) {
//            iconBounds = uiVizCoord::vizBounds(
//                icon.getScaledBounds().x - getScaledPadding() * 4,
//                icon.getScaledBounds().y + icon.getScaledBounds().height / 2, 
//                icon.getScaledBounds().width,
//                icon.getScaledBounds().height
//            );
//        }
//        return iconBounds;
//    }    
//    
//
//    virtual void showContextMenu(int menuTag, int x, int y) {
//        
//        uiVizWidget* contextMenuWidget = getPopoutWidgetForMenuTag(menuTag);
//        
//        // Show it!
//        if (contextMenuWidget != nullptr) {
//            contextMenuWidget->setPopoutWidgetDirection(PopoutDirection::NONE);
//            contextMenuWidget->setTheme(getViz()->getThemeManager()->getContrastingSystemTheme(getTheme(), true));
//            
//            contextMenuWidget->setWidgetPosition(x, y, false);
//            contextMenuWidget->setShowingAsPopout(true);
//            contextMenuWidget->setIsVisible(true);
//            contextMenuWidget->setActiveWidget();
//            contextMenuWidget->setNeedsUpdate(true);
//            contextMenuWidget->setWidgetNeedsUpdate(true);
//            //onContentWidgetUnhovered have a pin icon for menu
//            // if pinned, don't hide when lost focus, otherwise do hide!
//            // add select key custom content to menu
//            // write a function to determine if context menu is full obscured, if so, hide it!
//            
//            // tweak getPopoutWidgetForHoveredTitleIcon to return correct widget (eg the switch statement above), then can use it
//        }
//        
//    }
//
//    void allocateFbo(bool initialize) {
//
//		if (!getUseFbo()) return;
//		
//		// Do we really need to allocate ?
//		if (!initialize && mFboAllocatedWidth == scale(getWidgetStateWidth()) && mFboAllocatedHeight == scale(getWidgetStateHeight())) return;
//
//        // $$$ EXPENSIVE allocate fbo $$$
//        mFboAllocatedWidth = scale(getWidgetStateWidth());
//        mFboAllocatedHeight = scale(getWidgetStateHeight());
//        
//        if (mFboAllocatedWidth == 0 ||  mFboAllocatedHeight == 0) return;
//    
//        #ifdef TARGET_OPENGLES
//            fbo.allocate(mFboAllocatedWidth, mFboAllocatedHeight, GL_RGBA);
//        #else
//            switch (getFboMode()) {
//                case FboMode::LOW:
//                    // Use only one fbo with GL_RGBA - the introduced alpha channel reduces the colour somewhat and
//                    // does not look pristine. In addition, use only 8 samples
//                    fbo.allocate(mFboAllocatedWidth, mFboAllocatedHeight);
//                    break;
//                case FboMode::MEDIUM:
//                    // Use only one fbo with GL_RGBA - the introduced alpha channel reduces the colour somewhat and
//                    // does not look pristine. Use 16 samples
//                    fbo.allocate(mFboAllocatedWidth, mFboAllocatedHeight, GL_RGBA, 16);
//                    break;
//                case FboMode::HIGH:
//                    // Use 2 x fbos, one dedicated to content and one dedicated to widget chrome. Colors look much better
//                    // because the alpha channel is not used as much in the content, thereform making them more accurate
//                    fbo.allocate(mFboAllocatedWidth, mFboAllocatedHeight, GL_RGBA, 16);   // GL_RGBA32F, 32);
//                    break;
//                case FboMode::ULTRA:
//                    // Use 2 x fbos, one dedicated to content and one dedicated to widget chrome. Colors look much better
//                    // because the alpha channel is not used as much in the content, thereform making them more accurate
//                    // in addition,
//                    // TODO: OVERSAMPLING
//                    fbo.allocate(mFboAllocatedWidth, mFboAllocatedHeight, GL_RGBA, 16);
//                    break;
//            }
//        #endif
//        
//        if (initialize){
//            fbo.begin();
//            ofClear(255, 255, 255, 0);
//            fbo.end();
//        }
//    }
//
//    AdditionalState getAdditionalState() {
//        return mAdditionalState;
//    }
//    
//    void setAdditionalState(AdditionalState additionalState) {
//        mAdditionalState = additionalState;
//    }
//    
//    bool getIsVisible() override {
//        
//        return uiVizWidgetBase::getIsVisible(); 
//    }
//    
//    virtual void setIsVisible(bool value) override {
//        uiVizWidgetBase::setIsVisible(value);
//        if (!value) {
//           if (getIsActiveWidget()) clearActiveWidgetId();
//		}
//		else {
//			setWasJustInitialized(true);
//		}
//    }
//
//    bool getIsMinimized() {
//        return mIsMinimized;
//    }
//    
//    void setIsMinimized(bool value) {
//        mIsMinimized = value;
//        scaleUITitleSize();
//        setWidgetNeedsUpdate(true);
//        setNeedsUpdate(true);
//    }
//
//    bool getDrawWidgetChrome() {
//        return mDrawWidgetChrome;
//    }
//    
//    void setDrawWidgetChrome(bool value) {
//        mDrawWidgetChrome = value;
//    }
//    
//    bool getDrawWidgetTitle() {
//        return mDrawWidgetTitle;
//    }
//    
//    void setDrawWidgetTitle(bool value) {
//        mDrawWidgetTitle = value;
//    }
//    
//    float getCurrentWidgetAlpha() {
//        return mUICurrentWidgetAlpha;
//    }
//    
//    // Read from config in due course
//    ofColor getDividerColor() {
//        return ofColor::lightGray;
//    }
//
//    bool getDrawnByWidgetManager() {
//        return mDrawnByWidgetManager;
//    }
//    
//    void setDrawnByWidgetManager(bool value) {
//        mDrawnByWidgetManager = value;
//    }
//
//    bool isWidgetUICompletelyTransparent() {
//        return mUICurrentWidgetAlpha <= 0;
//    }
//
//    bool getIsTitleAutohide() {
//        return mIsTitleAutohide;
//    }
//    
//    void setIsTitleAutohide(bool val) {
//         mIsTitleAutohide = val;
//    }
//    
//    bool getShowTitleIcons() {
//        return mShowTitleIcons;
//    }
//    
//    void setShowTitleIcons(bool val) {
//        mShowTitleIcons = val;
//    }
//
//    int getFboNeedsUpdate() {
//        return mFboNeedsUpdate;
//    }
//    
//    void setFboNeedsUpdate(bool val) {
//        mFboNeedsUpdate = val;
//    }
//    
//    int getWidgetStateX() {
//        if (getIsMinimized()) {
//            return getX() + mMinimizedOffsetX;
//        } else {
//            return getX() + mNonMinimizedOffsetX;
//        }
//    }
//
//    int getWidgetStateY()  {
//        if (getIsMinimized()) {
//            return getY() + mMinimizedOffsetY;
//        } else {
//            return getY() + mNonMinimizedOffsetY;
//        }
//    }
//
//    virtual int getWidgetStateWidth() override {
//        if (getIsMinimized()) {
//            return mMinimizedWidth + getNonScaledPadding() * 2.0f;
//        } else {
//            return getWidth();
//        }
//    }
//    
//    virtual int getWidgetStateHeight() override {
//        if (getIsMinimized()) {
//            return mMinimizedHeight + getNonScaledPadding() * 2.0f;
//        } else {
//            return getHeight();
//        }
//    }
//
//    virtual int getUsableX() override {
//        return getUsableX(true);
//    }
//    
//    virtual int getUsableY() override {
//        return getUsableY(true);
//    }
//    
//    virtual int getUsableX(bool inclScrollOffset) override {
//        int scrollOffsetX = inclScrollOffset ? getScrollOffsetX() : 0;
//        if (getIsMinimized() || !getDrawWidgetChrome()) {
//            return getWidgetStateX() + getNonScaledPadding() + scrollOffsetX; // Todo make configurable
//        } else {
//            if (mTitleStyle == TitleStyle::LEFT_WITH_WIDGET_RESIZE) {
//                return getWidgetStateX() + deScale(mUICurrentTitleBarSize) + getNonScaledPadding() + scrollOffsetX;
//            } else if (mTitleStyle == TitleStyle::LEFT_OVERLAY_FULL || mTitleStyle == TitleStyle::LEFT_OVERLAY || mTitleStyle == TitleStyle::LEFT_STATIC) {
//                return getWidgetStateX() + getUnhoveredTitleBarSize(false) + getNonScaledPadding() + scrollOffsetX;
//            } else if (mTitleStyle == TitleStyle::RIGHT_WITH_WIDGET_RESIZE) {
//                return getWidgetStateX() + getNonScaledPadding() + scrollOffsetX;
//            } else { // (mTitleStyle == RIGHT_OVERLAY_FULL || mTitleStyle == RIGHT_OVERLAY || mTitleStyle == RIGHT_STATIC ||  mTitleStyle == NONE) {
//                return getWidgetStateX() + getNonScaledPadding() + scrollOffsetX;
//            }
//        }
//    }
//    
//    virtual int getUsableY(bool inclScrollOffset) override {
//        int scrollOffsetY = inclScrollOffset ? getScrollOffsetY() : 0;
//        if (getIsMinimized() || !getDrawWidgetChrome()) {
//            return getWidgetStateY() + getNonScaledPadding() + scrollOffsetY; // Todo make configurable
//        } else {
//            if (mTitleStyle == TitleStyle::TOP_WITH_WIDGET_RESIZE) {
//                return getWidgetStateY() + deScale(mUICurrentTitleBarSize) + getNonScaledPadding() + scrollOffsetY;
//            } else if (mTitleStyle == TitleStyle::TOP_OVERLAY_FULL || mTitleStyle == TitleStyle::TOP_OVERLAY || mTitleStyle == TitleStyle::TOP_STATIC) {
//                return getWidgetStateY() + getUnhoveredTitleBarSize(false) + getNonScaledPadding() + scrollOffsetY;
//            } else if (mTitleStyle == TitleStyle::BOTTOM_WITH_WIDGET_RESIZE) {
//                return getWidgetStateY() + getNonScaledPadding() + scrollOffsetY;
//            } else { // (mTitleStyle == BOTTOM_OVERLAY_FULL || mTitleStyle == BOTTOM_OVERLAY || mTitleStyle == BOTTOM_STATIC ||  mTitleStyle == NONE) {
//                return getWidgetStateY() + getNonScaledPadding() + scrollOffsetY;
//            }
//        }
//    }
//    
//    int getCoreUsableWidth() {
//        if (getIsMinimized()) {
//            return mMinimizedWidth;
//        } else {
//            if (mTitleStyle == TitleStyle::LEFT_WITH_WIDGET_RESIZE || mTitleStyle == TitleStyle::RIGHT_WITH_WIDGET_RESIZE) {
//                return getWidth() - deScale(mUICurrentTitleBarSize) - getNonScaledPadding()*2.0f;
//            } else {
//                return getWidth() - ((isTitleTop() || isTitleBottom() || isTitleNone() || !getDrawWidgetTitle()) ? 0 : getUnhoveredTitleBarSize(false)) - getNonScaledPadding()*2.0f;
//            }
//        }
//    }
//    
//    int getCoreUsableHeight() {
//        if (getIsMinimized()) {
//            return mMinimizedHeight;
//        } else {
//            if (mTitleStyle == TitleStyle::TOP_WITH_WIDGET_RESIZE || mTitleStyle == TitleStyle::BOTTOM_WITH_WIDGET_RESIZE) {
//                return getHeight() - deScale(mUICurrentTitleBarSize) - getNonScaledPadding()*2.0f;
//            } else {
//                return getHeight() - ((isTitleLeft() || isTitleRight() || isTitleNone() || !getDrawWidgetTitle()) ? 0 : getUnhoveredTitleBarSize(false)) - getNonScaledPadding()*2.0f;
//            }
//        }
//    }
//    
//    virtual int getUsableWidth() override {
//        return getCoreUsableWidth();
//    }
//    
//    virtual int getUsableHeight() override {
//        return getCoreUsableHeight();
//    }
//    
//    int getUsableWidthIncludingTitle() {
//        return getCoreUsableWidth() + getUnhoveredTitleBarSize(false);
//    }
//    
//    int getUsableHeightIncludingTitle() {
//        return getCoreUsableHeight() + getUnhoveredTitleBarSize(false);
//    }
//
//    void setOffsetsX(float minimizedOffsetX, float nonMinimizedOffsetX) {
//        mMinimizedOffsetX = minimizedOffsetX;
//        mNonMinimizedOffsetX = nonMinimizedOffsetX;
//    }
//    
//    void setOffsetsY(float minimizedOffsetY, float nonMinimizedOffsetY) {
//        mMinimizedOffsetY = minimizedOffsetY;
//        mNonMinimizedOffsetY = nonMinimizedOffsetY;
//    }
//    
//    void setPosition(float x, float y) {
//        float offsetX = getIsMinimized() ? mMinimizedOffsetX : mNonMinimizedOffsetX;
//        float offsetY = getIsMinimized() ? mMinimizedOffsetY : mNonMinimizedOffsetY;
//        
//        int clampX = x;
//        clampX = std::max((float)clampX - offsetX, (float)getScreenPadding());
//        clampX = std::min((float)clampX, (float)(deScale(ofGetWindowWidth()) - getScreenPadding() - getWidgetStateWidth()));
//        setX(clampX);
//        
//        int clampY = y;
//        clampY = std::max((float)clampY - offsetY, (float)getScreenPadding());
//        clampY = std::min((float)clampY, (float)(deScale(ofGetWindowHeight()) - getScreenPadding() - getWidgetStateHeight()));
//        setY(clampY);
//    }
//    
//    void applyDockingLogic() {
//        
//        if (getX_Expr() == "" && uiVizWidgetBase::getX() >= (deScale(ofGetWindowWidth()) - getScreenPadding() - getWidgetStateWidth())) {
//            setX_Expr("${WINDOW.WIDTH} - ${SELF.WIDTH}");
//            setX_ExprWasSetProgramatically(true);
//        }
//        if (getY_Expr() == "" && uiVizWidgetBase::getY() >= (deScale(ofGetWindowHeight()) - getScreenPadding() - getWidgetStateHeight())) {
//            setY_Expr("${WINDOW.HEIGHT} - ${SELF.HEIGHT}");
//            setY_ExprWasSetProgramatically(true);
//        }
//
//        if (getWidth_Expr() == "" && getWidgetStateWidth() >= (deScale(ofGetWindowWidth()) - getScreenPadding()*2)) {
//            setWidth_Expr("${WINDOW.WIDTH}");
//            setWidth_ExprWasSetProgramatically(true);
//        }
//        if (getHeight_Expr() == "" && getWidgetStateHeight() >= (deScale(ofGetWindowHeight()) - getScreenPadding())) {
//            setHeight_Expr("${WINDOW.HEIGHT}");
//            setHeight_ExprWasSetProgramatically(true);
//        }
//        
//    }
//    
//    virtual void setWidgetPosition(float x, float y, bool enableDockingLogic) override {
//        if (getX() != x || getY() != y) {
//            setPosition(x, y);
//            if (enableDockingLogic) applyDockingLogic();
//            setWidgetNeedsUpdate(true);
//        }
//    }
//    
//    virtual uiVizElm::vizRect setSize(int width, int height) override {
//        return uiVizWidgetBase::setSize(width, height);
//    }
//    
//    void setPopoutWidgetDirection(PopoutDirection val)  {
//        mPopoutDirection = val;
//    }    
//
//    void setWidgetSize(int width, int height, bool enableDockingLogic, bool widthSetByExpression, bool heightSetByExpression) {
//
//        bool widthChanged = getWidth() != width;
//        bool heightChanged = getHeight() != height;
//
//        if (widthChanged || heightChanged || 
//            (getLockAspectRatio() && height != width * getAspectRatio())
//        ) {
//
//            mWidthChangedByExpression = widthSetByExpression && widthChanged;
//            mHeightChangedByExpression = heightSetByExpression && heightChanged;
//
//            if (mPopoutDirection != PopoutDirection::NONE && getShowingAsPopout()) {
//                int min_ArrowX = deScale(vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.getTriangle().x3 + getScaledPadding()); // For resizing from the left
//                int min_ArrowY = deScale(vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.getTriangle().y3 + getScaledPadding());
//                int max_ArrowX = deScale(vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.getTriangle().x1 + getScaledPadding());
//                int max_ArrowY = deScale(vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.getTriangle().y1 + getScaledPadding());
//
//                int clampedWidth = min_ArrowX - getX() + getNonScaledPadding();
//                int clampedHeight = min_ArrowY - getY() + getNonScaledPadding();
//
//                switch(mPopoutDirection) {
//                    case PopoutDirection::DOWN:
//                        clampedWidth = max((int)width, (int)clampedWidth);
//                        clampedHeight = height;
//                        break;                    
//                    case PopoutDirection::UP:
//                        clampedWidth = max((int)width, (int)clampedWidth);
//                        // WIP : setY(getY() + getHeight() - height - 15);
//                         // Cant resize for now when popped from bottom (TODO: FIX)
//                        clampedHeight = getHeight();
//                        break;
//                    case PopoutDirection::LEFT:
//                         // Cant resize for now when popped from left (TODO: FIX)                    
//                        clampedWidth = getWidth();
//                        clampedHeight = max((int)height, (int)clampedHeight);  
//                        break;                        
//                    case PopoutDirection::RIGHT:
//                        clampedWidth = width;
//                        clampedHeight = max((int)height, (int)clampedHeight);                 
//                        break;
//                }
//                uiVizWidgetBase::setWidgetSize(clampedWidth, clampedHeight, false);  
//            } else {
//                uiVizWidgetBase::setWidgetSize(width, height, enableDockingLogic);
//                if (enableDockingLogic) applyDockingLogic();
//            }
//            setWidgetNeedsUpdate(true);
//            
//            for(uiVizWidgetElm &elm:mWidgetElements){
//                //ofResizeEventArgs e(width, height);
//                //elm.onCoreWidgetResized(e);
//                ofResizeEventArgs args(width, height);
//                ofNotifyEvent(elm.widgetResized, args);                
//            }
//        }
//    }
//
//    void setWidgetSize(int width, int height, bool enableDockingLogic) override {
//        mWidthChangedByExpression = false;
//        mHeightChangedByExpression = false;
//        setWidgetSize(width, height, enableDockingLogic, false, false);
//    }
//
//    bool getWidthChangedByExpression() {
//        return mWidthChangedByExpression;
//    }
//
//    bool getHeightChangedByExpression() {
//        return mHeightChangedByExpression;
//    }    
//
//    void setWidgetBounds(float x, float y, float width, float height) {
//         if (getX() != x || getY() != y || getWidth() != width || getHeight() != height) {
//            setPosition(x, y);
//            setSize(width, height);
//            setWidgetNeedsUpdate(true);
//         }
//    }
//
//    void setMinimizedSize(int width, int height) {
//        mMinimizedWidth = width;
//        mMinimizedHeight = height;
//    }
//    
//    void setWidgetMinimizedSize(float width, float height) {
//        setMinimizedSize(width, height);
//        setWidgetNeedsUpdate(true);
//    }
//
//    virtual void setTitle(string title) override {
//        uiVizWidgetBase::setTitle(title);
//        mDrawableWidgetTitle = title;
//    }
//
//	void setTitleStyle(TitleStyle titleStyle) { 
//		mTitleStyle = titleStyle;
//	}
//    
//    TitleStyle getTitleStyle() {
//        return mTitleStyle;
//    }
//
//    int getStaticTitleBarSize(bool scaled) {
//        return scaled ? scale(mStaticTitleBarSize) : mStaticTitleBarSize;
//    }
//
//    void setStaticTopTitleBarSize(int val) {
//        setTitleStyle(TitleStyle::TOP_STATIC);
//        mStaticTitleBarSize = val;
//        scaleUITitleSize();
//    }
//
//    void setStaticBottomTitleBarSize(int val) {
//        setTitleStyle(TitleStyle::BOTTOM_STATIC);
//        mStaticTitleBarSize = val;
//        scaleUITitleSize();
//    }
//
//    void setStaticLeftTitleBarSize(int val) {
//        setTitleStyle(TitleStyle::LEFT_STATIC);
//        mStaticTitleBarSize = val;
//        scaleUITitleSize();
//    }
//
//    void setStaticRightTitleBarSize(int val) {
//        setTitleStyle(TitleStyle::RIGHT_STATIC);
//        mStaticTitleBarSize = val;
//        scaleUITitleSize();
//    }            
//
//    int getUnhoveredTitleBarSize(bool scaled) {
//        if (mTitleStyle == TitleStyle::NONE) {
//            return (scaled ? getScaledPadding() : getNonScaledPadding());
//        } else {
//            if (getIsTitleAutohide() && !isWidgetHovered() && !getIsResizing()) {
//                return 0;
//            } else {
//                //return (scaled ? getScaledPadding() : getNonScaledPadding()) * 4;
//                return getStaticTitleBarSize(scaled);
//
//            }
//        }
//    }
//
//    int getHoveredTitleBarSize(bool scaled) {
//        if (getIsMinimized()) {
//            if (isTitleLeft() || isTitleRight()) {
//                return scaled ? scale(getWidgetStateWidth()) : getWidgetStateWidth();
//            } else {
//                return scaled ? scale(getWidgetStateHeight()) : getWidgetStateHeight();
//            }
//        } else {
//            if (mTitleStyle == TitleStyle::TOP_OVERLAY_FULL || mTitleStyle == TitleStyle::BOTTOM_OVERLAY_FULL) {
//                return widgetFrame.getRectangle().height;
//            } else if (mTitleStyle == TitleStyle::LEFT_OVERLAY_FULL || mTitleStyle == TitleStyle::RIGHT_OVERLAY_FULL) {
//                return widgetFrame.getRectangle().width;
//            } else {
//                return (scaled ? getScaledPadding() : getNonScaledPadding()) * 8; // Or some user defined value!
//            }
//        }
//    }
//
//    void setZindex(int zIndex) override  {
//        uiVizWidgetBase::setZindex(zIndex);
//        if (getWidgetElements().size() > 0) {
//            for(uiVizWidgetElm &widgetElm:getWidgetElements()){
//                widgetElm.setZindex(zIndex);
//            }
//        }
//    }
//    
//	void setFboMode(FboMode fboMode) {
//		mFboMode = fboMode;
//	}
//
//	FboMode getFboMode() {
//		return mFboMode;
//	}
//
//	bool getIsHighOrUltraFboMode() {
//		return mFboMode == FboMode::HIGH || mFboMode == FboMode::ULTRA;
//	}
//
//    // vector of widgets
//    
//    void connectWidget(uiVizWidget widget) {
//        /* Use this to connect another widget to this widget instance eg
//        
//        ~~~~~~      ~~~~~~~~~~
//        | ME | <--- | WIDGET |
//        ~~~~~~      ~~~~~~~~~~
//         
//         */
//    }
//    
//    void connectToWidget(uiVizWidget widget) {
//        /* Use this to connect this instance to another widget ie
//        
//        ~~~~~~~~~~      ~~~~~~
//        | WIDGET | <--- | ME |
//        ~~~~~~~~~~      ~~~~~~
//
//        
//         */
//        
//    }
//
//	virtual void saveWidgetXMLToFile(string fileName) { 
//        ofxXmlSettings xml = saveState();
//        xml.saveFile(fileName);
//    }
//
//	virtual ofPixels saveWidgetContentsToPixels(uiVizWidgetContext::DrawContext drawContext) { 
//        TitleStyle origTitleStyle = getTitleStyle();
//
//        // populate the fbo
//        setTitleStyle(TitleStyle::NONE);        
//        this->context.drawContext = drawContext;
//        if (!getIsMinimized()) {
//            update(this->context); 
//        } else {
//            updateMinimized();
//        }
//        coreDrawWidgetContent(true);
//        this->context.drawContext = drawContext;
//        setTitleStyle(origTitleStyle);
//        
//		ofPixels pixels;
//        pixels.allocate(scale(getWidth()), scale(getHeight()),  OF_IMAGE_COLOR_ALPHA);
//		fbo.readToPixels(pixels);
//        return pixels;
//	}
//
//	virtual void saveWidgetContentsToImageFile(string fileName, uiVizWidgetContext::DrawContext drawContext) { 
//		ofPixels pixels = saveWidgetContentsToPixels(drawContext);
//		ofSaveImage(pixels, fileName, OF_IMAGE_QUALITY_BEST);     
//	}
//
//	virtual void saveWidgetContentsToBuffer(ofBuffer &buffer, uiVizWidgetContext::DrawContext drawContext) { 
//		ofPixels pixels = saveWidgetContentsToPixels(drawContext);
//        ofImage image;
//        image.setFromPixels(pixels);
//        image.save(buffer, OF_IMAGE_FORMAT_PNG, OF_IMAGE_QUALITY_BEST);
//	}
//
//	virtual void saveWidgetContentsToHTMLFile(string fileName) { 
//    }    
//
//	virtual ofFbo saveWidgetContentsToFbo() override { 
//        TitleStyle origTitleStyle = getTitleStyle();
//        setTitleStyle(TitleStyle::NONE);     
//
//        bool origFboVal = getUseFbo();
//        setUseFbo(false);
//
//        this->context.drawContext = uiVizWidgetContext::IMAGE;
//        if(widgetNeedsUpdate()) {
//            updateWidget();
//        }
//        if (!getIsMinimized()) {
//            update(this->context); 
//        } else {
//            updateMinimized();
//        }
//
//        ofFbo fboCopy;   
//        #ifdef TARGET_OPENGLES
//            fboCopy.allocate(scale(getWidth()), scale(getHeight()), GL_RGBA);
//        #else
//            fboCopy.allocate(scale(getWidth()), scale(getHeight()),  GL_RGBA, 16); // GL_RGBA32F, 32);
//        #endif               
//        fboCopy.begin();
//        ofClear(0, 0, 0, 0);
//        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//        ofPushMatrix();
//        ofTranslate(-1*scale(getWidgetStateX()), -1*scale(getWidgetStateY()));
//
//
//        coreDrawWidgetContent(true);
//        this->context.drawContext = uiVizWidgetContext::SCREEN;
//        fboCopy.end();
//
//        setTitleStyle(origTitleStyle);
//        setUseFbo(origFboVal);
//
//
//        return fboCopy;
//	}    
//
//	void onCoreWidgetScaleChanged(float & scale) override {
//		scaleUITitleSize();
//		setWidgetNeedsUpdate(true);
//        setNeedsUpdate(true);
//        
//        mFboAllocatedWidth = 0;
//        mFboAllocatedHeight = 0;
//        
//        allocateFbo(true);
//        onWidgetScaleChanged(scale);
//        initWidgetScale(scale);        
//        //initWidget(); // this causes much gammy-ness with widgdet states when resizing!
//
//        setExpressionRecalculationRequired(true);
//        
//        for(uiVizWidgetElm &elm:mWidgetElements) {
//            elm.initWidgetScale(scale);            
//            //elm.initWidget(); // this causes much gammy-ness with widgdet states when resizing!
//        }
//        
//        updateWidgetPopoutArrow();
//        
//	}
//    
//
//
//    void showChildWithLayoutExpressions(string xExpr, string yExpr, string widthExpr, string heightExpr, bool popout) {
//        setIsDraggable(false);
//        setShowingAsPopout(popout);
//
//        setX_Expr(xExpr);
//        setY_Expr(yExpr);
//        setWidth_Expr(widthExpr);
//        setHeight_Expr(heightExpr);
//
//        setIsAutoResizeToContentsWidth(false);
//        setIsAutoResizeToContentsHeight(false);
//
//        if (parentWidget()) {
//            setExpressionRecalculationRequired(true);
//            parentWidget()->setExpressionRecalculationRequired(true);
//        }
//
//        setIsVisible(true);
//    }       
//    
//    bool isPopoutFromTitle() {
//        switch(mPopoutDirection) {
//            case PopoutDirection::DOWN: return isTitleTop();
//            case PopoutDirection::UP: return isTitleBottom();
//            case PopoutDirection::LEFT: return isTitleRight();
//            case PopoutDirection::RIGHT: return isTitleLeft();
//        }
//        return false;
//    }
//    
//    ofColor getWidgetStateColor(float alpha) {
//        
//        switch (mAdditionalState) {
//            case AdditionalState::SELECTED :
//                return getTheme().WidgetColor_withAlpha(getTheme().HoveredWidgetAlpha);
//                
//            default : {
//                return getTheme().WidgetColor_withAlpha(alpha);
//            }
//                
//        }
//    }
//    
//    ofColor getTitleStateColor() {
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleColor_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleAlpha : getTheme().UnhoveredTitleAlpha);
//        }
//    }
//
//    ofColor getTitleStateGradientColor1() {
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleGradientColor1_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleAlpha : getTheme().UnhoveredTitleAlpha);
//        }
//    }
//
//    ofColor getTitleStateGradientColor2() {
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleGradientColor2_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleAlpha : getTheme().UnhoveredTitleAlpha);
//        }
//    }  
//
//    ofColor getTitleStateGradientColor3() {
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleGradientColor3_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleAlpha : getTheme().UnhoveredTitleAlpha);
//        }
//    }  
//
//    ofColor getTitleStateGradientColor4() {
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleGradientColor4_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleAlpha : getTheme().UnhoveredTitleAlpha);
//        }
//    }                  
//    
//    ofColor getTitleFontStateColor() {
//        
//        switch (mAdditionalState) {
//            default :
//                return getTheme().TitleFontColor_withAlpha(isWidgetHovered() && getIsActiveWidget() ? getTheme().HoveredTitleFontAlpha : getTheme().UnhoveredTitleFontAlpha);
//        }
//    }
//
//
//    bool isTitleOverlay() {
//        return (mTitleStyle == TitleStyle::TOP_OVERLAY || mTitleStyle == TitleStyle::TOP_OVERLAY_FULL || mTitleStyle == TitleStyle::BOTTOM_OVERLAY || mTitleStyle == TitleStyle::BOTTOM_OVERLAY_FULL ||
//                mTitleStyle == TitleStyle::LEFT_OVERLAY || mTitleStyle == TitleStyle::LEFT_OVERLAY_FULL || mTitleStyle == TitleStyle::RIGHT_OVERLAY || mTitleStyle == TitleStyle::RIGHT_OVERLAY_FULL);
//    }
//    
//    bool isTitleResize() {
//        return (mTitleStyle == TitleStyle::TOP_WITH_WIDGET_RESIZE || mTitleStyle == TitleStyle::BOTTOM_WITH_WIDGET_RESIZE ||
//                mTitleStyle == TitleStyle::LEFT_WITH_WIDGET_RESIZE || mTitleStyle == TitleStyle::RIGHT_WITH_WIDGET_RESIZE);
//    }
//    
//    bool isTitleTop() {
//        return (mTitleStyle == TitleStyle::TOP_STATIC || mTitleStyle == TitleStyle::TOP_OVERLAY ||
//                mTitleStyle == TitleStyle::TOP_OVERLAY_FULL || mTitleStyle == TitleStyle::TOP_WITH_WIDGET_RESIZE);
//    }
//    
//    bool isTitleBottom() {
//        return (mTitleStyle == TitleStyle::BOTTOM_STATIC || mTitleStyle == TitleStyle::BOTTOM_OVERLAY ||
//                mTitleStyle == TitleStyle::BOTTOM_OVERLAY_FULL || mTitleStyle == TitleStyle::BOTTOM_WITH_WIDGET_RESIZE);
//    }
//    
//    bool isTitleLeft() {
//        return (mTitleStyle == TitleStyle::LEFT_STATIC || mTitleStyle == TitleStyle::LEFT_OVERLAY ||
//                mTitleStyle == TitleStyle::LEFT_OVERLAY_FULL || mTitleStyle == TitleStyle::LEFT_WITH_WIDGET_RESIZE);
//    }
//    
//    bool isTitleRight() {
//        return (mTitleStyle == TitleStyle::RIGHT_STATIC || mTitleStyle == TitleStyle::RIGHT_OVERLAY ||
//                mTitleStyle == TitleStyle::RIGHT_OVERLAY_FULL || mTitleStyle == TitleStyle::RIGHT_WITH_WIDGET_RESIZE);
//    }
//    
//    bool isTitleStatic() {
//        return (mTitleStyle == TitleStyle::TOP_STATIC || mTitleStyle == TitleStyle::BOTTOM_STATIC ||
//                mTitleStyle == TitleStyle::LEFT_STATIC || mTitleStyle == TitleStyle::RIGHT_STATIC);
//    }
//    
//    bool isTitleNone() {
//        return (mTitleStyle == TitleStyle::NONE);
//    }
//
//    virtual bool hasActiveChildWidgetOrElement(bool includeClipboard) {
//        if (getIsActiveWidget()) return true;
//        if (includeClipboard && shouldShowClipboardForThisWidget()) return true;
//
//        for(uiVizWidgetElm &elm:getWidgetElements()) {
//            if (elm.getIsActiveWidget()) return true;
//            if (includeClipboard && elm.shouldShowClipboardForThisWidget()) return true;
//        }
//
//        for(uiVizWidget &childWidget:getChildWidgets()) {
//            if (childWidget.getIsActiveWidget()) return true;
//            if (includeClipboard && childWidget.shouldShowClipboardForThisWidget()) return true;
//            for(uiVizWidgetElm &elm:childWidget.getWidgetElements()) {
//                if (elm.getIsActiveWidget()) return true;
//                if (includeClipboard && elm.shouldShowClipboardForThisWidget()) return true;
//            }                        
//        }
//        return false;    
//    }     
//
//
//    virtual void onCoreWidgetWindowResized() override {
//        
//        setExpressionRecalculationRequired(true);
//        setMaxWidth(ofGetWindowWidth()-getScreenPadding()*2);
//        setMaxHeight(ofGetWindowHeight()-getScreenPadding()*2);
//        
//        setWidgetPosition(getWidgetStateX(), getWidgetStateY(), true);
//        
//        // ^^ If window has shrunk, the widget will be brought back into view - this isn't necessarily always the desired behaviour, can make a behaviour enum :
//        // Dock left, stay in viewX, etc
//        setWidgetNeedsUpdate(true);
//        if(mPopoutDirection != PopoutDirection::NONE && getShowingAsPopout()) setIsVisible(false);
//        
//        mFboAllocatedWidth = 0;
//        mFboAllocatedHeight = 0;
//        
//        allocateFbo(true);
//    }
//
//    virtual void onCoreWidgetMouseScrolled(ofMouseEventArgs &e) override {
//        if (getIsActiveWidget()) {
//            switch(getScrollAction()) {
//                case ScrollAction::ZOOM:
//                    if (!getIsResizable() || isTitleHovered()) return;
//                    setWidgetSize(getWidth() + e.scrollY*getScrollScaleX(), getHeight() + e.scrollY*getScrollScaleY(), true);
//                    mMustNotifyAfterUserResizingEndedTimeout = ofGetSystemTimeMillis() + 500;
//                    onWidgetMouseScrolled(e);
//                    break;
//                    
//                case ScrollAction::SCROLL:
//                    uiVizWidgetBase::onCoreWidgetMouseScrolled(e);
//                    break;
//            }
//        }
//    }
//
//    virtual void onCoreWidgetWindowResized(ofResizeEventArgs &e) override {
//		onCoreWidgetWindowResized();
//    }
//    
//    virtual void onCoreWidgetKeyPressed(ofKeyEventArgs &e) override {
//        if (getIsActiveWidget()) {
//            uiVizWidgetBase::onCoreWidgetKeyPressed(e);
//            for(uiVizWidgetElm &elm:mWidgetElements) {
//                if (elm.getIsFocused(true)) {
//                    //elm.onWidgetKeyPressed(e); // this is handled by the elm's onCoreWidgetKeyPressed event
//                    
//                    if (e.key == OF_KEY_TAB) {
//                        focusNextWidgetElement();
//                    }
//                }
//            }
//        }
//    }
//    
//    virtual void onCoreWidgetMouseReleased(ofMouseEventArgs &e) override {
//
//        if (getIsActiveWidget() && !getIsDragging() && !getIsResizing()) {
//            onCoreWidgetWidgetClicked(e);
//        }
//		uiVizWidgetBase::onCoreWidgetMouseReleased(e);        
//        
//        setIsDragging(false);
//        setIsResizing(false);
//        if (getViz()->getIsAnyWidgetDraggingOrResizing()) {
//            getViz()->revertBoostUserExperience();
//        }
//        getViz()->setIsAnyWidgetDraggingOrResizing(false);
//    }
//
//	virtual void onCoreWidgetMouseDragged(ofMouseEventArgs &e) override {
//		if (getIsActiveWidget()) {
//
//            if (getExternalDrop().getIsDragging()) {
//                getExternalDrop().handleExternalDragAndDropMotionNotify();
//                if (!ofGetMousePressed()) getExternalDrop().handleExternalDragAndDropButtonReleaseEvent();
//            }
//
//			if(getIsEnabled()) onWidgetMouseDragged(e);
//			if (getIsActiveWidget() && !getIsScrollingXMouseDown() && !getIsScrollingYMouseDown() && !getIsDragging() && !getIsResizing()) {
//				onCoreWidgetMouseContentDragged(e);
//			}
//		}
//	}
//    
//    virtual void onWidgetMouseScrolled(ofMouseEventArgs &e) override {
//        // Implement any behaviour in derrived class which should handle mouse released...
//    }      
//
//
//
//    bool getIsWidgetPinned() {
//        return mIsWidgetPinned;
//    }
//
//    void setIsWidgetPinned(bool val) {
//        mIsWidgetPinned = val;
//    }
//
//    bool getShowWidgetPin() {
//        return mShowWidgetPin;
//    }
//
//    void setShowWidgetPin(bool val) {
//        mShowWidgetPin = val;
//    }
//     
//
//private:
//    uiVizWidgetContext context;
//    bool mIsWidgetPinned = false;
//    bool mShowWidgetPin = false;      
//    bool mWidthChangedByExpression = false;
//    bool mHeightChangedByExpression = false;
//
//    vector<uiVizIcon> mPositionedTitleIcons;
//    bool mShowPopoutWidgetWhenTitleMenuIconHovered = false;
//
//
//    void addWidgetElement(uiVizWidgetElm &e) {
//        removeWidgetElement(&e);
//        mWidgetElements.push_back(e);
//    }
//
//    uiVizWidgetElm* addWidgetElement(string ELM_CLASS, string persistentId, string widgetXML) {
//        mapElements();
//         // Does the class exist in the map?
//        if (elmClassMap.count(ELM_CLASS) > 0) {
//            uiVizWidgetElm* elm = elmClassMap[ELM_CLASS](persistentId, widgetXML, this);
//            addWidgetElement(*elm);
//            return elm;
//        } else {
//            ofLogWarning("uiVizWidget") << "[Element:" << persistentId << "] of class \"" << ELM_CLASS << "\" failed to load. [" + widgetXML + "]";
//        }
//
//        return nullptr;
//    }
//
//    virtual void onCoreWidgetEventReceived(uiVizWidgetEventArgs &args) override {
//        
//        /*****************************************************************
//         Internal messages sent by children to be handled by this widget
//         *****************************************************************/
//       
//        if (args.eventName == WIDGET_EVENT::FOCUS_NEXT_ELEMENT) {
//            focusNextWidgetElement();
//            return;
//        }
//        
//        if (args.eventName == WIDGET_EVENT::FOCUS_ELEMENT) {
//            focusWidgetElement(args.widgetId);
//            return;
//        }
//        
//        if (args.eventName == WIDGET_EVENT::CLIPBOARD_PASTE) {
//            focusWidgetElement(args.widgetId);
//            return;
//        }
//
//    }
//    
//    void init() {
//        mMinimizedWidth = getWidth() * 0.25f;
//        mMinimizedHeight = getHeight() * 0.25f;
//        
//        getViz()->addWidgetId(getWidgetId());
//        scaleUITitleSize();
//        setWasJustInitialized(true);
//        mUICurrentWidgetAlpha = 0.0f; // Let it fade in on inital draw
//        
//
//        setUseFbo(getViz()->getUseFbo());
//
//        if (getViz()->getUseFbo()) {
//          //  allocateFbo(true); // disabled since it may not even be visible yet!
//        }
//    }
//    
//    void updateWidgetUI() {
//        widgetFrame.setRectangle(scale(getWidgetStateX()), scale(getWidgetStateY()), scale(getWidgetStateWidth()), scale(getWidgetStateHeight()));
//        updateWidgetUITitle();
//        
//        widgetResizeBottom.setRectangle(scale(getWidgetStateX()), scale(getWidgetStateY() + getWidgetStateHeight() - getNonScaledPadding()), scale(getWidgetStateWidth()),  getScaledPadding());
//        widgetResizeLeft.setRectangle(scale(getWidgetStateX()), scale(getWidgetStateY()), getScaledPadding(),  scale(getWidgetStateHeight()));
//        widgetResizeRight.setRectangle(scale(getWidgetStateX() + getWidgetStateWidth() - getNonScaledPadding()), scale(getWidgetStateY()), getScaledPadding(),  scale(getWidgetStateHeight()));
//        titleFont = (getViz()->getScale() < 1) ? getViz()->getSmallFont() : getViz()->getMediumFont();
//        ofRectangle rectTitleFontAreaOf = titleFont->rect(getTitle() + "Xy"); // (concat an upper case and a descender letter)
//        rectTitleFontArea.setRectangle(rectTitleFontAreaOf.getX(), rectTitleFontAreaOf.getY(), rectTitleFontAreaOf.getWidth(), rectTitleFontAreaOf.getHeight());
//		updateWidgetUIPathElm();
//        //updateWidgetPopoutArrow();
//        
//    }
//    
//    void scaleUITitleSize() {
//        // The reason we can't have this called inside updateWidgetUI is because
//        // it would cause any animating title resize to "jump" to a position
//        if (getIsMinimized()) {
//            mUICurrentTitleBarSize = getHoveredTitleBarSize(true);
//        } else {
//            mUICurrentTitleBarSize = getUnhoveredTitleBarSize(true);
//        }
//    }
//    
//    void updateWidgetUITitle() {
//        uiVizCoord::vizBounds titleBounds = getWidgetUITitleBounds(false);
//        widgetTitle.setRectangle(titleBounds.x, titleBounds.y, titleBounds.width,  titleBounds.height);
//		updateWidgetTitlePathElm();
//    }
//    
//    uiVizCoord::vizBounds getWidgetUITitleBounds(bool isAllocating) {
//        if (isTitleTop()) {
//            return uiVizCoord::vizBounds(scale(getWidgetStateX()), scale(getWidgetStateY()), scale(getWidgetStateWidth()),  (isAllocating ? getHoveredTitleBarSize(true) : mUICurrentTitleBarSize));
//        } else if (isTitleBottom()) {
//            return uiVizCoord::vizBounds(scale(getWidgetStateX()), isAllocating ? getHoveredTitleBarSize(true) : scale(getWidgetStateY()) + scale(getWidgetStateHeight()) + mUICurrentTitleBarSize*-1.0f , scale(getWidgetStateWidth()),  mUICurrentTitleBarSize);
//        } else if (isTitleLeft()) {
//           return uiVizCoord::vizBounds(scale(getWidgetStateX()), scale(getWidgetStateY()), mUICurrentTitleBarSize,  scale(getWidgetStateHeight()));
//        } else if (isTitleRight()) {
//            return uiVizCoord::vizBounds(isAllocating ? getHoveredTitleBarSize(true) : scale(getWidgetStateX()) + scale(getWidgetStateWidth()) + mUICurrentTitleBarSize*-1.0f, scale(getWidgetStateY()), mUICurrentTitleBarSize,  scale(getWidgetStateHeight()));
//        }
//        return uiVizCoord::vizBounds(0, 0, 10, 10);
//    }
//
//    void drawWidgetUITitle(bool skipDraw) {
//        
//        if (!getDrawWidgetTitle() || isWidgetUICompletelyTransparent() || mTitleStyle == TitleStyle::NONE) return;
//        
//        if (getIsMinimized() && !isWidgetHovered()) {
//            return;
//        }
//        
//        // Title Autohide check
//        if (!getIsDragging() && !getIsResizing() && getIsTitleAutohide() && !mDidUpdateForAutohide) {
//            if ((!isWidgetHovered() && mUICurrentTitleBarSize > 0) || (isWidgetHovered() && getIsActiveWidget() && mUICurrentTitleBarSize <= 0)) {
//                scaleUITitleSize();
//                setWidgetNeedsUpdate(true);
//                setNeedsUpdate(true);
//                mDidUpdateForAutohide = true;
//                return;
//            }
//        }
//       
//        
//        if (getIsMinimized()) {
//           // mUICurrentTitleBarSize = getHoveredTitleBarSize(true);
//        }
//        
//        
//        //--------------------------- TITLE HOVER (CONTENT RESIZE) -----------------------------------
//        if (!isTitleStatic()) {
//            handleTitle();
//        }
//        
//        //--------------------------- WIDGET TITLE BAR -----------------------------------
//        if (!skipDraw) {
//            ofPushStyle();               
//            ofSetColor(getTitleStateColor());
//            vizElm_WIDGET_TITLE.draw();
//            ofPopStyle();               
//        }
//
//
//        //--------------------------- WIDGET ICONS -----------------------------------
//        int iconWidthUsage = 0;
//        if (!skipDraw && !getIsDragging()) {
//            iconWidthUsage = drawWidgetTitleIcons();
//        }
//
//        
//        //--------------------------- WIDGET TITLE TEXT -----------------------------------        
//        // mMustNotifyAfterUserResizingEndedTimeout is > 0 when user is resizing, skip title text draw
//        if (!skipDraw && mMustNotifyAfterUserResizingEndedTimeout == 0) {
//            if ((getTitle() != "" || getIsVisualDebugMode()) && !isTitleLeft() && !isTitleRight() && !getIsMinimized() &&
//                ((!getIsTitleAutohide() || isWidgetHovered()) || (getIsTitleAutohide() && getIsResizing()) || (getIsTitleAutohide() && getIsDragging()))) {
//
//
//
//                if (widgetTitle.getRectangle().height > rectTitleFontArea.getRectangle().height) {
//
//                    int avalWidthForText = scale(getUsableWidth()) - iconWidthUsage;
//                    // Shorten the title text if too long ...
//                    while(titleFont->width(mDrawableWidgetTitle) > avalWidthForText && mDrawableWidgetTitle.length() > 0)  {
//                        mDrawableWidgetTitle.pop_back();
//                    }
//
//                    ofPushStyle();        
//                    ofSetColor(getTitleFontStateColor());               
//                    titleFont->draw(getIsVisualDebugMode() ? 
//                        ("[" + getWidgetId() + "|" + ofToString(getX()) + "," + ofToString(getY()) + "," + ofToString(getWidth()) + "," + ofToString(getHeight()) + getTitle() + "]") : mDrawableWidgetTitle,
//                        widgetTitle.getRectangle().x + getScaledPadding(),
//                        widgetTitle.getRectangle().y + (widgetTitle.getRectangle().height / 2.0f + rectTitleFontArea.getRectangle().height / 2.5f)
//                    );
//                    ofPopStyle();                                       
//                }
//            }
//        }
//
//    }
//    
//    uiVizIcon getWidgetTitleIconByTag(int iconTag) {
//        for (uiVizIcon icon:mPositionedTitleIcons) {
//            if (icon.getTag() == iconTag) {
//                return icon;
//            }
//        }
//        return uiVizIcon();
//    }
//
//    int drawWidgetTitleIcons() {
//        vector<uiVizIcon> icons = getIsMinimized() ? getWidgetTitleMinimizedIcons() : ((isTitleHovered() || getIsDragging()) && getIsActiveWidget() ? getWidgetTitleHoveredIcons() : getWidgetTitleIcons());
//        int iconWidthUsage = 0;
//
//        if (icons.size() > 0) {
//            for (int i = 0; i <= icons.size() - 1 ; i++) {
//                
//                int iconX = 0;
//                int iconY = 0;
//                
//                if (isTitleTop() || isTitleBottom()) {
//                    iconX = widgetTitle.getRectangle().x + scale(getCoreUsableWidth() ) + ((icons[i].getScaledBounds().width * 1.5f * i) * -1) - getScaledPadding() * 2;
//                    iconY = (widgetTitle.getRectangle().y) + (widgetTitle.getRectangle().height - icons[i].getScaledBounds().height) / 2;
//                } else {
//                    iconX = widgetTitle.getRectangle().x + (widgetTitle.getRectangle().width - icons[i].getScaledBounds().width) / 2;
//                    iconY = (widgetTitle.getRectangle().y) + scale(getCoreUsableHeight()) + ((icons[i].getScaledBounds().height * 1.5f * i) * -1) - getScaledPadding() * 2;
//                }
//                
//                if (getIsActiveWidget() && !getViz()->getIsAnyWidgetDraggingOrResizing()) {
//                    icons[i].setScaledPos(iconX, iconY);
//                    icons[i].setColor(getTheme().TitleFontColor_withAlpha(0.5f));
//                    
//                    if (icons[i].isHovered()) {
//                        icons[i].setColor(getTheme().TitleFontColor);
//                        
//                        uiVizCoord::vizBounds iconBounds = uiVizCoord::vizBounds(
//                                                                                 deScale(icons[i].getScaledBounds().x),
//                                                                                 deScale(icons[i].getScaledBounds().y),
//                                                                                 deScale(icons[i].getScaledBounds().width),
//                                                                                 deScale(icons[i].getScaledBounds().height));
//
//                        uiVizElm vizElm_ICON_HOVER;
//                        vizElm_ICON_HOVER.setRectRounded(
//                                                         scale(iconBounds.x),
//                                                         scale(iconBounds.y),
//                                                         scale(iconBounds.width),
//                                                         scale(iconBounds.height),
//                                                         scale(5),
//                                                         getTheme().TitleColor_withAlpha(getTheme().ContentChromeAlpha));
//                        vizElm_ICON_HOVER.draw();
//                        
//                        titleIconHovered(icons[i].getTag(), iconBounds);
//                        
//                        if (!mIsTitleResizing && getIsMousePressedAndReleasedOverWidget(true)) {
//                            titleIconClicked(icons[i].getTag(), iconBounds);
//                        }
//                    }
//
//                    if (widgetTitle.getRectangle().height >= deScale(icons[i].getScaledBounds().height)  && (!getIsTitleAutohide() || isWidgetHovered())) {
//                        icons[i].drawSvg();
//                    }
//
//                    iconWidthUsage += icons[i].getScaledBounds().width;
//                    
//                }
//            }
//        }
//        mPositionedTitleIcons = icons;
//        return iconWidthUsage + getScaledPadding();
//    }
//
//    void drawWidgetUI(bool skipDrawTitle) {
//        // Widget ui fade in / out
//        if (getWasJustInitialized() && !getIsModalWidget()) {
//            mUICurrentWidgetAlpha = scaleAnimation(getWidgetId() + "_initialized", mUICurrentWidgetAlpha, getTheme().UnhoveredWidgetAlpha, 0.3f);
//            if (mUICurrentWidgetAlpha >= getTheme().UnhoveredWidgetAlpha) {
//                setWasJustInitialized(false);
//            }
//        } else {
//            if ((isWidgetHovered() && getIsActiveWidget()) || getIsModalWidget()) {
//                removeAnimation(getWidgetId() + "_unhovered");
//                mUICurrentWidgetAlpha = scaleAnimation(getWidgetId() + "_hovered", mUICurrentWidgetAlpha, getTheme().HoveredWidgetAlpha, 0.3f);
//            } else {
//                removeAnimation(getWidgetId() + "_hovered");
//                mUICurrentWidgetAlpha = scaleAnimation(getWidgetId() + "_unhovered", mUICurrentWidgetAlpha, getTheme().UnhoveredWidgetAlpha, 0.3f); 
//            }
//        }
//        
//        // Jump out if it's still completely transparrent!
//        if (isWidgetUICompletelyTransparent()) return;
//
//        if (getDrawWidgetChrome()) {
//            //ofSetColor();
//            //vizElm_WIDGET_UI.setRectGradient(ofColor::red, getTitleStateGradientColor2(), getTitleStateGradientColor3(), getTitleStateGradientColor4());    
//            if (getIsHighlighted()) {
//                vizElm_WIDGET_UI_SHADOW.draw();
//            } else {
//                if (getIsShadow()) vizElm_WIDGET_UI_SHADOW.draw();
//            }
//            
//            //  }
//
//            vizElm_WIDGET_UI.setColor(getWidgetStateColor(mUICurrentWidgetAlpha));
//            vizElm_WIDGET_UI.draw();
//            
//            // Uncomment to see resize bars
//            /*
//             if (getIsResizable()) {
//             // move to it's own function, fade in only within 3/4 of position
//             ofPushStyle();                
//             ofSetColor(255, 255, 255, 255 * mUICurrentWidgetAlpha*0.5f);
//             ofDrawRectRounded(widgetResizeBottom.getX(), widgetResizeBottom.getY(), widgetResizeBottom.getWidth(), widgetResizeBottom.getHeight(), 5);
//             ofDrawRectRounded(widgetResizeLeft.getX(), widgetResizeLeft.getY(), widgetResizeLeft.getWidth(), widgetResizeLeft.getHeight(), 5);
//             ofDrawRectRounded(widgetResizeRight.getX(), widgetResizeRight.getY(), widgetResizeRight.getWidth(), widgetResizeRight.getHeight(), 5);
//            ofPopStyle();                
//             }
//             */
//            
//            // Popout arrow
//            if (mPopoutDirection != PopoutDirection::NONE) {
//                vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.setColor(getWidgetStateColor(mUICurrentWidgetAlpha));
//                vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.draw();
//                if (isPopoutFromTitle()) {
//                    vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.setColor(getTitleStateColor());
//                    vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.draw();
//                }
//            }
//            
//        }
//        
//        // Explanation for the following line:
//        // We DONT want to skip drawing the title if user is dragging, very odd looking line, just think double negative...
//        if (!skipDrawTitle) {
//            bool skipDraw = !isTitleStatic() && !getIsDragging() && !getIsResizing() && getIsActiveWidget();
//            drawWidgetUITitle(skipDraw);
//        }
//        
//        if (getIsDragging() || getIsResizing() || mIsTitleResizing || isWidgetHovered()) {
//
//            //--------------------------- MOVING -----------------------------------
//            handleMoveDrag();
//            
//            //--------------------------- RESIZING -----------------------------------
//            handleResize();
//		}
//		else {
//
//		}
//        
//        //--------------------------- RESIZING BY USER ENDED-----------------------------------
//        if (mMustNotifyAfterUserResizingEndedTimeout > 0 && ofGetSystemTimeMillis() >= mMustNotifyAfterUserResizingEndedTimeout && !ofGetMousePressed()) {
//            mMustNotifyAfterUserResizingEndedTimeout = 0;
//            onWidgetResizingByUserEnded(getWidth(), getHeight());
//        }
//    }
//    
//    void handleTitle() {
//        /************************
//         Do NOT call updateWidget or updateWidgetUI
//         inside this function
//         ************************/
//        
//        if (isTitleHovered() && getIsActiveWidget()) {
// 
//            if (mUICurrentTitleBarSize < getHoveredTitleBarSize(true)) {
//                if (!mIsTitleResizing) {
//                    getViz()->boostUserExperience(false);
//                }
//                mIsTitleResizing = true;
//                
//                if (getIsTitleAutohide()) {
//                    mDidUpdateForAutohide = false;
//                }
//                
//                mUICurrentTitleBarSize = scaleAnimationForUI(getWidgetId() + "_hovered_titlebar_size", mUICurrentTitleBarSize, getHoveredTitleBarSize(true), 0.75f);
//                updateWidgetUITitle();
//
//                if (isTitleResize()) {
//                    setNeedsUpdate(true);
//                }
//                
//            } else {
//                if (mIsTitleResizing && (!getViz()->getIsAnyWidgetDraggingOrResizing())) {
//                    getViz()->revertBoostUserExperience();
//                }
//                setNeedsUpdate(true);
//                mIsTitleResizing = false;
//            }
//        } else {
//            if (mUICurrentTitleBarSize > getUnhoveredTitleBarSize(true)) {
//                if (!mIsTitleResizing) {
//                    getViz()->boostUserExperience(false);
//                }
//                mIsTitleResizing = true;
//
//                if (getIsTitleAutohide()) {
//                    mDidUpdateForAutohide = false;
//                }
//                
//                if (getIsDragging() || getIsResizing()) {
//                    return;
//                }
//                mUICurrentTitleBarSize = scaleAnimationForUI(getWidgetId() + "_unhovered_titlebar_size", mUICurrentTitleBarSize, getUnhoveredTitleBarSize(true), 0.75f);
//                updateWidgetUITitle();
//                
//                if (isTitleResize()) {
//                    setNeedsUpdate(true);
//                }
//                
//            } else {
//                if (mIsTitleResizing && (!getViz()->getIsAnyWidgetDraggingOrResizing())) {
//                    getViz()->revertBoostUserExperience();
//                }
//                mIsTitleResizing = false;
//            }
//        }
//    }
//    
//    void handleMoveDrag() {
//        /************************
//         Do NOT call updateWidget or updateWidgetUI
//         inside this function
//         ************************/
//
//        if (!getIsActiveWidget()) {
//            return;
//        }
//        
//        if (!getIsResizing() && (getIsDragging() || (ofGetMousePressed() && isTitleHovered()))) {
//            if (!getIsDragging()) {
//
//                if (mDraggingStartedXOriginal == -1 || mDraggingStartedYOriginal == -1) {
//                    mDraggingStartedXOriginal = ofGetMouseX();
//                    mDraggingStartedYOriginal = ofGetMouseY();
//                }
//
//                if (isTitleHovered() && mDraggingStartedXOriginal == ofGetMouseX() && mDraggingStartedYOriginal == ofGetMouseY()) {
//                    return;
//                }
//
//                setIsDragging(true);
//                getViz()->setIsAnyWidgetDraggingOrResizing(true);
//                getViz()->boostUserExperience(true);
//                mDraggingStartedX = deScale(ofGetMouseX()) - getWidgetStateX();
//                mDraggingStartedY = deScale(ofGetMouseY()) - getWidgetStateY();
//                update(uiVizWidgetContext());
//            }
//            
//            if (!getIsDraggable()) {
//                return;
//            }
//
//            float newX = deScale(ofGetMouseX()) - mDraggingStartedX;
//            float newY = deScale(ofGetMouseY()) - mDraggingStartedY;
//            
//            setWidgetPosition(newX, newY, true);
//            
//            //--------------------------- "UN"DOCKING -----------------------------------
//            if (getX_Expr() != "" && getX_ExprWasSetProgramatically() &&
//                uiVizWidgetBase::getX() < (deScale(ofGetWindowWidth()) - getScreenPadding()*2 - getWidgetStateWidth())) {
//                setX_Expr("");
//            }
//            
//            if (getY_Expr() != "" && getY_ExprWasSetProgramatically() &&
//                uiVizWidgetBase::getY() < (deScale(ofGetWindowHeight()) - getScreenPadding()*2 - getWidgetStateHeight())) {
//                setY_Expr("");
//            }
//            //---------------------------------------------------------------------------
//            
//        } else {
//            setIsDragging(false);
//            mDraggingStartedXOriginal = -1;
//            mDraggingStartedYOriginal = -1;
//            if (!getViz()->getIsAnyWidgetDraggingOrResizing()) {
//                getViz()->revertBoostUserExperience();
//            }
//        }
//        
//        getViz()->setIsAnyWidgetDraggingOrResizing(getIsDragging());
//    }
//    
//    void handleResize() {
//        /************************
//         Do NOT call updateWidget or updateWidgetUI
//         inside this function
//         ************************/
//
//        if (!getIsActiveWidget()) {
//            return;
//        }  
//        
//        if (!getIsResizable() || getIsDragging() || getIsMinimized()) {
//            return;
//        }
//        
//        if (getIsResizing() || (ofGetMousePressed() && (
//                                                    (widgetResizeBottom.isHovered_Rect()) ||
//                                                    (widgetResizeLeft.isHovered_Rect()) ||
//                                                    (widgetResizeRight.isHovered_Rect()))
//                            )) {
//            
//            
//            if (!getIsResizing()) {
//                setIsResizing(true);
//                mMustNotifyAfterUserResizingEndedTimeout = ofGetSystemTimeMillis() + 500;
//
//                getViz()->boostUserExperience(true);
//                mDraggingStartedX = deScale(ofGetMouseX()) - getWidgetStateX();
//                mDraggingStartedY = deScale(ofGetMouseY()) - getWidgetStateY();
//                mResizingStartedX = deScale(ofGetMouseX()) - getWidgetStateWidth();
//                mResizingStartedY = deScale(ofGetMouseY()) - getWidgetStateHeight();
//                
//                if (widgetResizeLeft.isHovered_Rect()) {
//                    mIsResizingLeft = true;
//                }
//            }
//            
//            if (mIsResizingLeft) {
//              //  setWidgetBounds(deScale(ofGetMouseX()) + mResizingStartedX, getWidgetStateY(), getWidgetStateWidth() , getWidgetStateHeight());
//               
//                
//                setWidgetBounds(getWidgetStateX(), getWidgetStateY(), getWidgetStateWidth(), getWidgetStateHeight());
//                
//                /*
//                setWidgetBounds(
//                                deScale(ofGetMouseX()) - mDraggingStartedX,
//                                deScale(ofGetMouseY()) - mDraggingStartedY,
//                                mDraggingStartedX + mResizingStartedX + (-1.0f * deScale(ofGetMouseX())),
//                                mDraggingStartedY + mResizingStartedY + (-1.0f * deScale(ofGetMouseY())));
//                
//                */
//                // BUG :: Left resize doesnt work!!!
//                
//            } else {
//                setWidgetSize(deScale(ofGetMouseX()) - mResizingStartedX, deScale(ofGetMouseY()) - mResizingStartedY, true);
//            }
//            
//            //--------------------------- "UN"DOCKING -----------------------------------
//            if (getWidth_Expr() != "" && getWidth_ExprWasSetProgramatically() &&
//                getWidgetStateWidth() < (deScale(ofGetWindowWidth()) - getScreenPadding()*2)) {
//                setWidth_Expr("");
//            }
//            if (getHeight_Expr() != "" && getHeight_ExprWasSetProgramatically() &&
//                getWidgetStateHeight() < (deScale(ofGetWindowHeight()) - getScreenPadding()*2)) {
//                setHeight_Expr("");
//            }
//            //---------------------------------------------------------------------------
//            
//        } else {
//            
//            setIsResizing(false);
//            mIsResizingLeft = false;
//
//            if (!getViz()->getIsAnyWidgetDraggingOrResizing()) {
//                getViz()->revertBoostUserExperience();
//            }
//        }
//        
//        getViz()->setIsAnyWidgetDraggingOrResizing(getIsResizing());
//    }
//
//	void updateWidgetTitlePathElm() {
//		// $$$ expensive $$$
//        switch(getTitleStyle()) {
//            case TitleStyle::TOP_STATIC: {
//                getIsRoundedRectangle() ? vizElm_WIDGET_TITLE.setRectRounded(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height, scale(5), scale(5), 0, 0) :
//                    vizElm_WIDGET_TITLE.setRectangle(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height);                    
//                break;
//            }
//            case TitleStyle::BOTTOM_STATIC: {
//                getIsRoundedRectangle() ? vizElm_WIDGET_TITLE.setRectRounded(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height, 0, 0, scale(5), scale(5)) :
//                    vizElm_WIDGET_TITLE.setRectangle(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height);                  
//                break;
//            }
//            case TitleStyle::LEFT_STATIC: {
//                getIsRoundedRectangle() ? vizElm_WIDGET_TITLE.setRectRounded(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height, scale(5), 0, 0, scale(5)) :
//                    vizElm_WIDGET_TITLE.setRectangle(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height);
//                break;
//            }
//            case TitleStyle::RIGHT_STATIC: {
//                getIsRoundedRectangle() ? vizElm_WIDGET_TITLE.setRectRounded(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height, 0, scale(5), scale(5), 0) :
//                    vizElm_WIDGET_TITLE.setRectangle(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height);                    
//                break;
//            }
//            default: {
//                getIsRoundedRectangle() ? vizElm_WIDGET_TITLE.setRectRounded(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height, scale(5)) :
//                    vizElm_WIDGET_TITLE.setRectangle(widgetTitle.getRectangle().x, widgetTitle.getRectangle().y, widgetTitle.getRectangle().width, widgetTitle.getRectangle().height);
//                break;
//            }
//        }
//
//        if (getTheme().getTitleGradientSet()) {
//            vizElm_WIDGET_TITLE.setRectGradient(getTitleStateGradientColor1(), getTitleStateGradientColor2(), getTitleStateGradientColor3(), getTitleStateGradientColor4());     
//        }  
//	}
//
//	void updateWidgetUIPathElm() {
//		// $$$ expensive $$$
//        getIsRoundedRectangle() ? vizElm_WIDGET_UI.setRectRounded(widgetFrame.getRectangle().x, widgetFrame.getRectangle().y, widgetFrame.getRectangle().width, widgetFrame.getRectangle().height, scale(5)) :
//            vizElm_WIDGET_UI.setRectangle(widgetFrame.getRectangle().x, widgetFrame.getRectangle().y, widgetFrame.getRectangle().width, widgetFrame.getRectangle().height);               
//
//        // Widget Shadow
//        if (getIsShadow()) {
//            int shadowSize = scale(8);
//
//
//            vizElm_WIDGET_UI_SHADOW.setRectRounded( 
//                vizElm_WIDGET_UI.getRectangle().x - shadowSize, 
//                vizElm_WIDGET_UI.getRectangle().y - shadowSize, 
//                vizElm_WIDGET_UI.getRectangle().width + shadowSize*2,
//                vizElm_WIDGET_UI.getRectangle().height + shadowSize*2,
//                shadowSize, shadowSize, shadowSize, shadowSize
//                );     
//
//            setIsHighlighted(getIsHighlighted());
//
//        }
//   
//
//	}
//  
//    bool isTransitioningAlpha() override {
//        if (!getIsVisible()) return false;
//        return mTransitioningAlpha;
//    }
//
//    virtual bool hasActiveElement() override {
//        for(uiVizWidgetElm &elm:mWidgetElements) {
//            if (elm.getIsActiveWidget()) return true;
//        }
//        return false;
//    }
//    
//    uiVizWidget* mParent = NULL;
//    
//    int mMinimizedWidth, mMinimizedHeight;
//    
//    int mNonMinimizedOffsetX = 0;
//    int mNonMinimizedOffsetY = 0;
//
//    int mMinimizedOffsetX = 0;
//    int mMinimizedOffsetY = 0;
//    
//    bool mIsMinimized = false;
//    bool mDrawWidgetChrome = true;
//    bool mDrawWidgetTitle = true;
//    
//    TitleStyle mTitleStyle = TitleStyle::TOP_STATIC;
//    int mStaticTitleBarSize = 20;
//    string mDrawableWidgetTitle = "";
//        
//    AdditionalState mAdditionalState = AdditionalState::NONE;
//    bool mIsTitleAutohide = false;
//    bool mShowTitleIcons = true;
//    bool mDidUpdateForAutohide = false; // TODO : set it to false when unhovered!
//    shared_ptr<ofxSmartFont> titleFont;
//    uiVizElm rectTitleFontArea;
//    ofRectangle rectTitleFontAreaOf;
//    
//    bool mDrawnByWidgetManager = false;
//    
//    float mUICurrentTitleBarSize = 0;
//    
//    bool mIsResizingLeft = false;
//    bool mIsTitleResizing = false;
//    float mDraggingStartedX = 0;
//    float mDraggingStartedY = 0;
//    float mResizingStartedX = 0;
//    float mResizingStartedY = 0;
//    int mDraggingStartedXOriginal = -1;
//    int mDraggingStartedYOriginal = -1;    
//    uint64_t mMustNotifyAfterUserResizingEndedTimeout = 0;
//    
//    uiVizElm widgetFrame;
//    uiVizElm widgetTitle;
//    
//    uiVizElm widgetResizeBottom;
//    uiVizElm widgetResizeLeft;
//    uiVizElm widgetResizeRight;
//
//    float mUICurrentWidgetAlpha = 0.2f;
//    
//    std::vector<std::reference_wrapper<uiVizWidget>> mChildWidgets;
//    
//    uiVizElm vizElm_WIDGET_CONTENT_BLOCK;
//	uiVizElm vizElm_WIDGET_TITLE;
//	uiVizElm vizElm_WIDGET_UI;
//    uiVizElm vizElm_WIDGET_UI_SHADOW;
//
//	ofFbo fbo;
//    bool mFboNeedsUpdate = true;
//    int mFboAllocatedWidth = 0;
//    int mFboAllocatedHeight = 0;
//
//	FboMode mFboMode = FboMode::HIGH;
//    bool mTransitioningAlpha = false;
//
//    vector<reference_wrapper<uiVizWidgetElm>> mWidgetElements;
//
//};

