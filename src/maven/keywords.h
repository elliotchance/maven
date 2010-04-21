/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_KEYWORDS_H
#define _MAVEN_KEYWORDS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

string getImportName(MavenCompiler* c, string import);
string locateImport(MavenCompiler* c, string import);
bool keywordWhile(MavenCompiler* c, string line, string& close);
string keywordThrow(MavenCompiler* c, string line);
string keywordReturn(MavenCompiler* c, string line);
string keywordNew(MavenCompiler* c, string entity, string element, string args, string& type);
bool keywordIf(MavenCompiler* c, string line, string& close);
bool keywordFor(MavenCompiler* c, string line, string& close);
bool keywordEnum(MavenCompiler* c, string identifier, string code);
bool keywordElse(MavenCompiler* c, string line, string& close);
string keywordCatch(MavenCompiler* c, string line, MavenVariable& catchVar);
bool isReservedWord(MavenCompiler* c, string word);
bool isKeyword(MavenCompiler* c, string k);
bool importAll(MavenCompiler* c, string import, bool compiling);
void extendObject(MavenCompiler* c, MavenObject* o, string extendClass);
void extendObject(MavenCompiler* c, MavenObject* o, string extendClass);
bool alreadyImported(MavenCompiler* c, string file);

#endif
