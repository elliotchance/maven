/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void printAllNamespaces(MavenCompiler* c) {
	for(int i = 0; i < c->namespaces->length(); ++i) {
		cout << "Namespace: " << c->namespaces->at(i).name << endl;
		if(c->namespaces->at(i).objects->length() < 1000) {
			for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
				cout << "  Class: " << c->namespaces->at(i).objects->at(j)->name << endl;
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
					cout << "    Variable: " << c->namespaces->at(i).objects->at(j)->variables->at(k).name << endl;
				}
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
					cout << "    Function: " << c->namespaces->at(i).objects->at(j)->functions->at(k).name << endl;
				}
			}
		} else cout << "  DEAD, reports " << c->namespaces->at(i).objects->length() << " classes" << endl;
	}
}

void die(string message) {
	cerr << message << endl;
	exit(1);
}
