/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_dissect.h"
#include "compiler_find.h"
#include "compiler_operators.h"

using namespace std;

string keywordReturn(MavenCompiler* c, string line) {
	// we have to be in a function to use this
	if(c->currentFunction == "") {
		pushError(c, "Can not return out of non-function");
		return MAVEN_INVALID;
	}
	
	// it could be a void return
	if(line.length() == 6)
		return "return";
	
	StringList types;
	MavenMutability mut;
	string newCode = dissectCode(c, line.substr(7, line.length() - 7), types, mut);
	
	// check the return type matches the function its in
	int nID = findNamespaceID(c, c->currentNamespace);
	int oID = findObjectID(c, nID, c->currentClass);
	for(int i = 0; i < c->namespaces->at(nID).objects->at(oID)->functions->length(); ++i) {
		if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).name == c->currentFunction) {
			if(canCastBetween(c, types.join(","), c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType)) {
				return "return " + newCode;
			} else {
				pushError(c, "Can not cast return type %s to %s", types.join(","),
						  c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType);
				return MAVEN_INVALID;
			}
		}
	}
	
	// if it gets to here something really bad has gone wrong
	return MAVEN_INVALID;
}
