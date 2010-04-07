/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_dissect.h"
#include "compiler_variables.h"
#include "keywords.h"
#include "compiler_resolve.h"

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
		// FIXME: make sure types is 'int'
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
		r += c->namespaces[namespaceID].name + "::" + c->namespaces[namespaceID].objects[objectID].name;
		for(int i = 0; i < depth; ++i)
			r += "*";
		
		// args is assumed to be predissected.
		return r + "(" + args + ")";
	} else {
		string elements = dissectCode(c, element, types, mut);
		// FIXME: make sure types is 'int'
		
		string r = "new maven::";
		if(isEnum) {
			r += "int";
			rawType = "int";
			int nID = findNamespaceID(c, c->currentNamespace), enumID = findEnumID(c, nID, entity);
			if(trim(args) == "")
				args = intToString(c->namespaces[nID].enums[enumID].getDefaultValue());
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
