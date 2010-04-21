/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "objects.h"
#include "namespaces.h"
#include "variables.h"

// find class should eb smarted and take over objectExists?
vector<int> findClass(MavenCompiler* c, string entity, int& namespaceID, int& objectID) {
	// we only want to find the raw type
	StringList items = split('.', stripRawType(entity));
	vector<int> found;
	
	if(items.length() == 1) {
		namespaceID = -1;
		for(int i = 0; i < c->namespaces->length(); ++i) {
			objectID = findObjectID(c, i, entity);
			if(objectID >= 0) {
				namespaceID = i;
				found.push_back(objectID);
			}
		}
	} else if(items.length() == 2) {
		namespaceID = findNamespaceID(c, items[0]);
		found.push_back(findObjectID(c, namespaceID, items[1]));
	}
	
	if(found.size() > 0) objectID = found[0];
	else objectID = -1;
	return found;
}
