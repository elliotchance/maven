/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "scope.h"
#include "keywords.h"
#include "output.h"
#include "objects.h"

using namespace std;

bool keywordIf(MavenCompiler* c, string line, string& close) {
	int actionStart;
	StringList questiontype, actiontype;
	MavenMutability mut, mut2;
	string question = dissectCode(c, getStatementQuestion(line, actionStart), questiontype, mut);
	
	// before we dissect the action we need to make sure these is no extra statements
	string preaction = trim(line.substr(actionStart, line.length() - actionStart));
	
	// !C001
	if(startsWith(preaction, "if")) {
		writeAutoCPPLine(c, string("if(") + question + ") {");
		close = "}/*if*/" + close;
		keywordIf(c, preaction, close);
		return true;
	}
	if(startsWith(preaction, "for")) {
		writeAutoCPPLine(c, string("if(") + question + ") {");
		close = "}/*if*/" + close;
		keywordFor(c, preaction, close);
		return true;
	}
	if(startsWith(preaction, "while")) {
		writeAutoCPPLine(c, string("if(") + question + ") {");
		close = "}/*if*/" + close;
		keywordWhile(c, preaction, close);
		return true;
	}
	
	string action = dissectCode(c, preaction, actiontype, mut2);
	
	// !C003
	writeAutoCPPLine(c, objectCheckCPP(c));
	writeAutoCPPLine(c, string("if(") + question + ") {");
	if(trim(action) != "")
		writeAutoCPPLine(c, action + ";");
	close = "}/*if*/" + close;
	
	return true;
}
