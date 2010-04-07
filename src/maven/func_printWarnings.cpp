/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void printWarnings(MavenCompiler* c) {
	for(int i = 0; i < c->errors.length() && c->errors[i].level == MAVEN_WARNING; ++i) {
		cerr << "Warning (" << c->errors[i].file << ", line " << c->errors[i].line << "): ";
		fprintf(stderr, c->errors[i].message.c_str(), c->errors[i].arg1.c_str(), c->errors[i].arg2.c_str());
		cerr << endl;
		continue;
	}
}
