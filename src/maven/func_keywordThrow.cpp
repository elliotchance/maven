/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_dissect.h"

using namespace std;

string keywordThrow(MavenCompiler* c, string line) {
	// throw is pretty simple, as long as you give it an allocated Object
	// extending Exception it should have no problem. I'm not quite sure
	// how to stictly test this, maybe come back to it later
	StringList types;
	MavenMutability mut;
	string newCode = dissectCode(c, line, types, mut);
	
	// FIXME: now we check that the throwable object is readable
	
	// FIXME: now we check the 'types' returned is an extension of Exception.
	
	return "throw " + newCode;
}
