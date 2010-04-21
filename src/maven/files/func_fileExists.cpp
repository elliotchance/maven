/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

bool fileExists(string path) {
	struct stat stFileInfo;
	int intStat = stat(path.c_str(), &stFileInfo);
	return (intStat == 0);
}
