/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

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
