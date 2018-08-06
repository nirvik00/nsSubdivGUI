#pragma once

#include "ofMain.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "time.h"



class ctrlVector
{
private:
	int num;
	vector<int> intVector;

public:
	ctrlVector() {
	}
	vector<int> newIntVector(int);
	void displayVector();
};

