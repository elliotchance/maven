/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "objects.h"
#include "enums.h"
#include "constants.h"
#include "namespaces.h"

MavenVariable dissectVariable(MavenCompiler* c, string line) {
	MavenVariable v;
	StringList parts = smartTokens(line);
	v.atLine = c->lineNumber;
	
	// variable length arguments
	if(trim(line) == "...") {
		v.type = "maven.Object[]";
		v.name = "varargs";
		return v;
	}
	
	// read keywords in order
	if(trim(line) == "") return v;
	int i = 0;
	
	if(parts[i] == "public") {
		v.isPublic = true;
		++i;
	} else if(parts[i] == "private") {
		v.isPublic = false;
		++i;
	}
	
	if(parts[i] == "constant") {
		v.mutability = MU_CONSTANT;
		++i;
	}
	if(parts[i] == "static") {
		v.isStatic = true;
		++i;
	}
	
	v.type = parts[i++];
	
	int nID = findNamespaceID(c, c->currentNamespace);
	smartAssert(nID >= 0);
	int enumID = findEnumID(c, nID, v.type);
	
	if(!isDataType(v.type) && enumID < 0)
		v.type = findMavenObjectPath(c, v.type);
	if(enumID >= 0)
		v.type = c->currentNamespace + "." + c->namespaces->at(nID).enums[enumID].name;
	
	v.name = parts[i++];
	return v;
}
