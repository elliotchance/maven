/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_find.h"

string findLocalScope(MavenCompiler* c, string name, MavenVariable& r) {
	if(name == "") {
		r = MavenVariable();
		return "";
	}
	
	// its important to note that 'name' may come in like 'a.b' so we have to split it up
	string path = "";
	int namespaceID, objectID, variableID;
	StringList parts = split('.', name);
	
	// first find the localScope variable
	for(int i = 0; i < c->localScope.size(); ++i) {
		for(int j = 0; j < c->localScope[i].length(); ++j) {
			if(c->localScope[i][j].name == parts[0]) {
				r = c->localScope[i][j];
				path = r.name;
			}
		}
	}
	
	// ok now we have to go through the other parts to get its true type
	for(int i = 1; i < parts.length(); ++i) {
		findClass(c, r.type, namespaceID, objectID);
		if(namespaceID >= 0 && objectID >= 0) {
			variableID = findVariableID(c, namespaceID, objectID, parts[i]);
			if(variableID >= 0) {
				path += "->" + parts[i];
				r = c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(variableID);
			} else {
				// bug #45: ERROR
			}
		} else {
			// bug #45: ERROR
		}
	}
	
	// not found
	return path;
}
