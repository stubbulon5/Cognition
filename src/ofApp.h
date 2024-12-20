#pragma once

#include "ofMain.h"

// UI Stuff
#include "ofxXmlSettings.h"
//#include "ofxVST3.h"
#include "uiViz/uiVizBG.h"
#include "uiViz/uiVizShared.h"
#include "uiViz/uiVizWidgetManager.h"
#include "uiViz/widget/uiVizWidget.h"
#include "uiViz/widget/uiVizWidgetWindowTitle.h"
#include "uiViz/widget/uiVizWidgetCollection.h"
#include "uiViz/widget/uiVizWidgetSettings.h"

#include "app_widgets/uiVizWidgetKeyPicker.h"
#include "app_widgets/uiVizWidgetChordWheel.h"
#include "app_widgets/uiVizWidgetChordDesigner.h"
#include "app_widgets/uiVizWidgetChordBucket.h"
#include "app_widgets/uiVizWidgetChordBucketSuggester.h"
#include "app_widgets/uiVizWidgetScalePicker.h"
#include "app_widgets/uiVizWidgetGuitar.h"
#include "app_widgets/sdMidiShared.h"
// #include "app_widgets/sdFluidSynthShared.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void initAquamarine();
};
