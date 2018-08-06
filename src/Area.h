#pragma once

struct Child {
	std::string name;
	std::vector<float> areas;
	Child(){}
	Child(std::string name_, std::vector<float>areas_) {
		name = name_;
		areas = areas_;
	}
};

struct Parent {
	std::string name;
	std::vector<float> areas;
	Parent() {};
	Parent(std::string name_, std::vector<float>areas_) {
		name = name_;
		areas = areas_;
	}
	Child L; Child R;
	void setL(Child L_) {
		L = L_;
	}
	void setR(Child R_) {
		R = R_;
	}
};

struct Tree {
	std::string name;
	std::vector<float> areas;
	bool L=0, R=0;
	Tree() { }
	Tree(std::string name_, std::vector<float> ar_) {
		name = name_;
		areas = ar_;
	}
	std::string getName() { return name; }
	std::vector<float> getAreas() { return areas; }
};

struct SortName {
	bool operator() (Tree a, Tree b) const {
		return a.name < b.name;
	}
};

struct SortNameLength {
	bool operator() (Tree a, Tree b) const {
		return a.name.length() < b.name.length();
	}
};

struct colArStr {
	int re, gr, bl;
	float area;
	colArStr(float area_, int re_, int gr_, int bl_) {
		re = re_;
		gr = gr_;
		bl = bl_;
		area = area_;
	}
};

class Area
{
private:
	std:: vector<float> areaVector;
	std:: vector< std::vector<float> > splitV;
	std:: vector<int> markers;
	std:: vector<Tree> treeVec;
	std:: vector<Parent> parentVec;
	std:: vector<colArStr> colArStrVec;
public:
	Area();
	float getTotalAr();
	void initSubdiv();
	
	/* USING THE STRUCT AS A DATA STUCTURE */
	void subdiv(Tree); //new subdiv based on tree
	void constructGraph();
	void displayGraph();
	void displayAreaVec(std::vector<float> vec);
	std::vector<Parent> getParentVec();
	vector<colArStr> genColorVec();  
};