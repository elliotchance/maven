/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_constants.h"
#include "compiler_operators.h"

string validateOperator(MavenCompiler* c, string op, string type1, string type2, string& overloaded_function) {
	// bug #34: Add all the operators
	
	// overload check, find the base class
	int nID = -1, oID = -1;
	findClass(c, type1, nID, oID);
	if(nID >= 0 && oID >= 0) {
		// the operator we are looking for
		string opfunc = translateOperatorFunction("operator" + op);
		
		int i;
		for(i = 0; i < c->namespaces[nID].objects[oID].functions.length(); ++i) {
			if(c->namespaces[nID].objects[oID].functions[i].name == opfunc)
				break;
		}
		if(i < c->namespaces[nID].objects[oID].functions.length()) {
			overloaded_function = opfunc;
			return findMavenObjectPath(c, c->namespaces[nID].objects[oID].functions[i].returnType);
		}
	}
	
	// void is not allowed on either side
	if(type1 == "void" || type2 == "void")
		return MAVEN_INVALID;
	
	// if the types are the same and using =/== is always allowed
	if((op == "=" || op == "==") && type1 == type2)
		return type1;
	
	// boolean operators
	if(op == "==" || op == "<" || op == ">" || op == "<=" || op == ">=")
		return "boolean";
	
	// bitwise operators
	if(op == "&" || op == "&=" || op == "|" || op == "|=")
		return type1;
	
	// natural operators
	if(isDataType(type1) && isDataType(type2)) {
		// when using 2 native types the resulting type is the most powerful
		// of the two types
		if(getDataTypePrecedence(type1) > getDataTypePrecedence(type2))
			return type1;
		return type2;
	}
	
	// any Object can be assigned nil
	if(!isDataType(type1) && type2 == "nil") return "nil";
	
	// child objects
	if(type1 == "maven.Object" && !isDataType(type1))
		return type1;
	
	// enums
	int enumID1 = findEnumID(c, findNamespaceID(c, c->currentNamespace), type1);
	int enumID2 = findEnumID(c, findNamespaceID(c, c->currentNamespace), type2);
	if(enumID1 >= 0 && isDataType(type2))
		return "int";
	if(isDataType(type1) && enumID2 >= 0)
		return "int";
	if(enumID1 >= 0 && enumID2 >= 0)
		return "int";
	 
	// if we made it to here there was no explanation for what the operator is doing
	pushError(c, "Invalid operator '%s' between %s", op, "'" + type1 + "' and '" + type2 + "'");
	return MAVEN_INVALID;
}
