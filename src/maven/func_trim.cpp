/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string trim(string line) {
	int left = 0, right = line.length() - 1, off = 0;
	for(; left < line.length(); ++left)
		if(line[left] != ' ' && line[left] != '\t' && line[left] != '\n')
			break;
	for(; right >= 0; --right, ++off)
		if(line[right] != ' ' && line[right] != '\t' && line[right] != '\n')
			break;
	return line.substr(left, line.length() - left - off);
}
