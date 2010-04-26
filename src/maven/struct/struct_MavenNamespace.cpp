/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenNamespace.h"
#include "struct_MavenObject.h"

MavenNamespace::MavenNamespace() {
	objects = new MavenObjects();
}

MavenNamespace::~MavenNamespace() {
	// free(objects)
}

void MavenNamespace::sortObjects() {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int numLength = objects->length(); 
	for(i = 1; (i <= numLength) && flag; ++i) {
		flag = 0;
		for(j = 0; j < (numLength - 1); ++j) {
			if(strcmp(objects->at(j + 1)->name.c_str(), objects->at(j)->name.c_str()) < 0) {
				objects->swap(j, j + 1);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}

void MavenNamespace::sortEnums() {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int numLength = enums.size(); 
	for(i = 1; (i <= numLength) && flag; ++i) {
		flag = 0;
		for(j = 0; j < (numLength - 1); ++j) {
			if(strcmp(enums[j + 1].name.c_str(), enums[j].name.c_str()) < 0) {
				swapEnum(j, j + 1);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}

void MavenNamespace::swapEnum(int ID1, int ID2) {
	MavenEnum temp = enums[ID1];
	enums[ID1] = enums[ID2];
	enums[ID2] = temp;
}
