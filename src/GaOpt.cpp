#include "GaOpt.h"



GaOpt::GaOpt(){ }

void GaOpt::addCtrlEntry(std::vector<int> ctrl, std::vector<Parent> parent, int s) {
	ctrlVec.push_back(ctrl);
	vecParentVec.push_back(parent);
	scoreVec.push_back(s);
}

