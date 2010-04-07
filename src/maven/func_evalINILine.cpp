/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

void evalINILine(MavenCompiler* c, string line, string& header) {
	line = trim(line);
	if(line.length() < 2) return;
	
	// ignore comments
	if(line[0] == '#') return;
	
	// header
	if(line[0] == '[') {
		header = line.substr(1, line.length() - 2);
		return;
	}
	
	// split =
	string key = "", value = "";
	for(int i = 0; i < line.length(); ++i) {
		if(line[i] == '=') break;
		else key += line[i];
	}
	value = trim(line.substr(key.length() + 1, line.length() - key.length() - 1));
	key = header + "." + trim(key);
	c->iniFile.setKey(key, value);
}
