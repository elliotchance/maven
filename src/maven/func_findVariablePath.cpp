/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"

// bug #43: is this being used anymore?
string findVariablePath(MavenCompiler* c, string entity, int& namespaceID, int& objectID, int& variableID) {
	// the difficulty with this is that the number of dots doesnt indicate which part (if any)
	// is the namespace, class, variable and subvariables. So the way we do it is to try the first
	// part as a namespace, then try it as a class etc
	
	// split on the dot
	StringList parts = split('.', entity);
	if(parts.length() == 0) return "";
	namespaceID = -1;
	objectID = -1;
	variableID = -1;
	
	// 1. is the first part a namespace?
	for(int i = 0; i < c->namespaces->length(); ++i) {
		if(c->namespaces->at(i).name == parts[0]) {
			
			// now look for the class
			bool foundClass = false;
			for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
				if(c->namespaces->at(i).objects->at(j)->name == parts[1]) {
					foundClass = true;
					
					// now look for the variable
					for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
						if(c->namespaces->at(i).objects->at(j)->variables->at(k).name == parts[2]) {
							namespaceID = i;
							objectID = j;
							variableID = k;
							string r = c->namespaces->at(i).name + "::" + c->namespaces->at(i).objects->at(j)->name;
							if(c->namespaces->at(i).objects->at(j)->variables->at(k).isStatic)
								r += "$static";
							r += string("::") + c->namespaces->at(i).objects->at(j)->variables->at(k).name;
							return r;
						}
					}
					
					pushError(c, "%s does not have the member variable %s", parts[0] + "." + parts[1], parts[2]);
					return MAVEN_INVALID;
				}
			}
			if(!foundClass) {
				pushError(c, "class '%s' does not belong to namespace '%s'", parts[1], parts[0]);
				return MAVEN_INVALID;
			}
		}
	}
	
	// 2. now test as a class name, making sure it's not ambiguous
	vector<int> ambig;
	for(int i = 0; i < c->namespaces->length(); ++i)
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j)
			if(c->namespaces->at(i).objects->at(j)->name == parts[0])
				ambig.push_back(i);
				
	if(ambig.size() == 1) {
		return findVariablePath(c, c->namespaces->at(ambig[0]).name + "." + entity, namespaceID, objectID, variableID);
	} else if(ambig.size() > 1) {
		string belong = "";
		for(int i = 0; i < ambig.size(); ++i) {
			if(belong != "") belong += ", ";
			belong += c->namespaces->at(ambig[i]).name;
		}
		pushError(c, "%s is ambiguous, belonging to %s", parts[0], belong);
	}
	
	// 3. now look through all bare classes
	for(int i = 0; i < c->namespaces->length(); ++i)
		for(int j = 0; j < c->namespaces->at(i).objects->at(0)->variables->length(); ++j)
			if(c->namespaces->at(i).objects->at(0)->variables->at(j).name == parts[0])
				ambig.push_back(i);
	
	if(ambig.size() == 1) {
		return findVariablePath(c, c->namespaces->at(ambig[0]).name + ".nil." + entity, namespaceID, objectID, variableID);
	} else if(ambig.size() > 1) {
		string belong = "";
		for(int i = 0; i < ambig.size(); ++i) {
			if(belong != "") belong += ", ";
			belong += c->namespaces->at(ambig[i]).name;
		}
		pushError(c, "%s is ambiguous, belonging to %s", parts[0], belong);
	}
	
	// 4. now we look in the localScope
	string path = "";
	for(int i = 0; i < c->localScope.size(); ++i) {
		for(int j = 0; j < c->localScope[i].length(); ++j) {
			if(c->localScope[i][j].name == parts[0]) {
				variableID = MAVEN_LOCALSCOPE;
				return c->localScope[i][j].name;
			}
		}
	}
	
	// 5. it may be the current class (or even inherited)
	namespaceID = findNamespaceID(c, c->currentNamespace);
	objectID = findObjectID(c, namespaceID, c->currentClass);
	if(namespaceID >= 0 && objectID >= 0) {
		for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++i) {
			if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i).name == parts[0]) {
				variableID = i;
				return parts[0];
			}
		}
	}
	
	return MAVEN_INVALID;
}
