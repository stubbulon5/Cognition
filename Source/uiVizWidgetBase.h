/*
  ==============================================================================

    uiVizWidgetBase.h
    Created: 17 Mar 2024 8:22:41am
    Author:  Zabba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class uiVizWidgetBase  : public juce::Component
{
public:
    uiVizWidgetBase()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    uiVizWidgetBase(juce::String persistentId, juce::String widgetXML) {
        loadState(widgetXML);
    }       

    ~uiVizWidgetBase() override
    {
    }

    virtual void paint (juce::Graphics& g) override
    {
        
    }

    virtual void resized() override
    {

    }

   virtual void onWidgetLoaded() {
       // Implement any behaviour for when a widget has loaded
   }

   virtual bool loadState(juce::String widgetXML) {
       bool success = loadState(widgetXML, "widget");
       onWidgetLoaded();
       return success;
   }

   virtual bool loadState(juce::String widgetXML, juce::String parentTag) {
//        ofxXmlSettings mWidgetXML = ofxXmlSettings();
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//             cout << "[" << getPersistentId() << "]uiVizWidgetBase->loadState()\n";
//        #endif
//
//        if (!mWidgetXML.loadFromBuffer(widgetXML.c_str())) {
//            #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3      
//                cout << "[" << getPersistentId() << "]->Unable to load XML\n" << widgetXML.c_str() << "\n";
//            #endif            
//            return false;
//        }        
//        
//        // if has theme specified, use it, otherwise use getDefaultTheme
//        // getDefaultTheme is set by uiViz (loaded at app start)
//        
//        /**** Widget Class Type ****/
//        mWidgetClassType = mWidgetXML.getAttribute(parentTag, "class", "uiVizWidget");
//        /**** Theme ****/
//        string userThemeName = mWidgetXML.getAttribute(parentTag, "theme", "");
//
//        // If it was defined in XML, then persist it...
//        if (userThemeName != "") {
//            setShouldPersistTheme(true);
//        }
//
//        setShouldPersist(mWidgetXML.getAttribute(parentTag, "shouldPersist", false));
//        setIsSystemWidget(mWidgetXML.getAttribute(parentTag, "isSystemWidget", false));
//        setIsVisualDebugMode(mWidgetXML.getAttribute(parentTag, "visualDebugMode", false));
//        string defaultThemeName = getViz()->getThemeManager()->getDefaultTheme().Name;
//        setTheme(getViz()->getThemeManager()->getThemeByName((userThemeName != "" ? userThemeName : defaultThemeName), getIsSystemWidget()));
//        uiVizWidgetTheme theme = getTheme();
//        setIgnoreThemeChanges(userThemeName != "" ? true : false);
//        
//        mWidgetXML.pushTag(parentTag);
//        /**** Title ****/
//        setTitle(mWidgetXML.getValue("title", getTitle()));
//        setIsEnabled(mWidgetXML.getValue("isEnabled", getIsEnabled()));
//        
//        /**** Bounds ****/
//        setMaxWidth(mWidgetXML.getAttribute("bounds", "maxWidth", getMaxWidth()));
//        setMaxHeight(mWidgetXML.getAttribute("bounds", "maxHeight", getMaxHeight()));
//        setMinWidth(mWidgetXML.getAttribute("bounds", "minWidth", getMinWidth()));
//        setMinHeight(mWidgetXML.getAttribute("bounds", "minHeight", getMinHeight()));
//        
//        /* Expressions or regular value for coords / bounds ? */
//        (mWidgetXML.getAttribute("bounds", "widthExpr", "") != "") ?
//            setWidth_Expr(mWidgetXML.getAttribute("bounds", "widthExpr", ofToString(getWidth()))) : setWidth(mWidgetXML.getAttribute("bounds", "width", getWidth()));
//        
//        (mWidgetXML.getAttribute("bounds", "heightExpr", "") != "") ?
//            setHeight_Expr(mWidgetXML.getAttribute("bounds", "heightExpr", ofToString(getHeight()))) : setHeight(mWidgetXML.getAttribute("bounds", "height", getHeight()));
//        
//        (mWidgetXML.getAttribute("bounds", "xExpr", "") != "") ?
//            setX_Expr(mWidgetXML.getAttribute("bounds", "xExpr", ofToString(getX()))) : setX(mWidgetXML.getAttribute("bounds", "x", getX()));
//        
//        (mWidgetXML.getAttribute("bounds", "yExpr", "") != "") ?
//            setY_Expr(mWidgetXML.getAttribute("bounds", "yExpr", ofToString(getY()))) : setY(mWidgetXML.getAttribute("bounds", "y", getY()));
//        
//        setIsAutoResizeToContentsWidth(mWidgetXML.getAttribute("bounds", "autoResizeToContentsWidth", getIsAutoResizeToContentsWidth()));
//        setIsAutoResizeToContentsHeight(mWidgetXML.getAttribute("bounds", "autoResizeToContentsHeight", getIsAutoResizeToContentsHeight()));
//
//        /**** Behaviour ****/
//        setIsDraggable(mWidgetXML.getAttribute("behaviour", "draggable", getIsDraggable()));
//        setIsResizable(mWidgetXML.getAttribute("behaviour", "resizable", getIsResizable()));
//        
//        /**** Appearance ****/
//        setIsShadow(mWidgetXML.getAttribute("appearance", "shadow", getIsShadow()));
//
//        setIsRoundedRectangle(mWidgetXML.getAttribute("appearance", "roundedRectangle",
//                                                      ((ofToLower(parentTag) == "element") ?
//                                                      theme.ElementRoundedRectangle : theme.RoundedRectangle), 0));
//        setIsVisible(mWidgetXML.getAttribute("appearance", "visible", getIsVisible()));
//        setLockAspectRatio(mWidgetXML.getAttribute("appearance", "lockAspectRatio", getLockAspectRatio()));
//        setAspectRatio(mWidgetXML.getAttribute("appearance", "aspectRatio", getAspectRatio()));
//
//        if(mWidgetXML.pushTag("listenEvents")) {
//            for(int i = 0; i <  mWidgetXML.getNumTags("event"); i++){
//                getViz()->addToWidgetEventListenMap(
//                    getPersistentId(),
//                    mWidgetXML.getAttribute("event", "source", "", i),
//                    mWidgetXML.getAttribute("event", "eventName", "", i),
//                    mWidgetXML.getAttribute("event", "redirectEventName", "", i) // for renaming event to another... eg drag_and_drop_data_set -> receive_drag_and_drop_data
//                );
//            }
//            mWidgetXML.popTag(); // listenEvents
//        }
//        
//        mWidgetXML.popTag(); // parentTag
        return true;
   }

        //! The canonical widget reference Id
        juce::String getWidgetId() {
            // String representation of this address:
            const void * address = static_cast<const void*>(this);
            std::stringstream ss;
            ss << address;
            return ss.str();
        }


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (uiVizWidgetBase)
};






//
//
//
////!  The base from which all Widget and Widget Elements are derived. 
///*!
//  Core events and functionality for positioning, updating, drawing, saving and loading Widgets.
//*/
//class uiVizWidgetBase : public ofThread {
//public:
//    // Events
//    ofEvent<uiVizWidgetEventArgs>     widgetHovered;
//    ofEvent<uiVizWidgetEventArgs>     widgetUnhovered;
//    ofEvent<uiVizWidgetEventArgs>     widgetClicked;
//    ofEvent<uiVizWidgetEventArgs>     widgetLostFocus;
//    ofEvent<uiVizWidgetEventArgs>     widgetThemeChanged;
//    ofEvent<uiVizWidgetEventArgs>     widgetEventReceived;
//    ofEvent<ofResizeEventArgs>        widgetResized;
//
//
//    typedef exprtk::expression<float> expression_t;
//    expression_t expression;
//    
//    typedef exprtk::parser<float> calculator_t;
//    calculator_t calculator;
//    
//    enum ScrollAction {
//        ZOOM,
//        SCROLL,
//        BASIC,
//        NONE
//    };
//
//    enum CloseAction {
//        HIDE,
//        REMOVE
//    };    
//    
//    enum class DockLocation {
//        NONE,
//        TOP,
//        BOTTOM,
//        LEFT,
//        RIGHT
//    };
//
//    enum class DisplayType {
//        REGULAR,
//        POPOUT,
//        MENU
//
//    };  
//
//    enum class HorizontalAlign {
//        LEFT,
//        RIGHT,
//        CENTER
//    };    
//
//    enum class VerticalAlign {
//        TOP,
//        BOTTOM,
//        CENTER
//    };
//
//    enum class PopoutDirection { /* C++ 11 */
//        NONE,
//        DOWN,
//        UP,
//        LEFT,
//        RIGHT,
//    };
//
//    struct NonScaledPadding {
//        int top = 0;
//        int right = 0;
//        int bottom = 0;
//        int left = 0;
//        NonScaledPadding(int top, int right, int bottom, int left) : top(top), right(right), bottom(bottom), left(left) {}
//    };
//
//    struct DisplayOptions {
//        DisplayType displayType = DisplayType::REGULAR;
//        HorizontalAlign horizontalAlign = HorizontalAlign::LEFT;
//        VerticalAlign verticalAlign = VerticalAlign::CENTER;
//        NonScaledPadding nonScaledPadding = NonScaledPadding(0, 0, 0, 0);
//        // TODO: Add : MinWidth, MinHeight, Gradient colours?
//        DisplayOptions() {}
//        DisplayOptions(DisplayType displayType, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) : 
//            displayType(displayType), horizontalAlign(horizontalAlign), verticalAlign(verticalAlign) {}
//
//        DisplayOptions(DisplayType displayType, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign, NonScaledPadding nonScaledPadding) : 
//            displayType(displayType), horizontalAlign(horizontalAlign), verticalAlign(verticalAlign), nonScaledPadding(nonScaledPadding) {}     
//
//        DisplayOptions fromString(string semiColonDelimitedString) { // just like CSS eg a:1;b:2
//            DisplayOptions r = DisplayOptions();
//            semiColonDelimitedString = ofToUpper(semiColonDelimitedString);
//            ofStringReplace(semiColonDelimitedString, " ", "");
//            vector<string> pairs = ofSplitString(semiColonDelimitedString, ";");  
//            for(string pair:pairs) {
//                vector<string> keyVal = ofSplitString(pair, ":");
//                if (keyVal.size() < 2) continue;
//                if (keyVal[0] == "DISPLAYTYPE") {
//                    if(keyVal[1] == "REGULAR") { r.displayType = DisplayType::REGULAR; } else if 
//                      (keyVal[1] == "POPOUT") { r.displayType = DisplayType::POPOUT; } else if 
//                      (keyVal[1] == "MENU") { r.displayType = DisplayType::MENU; }
//                }
//            }
//            return r;  
//        }              
//    }; 
//
//    uiVizWidgetBase(string persistentId, string widgetXML) : mPersistentId(persistentId) {
//        mPersistentId = ofToUpper(mPersistentId);
//        init();
//        loadState(widgetXML);
//    }
//
//    uiVizWidgetBase(string persistentId, string widgetXML, string ownerWidgetId) : mPersistentId(persistentId), mOwnerWidgetId(ownerWidgetId) {
//        mPersistentId = ofToUpper(mPersistentId);
//        init();
//        loadState(widgetXML);
//    }    
//
//    virtual ~uiVizWidgetBase() {
//        // Make sure every event listened to is removed in destructor!
//        // NOTE ON VIRTUAL DESTRUCTOR : For this exampe: Base *myObj = new Derived(); delete myObj; If your derived class destructor is NOT virtual then
//        // only base class object will get deleted (because pointer is of base class "Base *myObj"). So there will be memory leak for derived object.
//        ofRemoveListener(getViz()->scaleChanged, this, &uiVizWidgetBase::onCoreWidgetScaleChanged);
//        ofRemoveListener(ofEvents().windowResized, this, &uiVizWidgetBase::onCoreWidgetWindowResized);
//        ofRemoveListener(ofEvents().mouseMoved, this, &uiVizWidgetBase::onCoreWidgetMouseMoved);
//        ofRemoveListener(ofEvents().mousePressed, this, &uiVizWidgetBase::onCoreWidgetMousePressed);
//        ofRemoveListener(ofEvents().mouseReleased, this, &uiVizWidgetBase::onCoreWidgetMouseReleased);
//        ofRemoveListener(ofEvents().mouseScrolled, this, &uiVizWidgetBase::onCoreWidgetMouseScrolled);
//        ofRemoveListener(ofEvents().fileDragEvent, this, &uiVizWidgetBase::onCoreWidgetFileDragEvent);
//		ofRemoveListener(ofEvents().mouseDragged, this, &uiVizWidgetBase::onCoreWidgetMouseDragged);
//        ofRemoveListener(ofEvents().mouseEntered, this, &uiVizWidgetBase::onCoreWindowMouseEntered);
//        ofRemoveListener(ofEvents().mouseExited, this, &uiVizWidgetBase::onCoreWindowMouseExited);        
//		ofRemoveListener(ofEvents().keyPressed, this, &uiVizWidgetBase::onCoreWidgetKeyPressed);
//		ofRemoveListener(ofEvents().keyReleased, this, &uiVizWidgetBase::onCoreWidgetKeyReleased);
//        
//        // Touch events
//        ofRemoveListener(ofEvents().touchDown, this, &uiVizWidgetBase::onCoreWidgetTouchDown);
//        ofRemoveListener(ofEvents().touchUp, this, &uiVizWidgetBase::onCoreWidgetTouchUp);
//        ofRemoveListener(widgetEventReceived, this,  &uiVizWidgetBase::onCoreWidgetEventReceived);
//        ofRemoveListener(widgetResized, this,  &uiVizWidgetBase::onCoreWidgetResized);   
//
//        getViz()->removeListeningEvents(getPersistentId());
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
//        cout << "[" << getPersistentId() << "]~uiVizWidgetBase()\n";
//        #endif
//    }
//    
//    bool getIsPermanentWidget() {
//        return mIsPermanentWidget;
//    }  
//
//    void setIsPermanentWidget(bool val) {
//        mIsPermanentWidget = val;
//    }
//
//    bool getIsHighlighted() {
//        return mIsHighlighted;
//    }  
//
//    virtual void setIsHighlighted(bool val) {
//        mIsHighlighted = val;
//    }
//
//    //! Hook before destructor is called. Use it to clear event listeners, etc
//    virtual void beforeDelete() {
//    }
//
//    void deleteThisWidget() {
//
//        /* 
//            If getting unexpected EXC_BAD_ACCESS errors make sure to check that ALL widgets are callling 
//            ofRemoveListener for ALL corresponding ofAddListener in ther destructors!
//        */
//
//        mShouldDeleteThisWidget = true;
//        if (getShowingAsPopout()) {
//            getViz()->setIsPopoutVisible(getWidgetId(), false);
//        }
//        clearActiveWidgetId();
//    }
//    
//    bool shouldDeleteThisWidget() {
//        return mShouldDeleteThisWidget;
//    }
//
//    void closeThisWidget(string result) {
//        switch(getCloseAction()) {
//            case CloseAction::HIDE: {
//                mShouldCloseThisWidget = true;
//                break;
//            }
//            case CloseAction::REMOVE: {
//                deleteThisWidget();
//                break;
//            }
//        }
//        getWidgetClosedCallback()(getPopoutOpenerWidget(), this, result); // call it...  
//
//        // Is below line necessary ???
//        // if(getPopoutWidget()) {
//        //     getPopoutWidget()->getWidgetClosedCallback()(getPopoutOpenerWidget(), this, result);
//        // }
//    }
//
//    void closeThisWidget() {
//        closeThisWidget("CLOSED");
//    }
//
//    std::function<void(uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, const string &)> getWidgetClosedCallback() { 
//        return mWidgetClosedCallback;
//    }    
//
//    void setWidgetClosedCallback(std::function<void(uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, const string &)> widgetClosedCallback) { 
//        mWidgetClosedCallback = widgetClosedCallback;
//    }      
//
//    bool shouldCloseThisWidget() {
//        return mShouldCloseThisWidget;
//    }    
//
//	void setIsEnabled(bool val) {
//        if (val != mIsEnabled) {
//
//            uiVizWidgetTheme theme = getViz()->getThemeManager()->getThemeByName(getTheme().Name);
//            if(!val) theme = getViz()->getThemeManager()->getLessOpacity(theme, true, 0.85f);
//            setTheme(theme);
//            setNeedsUpdate(true);
//            setWidgetNeedsUpdate(true);
//        }
//		mIsEnabled = val;
//	}
//
//	bool getIsEnabled() {
//		return mIsEnabled;
//	}   
//
//	virtual void setWasJustInitialized(bool val) {
//        mWasJustInitialized = val;
//        if (val) {
//            initWidgetScale(getViz()->getUserScale());
//            onWidgetScaleChanged(getViz()->getUserScale());
//            setExpressionRecalculationRequired(true);
//            onWidgetWasJustInitialized();
//        }
//	}
//
//	bool getWasJustInitialized() {
//		return mWasJustInitialized;
//	}
//
//    void updateWidgetPopoutArrow() {
//        
//        if (mPopoutDirection == PopoutDirection::NONE) return;
//        
//        int bubbleWidth = 15;
//
//        bool isPopingOutFromWidget = mPopoutFromWidget && mPopoutFromWidget != nullptr;
//
//        int rawPopoutX = mRawPopoutX;
//        int rawPopoutY = mRawPopoutY;
//
//        if (isPopingOutFromWidget) { 
//
//            int w = mPopoutFromWidget->getWidgetStateWidth();
//            int h = mPopoutFromWidget->getWidgetStateHeight();
//
//            switch(mPopoutDirection) {
//                case PopoutDirection::DOWN:{
//                    rawPopoutY = mPopoutFromWidget->getY() + (h + getNonScaledPadding() * 2);                
//                    rawPopoutX = mPopoutFromWidget->getX() + (w / 2.0f);
//                    break;
//                }
//                case PopoutDirection::UP:{
//                    rawPopoutY = mPopoutFromWidget->getY() - getHeight() - getNonScaledPadding() * 2;                
//                    rawPopoutX = mPopoutFromWidget->getX() + (w / 2.0f);                
//                    break;
//                }
//                case PopoutDirection::LEFT:{
//                    rawPopoutY = mPopoutFromWidget->getY() + (h / 2.0f);                                
//                    rawPopoutX = mPopoutFromWidget->getX() - getWidth() - getNonScaledPadding() * 2;                
//                    break;
//                }
//                case PopoutDirection::RIGHT:{
//                    rawPopoutY = mPopoutFromWidget->getY() + (h / 2.0f);                                  
//                    rawPopoutX = mPopoutFromWidget->getX()+ (w + getNonScaledPadding() * 2);                
//                    break;
//                }
//            }
//        } else {
//            switch(mPopoutDirection) {
//                case PopoutDirection::DOWN:{
//                    break;
//                }
//                case PopoutDirection::UP:{
//                    rawPopoutY = rawPopoutY - getHeight() + getNonScaledPadding() - deScale(bubbleWidth / 2.0f);
//                    break;
//                }
//                case PopoutDirection::LEFT:{
//                    rawPopoutX = rawPopoutX - getWidth() + getNonScaledPadding() - deScale(bubbleWidth / 2.0f);                
//                    break;
//                }
//                case PopoutDirection::RIGHT:{
//                    break;
//                }
//            }
//        }
//
//        int x = rawPopoutX;
//        int y = rawPopoutY;
//        
//        int bubbleOffset = mPopoutOffset;
//        setScreenPadding(5);
//        int widgetCenterX = x - (getWidth() / 2.0f);
//        int widgetCenterY = y - (getHeight() / 2.0f);
//        
//        int bubbleOffsetWidth = bubbleWidth + getScreenPadding() + (getNonScaledPadding()/2.0f) + scale(1);
//        int maxX = (deScale(ofGetWindowWidth()) - bubbleOffset - getWidgetStateWidth());
//        int maxY = (deScale(ofGetWindowHeight()) - bubbleOffset - getWidgetStateHeight());
//        
//        if (mPopoutDirection == PopoutDirection::RIGHT && x > maxX) mPopoutDirection = PopoutDirection::LEFT;
//        if (mPopoutDirection == PopoutDirection::DOWN && y > maxY) mPopoutDirection = PopoutDirection::UP;
//
//        switch(mPopoutDirection) {
//            case PopoutDirection::DOWN:
//            case PopoutDirection::UP:
//                setWidgetPosition(widgetCenterX,
//                                  (mPopoutDirection == PopoutDirection::DOWN) ? max(y, bubbleOffset) : min(y, maxY)
//                                  , false);
//                
//                mPopoutX = min(x, (int)(deScale(ofGetWindowWidth()) - bubbleOffsetWidth));
//                mPopoutX = max(mPopoutX, bubbleOffsetWidth);
//                mPopoutY = (mPopoutDirection == PopoutDirection::DOWN) ? max(getY(), bubbleOffset) : max(getY(), getY() + getHeight());
//                break;
//            case PopoutDirection::LEFT:
//            case PopoutDirection::RIGHT:
//                setWidgetPosition((mPopoutDirection == PopoutDirection::RIGHT) ? max(x, bubbleOffset) : min(x, maxX),
//                                  widgetCenterY
//                                  , false);
//                
//                mPopoutY = min(y, (int)(deScale(ofGetWindowHeight()) - bubbleOffsetWidth));
//                mPopoutY = max(mPopoutY, bubbleOffsetWidth);
//                mPopoutX = (mPopoutDirection == PopoutDirection::RIGHT) ? max(getX(), bubbleOffset) : max(getX(), getX() + getWidth());
//                break;
//        }
//
//        mPopoutX = scale(mPopoutX);
//        mPopoutY = scale(mPopoutY);
//        bubbleWidth = scale(bubbleWidth);
//        bubbleOffset = scale(bubbleOffset);
//
//        switch(mPopoutDirection) {
//            case PopoutDirection::DOWN:
//            case PopoutDirection::UP:
//                vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.setTriangle(
//                    mPopoutX - bubbleWidth, mPopoutY,
//                    mPopoutX, (mPopoutDirection == PopoutDirection::DOWN) ? mPopoutY-bubbleOffset : mPopoutY+bubbleOffset, // center top point
//                    mPopoutX + bubbleWidth, mPopoutY);
//                break;
//            case PopoutDirection::LEFT:
//            case PopoutDirection::RIGHT:
//                vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE.setTriangle(
//                    mPopoutX, mPopoutY - bubbleWidth,
//                    (mPopoutDirection == PopoutDirection::RIGHT) ? mPopoutX-bubbleOffset : mPopoutX+bubbleOffset, mPopoutY,  // center left point
//                    mPopoutX, mPopoutY + bubbleWidth);
//                break;
//        }
//    }
//    
//    virtual void popoutFrom(int x, int y, PopoutDirection popoutDirection) {
//        setIsDraggable(false);
//        mRawPopoutX = x;
//        mRawPopoutY = y;
//        mPopoutDirection = popoutDirection;
//        setSize(getWidth(), getHeight());
//        updateWidgetPopoutArrow();
//        setShowingAsPopout(true);
//        setIsVisible(true);
//        setActiveWidget();
//        //setMinimumWidth(getX()-);
//        onWidgetShownAsPopout(nullptr);
//        // if (parent()) {
//        //     parent()->setExpressionRecalculationRequired(true);
//        //     parent()->setWidgetNeedsUpdate(true);
//        // }
//        // setExpressionRecalculationRequired(true);
//        // setWidgetNeedsUpdate(true);
//    }
//
//    virtual void popoutFrom(uiVizWidgetBase* obj, PopoutDirection popoutDirection, uiVizWidgetTheme theme) {
//        setIsDraggable(false);
//
//        if (theme.Name != "") {
//            setTheme(theme);
//        }
//
//        mPopoutDirection = popoutDirection;
//        mPopoutFromWidget = obj;
//        if (mPopoutFromWidget) setPopoutOpenerWidget(mPopoutFromWidget);        
//
//
//// popout bug froim stringed
//        setSize(getWidth(), getHeight());       
//        updateWidgetPopoutArrow();
//        setShowingAsPopout(true);
//        setIsRoundedRectangle(true);
//        setIsVisible(true);
//        setActiveWidget();
//        onWidgetShownAsPopout(obj);
//    }  
//
//    virtual void popoutFrom(uiVizWidgetBase* obj, PopoutDirection popoutDirection, bool ignoreTheme = false) {
//        uiVizWidgetTheme theme = uiVizWidgetTheme();
//        if(obj && obj->parent()) theme = getViz()->getThemeManager()->getContrastingSystemTheme(obj->parent()->getTheme(), true);
//        popoutFrom(obj, popoutDirection, ignoreTheme ? uiVizWidgetTheme() : theme);
//    }
//
//    void popoutWithoutArrow(int x, int y) {
//        setIsDraggable(false);
//        setShowingAsPopout(true);
//        setWidgetPosition(x, y, false);        
//        setIsVisible(true);
//        setActiveWidget();
//        onWidgetShownAsPopout(nullptr);
//    }  
//
//    uiVizWidgetBase* getTargetDropWidget() {
//        return mTargetDropWidget;
//    }
//
//    void setTargetDropWidget(uiVizWidgetBase* val) {
//        mTargetDropWidget = val;
//    }             
//
//    virtual void showClipboardForThisWidget(bool val) {
//        mShouldShowClipboardForThisWidget = val;
//    }
//    
//    bool shouldShowClipboardForThisWidget() {
//        return mShouldShowClipboardForThisWidget;
//    }
//    
//    virtual string getSelectionDataForClipboard() {
//        // Implement
//        return "";
//    }
//    
//    bool getShouldPersist() {
//        return mShouldPersist;
//    }
//    
//    void setShouldPersist(bool val) {
//        mShouldPersist = val;
//    }
//
//    bool getShouldPersistTheme() {
//        return mShouldPersistTheme;
//    }
//    
//    void setShouldPersistTheme(bool val) {
//        mShouldPersistTheme = val;
//    }    
//    
//    virtual uiVizWidgetTheme& getTheme() {
//        return mTheme;
//    }
//    
//    virtual void setTheme(uiVizWidgetTheme val) {
//        bool valChanged = (mTheme.Name != val.Name);
//        mTheme = val;
//        if (valChanged) {
//            uiVizWidgetEventArgs args = uiVizWidgetEventArgs(getWidgetId(), *this);            
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//            ofNotifyEvent(widgetThemeChanged, args);
//            onWidgetThemeChanged(args);
//        }
//    }
//
//    float getStrongChromeAlpha() {
//        return 0.95f;
//    }        
//    
//
//    /*!
//        Load state from XML. Use this to popuate member level variables. Do not call virtual methods here.  
//    */

//    
//    static string getWidgetXMLFromFile(string fileName, bool exceptionIfNotFound) {
//        ofxXmlSettings widgetFile = ofxXmlSettings();
//        if (widgetFile.load(ofToDataPath(fileName))) {
//            TiXmlElement* rootElm = widgetFile.doc.RootElement();
//            TiXmlPrinter printer;
//            rootElm->Accept( &printer );
//            string widgetXML = printer.CStr();
//            return widgetXML;
//        }
//        if(exceptionIfNotFound) {
//            string exceptionStr = "[" + fileName + "] file not found or is invalid! Exiting...";
//            ofSystemAlertDialog(exceptionStr);
//            throw std::runtime_error(exceptionStr.c_str());
//            OF_EXIT_APP(1);            
//        }
//        return "";
//    }
//
//    static uiVizWidgetSignature getWidgetSignatureFromXML(string widgetXML) {
//        uiVizWidgetSignature widget;        
//        ofxXmlSettings widgetSettings = ofxXmlSettings();
//        if (widgetXML != "" && widgetSettings.loadFromBuffer(widgetXML)) {
//            string persistentId = widgetSettings.getAttribute("widget", "id", "");
//            string widgetClass = widgetSettings.getAttribute("widget", "class", "uiVizWidget");
//            widget = uiVizWidgetSignature(persistentId, widgetClass, widgetXML);
//        }
//        return widget;
//    }    
//
//    static uiVizWidgetSignature getWidgetSignatureFromFile(string fileName) {
//        uiVizWidgetSignature widgets;        
//        string widgetXML = getWidgetXMLFromFile(fileName, false);
//        return getWidgetSignatureFromXML(widgetXML);
//    }    
//    
//    bool loadStateFromFile(string fileName) {
//        string xml = getWidgetXMLFromFile(fileName, false);
//        if (xml != "") {
//            return loadState(xml);
//        } else {
//            return false;
//        }
//    }
//    
//

//
//     //! Implement any behaviour in derrived class which should handle when this widget changes visibility.
//	virtual void onWidgetVisibilityChanged(bool visible) {
//	}
//
//     //! Implement any behaviour in derrived class which should handle when this widget is initialized.
//	virtual void onWidgetWasJustInitialized() {
//	}
//
//     //! Implement any behaviour in derrived class which should handle when this widget is shown as a popout.
//	virtual void onWidgetShownAsPopout(uiVizWidgetBase* poppedOutFrom) {
//	}    
//    
//
//    virtual bool loadState(string widgetXML) {
//        bool success = loadState(widgetXML, "widget");
//        onWidgetLoaded();
//        return success;
//    }
//    
//    virtual ofxXmlSettings saveState(string parentTag) {
//        
//        ofxXmlSettings mWidgetXML = ofxXmlSettings();
//        
//        string additionalAttrib = "";
//        if (getShouldPersistTheme()) {
//            additionalAttrib += (getTheme().isDefault() ? "" : " theme='" + getTheme().Name + "'"); // don't persist theme name if default
//        }
//
//        if (getShouldPersist()) {
//            additionalAttrib += " shouldPersist='1'";
//        }        
//        
//        if (getIsVisualDebugMode()) {
//            additionalAttrib += " visualDebugMode='1'";
//        }
//
//        string xmlBuff =
//        "<" + parentTag + " id='" + getPersistentId() + "' class='uiVizWidget'" + additionalAttrib + ">" 
//        "<title>" + getTitle() + "</title>"
//        "<bounds "
//            "x='" + ofToString(getX()) + "'  y='" + ofToString(getY()) + "' "
//            "width='" + ofToString(getWidth()) + "'  height='" + ofToString(getHeight()) + "' "
//            "maxWidth='" + ofToString(getMaxWidth()) + "'  maxHeight='" + ofToString(getMaxHeight()) + "' "
//            "minWidth='" + ofToString(getMinWidth()) + "'  minHeight='" + ofToString(getMinHeight()) + "' "
//        "></bounds>"
//        "<behaviour "
//            "draggable='" + ofToString(getIsDraggable()) + "'  resizable='" + ofToString(getIsResizable()) + "' "
//        "></behaviour>"
//        "<appearance "
//            "visible='" + ofToString(getIsVisible()) + "' "
//            "shadow='" + ofToString(getIsShadow()) + "' "
//            "roundedRectangle='" + ofToString(getIsRoundedRectangle()) + "' "
//            "lockAspectRatio='" + ofToString(getLockAspectRatio()) + "'  aspectRatio='" + ofToString(getAspectRatio()) + "' "
//        "></appearance>"
//        "<properties/>"
//        "</" + parentTag + ">";
//        
//        // Expression bounds... eg ${MY_GUITAR.RIGHT}-20
//        if (mWidgetXML.loadFromBuffer(xmlBuff.c_str())) {
//            mWidgetXML.pushTag(parentTag);
//            if (getX_Expr() != "") {
//                mWidgetXML.removeAttribute("bounds", "x");
//                mWidgetXML.setAttribute("bounds", "xExpr", getX_Expr(), 0);
//            }
//            if (getY_Expr() != "") {
//                mWidgetXML.removeAttribute("bounds", "y");
//                mWidgetXML.setAttribute("bounds", "yExpr", getY_Expr(), 0);
//            }
//            if (getWidth_Expr() != "") {
//                mWidgetXML.removeAttribute("bounds", "width");
//                mWidgetXML.setAttribute("bounds", "widthExpr", getWidth_Expr(), 0);
//            }
//            if (getHeight_Expr() != "") {
//                mWidgetXML.removeAttribute("bounds", "height");
//                mWidgetXML.setAttribute("bounds", "heightExpr", getHeight_Expr(), 0);
//            }
//            if (getIsAutoResizeToContentsWidth()) {
//                mWidgetXML.setAttribute("bounds", "autoResizeToContentsWidth", true, 0);
//            }
//            if (getIsAutoResizeToContentsHeight()) {
//                mWidgetXML.setAttribute("bounds", "autoResizeToContentsHeight", true, 0);
//            }         
//
//            // Listen events
//            vector<uiViz::WidgetEvent> listeningEvents = getViz()->getListeningEvents(getPersistentId());
//            if(listeningEvents.size() > 0) {
//                mWidgetXML.addTag("listenEvents");   
//                mWidgetXML.pushTag("listenEvents");    
//                int eventIndex = 0;
//                for(uiViz::WidgetEvent e:listeningEvents) {
//                    mWidgetXML.addTag("event"); 
//                    mWidgetXML.setAttribute("event", "source", e.eventSenderId, eventIndex);
//                    mWidgetXML.setAttribute("event", "eventName", e.eventName, eventIndex);
//                    if (e.redirectEventName != "") mWidgetXML.setAttribute("event", "redirectEventName", e.redirectEventName, eventIndex);
//                    eventIndex++;
//                }
//                mWidgetXML.popTag(); // listenEvents        
//            }
// 
//
//
//            mWidgetXML.popTag(); // parentTag
//        }
//        return mWidgetXML;
//    }
//
//    virtual string getWidgetPrettyName() {
//        return uiVizShared::lang("WIDGET_NAME_" + getWidgetClassType());   // eg WIDGET_NAME_uiVizWidget in Lanuguage XML file
//    }
//
//    string getWidgetClassType() {
//        return mWidgetClassType;
//    }
//    
//    void setWidgetClassType(string val) {
//        mWidgetClassType = val;
//    }
//    
//    virtual ofxXmlSettings saveState() {
//        return saveState("widget");
//    }
//    
//    virtual string getXML() {
//        ofxXmlSettings mWidgetXML = saveState();
//        string XML = "";
//        mWidgetXML.copyXmlToString(XML);
//        return XML;
//    }
//    
//    widgetTelemetry* getWidgetTelemetry() {
//        return &mWidgetTelemetry;
//    }
//  
//    virtual void onWidgetThemeChanged(uiVizWidgetEventArgs args) {
//        // Implement any behaviour in derrived class which should theme change...
//    }
//
//    bool eventListenersExistForThisWidget(string eventName) {
//        //return getTransmitOscMessages() || getViz()->doesWidgetHaveListeners(getPersistentId(), eventName);
//        return getViz()->doesWidgetHaveListeners(getPersistentId(), eventName);
//    }
//
//    void eventTransmit(string eventSenderId, string eventName, string eventXML, uiVizWidgetBase& sender, uiVizWidgetBase* target, bool dispatchToLocalListeners) {
//        ofxXmlSettings xml = ofxXmlSettings();
//        if (!xml.loadFromBuffer(eventXML.c_str())) {
//            ofLogWarning("uiVizWidget") << eventSenderId << "." << eventName << ": failed to parse event XML \n" << eventXML;
//        }
//        
//        uiVizWidgetEventArgs args = uiVizWidgetEventArgs(eventSenderId, eventName, xml, sender, target);
//        ofNotifyEvent(widgetEventReceived, args);
//        onWidgetEventReceived(args);
//
//        target ? getViz()->addToEventTransmitQueue("/widget/event_transmit", "widget", eventSenderId, target->getPersistentId(), eventName, eventXML, getTransmitOscMessages(), dispatchToLocalListeners) : 
//            getViz()->addToEventTransmitQueue("/widget/event_transmit", "widget", eventSenderId, "", eventName, eventXML, getTransmitOscMessages(), dispatchToLocalListeners);
//        
//    }
//
//    void eventTransmit(string eventSenderId, string eventName, string eventXML, uiVizWidgetBase& sender, uiVizWidgetBase* target) {
//        eventTransmit(eventSenderId, eventName, eventXML, sender, target, true);
//    }
//
//    void eventTransmit(string eventSenderId, string eventName, string eventXML, uiVizWidgetBase& sender) {
//        eventTransmit(eventSenderId, eventName, eventXML, sender, nullptr);
//    }    
//
//    void addToEventTransmitQueue(string eventName, string eventXML) {
//        if(!eventListenersExistForThisWidget(eventName)) return;
//        getViz()->addToEventTransmitQueue(
//            "/widget/event_transmit", "widget", getPersistentId(), "", eventName, eventXML, getTransmitOscMessages(), true
//        );
//    }    
//    
//    virtual void onCoreWidgetEventReceived(uiVizWidgetEventArgs &args) {
//        // Internal...
//    }
//    
//    virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) {
//        // To be overridden in derived classes
//    }
//    
//    shared_ptr<ofxSmartFont> getSmallFontSizedForDimensions(int width, int height) {
//        return getViz()->getSmallFontSizedForDimensions(width, height);
//    }
//    
//    shared_ptr<ofxSmartFont> getMediumFontSizedForDimensions(int width, int height) {
//        return getViz()->getMediumFontSizedForDimensions(width, height);
//    }
//
//    shared_ptr<ofxSmartFont> getFontSizedForDimensions(int width, int height) {
//        return getViz()->getFontSizedForDimensions(width, height);
//    }
//    
//    shared_ptr<ofxSmartFont> getLargeFontSizedForDimensions(int width, int height) {
//        return getViz()->getLargeFontSizedForDimensions(width, height);
//    }
//    
//    virtual void setNeedsUpdate(bool needsUpdate) {
//        mNeedsUpdate = needsUpdate;
//    }
//    
//    bool needsUpdate() {
//        return mNeedsUpdate;
//    }
//    
//    // For content chrome
//    void setWidgetNeedsUpdate(bool needsUpdate) {
//        mWidgetUINeedsUpdate = needsUpdate;
//
//        #if VIZ_DEBUG_LEVEL >= 1 && VIZ_DEBUG_LEVEL < 2
//            cout << "UPDATING WIDGET..." + getWidgetId() + " [" + getTitle() + "]\n";
//        #endif        
//    }
//    
//    bool widgetNeedsUpdate() {
//        return mWidgetUINeedsUpdate;
//    }
//    
//    //! Set up visual elements in this function which require scaling
//    virtual void initWidgetScale(float scale) {
//        
//    }
//
//    //! set up all the stuff upon widget initialization
//    virtual void initWidget() {
//    }
//    
//    virtual void update(uiVizWidgetContext context) {
//        // Implemented by descendant class...
//    }
//    
//    virtual void draw(uiVizWidgetContext context) {
//        // Implemented by descendant class...
//    }
//
//    //! The widget reference Id which gets persisted when saving / serializing
//    string getPersistentId() {
//        return mPersistentId;
//    }
//    
//    void setPersistentId(string val) {
//        mPersistentId = ofToUpper(val);
//    }
//
//    //! The parent widget reference Id for this widget
//    string getParentPersistentId() {
//        return parent() ? parent()->getPersistentId() : "";
//    }    
//
//    //!  Raw X position. Excludes padding.
//    virtual int getX() {
//        return mX;
//    }
//    
//    //!  Raw Y position. Excludes padding.    
//    virtual int getY() {
//        return mY;
//    }
//    
//    //!  Raw Width. Excludes padding.
//    virtual int getWidth() {
//        return mWidth;
//    }
//    
//    //!  Raw Height. Excludes padding.    
//    virtual int getHeight() {
//        return mHeight;
//    }
//
//    //!  X position. Includes padding. Includes scroll offset.
//    virtual int getUsableX() {
//        return getUsableX(true);
//    }
//    
//    //!  Y position. Includes padding. Includes scroll offset.
//    virtual int getUsableY() {
//        return getUsableY(true);
//    }
//    
//    virtual int getUsableX(bool inclScrollOffset) {
//        int scrollOffsetX = inclScrollOffset ? getScrollOffsetX() : 0;
//        return getX() + scrollOffsetX;
//    }
//    
//    virtual int getUsableY(bool inclScrollOffset) {
//        int scrollOffsetY = inclScrollOffset ? getScrollOffsetY() : 0;
//        return getY() + scrollOffsetY;
//    }
//    
//    //!  Usable Width. Includes padding.    
//    virtual int getUsableWidth() {
//        return getWidth();
//    }
//    
//    //!  Usable Height. Includes padding.        
//    virtual int getUsableHeight() {
//        return getHeight();
//    }  
//
//    //!  Usable Width. Includes padding. (same as getUsableWidth() for uiVizWidgetBase)
//    virtual int getWidgetStateWidth() {
//        return getUsableWidth();
//    }
//    
//    //!  Usable Height. Includes padding. (same as getUsableHeight() for uiVizWidgetBase) 
//    virtual int getWidgetStateHeight() {
//        return getUsableHeight();
//    }    
//
//    //!  Should this widget resize to it's content width? Required implementation by widget developer
//    virtual bool getIsAutoResizeToContentsWidth() {
//        return mIsAutoResizeToContentsWidth;
//    }
//    
//     //!  Set wether this widget should resize to it's content width? Required implementation by widget developer
//    virtual void setIsAutoResizeToContentsWidth(bool val) {
//        mIsAutoResizeToContentsWidth = val;
//    }
//    
//    //!  Should this widget resize to it's content height? Required implementation by widget developer    
//    virtual bool getIsAutoResizeToContentsHeight() {
//        return mIsAutoResizeToContentsHeight;
//    }
//    
//    //!  Set wether this widget should resize to it's content height? Required implementation by widget developer    
//    virtual void setIsAutoResizeToContentsHeight(bool val) {
//        mIsAutoResizeToContentsHeight = val;
//    }    
//
//    int getScreenPadding() {
//        return mScreenPadding;
//    }
//    
//    void setScreenPadding(int val) {
//        mScreenPadding = val;
//    }
//    
//    string getX_Expr() {
//        return mX_Expr;
//    }
//    
//    string getY_Expr() {
//        return mY_Expr;
//    }
//    
//    string getWidth_Expr() {
//        return mWidth_Expr;
//    }
//    
//    string getHeight_Expr() {
//        return mHeight_Expr;
//    }
//
//    string getTitle() {
//        return mTitle;
//    }
//    
//    virtual int getTitleWidth() {
//        return (getTitle().size() > 0 ? mTitleWidth : 0);
//    }
//    
//    void setTitleWidth(int val) {
//        mTitleWidth = val;
//    }
//    
//    virtual void setTitle(string title) {
//        mTitle = title;
//    }
//    
//    bool getExpressionReferencesPersistentId(string persistentId) {
//
//        if (!getIsVisible()) return false;
//
//        return 
//            ofIsStringInString(getX_Expr(), "${" + persistentId) ||
//            ofIsStringInString(getY_Expr(), "${" + persistentId) ||
//            ofIsStringInString(getWidth_Expr(), "${" + persistentId) ||
//            ofIsStringInString(getHeight_Expr(), "${" + persistentId);
//    }
//
//    virtual bool getExpressionRecalculationRequired() {
//        return getIsVisible() && mExpressionRecalculationRequired;
//    }
//    
//    virtual void setExpressionRecalculationRequired(bool val) {
//         mExpressionRecalculationRequired = val;
//    }
//    
//    int getMinWidth() {
//        return mMinWidth;
//    }
//    
//    int getMinHeight() {
//        return mMinHeight;
//    }
//    
//    int getMaxWidth() {
//        return mMaxWidth;
//    }
//    
//    int getMaxHeight() {
//        return mMaxHeight;
//    }
//    
//    virtual void setX(int x) {
//        if (mX != x) setExpressionRecalculationRequired(true);
//        mX = x;
//    }
//    
//    virtual void setY(int y) {
//        if (mY != y) setExpressionRecalculationRequired(true);
//        mY = y;
//    }
//    
//    virtual void setWidth(int width) {
//        if (mWidth != width) {
//            setExpressionRecalculationRequired(true);
//            setTitle(getTitle()); // force title text recalculation 
//        }
//        mWidth = width;
//    }
//    
//    virtual void setHeight(int height) {
//        if (mHeight != height) {
//            setExpressionRecalculationRequired(true);
//            setTitle(getTitle()); // force title text recalculation
//        }
//        mHeight = height;
//    }
//    
//    virtual void setWidgetPosition(float x, float y, bool enableDockingLogic) {
//        setX(x);
//        setY(y);
//    }
//
//    virtual uiVizElm::vizRect setSize(int width, int height) {
//        int clampWidth = width;
//        clampWidth = std::max((float)clampWidth, (float)getMinWidth());
//        clampWidth = std::min((float)clampWidth, min((float)getMaxWidth(), (float)(deScale(ofGetWindowWidth()) - getScreenPadding() - getX())));
//        setWidth(clampWidth);
//        
//        int clampHeight = height;
//        clampHeight = std::max((float)clampHeight, (float)getMinHeight());
//        clampHeight = std::min((float)clampHeight, min((float)getMaxHeight(), (float)(deScale(ofGetWindowHeight()) - getScreenPadding() - getY())));
//        setHeight(clampHeight);
//        
//        setScrollOffsetY(getScrollOffsetY(), true);
//        setScrollOffsetX(getScrollOffsetX(), true);
//        return uiVizElm::vizRect(getX(), getY(), clampWidth, clampHeight);
//    }
//
//    virtual bool setWidgetSize_ShouldPrevent(int width, int height, bool enableDockingLogic) {
//        return false;
//    }
//
//    virtual void setWidgetSize(int width, int height, bool enableDockingLogic) {
//        if (getLockAspectRatio()) {
//            height = width * getAspectRatio();
//        }
//
//        if (getWidth() != width || getHeight() != height) {
//            int beforeSetWidth = getWidth();
//            int beforeSetHeight = getHeight();  
//
//            if (setWidgetSize_ShouldPrevent(width, height, enableDockingLogic)) {
//                return;
//            }
//
//            uiVizElm::vizRect resultRect = setSize(width, height);
//
//            if(resultRect.width != beforeSetWidth || resultRect.height != beforeSetHeight) {
//                ofResizeEventArgs args(resultRect.width, resultRect.height);
//                ofNotifyEvent(widgetResized, args);
//                setNeedsUpdate(true);
//            }
//        }
//    }
//
//    void setX_Expr(string expr) {
//        mX_Expr = (expr == "" ? "" : ofToUpper(expr));
//    }
//    
//    void setY_Expr(string expr) {
//        mY_Expr = (expr == "" ? "" : ofToUpper(expr));
//    }
//    
//    void setWidth_Expr(string expr) {
//        mWidth_Expr = (expr == "" ? "" : ofToUpper(expr));
//    }
//    
//    void setHeight_Expr(string expr) {
//        mHeight_Expr = (expr == "" ? "" : ofToUpper(expr));
//    }
//
//    void setIgnoreExpr_Layout(bool val) {
//        mIgnoreExpr_Layout = val;
//    }   
//
//    bool getIgnoreExpr_Layout() {
//        return mIgnoreExpr_Layout;
//    }         
//    
//    void clearWidgetLayoutExpressions() {
//        setX_Expr("");
//        setY_Expr("");
//        setWidth_Expr("");
//        setHeight_Expr("");
//    }
//    
//    void setMinWidth(int minWidth) {
//        mMinWidth = minWidth;
//    }
//    
//    void setMinHeight(int minHeight) {
//        mMinHeight = minHeight;
//    }
//    
//    void setMaxWidth(int maxWidth) {
//        mMaxWidth = maxWidth;
//    }
//    
//    void setMaxHeight(int maxHeight) {
//        mMaxHeight = maxHeight;
//    }
//    
//    bool getIsShadow() {
//        return mIsShadow;
//    }
//    
//    void setIsShadow(bool value) {
//        mIsShadow = value;
//    }
//
//    bool getIsRoundedRectangle() {
//        return mIsRoundedRectangle;
//    }
//    
//    void setIsRoundedRectangle(bool value) {
//        mIsRoundedRectangle = value;
//    }
//
//    float getAspectRatio() {
//        return mAspectRatio;
//    }
//    
//    void setAspectRatio(float val) {
//        mAspectRatio = val;
//    }
//    
//    bool getLockAspectRatio() {
//        return mLockAspectRatio;
//    }
//    
//    void setLockAspectRatio(bool val) {
//        mLockAspectRatio = val;
//    }
//    
//    virtual bool getIsVisible() {
//        // A widget should never be visible if it's parent is not!
//        uiVizWidgetBase* w = parent();
//        while(w) {
//            if (!w->getIsVisible()) return false;
//            w = w->parent();
//        }
//
//        return mIsVisible;
//    }
//    
//    virtual void setIsVisible(bool value) {
//        bool visibilityChanged = (getIsVisible() != value);
//        mIsVisible = value;
//        mShouldCloseThisWidget = false;
//        if (getShowingAsPopout()) {
//            getViz()->setIsPopoutVisible(getWidgetId(), value);
//            if (!value) {
//                // Restore the previously active widget
//                getViz()->setActiveWidgetId(getViz()->getNextInLineForFocusWidgetId());      
//            }
//        }
//        
//        if(visibilityChanged) onWidgetVisibilityChanged(value);     
//    }
//    
//    uiVizCoord::vizBounds getContentBoundsScaled() {
//        return mContentBoundsScaled;
//    }
//    
//    void clearContentBoundsScaled() {
//        mContentBoundsScaled = uiVizCoord::vizBounds(0, 0, 0, 0);
//    }
//    
//    void appendContentBoundsScaled(uiVizCoord::vizBounds boundsVal) {
//        if (boundsVal.x > mContentBoundsScaled.x)  mContentBoundsScaled.x = boundsVal.x;
//        if (boundsVal.y > mContentBoundsScaled.y)  mContentBoundsScaled.y = boundsVal.y;
//        mContentBoundsScaled.width += boundsVal.width;
//        mContentBoundsScaled.height += boundsVal.height;
//    }
//    
//    void setContentBoundsScaled(uiVizCoord::vizBounds boundsVal) {
//        mContentBoundsScaled.x = boundsVal.x;
//        mContentBoundsScaled.y = boundsVal.y;
//        mContentBoundsScaled.width = boundsVal.width;
//        mContentBoundsScaled.height = boundsVal.height;
//    }
//
//    void resetTimer() {
//        mElapsedTimerMillis = 0;
//    }
//    
//    uint64_t getTimerMillis() {
//        if (mElapsedTimerMillis == 0) mElapsedTimerMillis = ofGetSystemTimeMillis();
//        return ofGetSystemTimeMillis() - mElapsedTimerMillis;
//    }
//
//    int getScrollingStartedIntervalX() {
//        return ofGetSystemTimeMillis() - mScrollingStartedMS_X;
//    }
//    
//    bool getIsScrollingXMouseDown() {
//        return mIsScrollingXMouseDown;
//    }
//    
//    void setIsScrollingXMouseDown(bool val) {
//        mIsScrollingXMouseDown = val;
//    }
//    
//    bool getIsScrollingYMouseDown() {
//        return mIsScrollingYMouseDown;
//    }
//    
//    void setIsScrollingYMouseDown(bool val) {
//        mIsScrollingYMouseDown = val;
//    }
//    
//    bool getIsScrollingX() {
//        if (getIsScrollingXMouseDown()) return true;
//        if (mScrollingStartedMS_X == 0 || getScrollingStartedIntervalX() > 1200) {
//            mScrollingStartedMS_X = 0;
//            return false;
//        } else {
//            return true;
//        }
//    }
//    
//    void setIsScrollingX() {
//        mScrollingStartedMS_X = ofGetSystemTimeMillis();
//    }
//    
//    int getScrollingStartedIntervalY() {
//        return ofGetSystemTimeMillis() - mScrollingStartedMS_Y;
//    }
//    
//    bool getIsScrollingY() {
//        if (getIsScrollingYMouseDown()) return true;
//        if (mScrollingStartedMS_Y == 0 || getScrollingStartedIntervalY() > 1200) {
//            mScrollingStartedMS_Y = 0;
//            return false;
//        } else {
//            return true;
//        }
//    }
//    
//    void setIsScrollingY() {
//        mScrollingStartedMS_Y = ofGetSystemTimeMillis();
//    }
//    
//    float getScrollOffsetX() {
//        return mScrollOffsetX;
//    }
//    
//    float getScrollOffsetY() {
//        return mScrollOffsetY;
//    }
//    
//    virtual void setScrollOffsetX(float val, bool absolute) {
//        
//        if (val > 0 && getScrollOffsetX() >= 0) {
//            // we've reached the left of the content
//            mScrollOffsetX = 0.0f;
//            return;
//        }
//
//        if (getUsableWidth() >= deScale(getContentBoundsScaled().width) && mScrollOffsetX != 0) {
//            // we've reached the right of the content
//            mScrollOffsetX = 0.0f;
//            setWidgetNeedsUpdate(true);
//            return;
//        }          
//        
//        if (val < 0 && getScrollOffsetX() <= (getUsableWidth() - deScale(getContentBoundsScaled().width))) {
//            // we've reached the end of the content
//            mScrollOffsetX = getUsableWidth() - deScale(getContentBoundsScaled().width);
//            return;
//        }
//        
//        mScrollOffsetX = absolute ? val : mScrollOffsetX + val;
//        
//        if (absolute && getScrollOffsetX() != val) {
//            setWidgetNeedsUpdate(true);
//        }
//        
//    }
//    
//    virtual void setScrollOffsetY(float val, bool absolute) {
//        
//        if (val > 0 && getScrollOffsetY() >= 0) {
//            // we've reached the top of the content
//            mScrollOffsetY = 0.0f;
//            return;
//        }
//
//        if (getUsableHeight() >= deScale(getContentBoundsScaled().height) && mScrollOffsetY != 0) {
//            // we've reached the top of the content
//            mScrollOffsetY = 0.0f;
//            setWidgetNeedsUpdate(true);
//            return;
//        }        
//        
//        if (val < 0 && getScrollOffsetY() <= (getUsableHeight() - deScale(getContentBoundsScaled().height))) {
//            // we've reached the end of the content
//            mScrollOffsetY = getUsableHeight() - deScale(getContentBoundsScaled().height);
//            return;
//        }
//        mScrollOffsetY = absolute ? val : mScrollOffsetY + val;
//        
//        if (absolute && getScrollOffsetY() != val) {
//            setWidgetNeedsUpdate(true);
//        }
//        
//    }
//
//    float getScrollScaleX() {
//        return mScrollScaleX;
//    }
//
//    void setScrollScaleX(float val) {
//        mScrollScaleX = val;
//    }  
//
//    float getScrollScaleY() {
//        return mScrollScaleY;
//    }
//
//    void setScrollScaleY(float val) {
//        mScrollScaleY = val;
//    }     
//    
//    int getEnableScrollYPositive() {
//        return mEnableScrollYPositive;
//    }
//    
//    void setEnableScrollYPositive(bool val) {
//        mEnableScrollYPositive = val;
//    }
//    
//    int getEnableScrollYNegative() {
//        return mEnableScrollYNegative;
//    }
//    
//    void setEnableScrollYNegative(bool val) {
//        mEnableScrollYNegative = val;
//    }
//
//    int getEnableScrollXPositive() {
//        return mEnableScrollXPositive;
//    }
//    
//    void setEnableScrollXPositive(bool val) {
//        mEnableScrollXPositive = val;
//    }
//    
//    int getEnableScrollXNegative() {
//        return mEnableScrollXNegative;
//    }
//    
//    void setEnableScrollXNegative(bool val) {
//        mEnableScrollXNegative = val;
//    }
//
//    void setEnableScroll(bool val) {
//        setEnableScrollXPositive(val);
//        setEnableScrollXNegative(val);
//        setEnableScrollYPositive(val);
//        setEnableScrollYNegative(val);    
//    }
//    
//    void setScrollAction(ScrollAction val) {
//        mScrollAction = val;
//    }
//    
//    ScrollAction getScrollAction() {
//        return mScrollAction;
//    }
//
//    void setCloseAction(CloseAction val) {
//        mCloseAction = val;
//    }
//    
//    CloseAction getCloseAction() {
//        return mCloseAction;
//    }    
//
//    bool getIsDraggable() {
//        return mIsDraggable;
//    }
//    
//    void setIsDraggable(bool value) {
//        mIsDraggable = value;
//        mTempIsDraggable = value;
//    }
//
//    bool getIsResizable() {
//        return mIsResizable;
//    }
//    
//    void setIsResizable(bool value) {
//        mIsResizable = value;
//        mTempIsResizable = value;
//    }
//    
//    bool getIsAutoUpdateWhenActive() {
//        return mIsAutoUpdateWhenActive;
//    }
//    
//    bool getRespondedToFirstMousePressedEvent() {
//        return mRespondedToFirstMousePressedEvent;
//    }
//    
//    void setRespondedToFirstMousePressedEvent(bool value) {
//        mRespondedToFirstMousePressedEvent = value;
//    }
//    
//    bool getRespondedToFirstMouseReleasedEvent() {
//        return mRespondedToFirstMouseReleasedEvent;
//    }
//    
//    void setRespondedToFirstMouseReleasedEvent(bool value) {
//        mRespondedToFirstMouseReleasedEvent = value;
//    }
//
//    bool getMousePressWasRegisteredWhenCheckingForReleased() {
//        return mMousePressWasRegisteredWhenCheckingForReleased;
//    }
//    
//    void setMousePressWasRegisteredWhenCheckingForReleased(bool value) {
//        mMousePressWasRegisteredWhenCheckingForReleased = value;
//    }
//
//    void setIsAutoUpdateWhenActive(bool value) {
//        mIsAutoUpdateWhenActive = value;
//    }
//
//    bool getIsDragging() {
//        return mIsDragging;
//    }
//    
//    void setIsDragging(bool value) {
//        mIsDragging = value;
//        if(mIsDragging) {
//            mContentDragIconFbo = saveWidgetContentsToFbo();
//        } else {
//            mContentDragIconFbo.destroy();
//        }
//    }
//
//    bool getIsResizing() {
//        return mIsResizing;
//    }
//    
//    void setIsResizing(bool value) {
//        mIsResizing = value;
//    }
//    
//    virtual bool isTransitioningAlpha() {
//        return false;
//    }
//    
//    uiVizCoord::vizPoint getLastMouseClickCoords() {
//        return mLastMouseClickCoords;
//    }
//    
//    void setLastMouseClickCoords(uiVizCoord::vizPoint p) {
//        mLastMouseClickCoords = p;
//    }
//    
//    bool matchesWidgetId(string widgetId) {
//        return ofToLower(widgetId) == ofToLower(getWidgetId());
//    }    
//
//    bool matchesWidget(uiVizWidgetBase* w) {
//        if (!w) return false;
//        return matchesWidgetId(w->getWidgetId());
//    }
//
//    bool matchesWidget(vector<uiVizWidgetBase*> w) {
//        if (w.size() == 0) return false;
//        bool found = false;
//        for(uiVizWidgetBase* wb:w) {
//
//            if (wb && matchesWidgetId(wb->getWidgetId())) {
//                return true;
//            }
//        }
//        return false;
//    }      
//
//    bool matchesParentWidgetId(string widgetId) {
//        if (parent()) {
//            return ofToLower(widgetId) == ofToLower(parent()->getWidgetId());
//        }
//        return false;
//    }  
//
//    bool matchesParentWidget(uiVizWidgetBase* w) {
//        if (!w) return false;
//        return matchesParentWidgetId(w->getWidgetId());
//    }
//
//    bool matchesWidgetOrParent(uiVizWidgetBase* w) {
//        if (matchesWidget(w)) return true;
//        if (matchesParentWidget(w)) return true;
//        return false;
//    }     
//
//    bool matchesWidgetOrChildOf(uiVizWidgetBase* w) {
//        if (matchesWidget(w)) return true;
//        if (parent() && w->getWidgetId() == parent()->getWidgetId()) return true;
//        return false;
//    }  
//
//    bool matchesWidgetOrDescendantOf(uiVizWidgetBase* w) {
//        // TODO : implement
//        return false;
//    }      
//
//
//    //! The widget Id of the widget responsible for maintaining this widget lifecycle. If empty, the widgetManager is responsible  
//   string getOwnerWidgetId() {
//        return mOwnerWidgetId;
//    }    
//    
//   void setOwnerWidgetId(string val) {
//        mOwnerWidgetId = val;
//    } 
//
//    string getActiveWidgetId() {
//        return getViz()->getActiveWidgetId();
//    }
//    
//    bool getIsActiveWidget() {
//        return getViz()->isActiveWidgetId(getWidgetId());
//    }
//    
//    bool getIsChildOfModal() {
//        return getIsChildOfModal(this); 
//    }    
//
//    void setActiveWidget() {
//        if (!getIsVisible()) return;
//
//        // A widget should never be become active if it's parent is not visible!
//        uiVizWidgetBase* w = parent();
//        while(w) {
//            if (!w->getIsVisible()) return;
//            w = w->parent();
//        }
//
//        if(getViz()->getModalWidgetId() != "" && !getViz()->getIsPopoutVisible()) { // Only enforce modal logic if Context menu not visible! 
//            if(!getIsChildOfModal()) return;
//        }
//        getViz()->setActiveWidgetId(getWidgetId());
//
//        uiVizWidgetBase* r = root();
//        if (r) {
//            getViz()->setTopmostActiveRootWidgetId(r->getWidgetId());
//        }
//        
//    }
//    
//    void clearActiveWidgetId() {
//        /* 
//            If getting unexpected EXC_BAD_ACCESS errors make sure to check that ALL widgets are callling 
//            ofRemoveListener for ALL corresponding ofAddListener in ther destructors!
//        */
//
//        getViz()->clearActiveWidgetId();
//    }
//
//    bool getIsModalWidget() {
//        return getViz()->isModalWidgetId(getWidgetId());
//    }
//
//    void clearIfModal() {
//        if(getIsModalWidget()) {
//            clearModalWidgetId();
//        }
//    }
//    
//    void setModalWidget() {
//        setActiveWidget();
//        getViz()->setModalWidgetId(getWidgetId());
//    }
//    
//    void clearModalWidgetId() {
//        clearActiveWidgetId();
//        getViz()->clearModalWidgetId();
//    }
//    
//    bool getIsRootWidget() {
//        return parent() == nullptr;
//    }
//
//    bool getIsNextInLineForFocus() {
//        return mIsNextInLineForFocus;
//    }
//    
//    void setIsNextInLineForFocus(bool val) {
//        mIsNextInLineForFocus = val;
//        if (val) getViz()->setNextInLineForFocusWidgetId(getWidgetId());
//    }
//
//    //! Override if extending uiVizWidgetBase for returning the index of a child element
//    virtual int getWidgetElementIndex(string persistentId) {
//        return 0;
//    } 
//
//    //! Override if extending uiVizWidgetBase for returning the count of child elements
//    virtual int getWidgetElementSize() {
//        return 0;
//    }           
//    
//    string getTargetDropWidgetId() {
//        return getViz()->getTargetDropWidgetId();
//    }
//    
//    void setTargetDropWidgetId() {
//        getViz()->setTargetDropWidgetId(getWidgetId());
//    }
//    
//    void clearTargetDropWidgetId() {
//        getViz()->clearTargetDropWidgetId();
//    }
//    
//    int getUserExperience() {
//        return getViz()->getUserExperience();
//    }
//
//    float scale(float val) {
//        return getViz()->scale(val);
//    }
//    
//    float deScale(float val) {
//        return getViz()->deScale(val);
//    }
//
//	float scaleAnimation(string animationName, float currVal, float targetVal, float secondsDuration) {
//		return getViz()->scaleAnimation(getWidgetId(), getPersistentId() + "_" + animationName, currVal, targetVal, secondsDuration);
//	}
//
//	float scaleAnimationForUI(string animationName, float currVal, float targetVal, float secondsDuration) {
//		return getViz()->scaleAnimationForUI(getWidgetId(), getPersistentId() + "_" + animationName, currVal, targetVal, secondsDuration);
//	}
//
//    void removeAnimation(string animationName) {
//            getViz()->removeAnimation(getPersistentId() + "_" + animationName);
//    }     
//    
//    int getNonScaledPadding() {
//        return getViz()->getNonScaledPadding();
//    }
//    
//    int getScaledPadding() {
//        return getViz()->getScaledPadding();
//    }
//
//	bool isDraggingContent() {
//		return  /* getScrollAction() != ScrollAction::SCROLL && */!getIsScrollingXMouseDown() && !getIsScrollingYMouseDown() && mIsDraggingContent;
//
//        //todo --> convert !getIsScrollingXMouseDown() && !getIsScrollingYMouseDown() to TOUCH 
//	}
//
//    bool getIsUnhoverLoseFocus() {
//        return mIsUnhoverLoseFocus;
//    }
//    
//    void setIsUnhoverLoseFocus(bool val) {
//        mIsUnhoverLoseFocus = val;
//    }
//
//    bool getShouldCloseIfOtherWidgetClicked() {
//        if(getIsModalWidget()) return false;
//        return mShouldCloseIfOtherWidgetClicked;
//    }
//    
//    void setShouldCloseIfOtherWidgetClicked(bool val) {
//        mShouldCloseIfOtherWidgetClicked = val;
//    }
//
//    bool getUseFbo() {
//        return mUseFbo;
//    }
//    
//    void setUseFbo(bool value) {
//        mUseFbo = value;
//    }
//
//    virtual uiVizWidgetBase* parent() {
//        return nullptr;
//    }
//
//    virtual uiVizWidgetBase* root() {
//        uiVizWidgetBase* r = this;
//        uiVizWidgetBase* w = parent();
//        while(w) {
//            r = w;
//            w = w->parent();            
//        }   
//        return r; 
//    }
//
//    string getPesistentIdPath() {
//        string path = getPersistentId();
//        uiVizWidgetBase* w = parent();
//        while(w) {
//            path = w->getPersistentId() + "->" + path;
//            w = w->parent();
//        }
//        return path;
//    }    
//
//    virtual ofFbo saveWidgetContentsToFbo() { 
//        // Do something in descendant class
//    }
//
//    virtual ofFbo getContentDragIconFbo() {
//        return mContentDragIconFbo;
//    }     
//
//    virtual void drawContentDragIcon() {
//        if(getContentDragIconFbo().isAllocated()) {
//
//            float ratio = (float)getWidth()/(float)getHeight();
//            if (ratio == 0) ratio = 1;
//            int targetWidth = 40;
//            int targetHeight = 40;
//
//            if (targetWidth > targetHeight) {
//                targetWidth = (float)targetWidth/ratio;
//            } else {
//                targetHeight = (float)targetHeight/ratio;
//            }
//            
//            getContentDragIconFbo().draw(ofGetMouseX(), ofGetMouseY(), scale(targetWidth), scale(targetHeight));
//        } else {
//            // this is a placeholder "catch all" rectangle to indicate contnet being DRAGGED
//            ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), scale(30), scale(40));
//        }
//
//    }
//
//    virtual void drawPotentiallyDropTargetIndication() {
//        // this is a placeholder "catch all" rectangle to indicate contnet (potentially) being DROPPED
//
//        ofColor c = (getTheme().IsDark ? ofColor(255, 255, 255, 100) : ofColor(0, 0, 0, 100));
//
//        uiVizElm vizElm_POTENTIAL_DROP_INDICATOR;
//        getIsRoundedRectangle() ? vizElm_POTENTIAL_DROP_INDICATOR.setRectRounded(scale(getX()), scale(getY()), scale(getWidth()), scale(getHeight()), getScaledPadding(), c) :
//            vizElm_POTENTIAL_DROP_INDICATOR.setRectangle(scale(getX()), scale(getY()), scale(getWidth()), scale(getHeight()), c);
//
//        //vizElm_POTENTIAL_DROP_INDICATOR.setFilled(false);
//
//        vizElm_POTENTIAL_DROP_INDICATOR.draw();
//    }    
//    
//    virtual bool getIsMousePressedOverWidget(bool respondConstantly) {
//        if (!getIsActiveWidget()) return false;
//        
//        if (!getIsScrollingY() && !getIsScrollingX() && !getIsDragging() && !getIsResizing() && ofGetMousePressed() && (!getRespondedToFirstMousePressedEvent() || respondConstantly)) {
//            setRespondedToFirstMousePressedEvent(true);
//            return true;
//        }
//        return false;
//    }
//    
//    bool ofGetTouchDownOrMousePressed() {
//        return ofGetMousePressed(); // || TODO: istoucheddown 
//    }
//    
//    virtual bool getIsMousePressedAndReleasedOverWidget(bool includeWidgetChromeElements) {
//        if (!getIsActiveWidget()) return false;
//        
//        if (!getIsDragging() && !getIsResizing() && !ofGetMousePressed() && (getMousePressWasRegisteredWhenCheckingForReleased() && !getRespondedToFirstMouseReleasedEvent())) {
//            
//            setRespondedToFirstMouseReleasedEvent(true);
//            setMousePressWasRegisteredWhenCheckingForReleased(false);
//            
//            int mX = deScale(ofGetMouseX());
//            int mY = deScale(ofGetMouseY());
//            uiVizCoord::vizPoint p = getLastMouseClickCoords();
//            
//            if (mX > p.x + mMinPixelsMovedToRegisterDrag || mX < p.x  - mMinPixelsMovedToRegisterDrag ||
//                mY > p.y + mMinPixelsMovedToRegisterDrag || mY < p.y  - mMinPixelsMovedToRegisterDrag) {
//                // The mouse moved too much to register a pressed and released event
//                return false;
//            } else {
//                return true;
//            }
//        }
//        
//        return false;
//    }
//    
//    virtual bool isWidgetHovered() {
//        
//        //if (!getIsVisible()) return false;
//
//        int mX = deScale(ofGetMouseX());
//        int mY = deScale(ofGetMouseY());
//        
//        return (mX > getX() && mX < getX() + getWidth() && mY > getY() && mY < getY() + getHeight());
//    }
//    
//	virtual void onWidgetAfterAllWidgetsLoaded(std::vector<std::reference_wrapper<uiVizWidget>> widgets) {
//		// Fires when WidgetManager has loaded all widgets
//
//	}
//
//    virtual void onCoreWidgetScaleChanged(float& scale) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//		onWidgetScaleChanged(scale);
//    }
//
//	virtual void onWidgetScaleChanged(float scale) {
//		// Implement any behaviour in derrived class which should handle scale change...
//	}
// 
//     //! Implement any behaviour in derrived class which should handle when this widget is added to a parent.
//	virtual void onWidgetAddedAsChild(uiVizWidgetEventArgs args) {
//	}
//    
//
//    virtual void onCoreWidgetWindowResized() {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//		onWidgetWindowResized();
//    }
//
//	virtual void onWidgetWindowResized() {
//		// Implement any behaviour in derrived class which should handle window resize...
//	}
//
//	virtual void onWidgetOwnedWidgetClosed(uiVizWidgetBase* closedWidget) {
//		// Implement any behaviour in derrived class which should handle when owned widget is closed...
//	}    
//    
//    virtual void onCoreWidgetWindowResized(ofResizeEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//		onWidgetWindowResized(e);
//    }
//
//    virtual void onCoreWidgetResized(ofResizeEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//        eventTransmit(getPersistentId(), WIDGET_EVENT::RESIZED, "<event width=\"" + ofToString(e.width) + "\" height=\"" + ofToString(e.height) + "\"></event>", *this);        
//		onWidgetResized(e.width, e.height);
//    }
//
//
//	virtual void onWidgetWindowResized(ofResizeEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle window resize...
//	}
//    
//    virtual void onCoreWidgetMouseMoved(ofMouseEventArgs &e) {
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...
//        if (getIsActiveWidget() && getIsEnabled()) {
//            if (getExternalDrop().getIsDragging()) {
//                getExternalDrop().handleExternalDragAndDropMotionNotify();
//                if (!ofGetMousePressed()) getExternalDrop().handleExternalDragAndDropButtonReleaseEvent();
//            }
//        }         
//    }
//    
//    void handleMousePressed(const std::function<void(ofMouseEventArgs &)> &func) {
//        m_onCoreWidgetMousePressedFunction = func;
//    }   
//
//    virtual void onCoreWidgetMousePressed(ofMouseEventArgs &e) {
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...
//        if (getIsActiveWidget()) {
//            setRespondedToFirstMouseReleasedEvent(false);
//            setMousePressWasRegisteredWhenCheckingForReleased(true);
//            setLastMouseClickCoords(uiVizCoord::vizPoint(deScale(ofGetMouseX()), deScale(ofGetMouseY())));
//            
//            if (!isDraggingContent()) {
//                mPotentiallyStartedDraggingStartX = deScale(ofGetMouseX());
//                mPotentiallyStartedDraggingStartY = deScale(ofGetMouseY());
//                // cout << "registered potential drag start position: " << mPotentiallyStartedDraggingStartX << "," << mPotentiallyStartedDraggingStartY << "\n";
//            }
//            
//            if(getIsEnabled()) {
//                onWidgetMousePressed(e);
//                m_onCoreWidgetMousePressedFunction(e);
//            } //test this
//        }
//    }
//    
//    virtual void onWidgetMousePressed(ofMouseEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse released...
//    }
//
//    void handleMouseReleased(const std::function<void(ofMouseEventArgs &)> &func) {
//        m_onCoreWidgetMouseReleasedFunction = func;
//    }  
//
//    virtual void onCoreWidgetMouseReleased(ofMouseEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//        setRespondedToFirstMousePressedEvent(false);
//        
//        if (mDraggingFileIn) {
//            mDraggingFileIn = false;
//        }
//        
//		if (isDraggingContent()) {
//            // Restore values back what they were before drag operation
//            setIsDraggable(mTempIsDraggable);
//            setIsResizable(mTempIsResizable);    
//            getViz()->setIsAnyWidgetDraggingOrResizing(false);
//            setIsDragging(false);
//
//            if (!mIsWindowHovered) {
//                cout << "Sending the following data EXTERNALLY:\n" << getDragData();         
//                onWidgetMouseContentDragReleased_Externally(e, getDragData());
//            }       
//
//			onWidgetMouseContentDragReleased(e, getDragData());
//
//            if(getIsEnabled()) {
//                if (getTargetDropWidgetId() != getWidgetId()) {
//                    uiVizWidgetBase* widgetTarget = getTargetDropWidget();
//                    if (widgetTarget != nullptr) {
//                        widgetTarget->eventTransmit(getPersistentId(), WIDGET_EVENT::RECEIVE_DRAG_AND_DROP_DATA, "<event>" + getDragData() + "</event>", *this, widgetTarget); // uiVizShared::encodeForXML(
//                    }
//                    
//                } else {
//                    eventTransmit(getPersistentId(), WIDGET_EVENT::RECEIVE_DRAG_AND_DROP_DATA, "<event>" + getDragData() + "</event>", *this);
//                }
//            }
//
//            
//            mIsDraggingContent = false;
//		}    
//        
//        setIsScrollingXMouseDown(false);
//        setIsScrollingYMouseDown(false);
//
//        if (getExternalDrop().getIsDragging()) {
//            getExternalDrop().handleExternalDragAndDropButtonReleaseEvent();       
//        }       
//
//		if (getIsActiveWidget()) {
//            if(getIsEnabled()) {
//                onWidgetMouseReleased(e);
//                m_onCoreWidgetMouseReleasedFunction(e);                
//            }
//		}
//    }
//
//	virtual void onWidgetMouseReleased(ofMouseEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle mouse released...
//	}
//    
//    virtual void onCoreWidgetTouchDown(ofTouchEventArgs &e) {
//
//        
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...
//        
//        if (getIsActiveWidget()) {
//            if (e.numTouches >= 2) {
//                ofMouseEventArgs args(ofMouseEventArgs::Type::Pressed, e.x, e.y, OF_MOUSE_BUTTON_RIGHT, 0);
//                onCoreWidgetMousePressed(args);
//                
//            }
//        }
//
//    }
//    
//    virtual void onWidgetTouchDown(ofTouchEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse released...
//    }
//    
//    virtual void onCoreWidgetTouchUp(ofTouchEventArgs &e) {
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...
//
//        if (getIsActiveWidget()) {
//            ofMouseEventArgs args(ofMouseEventArgs::Type::Released, e.x, e.y, OF_MOUSE_BUTTON_LEFT, 0);
//            onCoreWidgetMouseReleased(args);
//            onWidgetTouchUp(e);
//            
//            setNeedsUpdate(true);
//            setWidgetNeedsUpdate(true);
//        }
//    }
//    
//    virtual void onWidgetTouchUp(ofTouchEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse released...
//    }
//    
//	virtual void onWidgetMouseContentDragReleased(ofMouseEventArgs &e, string dragData) {
//		// Implement any behaviour in derrived class which should handle mouse released...
//	}
//
//	virtual void onWidgetMouseContentDragReleased_Externally(ofMouseEventArgs &e, string dragData) {
//		// Implement any behaviour in derrived class which should handle mouse released (outside of the application window)...
//	}    
//    
//    virtual void onWidgetResized(int width, int height) {
//        // Hook for resized event
//    }
//
//    virtual void onWidgetResizingByUserEnded(int width, int height) {
//        // Hook for resized event (by user)
//    }    
//    
//    // Draws scrollbar and scrolls to specified amount
//    void scrollX(int val) {
//        ofMouseEventArgs args(ofMouseEventArgs::Type::Scrolled, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);
//        args.scrollX = val;
//        onCoreWidgetMouseScrolled(args);
//    }
//    
//    // Draws scrollbar and scrolls to specified amount
//    void scrollY(int val) {
//        ofMouseEventArgs args(ofMouseEventArgs::Type::Scrolled, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);
//        args.scrollY = val;
//        onCoreWidgetMouseScrolled(args);
//    }
//
//    // Draws scrollbar and scrolls to specified amount
//    void scroll(int x, int y) {
//        ofMouseEventArgs args(ofMouseEventArgs::Type::Scrolled, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);
//        args.scrollX = x;        
//        args.scrollY = y;
//        onCoreWidgetMouseScrolled(args);
//    }    
//
//    void scrollX_End() {
//        if (deScale(getContentBoundsScaled().width) <= getWidth()) {
//            setScrollOffsetX(0, true);
//        } else {
//            setScrollOffsetX(getUsableWidth()-deScale(getContentBoundsScaled().width), true);
//        }
//        setNeedsUpdate(true);
//    }
//    
//    void scrollY_End() {
//        if (deScale(getContentBoundsScaled().height) <= getHeight()) {
//            setScrollOffsetY(0, true);
//        } else {
//            setScrollOffsetY(getUsableHeight()-deScale(getContentBoundsScaled().height), true);
//        }
//        setNeedsUpdate(true);        
//    }    
//    
//    virtual void onCoreWidgetMouseScrolled(ofMouseEventArgs &e) {
//        if (getIsActiveWidget()) {
//            switch(getScrollAction()) {
//                case ScrollAction::ZOOM:
//                    if (!getIsResizable()) return;
//                    setSize(getWidth() + e.scrollY*getScrollScaleX(), getHeight() + e.scrollY*getScrollScaleY());
//                    onWidgetMouseScrolled(e);
//                    break;
//                    
//                case ScrollAction::SCROLL: {
//                        // Basic scroll functionality for widgets!
//                        int origScrollOffsetX = getScrollOffsetX();
//                        int origScrollOffsetY = getScrollOffsetY();
//                    
//                        if (getUsableWidth() < deScale(getContentBoundsScaled().width)) {
//                            if (e.scrollX > 0) {
//                                // content moving rightwards
//                                if (getEnableScrollXPositive()) setScrollOffsetX(e.scrollX*getScrollScaleX(), false);
//                            } else {
//                                if (getEnableScrollXNegative()) setScrollOffsetX(e.scrollX*getScrollScaleX(), false);
//                            }                            
//                        }                    
//
//                        if (getUsableHeight() < deScale(getContentBoundsScaled().height)) {
//                            if (e.scrollY > 0) {
//                                // content moving downwards
//                                if (getEnableScrollYPositive()) setScrollOffsetY(e.scrollY*getScrollScaleY(), false);
//                            } else {
//                                if (getEnableScrollYNegative()) setScrollOffsetY(e.scrollY*getScrollScaleY(), false);
//                            }                            
//                        }
//                    
//                        if (origScrollOffsetX != getScrollOffsetX() || origScrollOffsetY != getScrollOffsetY()) {
//                            
//                            if (origScrollOffsetX != getScrollOffsetX()) setIsScrollingX();
//                            if (origScrollOffsetY != getScrollOffsetY()) setIsScrollingY();
//                            
//                            setNeedsUpdate(true);
//                            onWidgetMouseScrolled(e);
//                        }
//                    }
//                    break;
//                    
//                case ScrollAction::BASIC:
//                    onWidgetMouseScrolled(e);
//                    break;
//            }
//        }
//    }
//    
//    void coreDrawWidgetScrollbars(ofColor scrollbarColor) {
//        if ((getEnableScrollXPositive() || getEnableScrollXNegative()) && deScale(getContentBoundsScaled().width) > getUsableWidth()) {
//            float scrollBarXPerc = std::min((float)1, (float)(getUsableWidth() / (float)deScale(getContentBoundsScaled().width)));
//            
//            vizElm_WIDGET_SCROLLBAR_X.setRectRounded(
//                                                     std::max((float)scale(getUsableX(false)), (float)scale(getUsableX(false) + getScrollOffsetX() * -1 * scrollBarXPerc)),
//                                                     scale(getUsableY(false) + getUsableHeight()) - getScaledPadding() * 2,
//                                                     scale(scrollBarXPerc * getUsableWidth()),
//                                                     scale(10),
//                                                     scale(5),
//                                                     ofColor(scrollbarColor));
//             
//            int scrollX = getPotentiallyStartedDraggingStartX() - (int)deScale(ofGetMouseX());
//            bool isScrollbarHovered = !isDraggingContent() && vizElm_WIDGET_SCROLLBAR_X.isHovered_Rect();
//            bool isDraggingToScroll = false;// TODO: ADD 2 FINGER SWIPE TO SCROLLE HERE OLD CODE: getIsMousePressedOverWidget(true) && scrollX != 0;
//            
//            if (getIsScrollingX() || isScrollbarHovered || isDraggingToScroll) {
//                vizElm_WIDGET_SCROLLBAR_X.draw();
//                if (isScrollbarHovered) setIsScrollingX();
//                
//                if ((!getIsScrollingXMouseDown() && ofGetMousePressed() && isScrollbarHovered) || isDraggingToScroll) {
//                    setIsScrollingXMouseDown(true);
//                }
//                
//                if (getIsScrollingXMouseDown() && scrollX != 0) {
//                    ofMouseEventArgs args(ofMouseEventArgs::Type::Scrolled, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);
//                    args.scrollX = scrollX;
//                    onCoreWidgetMouseScrolled(args);
//                    setPotentiallyStartedDraggingStartX((int)deScale(ofGetMouseX()));
//                }
//            }
//        }
//        
//        
//        if ((getEnableScrollYPositive() || getEnableScrollYNegative()) && deScale(getContentBoundsScaled().height) > getUsableHeight()) {
//            float scrollBarYPerc = std::min((float)1, (float)(getUsableHeight() / (float)deScale(getContentBoundsScaled().height)));
//
//            vizElm_WIDGET_SCROLLBAR_Y.setRectRounded(
//                                                    // scale(getUsableX(false) + getUsableWidth()) - getScaledPadding() * 2
//                                                     scale(getX() + getWidth()) - getScaledPadding() - scale(10),  //come back to this
//                                                     std::max((float)scale(getUsableY(false)), (float)scale(getUsableY(false) + getScrollOffsetY() * -1 * scrollBarYPerc)),
//                                                     scale(10),
//                                                     scale(scrollBarYPerc * getUsableHeight()),
//                                                     scale(5),
//                                                     ofColor(scrollbarColor));
//            
//            //int scrollY = getPotentiallyStartedDraggingStartY() - ofGetMouseY();
//            // bool isScrollbarHovered = vizElm_WIDGET_SCROLLBAR_Y.isHovered_Rect();
//
//            int scrollY = getPotentiallyStartedDraggingStartY() - (int)deScale(ofGetMouseY());
//
//            // Show the scrollbar if the right edge of the widget is hovered - WIP
//           bool isScrollbarHovered = !isDraggingContent() &&  (
//                        deScale(ofGetMouseX()) >= (getUsableX() + getUsableWidth() - deScale(vizElm_WIDGET_SCROLLBAR_Y.getRectangle().width)) &&
//                        deScale(ofGetMouseX()) <= (getUsableX() + getUsableWidth()) &&
//                        deScale(ofGetMouseY()) >= (getUsableY()) &&
//                        deScale(ofGetMouseY()) <= (getUsableY() + getUsableHeight())
//                        ); 
//
//            bool isDraggingToScroll = false;// // TODO: ADD 2 FINGER SWIPE TO SCROLLE HERE OLD CODE:  getIsMousePressedOverWidget(true) && scrollY != 0;
//
//            if (getIsScrollingY() || isScrollbarHovered || isDraggingToScroll) {
//                vizElm_WIDGET_SCROLLBAR_Y.draw();
//                if (isScrollbarHovered) setIsScrollingY();
//                
//                if ((!getIsScrollingYMouseDown() && ofGetMousePressed() && isScrollbarHovered) || isDraggingToScroll) {
//                    setIsScrollingYMouseDown(true);
//                }
//                
//                if (getIsScrollingYMouseDown() && scrollY != 0) {
//                    ofMouseEventArgs args(ofMouseEventArgs::Type::Scrolled, 0, 0, OF_MOUSE_BUTTON_LEFT, 0);
//                    args.scrollY = scrollY;
//                    onCoreWidgetMouseScrolled(args);
//                    //setPotentiallyStartedDraggingStartY(ofGetMouseY());
//                    setPotentiallyStartedDraggingStartY((int)deScale(ofGetMouseY()));
//                }
//            }
//        }
//    }
//    
//    virtual void onWidgetMouseScrolled(ofMouseEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse released...
//    }
//    
//    virtual void onCoreWidgetFileDragEvent(ofDragInfo &dragInfo) {
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...
//        if (mDraggingFileIn) {
//            onWidgetFileDragEvent(dragInfo);
//            mDraggingFileIn = false;
//        }
//    }
//
//    virtual void onWidgetFileDragEvent(ofDragInfo &dragInfo) {
//        if(!getIsEnabled()) return;
//        // Implement any behaviour in derrived class which should handle mouse released...
//       // ofSystemAlertDialog("widget " + getWidgetId() + " received file " + dragInfo.files[0]);
//        
//        // BUG : currently it's firing for all events!!!! - scope it to only the HOVERED widget
//        
//        /*
//         if (isWidgetHovered() ) {  // and dragging file in
//             ofSystemAlertDialog("widget " + getWidgetId() + " received file ");
//         }
//         */
//        
//        
//    }
//    
//    virtual void onCoreWindowMouseEntered(ofMouseEventArgs &e) {
//        mDraggingFileIn = true;
//        mIsWindowHovered = true;
//    }
//
//    virtual void onCoreWindowMouseExited(ofMouseEventArgs &e) {
//        mIsWindowHovered = false;
//    }
//
//	virtual void onCoreWidgetMouseDragged(ofMouseEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//        if (getIsActiveWidget()) { 
//            if(getIsEnabled()) {
//                onWidgetMouseDragged(e);   
//
//
//
//
//cout << "B_DRAGIN'";
//            if (getExternalDrop().getIsDragging()) {
//                cout << "INSIDE_DRAGIN'"; 
//                getExternalDrop().handleExternalDragAndDropMotionNotify();
//                if (!ofGetMousePressed()) getExternalDrop().handleExternalDragAndDropButtonReleaseEvent();
//            }
//cout << "A_DRAGIN'";   
//
//
//            }
//        }
//	}
//
//	virtual void onWidgetMouseDragged(ofMouseEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle mouse dragged...
//	}
//
//	virtual void onCoreWidgetMouseContentDragged(ofMouseEventArgs &e) {
//		// ONLY override this method if you want to override core widget beh\aviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//
//		if (getIsActiveWidget()) {
//            // We want a small amount of inital mouse movement in order to assert it's a genuine drag opperation
//            int mX = deScale(ofGetMouseX());
//            int mY = deScale(ofGetMouseY());
//            
//            if (mX > mPotentiallyStartedDraggingStartX + mMinPixelsMovedToRegisterDrag ||
//                mX < mPotentiallyStartedDraggingStartX - mMinPixelsMovedToRegisterDrag ||
//                mY > mPotentiallyStartedDraggingStartY + mMinPixelsMovedToRegisterDrag ||
//                mY < mPotentiallyStartedDraggingStartY - mMinPixelsMovedToRegisterDrag) {
//                
//
//                if (!isDraggingContent()) {
//                    // Save the original states... so we can begin the drag operation
//                    mTempIsDraggable = mIsDraggable;
//                    mTempIsResizable = mIsResizable;
//                    
//                    // Prevent the widget chrome from resizing/dragging when we're dragging content outside of it's bounds
//                    mIsDraggable = false;
//                    mIsResizable = false;
//                    getViz()->setIsAnyWidgetDraggingOrResizing(true);
//                    setIsDragging(true);
//                    setRespondedToFirstMouseReleasedEvent(true);
//                    mIsDraggingContent = true;
//                }
//                
//               if (getIsEnabled()) {
//                   onWidgetMouseContentDragged(e);
//
//                    if (!getExternalDrop().getIsDragging()) {
//                        // Initiate external Drag and Drop
//                        vector<string> dragFiles = getFilesForExternalDropOperation(getDragData()); 
//                        getExternalDrop().externalDragAndDropFileInit(dragFiles);
//                    }  
//
//               }
//            }
//		}
//	}
//
//    virtual vector<string> getFilesForExternalDropOperation(string dragData) {
//        return vector<string>(); // default to no no files / nothing
//    }
//
//	virtual void onWidgetMouseContentDragged(ofMouseEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle mouse dragged...
//	}
//
//	virtual void onCoreWidgetKeyPressed(ofKeyEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//		if (getIsActiveWidget() && getIsEnabled()) {
//            mHeldDownKeys[e.key] = true;
//            onWidgetKeyPressed(e);
//        }
//	}
//
//	virtual void onWidgetKeyPressed(ofKeyEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle key pressed
//        return;
//	}
//
//    virtual void onWidgetHovered(uiVizWidgetEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse entered...
//    }
//
//    virtual void onWidgetUnhovered(uiVizWidgetEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse exited...
//    }      
//
//    virtual void onWidgetMouseOver(uiVizWidgetEventArgs &e) {
//        // Implement any behaviour in derrived class which should handle mouse exited...
//    }     
//
//	virtual void onCoreWidgetWidgetClicked(ofMouseEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//        if (getIsActiveWidget() && !getIsDragging() && !isDraggingContent()) {
//            if(getIsEnabled()) onWidgetClicked(e);
//        }
//	}
//
//	virtual void onWidgetClicked(ofMouseEventArgs &e) {
//		// Don't implement any base widget logic here, this event is for specific widget click events / functionality
//	}
//
//	virtual void onCoreWidgetKeyReleased(ofKeyEventArgs &e) {
//		// ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//		//  to respond to this event and prevent modifying how core widget functionality works...
//        if (getIsActiveWidget() && getIsEnabled()) {
//            mHeldDownKeys[e.key] = false;
//            onWidgetKeyReleased(e);
//        }
//	}
//
//    //! Check is a certain key is currently held down
//    bool isKeyPressed(int key) {
//        if (key <= 255) return mHeldDownKeys[key];
//        return false;
//    } 
//
//	virtual void onWidgetKeyReleased(ofKeyEventArgs &e) {
//		// Implement any behaviour in derrived class which should handle key pressed
//	}
//       
//    shared_ptr<uiViz> getViz() {
//        return viz;
//    }
//    
//    int getZindex() {
//        return mZIndex;
//    }
//    
//    virtual void setZindex(int zIndex) {
//        mZIndex = zIndex;
//    }
//    
//    bool isTopLevel() {
//        return getZindex() == 0;
//    }
//
//    void setDragData(string dragData) {
//        //cout << "[" << getPersistentId() << "] SETTING DRAG DATA:\n" << mDragData;        
//        mDragData = dragData;
//        eventTransmit(getPersistentId(), WIDGET_EVENT::DRAG_AND_DROP_DATA_SET, "<event>" + mDragData + "</event>", *this);
//    }
//    
//    string getDragData() {
//        return mDragData;
//    }
//    
//    void clearDragData() {
//        mDragData = "";
//    }
//
//    int getPotentiallyStartedDraggingStartX() {
//        return mPotentiallyStartedDraggingStartX;
//    }
//    
//    void setPotentiallyStartedDraggingStartX(int val) {
//        mPotentiallyStartedDraggingStartX = val;
//    }
//    
//    int getPotentiallyStartedDraggingStartY() {
//        return mPotentiallyStartedDraggingStartY;
//    }
//    
//    void setPotentiallyStartedDraggingStartY(int val) {
//        mPotentiallyStartedDraggingStartY = val;
//    }
//    
//    bool getDidMoveFocus() {
//        return mDidMoveFocus;
//    }
//    
//    void setDidMoveFocus(bool val) {
//        mDidMoveFocus = val;
//    }
//    
//    bool getIgnoreThemeChanges() {
//        return mIgnoreThemeChanges;
//    }
//    
//    void setIgnoreThemeChanges(bool val) {
//        mIgnoreThemeChanges = val;
//    }
//    
//    bool getIsSystemWidget() {
//        return mIsSystemWidget;
//    }
//    
//    void setIsSystemWidget(bool val) {
//        mIsSystemWidget = val;
//    }
//
//    bool getIsVisualDebugMode() {
//        if(uiVizShared::getVizDebug() > -1) {
//            return (uiVizShared::getVizDebug() == 1);
//        }
//        return mIsVisualDebugMode;
//    }
//    
//    void setIsVisualDebugMode(bool value) {
//        mIsVisualDebugMode = value;
//    }         
//
//    bool getUpdatedSinceUnhovered() {
//        return mUpdatedSinceUnhovered;
//    }
//
//    void setUpdatedSinceUnhovered(bool val) {
//        mUpdatedSinceUnhovered = val;
//    }
//
//    void setShowingAsPopout(bool val) {
//        mShowingAsPopout = val;
//    }
//
//    bool getShowingAsPopout() {
//        return mShowingAsPopout;
//    }   
//
//    virtual bool hasActiveElement() {
//        return false;
//    }
//
//    void setMetadata(string key, string val)  {
//        mMetadata[key] = val;
//    } 
//
//    void setMetadata(string key, float val) {
//        setMetadata(key, ofToString(val));
//    }
//
//    void setMetadata(string key, double val) {
//        setMetadata(key, ofToString(val));
//    }
//
//    void setMetadata(string key, int val) {
//        setMetadata(key, ofToString(val));
//    }
//
//    void setMetadata(string key, int64_t val) {
//        setMetadata(key, ofToString(val));
//    }
//
//    void setMetadata(string key, bool val) {
//        setMetadata(key, ofToString(val));
//    }     
//
//    string getMetadata(string key)  {
//        std::map<string, string>::iterator it = mMetadata.find(key);
//        if (it != mMetadata.end()) {
//            return it->second;
//        } else {
//            return "";
//        }
//    }
//    
//    float getMetadataFloat(string key) {
//        return ofToFloat(getMetadata(key));
//    }
//
//    double getMetadataDouble(string key) {
//        return ofToDouble(getMetadata(key));
//    }
//
//    int getMetadataInt(string key) {
//        return ofToInt(getMetadata(key));
//    }
//
//    int64_t getMetadataInt64(string key) {
//        return ofToInt64(getMetadata(key));
//    }
//
//    bool getMetadataBool(string key) {
//        return ofToBool(getMetadata(key));
//    }    
//
//    void deleteMetadata(string key)  {
//        std::map<string, string>::iterator it = mMetadata.find(key);
//        if (it != mMetadata.end()) {
//            mMetadata.erase(it);
//        }
//    }                
//
//    void clearMetadata()  {
//        mMetadata.clear();
//    }    
//
//    void setPopoutWidget(uiVizWidgetBase* w) {
//        if(w) w->setPopoutOpenerWidget(this);
//        mPopoutWidget = w;
//    }
//
//    uiVizWidgetBase* getPopoutWidget() {
//        return mPopoutWidget;
//    }     
//
//    uiVizWidgetBase* getPopoutOpenerWidget() {
//        return mPopoutOpenerWidget;
//    }    
//
//    void setPopoutOpenerWidget(uiVizWidgetBase* w) {
//        mPopoutOpenerWidget = w;
//    }               
//    
//protected:
//
//    bool getX_ExprWasSetProgramatically() {
//        return mX_ExprWasSetProgramatically;
//    }
//    
//    void setX_ExprWasSetProgramatically(bool val) {
//        mX_ExprWasSetProgramatically = val;
//    }
//    
//    bool getY_ExprWasSetProgramatically() {
//        return mY_ExprWasSetProgramatically;
//    }
//    
//    void setY_ExprWasSetProgramatically(bool val) {
//        mY_ExprWasSetProgramatically = val;
//    }
//    
//    bool getWidth_ExprWasSetProgramatically() {
//        return mWidth_ExprWasSetProgramatically;
//    }
//    
//    void setWidth_ExprWasSetProgramatically(bool val) {
//        mWidth_ExprWasSetProgramatically = val;
//    }
//    
//    bool getHeight_ExprWasSetProgramatically() {
//        return mHeight_ExprWasSetProgramatically;
//    }
//    
//    void setHeight_ExprWasSetProgramatically(bool val) {
//        mHeight_ExprWasSetProgramatically = val;
//    }  
//
//    ofxExternalDrop& getExternalDrop() {
//        if(!externalDropInitialized) {
//            externalDrop = ofxExternalDrop(true);
//            externalDropInitialized = true;
//        }
//        return externalDrop;
//    }
//
//    void clearExternalDrop() {
//        externalDrop = ofxExternalDrop(false);
//        externalDropInitialized = false;
//    }    
//
//    bool getTransmitOscMessages() {
//        return mTransmitOscMessages;
//    }
//
//    void setTransmitOscMessages(bool val) {
//        mTransmitOscMessages = val;
//    }     
//
//    PopoutDirection mPopoutDirection = PopoutDirection::NONE;
//    uiVizElm vizElm_WIDGET_TITLE_BUBBLE_TRIANGLE;      
//
//private:
//    uiVizWidgetContext context;
//    bool mHeldDownKeys[256];
//
//    bool getIsChildOfModal(uiVizWidgetBase* widget) {
//        uiVizWidgetBase* w = parent();
//        while(w) {
//            if (w->getWidgetId() == getViz()->getModalWidgetId()) return true;
//            w = w->parent();
//        }   
//        return getWidgetId() == getViz()->getModalWidgetId();     
//    }
//
//    ofxExternalDrop externalDrop;
//    bool externalDropInitialized = false;
//
//    void init() {
//        viz = uiVizShared::getViz();
//        ofAddListener(getViz()->scaleChanged, this,  &uiVizWidgetBase::onCoreWidgetScaleChanged);
//        ofAddListener(ofEvents().windowResized, this, &uiVizWidgetBase::onCoreWidgetWindowResized);
//        ofAddListener(ofEvents().mouseMoved, this, &uiVizWidgetBase::onCoreWidgetMouseMoved);
//        ofAddListener(ofEvents().mousePressed, this, &uiVizWidgetBase::onCoreWidgetMousePressed);
//        ofAddListener(ofEvents().mouseReleased, this, &uiVizWidgetBase::onCoreWidgetMouseReleased);
//        ofAddListener(ofEvents().mouseScrolled, this, &uiVizWidgetBase::onCoreWidgetMouseScrolled);
//        ofAddListener(ofEvents().fileDragEvent, this, &uiVizWidgetBase::onCoreWidgetFileDragEvent);
//		ofAddListener(ofEvents().mouseDragged, this, &uiVizWidgetBase::onCoreWidgetMouseDragged);
//        ofAddListener(ofEvents().mouseEntered, this, &uiVizWidgetBase::onCoreWindowMouseEntered);
//        ofAddListener(ofEvents().mouseExited, this, &uiVizWidgetBase::onCoreWindowMouseExited);
//		ofAddListener(ofEvents().keyPressed, this, &uiVizWidgetBase::onCoreWidgetKeyPressed);
//		ofAddListener(ofEvents().keyReleased, this, &uiVizWidgetBase::onCoreWidgetKeyReleased);
//        
//        // Touch events
//        ofAddListener(ofEvents().touchDown, this, &uiVizWidgetBase::onCoreWidgetTouchDown);
//        ofAddListener(ofEvents().touchUp, this, &uiVizWidgetBase::onCoreWidgetTouchUp);
//        
//        ofAddListener(widgetEventReceived, this,  &uiVizWidgetBase::onCoreWidgetEventReceived);
//        ofAddListener(widgetResized, this,  &uiVizWidgetBase::onCoreWidgetResized);       
//        
//        // Aspect ratio
//        if (getHeight() > 0) {
//            setAspectRatio(getWidth() / (float)getHeight());
//        } else {
//            setAspectRatio(1.0f);
//        }
//
//        for (int i=0; i<255; i++) {
//            mHeldDownKeys[i] = false;
//        }
//
//       // ofxExternalDrop externalDrop = ofxExternalDrop();
//
//    }
//    
//    // Lambda type event handlers
//    std::function<void(ofMouseEventArgs &)> m_onCoreWidgetMousePressedFunction = [this](ofMouseEventArgs &){};
//    std::function<void(ofMouseEventArgs &)> m_onCoreWidgetMouseReleasedFunction = [this](ofMouseEventArgs &){};
//
//    widgetTelemetry mWidgetTelemetry;
//    uiVizWidgetTheme mTheme = uiVizWidgetTheme();
//    
//    bool mIsPermanentWidget = false;
//    bool mIsHighlighted = false;    
//    bool mShouldDeleteThisWidget = false;
//    bool mShouldCloseThisWidget = false;
//    bool mIsEnabled = true;
//	bool mWasJustInitialized = true;
//    uiVizWidgetBase* mTargetDropWidget = nullptr;    
//    bool mShouldShowClipboardForThisWidget = false;
//    string mPersistentId = "";  
//    string mOwnerWidgetId = "";  
//    string mWidgetClassType = "";
//    bool mShouldPersist = false;
//    bool mShouldPersistTheme = false;
//    bool mNeedsUpdate = true;
//    bool mWidgetUINeedsUpdate = true;
//    int mX = 0;
//    int mY = 0;
//    int mWidth = 100;
//    int mHeight = 100;
//    bool mIsAutoResizeToContentsWidth = false;
//    bool mIsAutoResizeToContentsHeight = false;
//    int mScreenPadding = 0;
//    
//    string mX_Expr = "";
//    string mY_Expr = "";
//    string mWidth_Expr = "";
//    string mHeight_Expr = "";
//    bool mIgnoreExpr_Layout = false;
//    bool mExpressionRecalculationRequired = true;
//    bool mX_ExprWasSetProgramatically = false;
//    bool mY_ExprWasSetProgramatically = false;
//    bool mWidth_ExprWasSetProgramatically = false;
//    bool mHeight_ExprWasSetProgramatically = false;
//    bool mUpdatedSinceUnhovered = true;
//    bool mShowingAsPopout = false;
//
//
//    uiVizWidgetBase* mPopoutFromWidget = nullptr;
//    int mPopoutX = 0;
//    int mPopoutY = 0;
//    int mRawPopoutX = 0;
//    int mRawPopoutY = 0;
//    int mPopoutOffset = 15;    
// 
//    
//    int mMinWidth = 75;
//    int mMinHeight = 75;
//    int mMaxWidth = ofGetWindowWidth()*10;
//    int mMaxHeight = ofGetWindowHeight()*10;
//    bool mIsRoundedRectangle = true;
//    bool mIsShadow = true;
//    string mTitle = "";
//    int  mTitleWidth = 150;
//    float mScrollOffsetX = 0.0f;
//    float mScrollOffsetY = 0.0f;
//    float mScrollScaleX = 10.0f;
//    float mScrollScaleY = 10.0f;
//    bool mIsVisible = true;
//    uiVizCoord::vizBounds mContentBoundsScaled = uiVizCoord::vizBounds(0, 0, 0, 0);
//    
//    ScrollAction mScrollAction = ScrollAction::ZOOM;
//    CloseAction mCloseAction = CloseAction::REMOVE;
//    
//    bool mEnableScrollXPositive = false;
//    bool mEnableScrollXNegative = false;
//    bool mEnableScrollYPositive = false;
//    bool mEnableScrollYNegative = false;
//
//    uint64_t mElapsedTimerMillis = 0;
//    
//    int mScrollingStartedMS_Y = 0;
//    int mScrollingStartedMS_X = 0;
//    bool mIsScrollingXMouseDown = false;
//    bool mIsScrollingYMouseDown = false;
//    
//    bool mLockAspectRatio = false;
//    float mAspectRatio = 1.0f;
//    
//    bool mIsDraggable = true;
//    bool mIsResizable = true;
//    
//    bool mIsDragging = false;
//    bool mIsResizing = false;
//    bool mIsAutoUpdateWhenActive = true;
//    bool mIsUnhoverLoseFocus = true;
//    bool mShouldCloseIfOtherWidgetClicked = false;
//    bool mUseFbo = true;
//    
//    bool mRespondedToFirstMousePressedEvent = false;
//    bool mRespondedToFirstMouseReleasedEvent = false;
//    bool mMousePressWasRegisteredWhenCheckingForReleased = false;
//    
//    shared_ptr<uiViz> viz;
//    int mZIndex = 0;
//    bool mIsNextInLineForFocus = true;
//	bool mIsDraggingContent = false;
//    int mPotentiallyStartedDraggingStartX = 0;
//    int mPotentiallyStartedDraggingStartY = 0;
//    int mMinPixelsMovedToRegisterDrag = 20;
//    uiVizCoord::vizPoint mLastMouseClickCoords = uiVizCoord::vizPoint(0, 0);
//    
//    bool mTempIsDraggable = true;
//    bool mTempIsResizable = true;
//    
//    bool mDraggingFileIn = false;
//    bool mIsWindowHovered = true;
//    
//    string mDragData = "";
//    bool mTransmitOscMessages = true;
//    ofFbo mContentDragIconFbo;
//    
//    //vector<TargetWidgetAction> mTargetWidgetActions;
//    //std::vector<std::reference_wrapper<uiVizWidgetBase>> mTargetWidgets;
//
//    bool mDidMoveFocus = false;
//    bool mIgnoreThemeChanges = false;
//    bool mIsSystemWidget = false;
//    bool mIsVisualDebugMode = false;    
//
//    uiVizElm vizElm_WIDGET_SCROLLBAR_X;
//    uiVizElm vizElm_WIDGET_SCROLLBAR_Y;
//
//    map<string, string> mMetadata;
//    std::function<void(uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, const string &)> mWidgetClosedCallback = [](uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, string result){};
//    uiVizWidgetBase* mPopoutWidget = nullptr;
//    uiVizWidgetBase* mPopoutOpenerWidget = nullptr;
//    
//
//};
//
////------------------------------ uiVizWidgetElm : derive all widget elements from this --------------------------------
//class uiVizWidgetElm : public uiVizWidgetBase {
//    
//public:
//    
//    uiVizWidgetElm(string persistentId, string widgetXML, uiVizWidgetBase* parent) : uiVizWidgetBase(persistentId, widgetXML) {
//        init();
//        mParent = parent; // The hosting widget (not necessarily uiVizWidget, could be anything derrived from uiVizWidgetBase
//        loadState(widgetXML);
//    }
//    
//    int getRelativeX() {
//        return uiVizWidgetBase::getX();
//    }
//    
//    int getRelativeY() {
//        return uiVizWidgetBase::getY();
//    }
// 
//    virtual int getX() override {
//        return (parent() != NULL && parent() != nullptr) ?
//            parent()->getX() + uiVizWidgetBase::getX() : uiVizWidgetBase::getX();
//    }
//    
//    virtual int getY() override {
//        return (parent() != NULL && parent() != nullptr) ?
//            parent()->getY() + uiVizWidgetBase::getY() : uiVizWidgetBase::getY();
//    }
//    
//    virtual int getUsableX() override {
//        return (parent() != NULL && parent() != nullptr) ?
//            getNonScaledPadding() + uiVizWidgetBase::getX() + parent()->getX() + getScrollOffsetX() : getNonScaledPadding() + uiVizWidgetBase::getX() + getScrollOffsetX();
//        
//    }
//    
//    virtual int getUsableY() override {
//        return (parent() != NULL && parent() != nullptr) ?
//            getNonScaledPadding() + uiVizWidgetBase::getY() + parent()->getY() + getScrollOffsetY() : getNonScaledPadding() + uiVizWidgetBase::getY() + getScrollOffsetY();
//    }
//    
//    virtual void setX(int x) override {
//        if (uiVizWidgetBase::getX() != x) {
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//            setShouldRedetermineElementVisibility(true);
//        }
//        uiVizWidgetBase::setX(x);
//    }
//    
//    virtual void setY(int y) override {
//        if (uiVizWidgetBase::getY() != y) {
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//            setShouldRedetermineElementVisibility(true);
//        }
//        uiVizWidgetBase::setY(y);
//    }
//
//    bool isInsideWidgetBounds()  {
//        bool insideX = ((getX() + getWidth())  >= parent()->getX() && (getX()) < (parent()->getX() + parent()->getWidth()));
//        bool insideY = ((getY() + getHeight()) >= parent()->getY() && (getY()) < (parent()->getY() + parent()->getHeight()));
//
//        if (!insideX || !insideY) {
//            return false;
//        } else {
//            return true;
//        }
//    }
//
//    void determineElementVisibility() {
//        if (!mShouldRedetermineElementVisibility || (parent() && !parent()->getIsVisible())) {
//            return;
//        } else {
//            mShouldRedetermineElementVisibility = false;
//        }
//        
//        if (!mOutOfBounds_ElementWasHidden) mOutOfBounds_ElementWasOriginallyVisible = getIsVisible();
//        if (!isInsideWidgetBounds()) {
//            // mOutOfBounds_ElementWasOriginallyVisible = getIsVisible();       
//            setIsVisible(false);
//            mOutOfBounds_ElementWasHidden = true;
//        } else {
//            if (mOutOfBounds_ElementWasOriginallyVisible && mOutOfBounds_ElementWasHidden) {
//                setIsVisible(true);
//                mOutOfBounds_ElementWasHidden = true;
//            }
//        }        
//    }
//
//    bool getShouldRedetermineElementVisibility() {
//        return mShouldRedetermineElementVisibility;
//    }
//
//    void setShouldRedetermineElementVisibility(bool val) {
//        mShouldRedetermineElementVisibility = val;
//    }      
//    
//    virtual void setWidth(int width) override {
//        if (uiVizWidgetBase::getWidth() != width) {
//            mAllocatedSinceLastResize = false;
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//        }
//        uiVizWidgetBase::setWidth(width);
//    }
//    
//    virtual void setHeight(int height) override {
//        if (uiVizWidgetBase::getHeight() != height) {
//            mAllocatedSinceLastResize = false;
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//        }
//        uiVizWidgetBase::setHeight(height);
//    }
//    
//    float getCurrentForegroundAlpha() {
//        return mCurrentForegroundAlpha;
//    }
//    
//    float getCurrentBackgroundAlpha() {
//        return mCurrentBackgroundAlpha;
//    }
//
//    virtual void setTheme(uiVizWidgetTheme val) override {
//        if (getIgnoreThemeChanges()) return;
//        uiVizWidgetBase::setTheme(val);
//        uiVizWidgetTheme theme = getTheme();
//        setIsRoundedRectangle(theme.ElementRoundedRectangle);
//    }
//    
//    virtual void onWidgetLoaded() override {
//        // Implement any behaviour for when a widget has loaded
//    }
//
//    virtual bool loadState(string widgetXML) override {
//        uiVizWidgetBase::loadState(widgetXML, "element");
//        ofxXmlSettings mWidgetXML = ofxXmlSettings();
//        
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//             cout << "[" << getPersistentId() << "]uiVizWidgetElm->loadState()\n";
//        #endif
//
//        if (!mWidgetXML.loadFromBuffer(widgetXML.c_str())) {
//            #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3       
//                cout << "[" << getPersistentId() << "]uiVizWidgetElm->Unable to load XML\n" << widgetXML.c_str() << "\n";
//            #endif            
//            return false;
//        }    
//        
//        mWidgetXML.pushTag("element");
//
//        // Get the x,y values. If not found set to zero (top left of host widget)
//        if (parent() != NULL && parent() != nullptr) {
//            if (getX_Expr() == "") {
//                setX(mWidgetXML.getAttribute("bounds", "x", 0));
//            }
//            if (getY_Expr() == "") {
//                setY(mWidgetXML.getAttribute("bounds", "y", 0));
//            }
//        }
//
//        uiVizWidgetTheme theme = (parent() ? parent()->getTheme() : getTheme());
//        
//        if (mWidgetXML.tagExists("appearance")) {
//            theme.loadForElement(theme, widgetXML);
//        }
//        mWidgetXML.popTag(); // element
//        
//        onWidgetLoaded();
//
//        return true;
//    }
//    
//    virtual ofxXmlSettings saveState() override {
//        ofxXmlSettings mWidgetXML;
//        if(!getShouldPersist()) return mWidgetXML;
//        
//        mWidgetXML = uiVizWidgetBase::saveState("element");
//        while (mWidgetXML.popTag() > 0); // pop to top!
//        mWidgetXML.setAttribute("element", "class", "uiVizWidgetElm", 0);
//        mWidgetXML.pushTag("element");
//
//        // Store the relative x,y values NOT absolute!
//        if (getX_Expr() == "") {
//            mWidgetXML.setAttribute("bounds", "x", getRelativeX(), 0);
//        }
//        if (getY_Expr() == "") {
//            mWidgetXML.setAttribute("bounds", "y", getRelativeY(), 0);
//        }
//        
//        if (getShouldPersistTheme()) {
//            mWidgetXML.pushTag("appearance");
//            mWidgetXML.addTag("foregroundColor");
//            mWidgetXML.setAttribute("foregroundColor", "color", getTheme().getElementForegroundColorHex(), 0);
//
//            mWidgetXML.addTag("foregroundAlpha");
//            mWidgetXML.setAttribute("foregroundAlpha", "hovered", getTheme().ElementHoveredForegroundAlpha, 1);
//            mWidgetXML.setAttribute("foregroundAlpha", "unhovered", getTheme().ElementUnhoveredForegroundAlpha, 1);
//            
//            mWidgetXML.addTag("backgroundColor");
//            mWidgetXML.setAttribute("backgroundColor", "color", getTheme().getElementBackgroundColorHex(), 0);
//            
//            mWidgetXML.addTag("backgroundAlpha");
//            mWidgetXML.setAttribute("backgroundAlpha", "hovered", getTheme().ElementHoveredBackgroundAlpha, 1);
//            mWidgetXML.setAttribute("backgroundAlpha", "unhovered", getTheme().ElementUnhoveredBackgroundAlpha, 1);
//
//            mWidgetXML.popTag(); // appearance
//        }
//
//        mWidgetXML.popTag(); // element
//   
//        return mWidgetXML;
//    }
//
//    virtual void update(uiVizWidgetContext context) override {
//        // Implemented by descendant class...
//    }
//    
//    bool isActiveOrParentActive() {
//        if (parent()) {
//            return (parent()->getWidgetId() == getActiveWidgetId() || getWidgetId() == getActiveWidgetId());
//        } else {
//            return (getWidgetId() == getActiveWidgetId());
//        };
//    }
//    
//    bool isParentActive() {
//        if (parent()) {
//            return (parent()->getWidgetId() == getActiveWidgetId());
//        }
//        return false;
//    }
//
//    bool isRootActive() {
//        if (root()) {
//            return (root()->getWidgetId() == getActiveWidgetId());
//        }
//        return false;
//    }    
//    
//    virtual void onCoreWidgetKeyPressed(ofKeyEventArgs &e) override {
//        // ONLY override this method if you want to override core widget behaviour. Use "onWidget$$$$" methods in descendant classes
//        //  to respond to this event and prevent modifying how core widget functionality works...   
//        if (parent()) {
//            if (!parent()->getIsActiveWidget() && !parent()->hasActiveElement()) return;
//            if (getIsFocused(false) && getIsEnabled()) onWidgetKeyPressed(e);
//
//            if (!parent()->getDidMoveFocus() && e.key == OF_KEY_TAB) {
//                parent()->eventTransmit(getPersistentId(), WIDGET_EVENT::FOCUS_NEXT_ELEMENT, "<event></event>", *this);
//                return;
//            }
//        }
//    }
//
//    virtual void onCoreWidgetMouseReleased(ofMouseEventArgs &e) override {
//        mIsElmDragging = false;
//        uiVizWidgetBase::onCoreWidgetMouseReleased(e);
//    }
//    
//    virtual void onCoreWidgetMousePressed(ofMouseEventArgs &e) override {
//        if (e.button == OF_MOUSE_BUTTON_LEFT && isWidgetHovered() && getIsActiveWidget()) {
//            mIsElmDragging = true;
//        }
//        
//        uiVizWidgetBase::onCoreWidgetMousePressed(e);
//    }
//
//    virtual void onCoreWidgetMouseDragged(ofMouseEventArgs &e) override {
//        // The below condition caters for the situation where a user began dragging on an elm quickly
//        // and the mouse is no longer over the elm, but the mouse button is still down!
//        if (getIsElmDragging()) {
//            if(getIsEnabled()) onWidgetMouseDragged(e);
//        } else {
//            uiVizWidgetBase::onCoreWidgetMouseDragged(e);
//        }
//    }
//
//    virtual void onCoreWidgetEventReceived(uiVizWidgetEventArgs &args) override {
//        if(!getIsEnabled()) return;
//        if (args.eventName == WIDGET_EVENT::CLIPBOARD_PASTE) {
//            setWidgetNeedsUpdate(true);
//            setNeedsUpdate(true);
//        }
//    }
//    
//    virtual void onAllSiblingElementsLoaded() {
//        
//    }
//    
//    void handleDrawEvents() {
//        uiVizWidgetEventArgs args = uiVizWidgetEventArgs(getWidgetId(), *this);
//        bool hovered = isWidgetHovered();
//        
//        if (hovered) {
//            setTargetDropWidgetId();
//        }
//        
//        if ((hovered) && !getIsDragging() && !getIsResizing() && !getViz()->getIsAnyWidgetDraggingOrResizing()) {
//            if (hovered) {
//                ofNotifyEvent(widgetHovered, args);
//            }
//            
//            if (((isTopLevel() || getActiveWidgetId() == ""))) {
//                //if (ofGetMousePressed()) ofNotifyEvent(widgetClicked, args);
//                //if (!getIsActiveWidget()) setActiveWidget();
//                
//                if (!getIsActiveWidget()) {
//                    setActiveWidget();
//                    onWidgetHovered(args);
//                }
//                onWidgetMouseOver(args);
//                if (ofGetMousePressed()) {
//                    ofNotifyEvent(widgetClicked, args);
//                }
//                
//            } // getValue() setValue(), settings and send feedback (widget with a menu on the left)
//            
//        } else if (!getViz()->getIsAnyWidgetDraggingOrResizing() && getIsActiveWidget()) {
//            clearTargetDropWidgetId();
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
//    void coreDraw() {
//        
//        if (!getIsVisible()) return;
//
//        getWidgetTelemetry()->startDraw(); //////////////////////////////////////////////////////////
//        
//        handleDrawEvents();
//        
//        if ((getIsActiveWidget() || getIsFocused(true)) && getIsEnabled()) {
//            if (mCurrentForegroundAlpha != getTheme().ElementHoveredForegroundAlpha) {
//                mCurrentForegroundAlpha = scaleAnimation(getWidgetId() + "_foreground_hovered", mCurrentForegroundAlpha, getTheme().ElementHoveredForegroundAlpha, 0.6f);
//            }
//            if (mCurrentBackgroundAlpha != getTheme().ElementHoveredBackgroundAlpha) {
//                mCurrentBackgroundAlpha = scaleAnimation(getWidgetId() + "_background_hovered", mCurrentBackgroundAlpha, getTheme().ElementHoveredBackgroundAlpha, 0.6f);
//            }
//        } else {
//            if (mCurrentForegroundAlpha != getTheme().ElementUnhoveredForegroundAlpha) {
//                mCurrentForegroundAlpha = scaleAnimation(getWidgetId() + "_foreground_unhovered", mCurrentForegroundAlpha, getTheme().ElementUnhoveredForegroundAlpha, 0.6f);
//            }
//            if (mCurrentBackgroundAlpha != getTheme().ElementUnhoveredBackgroundAlpha) {
//                mCurrentBackgroundAlpha = scaleAnimation(getWidgetId() + "_background_unhovered", mCurrentBackgroundAlpha, getTheme().ElementUnhoveredBackgroundAlpha, 0.6f);
//            }
//        }
//        
//        allocateFbo();
//        fboBegin();
//        draw(this->context);     
//        fboEnd();
//        fboDraw();
//
//        if (parent() && parent()->getIsVisualDebugMode()) uiVizWidgetElm::draw(this->context);           
//
//        if (getIsActiveWidget() && getScrollAction() == ScrollAction::SCROLL) {
//            coreDrawWidgetScrollbars(getTheme().WidgetAccentHighContrast1Color_withAlpha(0.5f));
//        }
//        
//        getWidgetTelemetry()->endDraw(); //////////////////////////////////////////////////////////
//    }
//    
//    bool isTransitioningAlpha() override {
//        if (!getIsVisible()) return false;
//        if (getIsActiveWidget()) {
//            return mCurrentForegroundAlpha != getTheme().ElementHoveredForegroundAlpha || mCurrentBackgroundAlpha != getTheme().ElementHoveredBackgroundAlpha;
//        } else {
//            return mCurrentForegroundAlpha != getTheme().ElementUnhoveredForegroundAlpha || mCurrentBackgroundAlpha != getTheme().ElementUnhoveredBackgroundAlpha;
//        }
//    }
//    
//    virtual void setNeedsUpdate(bool needsUpdate) override {
//        uiVizWidgetBase::setNeedsUpdate(needsUpdate);
//        
//        uiVizWidgetBase* p = parent();
//        
//        if(p) {
//            p->setNeedsUpdate(needsUpdate);
//        }
//    }
//    
//    virtual void draw(uiVizWidgetContext context) override {
//        // Implemented by descendant class...
//
//        int elmIndex = parent() ? parent()->getWidgetElementIndex(getPersistentId()) : 0;
//        int hueAngle = (parent() ? 255.0f * ((float)elmIndex) / max(1, (int)parent()->getWidgetElementSize()) : 0);
//        ofColor color = ofColor::fromHsb(hueAngle, 255, getTheme().IsDark ? 200 : 100);
//        ofColor color2 = ofColor(color.r, color.g, color.b, 200);
//
//        uiVizElm vizElm_BLANK;  
//        vizElm_BLANK.setRectangle(scale(getX()), scale(getY()), scale(getWidth()), scale(getHeight()));
//        vizElm_BLANK.setStroke(scale(2), color);          
//        vizElm_BLANK.draw();
//
//        uiVizElm vizElm_BLANK2;  
//        vizElm_BLANK2.setRectangle(scale(getX()), scale(getY()), scale(getWidth()), scale(getHeight()), color2);
//        vizElm_BLANK2.draw();        
//
//        uiVizElm errRect;
//        ofRectangle errRectOf = titleFont->rect(ofToString(elmIndex) + ":" + getPersistentId());
//        errRect.setRectangle(errRectOf.getX(), errRectOf.getY(), errRectOf.getWidth(), errRectOf.getHeight());    
//
//        ofPushStyle();   
//        ofSetColor(getTheme().IsDark ? ofColor::black : ofColor::white);
//        titleFont->draw(ofToString(elmIndex) + ":" + getPersistentId(),
//                        getViz()->scale(getX() + (getWidth() / 2.0f)) - errRect.getRectangle().width / 2.0f,
//                        getViz()->scale(getY() + (getHeight() / 2.0f ))  + errRect.getRectangle().height / 2.0f);
//        ofPopStyle();                           
//    }
//    
//    virtual ~uiVizWidgetElm() {
//
//        #if VIZ_DEBUG_LEVEL >= 2 && VIZ_DEBUG_LEVEL < 3
//        cout << "[" << getPersistentId() << "]~uiVizWidgetElm()\n";
//        #endif        
//    }
//    
//    virtual uiVizWidgetBase* parent() override {
//        return mParent;
//    }
//    
//    bool getIsFocused(bool parentMustBeHovered) {
//        if (!getIsVisible()) return false;
//        return (mIsFocused && !parentMustBeHovered) || (mIsFocused && parentMustBeHovered && parent() && parent()->isWidgetHovered());
//    }
//    
//    void setIsFocused(bool val) {
//        mIsFocused = val;
//    }
//    
//    bool getIsSiblingFocused() {
//        return mIsSiblingFocused;
//    }
//    
//    void setIsSiblingFocused(bool val) {
//        mIsSiblingFocused = val;
//    }
//    
//    bool getIsElmDragging() {
//        return mIsElmDragging;
//    }
//    
//    bool getAllSiblingElementsLoaded() {
//        return mAllSiblingElementsLoaded;
//    }
//    
//    void setAllSiblingElementsLoaded(bool val) {
//        mAllSiblingElementsLoaded = val;
//    }
//
//    void allocateFbo() {
//        if (!mAllocatedSinceLastResize) {
//            
//            #ifdef TARGET_OPENGLES
//                fbo.allocate(scale(getWidth()), scale(getHeight()), GL_RGBA);
//            #else
//                fbo.allocate(scale(getWidth()), scale(getHeight()),  GL_RGBA, 16); // GL_RGBA32F, 32);
//            #endif
//            
//            fbo.begin();
//            ofClear(255, 255, 255);
//            fbo.end();
//            mAllocatedSinceLastResize = true;
//        }
//    }
//    void fboBegin() {
//        fbo.begin();
//        ofClear(0, 0, 0, 0);
//        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//        ofPushMatrix();
//        ofTranslate(-1*scale(getX()), -1*scale(getY()));
//        ofPushStyle();
//    }
//    
//    void fboEnd() {
//        ofPopStyle();
//        ofPopMatrix();
//        fbo.end();
//    }
//    
//    void fboDraw() {
//        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//        
//        
//        #ifdef TARGET_OPENGLES
//            //fbo.draw(scale(getX()), scale(getY()), scale(-1*getWidth()), scale(-1*getHeight()));
//            fbo.draw(1.5f*scale(getX()), -1.5f*scale(getY()), scale(getWidth()), -1.5f*scale(getHeight()));
//        #else
//            fbo.draw(scale(getX()), scale(getY()), scale(getWidth()), scale(getHeight()));
//        #endif
//        
//        
//        ofEnableAlphaBlending();     
//    }
//
//    void setPopoutWidget(uiVizWidgetBase* w, PopoutDirection popoutDirection, uiVizWidgetTheme theme) {
//        setPopoutWidget(w, popoutDirection, theme, true);
//    }
//
//    void setPopoutWidget(uiVizWidgetBase* w, PopoutDirection popoutDirection) {
//        setPopoutWidget(w, popoutDirection, uiVizWidgetTheme(), false);
//    }
//
//    void setPopoutWidgetIgnoreTheme(uiVizWidgetBase* w, PopoutDirection popoutDirection) {
//        setPopoutWidget(w, popoutDirection, uiVizWidgetTheme(), true);
//    }
//
//    void setPopoutWidgetShownCallback(std::function<void()> popoutShownCallback) { 
//        mPopoutShownCallback = popoutShownCallback;
//    }
//
//    void setPopoutWidgetClosedCallback(std::function<void(uiVizWidgetBase* sender, uiVizWidgetBase* closedWidget, const string &)> popoutClosedCallback) { 
//        if (getPopoutWidget()) {
//            getPopoutWidget()->setWidgetClosedCallback(popoutClosedCallback);
//        }
//    }
//
//    void showPopoutWidgetIfSet() {
//        if (getPopoutWidget()) {
//            if(mThemeWasSetForPopout) {
//                getPopoutWidget()->popoutFrom(this, mPopoutDirection, true);
//            } else {
//                getPopoutWidget()->popoutFrom(this, mPopoutDirection);                
//            }
//            setActiveWidget();
//            mPopoutShownCallback(); // call it...
//        }
//    }
// 
//
//
//private:
//    uiVizWidgetContext context;
//
//    uiVizWidgetBase* mParent;
//    shared_ptr<ofxSmartFont> titleFont;
//    bool mIsElmDragging = false;
//    bool mShouldRedetermineElementVisibility = true;
//    bool mOutOfBounds_ElementWasHidden = false;
//    bool mOutOfBounds_ElementWasOriginallyVisible = true;    
//
//    float mCurrentForegroundAlpha = 0.80f;
//    float mCurrentBackgroundAlpha = 0.70f;   
//
//    bool mIsFocused = false;
//    bool mIsSiblingFocused = false;
//    bool mAllSiblingElementsLoaded = false;
//    ofFbo fbo;
//    bool mAllocatedSinceLastResize = false;
//
//
//    // Popout stuff
//    PopoutDirection mPopoutDirection = PopoutDirection::DOWN;
//    bool mThemeWasSetForPopout = false;    
//
//    std::function<void()> mPopoutShownCallback = [](){};
//
//    void init() {
//        titleFont = (getViz()->getScale() < 1) ? getViz()->getSmallFont() : getViz()->getMediumFont();
//        uiVizWidgetBase::setWidth(35);
//        uiVizWidgetBase::setHeight(30);
//        setIsResizing(false);
//        setIsDragging(false);
//        setIsResizable(false);
//        setIsDraggable(false);
//        setScrollAction(ScrollAction::NONE);
//    }
//
//    void setPopoutWidget(uiVizWidgetBase* w, PopoutDirection popoutDirection, uiVizWidgetTheme theme, bool themeWasSet) {
//        if (w && w != nullptr) {
//            mThemeWasSetForPopout = themeWasSet;
//            mPopoutDirection = popoutDirection;
//            uiVizWidgetBase::setPopoutWidget(w);
//            w->setIsVisible(false);
//        }
//    }       
//    
//};
//
//
//
//
//#include "element/uiVizWidgetElmTextbox.h"
//#include "element/uiVizWidgetElmTextarea.h"
//#include "element/uiVizWidgetElmLabel.h"
//#include "element/uiVizWidgetElmButton.h"
//#include "element/uiVizWidgetElmSlider.h"
//#include "element/uiVizWidgetElmCheckbox.h"
//#include "element/uiVizWidgetElmDropdown.h"
//#include "element/uiVizWidgetElmBreadcrumb.h"
//#include "element/uiVizWidgetElmImage.h"
//#include "element/uiVizWidgetElmProgressBar.h"
//
//template<typename T> uiVizWidgetElm * createElement(string persistentId, string elementXML, uiVizWidgetBase* parent) { return new T(persistentId, elementXML, parent); }
//typedef std::map<std::string, uiVizWidgetElm*(*)(string persistentId, string elementXML, uiVizWidgetBase* parent)> element_map_type;
//
//
//
