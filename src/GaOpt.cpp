#include "GaOpt.h"

GaOpt::GaOpt(){ }

void GaOpt::addEntry(std::vector<int> ctrl, std::vector<Parent> parent, int s, int ite) {
	//THIS IS CALLED FROM EXTERNAL FOR LOOP
	//PART OF ITERATION: ADDING 1 ENTRY AT A TIME
	CtrlStr C(ctrl, s, ite); ctrlStrVec.push_back(C); 
	ParentStr P(parent, s, ite); parentStrVec.push_back(P);
}

void GaOpt::propagateScores(int T) {
	addNewParent(10); addNewControl(10, 10); //controls 10 iterations, 10 number of subdiv orientation
	cout << "initial Control Struct Population : " << popCtrlStrVec.size() << endl;
	cout << "initial Parents Struct Population : " << popParentStrVec.size() << endl;
	/* PROPAGATE - CONTROL VECTORS  #input T */
	for (int i = 0; i < ctrlStrVec.size(); i++) {
		CtrlStr C = ctrlStrVec[i];
		int score = C.score;
		int gen = C.gen;
		int n = T*score;
		for (int j = 0; j < n; j++) {
			popCtrlStrVec.push_back(C);
		}
	}
	/* CROSSING - CONTROL VECTORS  #input T */
	std::vector<CtrlStr> crossCtrlVec = crossControl(T);
	for (int i = 0; i < crossCtrlVec.size(); i++) {
		popCtrlStrVec.push_back(crossCtrlVec[i]);
	}
	/* PROPAGATE - CONTROL VECTORS  #input T */
	for (int i = 0; i < parentStrVec.size(); i++) {
		ParentStr P = parentStrVec[i];
		int score = P.score;
		int gen = P.gen;		
		int n = T*score;
		for (int j = 0; j < n; j++) {
			popParentStrVec.push_back(P);
		}
	}
}

std::vector<CtrlStr> GaOpt::getCtrl(int n) {
	/* RANDOMLY SHUFFLE CONTROL STRUCT VECTOR */
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(popCtrlStrVec), std::end(popCtrlStrVec), rng);

	std::vector<CtrlStr>result; result.clear();
	for (int i = 0; i < popCtrlStrVec.size(); i++) {
		if (result.size() > n) break;
		result.push_back(popCtrlStrVec[i]);
	}
	cout << "size of control population: " << popCtrlStrVec.size() << endl;
	return result;
}

std::vector<ParentStr> GaOpt::getParent(int n) {
	/* RANDOMLY SHUFFLE PARENT STRUCT VECTOR */
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(popParentStrVec), std::end(popParentStrVec), rng);
	
	std::vector<ParentStr>result; result.clear();
	for (int i = 0; i < popParentStrVec.size(); i++) {
		if (result.size() > n) break;
		result.push_back(popParentStrVec[i]);
	}
	cout << "size of parent population: " << popParentStrVec.size() << endl;
	return result;
}

std::vector<CtrlStr> GaOpt::crossControl(int T) {
	std::vector<CtrlStr> crossCtrlVec; crossCtrlVec.clear();
	for (int i = 0; i < T; i++) {
		int a = ofRandom(0,popCtrlStrVec.size()-1);
		int b= ofRandom(0, popCtrlStrVec.size() - 1);
		CtrlStr A = popCtrlStrVec[a]; int gen = A.gen; int score = A.score;
		CtrlStr B = popCtrlStrVec[b];
		std::vector<int> ctrlStrA = A.ctrlVec; 
		std::vector<int> ctrlStrB = B.ctrlVec;
		std::vector<int> ctrlStrC; ctrlStrC.clear();
		int n = ctrlStrA.size();
		for (int j = 0; j < ctrlStrA.size(); j++) {
			if (j < n / 2) {
				ctrlStrC.push_back(ctrlStrA[j]);
			}
			else {
				ctrlStrC.push_back(ctrlStrB[j]);
			}
		}
		int scoreR = (int)ofRandom(1, 10);
		CtrlStr X(ctrlStrC, scoreR, gen);
		crossCtrlVec.push_back(X);
	}
	return crossCtrlVec;
}

void GaOpt::addNewParent(int T) {
	/* ADD NEW AREA - PARENT-CHILD RELATIONSHIP */
	for (int i = 0; i<T; i++) {
		Area ar;
		ar.initSubdiv();					// initialize the sub-division module
		ar.constructGraph();				// construct parent-child relationships
		std::vector<Parent> parentVec; parentVec.clear();
		parentVec = ar.getParentVec();
		int scoreR = 1;//(int)ofRandom(1, 10);
		ParentStr P(parentVec, scoreR, 0);
		parentStrVec.push_back(P);
	}
}

void GaOpt::addNewControl(int T, int NUM) {
	/* ADD NEW CONTROL VECTOR */
	vector<int> cV; cV.clear();
	for (int i = 0; i < T; i++) {
		ctrlVector cv;						 // control vector
		/*  initialize the control vector */
		cV = cv.newIntVector(NUM);
		int scoreR = 1;// (int)ofRandom(1, 10);
		CtrlStr C(cV, scoreR, 1);
		ctrlStrVec.push_back(C);
	}
}

void GaOpt::restrictPopulation(int t, int T) {
	/* GET THE TOP RANKING CONTROL VECTORS */
	std::function<bool(CtrlStr, CtrlStr)> sorterCtrl = SortCtrlDesc();
	std::sort(popCtrlStrVec.begin(), popCtrlStrVec.end(), sorterCtrl);
	popCtrlStrVec.erase(popCtrlStrVec.begin()+10, popCtrlStrVec.end());

	auto rng1 = std::default_random_engine();
	std::shuffle(ctrlStrVec.begin(), ctrlStrVec.end(), rng1);
	ctrlStrVec.erase(ctrlStrVec.begin() + 10, ctrlStrVec.end());

	/* GET THE TOP RANKING PARENT-CHILD VECTORS #input t */
	std::function<bool(ParentStr, ParentStr)> sorterParent = SortParentDesc();
	std::sort(popParentStrVec.begin(), popParentStrVec.end(), sorterParent);
	popParentStrVec.erase(popParentStrVec.begin()+10, popParentStrVec.end());

	auto rng2 = std::default_random_engine();
	std::shuffle(parentStrVec.begin(), parentStrVec.end(), rng2);
	parentStrVec.erase(parentStrVec.begin() + 10, parentStrVec.end());
}

