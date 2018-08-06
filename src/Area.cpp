#include "ofMain.h"

#include "Area.h"
#include <string>

Area::Area()
{
	/* 6547, 5544, 109, 4706, 8845, 5325, 2049, 2808, 6024, 3042 */
	areaVector.clear();
	areaVector.push_back(6547.0);
	areaVector.push_back(5544.0);
	areaVector.push_back(4815.0);
	areaVector.push_back(8845.0);
	areaVector.push_back(5325.0);
	areaVector.push_back(2049.0);
	areaVector.push_back(2808.0);
	areaVector.push_back(6024.0);
	areaVector.push_back(3042.0);
	/*  26985, 9243, 8593 */
	/*
	areaVector.clear();
	areaVector.push_back(26985.0);
	areaVector.push_back(9243.0);
	areaVector.push_back(8593.0);
	*/
	
}

vector<colArStr> Area::genColorVec() {
	colArStrVec.clear();
	for (int i = 0; i < areaVector.size(); i++) {
		int re = (int)(ofRandom(0, 1) * 255);
		int gr = (int)(ofRandom(0, 1) * 255);
		int bl = (int)(ofRandom(0, 1) * 255);
		colArStr colr(areaVector[i], re, gr, bl);
		colArStrVec.push_back(colr);
	}
	return colArStrVec;
}

float Area::getTotalAr() {
	double sum=0;
	for (int i = 0; i < areaVector.size(); i++) {
		sum += areaVector[i];
	}
	return sum;
}

void Area::initSubdiv() {
	splitV.clear();
	treeVec.clear();
	Tree tree("O", areaVector);
	treeVec.push_back(tree);
	subdiv(tree);

	std::function<bool(Tree, Tree)>sorter0 = SortName();
	std::sort(treeVec.begin(), treeVec.end(), sorter0);

	std::function<bool(Tree, Tree)>sorter1 = SortNameLength();
	std::sort(treeVec.begin(), treeVec.end(), sorter1);
}

void Area::subdiv(Tree tr) {
	std::vector<float> areaV = tr.getAreas();
	std::string parentName = tr.getName();
	
	int x = 1 + rand() % (areaV.size() - 1);
	std::vector<float> a0, a1;
	for (unsigned int i = 0; i < areaV.size(); i++) {
		if (i < x) {
			a0.push_back(areaV[i]);			
		}
		else {
			a1.push_back(areaV[i]);
		}
	}
	if (a0.size() > 1) {
		std::string name = parentName + "L";
		Tree T0(name, a0);
		subdiv(T0); treeVec.push_back(T0);
	}
	else {
		std::string name = parentName + "L";
		Tree T0(name, a0); treeVec.push_back(T0);
	}

	if (a1.size() > 1) {
		std::string name = parentName + "R";
		Tree T1(name, a1); 
		subdiv(T1); treeVec.push_back(T1);
	}
	else {
		std::string name = parentName + "R";
		Tree T1(name, a1); treeVec.push_back(T1);
	}
}

void Area::constructGraph() {
	parentVec.clear();
	for (int i = 0; i < treeVec.size(); i++) {
		std::string name0 = treeVec[i].name;
		int g = treeVec[i].name.length();
		Parent parent(name0, treeVec[i].getAreas());
		for (int j = 0; j < treeVec.size(); j++) {
			std::string name1 = treeVec[j].name;
			int e = treeVec[j].name.length();
			std::string seg = name1.substr(0, e - 1);
			std::string pos = name1.substr(e - 1, e);
			if(e == (g+1) && name0==seg){
				if (pos == "L") {
					Child childL(name1, treeVec[j].getAreas());
					parent.setL(childL);
				}
				else {
					Child childR(name1, treeVec[j].getAreas());
					parent.setR(childR);
				}					
			}
		}
		parentVec.push_back(parent);
	}
}

void Area::displayAreaVec(std::vector<float> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << ", ";
	}
}

void Area::displayGraph() {
	for (int i = 0; i < parentVec.size(); i++) {
		Parent parent = parentVec[i];
		std::string name = parent.name;
		std::string L = parent.L.name;
		std::string R = parent.R.name;
		if (L == "" && R=="") {
			std::cout << "parent : " << name << " "; displayAreaVec(parent.areas); cout << std::endl;
		}
		else {
			std::vector<float> pAreas = parent.areas;
			std::vector<float> LAreas = parent.L.areas;
			std::vector<float> RAreas = parent.R.areas;
			std::cout << "parent : " << name << "  "; displayAreaVec(parent.areas);  std::cout << std::endl;
			std::cout << "  child-L : " << L << "  "; displayAreaVec(parent.L.areas); std::cout << std::endl;
			std::cout << "  child-R : " << R << "  "; displayAreaVec(parent.R.areas); std::cout << std::endl;
		}
	}
}

std::vector<Parent> Area::getParentVec() {
	return parentVec;
}