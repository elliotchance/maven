/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_NAMESPACES_H
#define _MAVEN_NAMESPACES_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

void pushNamespace(MavenCompiler* c, string namespaceName);
int findNamespaceID(MavenCompiler* c, string namespaceName);

#endif
