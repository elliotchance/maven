/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

string appendArrayDepth(MavenCompiler* c, string type, int depth) {
	for(int i = 0; i < depth; ++i)
		type += "[]";
	return type;
}
