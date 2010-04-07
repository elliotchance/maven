/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_find.h"
#include "compiler_errors.h"

bool canCastBetween(MavenCompiler* c, string type1, string type2, bool strict, bool warn) {
	if(strict)
		return type1 == type2;
	
	// matching exact types is always OK
	if(type1 == type2)
		return true;
	
	// this function can take signatures (rather than just bare types)
	StringList types1 = split(',', type1);
	StringList types2 = split(',', type2);
	
	// if the number of arguments doesn't match then we know straight away it won't work
	if(types1.length() != types2.length())
		return false;
	
	if(types1.length() > 1) {
		for(int i = 0; i < types1.length(); ++i)
			if(!canCastBetween(c, types1[i], types2[i], strict, warn))
				return false;
		return true;
	}
	
	// FIXME: this should be smarter, for now we'll assume anything can be an Object
	if(type1 == "maven.Object" && !isDataType(type2))
		return true;
	
	// nil can be assigned to any Object
	if(!isDataType(type1) && type2 == "nil")
		return true;
	
	// if type1 is an enum, the typing is very strict. type2 must be exactly the same
	int enumID = findEnumID(c, findNamespaceID(c, c->currentNamespace), type1);
	if(enumID >= 0) {
		// an enum may be cast into an integer based type
		if(type2 == "int" || type2 == "long" || type2 == "float" ||
		   type2 == "double" || type2 == "quad" || type2 == "char" ||
		   type2 == "short")
			return true;
		
		// otherwise no
		return false;
	} else if(type1 == "boolean") {
		// definite
		return true;
	} else if(type1 == "byte") {
		// definite
		return true;
	} else if(type1 == "char") {
		// definite
		if(type2 == "boolean" || type2 == "char" || type2 == "double" ||
		   type2 == "float" || type2 == "int" || type2 == "long" ||
		   type2 == "quad" || type2 == "short")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "double") {
		// definite
		if(type2 == "boolean" || type2 == "quad")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte" || type2 == "char" || type2 == "float" || type2 == "int" ||
		   type2 == "long" || type2 == "short") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "float") {
		// definite
		if(type2 == "boolean" || type2 == "double" || type2 == "quad")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte" || type2 == "char" || type2 == "int" || type2 == "long" ||
		   type2 == "short") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "int") {
		// definite
		if(type2 == "boolean" || type2 == "double" || type2 == "long" || type2 == "quad")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte" || type2 == "char" || type2 == "float" || type2 == "short") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "long") {
		// definite
		if(type2 == "boolean" || type2 == "quad")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte" || type2 == "char" || type2 == "float" || type2 == "short" ||
		   type2 == "double" || type2 == "long" || type2 == "int") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "quad") {
		// definite
		if(type2 == "boolean")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte" || type2 == "char" || type2 == "double" ||
		   type2 == "float" || type2 == "int" || type2 == "long" || type2 == "short") {
			if(warn)
				pushWarning(c, "Possible loss in precision casting '%s' to '%s'", type1, type2);
			return true;
		}
		
		// can't do it
		return false;
	} else if(type1 == "short") {
		// definite
		if(type2 == "boolean" || type2 == "char" || type2 == "int" || type2 == "short" ||
		   type2 == "double" || type2 == "float" || type2 == "long" || type2 == "quad")
			return true;
		
		// may lose precision, but still works
		if(type2 == "byte")
			return true;
		
		// can't do it
		return false;
	}
	
	// we can have one type fit into another as long is it is extended
	// FIXME: we have to look at the inheritence of the inheritence, etc
	int nID1, oID1, nID2, oID2;
	findClass(c, type1, nID1, oID1);
	findClass(c, type2, nID2, oID2);
	if(nID1 >= 0 && oID1 >= 0 && nID2 >= 0 && oID2 >= 0) {
		StringList extends = split(',', c->namespaces[nID2].objects[oID2].extends);
		for(int i = 0; i < extends.length(); ++i)
			if(findMavenObjectPath(c, type1) == findMavenObjectPath(c, extends[i]))
				return true;
	}
	
	return false;
}
