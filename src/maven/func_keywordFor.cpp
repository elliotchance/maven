/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "keywords.h"
#include "compiler_errors.h"
#include "compiler_strings.h"
#include "compiler_dissect.h"
#include "compiler_constants.h"
#include "compiler_push.h"
#include "compiler_find.h"
#include "compiler_compilefile.h"
#include "compiler_variables.h"

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
	
	// FIXME: check that the 'middle part' of the 'for' is a boolean or number type
	string cpp = "for(" + init;
	cpp += "; " + dissectCode(c, trim(qp[1]), type, mut);
	cpp += "; " + dissectCode(c, trim(qp[2]), type, mut) + "){";
	
	// FIXME: needs to count '()' brackets
	cpp += dissectCode(c, trim(line.substr(line.find(')', question.length()) + 1)), type, mut) + ";";
	
	// closure
	close = "}/*for*/" + close;
	
	// !C003
	writeAutoCPPLine(c, objectCheckCPP(c));
	writeAutoCPPLine(c, cpp);
	
	return true;
}
