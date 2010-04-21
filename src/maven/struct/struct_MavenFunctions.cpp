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
