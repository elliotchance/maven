/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_GNU_H
#define _MAVEN_GNU_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

MAVEN_DECL void gnuCompile(MavenCompiler* c);
MAVEN_DECL void gnuLink(MavenCompiler* c);

#endif
