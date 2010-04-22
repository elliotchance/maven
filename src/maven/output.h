/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_OUTPUT_H
#define _MAVEN_OUTPUT_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

void writeMapObject(MavenCompiler* c, int namespaceID, int objectID);
void writeMapFileLine(MavenCompiler* c, string line);
void writeMapFile(MavenCompiler* c);
void writeEntryPoint(MavenCompiler* c);
void writeCPPLine(MavenCompiler* c, string line);
void writeAutoCPPLine(MavenCompiler* c, string line);
bool fileWriteLine(ofstream& file, string line);
string cType(string type);

#endif
