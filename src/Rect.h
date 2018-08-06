#pragma once

#include "Pt.h"
#include "Area.h"


class Rect
{
	int state;
	Pt ptArr[4];
	Pt a, b, c, d;
	std::string name="O";
	vector<Rect> rectVector;
	vector<int> intVector;
	vector<Parent> parentVec; //area tree

public:
	Rect() {}
	
	Rect( vector<int> v) { 
		for (unsigned int i = 0; i < v.size(); i++) {
			intVector.push_back(v[i]);
		}
	}
	Rect(Pt a_, Pt b_, Pt c_, Pt d_) {
		a = a_;
		b = b_;
		c = c_;
		d = d_;
	}
	Rect(Pt arr[4]) {
		a = arr[0];
		b = arr[1];
		c = arr[2];
		d = arr[3];
	}
	Pt getA();
	Pt getB();
	Pt getC();
	Pt getD();
	Pt getCen();

	Rect genIniRect(Pt p, float m, float n, float A);
	
	float sumAr(vector<float>ar);
	float getCoordArea();

	void setName(string t) { name = t; }
	std::string getName() { return name; }

	void setParentVec(vector<Parent>); //area tree
	vector<Rect> getRectVector();

	void setIntVector(vector<int>);
	void incrementState();
	void clrState();

	void clrRectVector();
	void setup(Pt, Pt, Pt, Pt);
	void setup(Pt[4]);

	void drawRect();
	void drawRect(int);
	void drawRect(vector<Rect>);
	void drawRect(vector<Rect>, int);
	void drawRect(int re, int gr, int bl);
	
	Rect moveRect(float, float);

	//  int[0] = C  = max number of recursions - prevent endlessness;
	//  int[1] = re = recursion - state
	void subdivide(Rect, int, int, Parent); 
};