/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

// FIXME: these dont really need to be here
string getLastEntity(string str) {
	StringList items = split('.', str);
	return items[items.length() - 1];
}
