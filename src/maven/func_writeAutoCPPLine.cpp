/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_compilefile.h"
#include "compiler_push.h"

void writeAutoCPPLine(MavenCompiler* c, string line) {
	if(c->currentFunction == "") pushEntryLine(c, line);
	else writeCPPLine(c, line);
}
