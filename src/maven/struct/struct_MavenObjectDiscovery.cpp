/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenObjectDiscovery.h"

using namespace std;

MavenObjectDiscovery::MavenObjectDiscovery(int nID, int oID) {
	namespaceID = nID;
	objectID = oID;
}
