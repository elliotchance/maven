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

void MavenObjects::swap(int ID1, int ID2) {
	MavenObject* temp = objects[ID1];
	objects[ID1] = objects[ID2];
	objects[ID2] = temp;
}
