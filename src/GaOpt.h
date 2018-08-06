#pragma once

#include "ofMain.h"
#include "Area.h"
#include "ctrlVector.h"

class GaOpt
{
public:
	GaOpt();
	void addCtrlEntry(std::vector<int>, std::vector<Parent>, int);
private:
	std::vector< std::vector<int> > ctrlVec;
	std::vector< std::vector<Parent> > vecParentVec;
	std::vector<int> scoreVec;
};

