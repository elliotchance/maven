/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL void clean(MavenCompiler* c);
MAVEN_DECL void evalINILine(MavenCompiler* c, string line, string& header);
MAVEN_DECL void finish(MavenCompiler* c);
MAVEN_DECL void init(MavenCompiler* c);
MAVEN_DECL void readINI(MavenCompiler* c);
MAVEN_DECL bool resetCurrent(MavenCompiler* c, string file, string namespaceName, int newLineNumber = 1);
MAVEN_DECL void processProgramArguments(MavenCompiler* c, int argc, char** argv);
MAVEN_DECL void die(string message);
MAVEN_DECL void usage();
