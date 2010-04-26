/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_OBJECTS_H
#define _MAVEN_STRUCT_OBJECTS_H 1

#include "maven.h"

struct MavenObject;

class MavenObjects {
private:
	vector<MavenObject*> objects;
	
public:
	MavenObjects();
	int length();
	MavenObject* operator [](int element);
	MavenObject* at(int element);
	void push(MavenObject* object);
	
	void swap(int ID1, int ID2);
};

#endif
