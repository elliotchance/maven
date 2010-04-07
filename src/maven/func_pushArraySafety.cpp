/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_push.h"
#include "compiler_strings.h"
#include "compiler_resolve.h"

void pushArraySafety(MavenCompiler* c, string var, string element) {
	pushObjectCheck(c, element + " >= " + var + "->length",
					"throw new maven::BoundsException(new maven::String((std::string(\"Accessing " +
					unresolveMavenPath(c, var) + " at element \") + maven::String::valueOf((int) " +
					element + ")->s + \" when the array only contains \" + maven::String::valueOf((int) " +
					var + "->length)->s + \" elements.\\n\").c_str()), new maven::String(\"" +
					c->currentFile + "\"), " + intToString(c->lineNumber) + ");");
}
