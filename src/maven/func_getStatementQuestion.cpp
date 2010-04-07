/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string getStatementQuestion(string line, int& actionStart) {
	// skip to open bracket
	int start = 0, end = 0;
	for(; start < line.length(); ++start) {
		if(line[start] == '(') break;
	}
	++start;
	
	// skip to close bracket
	int bracketCount = 0;
	for(end = start; end < line.length(); ++end) {
		if(line[end] == '(')
			++bracketCount;
		else if(line[end] == ')') {
			if(!bracketCount) break;
			--bracketCount;
		}
	}
	
	actionStart = end + 1;
	return trim(line.substr(start, end - start));
}
