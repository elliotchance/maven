/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isKeyword(MavenCompiler* c, string k) {
	for(int i = 0; i < c->reservedWords.length(); ++i)
		if(k == c->reservedWords[i]) return true;
	return false;
}
