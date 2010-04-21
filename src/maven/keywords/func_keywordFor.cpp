/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "enums.h"
#include "constants.h"
#include "scope.h"
#include "output.h"
#include "objects.h"

using namespace std;

bool keywordFor(MavenCompiler* c, string line, string& close) {
	int actionStart;
	string question = getStatementQuestion(line, actionStart);
	StringList qp = split(';', question);
	
	if(qp.length() != 3) {
		pushError(c, "Incomplete for statement");
		return false;
	}
	
	StringList type;
	MavenMutability mut;
	StringList tokens = split(' ', trim(qp[0]));
	string init = "";
	if(tokens.length() > 0) {
		MavenVariable v;
		
		// look for a type
		if(isDataType(tokens[0]) || objectExists(c, tokens[0]) || enumExists(c, tokens[0])) {
			v.type = tokens[0];
			v.name = tokens[1];
			init = v.type + " " + v.name;
			if(tokens.length() > 2)
				init += string(" = ") + dissectCode(c, trim(tokens.join(" ", 3, tokens.length() - 1)), type, mut);
		} else init = dissectCode(c, trim(qp[0]), type, mut);
		
		pushLocalScope(c, v);
	}
	
	// bug #28: check that the 'middle part' of the 'for' is a boolean or number type
	string cpp = "for(" + init;
	cpp += "; " + dissectCode(c, trim(qp[1]), type, mut);
	cpp += "; " + dissectCode(c, trim(qp[2]), type, mut) + "){";
	
	// bug #29: needs to count '()' brackets
	cpp += dissectCode(c, trim(line.substr(line.find(')', question.length()) + 1)), type, mut) + ";";
	
	// closure
	close = "}/*for*/" + close;
	
	// !C003
	writeAutoCPPLine(c, objectCheckCPP(c));
	writeAutoCPPLine(c, cpp);
	
	return true;
}
