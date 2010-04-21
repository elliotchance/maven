/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_ENUMS_H
#define _MAVEN_ENUMS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

bool enumExists(MavenCompiler* c, string name);
int findEnumElement(MavenCompiler *c, string entity, int& namespaceID, int& enumID);
int findEnumID(MavenCompiler* c, int namespaceID, string enumName);
string findMavenEnumPath(MavenCompiler* c, string entity);

#endif
