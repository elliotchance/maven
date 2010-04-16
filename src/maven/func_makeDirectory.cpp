/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool makeDirectory(string path) {
#if MAVEN_OS == 1
	system((string("mkdir -p \"") + path + "\"").c_str());
#elif MAVEN_OS == 2
	system((string("mkdir \"") + path + "\"").c_str());
#endif
	return true;
}
