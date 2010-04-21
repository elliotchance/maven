/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "namespaces.h"

int findEnumID(MavenCompiler* c, int namespaceID, string enumName) {
	// enum name is allowed to be in the form namespace.enumName
	StringList parts = split('.', enumName);
	if(parts.length() > 1) {
		namespaceID = findNamespaceID(c, parts[0]);
		enumName = parts[1];
	}
	
	if(namespaceID < 0) return -1;
	for(int i = 0; i < c->namespaces->at(namespaceID).enums.size(); ++i)
		if(c->namespaces->at(namespaceID).enums[i].name == enumName)
			return i;
	return -1;
}
