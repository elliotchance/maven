/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_constants.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_errors.h"
#include "compiler_variables.h"

string findObjectPath(MavenCompiler* c, string entity, bool includePointer) {
	// for variable length arguments
	entity = trim(entity);
	if(entity == "...")
		return "maven::objectArray*";
	
	StringList items = split('.', stripRawType(entity));
	int namespaceID, objectID;
	
	// take off the array
	int arrayDepth = getArrayDepth(entity);
	entity = stripRawType(entity);
	
	string pntr = "";
	for(int i = 0; i < arrayDepth; ++i)
		pntr += "*";
	
	if(enumExists(c, entity)) {
		if(arrayDepth == 0)
			pntr += "*";
		else return "maven::intArray*";
	} else if(!isDataType(entity)) {
		if(arrayDepth == 0)
			pntr += "*";
		else return "maven::objectArray*";
	} else {
		if(arrayDepth == 0)
			return entity;
		else return "maven::" + entity + "Array*";
	}
	if(!includePointer) pntr = "";
	
	if(items.length() == 1) {
		// if there is no namespace specified we will have to look for it
		// and recognise ambiguous objects
		vector<int> found;
		for(namespaceID = 0; namespaceID < c->namespaces.length(); ++namespaceID) {
			objectID = findObjectID(c, namespaceID, items[0]);
			if(objectID >= 0) found.push_back(namespaceID);
			else {
				objectID = findEnumID(c, namespaceID, items[0]);
				if(objectID >= 0) found.push_back(namespaceID);
			}
		}
		--namespaceID;
		
		if(found.size() == 0) return MAVEN_INVALID;
		else if(found.size() == 1) {
			return c->namespaces[found[0]].name + "::" + items[0] + pntr;
		} else pushError(c, "Ambiguous class '%s'", items[0]);
	} else if(items.length() == 2) {
		namespaceID = findNamespaceID(c, items[0]);
		if(namespaceID < 0) return MAVEN_INVALID;
		
		objectID = findObjectID(c, namespaceID, items[1]);
		if(objectID < 0) {
			objectID = findEnumID(c, namespaceID, items[1]);
			if(objectID >= 0) return "int";
			else return MAVEN_INVALID;
		}
		
		return items[0] + "::" + items[1] + pntr;
	}
	
	return MAVEN_INVALID;
}
