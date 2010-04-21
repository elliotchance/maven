/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string trim(string line) {
	int left = 0, right = line.length() - 1, off = 0;
	
	// start
	for(; left < line.length(); ++left)
		if(!isspace(line[left]))
			break;
	
	// end
	for(; right >= 0; --right, ++off)
		if(!isspace(line[right]))
			break;
	
	return line.substr(left, line.length() - left - off);
}
