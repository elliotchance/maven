/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string getLastEntity(string str) {
	StringList items = split('.', str);
	return items[items.length() - 1];
}
