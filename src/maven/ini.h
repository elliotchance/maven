/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_INI_H
#define _MAVEN_INI_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

void readINI(MavenCompiler* c);
string locateMavenINI(MavenCompiler* c);
void evalINILine(MavenCompiler* c, string line, string& header);

#endif
