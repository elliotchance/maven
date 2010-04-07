/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

StringList readDirectory(string path) {
	struct dirent *ep;
	DIR* dp = opendir(path.c_str());
	StringList r;
	if(dp != NULL) {
		while(ep = readdir(dp)) {
			if(ep->d_name[0] == '.') continue;
			r.push(ep->d_name);
		}
		closedir(dp);
	}
	return r;
}
