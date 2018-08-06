#include "Rect.h"
#include "Area.h"


Rect Rect::genIniRect(Pt p, float m, float n, float A) {
	float y = sqrt((A*n) / m);
	float x = m*y / n;
	Pt a = Pt(p.x, p.y);
	Pt b = Pt(a.x + x, p.y);
	Pt c = Pt(a.x + x, p.y + y);
	Pt d = Pt(a.x, p.y + y);
	Rect r(a, b, c, d);
	return r;
}
Pt Rect::getA() {
	return a;
}
Pt Rect::getB() {
	return b;
}
Pt Rect::getC() {
	return c;
}
Pt Rect::getD() {
	return d;
}
Pt Rect::getCen() {
	return Pt((a.x + c.x) / 2, (a.y + c.y) / 2);
}

void Rect::clrRectVector() {
	rectVector.clear();
}
void Rect::setParentVec(vector<Parent> v) {
	parentVec.clear();
	for (int i = 0; i < v.size(); i++) {
		parentVec.push_back(v[i]);
	}
}
vector<Rect>Rect::getRectVector() {
	return rectVector;
}

void Rect::setIntVector(vector<int> v) {
	intVector.clear();
	intVector = v;
}

void Rect::setup(Pt a_, Pt b_, Pt c_, Pt d_) {
	a = a_;
	b = b_;
	c = c_;
	d = d_;
}
void Rect::setup(Pt arr[4]) {
	a = arr[0];
	b = arr[1];
	c = arr[2];
	d = arr[3];
}

void Rect::drawRect() {
	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(0, 0, 0);
	ofLine(a.x, a.y, b.x, b.y);
	ofLine(b.x, b.y, c.x, c.y);
	ofLine(c.x, c.y, d.x, d.y);
	ofLine(d.x, d.y, a.x, a.y);
	ofSetColor(150, 150, 150);
	ofLine(a.x, a.y, c.x, c.y);
	ofLine(b.x, b.y, d.x, d.y);
}
void Rect::drawRect(int t) {
	ofNoFill();
	ofSetLineWidth(t);
	ofSetColor(0, 0, 0);
	ofLine(a.x, a.y, b.x, b.y);
	ofLine(b.x, b.y, c.x, c.y);
	ofLine(c.x, c.y, d.x, d.y);
	ofLine(d.x, d.y, a.x, a.y);
	ofSetLineWidth(1);
}
void Rect::drawRect(vector<Rect> rV) {
	for (unsigned int i = 0; i<rV.size(); i++) {
		ofSetColor(0, 0, 0);
		ofSetLineWidth(2);
		Pt a = rV[i].getA(); 
		Pt b = rV[i].getB(); 
		Pt c = rV[i].getC(); 
		Pt d = rV[i].getD(); 
		ofLine(a.x, a.y, b.x, b.y);
		ofLine(b.x, b.y, c.x, c.y);
		ofLine(c.x, c.y, d.x, d.y);
		ofLine(d.x, d.y, a.x, a.y);
	}
	ofSetLineWidth(1);
}
void Rect::drawRect(vector<Rect>rV, int t) {
	for (unsigned int i = 0; i<rV.size(); i++) {
		ofSetColor(0, 0, 0);
		ofSetLineWidth(t);
		Pt a = rV[i].getA();
		Pt b = rV[i].getB();
		Pt c = rV[i].getC();
		Pt d = rV[i].getD();
		ofLine(a.x, a.y, b.x, b.y);
		ofLine(b.x, b.y, c.x, c.y);
		ofLine(c.x, c.y, d.x, d.y);
		ofLine(d.x, d.y, a.x, a.y);
	}	
	ofSetLineWidth(1);
}

void Rect::drawRect(int re, int gr, int bl) {
	ofSetColor(re, gr, bl);
	ofFill();
	float w = b.x - a.x; float h = d.y - a.y;
	ofDrawRectangle(a.x, a.y, w, h);
	
	ofSetColor(0,0,0);
	ofNoFill();
	ofDrawRectangle(a.x, a.y, w, h);
}

void Rect::incrementState() {
	state++;
}
void Rect::clrState() {
	state = 0;
}

void Rect::subdivide(Rect r, int C, int re, Parent parent) {
	/* DISSECT THE AREA TREE */
	Child cL = parent.L; Child cR = parent.R;
	float ArL = sumAr(cL.areas); float ArR = sumAr(cR.areas);
	/*
	cout << "parent : " << parent.name << " , " << sumAr(parent.areas) << endl;
	cout << "children : " << cL.name << " , " << ArL << endl;
	cout << "children : " << cR.name << " , " << ArR << endl;
	*/
	/* GEOMETRIC OPERATIONS */
	Pt a = r.getA();
	Pt b = r.getB();
	Pt c = r.getC();
	Pt d = r.getD();
	float Width = a.distance(b); float Height = a.distance(d);
	float AREA = Width*Height;
	
	int w = intVector[state];
	incrementState();
	
	/* PRINT STATES - CHECK */
	//cout << "\nrec: " << state << ", w: " << w << endl;
	
	Rect r0, r1;
	if (w == 0) {
		float DiL = ArL / (a.distance(d));
		float ab = a.distance(b);
		float dc = d.distance(c);
		Pt m = Pt(a.x + ((b.x - a.x)*DiL / ab), a.y + ((b.y - a.y)*DiL / ab));
		Pt n = Pt(d.x + ((c.x - d.x)*DiL / dc), d.y + ((c.y - d.y)*DiL / dc));
		r0.setup(a, m, n, d); r1.setup(m, b, c, n);
		r0.setName(cL.name); r1.setName(cR.name);
	}
	else {
		float DiR = ArL / (a.distance(b));
		float da = a.distance(d);
		float bc = b.distance(c);
		Pt m = Pt(b.x + ((c.x - b.x)*DiR / bc), b.y + ((c.y - b.y)*DiR / bc));
		Pt n = Pt(a.x + ((d.x - a.x)*DiR / da), a.y + ((d.y - a.y)*DiR / da));
		r0.setup(a, b, m, n); r1.setup(n, m, c, d);
		r0.setName(cL.name); r1.setName(cR.name);
	}

	if (C < 10) {
		C++;
		Parent pL("", vector<float>{}), pR("", vector<float>{});
		for (int i = 0; i < parentVec.size(); i++) {
			std::string name0 = parentVec[i].name;
			std::vector<float>ar0 = parentVec[i].areas;
			if (cL.name == name0) {
				pL = parentVec[i];
			}
			if (cR.name == name0) {
				pR = parentVec[i];
			}
		}
		if ((sumAr(pL.L.areas) > 1) || (sumAr(pL.R.areas) > 1)){
			//cout << "\nGoing into Left subdivision " << pL.name << ": " << sumAr(pL.areas) << std::endl;
			subdivide(r0, C, re, pL); 
		}
		else {
			rectVector.push_back(r0);
		}
		if ((sumAr(pR.L.areas) > 1) || (sumAr(pR.R.areas) > 1)) {
			//cout << "\nGoing into Right subdivision " << pR.name << ": " << sumAr(pR.areas) << std::endl;
			subdivide(r1, C, re, pR); 
		}
		else {
			rectVector.push_back(r1);
		}
	}
	else {
		rectVector.push_back(r0); rectVector.push_back(r1);
	}
}


Rect Rect::moveRect(float x, float y) {
	Pt a = getA(); Pt b = getB(); Pt c = getC(); Pt d = getD();
	float dx = fabs(c.x - a.x);
	Pt A = Pt(a.x + x, a.y); Pt B = Pt(b.x + x, b.y); Pt C = Pt(B.x, c.y); Pt D = Pt(A.x, d.y);
	Pt ptx[4] = { A,B,C,D };
	Rect s(ptx);
	return s;
}


float Rect::sumAr(vector<float>ar) {
	double sum = 0;
	for (int i = 0; i < ar.size(); i++) {
		sum += ar[i];
	}
	return sum;
}
float Rect::getCoordArea() {
	float w = (c.x - a.x); float h = (c.y - a.y);
	return (w*h);
}



