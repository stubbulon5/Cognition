#include "ofApp.h"


void ofApp::setup(){

    //---------- SETTINGS ----------
    ofSetEscapeQuitsApp(false);

    Aquamarine::App::BOOTSTRAP(
        "cognition",
        APP_CONSTANTS::getAppWidgetMap(),
        APP_CONSTANTS::getIconCacheMap(1.0),
        "1.0.0",
        "jam",
        APP_CONSTANTS::DEFAULT_LANGUAGE_XML
    );

	// Midi initialize - make it configurable too...
	MidiShared::configure();

    ofSetWindowTitle("cognition");
    ofSetWindowShape(ofGetScreenWidth() * 0.8f, ofGetScreenHeight() * 0.8f);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight() / 2 - ofGetHeight() / 2);

    Aquamarine::Widget* mainMenuWidget = Aquamarine::WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU, "APP_MAIN_MENU", "<widget></widget>");
    Aquamarine::WidgetManager::addWidget(*mainMenuWidget, false);

    // Aquamarine::Widget* picker = Aquamarine::WidgetManager::loadWidget(Aquamarine::WidgetManager::WIDGET_CLASS_COLOR_PICKER, "COLOR", "<widget></widget>");

    // picker->setWidgetSize(350, 350, false);
    // Aquamarine::WidgetManager::addWidget(*picker, false);    

    // Aquamarine::Widget* settings = Aquamarine::WidgetManager::loadWidget("WidgetSettings", "zzz", "<widget></widget>");
    // Aquamarine::WidgetManager::addWidget(*settings, false);
}

//------------------------------ DRAW & UPDATE--------------------------------
void ofApp::update() {
}

void ofApp::draw() {
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
