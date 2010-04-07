/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string appendArrayDepth(MavenCompiler* c, string type, int depth) {
	for(int i = 0; i < depth; ++i)
		type += "[]";
	return type;
}
