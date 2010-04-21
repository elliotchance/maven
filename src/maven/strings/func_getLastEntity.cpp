/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"

string getLastEntity(string str) {
	StringList items = split('.', str);
	return items[items.length() - 1];
}
