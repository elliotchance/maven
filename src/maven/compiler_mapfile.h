/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL int  countStaticVariables(MavenCompiler* c, int namespaceID, int objectID);
MAVEN_DECL int  countClassMethods(MavenCompiler* c, int namespaceID, int objectID);
MAVEN_DECL bool mapLine(MavenCompiler* c, string line);
MAVEN_DECL void writeMapFileLine(MavenCompiler* c, string line);
MAVEN_DECL void writeMapObject(MavenCompiler* c, int namespaceID, int objectID);
MAVEN_DECL void writeMapFile(MavenCompiler* c);
MAVEN_DECL bool fileWriteLine(ofstream& file, string line);
