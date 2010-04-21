/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

string objectCheckCPP(MavenCompiler* c) {
	// bug #53: these Strings need to be on the constant stack
	
	// "if(" + c->objectCheck[i] + " == 0) throw new maven::ObjectNilException(new maven::String(\"" + unresolveMavenPath(c, c->objectCheck[i]) + " is nil\\n\"), new maven::String(\"" + c->currentFile + "\"), " + intToString(c->lineNumber) + ");
	// "if(" + c->objectBoundsCheck[i] + ") throw new maven::BoundsException(new maven::String(\"Accessing " + unresolveMavenPath(c, c->objectBoundsCheck[i]) + " at element ? when the array only contains ? elements.\\n\"), new maven::String(\"" + c->currentFile + "\"), " + intToString(c->lineNumber) + ");\n"
	
	
	string check = "";
	if(c->objectCheck.size() > 0) {
		for(int i = 0; i < c->objectCheck.size(); ++i)
			check += "if(" + c->objectCheck[i].key + ") { " + c->objectCheck[i].value + " }\n";
		c->objectCheck.clear();
	}
	
	return check;
}
