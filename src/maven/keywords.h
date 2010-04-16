/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "config.h"
#include "structs.h"
#include "maven.h"

using namespace std;

// keyword_catch.h
MAVEN_DECL string keywordCatch(MavenCompiler* c, string line, MavenVariable& catchVar);

// keyword_else.h
MAVEN_DECL bool   keywordElse(MavenCompiler* c, string line, string& close);

// keyword_enum.h
MAVEN_DECL bool   keywordEnum(MavenCompiler* c, string identifer, string code);

// keyword_for.h
MAVEN_DECL bool   keywordFor(MavenCompiler* c, string line, string& close);

// keyword_if.h
MAVEN_DECL bool   keywordIf(MavenCompiler* c, string line, string& close);

// keyword_new.h
MAVEN_DECL string keywordNew(MavenCompiler* c, string entity, string element, string args, string& type);
MAVEN_DECL string appendArrayDepth(MavenCompiler* c, string type, int depth);

// keyword_return.h
MAVEN_DECL string keywordReturn(MavenCompiler* c, string line);

// keyword_throw.h
MAVEN_DECL string keywordThrow(MavenCompiler* c, string line);

// keyword_while.h
MAVEN_DECL bool   keywordWhile(MavenCompiler* c, string line, string& close);

// keyword_extends.h
MAVEN_DECL void   extendObject(MavenCompiler* c, MavenObject* o, string extendClass);

// keyword_import.h
MAVEN_DECL bool   includeLibraryIfExists(MavenCompiler* c, string import);
MAVEN_DECL bool   fileExists(string path);
MAVEN_DECL bool   alreadyImported(MavenCompiler* c, string file);
MAVEN_DECL string locateImport(MavenCompiler* c, string import);
MAVEN_DECL bool   importAll(MavenCompiler* c, string import, bool compiling);
