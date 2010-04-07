/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL string compilerFunctionCast(MavenCompiler* c, string signature, string args, string& type);
MAVEN_DECL string compilerFunctionSelector(MavenCompiler* c, string signature, string args, string& type);
MAVEN_DECL string compilerFunctionType(MavenCompiler* c, string signature, string args, StringList& types);
