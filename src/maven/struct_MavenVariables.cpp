/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

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
