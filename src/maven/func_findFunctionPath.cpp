/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_find.h"
#include "compiler_errors.h"

string findFunctionPath(MavenCompiler* c, string entity, MavenVariables args, int& namespaceID, int& objectID, int& funcID) {
	StringList items = split('.', entity);
	
	if(items.length() == 1) {
		namespaceID = findNamespaceID(c, c->currentNamespace);
		objectID = findObjectID(c, namespaceID, c->currentClass);
		funcID = findFunctionID(c, namespaceID, objectID, items[0], args);
		if(funcID >= 0)
			return c->namespaces->at(namespaceID).name + "::" +
				   c->namespaces->at(namespaceID).objects->at(objectID)->name + "::" + items[0];
		//if(funcID >= 0 && namespaces->at(namespaceID).objects->at(objectID)->functions[funcID].alias_system)
		//	return items[0];
		
		//if(namespaces->at(namespaceID).objects->at(objectID).name != MAVEN_BARE_CLASS)
			return c->namespaces->at(namespaceID).name + "::" +
		           c->namespaces->at(namespaceID).objects->at(objectID)->name + "::" + items[0];
		//return namespaces->at(namespaceID).name + "::" + items[0];
	} else if(items.length() == 2) {
		// if there is no namespace specified we will have to look for it
		// and recognise ambiguous objects
		
		namespaceID = objectID = funcID = -1;
		string vp = findVariablePath(c, items[0], namespaceID, objectID, funcID);
		if(namespaceID >= 0 && objectID >= 0 && funcID >= 0) {
			vp = c->namespaces->at(namespaceID).name + "::" +  c->namespaces->at(namespaceID).objects->at(objectID)->name + "$static::" +
				 items[0] + "->" + items[1];
			string origType = c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(funcID).type;
			namespaceID = findNamespaceID(c, getFirstEntity(origType));
			objectID = findObjectID(c, namespaceID, getLastEntity(origType));
			funcID = findFunctionID(c, namespaceID, objectID, items[1], args, false);
			return vp;
		}
		
		// first we will try the first argumument as the name of the class
		vector<int> found = findClass(c, items[0], namespaceID, objectID);
		
		// if we didnt find it, maybe it's a variable
		if(found.size() == 0) {
			namespaceID = objectID = -1;
			
			// bug #46: local scope
			/*for(int i = 0; i < localScope[localScope.size() - 1].length(); ++i) {
				if(localScope[localScope.size() - 1][i].name == items[i]) {
					findClass(localScope[localScope.size() - 1][i].type, namespaceID, objectID);
					if(namespaceID >= 0 && objectID >= 0) {
						funcID = findFunctionID(c, namespaceID, objectID, items[1], args, false);
						return items[0] + "->" + items[1];
					}
				}
			}*/
			
			// globals here
			return MAVEN_INVALID;
		} else if(found.size() == 1) {
			objectID = findObjectID(c, namespaceID, items[0]);
			funcID = findFunctionID(c, namespaceID, objectID, items[1], args);
			if(funcID < 0) return MAVEN_INVALID;
			return c->namespaces->at(namespaceID).name + "::" + items[0] + "::" + items[1];
		} else pushError(c, "Ambiguous class '%s'", items[1]);
	} else if(items.length() == 3) {
		namespaceID = findNamespaceID(c, items[0]);
		if(namespaceID < 0) return MAVEN_INVALID;
		objectID = findObjectID(c, namespaceID, items[1]);
		if(objectID < 0) return MAVEN_INVALID;
		funcID = findFunctionID(c, namespaceID, objectID, items[2], args);
		return items[0] + "::" + items[1] + "::" + items[2];
	}
	
	return MAVEN_INVALID;
}
