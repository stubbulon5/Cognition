
#pragma once
#include "uiViz.h"
#include "uiLang.h"
#include "ofxXmlSettings.h"

class uiVizShared {
    
public:
    static ofxXmlSettings initSettingsFile(string settingsPath, string settingsFileName);
    static string getSettingsPath();
    static string getSettingsFileName();
    static string getSettingsFileFullPath();
    static int getDefaultFPS();
    static float getDefaultScaling();

    static void configure( /* The full path to the Settings file */        
        float SETTING_User_Scale,
        string SETTING_language,
        int SETTING_userExperience,
        bool SETTING_useFbo,
        bool SETTING_showFps,
        string SETTING_absoluteFontPath,
        bool SETTING_SETTING_autoLoadMostRecentProject,
        string SETTING_themeName
    );

    static std::shared_ptr<uiViz> getViz();
    static void setUserScale(float val);
    static void setUserExperience(float val);
    static void setUseFbo(bool useFbo);
    static void setShowFps(bool useFbo);
    static void setUserExperience(float val, bool isInitializing);
    static void throttleUserExperience();
    static void revertThrottleUserExperience();
    static void setResolutionMultiplier();
    static void setUserFont(string absolutePath);
    static string getUserSpecifiedFont();
    static string lang(string tag);
    static void langLoadXML(string xml);
    static void langLoadFile(string filename);
    static string encodeForXML(string val);
    static string encodeForJSON(string val);
    static string getMachineId();
    static string XOR_Encryption(string toBeEncrypted, string sKey, bool includeMachineIdInKey);
    static string Pretty_Bytes(uint64_t bytes);
    static string removeFileExtension(const std::string& filename);
    static vector<string> tokenize(const string & str, const string & delim);
    static void appendXMLToTarget(TiXmlElement* source, ofxXmlSettings* target, bool recursive);
    static string getXMLAtTag(ofxXmlSettings* xml, string tag, int which);
    static string& implode(const std::vector<std::string>& elems, char delim, std::string& s);
    static string implode(const std::vector<std::string>& elems, char delim);
    static string base64EncodeString(ofBuffer tmpBuff);
    static void launchBrowser(const string uriStr);

    static int getVizDebug();
    static void setVizDebug(int val);

private:
    static std::shared_ptr<uiViz> viz;
    static string APP_SETTINGS_PATH;    
    static string APP_SETTINGS_FILE_NAME;     
    static string APP_SETTINGS_FILE_FULL_PATH;       
    static int mVizDebug;  

    
};
