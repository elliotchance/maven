/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void printAllNamespaces(MavenCompiler* c) {
	for(int i = 0; i < c->namespaces.length(); ++i) {
		cout << c->namespaces[i].name << endl;
		for(int j = 0; j < c->namespaces[i].objects.length(); ++j) {
			cout << "  " << c->namespaces[i].objects[j].name << endl;
		}
	}
}

void die(string message) {
	cerr << message << endl;
	exit(1);
}
