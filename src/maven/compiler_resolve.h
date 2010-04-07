/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL string resolveVariable(MavenCompiler* c, string entity, MavenVariable& v, int& namespaceID, int& objectID, bool& isLocal, bool forFunction);
MAVEN_DECL string unresolveMavenPath(MavenCompiler* c, string path);
MAVEN_DECL string getNextTempVariable(MavenCompiler* c);
