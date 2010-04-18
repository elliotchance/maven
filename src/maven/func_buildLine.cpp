/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string buildLine(MavenCompiler* c, string bareword, string entity, string args) {
	string r = bareword + " ";
	if(entity != "")
		r += entity + "(" + args + ")";
	return r;
}
