/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL bool isErrors(MavenCompiler* c);
MAVEN_DECL bool isWarnings(MavenCompiler* c);
MAVEN_DECL void reverseErrors(MavenCompiler* c, int start, int len);
MAVEN_DECL void printWarnings(MavenCompiler* c);
MAVEN_DECL void printErrors(MavenCompiler* c);
MAVEN_DECL bool pushWarning(MavenCompiler* c, string message);
MAVEN_DECL bool pushWarning(MavenCompiler* c, string message, string arg);
MAVEN_DECL bool pushWarning(MavenCompiler* c, string message, string arg1, string arg2);
MAVEN_DECL bool pushError(MavenCompiler* c, string message);
MAVEN_DECL bool pushError(MavenCompiler* c, string message, string arg);
MAVEN_DECL bool pushError(MavenCompiler* c, string message, string arg1, string arg2);
MAVEN_DECL void printErrorsAndWarnings(MavenCompiler* c);
