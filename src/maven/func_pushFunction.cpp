/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"

bool pushFunction(MavenCompiler* c, int namespaceID, int objectID, MavenFunction func) {
	// bare functions must be public and static
	if(namespaceID == 0 && objectID == 0) {
		func.isPublic = true;
		func.isStatic = true;
	}
	
	// if its in an abstract class its static
	if(c->namespaces[namespaceID].objects[objectID].isAbstract &&
	   func.name != "callMethodByName")
		func.isStatic = true;
	
	if(func.name == "getClassVariables")
		func.isStatic = false;
	
	// we will not allow a constructor to go into an abstract class
	if(c->namespaces[namespaceID].objects[objectID].isAbstract &&
	   func.returnType == "<constructor>") {
		pushError(c, "You are not allowed to put a constructor into an abstract class");
		return false;
	}
	
	// normally here I would simply use findFunctionID(c, ) to see if the function existed, however
	// because inherited methods can be overloaded on multiple depths we need to have a manual
	// look through
	for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].functions.length(); ++i) {
		if(c->namespaces[namespaceID].objects[objectID].functions[i].name == func.name &&
		   c->namespaces[namespaceID].objects[objectID].functions[i].getSignature() == func.getSignature()) {
			if(c->namespaces[namespaceID].objects[objectID].functions[i].isInherited) {
				// inherited function have to update the return type
				c->namespaces[namespaceID].objects[objectID].functions[i].returnType =
					findMavenObjectPath(c, func.returnType);
			} else {
				pushError(c, "Method %s already defined (previously defined at line %s)",
						  c->namespaces[namespaceID].objects[objectID].functions[i].name +
						  "(" + c->namespaces[namespaceID].objects[objectID].functions[i].getSignature() + ")",
						  intToString(c->namespaces[namespaceID].objects[objectID].functions[i].atLine));
				return false;
			}
		}
	}
	
	/*int functionID = findFunctionID(c, namespaceID, objectID, func.name, func.args, true);
	if(functionID >= 0) {
		// we are allowed to override inherited methods
		if(!namespaces[namespaceID].objects[objectID].functions[functionID].isInherited) {
			
		}
	}*/
	
	// functions are also not allowed to have the same name as a variable (includes inherited)
	for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].variables.length(); ++i) {
		if(c->namespaces[namespaceID].objects[objectID].variables[i].name == func.name) {
			pushError(c, "You can not define the function %s(%s) with the same name as a variable member", func.name, func.getSignature());
			return MAVEN_INVALID;
		}
	}
	
	// push function
	c->namespaces[namespaceID].objects[objectID].functions.push(func);
	return true;
}
