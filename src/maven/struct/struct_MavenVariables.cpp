/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenVariables.h"

using namespace std;

MavenVariables::MavenVariables() {
}

void MavenVariables::push(MavenVariable var) {
	vars.push_back(var);
}

int MavenVariables::length() {
	return vars.size();
}

/**
 * @deprecated. Use at().
 */
MavenVariable& MavenVariables::operator[](int element) {
	return vars[element];
}

MavenVariable& MavenVariables::at(int element) {
	return vars[element];
}

string MavenVariables::getCPP(MavenCompiler* mc) {
	string r = "";
	for(int l = 0; l < vars.size(); ++l) {
		if(l) r += ", ";
		r += vars[l].getCPP(mc);
	}
	return r;
}

void MavenVariables::sortVariables() {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int numLength = vars.size(); 
	for(i = 1; (i <= numLength) && flag; ++i) {
		flag = 0;
		for(j = 0; j < (numLength - 1); ++j) {
			if(strcmp(vars[j + 1].name.c_str(), vars[j].name.c_str()) < 0) {
				swapVariable(j, j + 1);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}

void MavenVariables::swapVariable(int ID1, int ID2) {
	MavenVariable temp = vars[ID1];
	vars[ID1] = vars[ID2];
	vars[ID2] = temp;
}
