#include "ofApp.h"

void ofApp::setup(){

    //---------- SETTINGS ----------
    ofSetEscapeQuitsApp(false);

    #ifdef TARGET_OSX  
        // Use the "internal" data folder if it exitst
        string dataPathRoot = ofFilePath::getCurrentExeDir() + "data/";
        if (ofDirectory::doesDirectoryExist(dataPathRoot, false)) {
            ofSetDataPathRoot(dataPathRoot);
        }
    #endif 

    #if VIZ_DEBUG_LEVEL > -1
        ofSetLogLevel(ofLogLevel::OF_LOG_NOTICE);
    #else
        ofSetLogLevel(ofLogLevel::OF_LOG_SILENT);    
    #endif  

    ofxXmlSettings settings = 
        Aquamarine::Shared::initSettingsFile(
            APP_CONSTANTS::APPLICATION_SETTINGS_FOLDER(),
            APP_CONSTANTS::APPLICATION_SETTINGS_FILE()
        );

    Aquamarine::Shared::configure(
        settings.getValue("settings:userInterfaceScaling", Aquamarine::Shared::getDefaultScaling()),
        settings.getValue("settings:language", "english"),
        settings.getValue("settings:userExperience", Aquamarine::Shared::getDefaultFPS()),
        settings.getValue("settings:useFbo", true),
        settings.getValue("settings:showFps", false),
        settings.getValue("settings:fontPath", "fonts/Verdana.ttf"),
        settings.getValue("settings:autoLoadMostRecentProject", true),
        settings.getValue("settings:themeName", "Aqumarine")
    );

    Aquamarine::Shared::langLoadXML(APP_CONSTANTS::DEFAULT_LANGUAGE_XML);
    APP_CONSTANTS::BOOTSTRAP_APP();
    
	// Midi initialize - make it configurable too...
	MidiShared::configure();

    ofSetWindowTitle("cognition");
    ofSetWindowShape(ofGetScreenWidth() * 0.8f, ofGetScreenHeight() * 0.8f);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight() / 2 - ofGetHeight() / 2);

    initAquamarine();
}

void ofApp::initAquamarine() {
    Aquamarine::WidgetManager::removeAllWidgets();
    
    /* Add the main menu */
    Aquamarine::Widget* mainMenuWidget = Aquamarine::WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU, "APP_MAIN_MENU", "<widget></widget>");
    Aquamarine::WidgetManager::addWidget(*mainMenuWidget, false);
}

//------------------------------ DRAW & UPDATE--------------------------------
void ofApp::update() {
}

void ofApp::draw() {
	// vizBG->draw();
    Aquamarine::WidgetManager::drawWidgets();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    // TODO : make this a user setting!
    if (Aquamarine::Shared::getViz() != nullptr && !Aquamarine::Shared::getViz()->getIsAnyWidgetDraggingOrResizing()) {
        Aquamarine::Shared::revertThrottleUserExperience();
    }
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    // TODO : make this a user setting!
    if (Aquamarine::Shared::getViz() != nullptr && !Aquamarine::Shared::getViz()->getIsAnyWidgetDraggingOrResizing()) {
        Aquamarine::Shared::throttleUserExperience();
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    if (Aquamarine::Shared::getViz() != nullptr) {
        Aquamarine::Shared::setResolutionMultiplier();
        Aquamarine::Shared::setUserScale(Aquamarine::Shared::getViz()->getUserScale());
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void ofApp::exit() {
    // clean up
    MidiShared::closePort();
}
