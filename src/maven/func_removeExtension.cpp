/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string removeExtension(string file) {
	StringList parts = split('.', file);
	return parts.join(".", 0, parts.length() - 2);
}
