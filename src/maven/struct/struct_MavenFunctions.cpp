/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenFunctions.h"

MavenFunctions::MavenFunctions() {
}

void MavenFunctions::push(MavenFunction func) {
	funcs.push_back(func);
}

int MavenFunctions::length() {
	return funcs.size();
}

MavenFunction& MavenFunctions::operator[](int element) {
	return funcs[element];
}

MavenFunction& MavenFunctions::at(int element) {
	return funcs[element];
}

void MavenFunctions::sortFunctions() {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int numLength = funcs.size(); 
	for(i = 1; (i <= numLength) && flag; ++i) {
		flag = 0;
		for(j = 0; j < (numLength - 1); ++j) {
			if(strcmp(funcs[j + 1].name.c_str(), funcs[j].name.c_str()) < 0) {
				swapFunction(j, j + 1);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}

void MavenFunctions::swapFunction(int ID1, int ID2) {
	MavenFunction temp = funcs[ID1];
	funcs[ID1] = funcs[ID2];
	funcs[ID2] = temp;
}
