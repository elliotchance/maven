/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "doc.h"

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
