/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenNamespaces.h"
#include "struct_MavenNamespace.h"

MavenNamespaces::MavenNamespaces() {
}

int MavenNamespaces::length() {
	return namespaces.size();
}

MavenNamespace& MavenNamespaces::operator [](int element) {
	return namespaces[element];
}

MavenNamespace& MavenNamespaces::at(int element) {
	return namespaces[element];
}

void MavenNamespaces::push(MavenNamespace* ns) {
	namespaces.push_back(*ns);
}

void MavenNamespaces::sortNamespaces() {
	int i, j, flag = 1;       // set flag to 1 to start first pass
	MavenNamespace* temp;     // holding variable
	int numLength = namespaces.size(); 
	for(i = 1; (i <= numLength) && flag; ++i) {
		flag = 0;
		for(j = 0; j < (numLength - 1); ++j) {
			if(strcmp(at(j + 1).name.c_str(), at(j).name.c_str()) < 0) {
				swap(j, j + 1);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}

void MavenNamespaces::swap(int ID1, int ID2) {
	MavenNamespace temp = namespaces[ID1];
	namespaces[ID1] = namespaces[ID2];
	namespaces[ID2] = temp;
}
