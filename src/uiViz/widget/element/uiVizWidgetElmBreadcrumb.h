#pragma once
#include "../uiVizWidget.h"



class uiVizWidgetElmBreadcrumbItemSlice {
public:
    uiVizCoord::vizBounds fontRect = uiVizCoord::vizBounds(0, 0, 0, 0);   
    uiVizCoord::vizBounds bounds = uiVizCoord::vizBounds(0, 0, 0, 0);
    uiVizElm button;
    ofColor regularColor;
    ofColor selectedColor;
    ofColor hoveredColor;
    ofColor regularFontColor;
    ofColor selectedFontColor;
    ofColor hoveredFontColor;
    ofColor disabledFontColor;

    float currentAlpha = 0.0f;

    bool isHovered() {
        int mX = ofGetMouseX();
        int mY = ofGetMouseY();
        return mX > button.getRectangle().x && mY > button.getRectangle().y && mX < button.getRectangle().x + button.getRectangle().width && mY < button.getRectangle().y + button.getRectangle().height;
    }

    uiVizWidgetElmBreadcrumbItemSlice() {};

    ~uiVizWidgetElmBreadcrumbItemSlice() {
    }
};


class uiVizWidgetElmBreadcrumbItem {
public:
    string label = "";
    string key = "";
    vector<string> metadata;
    bool isSelected = false;
    uiVizWidgetElmBreadcrumbItemSlice breadcrumbSlice = uiVizWidgetElmBreadcrumbItemSlice();

    uiVizWidgetElmBreadcrumbItem(string key, string label) : key(key), label(label) {};
    uiVizWidgetElmBreadcrumbItem(string key, string label, vector<string> metadata) : key(key), label(label), metadata(metadata) {};

    ~uiVizWidgetElmBreadcrumbItem() {
    }
};

class uiVizWidgetElmBreadcrumb : public uiVizWidgetElm {

public:

    uiVizWidgetElmBreadcrumb(string persistentId, string widgetXML, uiVizWidgetBase* parent) : uiVizWidgetElm(persistentId, widgetXML, parent) {
        initWidget();
        loadState(widgetXML);
    }
    
/*! Inside \<element>:\n
    \<items>\n
    \<item key="Item_1">Item 1\</item>\n
    \<item key="Item_2">Item 2\</item>\n
    \<item key="Item_3">Item 3\</item>\n
    \</items>\n
*/
    virtual bool loadState(string widgetXML) override {
        uiVizWidgetElm::loadState(widgetXML);
        ofxXmlSettings settings = ofxXmlSettings();
        
        if (!settings.loadFromBuffer(widgetXML.c_str())) {
            return false;
        }
        
        settings.pushTag("element");

        setIconTag(settings.getAttribute("properties", "icon", "REG_REG_PLAY_BUTTON"));
        mSelectedIndex = 0;
        if (settings.pushTag("items")) {
            vector<uiVizWidgetElmBreadcrumbItem> items = vector<uiVizWidgetElmBreadcrumbItem>();
            for (int j=0; j< settings.getNumTags("item"); j++) {
                items.push_back(
                    uiVizWidgetElmBreadcrumbItem(
                        settings.getAttribute("item", "key", "HC" + ofToString(j), j),
                        settings.getValue("item", "", j)
                    )
                );
                mSelectedIndex++;
            }
            setBreadcrumbItemItems(items);
            settings.popTag(); // items
        }        
        
        // Get some values here
        settings.popTag();
        
        return true;
    }
    
    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidgetElm::saveState();

        mWidgetXML.setAttribute("element", "class", WIDGET_ELM_CLASS::BREADCRUMB, 0);
        
        mWidgetXML.pushTag("element");
        // Populate some values here
        mWidgetXML.popTag();
        
        return mWidgetXML;
    }
    
    virtual ~uiVizWidgetElmBreadcrumb() {
    }




    virtual void update(uiVizWidgetContext context) override {
        int accumWidth = 0;
        int index = 0;

        getIsRoundedRectangle() ? breadcrumbBG.setRectRounded(getViz()->scale(getX()), getViz()->scale(getY()), getViz()->scale(getWidth()), getViz()->scale(getHeight()), scale(5), getTheme().ElementBackgroundColor_withAlpha(getTheme().ElementUnhoveredBackgroundAlpha)) :
            breadcrumbBG.setRectangle(getViz()->scale(getX()), getViz()->scale(getY()), getViz()->scale(getWidth()), getViz()->scale(getHeight()), getTheme().ElementBackgroundColor_withAlpha(getTheme().ElementUnhoveredBackgroundAlpha));

        for(uiVizWidgetElmBreadcrumbItem& item:mBreadcrumbItemItems) {

            int x = getViz()->scale(getUsableX())-getScaledPadding()+accumWidth;
            int y = getViz()->scale(getY());
            
            fontStyle = uiVizShared::getViz()->getLargeFontStyle();            
            ofRectangle fontRect = uiVizShared::getViz()->getTextBounds(item.label, fontStyle, x, y); 
            
            item.breadcrumbSlice.fontRect = uiVizCoord::vizBounds(x, y, fontRect.width, fontRect.height);

            int cellWidth = item.breadcrumbSlice.fontRect.width + ((getIconTag() != "") ? icon.getScaledBounds().width + getScaledPadding()*1.0 : getScaledPadding()*1.0);

            getIsRoundedRectangle() ? item.breadcrumbSlice.button.setRectRounded(x, y, cellWidth, getViz()->scale(getHeight()), scale(5), getTheme().ElementBackgroundColor_withAlpha(getCurrentBackgroundAlpha())) :
                item.breadcrumbSlice.button.setRectangle(x, y, cellWidth, getViz()->scale(getHeight()), getTheme().ElementBackgroundColor_withAlpha(getCurrentBackgroundAlpha()));

            accumWidth += cellWidth;
            
            if (index >= mSelectedIndex) break;
            index++;

        } 

        setContentBoundsScaled(uiVizCoord::vizBounds(
                    getContentBoundsScaled().x,
                    getContentBoundsScaled().y,
                    accumWidth + getScaledPadding(), 
                    getUsableHeight()
                    ));

        if (mBreadcrumbItemItemsChanged) {
            scrollX_End();
            mBreadcrumbItemItemsChanged = false;
        }
    }

    void onWidgetResized(int width, int height) override {
        mBreadcrumbItemItemsChanged = true;
    }    

    virtual void draw(uiVizWidgetContext context) override {

        breadcrumbBG.draw();

        vector<uiVizWidgetElmBreadcrumbItem> items = getBreadcrumbItems();
        int index = 0;
        for(uiVizWidgetElmBreadcrumbItem& item:items) {

            bool isHovered = item.breadcrumbSlice.button.isHovered_Rect() && getIsEnabled();

            item.breadcrumbSlice.button.setColor(getTheme().ElementBackgroundColor_withAlpha((isHovered ? getCurrentBackgroundAlpha() : getTheme().ElementUnhoveredBackgroundAlpha)));
            if (isHovered) {
                item.breadcrumbSlice.button.draw();
            }

            ofPushStyle();               
            ofSetColor(getTheme().ElementForegroundColor_withAlpha((isHovered ? getCurrentForegroundAlpha() : getTheme().ElementUnhoveredForegroundAlpha)));

            int iconHeight = icon.getScaledBounds().height/2;
            int buttonHeight =  item.breadcrumbSlice.button.getRectangle().height/2;
            int offset = (iconHeight*0.5f + buttonHeight*0.5f)*0.5f;

            if (getIconTag() != "" && index > 0) {
                icon.setScaledPos(
                    item.breadcrumbSlice.fontRect.x, 
                    item.breadcrumbSlice.button.getRectangle().y + offset
                );
                icon.drawSvg();
            }
            
            fontStyle.color = getTheme().TypographyPrimaryColor_withAlpha(getTheme().ElementHoveredForegroundAlpha);

            getViz()->getFonts(getTheme())->draw(
                item.label, 
                fontStyle, 
                item.breadcrumbSlice.fontRect.x + ((getIconTag() != "") ? icon.getScaledBounds().width : getScaledPadding()*1.0f), 
                item.breadcrumbSlice.fontRect.y + item.breadcrumbSlice.fontRect.height*0.25f + scale(getUsableHeight()*0.5f)
            );
            ofPopStyle();               

            
            if (isHovered && getIsMousePressedAndReleasedOverWidget(false)) {
                press(index);
            }

            if (index >= mSelectedIndex) break;
            index++;
        } 
    }
    
    void press(int index) {
        index = min(index, (int)getBreadcrumbItems().size()-1);
        mSelectedIndex = index;
        string key = getBreadcrumbItemKeyString(index);
        parent()->eventTransmit(getPersistentId(), WIDGET_EVENT::CLICK, "<event index=\"" +  ofToString(index)  + "\">" + uiVizShared::encodeForXML(key) + "</event>", *this);
        mBreadcrumbItemItemsChanged = true;
        setNeedsUpdate(true);
    }
    
    void setIconTag(string val) {
        mIconTag = val;
        icon = uiVizIconCache::getIcon(val);
    }

    string getIconTag() {
        return mIconTag;
    }

     vector<uiVizWidgetElmBreadcrumbItem> getBreadcrumbItems() {
        return mBreadcrumbItemItems;
    }

    string getBreadcrumbItemKeyString(int index) {
        vector<uiVizWidgetElmBreadcrumbItem> breadcrumbItems = getBreadcrumbItems();
        index = min(index, (int)breadcrumbItems.size()-1);
        string retVal = "";
        for (int i=0; i<=index; i++) {
            retVal += mDelimiter + breadcrumbItems[i].key;
        }
        return retVal;
    }    

     void setBreadcrumbItemItems(string delimitedItems, string delimiter) {
         mDelimiter = delimiter;
         vector<string> items = ofSplitString(delimitedItems, delimiter);
         vector<uiVizWidgetElmBreadcrumbItem> breadcrumbItems = vector<uiVizWidgetElmBreadcrumbItem>();
         int index = -1;
         for (string item:items) {
                if (item == "") continue; 
                breadcrumbItems.push_back(
                    uiVizWidgetElmBreadcrumbItem(
                        item,
                        item
                    )
                );
                index++;
                mSelectedIndex = index;
         }
        setBreadcrumbItemItems(breadcrumbItems);
    }       

    void setBreadcrumbItemItems(vector<uiVizWidgetElmBreadcrumbItem> items) {
        mBreadcrumbItemItems = items;
        mBreadcrumbItemItemsChanged = true;
        setNeedsUpdate(true);
        setWidgetNeedsUpdate(true);
    }

private:
    
    uiVizElm breadcrumbBG;

    string mIconTag = "REG_REG_PLAY_BUTTON";
    string mDelimiter = "|";
    int mSelectedIndex = 0;

    ofRectangle titleRect;
    ofxFontStash2::Style fontStyle;
    uiVizIcon icon;
    bool mBreadcrumbItemItemsChanged = true;

    vector<uiVizWidgetElmBreadcrumbItem> mBreadcrumbItemItems;

    void initWidget() override {
        setWidth(100);
        setEnableScrollYPositive(false);
        setEnableScrollYNegative(false);
        setEnableScrollXPositive(true);
        setEnableScrollXNegative(true);
        setScrollAction(ScrollAction::SCROLL);

    }

};