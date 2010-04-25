/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "errors.h"
#include "objects.h"
#include "namespaces.h"
#include "constants.h"
#include "operators.h"
#include "enums.h"

string validateOperator(MavenCompiler* c, string op, string type1, string type2, string& overloaded_function) {
	// bug #34: Add all the operators
	
	// overload check, find the base class
	int nID = -1, oID = -1;
	findClass(c, type1, nID, oID);
	if(nID >= 0 && oID >= 0) {
		// the operator we are looking for
		string opfunc = translateOperatorFunction("operator" + op);
		
		int i;
		for(i = 0; i < c->namespaces->at(nID).objects->at(oID)->functions->length(); ++i) {
			if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).name == opfunc)
				break;
		}
		if(i < c->namespaces->at(nID).objects->at(oID)->functions->length()) {
			overloaded_function = opfunc;
			return findMavenObjectPath(c, c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType);
		}
	}
	
	// void is not allowed on either side
	if(type1 == "void" || type2 == "void")
		return MAVEN_INVALID;
	
	// assignment of same types
	if(op == "=" && type1 == type2)
		return type1;
	
	// boolean operators for native types
	if((op == "<" || op == ">" || op == "<=" || op == ">=") && isDataType(type1) && isDataType(type2))
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
	
	// any Object can be compared to nil
	if(!isDataType(type1) && type2 == "nil" && (op == "===" || op == "!=="))
		return "boolean";
	if(!isDataType(type2) && type1 == "nil" && (op == "===" || op == "!=="))
		return "boolean";
	
	// child objects
	if(type1 == "maven.Object" && !isDataType(type1))
		return type1;
	
	// enums
	int cnID = findNamespaceID(c, c->currentNamespace);
	int enumID1 = findEnumID(c, cnID, type1);
	int enumID2 = findEnumID(c, cnID, type2);
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
