/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void printWarnings(MavenCompiler* c) {
	for(int i = 0; i < c->errors.length() && c->errors[i].level == MAVEN_WARNING; ++i) {
		cerr << "Warning";
		if(c->errors[i].file != "" || c->errors[i].line > 0)
			cerr << " (";
		if(c->errors[i].file != "")
			cerr << c->errors[i].file;
		if(c->errors[i].line > 0)
			cerr << ", line " << c->errors[i].line;
		if(c->errors[i].file != "" || c->errors[i].line > 0)
			cerr << ")";
		cerr << ": ";
		fprintf(stderr, c->errors[i].message.c_str(), c->errors[i].arg1.c_str(),
				c->errors[i].arg2.c_str());
		cerr << endl;
		continue;
	}
}
