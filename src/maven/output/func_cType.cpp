/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "constants.h"

string cType(string type) {
	if(isDataType(type))
		return "m" + type;
	return type;
}
