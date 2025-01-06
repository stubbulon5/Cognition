#pragma once
#include "ofxAquamarine.h"
using json = nlohmann::json;

class WidgetNotifications : public Aquamarine::WidgetTable
{

public:
    ofEvent<Aquamarine::WidgetEventArgs> notificationItemsChanged;

    struct notificationItem
    {
        string type = "";
        string id = "";
        string title = "";
        string data = "";
        bool acknowledged = 0;
        bool deleted = 0;
        uint64_t dateAdded = -1;
        string datePublished = "";

        notificationItem(string type, string id, string title, string data, bool acknowledged, bool deleted, uint64_t dateAdded, string datePublished) : type(type), id(id), title(title), data(data), acknowledged(acknowledged), deleted(deleted), dateAdded(dateAdded), datePublished(datePublished) {};
    };

    WidgetNotifications(string persistentId, string widgetXML) : WidgetTable(persistentId, widgetXML)
    {
        initWidget();
    }

    virtual ofxXmlSettings saveState() override
    {
        ofxXmlSettings mWidgetXML = Widget::saveState();
        mWidgetXML.setAttribute("widget", "class", APP_CONSTANTS::WIDGET_CLASS_NOTIFICATIONS, 0);
        return mWidgetXML;
    }

    virtual ~WidgetNotifications()
    {
    }

    bool populateLinks()
    {
        mNewItemsFound = false;

        vector<notificationItem> appUpdates = refreshAppUpdateNotificationFeed(false);
        vector<notificationItem> links = refreshLinksNotificationFeed(false);

        // Merge the vectors...
        std::vector<notificationItem> allNotifications(appUpdates);
        allNotifications.insert(allNotifications.end(), links.begin(), links.end());

        std::vector<Aquamarine::WidgetTableRow> rows;

        for (notificationItem item : allNotifications)
        {

            if (item.deleted)
                continue;

            Aquamarine::WidgetTableRow row(item.id, {Aquamarine::WidgetTableCell(
                                                         "",
                                                         ""),
                                                     Aquamarine::WidgetTableCell(
                                                         "",
                                                         item.title),
                                                     Aquamarine::WidgetTableCell(
                                                         "",
                                                         "")});
            row.setMetadata("TYPE", item.type);
            row.setMetadata("ID", item.id);
            row.setMetadata("data", item.data);
            row.setMetadata("published", item.datePublished);
            row.setMetadata("acknowledged", item.acknowledged ? "1" : "0");
            row.setMetadata("deleted", item.deleted ? "1" : "0");
            rows.push_back(row);

            if (!mNewItemsFound && !item.deleted && !item.acknowledged)
                mNewItemsFound = true;
        }

        setHeaderRow(Aquamarine::WidgetTableRow("HEADER", {Aquamarine::WidgetTableCell(
                                                               "ICON",
                                                               "",
                                                               60),
                                                           Aquamarine::WidgetTableCell(
                                                               "ITEM",
                                                               "",
                                                               100,
                                                               250),
                                                           Aquamarine::WidgetTableCell(
                                                               "DELETE",
                                                               "",
                                                               60)

                                                          }));
        setIsAutoResizeToContentsHeight(true);
        setRowHeight(60);
        setTableRows(rows);

        // Notify any listeners...
        Aquamarine::WidgetEventArgs args = Aquamarine::WidgetEventArgs(getWidgetId(), *this);
        ofNotifyEvent(notificationItemsChanged, args);

        return mNewItemsFound;
    }

    bool getNewItemsFound()
    {
        return mNewItemsFound;
    }

    vector<notificationItem> refreshAppUpdateNotificationFeed(bool forceRefreshFromSource)
    {
        int MAX_NOTIFICATIONS = 5;
        int REFRESH_AFTER_THIS_MANY_HOURS = 23;

        setNotificationLastChecked("appUpdate");
        addNotification(
            APP_CONSTANTS::APPLICATION_WEBSITE + "/download/1.1/linux",
            "Cognition ver 1.1 update",
            APP_CONSTANTS::APPLICATION_WEBSITE + "/download/1.1/linux",
            "Not really",
            "appUpdate");

        addNotification(
            APP_CONSTANTS::APPLICATION_WEBSITE + "/download/1.1/linux2",
            "Cognition ver 1.1 update222",
            APP_CONSTANTS::APPLICATION_WEBSITE + "/download/1.1/linux2",
            "Not really222",
            "appUpdate");


        pruneNotifications(MAX_NOTIFICATIONS, "appUpdate");
        return getNotifications("appUpdate");
    }

    vector<notificationItem> refreshLinksNotificationFeed(bool forceRefreshFromSource)
    {

        // WEBSITE IS DOWN!! Exit early..... ------------------------------------------------
        return vector<notificationItem>();
        // ----------------------------------------------------------------------------------

        int MAX_NOTIFICATIONS = 3;
        int REFRESH_AFTER_THIS_MANY_HOURS = 23;

        uint64_t epochLastCheck = getNotificationLastChecked("link");
        uint64_t epochNow = std::time(nullptr);
        uint64_t secsSinceLastCheck = epochNow - epochLastCheck;
        float hoursSinceLastCheck = (float)secsSinceLastCheck / 3600.0f;

        bool needToRefresh = (hoursSinceLastCheck > REFRESH_AFTER_THIS_MANY_HOURS || forceRefreshFromSource);

        if (needToRefresh)
        {
            ofHttpResponse resp = ofLoadURL(APP_CONSTANTS::APPLICATION_WEBSITE + "/feed");
            // cout << resp.data << endl;

            ofxXmlSettings newsXML;
            if (newsXML.loadFromBuffer(resp.data) && newsXML.pushTag("rss") && newsXML.pushTag("channel"))
            {
                setNotificationLastChecked("link");
                for (int i = 0; i < newsXML.getNumTags("item"); i++)
                {
                    if (i > MAX_NOTIFICATIONS - 1)
                        break; // Only want a max of 10 items...
                    if (newsXML.pushTag("item", i))
                    {
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

    static void ensureSettingsObj(json &settings)
    {
        if (!settings.contains("settings"))
            settings["settings"] = nullptr;
        if (!settings["settings"].contains("notifications"))
            settings["settings"]["notifications"] = nullptr;
    }

    static vector<notificationItem> getNotifications(string notificationType)
    {
        vector<notificationItem> notifications;
        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains(notificationType))
            sett["settings"]["notifications"][notificationType] = {};

        auto ary = sett["settings"]["notifications"][notificationType];

        for (auto &item : ary.items())
        {
            json *obj = &item.value();

            string id;
            obj->at("id").get_to(id);
            string title;
            obj->at("title").get_to(title);
            string data;
            obj->at("data").get_to(data);
            bool acknowledged;
            obj->at("acknowledged").get_to(acknowledged);
            bool deleted;
            obj->at("deleted").get_to(deleted);
            uint64_t dateAdded;
            obj->at("dateAdded").get_to(dateAdded);
            string datePublished;
            obj->at("datePublished").get_to(datePublished);

            notifications.push_back(
                notificationItem(
                    notificationType,
                    id,
                    title,
                    data,
                    acknowledged,
                    deleted,
                    dateAdded,
                    datePublished));
        }
        return notifications;
    }

    static uint64_t getNotificationLastChecked(string notificationType)
    {
        vector<notificationItem> notifications;
        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains("dateLastChecked"))
            sett["settings"]["notifications"]["dateLastChecked"] = "0";

        string num = "0";

        sett["settings"]["notifications"]["dateLastChecked"].get_to(num);
        return std::strtoul(num.c_str(), NULL, 0);
    }

    static void setNotificationLastChecked(string notificationType)
    {
        vector<notificationItem> notifications;
        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains("dateLastChecked"))
            sett["settings"]["notifications"]["dateLastChecked"] = "0";

        // Get epoch
        std::time_t result = std::time(nullptr);

        sett["settings"]["notifications"]["dateLastChecked"] = result;

        // Save the file
        std::ofstream ofs(Aquamarine::Shared::getSettingsFileFullPath());
        ofs << sett;
    }

    static bool acknowledgeNotification(string id, string notificationType, bool deleteItem)
    {
        vector<notificationItem> notifications;
        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains(notificationType))
            sett["settings"]["notifications"][notificationType] = {};


        for (auto& [key, value] : sett["settings"]["notifications"][notificationType].items()) {
            std::cout << key << " : " << value << "\n";

            if (value["id"] == id)
            {
                value["acknowledged"] = true;
                if (deleteItem)
                    value["deleted"] =  true;

                // Save the file
                std::ofstream ofs(Aquamarine::Shared::getSettingsFileFullPath());
                ofs << sett;

                return true;
            }
        }        

        return false;
    }

    static void addNotification(string id, string title, string data, string pubDate, string notificationType)
    {
        vector<notificationItem> notifications;
        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains(notificationType))
            sett["settings"]["notifications"][notificationType] = json::array();

        for (const auto &item : sett["settings"]["notifications"][notificationType].items())
        {

            string existingId;
            item.value()["id"].get_to(existingId);
            string title;

            if (existingId == id)
            {
                // Already there!
                return;
            }
        }

        json newItem = {
            {"id", id},
            {"title", title},
            {"data", data},
            {"acknowledged", false},
            {"deleted", false},
            {"dateAdded", std::time(nullptr)},
            {"datePublished", pubDate}};

        sett["settings"]["notifications"][notificationType].push_back(newItem);

        // Save the file
        std::ofstream ofs(Aquamarine::Shared::getSettingsFileFullPath());
        ofs << sett;
    }

    static void pruneNotifications(int maxItems, string notificationType)
    {
        vector<notificationItem> notifications = getNotifications(notificationType);
        vector<json> notificationsToSave;

        int added = 0;
        for (notificationItem n : notifications)
        {
            if (added >= maxItems)
                continue;

            notificationsToSave.push_back({{"id", n.id},
                                            {"title", n.title},
                                            {"data", n.data},
                                            {"acknowledged", n.acknowledged},
                                            {"deleted", n.deleted},
                                            {"dateAdded", n.dateAdded},
                                            {"datePublished", n.datePublished}}

            );
            added++;
        }

        json sett = Aquamarine::WidgetSettings::getSettingsJson();
        ensureSettingsObj(sett);

        if (!sett["settings"]["notifications"].contains(notificationType))
            sett["settings"]["notifications"][notificationType] = {};

        sett["settings"]["notifications"][notificationType] = notificationsToSave;

        // Save the file
        std::ofstream ofs(Aquamarine::Shared::getSettingsFileFullPath());
        ofs << sett;
    }

    virtual void onWidgetEventReceived(Aquamarine::WidgetEventArgs &args) override
    {
        string event = args.getFullEventName();
        if (args.sender.getPersistentId() == getPersistentId())
        {
            if (args.eventName == Aquamarine::WIDGET_EVENT::TABLE_CELL_SELECTED)
            {
                Aquamarine::WidgetTableRow *eventRow = getTableRow(args.eventXML);
                Aquamarine::WidgetTableCell *eventCell = getTableCell(args.eventXML);
                if (!eventRow || !eventCell)
                    return;

                Aquamarine::Coord::vizPoint p = getTableRowAndColForEvent(args.eventXML);

                string type = eventRow->getMetadata("TYPE");
                string id = eventRow->getMetadata("ID");
                string headerRowKey = getHeaderCellByIndex(p.x).key;

                if (headerRowKey == "ICON" || headerRowKey == "ITEM")
                {
                    if (type == "link")
                    {
                        string link = eventRow->getMetadata("data");
                        acknowledgeNotification(id, type, false);
                        ofLaunchBrowser(link, false);
                    }
                    else if (type == "appUpdate")
                    {
                        string link = eventRow->getMetadata("data");
                        acknowledgeNotification(id, type, false);
                        ofLaunchBrowser(link, false);
                    }
                    clearSelectedRows();
                    populateLinks();
                    closeThisWidget();
                }
                else if (headerRowKey == "DELETE")
                {
                    acknowledgeNotification(id, type, true);
                    clearSelectedRows();
                    populateLinks();
                }
            }
        }
    }

    virtual void drawCellContent(bool isRowSelected, bool isRowHovered, bool isCellHovered, int absoluteScaledX, int absoluteScaledY, int absoluteScaledLabelX, int absoluteScaledLabelY, int scaledWidth, int scaledHeight, Aquamarine::WidgetTableRow &row, Aquamarine::WidgetTableCell &cell, int rowIndex, int colIndex) override
    {

        bool acknowledged = row.getMetadata("acknowledged") == "1";
        float alpha = (acknowledged ? 0.7f : 1.0f);
        ofColor color = (acknowledged ? getTheme().TypographyPrimaryColor_withAlpha(alpha) : getTheme().WidgetAccentHighContrast2Color_withAlpha(alpha));

        if (getHeaderCellByIndex(colIndex).key == "ICON")
        {
            if (row.getMetadata("TYPE") == "appUpdate")
            {
                iconDownload.setColor(color);
                iconDownload.setScaledPos(absoluteScaledX + scale(12), absoluteScaledY + scale(12));
                iconDownload.drawSvg();
            }
            else if (row.getMetadata("TYPE") == "link")
            {
                iconLink.setColor(color);
                iconLink.setScaledPos(absoluteScaledX + scale(12), absoluteScaledY + scale(12));
                iconLink.drawSvg();
            }
        }

        if (getHeaderCellByIndex(colIndex).key == "ITEM")
        {
            ofPushStyle();
            ofSetColor(color);
            getFont()->draw(cell.label, absoluteScaledLabelX, absoluteScaledLabelY);
            ofPopStyle();
        }

        if (getHeaderCellByIndex(colIndex).key == "DELETE")
        {
            iconClose.setScaledPos(
                absoluteScaledX + (scaledWidth - iconClose.getScaledBounds().width) / 2.0f,
                absoluteScaledY + (scaledHeight - iconClose.getScaledBounds().height) / 2.0f);
            Aquamarine::Elm vizElm_cell;
            vizElm_cell.setRectangle(absoluteScaledX, absoluteScaledY, scaledWidth, scaledHeight);
            if (vizElm_cell.isHovered_Rect())
            {
                vizElm_cell.setColor(ofColor(255, 0, 0, 180));
                vizElm_cell.draw();
                iconClose.setColor(getTheme().TypographyPrimaryColor_withAlpha(1));
            }
            else
            {
                vizElm_cell.setColor(ofColor::blue);
                iconClose.setColor(getTheme().TypographyPrimaryColor_withAlpha(0.7f));
            }
            iconClose.drawSvg();
        }
    }

    virtual void drawCellHighlight_Selected(bool isRowSelected, bool isRowHovered, int absoluteScaledX, int absoluteScaledY, int scaledWidth, int scaledHeight, Aquamarine::WidgetTableRow &row, Aquamarine::WidgetTableCell &cell, int rowIndex, int colIndex)
    {
        Aquamarine::Elm vizElm_cell;
        vizElm_cell.setRectangle(
            absoluteScaledX, absoluteScaledY,
            scaledWidth, scaledHeight,
            getCellSelectionColor());
        vizElm_cell.draw();
    }

private:
    Aquamarine::Icon iconLink, iconDownload, iconClose;
    bool mNewItemsFound = false;

    void initWidget() override
    {

        iconLink = Aquamarine::IconCache::getIcon("REG_INFO");
        iconDownload = Aquamarine::IconCache::getIcon("REG_NEW_RELEASE");
        iconClose = Aquamarine::IconCache::getIcon("REG_WIDGET_CLOSE");

        iconLink.scaleSvg(2, 2);
        iconDownload.scaleSvg(2, 2);

        setDrawWidgetChrome(true);
        setStaticBottomTitleBarSize(40);
        setEnableScroll(false);

        populateLinks();
        setTitle("");
    }
};
