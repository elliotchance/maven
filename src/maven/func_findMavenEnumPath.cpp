/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_variables.h"

string findMavenEnumPath(MavenCompiler* c, string entity) {
	StringList items = split('.', trim(entity));
	int namespaceID, objectID;
	
	// we take off the array brackets [] and then add them on at the end
	string array = entity.substr(stripRawType(entity).length(), 10);
	entity = entity.substr(0, stripRawType(entity).length());
	
	if(isDataType(entity))
		return entity + array;
	
	if(items.length() == 1) {
		// if there is no namespace specified we will have to look for it
		// and recognise ambiguous objects
		vector<int> found;
		string a = stripRawType(items[0]);
		for(namespaceID = 0; namespaceID < c->namespaces.length(); ++namespaceID) {
			objectID = findEnumID(c, namespaceID, a);
			if(objectID >= 0) found.push_back(namespaceID);
		}
		--namespaceID;
		
		if(found.size() == 0) return MAVEN_INVALID;
		else if(found.size() == 1) {
			return c->namespaces[found[0]].name + "." + a + array;
		} else pushError(c, "Ambiguous class '%s'", a);
	} else if(items.length() == 2) {
		namespaceID = findNamespaceID(c, items[0]);
		if(namespaceID < 0) return MAVEN_INVALID;
		objectID = findEnumID(c, namespaceID, items[1]);
		if(objectID < 0) return MAVEN_INVALID;
		return items[0] + "." + items[1] + array;
	}
	
	return MAVEN_INVALID;
}
