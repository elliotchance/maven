/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "strings.h"
#include "errors.h"
#include "objects.h"
#include "keywords.h"
#include "output.h"

MavenObject* dissectObject(MavenCompiler* c, string line) {
	MavenObject* o = new MavenObject();
	StringList tokens = smartTokens(line);
	o->line = c->lineNumber;
	
	int i;
	for(i = 0; i < tokens.length(); ++i) {
		if(tokens[i] == "class")
			break;
		else if(tokens[i] == "abstract")
			o->isAbstract = true;
	}
	o->name = tokens[i + 1];
	
	if(tokens.length() > i + 2) {
		if(tokens[i + 2] == "extends") {
			// make sure the we already know what the class is
			string path = cType(findObjectPath(c, tokens[i + 3]));
			if(path == MAVEN_INVALID) {
				pushError(c, "Unknown extended class %s", tokens[i + 3]);
				return o;
			}
			extendObject(c, o, tokens[i + 3]);
			return o;
		} else {
			pushError(c, "Expected 'extends' received '%s'", tokens[i + 2]);
		}
	}
	
	// all Objects have to extend Object. This needs to be fixed to check if Object
	// is already extended.
	extendObject(c, o, "maven.Object");
	
	return o;
}
