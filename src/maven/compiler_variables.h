/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL string stripRawType(string type);
MAVEN_DECL void   newLocalScope(MavenCompiler* c);
MAVEN_DECL void   deleteLocalScope(MavenCompiler* c);
MAVEN_DECL bool   isKeyword(MavenCompiler* c, string k);
MAVEN_DECL bool   registerVariable(MavenCompiler* c, StringList tokens, bool compiling, MavenVariable& v);
MAVEN_DECL int    getArrayDepth(string type);
MAVEN_DECL string stripArrayDepth(string type, int depth);
MAVEN_DECL bool   validEntityName(string name);
MAVEN_DECL bool   isRegisteringVariable(MavenCompiler* c, StringList tokens);
MAVEN_DECL string objectCheckCPP(MavenCompiler* c);
MAVEN_DECL bool   isRegisteringFunction(MavenCompiler* c, string line);
