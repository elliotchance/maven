/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

bool resetCurrent(MavenCompiler* c, string file, string namespaceName, int newLineNumber) {
	c->currentClass = MAVEN_BARE_CLASS;
	c->currentFunction = "";
	c->currentNamespace = namespaceName;
	c->currentFile = file;
	c->lineNumber = newLineNumber;
	return true;
}
