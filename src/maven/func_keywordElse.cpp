/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "keywords.h"
#include "compiler_dissect.h"
#include "compiler_strings.h"
#include "compiler_compilefile.h"

using namespace std;

bool keywordElse(MavenCompiler* c, string line, string& close) {
	// bug #27: some way to check that it immediatly follows an 'if'
	StringList types;
	MavenMutability mut;
	string preaction = trim(line.substr(4, line.length() - 4));
	
	// !C001
	if(startsWith(preaction, "if")) {
		writeAutoCPPLine(c, string("else "));
		keywordIf(c, preaction, close);
		return true;
	}
	if(startsWith(preaction, "for")) {
		writeAutoCPPLine(c, string("else {"));
		close = "}/*else*/" + close;
		keywordFor(c, preaction, close);
		return true;
	}
	if(startsWith(preaction, "while")) {
		writeAutoCPPLine(c, string("else {"));
		close = "}/*else*/" + close;
		keywordWhile(c, preaction, close);
		return true;
	}
	
	writeAutoCPPLine(c, string("else {") + dissectCode(c, preaction, types, mut) + ";");
	close = "}/*else*/" + close;
	return true;
}
