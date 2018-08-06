#include "GaOpt.h"

GaOpt::GaOpt(){ }

void GaOpt::addCtrlEntry(std::vector<int> ctrl, std::vector<Parent> parent, int s, int ite) {
	CtrlStr C(ctrl, s, ite); ctrlStrVec.push_back(C);
	ParentStr P(parent, s, ite); parentStrVec.push_back(P);
}

void GaOpt::propagateScores() {
	for (int i = 0; i < ctrlStrVec.size(); i++) {
		
	}
}

