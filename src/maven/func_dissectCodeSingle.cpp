/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string dissectCodeSingle(MavenCompiler* c, string bareword, string entity, string element, string args, string signature, string& type, MavenMutability& mut, string nextop) {
	
	// bareword is for things such as variable names and like: 3, new, "A String" etc
	// entity is for things like functions, classes, objects etc
	
	// or not
	MavenFunction f;
	string resolve = ""; //resolveFunction(c, entity, f, signature, namespaceID, objectID, args);
	
	// calling a Selector
	if(f.returnType.substr(0, 5) == "<call") {
		type = f.returnType.substr(6, f.returnType.length() - 7);
		StringList splitArgs = splitCommas(args);
		string r = "*((" + type + "*) " + resolve + "->call(";
		for(int i = 0; i < splitArgs.length(); ++i) {
			if(i > 0) r += ",";
			r += "maven::Selector::voidise(" + splitArgs[i] + ")";
		}
		r += "))";
		return r;
	}
	
	type = MAVEN_INVALID;
	return MAVEN_INVALID;
}
