/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool fileWriteLine(ofstream& file, string line) {
	file.write(line.c_str(), line.length());
	file.write("\n", 1);
	return true;
}
