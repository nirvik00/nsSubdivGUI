#include "Pt.h"

void Pt::setup(float x_, float y_) {
	x = x_;
	y = y_;
}

void Pt::setup(vector<Pt> ptV) {
	ptVec = ptV;
}

void Pt::drawPt() {
	ofSetColor(0, 0, 0);
	ofCircle(x, y, 10);
}

void Pt::drawPt(int re, int gr, int bl) {
	ofSetColor(re, gr, bl);
	ofCircle(x, y, 10);
}

void Pt::drawPt(int re, int gr, int bl, int t) {
	ofSetColor(re, gr, bl);
	ofCircle(x, y, t);
}

void Pt::drawPtVec() {
	ofSetColor(0, 0, 0);
	if (ptVec.size() > 0) {
		for (unsigned int i = 0; i < ptVec.size(); i++) {
			float x = ptVec[i].x;
			float y = ptVec[i].y;
			Pt p;
			p.setup(p.x, p.y);
			p.drawPt();
		}
	}
}


float Pt::distance(Pt b) {
	return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y));

}










