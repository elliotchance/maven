/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_COMPILER_FUNCTIONS_H
#define _MAVEN_COMPILER_FUNCTIONS_H 1

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"

string compilerFunctionCast(MavenCompiler* c, string signature, string args, string& type);
string compilerFunctionSelector(MavenCompiler* c, string signature, string args, string& type);
string compilerFunctionType(MavenCompiler* c, string signature, string args, StringList& types);
bool includeLibraryIfExists(MavenCompiler* c, string import);

#endif
