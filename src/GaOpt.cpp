#include "GaOpt.h"

GaOpt::GaOpt(){ }

void GaOpt::addEntry(std::vector<int> ctrl, std::vector<Parent> parent, int s, int ite) {
	CtrlStr C(ctrl, s, ite); ctrlStrVec.push_back(C);
	ParentStr P(parent, s, ite); parentStrVec.push_back(P);
}

void GaOpt::propagateScores() {
	for (int i = 0; i < ctrlStrVec.size(); i++) {
		CtrlStr C = ctrlStrVec[i];
		int score = C.score;
		int gen = C.gen;
		//int n = gen*gen*score;
		int n = gen*score;
		for (int j = 0; j < n; j++) {
			//cout << "\nControl propagation \n";
			popCtrlStrVec.push_back(C);
		}
	}
	for (int i = 0; i < parentStrVec.size(); i++) {
		ParentStr P = parentStrVec[i];
		int score = P.score;
		int gen = P.gen;		
		//int n = gen*gen*score;
		int n = gen*score;
		for (int j = 0; j < n; j++) {
			//cout << "\nParent propagation \n";
			popParentStrVec.push_back(P);
		}
	}
}
void GaOpt::restrict(int t) {
	std::function<bool(CtrlStr, CtrlStr)> sortCtrl = SortCtrlDesc();
	std::sort(popCtrlStrVec.begin(), popCtrlStrVec.end(), sortCtrl);
	std::vector<CtrlStr>newPopCtrlStr;
	for (int i = 0; i < popCtrlStrVec.size(); i++) {
		if (newPopCtrlStr.size() > t) break;
		newPopCtrlStr.push_back(popCtrlStrVec[i]);
	}
	popCtrlStrVec.clear();
	for (int i = 0; i < newPopCtrlStr.size(); i++) {
		popCtrlStrVec.push_back(newPopCtrlStr[i]);
	}
	newPopCtrlStr.clear();

	std::function<bool(ParentStr, ParentStr)> sorter = SortParentDesc();
	std::sort(popParentStrVec.begin(), popParentStrVec.end(), sorter);
	std::vector<ParentStr>newPopParentStrVec;
	for (int i = 0; i < popParentStrVec.size(); i++) {
		if (newPopParentStrVec.size() > t) break;
		newPopParentStrVec.push_back(popParentStrVec[i]);
	}
	popCtrlStrVec.clear();
	for (int i = 0; i < newPopParentStrVec.size(); i++) {
		popParentStrVec.push_back(newPopParentStrVec[i]);
	}
	newPopParentStrVec.clear();

}
std::vector<CtrlStr> GaOpt::getCtrl(int n) {
	std::function<bool(CtrlStr, CtrlStr)> sortCtrl = SortCtrlDesc();
	std::sort(popCtrlStrVec.begin(), popCtrlStrVec.end(), sortCtrl);

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(popCtrlStrVec), std::end(popCtrlStrVec), rng);

	std::vector<CtrlStr>result; result.clear();
	for (int i = 0; i < popCtrlStrVec.size(); i++) {
		if (result.size() > n) break;
		result.push_back(popCtrlStrVec[i]);
	}
	return result;
}

std::vector<ParentStr> GaOpt::getParent(int n) {
	std::function<bool(ParentStr, ParentStr)> sorter = SortParentDesc();
	std::sort(popParentStrVec.begin(), popParentStrVec.end(), sorter);
	std::vector<ParentStr>result; result.clear();

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(popParentStrVec), std::end(popParentStrVec), rng);

	for (int i = 0; i < popParentStrVec.size(); i++) {
		if (result.size() > n) break;
		result.push_back(popParentStrVec[i]);
	}
	return result;
}

void GaOpt::crossControl() {
	for (int i = 0; i < popCtrlStrVec.size(); i++) {
		int a = ofRandom(0,popCtrlStrVec.size()-1);
		int b= ofRandom(0, popCtrlStrVec.size() - 1);
		CtrlStr A = popCtrlStrVec[a];
		CtrlStr B = popCtrlStrVec[b];
		std::vector<int> ctrlStrA = A.ctrlVec; 
		std::vector<int> ctrlStrB = B.ctrlVec;

	}
}