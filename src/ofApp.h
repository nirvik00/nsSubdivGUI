#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Area.h"
#include "Pt.h"
#include "Rect.h"
#include "ctrlVector.h"
#include "GaOpt.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		/*	MY METHODS  */
		void storePreferences();
		void displayGenerationMetrics();
		void displayAreaVec(std::vector<float> vec);

		/*my global variables*/
		Area ar;
		GaOpt gaOpt;
		vector<colArStr> colrArStructVec = ar.genColorVec();
		int NUM = 10;

		/* TEMPORARY OR single elements*/
		Pt a, b, c, d;							// points
		vector<Parent> parentVec;				// tree of subdivision : area, naming
		vector<int> cvV;						//control vector : to control subdivisions


		/* vector of single elements*/
		vector<Area> vecArea;
		vector<Rect> vecBoundaryRect;			// agnostic to code : position of system
		vector<Rect> vecIniRect;				// initial rect which will get transformed
		vector< vector<Rect> > vecOutRect;		// contain the pendant geometry

		/* GLOBAL COUNTER FOR NUMBER OF CHANGES */
		int global_image_counter = 0;
		int global_iteration_counter = 0;

		/* GUI */
		ofxPanel gui;
		ofxIntSlider gen0, gen1, gen2, gen3, gen4, gen5, gen6, gen7;
		
		/* GUI SCORES */
		vector<int>scoreVec;					// score of all sliders taken per generation

		/* GLOBAL VECTORS FOR DNA */
		vector< vector<int> > vecCtrlVec;		// collection of control vectors for this generations
		vector< vector<Parent> > vecParentVec;	// collection of family trees for this generations
		
};

