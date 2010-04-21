/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_COMPILER_H
#define _MAVEN_COMPILER_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

string buildLine(MavenCompiler* c, string bareword, string entity, string args);
bool compileFile(MavenCompiler* c, string file, int mode);
bool compileLine(MavenCompiler* c, string line);
void printAllNamespaces(MavenCompiler* c);
void die(string message);
bool mapLine(MavenCompiler* c, string line);
void pushEntryLine(MavenCompiler* c, string line);
bool resetCurrent(MavenCompiler* c, string file, string namespaceName, int newLineNumber);
void usage();

#endif
