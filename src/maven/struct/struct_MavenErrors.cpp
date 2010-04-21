/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenErrors.h"

using namespace std;

MavenErrors::MavenErrors() {
}

int MavenErrors::length() {
	return errors.size();
}

void MavenErrors::clear() {
	errors.clear();
}

MavenError& MavenErrors::operator [](int element) {
	return errors[element];
}

void MavenErrors::push(MavenError error) {
	errors.push_back(error);
}
