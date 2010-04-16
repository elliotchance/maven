/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_errors.h"

void printErrors(MavenCompiler* c) {
	for(int i = 0; i < c->errors.length(); ++i) {
		if(c->errors[i].level == MAVEN_ERROR) cerr << "Error";
		else if(c->errors[i].level == MAVEN_WARNING) {
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
		
		// because errors are pushed in a chronolical order, if there are multiple
		// errors on the same line we can reverse them to show the path of what went wrong
		int grouped = 0;
		while(i + grouped < c->errors.length() &&
			  c->errors[i].file == c->errors[i + grouped].file &&
			  c->errors[i].line == c->errors[i + grouped].line)
			++grouped;
		
		reverseErrors(c, i, grouped);
		int pad = 0;
		string msg = "";
		if(c->errors[i].file.length() > 0)
			msg = string(" (") + c->errors[i].file + ", line " +
			intToString(c->errors[i].line) + "): ";
		else msg = ": ";
		pad = msg.length();
		cerr << msg;
		
		for(int j = 0; j < grouped; ++j) {
			// this is to align the '>>'
			if(j > 0) {
				//for(int p = 0; p < pad; ++p) cerr << " ";
				fprintf(stderr, "  >> ");
			}
			fprintf(stderr, c->errors[i + j].message.c_str(),
					c->errors[i + j].arg1.c_str(), c->errors[i + j].arg2.c_str());
			cerr << endl;
		}
		
		i += grouped;
	}
}
