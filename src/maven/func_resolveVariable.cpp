/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_constants.h"

string resolveVariable(MavenCompiler* c, string entity, MavenVariable& v, int& namespaceID,
					   int& objectID, bool& isLocal, bool forFunction) {
	// the difficulty with this is that the number of dots doesnt indicate which part (if any)
	// is the namespace, class, variable and subvariables. So the way we do it is to try the first
	// part as a namespace, then try it as a class etc
	if(entity == "")
		return "";
	
	// safety
	vector<int> ambig;
	namespaceID = -1;
	objectID = -1;
	int enumID = -1;
	isLocal = false;
	
	// the order in which a variable is searched for it important and goes as follows
	// 1. 'with' statement
	// 2. a compiler variable
	// 3. enum element
	// 4. in localScope
	// 5. in the current class (this include inherited variables)
	// 6. the name of a namespace
	// 7. the name of a class
	// 8. the name of an enum object
	// 9. the name of a function name (for @selector)
	
	// bug #14: 1. 'with' statement
	if(c->withObject.name != "" && entity.substr(0, c->withObject.name.length()) != c->withObject.name) {
		pushError(c, "maven does not support the 'with' statement");
		return MAVEN_INVALID;
	}
	
	// 2. a compiler variable
	if(entity[0] == '@') {
		v = getCompilerVariable(c, entity);
		if(v.name == MAVEN_INVALID) {
			pushError(c, "Unknown compiler variable %s", entity);
			return MAVEN_INVALID;
		}
		return v.defaultValue;
	}
	
	// 3. enum element
	int elementID = findEnumElement(c, entity, namespaceID, enumID);
	if(elementID == -2) {
		pushError(c, "Ambiguous enum element '%s'", entity);
		v.type = MAVEN_AMBIGUOUS;
		return MAVEN_INVALID;
	} else if(elementID >= 0) {
		v.type = c->namespaces->at(namespaceID).name + "." +
				 c->namespaces->at(namespaceID).enums[enumID].name;
		return intToString(c->namespaces->at(namespaceID).enums[enumID].items[elementID].value);
	}
	
	// 4. look in the localScope
	for(int i = 0; i < c->localScope.size(); ++i) {
		for(int j = 0; j < c->localScope[i].length(); ++j) {
			if(c->localScope[i][j].name == entity) {
				v = c->localScope[i][j];
				isLocal = true;
				return c->localScope[i][j].name;
			}
		}
	}
	
	// 5. it may be the current class (or even inherited)
	namespaceID = findNamespaceID(c, c->currentNamespace);
	objectID = findObjectID(c, namespaceID, c->currentClass);
	if(namespaceID >= 0 && objectID >= 0) {
		for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++i) {
			if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i).name == entity) {
				v = c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i);
				string r = entity;
				
				if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i).isStatic)
					r = c->currentNamespace + "::" + c->currentClass + "$static::" + r;
				
				return r;
			}
		}
	}
	
	// now look through all bare classes
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).objects->at(0)->variables->length(); ++j) {
			if(c->namespaces->at(i).objects->at(0)->variables->at(j).name == entity) {
				ambig.push_back(i);
				v = c->namespaces->at(i).objects->at(0)->variables->at(j);
			}
		}
	}
	
	if(ambig.size() == 1) {
		namespaceID = ambig[0];
		objectID = findObjectID(c, namespaceID, "nil");
		return c->namespaces->at(namespaceID).name + "::nil$static::" + entity;
	} else if(ambig.size() > 1) {
		string belong = "";
		for(int i = 0; i < ambig.size(); ++i) {
			if(belong != "")
				belong += ", ";
			belong += c->namespaces->at(ambig[i]).name;
		}
		pushError(c, "%s is ambiguous, belonging to %s", entity, belong);
	}
	
	// 6. the name of a namespace
	namespaceID = findNamespaceID(c, entity);
	if(namespaceID >= 0) {
		v.name = c->namespaces->at(namespaceID).name;
		v.type = "<Namespace: " + v.name + ">";
		return c->namespaces->at(namespaceID).name;
	}
	
	// 7. the name of a class
	findClass(c, entity, namespaceID, objectID);
	if(namespaceID >= 0 && objectID >= 0) {
		v.name = c->namespaces->at(namespaceID).name + "." +
				 c->namespaces->at(namespaceID).objects->at(objectID)->name;
		v.type = "<Class: " + v.name + ">";
		return c->namespaces->at(namespaceID).name + "::" +
		c->namespaces->at(namespaceID).objects->at(objectID)->name;
	}
	
	// 8. the name of an enum object
	namespaceID = findNamespaceID(c, c->currentNamespace);
	enumID = findEnumID(c, namespaceID, entity);
	if(enumID >= 0) {
		v.name = c->namespaces->at(namespaceID).name + "." +
				 c->namespaces->at(namespaceID).enums[enumID].name;
		v.type = "<Enum: " + v.name + ">";
		return c->namespaces->at(namespaceID).name + "::" +
			   c->namespaces->at(namespaceID).enums[enumID].name;
	}
	
	// 9. we have to allow bar function names (that look like variable names)
	// to be left alone for @selector(), so lets first try it as a function
	namespaceID = findNamespaceID(c, c->currentNamespace);
	objectID = findObjectID(c, namespaceID, c->currentClass);
	if(namespaceID >= 0 && objectID >= 0) {
		for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++i) {
			if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name == entity) {
				v.type = "<Function: " + intToString(namespaceID) + "," + intToString(objectID) + "," +
					intToString(i) + ">";
				return entity;
			}
		}
	}
	
	pushError(c, "Can not resolve variable %s", entity);
	return MAVEN_INVALID;
}
