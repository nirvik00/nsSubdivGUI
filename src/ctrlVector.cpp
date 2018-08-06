#include "ctrlVector.h"
vector<int> ctrlVector::newIntVector(int num) {
	
	intVector.clear();
	//cout << "\nControl Vector display :  ";
	for (unsigned int i = 0; i < num; i++) {
		int r = ofRandom(2);
		intVector.push_back(r);
		//cout << r << ",";
	}
	//cout << endl;
	return intVector;
}

void ctrlVector::displayVector() {
	cout << "\ncontrol Vector : ";
	for (unsigned int i = 0; i < intVector.size(); i++) {
		cout << intVector[i] << ", ";
	}
	cout << endl;
}