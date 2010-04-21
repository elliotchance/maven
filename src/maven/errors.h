/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_ERRORS_H
#define _MAVEN_ERRORS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

bool isErrors(MavenCompiler* c);
bool isWarnings(MavenCompiler* c);
void printErrors(MavenCompiler* c);
void printWarnings(MavenCompiler* c);
bool pushError(MavenCompiler* c, string message);
bool pushError(MavenCompiler* c, string message, string arg);
bool pushError(MavenCompiler* c, string message, string arg1, string arg2);
bool pushWarning(MavenCompiler* c, string message);
bool pushWarning(MavenCompiler* c, string message, string arg);
bool pushWarning(MavenCompiler* c, string message, string arg1, string arg2);
void reverseErrors(MavenCompiler* c, int start, int len);

#endif
