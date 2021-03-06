#include "ofApp.h"

#include "Area.h"
#include "Pt.h"
#include "Rect.h"
#include "ctrlVector.h"


void ofApp::setup() {
	srand(time(NULL));
	/* GUI */
	gui.setup("SCORES");
	gui.add(gen0.setup("Score Gen-0", 0, 0, 10)); 
	gui.add(gen1.setup("Score Gen-1", 0, 0, 10));
	gui.add(gen2.setup("Score Gen-2", 0, 0, 10));
	gui.add(gen3.setup("Score Gen-3", 0, 0, 10));
	gui.add(gen4.setup("Score Gen-4", 0, 0, 10));
	gui.add(gen5.setup("Score Gen-5", 0, 0, 10));
	gui.add(gen6.setup("Score Gen-6", 0, 0, 10));
	gui.add(gen7.setup("Score Gen-7", 0, 0, 10));
	gui.add(propagate.setup("Propagate Scores", 10, 1, 100));
	gui.add(restrictPop.setup("Restrict Population", 50, 1, 100));
	gui.add(restrictCross.setup("Restrict Crossing", 10, 1, 100));
	gui.add(randomTGL.setup("Large Randomization", false));

	ofSetWindowTitle("Subdivision Dashboard");

	/* AREA SUBDIVISION, CONTROL VECTORS, GEOMETRY EQUIVALENCE */
	vecBoundaryRect.clear();	//	boundary rectangle
	vecIniRect.clear();			//	initial rectangle which undergoes transformation
	vecOutRect.clear();			//	output rectangle : pendant of area tree
	vecParentVec.clear();		//	parent tree : for all iterations in 1 generation
	vecCtrlVec.clear();			//	vector of control vector : for all iterations in 1 generation
	scoreVec.clear();			//	vector of scores for 1 generation

	/* GOTO GENERATION FUNCTIONS */
	/* GENERATE RANDOM ITERATIONS */
	//nsIniGen();
	
	/* USING THE LEARNING / OPTIMIZATION ALGORITHMS */
	if (global_iteration_counter == 0) {
		nsIniGen();
	}
	else {
		nsNextGen();
	}
	global_iteration_counter++;
}

void clrVec() {}

void ofApp::nsNextGen() {
	vecBoundaryRect.clear();	//	boundary rectangle
	vecIniRect.clear();			//	initial rectangle which undergoes transformation
	vecOutRect.clear();			//	output rectangle : pendant of area tree
	vecParentVec.clear();		//	parent tree : for all iterations in 1 generation
	vecCtrlVec.clear();			//	vector of control vector : for all iterations in 1 generation
	scoreVec.clear();			//	vector of scores for 1 generation

	std::cout << "next generation : " << global_iteration_counter << endl;
	if (opt_empty == 0) {
		global_iteration_counter = 0;
		setup();
	}
	
	if (randomTGL == 1) {
		GAOPT.addNewParent(10);
		GAOPT.addNewControl(10,10);
	}

	GAOPT.propagateScores(propagate);
	
	vector<CtrlStr> cV = GAOPT.getCtrl(8); 
	for (int i = 0; i < cV.size(); i++)	vecCtrlVec.push_back(cV[i].ctrlVec);

	vector<ParentStr> pV = GAOPT.getParent(8);
	for (int i = 0; i < pV.size(); i++) vecParentVec.push_back(pV[i].parentVec);
	
	std::cout << "restrictPop: " << restrictPop << " restrictCross: " << restrictCross << endl;
	GAOPT.restrictPopulation(restrictPop, restrictCross);

	int U = 5; int V = 2; int E = -1;
	for (unsigned int i = 300; i < 300 * U; i += 325) {
		for (unsigned int j = 0; j < 300 * V; j += 325) {
			E++;
			a = Pt(50 + i, 50 + j);
			b = Pt(a.x + 300, a.y);
			c = Pt(a.x + 300, b.y + 150);
			d = Pt(a.x, c.y);
			float totalArea = ar.getTotalAr();	
			vector<Parent> parentVec = vecParentVec[E];
			vector<int> cV = vecCtrlVec[E];
			/* RECTANGLE */
			Rect R0;									// Initialize the rectangle
			Rect r = R0.genIniRect(a, 1, 2, totalArea); // setup the initial rectangle
			r.setParentVec(parentVec);					// set the area tree to the rect
			r.setIntVector(cV);						// generate & set control vector to Rect
			vecIniRect.push_back(r);					//make a vector of initial rectangles
			vecBoundaryRect.push_back(r);
			r.clrState();
			r.subdivide(r, 0, 0, parentVec[0]);			// construct the vectors of rects from initial rect
			vector<Rect> rv;
			rv.clear();
			rv = r.getRectVector();						// get the vector of output vectors
			vecOutRect.push_back(rv);					// vector of output vectors from subdivision of initial rectangles
		}
	}


	/* DISPLAY THE PARENT -CHILD / AREAS */
	/*
	cout << "\n\nParent Child :  " << endl;
	for (int i = 0; i < vecParentVec.size(); i++) {
	cout << "Iteration :  " << i << endl;
	for (int j = 0; j < vecParentVec[i].size(); j++) {
	vecParentVec[i][j].display();
	}
	cout << endl;
	}
	*/


	/* DISPLAY THE CONTROL VECTORS */
	/*
	cout << "Control Vectors :  " << endl;
	for (int i = 0; i < vecCtrlVec.size(); i++) {
	cout << "Iteration :  " << i << endl;
	for (int j = 0; j < vecCtrlVec[i].size(); j++) {
	cout << vecCtrlVec[i][j] << "," ;
	}
	cout << endl;
	}
	*/

}

void ofApp::nsIniGen(){
	cout << "Initial Generation" << endl;
	/* ONE RECT ONLY *///int U = 2; int V = 1;
	/* MULTIPLE RECTS */int U = 5; int V = 2;
	for (unsigned int i = 300; i < 300 * U; i += 325) {
		for (unsigned int j = 0; j < 300 * V; j += 325) {
			a = Pt(50 + i, 50 + j);
			b = Pt(a.x + 300, a.y);
			c = Pt(a.x + 300, b.y + 150);
			d = Pt(a.x, c.y);			
			/* AREA */
			float totalArea = ar.getTotalAr();	// set total area from elements
			ar.initSubdiv();					// initialize the sub-division module
			ar.constructGraph();				// construct parent-child relationships
			parentVec.clear(); 
			parentVec = ar.getParentVec();		
			vecParentVec.push_back(parentVec);
			/* CONTROL */
			ctrlVector cv;						 // control vector
			/*  initialize the control vector */
			cvV.clear();						// clear the control vector
			cvV = cv.newIntVector(NUM);
			vecCtrlVec.push_back(cvV);
			
			/* RECTANGLE */
			Rect R0;									// Initialize the rectangle
			Rect r = R0.genIniRect(a, 1, 2, totalArea); // setup the initial rectangle
			r.setParentVec(parentVec);					// set the area tree to the rect
			r.setIntVector(cvV);						// generate & set control vector to Rect
			vecIniRect.push_back(r);					//make a vector of initial rectangles
			vecBoundaryRect.push_back(r);
			r.clrState();
			r.subdivide(r, 0, 0, parentVec[0]);			// construct the vectors of rects from initial rect
			vector<Rect> rv;
			rv.clear();
			rv = r.getRectVector();						// get the vector of output vectors
			vecOutRect.push_back(rv);					// vector of output vectors from subdivision of initial rectangles
		}
	}
}

void ofApp::update() {
	
	/* USING THE LEARNING / OPTIMIZATION ALGORITHMS */
	/*
	if (global_iteration_counter == 0) nsIniGen();
	else nsNextGen();
	global_iteration_counter++;
	*/
}

void ofApp::draw() {
	ofBackground(255, 255, 255);
	ofSetColor(255, 255, 255); ofFill(); ofDrawRectangle(0, 0, 1200, 750); ofNoFill();
	ofSetColor(0, 0, 0);
	float YD = 300;
	ofDrawBitmapString("KeyBoard Controls\n-----------------", 10, YD+285);
	ofDrawBitmapString("Press 'n' to create next generation", 10, YD + 315);
	ofDrawBitmapString("Press 'c' to change color scheme", 10, YD + 330);
	ofDrawBitmapString("Press 'p' to take a screenshot", 10, YD + 345);
	ofDrawBitmapString("Press 'm' to save & display metrics", 10, YD + 360);
	/*
	ofDrawBitmapString("Contact\n-------", 10, 620);
	ofDrawBitmapString("Nirvik Saha (GIT)\nDennis R Shelden (GIT)\nJohn R Haymaker (P+W)", 10, 650);
	*/
	for (int i = 0; i < vecBoundaryRect.size(); i++) {
		Rect R = vecBoundaryRect[i];
		vecBoundaryRect[i].drawRect(3);
		/* index of rect */
		ofSetColor(0, 0, 0);
		ofDrawBitmapString(to_string(i), R.getA().x - 20, R.getA().y + 10);
	}
	/* COLOR OF RECTANGLES - LEGEND */
	ofDrawBitmapString("Legend (Color & Area)\n---------------------", 10, YD);
	for (int i = 0; i < colrArStructVec.size(); i++) {
		float this_ar = colrArStructVec[i].area;
		int re = colrArStructVec[i].re;
		int gr = colrArStructVec[i].gr;
		int bl = colrArStructVec[i].bl;
		ofSetColor(re, gr, bl); 
		float x = 20; float y = YD+25+25*i; float w = 15; float h = 15;
		ofFill();  ofDrawRectangle(x, y, w, h);
		ofSetColor(0, 0, 0);
		string pr = to_string(i) + ". " + to_string((int)this_ar);
		ofDrawBitmapString(pr, x + 25, y+12.5);
	}
	/* PLOT THE PENDANT RECTANGLES : GEOMETRY / AREA-SUBDIVISION EQUIVALENCE */
	for (int i = 0; i < vecOutRect.size(); i++) {
		for (int j = 0; j < vecOutRect[i].size(); j++) {
			Rect p = vecOutRect[i][j];
			Pt m = p.getCen(); float ar = p.getCoordArea();
			int re, gr, bl, index;
			int sum = 0;
			for (int i = 0; i < colrArStructVec.size(); i++) {
				float this_ar = colrArStructVec[i].area;
				if (fabs(this_ar - ar) < 1){
					re = colrArStructVec[i].re;
					gr = colrArStructVec[i].gr;
					bl = colrArStructVec[i].bl;
					index = i;
					sum++;
					break;
				}
			}
			p.drawRect(re, gr, bl);
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(index, m.x, m.y);
		}
	}
	/* DRAW THE GUI */
	gui.draw();
}

void ofApp::keyPressed(int key) {
	if (key == 'n' || key == 'N') {
		/* SAVE THE USER PREFERENCES - GAOPT HEADER*/
		storePreferences();
		/* GO TO NEXT GENERATION*/
		setup();
	}else if (key == 'c' || key == 'C') {
		colrArStructVec = ar.genColorVec();
	}else if (key == 'p' || key == 'P') {
		global_image_counter++;
		ofImage screenshot;
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.saveImage("screenshot"+to_string(global_image_counter)+".png");
	}else if (key == 'm' || key == 'M') {
		displayGenerationMetrics();
	}
}

void ofApp::storePreferences() {
	scoreVec.clear();
	scoreVec.insert(scoreVec.end(), { gen0,gen1,gen2,gen3,gen4,gen5,gen6,gen7 });
	for (int i = 0; i < 8; i++) {
		vector<Parent> p = vecParentVec[i];
		vector<int> c = vecCtrlVec[i];
		int s = scoreVec[i];
		int g = global_iteration_counter;
		GAOPT.addEntry(c, p, s, g);
		opt_empty++;
	}
}

void ofApp::displayGenerationMetrics(){
	cout << "\nscores : ";
	for (int i = 0; i < scoreVec.size(); i++) {
		cout << i << ") " << scoreVec[i] << ", ";
	}
	cout << endl;
	cout << "\nControl Vectors : " << endl;
	for (int i = 0; i < vecCtrlVec.size(); i++) {
		cout << i << ") " << "Control Vector Score: " << scoreVec[i] << ", Vector: ";
		for (int j = 0; j < vecCtrlVec[i].size(); j++) {
			cout << vecCtrlVec[i][j] << ", ";
		}
		cout << endl;
	}	
	cout << "\nBinary Tree (s) : " << endl;
	for (int i = 0; i < vecParentVec.size(); i++) {
		cout << "\n" << i << ") " <<  "iteration  " << endl;
		for (int j = 0; j < vecParentVec[i].size(); j++) {
			string nameP = vecParentVec[i][j].name;
			string nameR = vecParentVec[i][j].L.name;
			string nameL = vecParentVec[i][j].R.name;
			vector<float> pA = vecParentVec[i][j].areas;
			vector<float> cLA = vecParentVec[i][j].L.areas;
			vector<float> cRA = vecParentVec[i][j].R.areas;
			cout << nameP << " : "; displayAreaVec(pA); cout << endl;
			if (nameL != "") { cout << "\t" << nameL << " : "; displayAreaVec(cLA); cout << endl; }
			if (nameR != "") { cout << "\t" << nameR << " : "; displayAreaVec(cRA); cout << endl; }
		}
	}
	cout << "--------------------------" << endl;
}

void ofApp::displayAreaVec(std::vector<float> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << ", ";
	}
}

void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
