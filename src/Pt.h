#pragma once
#include <cmath>
#include "ofMain.h"

class Pt
{
public:
	float x;
	float y;
	vector<Pt> ptVec;

	Pt(float a, float b) {
		x = a;
		y = b;
	}
	Pt(){}

	void setup(float, float);
	void setup(vector<Pt>);
	void drawPt();//black, lw=10
	void drawPt(int, int , int);//color
	void drawPt(int, int, int, int);//color, linewidth
	void drawPtVec();
	float distance(Pt b);
};

