/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_INIT_H
#define _MAVEN_INIT_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

void stripHyphen(string& key, string& value);
void processProgramArguments(MavenCompiler* c, int argc, char** argv);
void printErrorsAndWarnings(MavenCompiler* c);
int main(int argc, char** argv);
void init(MavenCompiler* c);
void finish(MavenCompiler* c);
void clean(MavenCompiler* c);

#endif
