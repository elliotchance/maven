/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

void skipWhitespace(string& str, int& cursor) {
	for(; cursor < str.length(); ++cursor)
		if(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n' && str[cursor] != '\r')
			return;
}
