/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_push.h"
#include "compiler_resolve.h"

void pushObjectSafety(MavenCompiler* c, string test) {
	test = trim(test);
	
	// ignore some variables that we know are OK
	if(test == "((maven::System*)global::nil$static::System)" || test == "this")
		return;
	
	pushObjectCheck(c, test + " == 0", "throw new maven::ObjectNilException(new maven::String(\"" +
					unresolveMavenPath(c, test) + " is nil\\n\"), new maven::String(\"" + c->currentFile + "\"), " +
					intToString(c->lineNumber) + ");");
}
