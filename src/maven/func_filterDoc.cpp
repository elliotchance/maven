/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string filterDoc(MavenCompiler* c, string comment) {
	string r = "";
	
	// first check if the tag is infact a doc tag
	if(comment.substr(0, 2) == "**")
		r = trim(comment.substr(2, comment.length() - 3));
	return r;
}
