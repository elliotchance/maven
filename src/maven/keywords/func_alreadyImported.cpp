/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

bool alreadyImported(MavenCompiler* c, string file) {
	for(int i = 0; i < c->imports.size(); ++i)
		if(c->imports[i] == file) return true;
	return false;
}
