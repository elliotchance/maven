/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string getNextTempVariable(MavenCompiler* c) {
	return "_temp" + intToString(c->UID++);
}
