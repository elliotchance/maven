/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isReservedWord(MavenCompiler* c, string word) {
	for(int i = 0; i < c->reservedWords.length(); ++i)
		if(c->reservedWords[i] == word)
			return true;
	return false;
}
