/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string compilerFunctionType(MavenCompiler* c, string signature, string args, StringList& types) {
	types.setTypes("maven.String");
	return "new maven::String(\"" + signature + "\")";
}
