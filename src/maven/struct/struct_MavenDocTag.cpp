/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "../struct_MavenDocTag.h";
#include "../strings.h"

bool MavenDocTag::inUse() {
	if(trim(body) != "")
		return true;
	if(trim(tagBrief) != "")
		return true;
	if(tagParam.length() > 0)
		return true;
	if(trim(tagReturn) != "")
		return true;
	if(trim(tagSince) != "")
		return true;
	if(tagThrows.length() > 0)
		return true;
	if(trim(tagVersion) != "")
		return true;
	
	return false;
}
