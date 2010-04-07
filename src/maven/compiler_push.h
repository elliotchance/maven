/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL void pushObjectCheck(MavenCompiler* c, string test, string action);
MAVEN_DECL bool pushSelector(MavenCompiler* c, string name);
MAVEN_DECL void pushNamespace(MavenCompiler* c, string namespaceName);
MAVEN_DECL void pushLocalScope(MavenCompiler* c, MavenVariable var);
MAVEN_DECL void pushVariable(MavenCompiler* c, int namespaceID, int objectID, MavenVariable var);
MAVEN_DECL bool pushObject(MavenCompiler* c, int namespaceID, MavenObject obj);
MAVEN_DECL bool pushFunction(MavenCompiler* c, int namespaceID, int objectID, MavenFunction func);
MAVEN_DECL void pushEntryLine(MavenCompiler* c, string line);
MAVEN_DECL void pushArraySafety(MavenCompiler* c, string var, string element);
MAVEN_DECL void pushObjectSafety(MavenCompiler* c, string test);
