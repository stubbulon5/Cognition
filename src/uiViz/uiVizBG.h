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
        uiVizWidgetTheme theme = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();
        bgCol1 = theme.BackgroundColor1_withAlpha(1.0f);
        bgCol2 = theme.BackgroundColor2_withAlpha(1.0f);
        bgCol3 = theme.BackgroundColor3_withAlpha(1.0f);
        bgCol4 = theme.BackgroundColor4_withAlpha(1.0f);
	}

	~uiVizBG() {
	}

	void draw() {
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

private:
	ofColor bgCol1, bgCol2, bgCol3, bgCol4;
    uiVizWidgetTheme theme;
};




