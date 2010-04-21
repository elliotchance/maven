/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "scope.h"

using namespace std;

string keywordThrow(MavenCompiler* c, string line) {
	// throw is pretty simple, as long as you give it an allocated Object
	// extending Exception it should have no problem. I'm not quite sure
	// how to stictly test this, maybe come back to it later
	StringList types;
	MavenMutability mut;
	string newCode = dissectCode(c, line, types, mut);
	
	// bug #36: now we check that the throwable object is readable
	
	// bug #37: now we check the 'types' returned is an extension of Exception.
	
	return "throw " + newCode;
}
