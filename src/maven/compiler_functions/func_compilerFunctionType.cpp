/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"

string compilerFunctionType(MavenCompiler* c, string signature) {
	return "new maven::String(\"" + signature + "\")";
}
