/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "enums.h"
#include "namespaces.h"
#include "variables.h"
#include "constants.h"
#include "objects.h"
#include "scope.h"

string keywordNew(MavenCompiler* c, string entity, string element, string args, string& type) {
	string rawType = stripRawType(entity);
	int depth = ((element != "") ? 1 : 0);
	//cout << "entity = '" << entity << "', element = '" << element << "', args = '" << args << "', line = " << c->lineNumber << endl;
	
	// if this is a native type
	StringList types;
	MavenMutability mut;
	if(isDataType(rawType)) {
		type = appendArrayDepth(c, rawType, depth);
		string r = "new maven::" + rawType + "Array(" + dissectCode(c, element, types, mut) + ")";
		// bug #54: make sure types is 'int'
		return r;
	}
	
	// first make sure the class exists
	bool isEnum = false;
	type = appendArrayDepth(c, findMavenObjectPath(c, trim(entity)), depth);
	if(stripRawType(type) == MAVEN_INVALID) {
		if(enumExists(c, stripRawType(entity))) {
			isEnum = true;
			type = c->currentNamespace + "." + appendArrayDepth(c, entity, depth);
		} else {
			pushError(c, "Unknown class '%s'", stripRawType(type));
			return MAVEN_INVALID;
		}
	}
	
	int namespaceID, objectID;
	findClass(c, entity, namespaceID, objectID);
	
	// if its a single Object
	if(element == "") {
		string r = "new ";
		r += c->namespaces->at(namespaceID).name + "::" + c->namespaces->at(namespaceID).objects->at(objectID)->name;
		for(int i = 0; i < depth; ++i)
			r += "*";
		
		// args is assumed to be predissected.
		return r + "(" + args + ")";
	} else {
		string elements = dissectCode(c, element, types, mut);
		// bug #54: make sure types is 'int'
		
		string r = "new maven::";
		if(isEnum) {
			r += "int";
			rawType = "int";
			int nID = findNamespaceID(c, c->currentNamespace), enumID = findEnumID(c, nID, entity);
			if(trim(args) == "")
				args = intToString(c->namespaces->at(nID).enums[enumID].getDefaultValue());
		} else r += "object";
		
		string tempVar = getNextTempVariable(c);
		if(isDataType(rawType))
			c->beforeLine += rawType + "* " + tempVar + " = new " + rawType + "[" + elements + "];\n";
		else c->beforeLine += "maven::Object** " + tempVar + " = new maven::Object*[" + elements + "];\n";
		c->beforeLine += "for(int __INIT = 0; __INIT < " + elements + "; ++__INIT)\n";
		if(isDataType(rawType)) {
			if(trim(args) == "")
				args = "0";
			c->beforeLine += tempVar + "[__INIT] = " + args + ";\n";
		} else c->beforeLine += tempVar + "[__INIT] = (maven::Object*) new " + rawType + "(" + args + ");\n";
		
		r += "Array(" + elements + "," + tempVar + ")";
		return r;
	}
}
