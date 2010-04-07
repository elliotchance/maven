/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

MavenObjects::MavenObjects() {
}

int MavenObjects::length() {
	return objects.size();
}

MavenObject& MavenObjects::operator [](int element) {
	return objects[element];
}

void MavenObjects::push(MavenObject object) {
	objects.push_back(object);
}
