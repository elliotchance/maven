/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_OBJECTDISCOVERY_H
#define _MAVEN_STRUCT_OBJECTDISCOVERY_H 1

#include "maven.h"

struct MavenObjectDiscovery {
	int namespaceID;
	int objectID;
	
	MavenObjectDiscovery(int nID, int oID);
};

#endif
