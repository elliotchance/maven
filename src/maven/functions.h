/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_FUNCTIONS_H
#define _MAVEN_FUNCTIONS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

bool pushFunction(MavenCompiler* c, int namespaceID, int objectID, MavenFunction func);
bool isRegisteringFunction(MavenCompiler* c, string line);
string findFunctionPath(MavenCompiler* c, string entity, MavenVariables args, int& namespaceID, int& objectID, int& funcID);
int findFunctionID(MavenCompiler* c, int namespaceID, int objectID, string function, MavenVariables args, bool strict = false);
MavenFunction dissectFunction(MavenCompiler* c, string line);
void dissectCodeArguments(MavenCompiler* c, string& rawargs, string& blocktype);
MavenVariables dissectArguments(MavenCompiler* c, string line);

#endif
