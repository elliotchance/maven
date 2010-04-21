/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

string buildLine(MavenCompiler* c, string bareword, string entity, string args) {
	string r = bareword + " ";
	if(entity != "")
		r += entity + "(" + args + ")";
	return r;
}
