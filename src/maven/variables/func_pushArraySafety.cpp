/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "objects.h"

void pushArraySafety(MavenCompiler* c, string var, string element) {
	pushObjectCheck(c, element + " >= " + var + "->length",
					"throw new maven::BoundsException(new maven::String((std::string(\"Accessing " +
					unresolveMavenPath(c, var) + " at element \") + maven::String::valueOf((int) " +
					element + ")->s + \" when the array only contains \" + maven::String::valueOf((int) " +
					var + "->length)->s + \" elements.\\n\").c_str()), new maven::String(\"" +
					c->currentFile + "\"), " + intToString(c->lineNumber) + ");");
}
