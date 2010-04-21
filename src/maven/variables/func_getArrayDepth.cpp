/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

int getArrayDepth(string type) {
	// very pseudo, this should be improved
	int depth = 0;
	for(int i = 0; i < type.length(); ++i)
		if(type[i] == '[') ++depth;
	return depth;
}
