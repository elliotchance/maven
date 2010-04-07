/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "keywords.h"
#include "compiler_strings.h"
#include "compiler_dissect.h"
#include "compiler_compilefile.h"
#include "compiler_variables.h"

using namespace std;

bool keywordWhile(MavenCompiler* c, string line, string& close) {
	int actionStart;
	string question = getStatementQuestion(line, actionStart);
	string action = trim(line.substr(line.find(')', question.length()) + 1));
	
	StringList type;
	MavenMutability mut;
	// FIXME: make sure type is boolean or number
	string cpp = "while(" + dissectCode(c, trim(question), type, mut) + ")";
	
	// FIXME: there needs to be a smarter way to deal with do {} while();
	//if(action != "") {
		cpp += "{";
	
		// FIXME: needs to count '()' brackets
		cpp += dissectCode(c, action, type, mut) + ";";
		
		// closure
		close = "}/*while*/" + close;
	//} else cpp += ";";
	
	// !C003
	writeAutoCPPLine(c, objectCheckCPP(c));
	writeAutoCPPLine(c, cpp);
	
	return true;
}
