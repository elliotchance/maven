/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool alreadyImported(MavenCompiler* c, string file) {
	for(int i = 0; i < c->imports.size(); ++i)
		if(c->imports[i] == file) return true;
	return false;
}
