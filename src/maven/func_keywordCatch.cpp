/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_errors.h"
#include "compiler_find.h"

using namespace std;

string keywordCatch(MavenCompiler* c, string line, MavenVariable& catchVar) {
	// strip out the catch
	string newCatch = line.substr(line.find('(') + 1, line.length() - line.find('(') - 2);
	
	// this can only be 2 words
	StringList words = split(' ', newCatch);
	if(words.length() != 2) {
		pushError(c, "Expecting two words in catch");
		return MAVEN_INVALID;
	}
	
	// make sure the first word is the name of a class
	// bug #26: and its extended from maven.Exception
	int namespaceID, objectID;
	findClass(c, words[0], namespaceID, objectID);
	if(namespaceID < 0 || objectID < 0) {
		pushError(c, "Unknown exception class %s", words[0]);
		return MAVEN_INVALID;
	}
	
	// make catchVar
	catchVar.name = words[1];
	catchVar.type = c->namespaces[namespaceID].name + "." + c->namespaces[namespaceID].objects[objectID].name;
	
	// build C++ version of catch
	newCatch = c->namespaces[namespaceID].name + "::" + c->namespaces[namespaceID].objects[objectID].name + "* " + words[1];
	return "catch(" + newCatch + ")";
}
