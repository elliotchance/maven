/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"

bool enumExists(MavenCompiler* c, string name) {
	StringList items = split('.', name);
	int namespaceID = -1, objectID = -1;
	
	if(items.length() == 1) {
		// recognise ambiguous objects
		vector<int> found;
		for(namespaceID = 0; namespaceID < c->namespaces->length(); ++namespaceID) {
			objectID = findEnumID(c, namespaceID, items[0]);
			if(objectID >= 0) found.push_back(namespaceID);
		}
		--namespaceID;
		
		if(found.size() > 1) pushError(c, "Ambiguous enumerator '%s'", items[0]);
		return (found.size() == 1);
	} else if(items.length() == 2) {
		namespaceID = findNamespaceID(c, items[0]);
		if(namespaceID < 0) return false;;
		objectID = findEnumID(c, namespaceID, items[1]);
		return (objectID >= 0);
	}
	
	return false;
}
