/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"

string basename(string path) {
	StringList parts = split('/', path);
	return parts[parts.length() - 1];
}