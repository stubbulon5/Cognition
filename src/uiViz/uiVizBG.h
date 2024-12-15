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

    ofBoxPrimitive box;

	uiVizBG() {

        box.set(100);

	}

	~uiVizBG() {
        palatte.clear();
	}

	void draw() {

		// Black (or white) background with colour squares like : http://colorizer.org/

		// When degree plays, the colour lights up!


		if (ofGetFrameNum() % 30 == 0) {

            if (increasing) {
                colourIterator += 0.0001f;
                if (colourIterator >= 1.1f) increasing = false;
            }
            else {
                colourIterator -= 0.0001f;
                if (colourIterator >= 0.7f) increasing = true;
            }
        
        /*
        vector<ofColor> palatte = {
            ofColor(ofColor::black),
            ofColor(ofColor::darkSlateBlue),
            ofColor(ofColor::black),
            ofColor(ofColor::darkSlateBlue)
        };*/


        uiVizWidgetTheme theme = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();


/*
        bgCol1 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * colourIterator, 161 * ofRandom(0.9f, 1.1f));
        bgCol2 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * ofRandom(0.9f, 1.1f), 104 * colourIterator);
        bgCol3 = ofColor(54 * ofRandom(0.9f, 1.1f), 119 * colourIterator, 169 * ofRandom(0.9f, 1.1f));
        bgCol4 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * ofRandom(0.9f, 1.1f), 104 * colourIterator);

        //}
        // for cirtus
        bgCol1 = palatte[3];
        bgCol2 = palatte[4];
        bgCol3 = palatte[1];
        bgCol4 = palatte[7];
        
*/
      //  bgCol1 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * colourIterator, 161 * ofRandom(0.9f, 1.1f));
      //  bgCol2 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * ofRandom(0.9f, 1.1f), 104 * colourIterator);
      //  bgCol3 = ofColor(54 * ofRandom(0.9f, 1.1f), 119 * colourIterator, 169 * ofRandom(0.9f, 1.1f));
      //  bgCol4 = ofColor(54 * ofRandom(0.9f, 1.1f), 169 * ofRandom(0.9f, 1.1f), 104 * colourIterator);

        // LIGHT <widgetAccentColor color1="#008793" color2="#A8EB12" color3="#051937" color4="#004D7A" />  
        // DARK  <widgetAccentColor color1="#051937" color2="#004D7A" color3="#008793" color4="#A8EB12" />

        uiVizWidgetTheme t = uiVizShared::getViz()->getThemeManager()->getDefaultTheme();
        bgCol1 = t.WidgetAccent1Color_withAlpha(1.0f);
        bgCol2 = t.WidgetAccent2Color_withAlpha(1.0f);
        bgCol3 = t.WidgetAccent3Color_withAlpha(1.0f);
        bgCol4 = t.WidgetAccent4Color_withAlpha(1.0f);

        if (t.IsDark) {
            bgCol1.setBrightness(255);
            bgCol2.setBrightness(255);
            bgCol3.setBrightness(255);
            bgCol4.setBrightness(255);
        } else {
            bgCol1.setBrightness(200);
            bgCol2.setBrightness(200);
            bgCol3.setBrightness(200);
            bgCol4.setBrightness(200);
        }



        //background-image: linear-gradient(to right top, #051937, #004d7a, #008793, #00bf72, #a8eb12);


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


    /*
    box.setPosition(ofGetWidth()*.2, ofGetHeight()*.75, 0);
    box.rotate(1, 1.0, 0.0, 0.0);
    box.rotate(1, 0, 1.0, 0.0);
         box.drawWireframe();
    */

	}

    void updateTheme() {
        
    }

private:
	ofColor bgCol1, bgCol2, bgCol3, bgCol4;

	vector<ofColor> palatte = {
	ofColor(169, 54, 62),
	ofColor(169, 104, 54),
	ofColor(169, 161, 54),
	ofColor(119, 169, 54),
	ofColor(62, 169, 54),
	ofColor(54, 169, 104),
	ofColor(54, 169, 161),
	ofColor(54, 119, 169),
	ofColor(54, 62, 169),
	ofColor(104, 54, 169),
	ofColor(161, 54, 169),
	ofColor(169, 54, 119)
	};


	float colourIterator = 0.8;
	bool increasing = true;

};




