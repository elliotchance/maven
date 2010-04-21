/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenObjects.h"

using namespace std;

MavenObjects::MavenObjects() {
}

int MavenObjects::length() {
	return objects.size();
}

MavenObject* MavenObjects::operator [](int element) {
	return objects[element];
}

MavenObject* MavenObjects::at(int element) {
	return objects[element];
}

void MavenObjects::push(MavenObject* object) {
	objects.push_back(object);
}
