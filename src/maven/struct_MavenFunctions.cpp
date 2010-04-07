/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

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
