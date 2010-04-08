/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

/**
 * This function is for splitting nested curly bracket-less statements.
 */
StringList splitNested(string str) {
	StringList r;
	string temp;
	int bracketCount = 0;
	for(int i = 0; i < str.length(); ++i) {
		temp += str[i];
		if(str[i] == '(') ++bracketCount;
		else if(str[i] == ')') {
			--bracketCount;
			if(!bracketCount) {
				r.push(trim(temp));
				temp = "";
			}
		}
	}
	return r;
}
