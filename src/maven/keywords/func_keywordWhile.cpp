/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "scope.h"
#include "objects.h"
#include "output.h"

using namespace std;

bool keywordWhile(MavenCompiler* c, string line, string& close) {
	int actionStart;
	string question = getStatementQuestion(line, actionStart);
	string action = trim(line.substr(line.find(')', question.length()) + 1));
	
	StringList type;
	MavenMutability mut;
	// bug #38: make sure type is boolean or number
	string cpp = "while(" + dissectCode(c, trim(question), type, mut) + ")";
	
	// bug #39: there needs to be a smarter way to deal with do {} while();
	//if(action != "") {
		cpp += "{";
	
		// bug #40: needs to count '()' brackets
		cpp += dissectCode(c, action, type, mut) + ";";
		
		// closure
		close = "}/*while*/" + close;
	//} else cpp += ";";
	
	// !C003
	writeAutoCPPLine(c, objectCheckCPP(c));
	writeAutoCPPLine(c, cpp);
	
	return true;
}
