/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "objects.h"

bool pushFunction(MavenCompiler* c, int namespaceID, int objectID, MavenFunction func) {
	// bare functions must be public and static
	if(namespaceID == 0 && objectID == 0) {
		func.isPublic = true;
		func.isStatic = true;
	}
	
	// if its in an abstract class its static
	if(c->namespaces->at(namespaceID).objects->at(objectID)->isAbstract &&
	   func.name != "callMethodByName")
		func.isStatic = true;
	
	if(func.name == "getClassVariables")
		func.isStatic = false;
	
	// we will not allow a constructor to go into an abstract class
	if(c->namespaces->at(namespaceID).objects->at(objectID)->isAbstract &&
	   func.returnType == "<constructor>") {
		pushError(c, "You are not allowed to put a constructor into an abstract class");
		return false;
	}
	
	// normally here I would simply use findFunctionID(c, ) to see if the function existed, however
	// because inherited methods can be overloaded on multiple depths we need to have a manual
	// look through
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++i) {
		if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name == func.name &&
		   c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).getSignature() == func.getSignature()) {
			if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).isInherited) {
				// inherited function have to update the return type
				c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).returnType =
					findMavenObjectPath(c, func.returnType);
			} else {
				pushError(c, "Method %s already defined (previously defined at line %s)",
						  c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name +
						  "(" + c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).getSignature() + ")",
						  intToString(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).atLine));
				return false;
			}
		}
	}
	
	/*int functionID = findFunctionID(c, namespaceID, objectID, func.name, func.args, true);
	if(functionID >= 0) {
		// we are allowed to override inherited methods
		if(!namespaces->at(namespaceID).objects->at(objectID)->functions[functionID].isInherited) {
			
		}
	}*/
	
	// functions are also not allowed to have the same name as a variable (includes inherited)
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++i) {
		if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i).name == func.name) {
			pushError(c, "You can not define the function %s(%s) with the same name as a variable member", func.name, func.getSignature());
			return MAVEN_INVALID;
		}
	}
	
	// push function
	c->namespaces->at(namespaceID).objects->at(objectID)->functions->push(func);
	return true;
}
