#pragma once

#include "ofMain.h"
#include "Area.h"
#include "ctrlVector.h"
#include <random>

struct CtrlStr {
	std::vector<int> ctrlVec;
	int score;
	int gen;
	int intScore=0;
	CtrlStr(std::vector<int> c, int s, int g) {
		ctrlVec.clear();
		for (int i = 0; i < c.size(); i++) { ctrlVec.push_back(c[i]); }
		score = s;
		gen = g;
	}
	void setIntScore(int t) { intScore = t; }
};
struct SortCtrlDesc {
	bool operator() (CtrlStr a, CtrlStr b) {
		return (a.score > b.score);
	}
};

struct ParentStr {
	std::vector<Parent> parentVec;
	int score;
	int gen;
	int intScore = 0;
	ParentStr(std::vector<Parent> p, int s, int g) {
		parentVec.clear();
		for (int i = 0; i < p.size(); i++) { parentVec.push_back(p[i]); }
		score = s;
		gen = g;
	}
	void setIntScore(int t) { intScore = t; }

};
struct SortParentDesc {
	bool operator() (ParentStr a, ParentStr b) {
		return (a.score > b.score);
	}
};
class GaOpt
{
	/* 
	Learning / Optimization mechanism
	* each generation has 8 iterations
	* each iteration is stored as a single entry
	* generation number is registered
	* combined score is given to control vector & parent-child relationships
	* this is split into two parts: 
		* control vector 
		* parent-child Area relationships
	* data structs above keeps an account of individual generation metrics
	** SPLIT:
	* score-generation-parent-child relationship 
	* score-generation-control vector
	* iteration number helps develop the discounted reward function
	* propagate control vector by (int)(gen*gen*score)
	* propagate family-relationship by (int)(gen*gen*score)
	*/
public:
	GaOpt();

	/* ADD ENTRY : ctrl-vector, parent-child, score, iteration */
	void addEntry(std::vector<int>, std::vector<Parent>, int, int);

	/* PROPAGATE SCORES OVER GENERATIONS */
	void propagateScores();

	/* RETRIEVE RESULTS */
	std::vector<CtrlStr> getCtrl(int);
	std::vector<ParentStr> getParent(int);

	/* RANDOM SHUFFLES */
	int myrandom(int);

	/* RESTRICT */
	void restrict(int t);

private:
	std::vector<CtrlStr> ctrlStrVec;
	std::vector<CtrlStr> popCtrlStrVec;
	std::vector<ParentStr> parentStrVec;
	std::vector<ParentStr> popParentStrVec;
};


