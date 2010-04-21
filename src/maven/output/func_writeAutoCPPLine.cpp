/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "output.h"
#include "compiler.h"

void writeAutoCPPLine(MavenCompiler* c, string line) {
	if(c->currentFunction == "")
		pushEntryLine(c, line);
	else writeCPPLine(c, line);
}
