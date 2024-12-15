//
//  uiVizMainMenu.h
//  bloom-macos
//
//  Created by Stuart Barnes on 12/04/2019.
//
#pragma once
#include "../uiViz/widget/uiVizWidget.h"
#include "appConstants.h"


struct Licence {
    bool isValid = false;
    string invalidLicenceReason = "Unknown reason...";
    string invalidLicenceCode = "UNKNOWN";
    string detailedErrorMessage = "";

    string username = "";
    string password = "";
    string issued_licence = "";
    string machineid = "";
    string token = "";
    uint64_t reauthorize_epoch = 0;
    
    int allowedAppMajorVersion = 0;
    int allowedAppMinorVersion = 0;
    
    string licenceXML = "";
    
    Licence(bool isValid) : isValid(isValid) {};
    
    static bool validateLicence(Licence& licence, bool fullValidation) {

        /*******************************************************
         * FULL LICENCE VALIDATION  
         *******************************************************/

        // TODO : if still inside reauthorize_epoch, early exit ....

        if (fullValidation) {
            string LICENCE_valid_until_version = "0.0.0";
            uint64_t LICENCE_valid_until_epoch = 0;
            string LICENCE_str = "";
            
            /************ User Credentials / token ************/
            if (licence.username == "") {
                licence.invalidLicenceCode = "USERNAME_NOT_PROVIDED";
                licence.invalidLicenceReason = "Username not provided";
                licence.isValid = false;
                return false;
            }

            if (licence.password == "") {
                licence.invalidLicenceCode = "PASSWORD_NOT_PROVIDED";
                licence.invalidLicenceReason = "Password not provided";
                licence.isValid = false;
                return false;
            }     

            if (licence.issued_licence == "") {
                licence.invalidLicenceCode = "LICENCE_NOT_PROVIDED";
                licence.invalidLicenceReason = "Licence not provided";
                licence.isValid = false;
                return false;
            }                                      
            
            /************ User Credentials / token ************/
            if (licence.token == "") {
                licence.invalidLicenceCode = "EXPIRED_TOKEN";
                licence.invalidLicenceReason = "Please sign in...";
                licence.isValid = false;
                return false;
            }

            /************ Licence Key validation ************/
            vector<string> licence_parts = ofSplitString(licence.issued_licence, "-");
            if (licence_parts.size() != 3) {
                licence.invalidLicenceCode = "LICENCE_KEY_MALFORMED";
                licence.invalidLicenceReason = "Licence Key should be comprised of 3 parts: ${valid_until_version}-${date_issued_epoch}-${random_10_char_string}";
                licence.isValid = false;
                return false;
            } else {
                LICENCE_valid_until_version = licence_parts[0];
                LICENCE_valid_until_epoch = ofToInt64(licence_parts[1]);
                LICENCE_str = licence_parts[2];
            }
            
            licence.allowedAppMajorVersion = uiVizWidgetManager::getAppMajorVersion(LICENCE_valid_until_version);
            licence.allowedAppMinorVersion = uiVizWidgetManager::getAppMinorVersion(LICENCE_valid_until_version);
            
            int currentAppMajorVersion = uiVizWidgetManager::getAppMajorVersion(APP_CONSTANTS::APPLICATION_VERSION);
            int currentAppMinorVersion = uiVizWidgetManager::getAppMinorVersion(APP_CONSTANTS::APPLICATION_VERSION);
            
            if (licence.allowedAppMajorVersion < currentAppMajorVersion ||
                (licence.allowedAppMajorVersion == currentAppMajorVersion && licence.allowedAppMinorVersion < currentAppMinorVersion)) {
                licence.invalidLicenceCode = "LICENCE_KEY_EXPIRED_VER";
                licence.invalidLicenceReason = "Licence is valid for an older version. Please upgrade your licence or download version " + ofToString(licence.allowedAppMajorVersion) + "." + ofToString(licence.allowedAppMinorVersion);
                licence.isValid = false;
                return false;
            }
            
            /************ Licence Key remote authorization ************/
            if (!REMOTE_validateLicence(licence)) {
                licence.isValid = false;
                return false;
            }

            /*
            if (exceeded_epoch_check date) {
            
            if(check_was_valid) {
            licence.isValid = true;
            refresh empoch refresh date to today + 14
            }
            
            if ()
            }
            */
            
            // check in with server here...
            //things to check:
            // username and password match
            // licence >= current app ver num
            // not deployed to more than 5 machines (machine id)
            
            // if expired last checked, (eg 14 days) check in online...
            // ensure not comprimised
            // update last checked and persist
            
            // else check
            
            /* PSEUDO CODE:
            
            
            // Check all fields of XML file to see if they have a value
            
            
            // Decode the Licence field to something like [valid_version]-[epochdate_expire]-[random_10_char_string]
            // Check that epochdate_expire >= currentDate
            // Check that valid_version >= getAppVersion
            -> if not, open url to previous versions or purchase new licence
            -. (download page, with prev versions)
            
            // Validate last checked in date
            if (lastCheckedInDate+14 > currentDate) {
            
            do httprequest to https://www.harmonyjam.com/check_update
            post : licence, username and password, machineid
            -> on server if (username && password is authenticated) {
            get_current_licence field for this user record (old licences are moved to previous_licences [] array)
            
            // if valid {
            log: machineid, date,
            return : 200 <response status = "ok"/>
            } else
            
            <response status="error">
            <messge>Login failed</messge>
            </response>
            
            <response status="too_many_registered_machines">
            <messge>Too many machines registered with licence. Please de-register some:</messge>
            <registered_machines>
            <machine id="1234567890" name="my macbook"/>
            <machine id="1234567890" name="my desktop"/>
            <machine id="1234567890" name="my ubuntu machine"/>
            </registered_machines>
            </response>
            
            
            }
            
            
            
            */
        }
        return true;

    }

    static Licence validateLicence(string licenceXML, bool fullValidation) {
        
        Licence licence = Licence(false);
        licence.licenceXML = licenceXML;
        
        ofxXmlSettings mWidgetXML = ofxXmlSettings();
        if (!mWidgetXML.loadFromBuffer(licenceXML.c_str())) {
            licence.invalidLicenceCode = "INVALID_XML";
            licence.invalidLicenceReason = "Invalid licence file";
            return licence;
        }
        
        if (!mWidgetXML.pushTag("licence"))  {
            licence.invalidLicenceCode = "INVALID_XML";
            licence.invalidLicenceReason = "Malformed licence file";
            return licence;
        }

/*
        if (licence.reauthorize_epoch == 0) {
            licence.invalidLicenceCode = "INVALID_XML";
            licence.invalidLicenceReason = "Invalid reauthorize epoch";
            return licence;
        }    
*/            

        // Populate the licence variables
        licence.username = mWidgetXML.getValue("username", "");
        licence.password = mWidgetXML.getValue("password", "");
        licence.issued_licence = mWidgetXML.getValue("issued_licence", "");
        licence.machineid = mWidgetXML.getValue("machineid", "");
        licence.token = mWidgetXML.getValue("token", "");
        string reauthorize = mWidgetXML.getValue("reauthorize", "");
        licence.reauthorize_epoch = ofToInt64(reauthorize);        
        
        // Further validation
        validateLicence(licence, fullValidation);

        /*******************************************************
         * HAS VALID LICENCE 
         *******************************************************/         
        licence.invalidLicenceCode = "";
        licence.invalidLicenceReason = "";
        licence.isValid = true;
        return licence;        

    }
    
    
    static void saveLicenceToFile(string username, string password, string issued_licence, string token, uint64_t reauthorize_epoch) {
        
        string licence_raw_xml =
        "<licence>"
        "<username>" + uiVizShared::encodeForXML(username) + "</username>"
        "<password>" + uiVizShared::encodeForXML(password) + "</password>"
        "<issued_licence>" + uiVizShared::encodeForXML(issued_licence) + "</issued_licence>"
        "<machineid>" + uiVizShared::encodeForXML(uiVizShared::getMachineId()) + "</machineid>"
        "<token>" + uiVizShared::encodeForXML(token) + "</token>"
        "<reauthorize>" + ofToString(reauthorize_epoch) + "</reauthorize>"
        "</licence>";
        
        string encryptedLicenceXML = uiVizShared::XOR_Encryption(licence_raw_xml, APP_CONSTANTS::APPLICATION_LIC_ENC_KEY, true);
        //cout << "\n\nencrypted:" << encryptedLicenceXML;
        //string decryptedLicenceXML = uiVizShared::XOR_Encryption(encryptedLicenceXML, APP_CONSTANTS::APPLICATION_LIC_ENC_KEY, true);
        //cout << "\n\ndecrypted:" << decryptedLicenceXML;
        ofBuffer encXMLBuff(encryptedLicenceXML.c_str(), encryptedLicenceXML.length());
        ofBufferToFile(APP_CONSTANTS::APPLICATION_LIC_ENC_KEY_FILE(), encXMLBuff);
    }
    
    static Licence getLicence() {
        string licenceEnc = Licence::loadLicenceFromFile();
        string licenceXML = uiVizShared::XOR_Encryption(licenceEnc, APP_CONSTANTS::APPLICATION_LIC_ENC_KEY, true);
        
        bool verified = false;
        if (licenceXML.size() > 10) {
            string verify = licenceXML.substr(licenceXML.size() -10, 10);
            verified = (verify == "</licence>");
        }
        
        Licence licence = Licence::validateLicence(licenceXML, false);
        return licence;
    }
    
    static bool hasValidLicence() {
        Licence licence = Licence::getLicence();
        return licence.isValid;
    }
    
    static string loadLicenceFromFile() {
        if (!ofFile::doesFileExist(APP_CONSTANTS::APPLICATION_LIC_ENC_KEY_FILE(), true)) return "";
        ofBuffer keyBuff = ofBufferFromFile(APP_CONSTANTS::APPLICATION_LIC_ENC_KEY_FILE(), true);
        return keyBuff.getText();
    }

    static bool REMOTE_getTokenForCredentials(Licence& licence) {

        nlohmann::json j;
        j["username"] = licence.username;
        j["password"] = licence.password;
        string postJson = j.dump();

        ofHttpRequest r = ofHttpRequest(APP_CONSTANTS::APPLICATION_WEBSITE+"/wp-json/jwt-auth/v1/token", "authorizeUser", false);
        r.contentType = "application/json";
        r.body = postJson;
        r.method = ofHttpRequest::POST;

        ofURLFileLoader l;
        ofHttpResponse resp = l.handleRequest(r);
        
        nlohmann::json respJson;
        
        try {
            respJson = nlohmann::json::parse(resp.data);
        } catch(...) { }        

        if (resp.status == 200 && !respJson.is_discarded()) {
            licence.token = respJson["token"];
            return true;
        }
        else if (resp.status == 403) {
            licence.invalidLicenceCode = "INCORRECT_CREDENTIALS";
            licence.invalidLicenceReason = "Incorrect username or password";
            return false;
        } else {
            licence.invalidLicenceCode = "USER_NOT_AUTHENTICATED";
            licence.invalidLicenceReason = "Unable to authenticate user";
            licence.detailedErrorMessage = (resp.error != "" ? resp.error : ofToString(resp.data));
            return false;
        }
    }    

    static bool REMOTE_validateLicence(Licence& licence) {
        // TODO: Do the call here and validate....
        licence.invalidLicenceCode = "LICENCE_TMP_ERR";
        licence.invalidLicenceReason = "AUTHENTICATED! Licence check still to be implemented...";

        licence.detailedErrorMessage = ""; // POST result
        // todo, validate licence and check machineid's
        return false;
    }      
    
};


class uiVizWidgetLicence : public uiVizWidget {
    
public:

    uiVizWidgetLicence(string persistentId, string widgetXML) : uiVizWidget(persistentId, widgetXML) {
        initWidget();
    }
    
    virtual ~uiVizWidgetLicence() {
    }
    
    void update(uiVizWidgetContext context) override {
    }
    
    void draw(uiVizWidgetContext context) override {
        if (keyIcon.getIsVisible()) {
            mUIIconScale = scaleAnimationForUI(getWidgetId() + "_main_menu_left_in", mUIIconScale, 2.0f, 1.0f);
            keyIcon.setScaledPos(scale(getUsableX()), scale(getUsableY()));
            uiVizCoord::vizBounds iconBounds = keyIcon.getScaledBounds();
            keyIcon.scaleSvg(mUIIconScale, mUIIconScale);
            keyIcon.drawSvg();
        } 
    }

     virtual void onWidgetEventReceived(uiVizWidgetEventArgs &args) override {

        string event = args.getFullEventName();
        
        if (event == "OK." + WIDGET_EVENT::CLICK) {
            
            PGS_VALIDATION_RESULT->setIsProgressing(true);

            Licence authLicence(false);
            authLicence.username = TXT_USERNAME->getValue();
            authLicence.password = TXT_PASSWORD->getValue();
            authLicence.issued_licence = TXT_LICENCE->getValue();

            if (TXT_LICENCE) {
                bool didAuthenticate = Licence::REMOTE_getTokenForCredentials(authLicence);



                if (!didAuthenticate) {
                    displayValidationResult(authLicence);
                } else {

                    Licence::saveLicenceToFile(
                        authLicence.username,
                        authLicence.password,
                        authLicence.issued_licence,
                        authLicence.token,
                        0
                    );

                    Licence licence = Licence::getLicence();
                    if (licence.isValid) Licence::validateLicence(licence, true); // Full validation
                    displayValidationResult(licence);
                }                    
            } else {
                // there was a problem with the form!!
            }
        } else if (event == "PGS_VALIDATION_RESULT." + WIDGET_EVENT::VALUE_CHANGED) {
            ofColor c = PGS_VALIDATION_RESULT->getTheme().ElementForegroundColor;
            int percCol = min(255, (int)(255.0f*PGS_VALIDATION_RESULT->getPerc())+100);
            PGS_VALIDATION_RESULT->getTheme().ElementForegroundColor = ofColor(c.r, c.g, c.b, percCol);            
        } else if (event == "CANCEL." + WIDGET_EVENT::CLICK) {
            closeThisWidget();      
        }               
          
    };
    
    void displayValidationResult(Licence licence) {
        uiVizWidgetElmLabel* LBL_VALIDATION_RESULT = getLabel("LBL_VALIDATION_RESULT");
        if (licence.isValid) {
            LBL_VALIDATION_RESULT->setValue("Valid licence key");
        } else {
            if (licence.detailedErrorMessage != "") {
                LBL_VALIDATION_RESULT->setValue(licence.invalidLicenceReason + " [" + licence.detailedErrorMessage + "]");
            } else {
                LBL_VALIDATION_RESULT->setValue(licence.invalidLicenceReason);
            }
            
        }

        setNeedsUpdate(true);
    }
    
    
private:
    
    bool loaded = false;
    uiVizIcon keyIcon;
    float mUIIconScale = 1.0f;
    
    uiVizWidgetElmTextbox* TXT_USERNAME;
    uiVizWidgetElmTextbox* TXT_PASSWORD;
    uiVizWidgetElmTextbox* TXT_LICENCE;
    uiVizWidgetElmProgressBar* PGS_VALIDATION_RESULT;

    void initWidget() override {
        if (loaded) return;
        
        keyIcon = uiVizIconCache::getIcon("MED_MENU");
        keyIcon.setColor(ofColor(255, 255, 255, 200));
        keyIcon.setIsVisible(false);
        
        if (!loaded) {
            uiVizWidgetManager::loadWidgetFromFileToExisting("ui/widgets/licence.xml", *this);
            loaded = true;            
        }
        
        Licence licence = Licence::getLicence();
        
        TXT_USERNAME = getTextbox("TXT_USERNAME");
        TXT_PASSWORD = getTextbox("TXT_PASSWORD");
        TXT_LICENCE = getTextbox("TXT_LICENCE");
        PGS_VALIDATION_RESULT = getProgressBar("PGS_VALIDATION_RESULT");
        
        
        if (TXT_USERNAME) TXT_USERNAME->setValue(licence.username, true);
        if (TXT_PASSWORD) TXT_PASSWORD->setValue(licence.password, true);
        if (TXT_USERNAME) TXT_LICENCE->setValue(licence.issued_licence, true);
        
        if (licence.isValid) Licence::validateLicence(licence, true); // Full validation        
        displayValidationResult(licence);

        /*
        loadState(R"(
                
        )");
        */
        setIsAutoUpdateWhenActive(true);       
    }
};

