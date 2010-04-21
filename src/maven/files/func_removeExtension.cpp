/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"

string removeExtension(string file) {
	StringList parts = split('.', file);
	return parts.join(".", 0, parts.length() - 2);
}
