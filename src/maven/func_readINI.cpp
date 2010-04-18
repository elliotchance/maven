/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_compilefile.h"
#include "compiler_errors.h"
#include "compiler_init.h"
#include "compiler_strings.h"

void readINI(MavenCompiler* c) {
	ifstream ifile;
	string maven_ini_location = locateMavenINI(c);
	
	// we need the maven.ini
	if(maven_ini_location == "") {
		pushError(c, "maven.ini could not be located");
		return;
	}
	
	ifile.open(maven_ini_location.c_str());
	if(!ifile.is_open()) {
		pushWarning(c, "Can't open %s", maven_ini_location);
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
