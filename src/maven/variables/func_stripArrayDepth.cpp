/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "strings.h"
#include "variables.h"

string stripArrayDepth(string type, int depth) {
	// if the depth we are trying to remove is greater than the depth of the
	// type we have a problem. Not sure how to deal with this yet...
	if(getArrayDepth(type) > depth)
		return MAVEN_INVALID;
	
	// this is also a fairly pseudo method for removing elements, this
	// method assumes the person has matching [ and ]
	int end = type.length() - 1;
	for(int depthCount = 0; depthCount < depth && end >= 0; --end)
		if(type[end] == '[') ++depthCount;
	
	return trim(type.substr(0, end + 1));
}
