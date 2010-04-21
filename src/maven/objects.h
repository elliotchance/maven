/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_OBJECTS_H
#define _MAVEN_OBJECTS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

bool pushObject(MavenCompiler* c, int namespaceID, MavenObject* obj);
void pushObjectCheck(MavenCompiler* c, string test, string action);
void pushObjectSafety(MavenCompiler* c, string test);
bool objectExists(MavenCompiler* c, string name);
string objectCheckCPP(MavenCompiler* c);
string nativeToObject(string type);
int findObjectID(MavenCompiler* c, int namespaceID, string objectName);
string findMavenObjectPath(MavenCompiler* c, string entity);
vector<int> findClass(MavenCompiler* c, string entity, int& namespaceID, int& objectID);
string findObjectPath(MavenCompiler* c, string entity, bool includePointer = true);
MavenObject* dissectObject(MavenCompiler* c, string line);
int countClassMethods(MavenCompiler* c, int namespaceID, int objectID);
string unresolveMavenPath(MavenCompiler* c, string path);

#endif
