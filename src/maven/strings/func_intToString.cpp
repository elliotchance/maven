/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string intToString(int value) {
	char buf[20]; 
	sprintf(buf, "%d", value);
	return buf;
}
