/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "strings.h"

string getNextTempVariable(MavenCompiler* c) {
	return "_temp" + intToString(c->UID++);
}
