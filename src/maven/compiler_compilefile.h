/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL bool compileBlock(MavenCompiler* c, string identifier, string code, int mode);

MAVEN_DECL bool compileFile(MavenCompiler* c, string file, int mode);

MAVEN_DECL bool compileLine(MavenCompiler* c, string line);

MAVEN_DECL StringList splitNested(string str);

MAVEN_DECL void writeAutoCPPLine(MavenCompiler* c, string line);

MAVEN_DECL void writeCPPLine(MavenCompiler* c, string line);

MAVEN_DECL void writeEntryPoint(MavenCompiler* c);
