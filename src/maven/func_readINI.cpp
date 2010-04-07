/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_init.h"

void readINI(MavenCompiler* c) {
	ifstream ifile;
	ifile.open(MAVEN_INI_LOCATION);
	if(!ifile.is_open()) {
		pushWarning(c, "Can't open %s", MAVEN_INI_LOCATION);
		return;
	}
	
	string line = "", header = "";
	while(!ifile.eof()) {
		char ch = ifile.get();
		
		if(ch == '\n') {
			evalINILine(c, line, header);
			line = "";
		} else line += ch;
	}
}
