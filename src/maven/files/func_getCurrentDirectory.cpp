/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string getCurrentDirectory() {
	char* path = new char[1024];
	getcwd(path, 1024);
	return string(path);
}
