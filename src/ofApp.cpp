#include "ofApp.h"

void ofApp::setup(){

    //---------- SETTINGS ----------
    ofSetEscapeQuitsApp(false);


    // appWidgets = new Aquamarine::AppWidgets();

    cognition = new Aquamarine::AppCognition();
    cognition->BOOTSTRAP();

    //Aquamarine::AppWidgets::registerCustomWidgets();

	// Midi initialize - make it configurable too...
	MidiShared::configure();

    ofSetWindowTitle(Aquamarine::App::APPLICATION_NAME());
    ofSetWindowShape(ofGetScreenWidth() * 0.8f, ofGetScreenHeight() * 0.8f);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight() / 2 - ofGetHeight() / 2);

    initAquamarine();
}

void ofApp::initAquamarine() {
    Aquamarine::WidgetManager::removeAllWidgets();
    
    /* Add the main menu */
    // Aquamarine::Widget* mainMenuWidget = Aquamarine::WidgetManager::loadWidget(APP_CONSTANTS::WIDGET_CLASS_MAIN_MENU, "APP_MAIN_MENU", "<widget></widget>");
    // Aquamarine::WidgetManager::addWidget(*mainMenuWidget, false);


    //     Aquamarine::WidgetSettings* w = dynamic_cast<Aquamarine::WidgetSettings*>(Aquamarine::WidgetManager::loadWidget("WidgetSettings", "ZEE", R"(
    //         <widget>
    //         <bounds width="150" height="150" minWidth="75" minHeight="75"  />
    //         </widget>
    //         )"));
    // Aquamarine::WidgetManager::addWidget(*w, false);

        // Aquamarine::WidgetManager::loadAndAddWidget("WidgetSettings", "ZEE", R"(
        //     <widget>
        //     <bounds width="150" height="150" minWidth="75" minHeight="75"  />
        //     </widget>
        //     )", false);    

        Aquamarine::WidgetManager::loadAndAddWidget("WidgetFileList", "ZOO", R"(
            <widget>
            <bounds width="150" height="150" minWidth="75" minHeight="75"  />
            </widget>
            )", false);    


    // Aquamarine::Widget* wSettings = Aquamarine::WidgetManager::loadWidget("WidgetSettings", "STOO_SETT", "<widget></widget>");
    // Aquamarine::WidgetSettings* castedSet = dynamic_cast<Aquamarine::WidgetSettings*>(wSettings);
    // Aquamarine::WidgetManager::addWidget(*wSettings, false);





    // DOESNT WORK - Casting as WidgetBase, not Widget!!!
    // Aquamarine::Widget* w = Aquamarine::WidgetManager::loadWidgetFromFile("Widget", "ZOO", "ui/widgets/about.xml");
    // Aquamarine::WidgetAbout* casted = dynamic_cast<Aquamarine::WidgetAbout*>(w);
    // Aquamarine::WidgetManager::addWidget(*casted, false);


    // WORKS ::::
    // Aquamarine::Widget* w = Aquamarine::WidgetManager::loadWidgetFromFile("Widget", "ZOO", "ui/widgets/about.xml");
    // Aquamarine::WidgetManager::addWidget(*w, false);






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
