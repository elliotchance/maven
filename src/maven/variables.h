/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_VARIABLES_H
#define _MAVEN_VARIABLES_H 1

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenVariable.h"

bool validEntityName(string name);
string stripRawType(string type);
string stripArrayDepth(string type, int depth);
string resolveVariable(MavenCompiler* c, string entity, MavenVariable& v, int& namespaceID,
					   int& objectID, bool& isLocal, bool forFunction);
bool registerVariable(MavenCompiler* c, StringList tokens, bool compiling, MavenVariable& v);
void pushVariable(MavenCompiler* c, int namespaceID, int objectID, MavenVariable var);
bool pushSelector(MavenCompiler* c, string name);
void pushArraySafety(MavenCompiler* c, string var, string element);
void newLocalScope(MavenCompiler* c);
bool isRegisteringVariable(MavenCompiler* c, StringList tokens);
string getNextTempVariable(MavenCompiler* c);
MavenVariable getCompilerVariable(MavenCompiler* c, string name);
int getArrayDepth(string type);
string findVariablePath(MavenCompiler* c, string entity, int& namespaceID, int& objectID, int& variableID);
int findVariableID(MavenCompiler* c, int namespaceID, int objectID, string variable);
MavenVariable dissectVariable(MavenCompiler* c, string line);
void deleteLocalScope(MavenCompiler* c);
int countStaticVariables(MavenCompiler* c, int namespaceID, int objectID);
string appendArrayDepth(MavenCompiler* c, string type, int depth);

#endif
