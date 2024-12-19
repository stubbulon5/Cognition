//
//  uiVizBG.h
//  bloom
//
//
#include "uiVizShared.h"

//------------------------------ UI VIZ BG CLASS --------------------------------
#pragma once
class uiVizBG {

public:
	uiVizBG() {
	}

	~uiVizBG() {
	}

	void draw() {
		if (ofGetFrameNum() % 30 == 0) {

            if (increasing) {
                colourIterator += 0.0001f;
                if (colourIterator >= 1.1f) increasing = false;
            }
            else {
                colourIterator -= 0.0001f;
                if (colourIterator >= 0.7f) increasing = true;
            }
        
        uiVizWidgetTheme theme = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();
        uiVizWidgetTheme t = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();

        bgCol1 = t.BackgroundColor1_withAlpha(1.0f);
        bgCol2 = t.BackgroundColor2_withAlpha(1.0f);
        bgCol3 = t.BackgroundColor3_withAlpha(1.0f);
        bgCol4 = t.BackgroundColor4_withAlpha(1.0f);
        }
        
        ofMesh temp;
        temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        temp.addVertex(ofPoint(0, 0));
        temp.addColor(bgCol1);
        temp.addVertex(ofPoint(ofGetWindowWidth(), 0));
        temp.addColor(bgCol2);
        temp.addVertex(ofPoint(0, ofGetWindowHeight()));
        temp.addColor(bgCol3);
        temp.addVertex(ofPoint(ofGetWindowWidth(), ofGetWindowHeight()));
        temp.addColor(bgCol4);

        temp.draw();
	}

    void updateTheme() {
        
    }

private:
	ofColor bgCol1, bgCol2, bgCol3, bgCol4;
	float colourIterator = 0.8;
	bool increasing = true;

};




