#pragma once
#include "../uiViz/widget/uiVizWidgetTable.h"
#include "../uiViz/widget/uiVizWidgetSettings.h"

class uiVizWidgetNotifications : public Aquamarine::uiVizWidgetTable {
    
public:
    ofEvent<Aquamarine::uiVizWidgetEventArgs>     notificationItemsChanged;

    struct notificationItem {
        string type = "";
        string id = "";
        string title = "";
        string data = "";
        bool acknowledged = 0;
        bool deleted = 0;
        uint64_t dateAdded = -1;
        string datePublished = "";

        notificationItem(string type, string id, string title, string data, bool acknowledged, bool deleted, uint64_t dateAdded, string datePublished) : 
            type(type), id(id), title(title), data(data), acknowledged(acknowledged), deleted(deleted), dateAdded(dateAdded), datePublished(datePublished) {};
    };

    uiVizWidgetNotifications(string persistentId, string widgetXML) : uiVizWidgetTable(persistentId, widgetXML) {
        initWidget();
    }

    virtual ofxXmlSettings saveState() override {
        ofxXmlSettings mWidgetXML = uiVizWidget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS, 0);
        return mWidgetXML;
    }    
    
    virtual ~uiVizWidgetNotifications() {
    }

    bool populateLinks() {
        mNewItemsFound = false;

        vector<notificationItem> appUpdates = refreshAppUpdateNotificationFeed(false);
        vector<notificationItem> links = refreshLinksNotificationFeed(false);

        // Merge the vectors...
        std::vector<notificationItem> allNotifications(appUpdates);
        allNotifications.insert(allNotifications.end(), links.begin(), links.end());        

        std::vector<Aquamarine::uiVizWidgetTableRow> rows;         

        for (notificationItem item:allNotifications) {

            if(item.deleted) continue;

            Aquamarine::uiVizWidgetTableRow row(item.id, {
                Aquamarine::uiVizWidgetTableCell(
                    "", 
                    ""
                ),            
                Aquamarine::uiVizWidgetTableCell(
                    "", 
                    item.title
                ),
                Aquamarine::uiVizWidgetTableCell(
                    "", 
                    ""
                )               
            });
            row.setMetadata("TYPE", item.type);
            row.setMetadata("ID", item.id);
            row.setMetadata("data", item.data);
            row.setMetadata("published", item.datePublished);
            row.setMetadata("acknowledged", item.acknowledged ? "1" : "0");
            row.setMetadata("deleted", item.deleted ? "1" : "0");
            rows.push_back(row);  

            if (!mNewItemsFound && !item.deleted && !item.acknowledged) mNewItemsFound = true;
                
        }

        setHeaderRow(Aquamarine::uiVizWidgetTableRow("HEADER", {
            Aquamarine::uiVizWidgetTableCell(
                "ICON",
                "",
                60
            ),            
            Aquamarine::uiVizWidgetTableCell(
                "ITEM",
                "", 
                100, 
                250
            ),
            Aquamarine::uiVizWidgetTableCell(
                "DELETE",
                "",
                60
            )        

        }));
        setIsAutoResizeToContentsHeight(true);
        setRowHeight(60);
        setTableRows(rows);

        // Notify any listeners...
        Aquamarine::uiVizWidgetEventArgs args = Aquamarine::uiVizWidgetEventArgs(getWidgetId(), *this);
        ofNotifyEvent(notificationItemsChanged, args);

        return mNewItemsFound;
    } 

    bool getNewItemsFound() {
        return mNewItemsFound;
    }

    vector<notificationItem> refreshAppUpdateNotificationFeed(bool forceRefreshFromSource) {
        int MAX_NOTIFICATIONS = 3;
        int REFRESH_AFTER_THIS_MANY_HOURS = 23;        
  
        setNotificationLastChecked("appUpdate");
        addNotification(
            APP_CONSTANTS::APPLICATION_WEBSITE+"/download/1.1/linux", 
            "Cognition ver 1.1 update", 
            APP_CONSTANTS::APPLICATION_WEBSITE+"/download/1.1/linux", 
            "Not really", 
            "appUpdate"
        );

        pruneNotifications(MAX_NOTIFICATIONS, "appUpdate");
        return getNotifications("appUpdate");
    }

    vector<notificationItem> refreshLinksNotificationFeed(bool forceRefreshFromSource) {

        // WEBSITE IS DOWN!! Exit early..... ------------------------------------------------
        return vector<notificationItem>();
        // ----------------------------------------------------------------------------------

        int MAX_NOTIFICATIONS = 3;
        int REFRESH_AFTER_THIS_MANY_HOURS = 23;

        uint64_t epochLastCheck = getNotificationLastChecked("link");
        uint64_t epochNow = ofGetUnixTime();
        uint64_t secsSinceLastCheck = epochNow - epochLastCheck;
        float hoursSinceLastCheck = (float)secsSinceLastCheck/3600.0f;

        bool needToRefresh = (hoursSinceLastCheck > REFRESH_AFTER_THIS_MANY_HOURS || forceRefreshFromSource);

        if (needToRefresh) {
            ofHttpResponse resp = ofLoadURL(APP_CONSTANTS::APPLICATION_WEBSITE+"/feed");
            //cout << resp.data << endl;

            ofxXmlSettings newsXML;
            if (newsXML.loadFromBuffer(resp.data) && newsXML.pushTag("rss") && newsXML.pushTag("channel")) {
                setNotificationLastChecked("link");
                for (int i=0; i<newsXML.getNumTags("item"); i++) {
                    if (i > MAX_NOTIFICATIONS-1) break; // Only want a max of 10 items...
                    if (newsXML.pushTag("item", i)) {
                        string title = newsXML.getValue("title", "");
                        string link = newsXML.getValue("link", "");
                        string pubDate = newsXML.getValue("pubDate", "");                    
                        string description = newsXML.getValue("description", "");
                        newsXML.popTag();
                        // Persist it ...
                        addNotification(link, title, link, pubDate, "link");
                    }
                }
            } 
        }
        pruneNotifications(MAX_NOTIFICATIONS, "link");
        return getNotifications("link");
    }

    static vector<notificationItem> getNotifications(string notificationType) {
        vector<notificationItem> notifications;        
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            } 
            if (!settings.pushTag(notificationType)) {
                settings.addTag(notificationType);
                settings.pushTag(notificationType);
            }    
            for(int j=0; j<settings.getNumTags("item"); j++) {
                notifications.push_back(
                    notificationItem(
                        notificationType,
                        settings.getAttribute("item", "id", "", j),              
                        settings.getAttribute("item", "title", "", j),              
                        settings.getAttribute("item", "data", "", j),       
                        settings.getAttribute("item", "acknowledged", "0", j) == "1",
                        settings.getAttribute("item", "deleted", "0", j) == "1",
                        settings.getAttribute("item", "dateAdded", -1, j),
                        settings.getAttribute("item", "datePublished", "", j)                               
                    )
                );                
            }
        }
        return notifications;        
    }

    static uint64_t getNotificationLastChecked(string notificationType) {
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();        
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            }
            string num = settings.getAttribute(notificationType, "dateLastChecked", "0", 0); 
            return std::strtoul(num.c_str(), NULL, 0);
        }
        return -1;        
    }

    static void setNotificationLastChecked(string notificationType) {
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();        
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            }
            settings.setAttribute(notificationType, "dateLastChecked", ofToString(ofGetUnixTime()), 0);    
            settings.saveFile(Aquamarine::uiVizShared::getSettingsFileFullPath() );        
        }        
    }

    static bool acknowledgeNotification(string id, string notificationType, bool deleteItem) {
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            } 
            if (!settings.pushTag(notificationType)) {
                settings.addTag(notificationType);
                settings.pushTag(notificationType);
            }    
            bool idFound = false;
            int itemCount = settings.getNumTags("item");
            for(int j=0; j<itemCount; j++) {
                string existingId = settings.getAttribute("item", "id", "", j);
                if (existingId == id) { 
                    settings.setAttribute("item", "acknowledged", "1", j);  
                    if (deleteItem) settings.setAttribute("item", "deleted", "1", j);                       
                    settings.saveFile(Aquamarine::uiVizShared::getSettingsFileFullPath() );
                    return true;
                }
            }
        }
        return false;
    }

    static void addNotification(string id, string title, string data, string pubDate, string notificationType) {
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            } 
            if (!settings.pushTag(notificationType)) {
                settings.addTag(notificationType);
                settings.pushTag(notificationType);
            }

            bool idFound = false;
            int itemCount = settings.getNumTags("item");
            for(int j=0; j<itemCount; j++) {
                string existingId = settings.getAttribute("item", "id", "", j);
                if (existingId == id) { idFound = true; break; }
            }

            if (!idFound) {
                settings.popTag(); // notificationType
                settings.pushTag(notificationType);   
                settings.addTag("item");
                settings.setAttribute("item", "id", id, itemCount);                
                settings.setAttribute("item", "title", title, itemCount);                
                settings.setAttribute("item", "data", data, itemCount);         
                settings.setAttribute("item", "acknowledged", "0", itemCount);  
                settings.setAttribute("item", "deleted", "0", itemCount);  
                settings.setAttribute("item", "dateAdded", ofToString(ofGetUnixTime()), itemCount);
                settings.setAttribute("item", "datePublished", pubDate, itemCount);                          
                settings.saveFile(Aquamarine::uiVizShared::getSettingsFileFullPath() );                
            }
        }
    }

    static void pruneNotifications(int maxItems, string notificationType) {
        ofxXmlSettings settings = Aquamarine::uiVizWidgetSettings::getSettings();
        if (settings.pushTag("settings")) {
            if (!settings.pushTag("notifications")) {
                settings.addTag("notifications");
                settings.pushTag("notifications");
            } 
            if (!settings.pushTag(notificationType)) {
                settings.addTag(notificationType);
                settings.pushTag(notificationType);
            }
            
            int from = max(0, (int)maxItems); 
            int total = settings.getNumTags("item");
            for(int j=from; j<total; j++) {
                settings.removeTag("item", j);
            }
            settings.saveFile(Aquamarine::uiVizShared::getSettingsFileFullPath() );                

        }
    }     

    virtual void onWidgetEventReceived(Aquamarine::uiVizWidgetEventArgs &args) override {
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId()) {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED) {
                Aquamarine::uiVizWidgetTableRow* eventRow = getTableRow(args.eventXML);
                Aquamarine::uiVizWidgetTableCell* eventCell = getTableCell(args.eventXML);
                if (!eventRow || !eventCell) return;

                Aquamarine::uiVizCoord::vizPoint p = getTableRowAndColForEvent(args.eventXML);

                string type = eventRow->getMetadata("TYPE");
                string id = eventRow->getMetadata("ID");
                string headerRowKey = getHeaderCellByIndex(p.x).key;

                if (headerRowKey == "ICON" || headerRowKey == "ITEM") {
                    if(type == "link") {
                        string link = eventRow->getMetadata("data");
                        acknowledgeNotification(id, type, false);
                        ofLaunchBrowser(link, false);
                    } else if(type == "appUpdate") {
                        string link = eventRow->getMetadata("data");
                        acknowledgeNotification(id, type, false);
                        ofLaunchBrowser(link, false);
                    } 
                    clearSelectedRows();
                    populateLinks();
                    closeThisWidget();                    
                } else if (headerRowKey == "DELETE") {
                    acknowledgeNotification(id, type, true);
                    clearSelectedRows();
                    populateLinks();
                }



            }
        }
    }    
//delete logic 
//refresh in title 
//dot anim - alternat 4x colours and fade from 0-1 apha
// generecise

// theme change

    virtual void drawCellContent(bool isRowSelected, bool isRowHovered, bool isCellHovered, int absoluteScaledX, int absoluteScaledY, int absoluteScaledLabelX, int absoluteScaledLabelY, int scaledWidth, int scaledHeight, Aquamarine::uiVizWidgetTableRow& row, Aquamarine::uiVizWidgetTableCell& cell, int rowIndex, int colIndex) override {

        bool acknowledged = row.getMetadata("acknowledged") == "1";
        float alpha = (acknowledged ? 0.7f : 1.0f);
        ofColor color = (acknowledged ? getTheme().TypographyPrimaryColor_withAlpha(alpha) : getTheme().WidgetAccentHighContrast2Color_withAlpha(alpha));

        if (getHeaderCellByIndex(colIndex).key == "ICON") {
            if (row.getMetadata("TYPE") == "appUpdate") {
                iconDownload.setColor(color);
                iconDownload.setScaledPos(absoluteScaledX + scale(12), absoluteScaledY + scale(12));
                iconDownload.drawSvg();
            } else if (row.getMetadata("TYPE") == "link")  {
                iconLink.setColor(color);
                iconLink.setScaledPos(absoluteScaledX + scale(12), absoluteScaledY + scale(12));
                iconLink.drawSvg();
            }
        }

        if (getHeaderCellByIndex(colIndex).key == "ITEM") {
            ofPushStyle();
            ofSetColor(color);
            getFont()->draw(cell.label, absoluteScaledLabelX, absoluteScaledLabelY);
            ofPopStyle();
        }

        if (getHeaderCellByIndex(colIndex).key == "DELETE") {
            iconClose.setScaledPos(
                absoluteScaledX+(scaledWidth-iconClose.getScaledBounds().width)/2.0f, 
                absoluteScaledY+(scaledHeight-iconClose.getScaledBounds().height)/2.0f
            );
            Aquamarine::uiVizElm vizElm_cell;
            vizElm_cell.setRectangle(absoluteScaledX, absoluteScaledY, scaledWidth, scaledHeight);
            if(vizElm_cell.isHovered_Rect()) {
                vizElm_cell.setColor(ofColor(255, 0, 0, 180));
                vizElm_cell.draw();                
                iconClose.setColor(getTheme().TypographyPrimaryColor_withAlpha(1));
            } else {
                vizElm_cell.setColor(ofColor::blue);                
                iconClose.setColor(getTheme().TypographyPrimaryColor_withAlpha(0.7f));
            }
            iconClose.drawSvg();
        }
    }    

    virtual void drawCellHighlight_Selected(bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, Aquamarine::uiVizWidgetTableRow& row, Aquamarine::uiVizWidgetTableCell& cell, int rowIndex, int colIndex) {
        Aquamarine::uiVizElm vizElm_cell;
        vizElm_cell.setRectangle(
            absoluteScaledX, absoluteScaledY,
            scaledWidth, scaledHeight,
            getCellSelectionColor()
        );
        vizElm_cell.draw();
    }          
 

    
private:
    Aquamarine::uiVizIcon iconLink, iconDownload, iconClose; 
    bool mNewItemsFound = false;

    void initWidget() override {  

        iconLink = Aquamarine::uiVizIconCache::getIcon("REG_INFO");
        iconDownload = Aquamarine::uiVizIconCache::getIcon("REG_NEW_RELEASE"); 
        iconClose = Aquamarine::uiVizIconCache::getIcon("REG_WIDGET_CLOSE"); 

        iconLink.scaleSvg(2, 2); 
        iconDownload.scaleSvg(2, 2); 
        

        setDrawWidgetChrome(true);
        setStaticBottomTitleBarSize(40);
        setEnableScroll(false);

        populateLinks();
        setTitle("");
    }
};


